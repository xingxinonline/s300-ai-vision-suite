/**
 * @file dsp_tracker_v2.c
 * @brief DSP 轻量级多目标 ID 关联器
 *
 * 简化版设计：
 * - 只做 ID 关联 + 速度估计
 * - 不做目标选择、状态机、遮挡处理
 * - 所有决策交给 M4
 *
 * @version 2.0
 * @date 2026-02-04
 */

#include <string.h>
#include "dsp_tracker_v2.h"
#include "custom_printf.h"

/*============================================================================
 * Internal Types
 *============================================================================*/

/**
 * @brief 简单速度估计器 (每个 track_id 一个)
 */
typedef struct {
    uint8_t  track_id;      /**< 对应的 track_id */
    uint8_t  valid;         /**< 是否有效 */
    int32_t  last_cx;       /**< 上一帧中心 X */
    int32_t  last_cy;       /**< 上一帧中心 Y */
    int8_t   vx;            /**< 速度 X (像素/帧) */
    int8_t   vy;            /**< 速度 Y (像素/帧) */
    uint8_t  update_count;  /**< 更新次数 (用于置信度) */
} VelocityEstimator_t;

/*============================================================================
 * Tracker Context
 *============================================================================*/

#define MAX_VELOCITY_SLOTS  5
#define MAX_TRACK_SLOTS     5       /**< 最大同时跟踪目标数 */
#define TRACK_MAX_MISS      30      /**< 允许漏检帧数 (30FPS下约1秒) */
#define VELOCITY_MAX_MISS   10      /**< 速度估计器保持帧数 */

/**
 * @brief Track 槽位 (带漏检容忍)
 */
typedef struct {
    DetectionBox_t box;         /**< 最后检测到的位置 */
    uint8_t        track_id;    /**< 分配的 ID */
    uint8_t        miss_count;  /**< 连续漏检帧数 */
    uint8_t        active;      /**< 是否活跃 */
} TrackSlot_t;

typedef struct {
    /* ID 关联 (带历史保留) */
    TrackSlot_t    slots[MAX_TRACK_SLOTS];
    uint8_t        next_track_id;
    
    /* 速度估计 */
    VelocityEstimator_t velocity[MAX_VELOCITY_SLOTS];
    
    /* 统计 */
    uint32_t       frame_count;
} TrackerCtx_t;

static TrackerCtx_t g_ctx;

/*============================================================================
 * Helper Functions
 *============================================================================*/

static inline int32_t max_i32(int32_t a, int32_t b) { return a > b ? a : b; }
static inline int32_t min_i32(int32_t a, int32_t b) { return a < b ? a : b; }

/**
 * @brief Integer square root
 */
static int32_t isqrt(int32_t n) {
    if (n <= 0) return 0;
    int32_t x = n, y = (x + 1) >> 1;
    while (y < x) { x = y; y = (x + n / x) >> 1; }
    return x;
}

/**
 * @brief Calculate IoU percentage (0-100)
 */
static int32_t calc_iou_pct(const DetectionBox_t *a, const DetectionBox_t *b)
{
    int32_t x1 = max_i32(a->x1, b->x1);
    int32_t y1 = max_i32(a->y1, b->y1);
    int32_t x2 = min_i32(a->x2, b->x2);
    int32_t y2 = min_i32(a->y2, b->y2);

    int32_t inter_w = max_i32(0, x2 - x1);
    int32_t inter_h = max_i32(0, y2 - y1);
    int32_t inter_area = inter_w * inter_h;

    int32_t area_a = (a->x2 - a->x1) * (a->y2 - a->y1);
    int32_t area_b = (b->x2 - b->x1) * (b->y2 - b->y1);
    int32_t union_area = area_a + area_b - inter_area;

    if (union_area <= 0) return 0;
    return (inter_area * 100) / union_area;
}

/**
 * @brief Calculate center distance
 */
static int32_t calc_center_dist(const DetectionBox_t *a, const DetectionBox_t *b)
{
    int32_t cx_a = (a->x1 + a->x2) / 2;
    int32_t cy_a = (a->y1 + a->y2) / 2;
    int32_t cx_b = (b->x1 + b->x2) / 2;
    int32_t cy_b = (b->y1 + b->y2) / 2;
    int32_t dx = cx_a - cx_b;
    int32_t dy = cy_a - cy_b;
    return isqrt(dx * dx + dy * dy);
}

/**
 * @brief Allocate new track_id
 */
static uint8_t alloc_id(void)
{
    uint8_t id = g_ctx.next_track_id++;
    if (g_ctx.next_track_id == 0) g_ctx.next_track_id = 1;  /* 跳过 0 */
    return id;
}

/*============================================================================
 * ID Assignment (with history retention)
 *============================================================================*/

/**
 * @brief Find best matching slot for a detection
 * @return Slot index, -1 if no match
 */
static int32_t match_slot(const DetectionBox_t *box, bool *slot_matched)
{
    int32_t best_slot = -1;
    int32_t best_iou = TRACKER_IOU_THRESHOLD_PCT - 1;
    int32_t best_dist = TRACKER_CENTER_DIST_THRESHOLD;
    
    for (int i = 0; i < MAX_TRACK_SLOTS; i++) {
        if (!g_ctx.slots[i].active || slot_matched[i]) continue;
        
        /* IoU 优先 */
        int32_t iou = calc_iou_pct(box, &g_ctx.slots[i].box);
        if (iou >= TRACKER_IOU_THRESHOLD_PCT && iou > best_iou) {
            best_iou = iou;
            best_slot = i;
            continue;
        }
        
        /* 距离备选 (只有没找到 IoU 匹配时) */
        if (best_slot < 0) {
            int32_t dist = calc_center_dist(box, &g_ctx.slots[i].box);
            if (dist < best_dist) {
                best_dist = dist;
                best_slot = i;
            }
        }
    }
    
    return best_slot;
}

/**
 * @brief Find empty slot
 */
static int32_t find_empty_slot(void)
{
    for (int i = 0; i < MAX_TRACK_SLOTS; i++) {
        if (!g_ctx.slots[i].active) return i;
    }
    return -1;
}

/**
 * @brief Assign track IDs with history retention
 *
 * 漏检时保留槽位最多 TRACK_MAX_MISS 帧，
 * 目标重新出现时可以匹配回原 ID。
 */
static void assign_track_ids(DetectionResult_t *result)
{
    if (result == NULL) return;
    
    bool slot_matched[MAX_TRACK_SLOTS] = {false};

    /* Step 1: Match detections to existing slots */
    for (uint32_t i = 0; i < result->count && i < MAX_DETECTION_COUNT; i++) {
        DetectionBox_t *cur = &result->boxes[i];
        
        int32_t slot_idx = match_slot(cur, slot_matched);
        
        if (slot_idx >= 0) {
            /* 匹配成功: 复用 ID，更新槽位 */
            TrackSlot_t *slot = &g_ctx.slots[slot_idx];
            cur->track_id = slot->track_id;
            slot->box = *cur;
            slot->miss_count = 0;
            slot_matched[slot_idx] = true;
            
#if TRACKER_DEBUG_LEVEL >= 2
            rt_kprintf("[TRK] Match: det[%lu] -> slot[%ld] id=%d\n",
                       (unsigned long)i, (long)slot_idx, cur->track_id);
#endif
        } else {
            /* 无匹配: 分配新槽位和 ID */
            int32_t empty = find_empty_slot();
            if (empty >= 0) {
                TrackSlot_t *slot = &g_ctx.slots[empty];
                slot->track_id = alloc_id();
                slot->box = *cur;
                slot->miss_count = 0;
                slot->active = 1;
                slot_matched[empty] = true;
                
                cur->track_id = slot->track_id;
                
#if TRACKER_DEBUG_LEVEL >= 2
                rt_kprintf("[TRK] New: det[%lu] -> slot[%ld] id=%d\n",
                           (unsigned long)i, (long)empty, cur->track_id);
#endif
            } else {
                /* 槽位满，直接分配临时 ID */
                cur->track_id = alloc_id();
#if TRACKER_DEBUG_LEVEL >= 1
                rt_kprintf("[TRK] WARN: slots full, temp id=%d\n", cur->track_id);
#endif
            }
        }
    }
    
    /* Step 2: 未匹配槽位 miss_count++，超过阈值则删除 */
    for (int i = 0; i < MAX_TRACK_SLOTS; i++) {
        if (g_ctx.slots[i].active && !slot_matched[i]) {
            g_ctx.slots[i].miss_count++;
            
            if (g_ctx.slots[i].miss_count > TRACK_MAX_MISS) {
#if TRACKER_DEBUG_LEVEL >= 2
                rt_kprintf("[TRK] Expire: slot[%d] id=%d after %d miss\n",
                           i, g_ctx.slots[i].track_id, g_ctx.slots[i].miss_count);
#endif
                g_ctx.slots[i].active = 0;
            }
        }
    }
}

/*============================================================================
 * Velocity Estimation
 *============================================================================*/

/**
 * @brief Find velocity slot by track_id
 */
static VelocityEstimator_t* find_velocity_slot(uint8_t track_id)
{
    for (int i = 0; i < MAX_VELOCITY_SLOTS; i++) {
        if (g_ctx.velocity[i].valid && g_ctx.velocity[i].track_id == track_id) {
            return &g_ctx.velocity[i];
        }
    }
    return NULL;
}

/**
 * @brief Allocate velocity slot
 */
static VelocityEstimator_t* alloc_velocity_slot(uint8_t track_id)
{
    /* Find empty slot */
    for (int i = 0; i < MAX_VELOCITY_SLOTS; i++) {
        if (!g_ctx.velocity[i].valid) {
            g_ctx.velocity[i].valid = 1;
            g_ctx.velocity[i].track_id = track_id;
            g_ctx.velocity[i].update_count = 0;
            g_ctx.velocity[i].vx = 0;
            g_ctx.velocity[i].vy = 0;
            return &g_ctx.velocity[i];
        }
    }
    
    /* Full - reuse oldest (simple LRU: use first slot) */
    g_ctx.velocity[0].valid = 1;
    g_ctx.velocity[0].track_id = track_id;
    g_ctx.velocity[0].update_count = 0;
    g_ctx.velocity[0].vx = 0;
    g_ctx.velocity[0].vy = 0;
    return &g_ctx.velocity[0];
}

/**
 * @brief Update velocity for all detections
 */
static void update_velocities(DetectionResult_t *result)
{
    bool slot_used[MAX_VELOCITY_SLOTS] = {false};
    
    for (uint32_t i = 0; i < result->count && i < MAX_DETECTION_COUNT; i++) {
        DetectionBox_t *box = &result->boxes[i];
        int32_t cx = (box->x1 + box->x2) / 2;
        int32_t cy = (box->y1 + box->y2) / 2;
        
        VelocityEstimator_t *vel = find_velocity_slot(box->track_id);
        if (vel == NULL) {
            vel = alloc_velocity_slot(box->track_id);
            vel->last_cx = cx;
            vel->last_cy = cy;
        }
        
        /* Mark as used */
        int slot_idx = vel - g_ctx.velocity;
        slot_used[slot_idx] = true;
        
        /* Calculate velocity */
        if (vel->update_count > 0) {
            int32_t dx = cx - vel->last_cx;
            int32_t dy = cy - vel->last_cy;
            
            /* Simple exponential smoothing: new = 0.7 * new + 0.3 * old */
            vel->vx = (int8_t)((dx * 7 + vel->vx * 3) / 10);
            vel->vy = (int8_t)((dy * 7 + vel->vy * 3) / 10);
        }
        
        vel->last_cx = cx;
        vel->last_cy = cy;
        vel->update_count++;
        
        /* Fill box velocity fields */
        box->vx = vel->vx;
        box->vy = vel->vy;
        box->speed = (uint8_t)min_i32(255, isqrt(vel->vx * vel->vx + vel->vy * vel->vy) * 10);
        box->kf_confidence = (vel->update_count >= 3) ? 100 : (vel->update_count * 30);
    }
    
    /* Clear unused slots (target disappeared) */
    for (int i = 0; i < MAX_VELOCITY_SLOTS; i++) {
        if (g_ctx.velocity[i].valid && !slot_used[i]) {
            /* Keep for a few frames in case target reappears */
            /* For simplicity, just clear immediately in v2 */
            g_ctx.velocity[i].valid = 0;
        }
    }
}

/*============================================================================
 * Public API
 *============================================================================*/

void tracker_init(void)
{
    memset(&g_ctx, 0, sizeof(g_ctx));
    g_ctx.next_track_id = 1;
    
#if TRACKER_DEBUG_LEVEL >= 1
    rt_kprintf("[TRK] Tracker v2 init (IoU>%d%% dist<%dpx)\n",
               TRACKER_IOU_THRESHOLD_PCT, TRACKER_CENTER_DIST_THRESHOLD);
#endif
}

void tracker_reset(void)
{
    memset(g_ctx.slots, 0, sizeof(g_ctx.slots));
    g_ctx.next_track_id = 1;
    memset(g_ctx.velocity, 0, sizeof(g_ctx.velocity));
    g_ctx.frame_count = 0;
    
#if TRACKER_DEBUG_LEVEL >= 1
    rt_kprintf("[TRK] Reset\n");
#endif
}

void tracker_process(DetectionResult_t *result)
{
    if (result == NULL) return;
    
    g_ctx.frame_count++;
    
    /* Step 1: Assign track IDs (with slot-based history retention) */
    assign_track_ids(result);
    
    /* Step 2: Update velocities */
    update_velocities(result);
    
    /* Step 3: DSP does NOT select target - let M4 decide */
    result->selected_idx = -1;
    
    /* Debug output */
#if TRACKER_DEBUG_LEVEL >= 1
    if (result->count > 0) {
        rt_kprintf("[TRK] Frame %lu: %lu targets [", 
                   (unsigned long)g_ctx.frame_count, (unsigned long)result->count);
        for (uint32_t i = 0; i < result->count && i < MAX_DETECTION_COUNT; i++) {
            DetectionBox_t *b = &result->boxes[i];
            int32_t cx = (b->x1 + b->x2) / 2;
            int32_t cy = (b->y1 + b->y2) / 2;
            rt_kprintf("id%d@(%ld,%ld)v(%d,%d)", 
                       b->track_id, (long)cx, (long)cy, b->vx, b->vy);
            if (i < result->count - 1) rt_kprintf(" ");
        }
        rt_kprintf("]\n");
    }
#endif
}
