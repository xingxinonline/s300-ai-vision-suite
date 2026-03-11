
/******************************************************************************\
 * Name        : testbench_dsp.c
 * Author      : Your name
 * Copyright   : Your copyright notice
 * Description : Hello World in C
\******************************************************************************/

/* includes */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "reg.h"
#include "kernel.h"
#include "dsp_mm.h"
#include "vec-c.h"
#include "face_detect.h"
#include "dsp_mailbox.h"
#include "control_proto.h"
#include "detection_protocol.h"
#include "face_detection_runtime_proto.h"

#include "custom_printf.h"

uint16_t display_width;
uint16_t display_height;
uint16_t snapshot_width;
uint16_t snapshot_height;

#define DISP_IMAGE_WIDTH            (display_width)
#define DISP_IMAGE_HEIGHT           (display_height)
#define SNAP_IMAGE_WIDTH            (snapshot_width)
#define SNAP_IMAGE_HEIGHT           (snapshot_height)

extern uint8_t bgr320_buffer1[160 * 120 * 3];

uint32_t wframe0_addr;
uint32_t wframe1_addr;
uint32_t rframe0_addr;
uint32_t rframe1_addr;
uint32_t alpha0_addr;
uint32_t alpha1_addr;

uint16_t *wframe0_buffer;
uint16_t *wframe1_buffer;
uint16_t *rframe0_buffer;
uint16_t *rframe1_buffer;
uint8_t *alpha0_buffer;
uint8_t *alpha1_buffer;

uint32_t times_cycles = 0;
uint32_t times_count = 0;
static uint32_t g_idle_cycles = 0u;
uint32_t face_detect_count  __attribute__((used, section(".sram1_data"), aligned(16))) = 0;

#define DSP_FEATURE_LEVEL           1u
#define DSP_MODEL_ALGO_ID           1u

typedef enum {
    DSP_CTRL_WAIT_HELLO = 0,
    DSP_CTRL_READY,
    DSP_CTRL_RESOURCE_ACCEPTED,
    DSP_CTRL_CONFIGURED,
    DSP_CTRL_RUNNING,
    DSP_CTRL_ERROR,
} DspControlState;

static DspControlState g_ctrl_state = DSP_CTRL_WAIT_HELLO;
static uint8_t g_ctrl_session_id = 0u;
static uint8_t g_heartbeat_seq = 0u;
static uint8_t g_video_resources_bound = 0u;
static uint8_t g_startup_log_emitted = 0u;

/*============================================================================
 * 多目标检测协议 - 双缓冲管理
 *============================================================================*/

/**
 * 检测结果双缓冲（静态分配在 DSP data 段）
 * 使用 aligned(16) 保证 DMA 友好对齐
 */
static DetectionResult_t g_detection_result_storage[2] __attribute__((aligned(16)));

/** 双缓冲指针数组 */
static DetectionResult_t *g_detection_result_buf[2];

/** 当前使用的缓冲区索引 */
static uint32_t g_detection_buf_index = 0;

/** 帧计数器（递增） */
static uint32_t g_detection_frame_counter = 0;

/**
 * @brief 将 DSP 本地地址转换为 M4 可访问地址
 * @param dsp_addr DSP 本地地址
 * @return M4 可访问的地址
 */
static inline uint32_t dsp_addr_to_m4(const void *dsp_addr)
{
    return (uint32_t)((uintptr_t)dsp_addr + DSP_PTCM_M4_BASE_OFFSET);
}

/**
 * @brief 初始化多目标检测缓冲区
 *
 * 设置双缓冲指针并初始化结构体头部
 */
static void detection_multi_init(void)
{
    // 设置双缓冲指针（指向静态分配的存储区）
    g_detection_result_buf[0] = &g_detection_result_storage[0];
    g_detection_result_buf[1] = &g_detection_result_storage[1];

    // 初始化两个缓冲区的头部
    for (int i = 0; i < 2; i++) {
        g_detection_result_buf[i]->magic        = DETECTION_RESULT_MAGIC;
        g_detection_result_buf[i]->version      = DETECTION_PROTOCOL_VERSION;
        g_detection_result_buf[i]->frame_id     = 0;
        g_detection_result_buf[i]->timestamp    = 0;
        g_detection_result_buf[i]->count        = 0;
        g_detection_result_buf[i]->selected_idx = -1;
    }

    g_detection_buf_index = 0;
    g_detection_frame_counter = 0;
}

/*============================================================================
 * 边界框过滤 - DSP 端过滤，确保与 M4 一致
 *============================================================================*/

/** 最小边界框尺寸（像素），过滤噪声检测 */
#define DSP_MIN_BOX_SIZE         16

/** 最小置信度阈值（score范围0.0-1.0，0.70表示70%置信度）
 *  提高阈值以减少小目标误检测 */
#define DSP_MIN_SCORE_THRESHOLD  0.80f

/** 最小面积百分比阈值（相对于 COORD_SPACE 面积）
 *  box < 5% 通常是误检测（背景噪声），应过滤 */
#define DSP_MIN_BOX_AREA_PCT     1

/** 坐标空间尺寸（与 M4 端 FACE_COORD_SPACE 一致） */
#define DSP_COORD_SPACE_W        160
#define DSP_COORD_SPACE_H        128

/**
 * @brief 校验边界框是否有效
 *
 * 与 M4 端 validate_box() 保持一致的过滤规则
 * 注意：score 范围是 0.0-1.0（与 face_detect.c 中 FaceRect.score 一致）
 *
 * @param x1, y1, x2, y2 边界框坐标
 * @param score 置信度 (0.0-1.0)
 * @return 1 有效，0 无效（应丢弃）
 */
static int is_box_valid(int32_t x1, int32_t y1, int32_t x2, int32_t y2, float score)
{
    /* 1. 置信度检查（主要过滤手段，score范围0.0-1.0） */
    if (score < DSP_MIN_SCORE_THRESHOLD) {
        return 0;
    }

    /* 2. 坐标顺序校正（确保 x1 < x2, y1 < y2）*/
    if (x2 < x1) { int32_t t = x1; x1 = x2; x2 = t; }
    if (y2 < y1) { int32_t t = y1; y1 = y2; y2 = t; }

    /* 3. 坐标范围检查（允许贴边，不做边缘裁剪） */
    if (x1 < 0 || y1 < 0) {
        return 0;
    }
    if (x2 > DSP_COORD_SPACE_W || y2 > DSP_COORD_SPACE_H) {
        return 0;
    }

    /* 4. 最小尺寸检查 */
    int32_t width  = x2 - x1;
    int32_t height = y2 - y1;
    if (width <= DSP_MIN_BOX_SIZE || height <= DSP_MIN_BOX_SIZE) {
        return 0;
    }

    /* 5. 最小面积百分比检查（过滤太小的误检测）
     *    日志显示 box=3%-4% 的目标多为误检测 */
    int32_t box_area = width * height;
    int32_t img_area = DSP_COORD_SPACE_W * DSP_COORD_SPACE_H;
    int32_t area_pct = (box_area * 100) / img_area;
    if (area_pct < DSP_MIN_BOX_AREA_PCT) {
        return 0;
    }

    return 1;
}

/**
 * @brief 填充多目标检测结果（带过滤）
 *
 * 将FaceRect数组过滤后转换为DetectionResult结构体
 * 只保留有效的边界框，确保 M4 端不需要再次过滤
 *
 * @param faces      检测到的人脸数组
 * @param face_count 检测到的人脸数量
 * @param timestamp  时间戳（毫秒）
 * @return 当前填充的DetectionResult指针
 */
static DetectionResult_t* detection_fill_result(const FaceRect *faces, int face_count, uint32_t timestamp)
{
    // 选择当前缓冲区
    DetectionResult_t *result = g_detection_result_buf[g_detection_buf_index];

    // 填充头部
    result->frame_id  = g_detection_frame_counter++;
    result->timestamp = timestamp;
    result->selected_idx = -1;

    // 限制输入数量
    int raw_count = (face_count > MAX_DETECTION_COUNT) ? MAX_DETECTION_COUNT : face_count;

    // 调试：打印所有原始检测框的置信度
    if (raw_count > 0) {
        rt_kprintf("[DSP:RAW] frame=%lu cnt=%d scores:", 
                   (unsigned long)g_detection_frame_counter, raw_count);
        for (int i = 0; i < raw_count; i++) {
            // score 范围是 0.0-1.0，转换为百分比整数打印
            int score_pct = (int)(faces[i].score * 100);
            rt_kprintf(" %d%%", score_pct);
        }
        rt_kprintf("\n");
    }

    // 过滤并填充有效检测框
    uint32_t valid_count = 0;
    for (int i = 0; i < raw_count; i++) {
        const FaceRect *src = &faces[i];

        // 边界框验证
        if (!is_box_valid(src->x1, src->y1, src->x2, src->y2, src->score)) {
            // 打印被过滤的框信息
            int score_pct = (int)(src->score * 100);
            rt_kprintf("[DSP:REJECT] idx=%d score=%d%% box=(%ld,%ld)-(%ld,%ld)\n",
                       i, score_pct,
                       (long)src->x1, (long)src->y1, (long)src->x2, (long)src->y2);
            continue;
        }

        // 复制有效框
        DetectionBox_t *dst = &result->boxes[valid_count];

        dst->score = src->score;
        dst->x1    = src->x1;
        dst->y1    = src->y1;
        dst->x2    = src->x2;
        dst->y2    = src->y2;

        // 确保坐标顺序正确
        if (dst->x2 < dst->x1) { int32_t t = dst->x1; dst->x1 = dst->x2; dst->x2 = t; }
        if (dst->y2 < dst->y1) { int32_t t = dst->y1; dst->y1 = dst->y2; dst->y2 = t; }

        // 复制5个关键点（10个坐标值）
        for (int j = 0; j < 10; j++) {
            dst->lm[j] = src->lm[j];
        }

        dst->type       = DETECTION_TYPE_FACE;
        dst->track_id   = 0;
        dst->vx         = 0;
        dst->vy         = 0;
        dst->speed      = 0;
        dst->kf_confidence = 0;
        dst->edge_flags = 0;
        dst->reserved   = 0;

        valid_count++;
    }

    result->count = valid_count;

    // 调试输出：如果有框被过滤
    if (raw_count > 0 && (int)valid_count != raw_count) {
        rt_kprintf("[DSP:FILTER] raw=%d valid=%lu\n", raw_count, (unsigned long)valid_count);
    }

    return result;
}

/**
 * @brief 发送多目标检测结果并切换缓冲区
 *
 * @param result 当前帧的检测结果
 */
static void detection_send_and_swap(DetectionResult_t *result)
{
    // 通过Mailbox发送多目标消息
    uint32_t msg = mailbox_send_multi_detection(result);

//    rt_kprintf("[DSP] TX frame=%d count=%d msg=0x%08X\n",
//               result->frame_id, result->count, msg);

    // 切换缓冲区
    g_detection_buf_index = 1 - g_detection_buf_index;
}

int32_t face_pos = 80;
int32_t face_pos_last = 80;

typedef uint16_t PIXEL565; // BGR565像素类型，2字节

PIXEL565 bgr565_buffer1[160 * 128] __attribute__((used, section(".face_data"), aligned(16))) ;

// 运行期上下文：集中管理缓冲区指针与分辨率参数，便于模块化
typedef struct {
    uint16_t *wframe0_buffer;
    uint16_t *wframe1_buffer;
    uint16_t *rframe0_buffer;
    uint16_t *rframe1_buffer;
    uint8_t  *alpha0_buffer;
    uint8_t  *alpha1_buffer;
    uint16_t display_width;
    uint16_t display_height;
    uint16_t snapshot_width;
    uint16_t snapshot_height;
} PipelineContext;

// 记录前处理的几何变换，用于通用坐标逆变换
typedef struct {
    int srcW, srcH;     // 原图尺寸
    int preW, preH;     // 旋转前的目标预处理尺寸（横屏:160x120，竖屏:120x160）
    int cropOx, cropOy; // 在原图中的裁剪偏移（相对原图左上角）
    int cropW, cropH;   // 裁剪后的区域尺寸（作为缩放输入尺寸）
    int rotated;        // 是否做了 CCW90 旋转（1竖屏，0横屏）
} Transform;

static const char *dsp_ctrl_state_name(DspControlState state)
{
    switch (state) {
    case DSP_CTRL_WAIT_HELLO:
        return "WAIT_HELLO";
    case DSP_CTRL_READY:
        return "READY";
    case DSP_CTRL_RESOURCE_ACCEPTED:
        return "RESOURCE_ACCEPTED";
    case DSP_CTRL_CONFIGURED:
        return "CONFIGURED";
    case DSP_CTRL_RUNNING:
        return "RUNNING";
    case DSP_CTRL_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

static void dsp_log_startup_banner(void)
{
    rt_kprintf("[DSP] ============================================\n");
    rt_kprintf("[DSP]   S300 DSP Face Detection Control Demo\n");
    rt_kprintf("[DSP] ============================================\n");
    rt_kprintf("[DSP] Control protocol: v%u.%u\n",
               (unsigned)((CONTROL_PROTOCOL_VERSION >> 8) & 0xFFu),
               (unsigned)(CONTROL_PROTOCOL_VERSION & 0xFFu));
    rt_kprintf("[DSP] Detection protocol: v%u.%u\n",
               (unsigned)((DETECTION_PROTOCOL_VERSION >> 8) & 0xFFu),
               (unsigned)(DETECTION_PROTOCOL_VERSION & 0xFFu));
    rt_kprintf("[DSP] Built: %s %s\n", __DATE__, __TIME__);
}

static void dsp_emit_startup_logs_once(void)
{
    if (g_startup_log_emitted != 0u) {
        return;
    }

    dsp_log_startup_banner();
    rt_kprintf("[DSP] buf[0] local=0x%08X m4=0x%08X\n",
               (uint32_t)(uintptr_t)g_detection_result_buf[0],
               dsp_addr_to_m4(g_detection_result_buf[0]));
    rt_kprintf("[DSP] buf[1] local=0x%08X m4=0x%08X\n",
               (uint32_t)(uintptr_t)g_detection_result_buf[1],
               dsp_addr_to_m4(g_detection_result_buf[1]));
    rt_kprintf("[DSP-CTRL] Waiting for CM4 control session\n");

    g_startup_log_emitted = 1u;
}

static void dsp_set_state(DspControlState next)
{
    if (g_ctrl_state != next) {
        rt_kprintf("[DSP-CTRL] %s -> %s\n",
                   dsp_ctrl_state_name(g_ctrl_state),
                   dsp_ctrl_state_name(next));
        g_ctrl_state = next;
    }
}

static ControlRunState_t dsp_get_run_state(void)
{
    switch (g_ctrl_state) {
    case DSP_CTRL_WAIT_HELLO:
        return CONTROL_RUN_STATE_INIT;
    case DSP_CTRL_READY:
    case DSP_CTRL_RESOURCE_ACCEPTED:
        return CONTROL_RUN_STATE_READY;
    case DSP_CTRL_CONFIGURED:
        return CONTROL_RUN_STATE_CONFIGURED;
    case DSP_CTRL_RUNNING:
        return CONTROL_RUN_STATE_RUNNING;
    case DSP_CTRL_ERROR:
    default:
        return CONTROL_RUN_STATE_ERROR;
    }
}

static void pipeline_context_reset(PipelineContext *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    wframe0_addr = 0;
    wframe1_addr = 0;
    rframe0_addr = 0;
    rframe1_addr = 0;
    alpha0_addr = 0;
    alpha1_addr = 0;
    wframe0_buffer = 0;
    wframe1_buffer = 0;
    rframe0_buffer = 0;
    rframe1_buffer = 0;
    alpha0_buffer = 0;
    alpha1_buffer = 0;
    display_width = 0;
    display_height = 0;
    snapshot_width = 0;
    snapshot_height = 0;
    g_video_resources_bound = 0u;
}

static void dsp_reset_control_session(PipelineContext *ctx, uint8_t session_id)
{
    g_ctrl_session_id = session_id;
    g_heartbeat_seq = 0u;
    pipeline_context_reset(ctx);
    detection_multi_init();
}

static void dsp_mailbox_reset_fifos(void)
{
    mailbox_clear_receive_fifo();
    mailbox_clear_send_fifo();
}

static void dsp_send_msg(uint32_t msg, const char *label)
{
    mailbox_write_data(msg);
    rt_kprintf("[DSP-CTRL] TX %-18s 0x%08X\n", label, msg);
}

static void dsp_send_ack(uint8_t kind, uint8_t code)
{
    dsp_send_msg(CONTROL_ACK_MAKE(kind, g_ctrl_session_id, code, CONTROL_ACK_OK), "ACK");
}

static void dsp_send_nack(uint8_t kind, uint8_t code, uint8_t err)
{
    dsp_send_msg(CONTROL_NACK_MAKE(kind, g_ctrl_session_id, code, err), "NACK");
}

static void dsp_send_status(uint8_t brief)
{
    dsp_send_msg(CONTROL_STATUS_MAKE(0u, g_ctrl_session_id, dsp_get_run_state(), brief), "STATUS");
}

static void dsp_send_heartbeat(void)
{
    dsp_send_msg(CONTROL_SYS_HEARTBEAT(g_ctrl_session_id, g_heartbeat_seq, dsp_get_run_state()),
                 "SYS.HEARTBEAT");
    g_heartbeat_seq++;
}

static void dsp_send_hello_ack(void)
{
    dsp_send_msg(
        CONTROL_SYS_HELLO_ACK(
            g_ctrl_session_id,
            CONTROL_BOOT_REASON_WARM_RESET,
            DSP_FEATURE_LEVEL,
            dsp_get_run_state()),
        "SYS.HELLO_ACK");
}

static void dsp_send_model_ready(void)
{
    dsp_send_msg(
        CONTROL_SYS_DSP_MODEL_READY(
            g_ctrl_session_id,
            DSP_MODEL_ALGO_ID,
            0u,
            dsp_get_run_state()),
        "SYS.DSP_MODEL_READY");
}

static void dsp_send_runtime_msg(uint32_t msg, const char *label)
{
    if (mailbox_write_data_nb(msg)) {
        rt_kprintf("[DSP-RT] TX %-18s 0x%08X\n", label, msg);
        return;
    }

    rt_kprintf("[DSP-RT] TX %-18s dropped\n", label);
}

static void dsp_request_mm_sync(uint32_t req, const char *label)
{
    dsp_send_runtime_msg(FD_RT_MAKE_MM_SYNC_REQ(req), label);
}

static int pipeline_bind_video_resources(PipelineContext *ctx)
{
    wframe0_addr = REG32(DSP_MM_BASE + 0x30);
    wframe1_addr = REG32(DSP_MM_BASE + 0x34);
    rframe0_addr = REG32(DSP_MM_BASE + 0x40);
    rframe1_addr = REG32(DSP_MM_BASE + 0x44);
    alpha0_addr  = REG32(DSP_MM_BASE + 0x48);
    alpha1_addr  = REG32(DSP_MM_BASE + 0x4C);

    display_width  = REG32(DSP_MM_BASE + 0x20) & 0x7FF;
    display_height = (REG32(DSP_MM_BASE + 0x20) & 0x3FF0000) >> 16;
    snapshot_width  = REG32(DSP_MM_BASE + 0x28) & 0x7FF;
    snapshot_height = (REG32(DSP_MM_BASE + 0x28) & 0x3FF0000) >> 16;

    if ((wframe0_addr == 0u) || (wframe1_addr == 0u) ||
        (alpha0_addr == 0u) || (alpha1_addr == 0u) ||
        (display_width == 0u) || (display_height == 0u) ||
        (snapshot_width == 0u) || (snapshot_height == 0u)) {
        return -1;
    }

    wframe0_buffer = (uint16_t *)wframe0_addr;
    wframe1_buffer = (uint16_t *)wframe1_addr;
    rframe0_buffer = (uint16_t *)rframe0_addr;
    rframe1_buffer = (uint16_t *)rframe1_addr;
    alpha0_buffer  = (uint8_t *)alpha0_addr;
    alpha1_buffer  = (uint8_t *)alpha1_addr;

    ctx->wframe0_buffer = wframe0_buffer;
    ctx->wframe1_buffer = wframe1_buffer;
    ctx->rframe0_buffer = rframe0_buffer;
    ctx->rframe1_buffer = rframe1_buffer;
    ctx->alpha0_buffer  = alpha0_buffer;
    ctx->alpha1_buffer  = alpha1_buffer;
    ctx->display_width  = display_width;
    ctx->display_height = display_height;
    ctx->snapshot_width  = snapshot_width;
    ctx->snapshot_height = snapshot_height;

    rt_kprintf("[DSP-CTRL] bind video display=%dx%d snapshot=%dx%d\n",
               display_width, display_height, snapshot_width, snapshot_height);

    size_t pix_count = (size_t)ctx->snapshot_width * (size_t)ctx->snapshot_height;
    for (size_t i = 0; i < pix_count; ++i) {
        ctx->wframe0_buffer[i] = 0xFFFF;
        ctx->wframe1_buffer[i] = 0xFFFF;
    }

    debug_test_dsp_mm();
    dsp_request_mm_sync(FD_RT_SYNC_REQ_CORE_REG_UPDATE, "MM.CORE_REG_UPDATE");
    dsp_request_mm_sync(FD_RT_SYNC_REQ_SPI_REG_UPDATE, "MM.SPI_REG_UPDATE");
    g_video_resources_bound = 1u;
    return 0;
}

static void dsp_handle_hello(PipelineContext *ctx, uint32_t msg)
{
    uint16_t arg = CONTROL_GET_ARG(msg);

    rt_kprintf("[DSP-CTRL] RX HELLO session=0x%02X proto=0x%04X\n",
               CONTROL_GET_SESSION(msg), arg);

    if (arg != CONTROL_PROTOCOL_VERSION) {
        g_ctrl_session_id = (uint8_t)CONTROL_GET_SESSION(msg);
        dsp_send_nack(CONTROL_RSP_KIND_SYS,
                      CONTROL_SYS_SUBTYPE_HELLO,
                      CONTROL_ERR_PROTOCOL_MISMATCH);
        dsp_set_state(DSP_CTRL_ERROR);
        return;
    }

    dsp_reset_control_session(ctx, (uint8_t)CONTROL_GET_SESSION(msg));
    dsp_emit_startup_logs_once();
    dsp_set_state(DSP_CTRL_READY);
    dsp_send_hello_ack();
}

static void dsp_handle_sys_message(PipelineContext *ctx, uint32_t msg)
{
    uint8_t subtype = (uint8_t)CONTROL_GET_SUBTYPE(msg);
    uint16_t arg = CONTROL_GET_ARG(msg);

    if (subtype == CONTROL_SYS_SUBTYPE_HELLO) {
        dsp_handle_hello(ctx, msg);
        return;
    }

    if (!control_msg_session_matches(msg, g_ctrl_session_id)) {
        rt_kprintf("[DSP-CTRL] session mismatch sys=0x%02X current=0x%02X\n",
                   CONTROL_GET_SESSION(msg), g_ctrl_session_id);
        dsp_send_nack(CONTROL_RSP_KIND_SYS, subtype, CONTROL_ERR_SESSION_MISMATCH);
        return;
    }

    switch (subtype) {
    case CONTROL_SYS_SUBTYPE_CM4_RESOURCE_READY: {
        uint8_t input_type = (uint8_t)CONTROL_RESOURCE_READY_GET_INPUT_TYPE(arg);
        uint8_t flags = (uint8_t)CONTROL_RESOURCE_READY_GET_FLAGS(arg);

        rt_kprintf("[DSP-CTRL] RX CM4_RESOURCE_READY input=%u flags=0x%02X slot=0x%02X\n",
                   input_type, flags, (unsigned)CONTROL_RESOURCE_READY_GET_CONFIG_SLOT(arg));

        if (input_type != CONTROL_INPUT_VIDEO) {
            dsp_send_nack(CONTROL_RSP_KIND_SYS, subtype, CONTROL_ERR_INVALID_CONFIG);
            dsp_set_state(DSP_CTRL_ERROR);
            return;
        }

        if ((flags & (CONTROL_RESOURCE_CAMERA_READY |
                      CONTROL_RESOURCE_MM_READY |
                      CONTROL_RESOURCE_LCD_READY)) !=
            (CONTROL_RESOURCE_CAMERA_READY |
             CONTROL_RESOURCE_MM_READY |
             CONTROL_RESOURCE_LCD_READY)) {
            dsp_send_nack(CONTROL_RSP_KIND_SYS, subtype, CONTROL_ERR_RESOURCE_NOT_READY);
            dsp_set_state(DSP_CTRL_ERROR);
            return;
        }

        if (pipeline_bind_video_resources(ctx) != 0) {
            dsp_send_nack(CONTROL_RSP_KIND_SYS, subtype, CONTROL_ERR_BUFFER_BIND_FAILED);
            dsp_set_state(DSP_CTRL_ERROR);
            return;
        }

        dsp_set_state(DSP_CTRL_RESOURCE_ACCEPTED);
        dsp_send_model_ready();
        return;
    }

    case CONTROL_SYS_SUBTYPE_START_STREAM:
        if (!g_video_resources_bound) {
            dsp_send_nack(CONTROL_RSP_KIND_SYS, subtype, CONTROL_ERR_MODEL_NOT_READY);
            return;
        }
        rt_kprintf("[DSP-CTRL] RX START_STREAM id=%u flags=0x%02X\n",
                   (unsigned)CONTROL_STREAM_GET_ID(arg),
                   (unsigned)CONTROL_STREAM_GET_FLAGS(arg));
        dsp_send_ack(CONTROL_RSP_KIND_SYS, CONTROL_SYS_SUBTYPE_START_STREAM);
        dsp_set_state(DSP_CTRL_RUNNING);
        return;

    case CONTROL_SYS_SUBTYPE_STOP_STREAM:
        rt_kprintf("[DSP-CTRL] RX STOP_STREAM\n");
        dsp_set_state(DSP_CTRL_CONFIGURED);
        dsp_send_ack(CONTROL_RSP_KIND_SYS, CONTROL_SYS_SUBTYPE_STOP_STREAM);
        return;

    case CONTROL_SYS_SUBTYPE_HEARTBEAT:
        rt_kprintf("[DSP-CTRL] RX HEARTBEAT seq=%u status=%u\n",
                   (unsigned)CONTROL_HEARTBEAT_GET_SEQ(arg),
                   (unsigned)CONTROL_HEARTBEAT_GET_STATUS(arg));
        dsp_send_heartbeat();
        return;

    default:
        rt_kprintf("[DSP-CTRL] RX SYS subtype=%u arg=0x%04X\n", subtype, arg);
        return;
    }
}

static void dsp_handle_cmd_message(uint32_t msg)
{
    uint8_t group = (uint8_t)CONTROL_GET_SUBTYPE(msg);
    uint16_t arg = CONTROL_GET_ARG(msg);
    uint8_t opcode = (uint8_t)CONTROL_CMD_GET_OPCODE(arg);

    if (!control_msg_session_matches(msg, g_ctrl_session_id)) {
        rt_kprintf("[DSP-CTRL] session mismatch cmd=0x%02X current=0x%02X\n",
                   CONTROL_GET_SESSION(msg), g_ctrl_session_id);
        dsp_send_nack(CONTROL_RSP_KIND_CMD, opcode, CONTROL_ERR_SESSION_MISMATCH);
        return;
    }

    rt_kprintf("[DSP-CTRL] RX CMD group=%u opcode=0x%02X arg=0x%02X\n",
               group, opcode, (unsigned)CONTROL_CMD_GET_ARG8(arg));

    if ((group == CONTROL_CMD_GRP_CONFIG) && (opcode == CONTROL_CMD_CONFIG_APPLY)) {
        if (!g_video_resources_bound) {
            dsp_send_nack(CONTROL_RSP_KIND_CMD, opcode, CONTROL_ERR_MODEL_NOT_READY);
            return;
        }
        dsp_send_ack(CONTROL_RSP_KIND_CMD, CONTROL_CMD_CONFIG_APPLY);
        return;
    }

    if ((group == CONTROL_CMD_GRP_BUFFER) && (opcode == CONTROL_CMD_BUFFER_BIND)) {
        if (!g_video_resources_bound) {
            dsp_send_nack(CONTROL_RSP_KIND_CMD, opcode, CONTROL_ERR_BUFFER_BIND_FAILED);
            return;
        }
        dsp_set_state(DSP_CTRL_CONFIGURED);
        dsp_send_ack(CONTROL_RSP_KIND_CMD, CONTROL_CMD_BUFFER_BIND);
        return;
    }

    dsp_send_nack(CONTROL_RSP_KIND_CMD, opcode, CONTROL_ERR_FEATURE_UNSUPPORTED);
}

static void dsp_poll_control_plane(PipelineContext *ctx)
{
    while (!mailbox_is_empty()) {
        uint32_t msg = mailbox_read_data();

        switch (CONTROL_GET_TYPE(msg)) {
        case CONTROL_MSG_TYPE_SYS:
            dsp_handle_sys_message(ctx, msg);
            break;
        case CONTROL_MSG_TYPE_CMD:
            dsp_handle_cmd_message(msg);
            break;
        default:
            rt_kprintf("[DSP-CTRL] RX ignored 0x%08X\n", msg);
            break;
        }
    }
}

static void dsp_log_idle_state(void)
{
    if ((g_idle_cycles == 0u) || ((g_idle_cycles % 10000000u) != 0u)) {
        return;
    }

    rt_kprintf("[DSP-CTRL] idle state=%s session=0x%02X hb=%lu drops=%lu\n",
               dsp_ctrl_state_name(g_ctrl_state),
               (unsigned)g_ctrl_session_id,
               (unsigned long)g_heartbeat_seq,
               (unsigned long)mailbox_get_drop_count());
    g_idle_cycles = 0u;
}

/**
 * 在同一块内存中对BGR565图像进行原地缩小
 * 使用最邻近插值，从右下向左上遍历，避免数据覆盖问题。
 *
 * @param image      输入与输出的图像缓冲区
 * @param orig_width 原始图像宽度
 * @param orig_height原始图像高度
 * @param new_width  缩小后的图像宽度
 * @param new_height 缩小后的图像高度
 * @return 0 表示成功，-1 表示失败
 */
int in_place_downscale_bgr565(PIXEL565* image,
                              int orig_width, int orig_height,
                              int new_width, int new_height) {
    if (!image) {
        return -1;
    }

    // 计算缩放比例
    int scale_x = orig_width / new_width;
    int scale_y = orig_height / new_height;

    // 要求scale_x和scale_y为整数且>0
    if (scale_x <= 0 || scale_y <= 0 ||
        (orig_width % new_width != 0) ||
        (orig_height % new_height != 0)) {
        // 不满足整倍缩放要求
        return -1;
    }

    // 从右下往左上遍历，防止数据被覆盖后还未读取
    for (int y = new_height - 1; y >= 0; y--) {
        for (int x = new_width - 1; x >= 0; x--) {
            int src_x = x * scale_x;
            int src_y = y * scale_y;
            PIXEL565 pixel = image[src_y * orig_width + src_x];
            image[y * new_width + x] = pixel;
        }
    }

    return 0;
}

// 限制矩形坐标满足 0 < x1 < x2 <160，0 < y1 < y2 <120
void clamp_face_rect(FaceRect *rect) {
    // 辅助宏：将整数值限制在 [min, max] 范围内
    #define CLAMP_INT(value, min_val, max_val) \
        do { \
            if ((value) < (min_val)) (value) = (min_val); \
            else if ((value) > (max_val)) (value) = (max_val); \
        } while (0)

    // ----------- 处理 x 坐标 -----------
    // 1. 先限制到默认范围 [0, DISP_IMAGE_WIDTH - 1]
    CLAMP_INT(rect->x1, 0, DISP_IMAGE_WIDTH - 1);
    CLAMP_INT(rect->x2, 0, DISP_IMAGE_WIDTH - 1);

    // 2. 确保 x1 > 0
    if (rect->x1 == 0) rect->x1 = 1;

    // 3. 确保 x2 > x1，否则调整
    if (rect->x2 <= rect->x1) {
        rect->x2 = rect->x1 + 1;
        // 如果超出最大值，回退到右边界并调整 x1
        if (rect->x2 > DISP_IMAGE_WIDTH - 1) {
            rect->x2 = DISP_IMAGE_WIDTH - 1;
            rect->x1 = rect->x2 - 1;
            if (rect->x1 < 1) rect->x1 = 1; // 二次保护
        }
    }

    // ----------- 处理 y 坐标 -----------
    // 1. 先限制到默认范围 [0, DISP_IMAGE_HEIGHT - 1]
    CLAMP_INT(rect->y1, 0, DISP_IMAGE_HEIGHT - 1);
    CLAMP_INT(rect->y2, 0, DISP_IMAGE_HEIGHT - 1);

    // 2. 确保 y1 > 0
    if (rect->y1 == 0) rect->y1 = 1;

    // 3. 确保 y2 > y1，否则调整
    if (rect->y2 <= rect->y1) {
        rect->y2 = rect->y1 + 1;
        // 如果超出最大值，回退到下边界并调整 y1
        if (rect->y2 > DISP_IMAGE_HEIGHT - 1) {
            rect->y2 = DISP_IMAGE_HEIGHT - 1;
            rect->y1 = rect->y2 - 1;
            if (rect->y1 < 1) rect->y1 = 1; // 二次保护
        }
    }
    #undef CLAMP_INT
}

/**
 * @brief 逆时针旋转90度（适用于RGB565格式）
 * @param src 原图像数据指针（128 * 160）
 * @param dst 目标图像数据指针（160 * 128）
 */
void rotate_ccw90(uint16_t *src, uint16_t *dst) {
    const int srcW = 128, srcH = 160;
    for (int y = 0; y < srcH; y++) {
        for (int x = 0; x < srcW; x++) {
            // 计算目标位置：旋转后宽高互换，坐标变换公式为 (y, srcW-1-x)
            int dstX = y;
            int dstY = srcW - 1 - x;
            // 目标数组索引计算
            int dstIdx = dstY * 160 + dstX; // 新宽度为160
            // 原数组索引计算
            int srcIdx = y * srcW + x;
            // 复制RGB565像素（2字节）
            dst[dstIdx] = src[srcIdx];
        }
    }
}

/**
 * @brief 通用逆时针旋转90度（RGB565），支持任意 WxH -> HxW
 * 优化版：按行处理减少索引计算，提升缓存命中率
 */
static void rotate_ccw90_generic(const uint16_t *src, int srcW, int srcH, uint16_t *dst) {
    // 逆时针旋转90度：dst[dstY][dstX] = src[y][x]
    // 其中 dstX = y, dstY = srcW - 1 - x
    // 目标尺寸：dstW = srcH, dstH = srcW
    
    const int dstW = srcH;  // 旋转后宽度 = 原高度
    
    // 按源图像行遍历（顺序读取，利用缓存）
    for (int y = 0; y < srcH; ++y) {
        const uint16_t* srcRow = src + y * srcW;
        int dstX = y;  // 固定的目标X坐标
        
        // 目标Y从 srcW-1 递减到 0
        for (int x = 0; x < srcW; ++x) {
            int dstY = srcW - 1 - x;
            dst[dstY * dstW + dstX] = srcRow[x];
        }
    }
}

/**
 * @brief 顺时针旋转90度还原（适用于RGB565格式）
 * @param src 旋转后的图像数据指针（160 * 128）
 * @param dst 还原后的图像数据指针（128 * 160）
 */
void restore_cw90(uint16_t *src, uint16_t *dst) {
    const int srcW = 160, srcH = 128;
    for (int y = 0; y < srcH; y++) {
        for (int x = 0; x < srcW; x++) {
            // 计算目标位置：旋转后宽高互换，坐标变换公式为 (srcH-1-y, x)
            int dstX = srcH - 1 - y;
            int dstY = x;
            // 目标数组索引计算
            int dstIdx = dstY * 128 + dstX; // 原宽度恢复为128
            // 原数组索引计算
            int srcIdx = y * srcW + x;
            // 复制RGB565像素（2字节）
            dst[dstIdx] = src[srcIdx];
        }
    }
}

/**
 * @brief 将旋转后图像（160x128）的人脸坐标还原到原图（128x160）
 * @param rotated_x   旋转后人脸框左上角x坐标
 * @param rotated_y   旋转后人脸框左上角y坐标
 * @param rotated_w   旋转后人脸框宽度
 * @param rotated_h   旋转后人脸框高度
 * @param original_box 还原后的原图坐标（输出参数）
 */
void restore_coordinates(int* original_x1, int* original_y1, int* original_x2, int* original_y2) {
    // 坐标逆变换（顺时针旋转90度）
	int rotated_x1 = *original_x1;
	int rotated_y1 = *original_y1;
	int rotated_x2 = *original_x2;
	int rotated_y2 = *original_y2;

    *original_x1 = 128 - 1 - rotated_y2;
    *original_y1 = rotated_x1; // 旋转后图像高度=128

    // 宽高交换
    *original_x2 = 128 - 1 - rotated_y1;
    *original_y2 = rotated_x2;
}

void restore_pixel(int* original_x, int* original_y) {
    // 坐标逆变换（顺时针旋转90度）
	int rotated_x = *original_x;
	int rotated_y = *original_y;

	// 宽高交换
    *original_x = 128 - 1 - rotated_y;
    *original_y = rotated_x; // 旋转后图像高度=128
}

// ==== 565 -> 888 (160x120) 最终转换，供推理直接使用 ====
// 优化版: 减少函数调用开销，展开位运算
static void convert_565_to_bgr888_160x120(const uint16_t* src160x120, uint8_t* dst888 /*bgr320_buffer1*/) {
    const uint16_t *src = src160x120;
    uint8_t *dst = dst888;
    // 160x120 = 19200 pixels, 每次处理4像素减少循环开销
    int total = 160 * 120;
    int i = 0;
    
    // 主循环：每次处理4个像素
    for (; i + 4 <= total; i += 4) {
        uint16_t p0 = src[i];
        uint16_t p1 = src[i+1];
        uint16_t p2 = src[i+2];
        uint16_t p3 = src[i+3];
        
        // BGR565: B[15:11] G[10:5] R[4:0]
        // 扩展到8位：高5位左移3位，低位填充高位的高2-3位
        uint8_t *d = dst + i * 3;
        
        // Pixel 0
        uint8_t r5_0 = (p0 & 0x001F);
        uint8_t g6_0 = (p0 >> 5) & 0x003F;
        uint8_t b5_0 = (p0 >> 11);
        d[0] = (b5_0 << 3) | (b5_0 >> 2);  // B
        d[1] = (g6_0 << 2) | (g6_0 >> 4);  // G
        d[2] = (r5_0 << 3) | (r5_0 >> 2);  // R
        
        // Pixel 1
        uint8_t r5_1 = (p1 & 0x001F);
        uint8_t g6_1 = (p1 >> 5) & 0x003F;
        uint8_t b5_1 = (p1 >> 11);
        d[3] = (b5_1 << 3) | (b5_1 >> 2);
        d[4] = (g6_1 << 2) | (g6_1 >> 4);
        d[5] = (r5_1 << 3) | (r5_1 >> 2);
        
        // Pixel 2
        uint8_t r5_2 = (p2 & 0x001F);
        uint8_t g6_2 = (p2 >> 5) & 0x003F;
        uint8_t b5_2 = (p2 >> 11);
        d[6] = (b5_2 << 3) | (b5_2 >> 2);
        d[7] = (g6_2 << 2) | (g6_2 >> 4);
        d[8] = (r5_2 << 3) | (r5_2 >> 2);
        
        // Pixel 3
        uint8_t r5_3 = (p3 & 0x001F);
        uint8_t g6_3 = (p3 >> 5) & 0x003F;
        uint8_t b5_3 = (p3 >> 11);
        d[9]  = (b5_3 << 3) | (b5_3 >> 2);
        d[10] = (g6_3 << 2) | (g6_3 >> 4);
        d[11] = (r5_3 << 3) | (r5_3 >> 2);
    }
    
    // 处理剩余像素
    for (; i < total; ++i) {
        uint16_t p = src[i];
        uint8_t r5 = (p & 0x001F);
        uint8_t g6 = (p >> 5) & 0x003F;
        uint8_t b5 = (p >> 11);
        uint8_t *d = dst + i * 3;
        d[0] = (b5 << 3) | (b5 >> 2);
        d[1] = (g6 << 2) | (g6 >> 4);
        d[2] = (r5 << 3) | (r5 >> 2);
    }
}


// 任意RGB565缩放（最近邻，定点步进）+ ROI 支持，srcStride 为源整图行步长
// 优化版：减少内层循环计算，预计算行指针
static void resize_bgr565_nn_roi(const uint16_t *src, int srcStride,
                                 int roiX, int roiY, int roiW, int roiH,
                                 uint16_t *dst, int dstW, int dstH) {
    // 使用16.16定点数，避免浮点
    uint32_t stepX = ((uint32_t)roiW << 16) / (uint32_t)dstW;
    uint32_t stepY = ((uint32_t)roiH << 16) / (uint32_t)dstH;
    
    // 预偏移源指针到ROI起点
    const uint16_t* srcBase = src + roiY * srcStride + roiX;
    
    uint32_t sy_fp = 0;
    for (int y = 0; y < dstH; ++y) {
        int sy = (int)(sy_fp >> 16);
        // 边界保护
        if (sy >= roiH) sy = roiH - 1;
        
        const uint16_t* srcRow = srcBase + sy * srcStride;
        uint16_t* dstRow = dst + y * dstW;
        
        uint32_t sx_fp = 0;
        // 展开内层循环：每次处理4个像素
        int x = 0;
        for (; x + 4 <= dstW; x += 4) {
            int sx0 = (int)(sx_fp >> 16); sx_fp += stepX;
            int sx1 = (int)(sx_fp >> 16); sx_fp += stepX;
            int sx2 = (int)(sx_fp >> 16); sx_fp += stepX;
            int sx3 = (int)(sx_fp >> 16); sx_fp += stepX;
            // 边界保护（理论上不需要，但防御性编程）
            if (sx0 >= roiW) sx0 = roiW - 1;
            if (sx1 >= roiW) sx1 = roiW - 1;
            if (sx2 >= roiW) sx2 = roiW - 1;
            if (sx3 >= roiW) sx3 = roiW - 1;
            dstRow[x]   = srcRow[sx0];
            dstRow[x+1] = srcRow[sx1];
            dstRow[x+2] = srcRow[sx2];
            dstRow[x+3] = srcRow[sx3];
        }
        // 处理剩余像素
        for (; x < dstW; ++x) {
            int sx = (int)(sx_fp >> 16);
            if (sx >= roiW) sx = roiW - 1;
            dstRow[x] = srcRow[sx];
            sx_fp += stepX;
        }
        sy_fp += stepY;
    }
}

// 整倍缩小（简化版）：直接使用最近邻采样，放弃均值聚合以提升性能
// 对于人脸检测任务，最近邻采样的质量损失可忽略不计
static void binning_downscale_bgr565_roi(const uint16_t *src, int srcStride,
                                         int roiX, int roiY, int roiW, int roiH,
                                         uint16_t *dst, int dstW, int dstH) {
    // 直接使用优化后的最近邻缩放
    resize_bgr565_nn_roi(src, srcStride, roiX, roiY, roiW, roiH, dst, dstW, dstH);
}

// 统一前处理：任意 >=160x120(横) 或 >=120x160(竖) 的RGB565输入 -> 160x120 RGB888 输出
// ★★★ 优化版：一次遍历完成 缩放+旋转+颜色转换，减少内存读写 ★★★
static void preprocess_to_160x120_bgr(const uint16_t* src, int srcW, int srcH, uint8_t* outRgb888, Transform* tfm)
{
    int portrait = (srcW < srcH);
    tfm->srcW = srcW; tfm->srcH = srcH;
    tfm->preW = portrait ? 120 : 160;
    tfm->preH = portrait ? 160 : 120;
    tfm->rotated = portrait ? 1 : 0;

    // 计算尽可能大的整数倍下采样比例，并做最小化对称裁剪
    int kx = srcW / tfm->preW;
    int ky = srcH / tfm->preH;
    if (kx < 1) kx = 1; if (ky < 1) ky = 1;
    int k = (kx < ky) ? kx : ky;
    int roiW = tfm->preW * k;
    int roiH = tfm->preH * k;
    int roiX = (srcW - roiW) / 2;
    int roiY = (srcH - roiH) / 2;
    if (roiX < 0) roiX = 0; if (roiY < 0) roiY = 0;

    tfm->cropOx = roiX; tfm->cropOy = roiY;
    tfm->cropW = roiW; tfm->cropH = roiH;

    // 预计算缩放步进（16.16 定点）
    uint32_t stepX = ((uint32_t)roiW << 16) / (uint32_t)tfm->preW;
    uint32_t stepY = ((uint32_t)roiH << 16) / (uint32_t)tfm->preH;
    
    // 预偏移源指针到ROI起点
    const uint16_t* srcBase = src + roiY * srcW + roiX;
    
    if (portrait) {
        // ★ 竖屏模式：一次遍历完成 缩放 + 逆时针旋转90° + RGB565→BGR888
        // 输入: srcW x srcH (如 240x320) → 缩放到 120x160 → 旋转到 160x120 (输出)
        // 旋转公式: dst[dstY][dstX] = scaled[y][x], 其中 dstX=y, dstY=preW-1-x
        // 即: 输出坐标 (dstX, dstY) 对应 scaled 坐标 (preW-1-dstY, dstX)
        
        const int dstW = 160;  // 输出宽度
        const int dstH = 120;  // 输出高度
        const int preW = 120;  // 缩放后（旋转前）宽度
        const int preH = 160;  // 缩放后（旋转前）高度
        
        // 逐行处理输出图像
        for (int dstY = 0; dstY < dstH; ++dstY) {
            // 旋转映射: 输出行 dstY 对应缩放后的列 x = preW - 1 - dstY
            int scaledX = preW - 1 - dstY;
            // 映射回原图坐标
            int srcX_fixed = scaledX * stepX;
            int srcX = srcX_fixed >> 16;
            if (srcX >= roiW) srcX = roiW - 1;
            
            uint8_t* dstRow = outRgb888 + dstY * dstW * 3;
            uint32_t sy_fp = 0;
            
            for (int dstX = 0; dstX < dstW; ++dstX) {
                // 旋转映射: 输出列 dstX 对应缩放后的行 y = dstX
                int scaledY = dstX;
                int srcY = (scaledY * stepY) >> 16;
                if (srcY >= roiH) srcY = roiH - 1;
                
                // 读取源像素
                uint16_t p = srcBase[srcY * srcW + srcX];
                
                // RGB565 → BGR888 转换
                uint8_t r5 = (p & 0x001F);
                uint8_t g6 = (p >> 5) & 0x003F;
                uint8_t b5 = (p >> 11);
                
                uint8_t* d = dstRow + dstX * 3;
                d[0] = (b5 << 3) | (b5 >> 2);  // B
                d[1] = (g6 << 2) | (g6 >> 4);  // G
                d[2] = (r5 << 3) | (r5 >> 2);  // R
            }
        }
    } else {
        // ★ 横屏模式：一次遍历完成 缩放 + RGB565→BGR888（无旋转）
        const int dstW = 160;
        const int dstH = 120;
        
        uint32_t sy_fp = 0;
        for (int y = 0; y < dstH; ++y) {
            int srcY = (int)(sy_fp >> 16);
            if (srcY >= roiH) srcY = roiH - 1;
            
            const uint16_t* srcRow = srcBase + srcY * srcW;
            uint8_t* dstRow = outRgb888 + y * dstW * 3;
            
            uint32_t sx_fp = 0;
            // 每次处理4个像素
            int x = 0;
            for (; x + 4 <= dstW; x += 4) {
                int sx0 = (int)(sx_fp >> 16); sx_fp += stepX;
                int sx1 = (int)(sx_fp >> 16); sx_fp += stepX;
                int sx2 = (int)(sx_fp >> 16); sx_fp += stepX;
                int sx3 = (int)(sx_fp >> 16); sx_fp += stepX;
                
                uint16_t p0 = srcRow[sx0 < roiW ? sx0 : roiW-1];
                uint16_t p1 = srcRow[sx1 < roiW ? sx1 : roiW-1];
                uint16_t p2 = srcRow[sx2 < roiW ? sx2 : roiW-1];
                uint16_t p3 = srcRow[sx3 < roiW ? sx3 : roiW-1];
                
                uint8_t* d = dstRow + x * 3;
                
                // Pixel 0
                d[0] = ((p0 >> 11) << 3) | ((p0 >> 11) >> 2);
                d[1] = (((p0 >> 5) & 0x3F) << 2) | (((p0 >> 5) & 0x3F) >> 4);
                d[2] = ((p0 & 0x1F) << 3) | ((p0 & 0x1F) >> 2);
                
                // Pixel 1
                d[3] = ((p1 >> 11) << 3) | ((p1 >> 11) >> 2);
                d[4] = (((p1 >> 5) & 0x3F) << 2) | (((p1 >> 5) & 0x3F) >> 4);
                d[5] = ((p1 & 0x1F) << 3) | ((p1 & 0x1F) >> 2);
                
                // Pixel 2
                d[6] = ((p2 >> 11) << 3) | ((p2 >> 11) >> 2);
                d[7] = (((p2 >> 5) & 0x3F) << 2) | (((p2 >> 5) & 0x3F) >> 4);
                d[8] = ((p2 & 0x1F) << 3) | ((p2 & 0x1F) >> 2);
                
                // Pixel 3
                d[9]  = ((p3 >> 11) << 3) | ((p3 >> 11) >> 2);
                d[10] = (((p3 >> 5) & 0x3F) << 2) | (((p3 >> 5) & 0x3F) >> 4);
                d[11] = ((p3 & 0x1F) << 3) | ((p3 & 0x1F) >> 2);
            }
            // 处理剩余像素
            for (; x < dstW; ++x) {
                int sx = (int)(sx_fp >> 16);
                if (sx >= roiW) sx = roiW - 1;
                sx_fp += stepX;
                
                uint16_t p = srcRow[sx];
                uint8_t* d = dstRow + x * 3;
                d[0] = ((p >> 11) << 3) | ((p >> 11) >> 2);
                d[1] = (((p >> 5) & 0x3F) << 2) | (((p >> 5) & 0x3F) >> 4);
                d[2] = ((p & 0x1F) << 3) | ((p & 0x1F) >> 2);
            }
            sy_fp += stepY;
        }
    }
}

// ============ 通用坐标逆变换：从CNN(160x120)坐标还原到原图(srcW x srcH) ============
static inline int clampi(int v, int lo, int hi) {
    if (v < lo) return lo; if (v > hi) return hi; return v;
}

static inline float clampf(float v, float lo, float hi) {
    if (v < lo) return lo; if (v > hi) return hi; return v;
}

// 将 CNN(160x120) 坐标点映射回原图坐标（浮点版）
static inline void map_point_cnn_to_original_float(const Transform* tfm,
                                                   float xc, float yc,
                                                   float* xo, float* yo) {
    // 1) CNN -> 预处理域（可能逆旋转）
    float xq, yq;
    if (tfm->rotated) {
        // 逆时针旋转过，需做顺时针逆变换
        xq = (float)(tfm->preW - 1) - yc;
        yq = xc;
    } else {
        xq = xc; yq = yc;
    }
    // 2) 预处理域 -> 裁剪域（缩放）
    float sx = (float)tfm->cropW / (float)tfm->preW;
    float sy = (float)tfm->cropH / (float)tfm->preH;
    float xcrop = xq * sx;
    float ycrop = yq * sy;
    // 3) 裁剪域 -> 原图（偏移）
    *xo = (float)tfm->cropOx + xcrop;
    *yo = (float)tfm->cropOy + ycrop;
}

// 将CNN坐标点(xc,yc)映射回原图坐标(xo,yo)
static void restore_faces_with_transform(FaceRect* faces, int count, const Transform* tfm) {
    const int srcW = tfm->srcW, srcH = tfm->srcH;
    // 其余变换参数直接通过 tfm 在映射函数中使用，无需在此展开
    for (int i = 0; i < count; ++i) {
        FaceRect* r = &faces[i];
        // 1) 映射四角为浮点，再用 floor/ceil 构出包围盒（避免缩水）
        float fx[4], fy[4];
        int xcnn[4] = { r->x1, r->x2, r->x1, r->x2 };
        int ycnn[4] = { r->y1, r->y1, r->y2, r->y2 };
        for (int k = 0; k < 4; ++k) {
            float xo, yo;
            map_point_cnn_to_original_float(tfm, (float)xcnn[k], (float)ycnn[k], &xo, &yo);
            fx[k] = clampf(xo, 0.0f, (float)(srcW - 1));
            fy[k] = clampf(yo, 0.0f, (float)(srcH - 1));
        }
        float xminf = fx[0], xmaxf = fx[0];
        float yminf = fy[0], ymaxf = fy[0];
        for (int k = 1; k < 4; ++k) {
            if (fx[k] < xminf) xminf = fx[k]; if (fx[k] > xmaxf) xmaxf = fx[k];
            if (fy[k] < yminf) yminf = fy[k]; if (fy[k] > ymaxf) ymaxf = fy[k];
        }
        int xmin = clampi((int)floorf(xminf), 0, srcW - 1);
        int xmax = clampi((int)ceilf(xmaxf), 0, srcW - 1);
        int ymin = clampi((int)floorf(yminf), 0, srcH - 1);
        int ymax = clampi((int)ceilf(ymaxf), 0, srcH - 1);
        if (xmax <= xmin) xmax = clampi(xmin + 1, 1, srcW - 1);
        if (ymax <= ymin) ymax = clampi(ymin + 1, 1, srcH - 1);
        r->x1 = xmin; r->y1 = ymin; r->x2 = xmax; r->y2 = ymax;

        // 2) 同步还原landmarks（5点），按浮点坐标回贴
        for (int p = 0; p < 5; ++p) {
            float xc = r->lm[2*p];
            float yc = r->lm[2*p + 1];
            float xo, yo;
            map_point_cnn_to_original_float(tfm, xc, yc, &xo, &yo);
            r->lm[2*p]     = clampf(xo, 0.0f, (float)(srcW - 1));
            r->lm[2*p + 1] = clampf(yo, 0.0f, (float)(srcH - 1));
        }
    }
}

// ==================== 业务流程拆分：模块化辅助函数 ====================

// 处理一帧：前处理->推理->坐标还原->通知（多目标检测协议 v2.1）
// frame_buffer: 待处理的帧缓冲区
// frame_idx: 0=wframe0, 1=wframe1（用于日志区分）
static void process_frame(PipelineContext* ctx, uint16_t* frame_buffer, int frame_idx) {
    // ========== 性能测量 ==========
    uint32_t t0, t1, t2, t3, t4;
    t0 = get_cycles_start();

    // 通用化：一次调用完成裁剪/旋转/缩放/转换，并记录变换参数
    Transform tfm;
    preprocess_to_160x120_bgr(frame_buffer,
                              ctx->snapshot_width,
                              ctx->snapshot_height,
                              bgr320_buffer1,
                              &tfm);
    t1 = get_cycles();

    int face_count = face_detect_rgb(bgr320_buffer1);
    t2 = get_cycles();

    // 使用多目标检测协议 v2.1
    if (face_count > 0) {
        // 使用通用逆变换还原所有检测框到原图坐标
        restore_faces_with_transform(faces_result, face_count, &tfm);

        // 填充DetectionResult结构体
        uint32_t timestamp = times_count * 100; // 简单时间戳
        DetectionResult_t *result = detection_fill_result(faces_result, face_count, timestamp);

        t3 = get_cycles();

        // 发送多目标结果并切换缓冲区
        detection_send_and_swap(result);
        t4 = get_cycles_end();

        // 打印性能数据（每帧打印用于诊断）
        // WATCHDOG 计数器每16个DSP周期加1，乘以16转换为实际周期
        uint32_t cyc_preproc = (t1 - t0) * 16;
        uint32_t cyc_detect  = (t2 - t1) * 16;
        uint32_t cyc_total   = (t4 - t0) * 16;
        // 转换为毫秒 (@ 400MHz)
        uint32_t ms_pre = cyc_preproc / 400000;
        uint32_t ms_det = cyc_detect / 400000;
        uint32_t ms_total = cyc_total / 400000;
        // 计算后处理总时和帧率
        uint32_t ms_post = g_perf_softmax_ms + g_perf_decode_ms + g_perf_nms_ms;
        uint32_t fps_theory = (ms_total > 0) ? (1000 / ms_total) : 999;
        uint32_t fps_actual = (fps_theory * 95) / 100;
//        rt_kprintf("[DSP] f%d Pre=%lu Inf=%lu Post=%lu(sm=%lu,dec=%lu,nms=%lu) Tot=%lu | FPS:%lu/%lu n=%d\n",
//                   frame_idx, ms_pre, g_perf_infer_ms, ms_post,
//                   g_perf_softmax_ms, g_perf_decode_ms, g_perf_nms_ms,
//                   ms_total, fps_theory, fps_actual, face_count);
    } else {
        t3 = get_cycles_end();
        // 无检测结果，发送空帧消息
        mailbox_send_no_detection();
        
        // 打印性能数据（每帧打印）
        uint32_t cyc_preproc = (t1 - t0) * 16;
        uint32_t cyc_detect  = (t2 - t1) * 16;
        uint32_t cyc_total   = (t3 - t0) * 16;
        uint32_t ms_pre = cyc_preproc / 400000;
        uint32_t ms_det = cyc_detect / 400000;
        uint32_t ms_total = cyc_total / 400000;
        // 计算后处理总时和帧率
        uint32_t ms_post = g_perf_softmax_ms + g_perf_decode_ms + g_perf_nms_ms;
        uint32_t fps_theory = (ms_total > 0) ? (1000 / ms_total) : 999;
        uint32_t fps_actual = (fps_theory * 95) / 100;
//        rt_kprintf("[DSP] f%d Pre=%lu Inf=%lu Post=%lu(sm=%lu,dec=%lu,nms=%lu) Tot=%lu | FPS:%lu/%lu\n",
//                   frame_idx, ms_pre, g_perf_infer_ms, ms_post,
//                   g_perf_softmax_ms, g_perf_decode_ms, g_perf_nms_ms,
//                   ms_total, fps_theory, fps_actual);
    }
}

// 双缓冲帧处理：wframe0 和 wframe1 都处理
static uint32_t g_dsp_frame_id = 0;  // DSP 帧计数器

static void process_frames_if_flagged(PipelineContext* ctx) {
    int processed_frame = 0;

    if (g_ctrl_state != DSP_CTRL_RUNNING || !g_video_resources_bound) {
        return;
    }

    // 处理 wframe0
    if (wframe0_flag) {
        wframe0_flag = 0;
        g_dsp_frame_id++;
        process_frame(ctx, ctx->wframe0_buffer, 0);
        REG32(DSP_MM_BASE + 0x38) = 1;  // 通知 wframe0 处理完成
        processed_frame = 1;
    }

    // 处理 wframe1
    if (wframe1_flag) {
        wframe1_flag = 0;
        g_dsp_frame_id++;
        process_frame(ctx, ctx->wframe1_buffer, 1);
        REG32(DSP_MM_BASE + 0x3C) = 1;  // 通知 wframe1 处理完成
        processed_frame = 1;
    }

    if (processed_frame && ((g_dsp_frame_id & 0x1Fu) == 0u)) {
        dsp_send_status((uint8_t)(g_dsp_frame_id & 0xFFu));
    }
}

int main(void)
{
    /* Test start */
    uint32_t dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;
    dd |= 0x1 << 16;
    _out(_cpm, dd, 0x924);
    dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;

    // 运行期上下文
    PipelineContext ctx = {0};
    dsp_mailbox_reset_fifos();
    pipeline_context_reset(&ctx);

    while (1)
    {
        if (times_cycles % 10000000 == 0) {
            times_count++;
        }

        dsp_poll_control_plane(&ctx);

        // 帧处理（双缓冲 pingpong）
        process_frames_if_flagged(&ctx);

        dsp_log_idle_state();

        times_cycles++;
        g_idle_cycles++;
    }
    return 0;
}


