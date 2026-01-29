/**
 * @file dsp_tracker.c
 * @brief DSP 侧多目标跟踪器实现 - 基于 IoU 匹配
 *
 * 为所有目标分配稳定的 track_id，并选择最靠近画面中心的目标。
 *
 * @version 2.0
 * @date 2026-01-29
 */

#include <string.h>
#include "dsp_tracker.h"
#include "custom_printf.h"

/*============================================================================
 * 跟踪器状态
 *============================================================================*/

typedef struct {
    DetectionBox_t prev_boxes[MAX_DETECTION_COUNT]; /**< 上一帧的检测框 */
    uint32_t       prev_count;                       /**< 上一帧目标数量 */
    uint8_t        next_track_id;                    /**< 下一个可分配的 ID */
    uint8_t        selected_track_id;                /**< 当前选中的 track_id */
} Tracker_t;

static Tracker_t g_tracker;

/*============================================================================
 * 辅助函数
 *============================================================================*/

static inline int32_t max_i32(int32_t a, int32_t b) { return a > b ? a : b; }
static inline int32_t min_i32(int32_t a, int32_t b) { return a < b ? a : b; }

/**
 * @brief 计算两个边界框的 IoU（定点数优化，返回 0-100）
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
    /* 返回百分比 0-100，避免浮点运算 */
    return (inter_area * 100) / union_area;
}

/**
 * @brief 计算边界框中心到画面中心的距离平方
 */
static int32_t calc_center_dist_sq(const DetectionBox_t *box)
{
    int32_t cx = (box->x1 + box->x2) / 2;
    int32_t cy = (box->y1 + box->y2) / 2;
    int32_t dx = cx - (TRACKER_FRAME_WIDTH / 2);
    int32_t dy = cy - (TRACKER_FRAME_HEIGHT / 2);
    return dx * dx + dy * dy;
}

/**
 * @brief 计算两个边界框中心点之间的距离
 */
static int32_t calc_box_center_dist(const DetectionBox_t *a, const DetectionBox_t *b)
{
    int32_t cx_a = (a->x1 + a->x2) / 2;
    int32_t cy_a = (a->y1 + a->y2) / 2;
    int32_t cx_b = (b->x1 + b->x2) / 2;
    int32_t cy_b = (b->y1 + b->y2) / 2;
    int32_t dx = cx_a - cx_b;
    int32_t dy = cy_a - cy_b;
    /* 返回曼哈顿距离（避免开方） */
    return (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
}

/**
 * @brief 分配新的 track_id
 */
static uint8_t alloc_track_id(void)
{
    uint8_t id = g_tracker.next_track_id;
    g_tracker.next_track_id++;
    if (g_tracker.next_track_id == 0) {
        g_tracker.next_track_id = 1;  /* 跳过 0 */
    }
    return id;
}

/*============================================================================
 * API 实现
 *============================================================================*/

void tracker_init(void)
{
    memset(&g_tracker, 0, sizeof(g_tracker));
    g_tracker.next_track_id = 1;
    
#if TRACKER_DEBUG_LEVEL >= 1
    rt_kprintf("[DSP:TRK] Multi-target tracker init (IoU>%d%%)\n", 
               TRACKER_IOU_THRESHOLD_PCT);
#endif
}

void tracker_reset(void)
{
    g_tracker.prev_count = 0;
    g_tracker.next_track_id = 1;
    g_tracker.selected_track_id = 0;
    
#if TRACKER_DEBUG_LEVEL >= 1
    rt_kprintf("[DSP:TRK] Tracker reset\n");
#endif
}

void tracker_assign_ids(DetectionResult_t *result)
{
    if (result == NULL) return;

    /* 无检测结果 */
    if (result->count == 0) {
        g_tracker.prev_count = 0;
        return;
    }

    /* 标记上一帧哪些目标已被匹配 */
    bool prev_matched[MAX_DETECTION_COUNT] = {false};
    uint32_t new_ids = 0;

    /* 贪婪匹配：为当前帧每个目标找最佳匹配 */
    for (uint32_t cur_idx = 0; cur_idx < result->count && cur_idx < MAX_DETECTION_COUNT; cur_idx++)
    {
        DetectionBox_t *cur_box = &result->boxes[cur_idx];
        int32_t best_iou_pct = TRACKER_IOU_THRESHOLD_PCT;
        int32_t best_prev_idx = -1;

        /* 在上一帧中查找最佳匹配 */
        for (uint32_t prev_idx = 0; prev_idx < g_tracker.prev_count; prev_idx++)
        {
            if (prev_matched[prev_idx]) continue;  /* 已被其他目标匹配 */

            int32_t iou_pct = calc_iou_pct(cur_box, &g_tracker.prev_boxes[prev_idx]);
            if (iou_pct > best_iou_pct) {
                best_iou_pct = iou_pct;
                best_prev_idx = (int32_t)prev_idx;
            }
        }

        /* IoU 匹配失败时，尝试中心点距离匹配 */
        if (best_prev_idx < 0 && g_tracker.prev_count > 0) {
            int32_t best_dist = TRACKER_CENTER_DIST_THRESHOLD;
            for (uint32_t prev_idx = 0; prev_idx < g_tracker.prev_count; prev_idx++)
            {
                if (prev_matched[prev_idx]) continue;
                
                int32_t dist = calc_box_center_dist(cur_box, &g_tracker.prev_boxes[prev_idx]);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_prev_idx = (int32_t)prev_idx;
                }
            }
#if TRACKER_DEBUG_LEVEL >= 2
            if (best_prev_idx >= 0) {
                rt_kprintf("[DSP:TRK] [%lu] id=%d matched by dist=%ld\n",
                           (unsigned long)cur_idx, 
                           g_tracker.prev_boxes[best_prev_idx].track_id,
                           (long)best_dist);
            }
#endif
        }

        if (best_prev_idx >= 0) {
            /* 匹配成功，继承 track_id */
            cur_box->track_id = g_tracker.prev_boxes[best_prev_idx].track_id;
            prev_matched[best_prev_idx] = true;
#if TRACKER_DEBUG_LEVEL >= 3
            rt_kprintf("[DSP:TRK] [%lu] id=%d matched prev[%ld] iou=%ld%%\n",
                       (unsigned long)cur_idx, cur_box->track_id, (long)best_prev_idx, (long)best_iou_pct);
#endif
        } else {
            /* 新目标，分配新 track_id */
            cur_box->track_id = alloc_track_id();
            new_ids++;
#if TRACKER_DEBUG_LEVEL >= 2
            rt_kprintf("[DSP:TRK] [%lu] new id=%d\n", (unsigned long)cur_idx, cur_box->track_id);
#endif
        }
    }

    /* 保存当前帧用于下一帧匹配 */
    memcpy(g_tracker.prev_boxes, result->boxes, result->count * sizeof(DetectionBox_t));
    g_tracker.prev_count = result->count;

#if TRACKER_DEBUG_LEVEL >= 2
    if (new_ids > 0 || result->count > 1) {
        rt_kprintf("[DSP:TRK] count=%lu new=%lu next_id=%d\n",
                   (unsigned long)result->count, (unsigned long)new_ids, g_tracker.next_track_id);
    }
#endif
}

void tracker_select_target(DetectionResult_t *result)
{
    if (result == NULL || result->count == 0) {
        result->selected_idx = -1;
        return;
    }

    int32_t selected = -1;

    /* 优先保持之前选中的目标 */
    if (g_tracker.selected_track_id != 0) {
        for (uint32_t i = 0; i < result->count; i++) {
            if (result->boxes[i].track_id == g_tracker.selected_track_id) {
                selected = (int32_t)i;
                break;
            }
        }
    }

    /* 如果之前的目标不存在，选择最靠近中心的目标 */
    if (selected < 0) {
        int32_t min_dist = 0x7FFFFFFF;
        for (uint32_t i = 0; i < result->count; i++) {
            int32_t dist = calc_center_dist_sq(&result->boxes[i]);
            if (dist < min_dist) {
                min_dist = dist;
                selected = (int32_t)i;
            }
        }
        
        /* 更新选中的 track_id */
        if (selected >= 0) {
            g_tracker.selected_track_id = result->boxes[selected].track_id;
#if TRACKER_DEBUG_LEVEL >= 1
            rt_kprintf("[DSP:TRK] Selected new target: id=%d idx=%ld\n",
                       g_tracker.selected_track_id, (long)selected);
#endif
        }
    }

    result->selected_idx = selected;

#if TRACKER_DEBUG_LEVEL >= 2
    if (selected >= 0) {
        rt_kprintf("[DSP:TRK] selected_idx=%ld track_id=%d\n",
                   (long)selected, result->boxes[selected].track_id);
    }
#endif
}

uint8_t tracker_get_selected_id(void)
{
    return g_tracker.selected_track_id;
}