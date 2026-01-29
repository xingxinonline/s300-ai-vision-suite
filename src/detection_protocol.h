/**
 * @file detection_protocol.h
 * @brief DSP与M4之间的多目标检测协议定义
 *
 * 本文件定义了DSP侧检测算法与M4侧face_tracker模块的通信协议。
 * 协议版本 v2.1 支持多目标检测，DSP 负责选择目标。
 *
 * @version 2.1
 * @date 2026-01-29
 */

#ifndef __DETECTION_PROTOCOL_H__
#define __DETECTION_PROTOCOL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================
 * 协议常量定义
 *============================================================================*/

/** 最大检测目标数量 */
#define MAX_DETECTION_COUNT         10

/** 检测结果魔数（用于数据校验）"DETF" */
#define DETECTION_RESULT_MAGIC      0x44455446u

/** 协议版本号 (v2.1 = 0x0201) */
#define DETECTION_PROTOCOL_VERSION  0x0201u

/**
 * @brief DSP内存地址映射说明
 *
 * DSP PTCM 内存地址映射：
 *   - DSP内核访问：0x00000000 ~ 0x0003FFFF (256KB)
 *   - M4/外部访问：0x44800000 ~ 0x4483FFFF (需加偏移)
 *
 * Mailbox 消息中的 payload 是 DSP 本地地址（28位），
 * M4 收到后需要加上 DSP_PTCM_M4_BASE_OFFSET 才能访问：
 *
 *   uint32_t msg = mailbox_read();
 *   uint32_t dsp_addr = GET_MSG_PAYLOAD(msg);
 *   DetectionResult_t *result = (DetectionResult_t *)(dsp_addr + DSP_PTCM_M4_BASE_OFFSET);
 */

/** M4访问DSP PTCM的基地址偏移 */
#define DSP_PTCM_M4_BASE_OFFSET     0x44800000u

/*============================================================================
 * 检测类型枚举
 *============================================================================*/

typedef enum {
    DETECTION_TYPE_UNKNOWN  = 0,  /**< 未知类型 */
    DETECTION_TYPE_FACE     = 1,  /**< 人脸检测 */
    DETECTION_TYPE_PERSON   = 2,  /**< 行人检测 */
    DETECTION_TYPE_GESTURE  = 3,  /**< 手势检测 */
    DETECTION_TYPE_OBJECT   = 4,  /**< 通用物体检测 */
} DetectionType_e;

/*============================================================================
 * 核心数据结构
 *============================================================================*/

/**
 * @brief 单个检测框结构体
 *
 * 包含单个检测目标的边界框、置信度、关键点等信息。
 * 结构体大小为 64 字节，使用 packed 属性保证内存对齐一致性。
 */
typedef struct __attribute__((packed)) {
    float    score;           /**< 置信度 [0.0, 1.0] */
    int32_t  x1, y1;          /**< 左上角坐标 */
    int32_t  x2, y2;          /**< 右下角坐标 */
    float    lm[10];          /**< 5个关键点坐标 (x0,y0,x1,y1,...,x4,y4) */
    uint8_t  type;            /**< 检测类型 (DetectionType_e) */
    uint8_t  track_id;        /**< 跟踪ID（由跟踪器分配） */
    uint8_t  reserved[2];     /**< 保留字段 */
} DetectionBox_t;             /* 64 bytes total */

/**
 * @brief 检测结果结构体
 *
 * 包含一帧图像的所有检测结果。
 * 结构体大小为 664 字节（24 字节头 + 10 * 64 字节检测框）。
 */
typedef struct __attribute__((packed)) {
    uint32_t       magic;        /**< 魔数 = DETECTION_RESULT_MAGIC */
    uint32_t       version;      /**< 协议版本 = DETECTION_PROTOCOL_VERSION */
    uint32_t       frame_id;     /**< 帧序号（递增） */
    uint32_t       timestamp;    /**< 时间戳（毫秒，可选） */
    uint32_t       count;        /**< 目标数量 [0, MAX_DETECTION_COUNT] */
    int32_t        selected_idx; /**< DSP选中的目标索引 [0,count-1]，-1表示无选中 */
    DetectionBox_t boxes[MAX_DETECTION_COUNT]; /**< 检测框数组 */
} DetectionResult_t;             /* 664 bytes total */

/*============================================================================
 * Mailbox 消息类型定义
 *============================================================================*/

/**
 * @brief Mailbox消息格式
 *
 * 32-bit 消息格式：
 *   Bit [31:28]: 消息类型
 *   Bit [27:0]:  Payload（DetectionResult 的偏移地址）
 */

/** 单目标消息类型（旧协议兼容） */
#define MAILBOX_MSG_TYPE_SINGLE     0x00000000u

/** 多目标消息类型（新协议） */
#define MAILBOX_MSG_TYPE_MULTI      0x10000000u

/** 本帧无检测结果 */
#define MAILBOX_MSG_TYPE_NO_DETECT  0xF0000000u

/** 消息类型掩码 */
#define MAILBOX_MSG_TYPE_MASK       0xF0000000u

/** Payload掩码 */
#define MAILBOX_MSG_PAYLOAD_MASK    0x0FFFFFFFu

/*============================================================================
 * 工具宏
 *============================================================================*/

/**
 * @brief 构造多目标检测消息
 * @param offset DetectionResult相对于DSP_DETECTION_BASE_ADDR的偏移
 */
#define MAKE_MULTI_DETECT_MSG(offset) \
    (MAILBOX_MSG_TYPE_MULTI | ((offset) & MAILBOX_MSG_PAYLOAD_MASK))

/**
 * @brief 构造单目标检测消息（兼容旧协议）
 * @param offset FaceRect相对于基地址的偏移
 */
#define MAKE_SINGLE_DETECT_MSG(offset) \
    (MAILBOX_MSG_TYPE_SINGLE | ((offset) & MAILBOX_MSG_PAYLOAD_MASK))

/**
 * @brief 从消息中提取消息类型
 */
#define GET_MSG_TYPE(msg)    ((msg) & MAILBOX_MSG_TYPE_MASK)

/**
 * @brief 从消息中提取Payload
 */
#define GET_MSG_PAYLOAD(msg) ((msg) & MAILBOX_MSG_PAYLOAD_MASK)

/*============================================================================
 * 编译时断言 - 确保结构体大小正确
 *============================================================================*/

/* 使用编译时数组大小检查（兼容非C11编译器） */
#ifndef COMPILE_TIME_ASSERT
#define COMPILE_TIME_ASSERT(cond, msg) \
    typedef char static_assertion_##msg[(cond) ? 1 : -1]
#endif

/* 结构体大小验证（仅在编译时检查） */
COMPILE_TIME_ASSERT(sizeof(DetectionBox_t) == 64, DetectionBox_size_mismatch);
COMPILE_TIME_ASSERT(sizeof(DetectionResult_t) == 664, DetectionResult_size_mismatch);

#ifdef __cplusplus
}
#endif

#endif /* __DETECTION_PROTOCOL_H__ */
