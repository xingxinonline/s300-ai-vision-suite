/**
 * @file kalman_filter.h
 * @brief Lightweight 2D Kalman Filter - Float Version
 *
 * Used for target tracking position prediction and smoothing:
 * - Bounding box center (cx, cy) and size (w, h) tracking
 * - Velocity estimation and position prediction
 * - Trajectory prediction during brief occlusions
 * - Detection jitter smoothing
 *
 * Uses single-precision float (double is NOT supported on this DSP).
 *
 * @version 1.1
 * @date 2026-01-30
 */

#ifndef __KALMAN_FILTER_H__
#define __KALMAN_FILTER_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================
 * Kalman Filter Parameters
 *============================================================================*/

/** Process noise (position), higher = more responsive but less smooth */
#define KF_PROCESS_NOISE_POS    0.05f

/** Process noise (velocity) */
#define KF_PROCESS_NOISE_VEL    0.02f

/** Measurement noise, higher = smoother but slower response */
#define KF_MEASURE_NOISE        0.1f

/** Initial uncertainty */
#define KF_INITIAL_UNCERTAINTY  10.0f

/** Velocity decay factor (velocity decreases during occlusion) */
#define KF_VELOCITY_DECAY       0.95f

/** Minimum uncertainty to prevent filter collapse */
#define KF_MIN_UNCERTAINTY      0.01f

/*============================================================================
 * Data Structures
 *============================================================================*/

/**
 * @brief 1D Kalman filter state
 *
 * State vector: [position, velocity]
 */
typedef struct {
    float x;      /**< Position estimate */
    float v;      /**< Velocity estimate (pixels/frame) */
    float p_x;    /**< Position uncertainty */
    float p_v;    /**< Velocity uncertainty */
} KalmanState1D_t;

/**
 * @brief Bounding box Kalman filter
 *
 * Tracks bounding box center and size
 */
typedef struct {
    KalmanState1D_t cx;         /**< Center X */
    KalmanState1D_t cy;         /**< Center Y */
    KalmanState1D_t w;          /**< Width */
    KalmanState1D_t h;          /**< Height */
    uint8_t         track_id;   /**< Associated track_id */
    uint8_t         initialized;/**< Is initialized */
    uint8_t         predict_count; /**< Consecutive prediction count (no observation) */
    uint8_t         reserved;
} KalmanBoxFilter_t;

/**
 * @brief Filtered bounding box output with velocity info for M4 arrow drawing
 */
typedef struct {
    int16_t x1, y1, x2, y2;     /**< Bounding box coordinates */
    int16_t vx, vy;             /**< Velocity estimate (pixels/frame, for arrow direction) */
    uint8_t confidence;         /**< Confidence (0-100), decreases with prediction count */
    uint8_t speed;              /**< Speed magnitude (0-255, for arrow size) */
} KalmanBoxOutput_t;

/*============================================================================
 * API Functions
 *============================================================================*/

/**
 * @brief Initialize bounding box Kalman filter
 */
void kalman_box_init(KalmanBoxFilter_t *kf);

/**
 * @brief Initialize/reset filter with detection result
 */
void kalman_box_reset(KalmanBoxFilter_t *kf, 
                      int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                      uint8_t track_id);

/**
 * @brief Predict next frame position (call when no observation)
 * @note This function MODIFIES filter state (increases predict_count, updates uncertainty)
 */
void kalman_box_predict(KalmanBoxFilter_t *kf, KalmanBoxOutput_t *out);

/**
 * @brief Predict next frame position WITHOUT modifying filter state (read-only)
 * @note Use this for matching purposes - doesn't affect filter state
 */
void kalman_box_predict_only(const KalmanBoxFilter_t *kf, KalmanBoxOutput_t *out);

/**
 * @brief Update filter with detection result (call when observation available)
 */
void kalman_box_update(KalmanBoxFilter_t *kf,
                       int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                       KalmanBoxOutput_t *out);

/**
 * @brief Check if filter is still valid (not exceeded max prediction count)
 */
bool kalman_box_is_valid(const KalmanBoxFilter_t *kf, uint8_t max_predict);

/**
 * @brief Get current velocity in pixels per frame
 * @param kf Filter instance
 * @param vx Output X velocity (can be NULL)
 * @param vy Output Y velocity (can be NULL)
 */
void kalman_box_get_velocity(const KalmanBoxFilter_t *kf, float *vx, float *vy);

/**
 * @brief Get velocity magnitude (speed) in pixels per frame
 * @param kf Filter instance
 * @return Speed in pixels per frame
 */
float kalman_box_get_speed(const KalmanBoxFilter_t *kf);

#ifdef __cplusplus
}
#endif

#endif /* __KALMAN_FILTER_H__ */
