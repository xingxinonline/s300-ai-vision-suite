/**
 * @file kalman_filter.c
 * @brief Lightweight 2D Kalman Filter - Float Version
 *
 * Uses single-precision float (double NOT supported on this DSP).
 *
 * @version 1.1
 * @date 2026-01-30
 */

#include "kalman_filter.h"
#include <string.h>
#include <math.h>

/*============================================================================
 * Internal Functions
 *============================================================================*/

/**
 * @brief Initialize 1D Kalman state
 */
static void kalman_1d_init(KalmanState1D_t *state, float initial_pos)
{
    state->x = initial_pos;
    state->v = 0.0f;
    state->p_x = KF_INITIAL_UNCERTAINTY;
    state->p_v = KF_INITIAL_UNCERTAINTY;
}

/**
 * @brief 1D Predict step
 *
 * State transition: x' = x + v, v' = v * decay
 * Uncertainty increase: P' = P + Q
 */
static float kalman_1d_predict(KalmanState1D_t *state)
{
    /* State prediction */
    state->x = state->x + state->v;
    state->v = state->v * KF_VELOCITY_DECAY;  /* Velocity decay */
    
    /* Uncertainty prediction */
    state->p_x = state->p_x + KF_PROCESS_NOISE_POS;
    state->p_v = state->p_v + KF_PROCESS_NOISE_VEL;
    
    return state->x;
}

/**
 * @brief 1D Update step (with observation)
 *
 * Kalman gain: K = P / (P + R)
 * State update: x = x + K * (z - x)
 * Uncertainty update: P = (1 - K) * P
 */
static float kalman_1d_update(KalmanState1D_t *state, float measurement)
{
    /* Predict first */
    kalman_1d_predict(state);
    
    /* Compute Kalman gain K = P / (P + R) */
    float denom = state->p_x + KF_MEASURE_NOISE;
    if (denom < 0.001f) denom = 0.001f;  /* Prevent division by zero */
    float K = state->p_x / denom;
    
    /* Clamp K to [0, 1] */
    if (K < 0.0f) K = 0.0f;
    if (K > 1.0f) K = 1.0f;
    
    /* Compute residual (innovation) */
    float residual = measurement - state->x;
    
    /* Update position estimate */
    state->x = state->x + K * residual;
    
    /* Update velocity estimate (infer velocity from residual) */
    state->v = state->v + K * (residual - state->v);
    
    /* Update uncertainty */
    state->p_x = (1.0f - K) * state->p_x;
    state->p_v = (1.0f - K) * state->p_v;
    
    /* Prevent uncertainty from becoming too small */
    if (state->p_x < KF_MIN_UNCERTAINTY) {
        state->p_x = KF_MIN_UNCERTAINTY;
    }
    if (state->p_v < KF_MIN_UNCERTAINTY) {
        state->p_v = KF_MIN_UNCERTAINTY;
    }
    
    return state->x;
}

/**
 * @brief Convert bounding box to center + size
 */
static void box_to_center(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                          float *cx, float *cy, float *w, float *h)
{
    *cx = (float)(x1 + x2) * 0.5f;
    *cy = (float)(y1 + y2) * 0.5f;
    *w = (float)(x2 - x1);
    *h = (float)(y2 - y1);
}

/**
 * @brief Convert center + size to bounding box
 */
static void center_to_box(float cx, float cy, float w, float h,
                          int16_t *x1, int16_t *y1, int16_t *x2, int16_t *y2)
{
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    *x1 = (int16_t)(cx - hw + 0.5f);
    *y1 = (int16_t)(cy - hh + 0.5f);
    *x2 = (int16_t)(cx + hw + 0.5f);
    *y2 = (int16_t)(cy + hh + 0.5f);
}

/**
 * @brief Compute speed from velocity components
 */
static float compute_speed(float vx, float vy)
{
    return sqrtf(vx * vx + vy * vy);
}

/**
 * @brief Convert speed to arrow size (0-255)
 * Maps speed 0-20 pixels/frame to 0-255
 */
static uint8_t speed_to_arrow_size(float speed)
{
    float scaled = speed * 12.75f;  /* 20 -> 255 */
    if (scaled > 255.0f) scaled = 255.0f;
    if (scaled < 0.0f) scaled = 0.0f;
    return (uint8_t)(scaled + 0.5f);
}

/*============================================================================
 * API Implementation
 *============================================================================*/

void kalman_box_init(KalmanBoxFilter_t *kf)
{
    memset(kf, 0, sizeof(KalmanBoxFilter_t));
}

void kalman_box_reset(KalmanBoxFilter_t *kf,
                      int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                      uint8_t track_id)
{
    float cx, cy, w, h;
    box_to_center(x1, y1, x2, y2, &cx, &cy, &w, &h);
    
    kalman_1d_init(&kf->cx, cx);
    kalman_1d_init(&kf->cy, cy);
    kalman_1d_init(&kf->w, w);
    kalman_1d_init(&kf->h, h);
    
    kf->track_id = track_id;
    kf->initialized = 1;
    kf->predict_count = 0;
}

void kalman_box_predict(KalmanBoxFilter_t *kf, KalmanBoxOutput_t *out)
{
    if (!kf->initialized) {
        memset(out, 0, sizeof(KalmanBoxOutput_t));
        return;
    }
    
    /* Predict each dimension */
    float cx = kalman_1d_predict(&kf->cx);
    float cy = kalman_1d_predict(&kf->cy);
    float w = kalman_1d_predict(&kf->w);
    float h = kalman_1d_predict(&kf->h);
    
    /* Clamp size to minimum */
    if (w < 10.0f) w = 10.0f;
    if (h < 10.0f) h = 10.0f;
    
    /* Convert to bounding box */
    center_to_box(cx, cy, w, h, &out->x1, &out->y1, &out->x2, &out->y2);
    
    /* Velocity output (for M4 arrow drawing) */
    out->vx = (int16_t)(kf->cx.v + 0.5f);
    out->vy = (int16_t)(kf->cy.v + 0.5f);
    
    /* Speed for arrow size */
    float speed = compute_speed(kf->cx.v, kf->cy.v);
    out->speed = speed_to_arrow_size(speed);
    
    /* Confidence decreases with prediction count */
    kf->predict_count++;
    if (kf->predict_count >= 10) {
        out->confidence = 10;
    } else {
        out->confidence = 100 - kf->predict_count * 10;
    }
}

void kalman_box_predict_only(const KalmanBoxFilter_t *kf, KalmanBoxOutput_t *out)
{
    if (!kf->initialized) {
        memset(out, 0, sizeof(KalmanBoxOutput_t));
        return;
    }
    
    /* Predict without modifying state (read-only) */
    float cx = kf->cx.x + kf->cx.v;
    float cy = kf->cy.x + kf->cy.v;
    float w = kf->w.x + kf->w.v;
    float h = kf->h.x + kf->h.v;
    
    /* Clamp size to minimum */
    if (w < 10.0f) w = 10.0f;
    if (h < 10.0f) h = 10.0f;
    
    /* Convert to bounding box */
    center_to_box(cx, cy, w, h, &out->x1, &out->y1, &out->x2, &out->y2);
    
    /* Velocity output */
    out->vx = (int16_t)(kf->cx.v + 0.5f);
    out->vy = (int16_t)(kf->cy.v + 0.5f);
    
    /* Speed for arrow size */
    float speed = compute_speed(kf->cx.v, kf->cy.v);
    out->speed = speed_to_arrow_size(speed);
    
    /* Confidence based on predict count */
    if (kf->predict_count >= 10) {
        out->confidence = 10;
    } else {
        out->confidence = 100 - kf->predict_count * 10;
    }
}

void kalman_box_update(KalmanBoxFilter_t *kf,
                       int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                       KalmanBoxOutput_t *out)
{
    float in_cx, in_cy, in_w, in_h;
    box_to_center(x1, y1, x2, y2, &in_cx, &in_cy, &in_w, &in_h);
    
    if (!kf->initialized) {
        /* First observation, initialize directly */
        kalman_box_reset(kf, x1, y1, x2, y2, kf->track_id);
        out->x1 = x1;
        out->y1 = y1;
        out->x2 = x2;
        out->y2 = y2;
        out->vx = 0;
        out->vy = 0;
        out->speed = 0;
        out->confidence = 100;
        return;
    }
    
    /* Update each dimension */
    float cx = kalman_1d_update(&kf->cx, in_cx);
    float cy = kalman_1d_update(&kf->cy, in_cy);
    float w = kalman_1d_update(&kf->w, in_w);
    float h = kalman_1d_update(&kf->h, in_h);
    
    /* Clamp size to minimum */
    if (w < 10.0f) w = 10.0f;
    if (h < 10.0f) h = 10.0f;
    
    /* Convert to bounding box */
    center_to_box(cx, cy, w, h, &out->x1, &out->y1, &out->x2, &out->y2);
    
    /* Velocity output (for M4 arrow drawing) */
    out->vx = (int16_t)(kf->cx.v + 0.5f);
    out->vy = (int16_t)(kf->cy.v + 0.5f);
    
    /* Speed for arrow size */
    float speed = compute_speed(kf->cx.v, kf->cy.v);
    out->speed = speed_to_arrow_size(speed);
    
    /* Observation received, reset predict count, full confidence */
    kf->predict_count = 0;
    out->confidence = 100;
}

bool kalman_box_is_valid(const KalmanBoxFilter_t *kf, uint8_t max_predict)
{
    if (!kf->initialized) return false;
    return kf->predict_count <= max_predict;
}

void kalman_box_get_velocity(const KalmanBoxFilter_t *kf, float *vx, float *vy)
{
    if (!kf->initialized) {
        if (vx) *vx = 0.0f;
        if (vy) *vy = 0.0f;
        return;
    }
    if (vx) *vx = kf->cx.v;
    if (vy) *vy = kf->cy.v;
}

float kalman_box_get_speed(const KalmanBoxFilter_t *kf)
{
    if (!kf->initialized) return 0.0f;
    return compute_speed(kf->cx.v, kf->cy.v);
}
