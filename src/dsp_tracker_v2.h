/**
 * @file dsp_tracker_v2.h
 * @brief DSP 轻量级多目标 ID 关联器
 *
 * 设计原则 (v2 简化版):
 * - DSP 只负责: 检测 + 过滤 + ID 关联 + 速度估计
 * - M4 负责: 目标选择 + 跟踪决策 + 遮挡处理 + 云台控制
 *
 * @version 2.0
 * @date 2026-02-04
 */

#ifndef __DSP_TRACKER_V2_H__
#define __DSP_TRACKER_V2_H__

#include <stdint.h>
#include <stdbool.h>
#include "detection_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================
 * Configuration
 *============================================================================*/

/** IoU 匹配阈值（百分比），低于此值尝试距离匹配 */
#define TRACKER_IOU_THRESHOLD_PCT       10

/** 中心点距离阈值（像素），IoU 失败时的备选匹配 
 *  160x128 图像对角线约 205px，设为 100px 允许较大移动 */
#define TRACKER_CENTER_DIST_THRESHOLD   100

/** 调试日志级别 (0=关闭, 1=关键, 2=详细) */
#define TRACKER_DEBUG_LEVEL             1

/*============================================================================
 * API Functions
 *============================================================================*/

/**
 * @brief 初始化跟踪器
 */
void tracker_init(void);

/**
 * @brief 重置跟踪器
 */
void tracker_reset(void);

/**
 * @brief 处理检测结果
 *
 * 完整的帧处理流程：
 * 1. ID 关联 (IoU/距离匹配)
 * 2. Kalman 速度估计
 * 3. 设置 selected_idx = -1 (DSP 不做选择)
 *
 * @param result 检测结果（输入/输出）
 */
void tracker_process(DetectionResult_t *result);

#ifdef __cplusplus
}
#endif

#endif /* __DSP_TRACKER_V2_H__ */
