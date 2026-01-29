/**
 * @file dsp_tracker.h
 * @brief DSP 侧多目标跟踪器 - 基于 IoU 匹配
 *
 * 为所有检测目标分配稳定的 track_id，并选择最靠近画面中心的目标
 * 作为追踪目标（通过 selected_idx 告知 M4）。
 *
 * @version 2.0
 * @date 2026-01-29
 */

#ifndef __DSP_TRACKER_H__
#define __DSP_TRACKER_H__

#include <stdint.h>
#include <stdbool.h>
#include "detection_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================
 * 配置参数
 *============================================================================*/

/** IoU 匹配阈值（百分比 0-100），低于此值尝试中心点距离匹配 */
#define TRACKER_IOU_THRESHOLD_PCT   20

/** 中心点距离阈值（像素），IoU失败时的备选匹配 */
#define TRACKER_CENTER_DIST_THRESHOLD  80

/** 目标丢失后保持的最大帧数（用于短暂遮挡恢复） */
#define TRACKER_MAX_LOST_FRAMES     5

/** 调试日志级别 (0=关闭, 1=关键, 2=详细, 3=全部) */
#define TRACKER_DEBUG_LEVEL         0

/** 画面尺寸（用于计算中心距离） */
#define TRACKER_FRAME_WIDTH         240
#define TRACKER_FRAME_HEIGHT        320

/*============================================================================
 * API 函数
 *============================================================================*/

/**
 * @brief 初始化跟踪器
 */
void tracker_init(void);

/**
 * @brief 重置跟踪器状态，清除所有跟踪目标
 */
void tracker_reset(void);

/**
 * @brief 为当前帧的检测结果分配 track_id（多目标跟踪）
 *
 * 算法（贪婪 IoU 匹配）：
 * 1. 遍历当前帧每个目标
 * 2. 在上一帧中找 IoU 最大且 > 阈值的目标
 * 3. 匹配成功：继承 track_id
 * 4. 匹配失败：分配新的 track_id
 *
 * @param result 当前帧检测结果（输入/输出，会修改 track_id 字段）
 */
void tracker_assign_ids(DetectionResult_t *result);

/**
 * @brief 选择追踪目标（最靠近画面中心）
 *
 * 选择规则：
 * 1. 优先保持之前选中的目标（如果仍存在）
 * 2. 否则选择最靠近画面中心的目标
 *
 * @param result 当前帧检测结果（输入/输出，会修改 selected_idx 字段）
 */
void tracker_select_target(DetectionResult_t *result);

/**
 * @brief 获取当前选中的 track_id
 *
 * @return 当前选中的 track_id，0 表示无选中目标
 */
uint8_t tracker_get_selected_id(void);

#ifdef __cplusplus
}
#endif

#endif /* __DSP_TRACKER_H__ */
