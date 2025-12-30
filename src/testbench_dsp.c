
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

#include "reg.h"
#include "kernel.h"
#include "dsp_mm.h"
#include "vec-c.h"
//#include "face_detect.h"
#include "dsp_mailbox.h"

#include "custom_printf.h"

// 统一的DSP调试输出：使用串口直接输出，避免rt_kprintf占用资源
#ifndef DSP_LOG
#define DSP_LOG(fmt, ...) do { \
        char _dsp_log_buf[192]; \
        int _len = snprintf(_dsp_log_buf, sizeof(_dsp_log_buf), fmt, ##__VA_ARGS__); \
        if (_len < 0) { \
            /* snprintf 出错，仍尝试输出固定标记 */ \
            rt_hw_console_output("[DSP_LOG snprintf error]\n"); \
        } else { \
            /* 若内容被截断，添加省略标记 */ \
            if (_len >= (int)sizeof(_dsp_log_buf)) { \
                _dsp_log_buf[sizeof(_dsp_log_buf)-5] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-4] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-3] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-2] = '\n'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-1] = '\0'; \
            } \
            rt_hw_console_output(_dsp_log_buf); \
        } \
    } while(0)
#endif

// uint16_t display_width;
// uint16_t display_height;
// uint16_t snapshot_width;
// uint16_t snapshot_height;

// #define DISP_IMAGE_WIDTH            (display_width)
// #define DISP_IMAGE_HEIGHT           (display_height)
// #define SNAP_IMAGE_WIDTH            (snapshot_width)
// #define SNAP_IMAGE_HEIGHT           (snapshot_height)

// extern uint8_t bgr320_buffer1[160 * 120 * 3];

// uint32_t wframe0_addr;
// uint32_t wframe1_addr;
// uint32_t rframe0_addr;
// uint32_t rframe1_addr;
// uint32_t alpha0_addr;
// uint32_t alpha1_addr;

// uint16_t *wframe0_buffer;
// uint16_t *wframe1_buffer;
// uint16_t *rframe0_buffer;
// uint16_t *rframe1_buffer;
// uint8_t *alpha0_buffer;
// uint8_t *alpha1_buffer;

// uint32_t times_cycles = 0;
// uint32_t times_count = 0;
// uint32_t face_detect_count  __attribute__((used, section(".sram1_data"), aligned(16))) = 0;

// int32_t face_pos = 80;
// int32_t face_pos_last = 80;

// typedef uint16_t PIXEL565; // BGR565像素类型，2字节

// PIXEL565 bgr565_buffer1[160 * 128] __attribute__((used, section(".face_data"), aligned(16))) ;

// // 运行期上下文：集中管理缓冲区指针与分辨率参数，便于模块化
// typedef struct {
//     uint16_t *wframe0_buffer;
//     uint16_t *wframe1_buffer;
//     uint16_t *rframe0_buffer;
//     uint16_t *rframe1_buffer;
//     uint8_t  *alpha0_buffer;
//     uint8_t  *alpha1_buffer;
//     uint16_t display_width;
//     uint16_t display_height;
//     uint16_t snapshot_width;
//     uint16_t snapshot_height;
// } PipelineContext;

// // 记录前处理的几何变换，用于通用坐标逆变换
// typedef struct {
//     int srcW, srcH;     // 原图尺寸
//     int preW, preH;     // 旋转前的目标预处理尺寸（横屏:160x120，竖屏:120x160）
//     int cropOx, cropOy; // 在原图中的裁剪偏移（相对原图左上角）
//     int cropW, cropH;   // 裁剪后的区域尺寸（作为缩放输入尺寸）
//     int rotated;        // 是否做了 CCW90 旋转（1竖屏，0横屏）
// } Transform;

// /**
//  * 在同一块内存中对BGR565图像进行原地缩小
//  * 使用最邻近插值，从右下向左上遍历，避免数据覆盖问题。
//  *
//  * @param image      输入与输出的图像缓冲区
//  * @param orig_width 原始图像宽度
//  * @param orig_height原始图像高度
//  * @param new_width  缩小后的图像宽度
//  * @param new_height 缩小后的图像高度
//  * @return 0 表示成功，-1 表示失败
//  */
// int in_place_downscale_bgr565(PIXEL565* image,
//                               int orig_width, int orig_height,
//                               int new_width, int new_height) {
//     if (!image) {
//         return -1;
//     }

//     // 计算缩放比例
//     int scale_x = orig_width / new_width;
//     int scale_y = orig_height / new_height;

//     // 要求scale_x和scale_y为整数且>0
//     if (scale_x <= 0 || scale_y <= 0 ||
//         (orig_width % new_width != 0) ||
//         (orig_height % new_height != 0)) {
//         // 不满足整倍缩放要求
//         return -1;
//     }

//     // 从右下往左上遍历，防止数据被覆盖后还未读取
//     for (int y = new_height - 1; y >= 0; y--) {
//         for (int x = new_width - 1; x >= 0; x--) {
//             int src_x = x * scale_x;
//             int src_y = y * scale_y;
//             PIXEL565 pixel = image[src_y * orig_width + src_x];
//             image[y * new_width + x] = pixel;
//         }
//     }

//     return 0;
// }

// // 限制矩形坐标满足 0 < x1 < x2 <160，0 < y1 < y2 <120
// void clamp_face_rect(FaceRect *rect) {
//     // 辅助宏：将整数值限制在 [min, max] 范围内
//     #define CLAMP_INT(value, min_val, max_val) \
//         do { \
//             if ((value) < (min_val)) (value) = (min_val); \
//             else if ((value) > (max_val)) (value) = (max_val); \
//         } while (0)

//     // ----------- 处理 x 坐标 -----------
//     // 1. 先限制到默认范围 [0, DISP_IMAGE_WIDTH - 1]
//     CLAMP_INT(rect->x1, 0, DISP_IMAGE_WIDTH - 1);
//     CLAMP_INT(rect->x2, 0, DISP_IMAGE_WIDTH - 1);

//     // 2. 确保 x1 > 0
//     if (rect->x1 == 0) rect->x1 = 1;

//     // 3. 确保 x2 > x1，否则调整
//     if (rect->x2 <= rect->x1) {
//         rect->x2 = rect->x1 + 1;
//         // 如果超出最大值，回退到右边界并调整 x1
//         if (rect->x2 > DISP_IMAGE_WIDTH - 1) {
//             rect->x2 = DISP_IMAGE_WIDTH - 1;
//             rect->x1 = rect->x2 - 1;
//             if (rect->x1 < 1) rect->x1 = 1; // 二次保护
//         }
//     }

//     // ----------- 处理 y 坐标 -----------
//     // 1. 先限制到默认范围 [0, DISP_IMAGE_HEIGHT - 1]
//     CLAMP_INT(rect->y1, 0, DISP_IMAGE_HEIGHT - 1);
//     CLAMP_INT(rect->y2, 0, DISP_IMAGE_HEIGHT - 1);

//     // 2. 确保 y1 > 0
//     if (rect->y1 == 0) rect->y1 = 1;

//     // 3. 确保 y2 > y1，否则调整
//     if (rect->y2 <= rect->y1) {
//         rect->y2 = rect->y1 + 1;
//         // 如果超出最大值，回退到下边界并调整 y1
//         if (rect->y2 > DISP_IMAGE_HEIGHT - 1) {
//             rect->y2 = DISP_IMAGE_HEIGHT - 1;
//             rect->y1 = rect->y2 - 1;
//             if (rect->y1 < 1) rect->y1 = 1; // 二次保护
//         }
//     }
//     #undef CLAMP_INT
// }

// /**
//  * @brief 逆时针旋转90度（适用于RGB565格式）
//  * @param src 原图像数据指针（128 * 160）
//  * @param dst 目标图像数据指针（160 * 128）
//  */
// void rotate_ccw90(uint16_t *src, uint16_t *dst) {
//     const int srcW = 128, srcH = 160;
//     for (int y = 0; y < srcH; y++) {
//         for (int x = 0; x < srcW; x++) {
//             // 计算目标位置：旋转后宽高互换，坐标变换公式为 (y, srcW-1-x)
//             int dstX = y;
//             int dstY = srcW - 1 - x;
//             // 目标数组索引计算
//             int dstIdx = dstY * 160 + dstX; // 新宽度为160
//             // 原数组索引计算
//             int srcIdx = y * srcW + x;
//             // 复制RGB565像素（2字节）
//             dst[dstIdx] = src[srcIdx];
//         }
//     }
// }

// /**
//  * @brief 通用逆时针旋转90度（RGB565），支持任意 WxH -> HxW
//  */
// static void rotate_ccw90_generic(const uint16_t *src, int srcW, int srcH, uint16_t *dst) {
//     for (int y = 0; y < srcH; y++) {
//         for (int x = 0; x < srcW; x++) {
//             int dstX = y;
//             int dstY = srcW - 1 - x;
//             int dstIdx = dstY * srcH + dstX; // 目标宽度=srcH
//             int srcIdx = y * srcW + x;
//             dst[dstIdx] = src[srcIdx];
//         }
//     }
// }

// /**
//  * @brief 顺时针旋转90度还原（适用于RGB565格式）
//  * @param src 旋转后的图像数据指针（160 * 128）
//  * @param dst 还原后的图像数据指针（128 * 160）
//  */
// void restore_cw90(uint16_t *src, uint16_t *dst) {
//     const int srcW = 160, srcH = 128;
//     for (int y = 0; y < srcH; y++) {
//         for (int x = 0; x < srcW; x++) {
//             // 计算目标位置：旋转后宽高互换，坐标变换公式为 (srcH-1-y, x)
//             int dstX = srcH - 1 - y;
//             int dstY = x;
//             // 目标数组索引计算
//             int dstIdx = dstY * 128 + dstX; // 原宽度恢复为128
//             // 原数组索引计算
//             int srcIdx = y * srcW + x;
//             // 复制RGB565像素（2字节）
//             dst[dstIdx] = src[srcIdx];
//         }
//     }
// }

// /**
//  * @brief 将旋转后图像（160x128）的人脸坐标还原到原图（128x160）
//  * @param rotated_x   旋转后人脸框左上角x坐标
//  * @param rotated_y   旋转后人脸框左上角y坐标
//  * @param rotated_w   旋转后人脸框宽度
//  * @param rotated_h   旋转后人脸框高度
//  * @param original_box 还原后的原图坐标（输出参数）
//  */
// void restore_coordinates(int* original_x1, int* original_y1, int* original_x2, int* original_y2) {
//     // 坐标逆变换（顺时针旋转90度）
// 	int rotated_x1 = *original_x1;
// 	int rotated_y1 = *original_y1;
// 	int rotated_x2 = *original_x2;
// 	int rotated_y2 = *original_y2;

//     *original_x1 = 128 - 1 - rotated_y2;
//     *original_y1 = rotated_x1; // 旋转后图像高度=128

//     // 宽高交换
//     *original_x2 = 128 - 1 - rotated_y1;
//     *original_y2 = rotated_x2;
// }

// void restore_pixel(int* original_x, int* original_y) {
//     // 坐标逆变换（顺时针旋转90度）
// 	int rotated_x = *original_x;
// 	int rotated_y = *original_y;

// 	// 宽高交换
//     *original_x = 128 - 1 - rotated_y;
//     *original_y = rotated_x; // 旋转后图像高度=128
// }

// // ==== 565 -> 888 (160x120) 最终转换，供推理直接使用 ====
// static inline void unpack_rgb565(uint16_t p, uint8_t* r, uint8_t* g, uint8_t* b) {
//     // 注意：硬件帧为RGB565还是BGR565需以实际为准；当前解码与face_detect中的BGR565ToRGB888一致
//     uint8_t blue  = (p & 0xF800) >> 11;
//     uint8_t green = (p & 0x07E0) >> 5;
//     uint8_t red   = (p & 0x001F);
//     *r = (red << 3) | (red >> 2);
//     *g = (green << 2) | (green >> 4);
//     *b = (blue << 3) | (blue >> 2);
// }

// static void convert_565_to_888_160x120(const uint16_t* src160x120, uint8_t* dst888 /*bgr320_buffer1*/) {
//     for (int y = 0; y < 120; ++y) {
//         for (int x = 0; x < 160; ++x) {
//             uint8_t r,g,b;
//             unpack_rgb565(src160x120[y*160 + x], &r, &g, &b);
//             int o = (y*160 + x)*3;
//             dst888[o+0] = r;
//             dst888[o+1] = g;
//             dst888[o+2] = b;
//         }
//     }
// }


// // 任意RGB565缩放（最近邻，定点步进）+ ROI 支持，srcStride 为源整图行步长
// static void resize_bgr565_nn_roi(const uint16_t *src, int srcStride,
//                                  int roiX, int roiY, int roiW, int roiH,
//                                  uint16_t *dst, int dstW, int dstH) {
//     uint32_t stepX = ((uint32_t)roiW << 16) / (uint32_t)dstW;
//     uint32_t stepY = ((uint32_t)roiH << 16) / (uint32_t)dstH;
//     uint32_t sy_fp = 0;
//     for (int y = 0; y < dstH; ++y) {
//         int sy = (int)(sy_fp >> 16);
//         if (sy >= roiH) sy = roiH - 1;
//         const uint16_t* srcRow = src + (roiY + sy) * srcStride + roiX;
//         uint32_t sx_fp = 0;
//         for (int x = 0; x < dstW; ++x) {
//             int sx = (int)(sx_fp >> 16);
//             if (sx >= roiW) sx = roiW - 1;
//             dst[y*dstW + x] = srcRow[sx];
//             sx_fp += stepX;
//         }
//         sy_fp += stepY;
//     }
// }

// // 整倍缩小的真实 binning（均值聚合），对 ROI 做 kx*ky 块平均后写入 dst
// static void binning_downscale_bgr565_roi(const uint16_t *src, int srcStride,
//                                          int roiX, int roiY, int roiW, int roiH,
//                                          uint16_t *dst, int dstW, int dstH) {
//     // 需要整除
//     if (roiW % dstW != 0 || roiH % dstH != 0 || dstW <= 0 || dstH <= 0) {
//         // 回退：直接最近邻
//         resize_bgr565_nn_roi(src, srcStride, roiX, roiY, roiW, roiH, dst, dstW, dstH);
//         return;
//     }
//     int fx = roiW / dstW; // 水平bin尺寸
//     int fy = roiH / dstH; // 垂直bin尺寸
//     int blockSize = fx * fy;
//     for (int dy = 0; dy < dstH; ++dy) {
//         int sy0 = roiY + dy * fy;
//         for (int dx = 0; dx < dstW; ++dx) {
//             int sx0 = roiX + dx * fx;
//             int sumR = 0, sumG = 0, sumB = 0;
//             for (int by = 0; by < fy; ++by) {
//                 const uint16_t* srow = src + (sy0 + by) * srcStride + sx0;
//                 for (int bx = 0; bx < fx; ++bx) {
//                     uint16_t p = srow[bx];
//                     int r5 = (p & 0x001F);
//                     int g6 = (p >> 5) & 0x003F;
//                     int b5 = (p >> 11);
//                     sumR += r5; sumG += g6; sumB += b5;
//                 }
//             }
//             // 四舍五入
//             int r5 = (sumR + (blockSize >> 1)) / blockSize;
//             int g6 = (sumG + (blockSize >> 1)) / blockSize;
//             int b5 = (sumB + (blockSize >> 1)) / blockSize;
//             if (r5 > 31) r5 = 31; if (b5 > 31) b5 = 31; if (g6 > 63) g6 = 63;
//             dst[dy * dstW + dx] = (uint16_t)((b5 << 11) | (g6 << 5) | r5);
//         }
//     }
// }

// // 统一前处理：任意 >=160x120(横) 或 >=120x160(竖) 的RGB565输入 -> 160x120 RGB888 输出
// static void preprocess_to_160x120_rgb(const uint16_t* src, int srcW, int srcH, uint8_t* outRgb888, Transform* tfm)
// {
//     int portrait = (srcW < srcH);
//     tfm->srcW = srcW; tfm->srcH = srcH;
//     tfm->preW = portrait ? 120 : 160;
//     tfm->preH = portrait ? 160 : 120;
//     tfm->rotated = portrait ? 1 : 0;

//     // 计算尽可能大的整数倍下采样比例，并做最小化对称裁剪
//     int kx = srcW / tfm->preW;
//     int ky = srcH / tfm->preH;
//     if (kx < 1) kx = 1; if (ky < 1) ky = 1; // 理论上不会出现<1（根据输入约束），防御性处理
//     int k = (kx < ky) ? kx : ky; // 选最小的整数倍缩放比例
//     int roiW = tfm->preW * k;
//     int roiH = tfm->preH * k;
//     int roiX = (srcW - roiW) / 2; // 居中裁剪，尽量保留全局内容
//     int roiY = (srcH - roiH) / 2;
//     if (roiX < 0) roiX = 0; if (roiY < 0) roiY = 0;

//     tfm->cropOx = roiX; tfm->cropOy = roiY;
//     tfm->cropW = roiW; tfm->cropH = roiH;

//     const uint16_t* scaled565 = NULL;
//     if (k >= 2) {
//         // 优先使用真实 binning（均值聚合）获得更好画质
//         binning_downscale_bgr565_roi(src, srcW, roiX, roiY, roiW, roiH, bgr565_buffer1, tfm->preW, tfm->preH);
//         scaled565 = bgr565_buffer1;
//     } else {
//         // k == 1：仅裁剪，无缩放；复制ROI为紧凑缓冲，保持接口一致
//         resize_bgr565_nn_roi(src, srcW, roiX, roiY, roiW, roiH, bgr565_buffer1, tfm->preW, tfm->preH);
//         scaled565 = bgr565_buffer1;
//     }

//     // 竖屏需要再旋转；横屏则直接转换
//     if (portrait) {
//         // 现在 scaled565 始终在 bgr565_buffer1，旋转输出到 wframe1 或反之均可
//         rotate_ccw90_generic(scaled565, 120, 160, wframe1_buffer);
//         convert_565_to_888_160x120((const uint16_t*)wframe1_buffer, outRgb888);
//     } else {
//         convert_565_to_888_160x120((const uint16_t*)scaled565, outRgb888);
//     }
// }

// // ============ 通用坐标逆变换：从CNN(160x120)坐标还原到原图(srcW x srcH) ============
// static inline int clampi(int v, int lo, int hi) {
//     if (v < lo) return lo; if (v > hi) return hi; return v;
// }

// static inline float clampf(float v, float lo, float hi) {
//     if (v < lo) return lo; if (v > hi) return hi; return v;
// }

// // 将 CNN(160x120) 坐标点映射回原图坐标（浮点版）
// static inline void map_point_cnn_to_original_float(const Transform* tfm,
//                                                    float xc, float yc,
//                                                    float* xo, float* yo) {
//     // 1) CNN -> 预处理域（可能逆旋转）
//     float xq, yq;
//     if (tfm->rotated) {
//         // 逆时针旋转过，需做顺时针逆变换
//         xq = (float)(tfm->preW - 1) - yc;
//         yq = xc;
//     } else {
//         xq = xc; yq = yc;
//     }
//     // 2) 预处理域 -> 裁剪域（缩放）
//     float sx = (float)tfm->cropW / (float)tfm->preW;
//     float sy = (float)tfm->cropH / (float)tfm->preH;
//     float xcrop = xq * sx;
//     float ycrop = yq * sy;
//     // 3) 裁剪域 -> 原图（偏移）
//     *xo = (float)tfm->cropOx + xcrop;
//     *yo = (float)tfm->cropOy + ycrop;
// }

// // 将CNN坐标点(xc,yc)映射回原图坐标(xo,yo)
// static void restore_faces_with_transform(FaceRect* faces, int count, const Transform* tfm) {
//     const int srcW = tfm->srcW, srcH = tfm->srcH;
//     // 其余变换参数直接通过 tfm 在映射函数中使用，无需在此展开
//     for (int i = 0; i < count; ++i) {
//         FaceRect* r = &faces[i];
//         // 1) 映射四角为浮点，再用 floor/ceil 构出包围盒（避免缩水）
//         float fx[4], fy[4];
//         int xcnn[4] = { r->x1, r->x2, r->x1, r->x2 };
//         int ycnn[4] = { r->y1, r->y1, r->y2, r->y2 };
//         for (int k = 0; k < 4; ++k) {
//             float xo, yo;
//             map_point_cnn_to_original_float(tfm, (float)xcnn[k], (float)ycnn[k], &xo, &yo);
//             fx[k] = clampf(xo, 0.0f, (float)(srcW - 1));
//             fy[k] = clampf(yo, 0.0f, (float)(srcH - 1));
//         }
//         float xminf = fx[0], xmaxf = fx[0];
//         float yminf = fy[0], ymaxf = fy[0];
//         for (int k = 1; k < 4; ++k) {
//             if (fx[k] < xminf) xminf = fx[k]; if (fx[k] > xmaxf) xmaxf = fx[k];
//             if (fy[k] < yminf) yminf = fy[k]; if (fy[k] > ymaxf) ymaxf = fy[k];
//         }
//         int xmin = clampi((int)floorf(xminf), 0, srcW - 1);
//         int xmax = clampi((int)ceilf(xmaxf), 0, srcW - 1);
//         int ymin = clampi((int)floorf(yminf), 0, srcH - 1);
//         int ymax = clampi((int)ceilf(ymaxf), 0, srcH - 1);
//         if (xmax <= xmin) xmax = clampi(xmin + 1, 1, srcW - 1);
//         if (ymax <= ymin) ymax = clampi(ymin + 1, 1, srcH - 1);
//         r->x1 = xmin; r->y1 = ymin; r->x2 = xmax; r->y2 = ymax;

//         // 2) 同步还原landmarks（5点），按浮点坐标回贴
//         for (int p = 0; p < 5; ++p) {
//             float xc = r->lm[2*p];
//             float yc = r->lm[2*p + 1];
//             float xo, yo;
//             map_point_cnn_to_original_float(tfm, xc, yc, &xo, &yo);
//             r->lm[2*p]     = clampf(xo, 0.0f, (float)(srcW - 1));
//             r->lm[2*p + 1] = clampf(yo, 0.0f, (float)(srcH - 1));
//         }
//     }
// }

// // ==================== 业务流程拆分：模块化辅助函数 ====================

// // 根据mailbox握手初始化地址、缓冲指针与分辨率
// /* CM4<->DSP 握手协议：
//  * CM4 发送 TOKEN_BOOT_REQ 提示 DSP 启动初始化；DSP 完成后回写 TOKEN_DSP_READY。
//  */
// #define TOKEN_BOOT_REQ   0x5A5A5A5AU
// #define TOKEN_DSP_READY  0xA5A5A5A5U
// static void mailbox_setup_if_needed(PipelineContext* ctx) {
//     if (mailbox_is_empty() == false) {
//         uint32_t recv_data = mailbox_read_data();
// //        DSP_LOG("mailbox_recv = 0x%x\n", recv_data);
//         if (recv_data == TOKEN_BOOT_REQ) {
//             wframe0_addr = REG32(DSP_MM_BASE + 0x30);
//             wframe1_addr = REG32(DSP_MM_BASE + 0x34);
//             rframe0_addr = REG32(DSP_MM_BASE + 0x40);
//             rframe1_addr = REG32(DSP_MM_BASE + 0x44);
//             alpha0_addr  = REG32(DSP_MM_BASE + 0x48);
//             alpha1_addr  = REG32(DSP_MM_BASE + 0x4C);
// //            DSP_LOG("wframe0_addr = 0x%p, rframe0_addr = 0x%p, alpha0_addr = 0x%p\n", (void*)wframe0_addr, (void*)rframe0_addr, (void*)alpha0_addr);
// //            DSP_LOG("wframe1_addr = 0x%p, rframe1_addr = 0x%p, alpha1_addr = 0x%p\n", (void*)wframe1_addr, (void*)rframe1_addr, (void*)alpha1_addr);

//             // 写全局地址与本地上下文
//             wframe0_buffer = (uint16_t *)wframe0_addr;
//             wframe1_buffer = (uint16_t *)wframe1_addr;
//             rframe0_buffer = (uint16_t *)rframe0_addr;
//             rframe1_buffer = (uint16_t *)rframe1_addr;
//             alpha0_buffer  = (uint8_t  *)alpha0_addr;
//             alpha1_buffer  = (uint8_t  *)alpha1_addr;

//             display_width  = REG32(DSP_MM_BASE + 0x20) & 0x7FF;
//             display_height = (REG32(DSP_MM_BASE + 0x20) & 0x3FF0000) >> 16;
//             snapshot_width  = REG32(DSP_MM_BASE + 0x28) & 0x7FF;
//             snapshot_height = (REG32(DSP_MM_BASE + 0x28) & 0x3FF0000) >> 16;

//             // 同步到上下文（避免后续传参再次依赖全局）
//             ctx->wframe0_buffer = wframe0_buffer;
//             ctx->wframe1_buffer = wframe1_buffer;
//             ctx->rframe0_buffer = rframe0_buffer;
//             ctx->rframe1_buffer = rframe1_buffer;
//             ctx->alpha0_buffer  = alpha0_buffer;
//             ctx->alpha1_buffer  = alpha1_buffer;
//             ctx->display_width  = display_width;
//             ctx->display_height = display_height;
//             ctx->snapshot_width  = snapshot_width;
//             ctx->snapshot_height = snapshot_height;

// //            DSP_LOG("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n",
// //                       display_width, display_height, snapshot_width, snapshot_height);

//             // 清屏为白色，避免残影
//             size_t pix_count = (size_t)ctx->snapshot_width * (size_t)ctx->snapshot_height;
//             for (size_t i = 0; i < pix_count; ++i) {
//                 ctx->wframe0_buffer[i] = 0xFFFF;
//                 ctx->wframe1_buffer[i] = 0xFFFF;
//             }
// //            DSP_LOG("init mm memory\n");

// //            DSP_LOG("dsp_mm self-test start (boot handshake)\n");
//             debug_test_dsp_mm();
// //            DSP_LOG("dsp_mm self-test finished, sending TOKEN_DSP_READY=0x%08X to CM4\n", TOKEN_DSP_READY);

//            REG32(DSP_MM_BASE + 0x70) = 1; // 由CM4接收READY后执行
//            REG32(DSP_MM_BASE + 0x1E0) = 1; // 由CM4接收READY后执行
// //            DSP_LOG("TOKEN_DSP_READY sent. times_count=%lu cycles=%lu (boot phase)\n", (unsigned long)times_count, (unsigned long)times_cycles);
//             // mailbox_write_data(TOKEN_DSP_READY); /* 改为通知CM4使能MM */
//         }
//     }
// }

// // 处理一帧：前处理->推理->坐标还原->通知
// static void process_wframe1_if_flagged(PipelineContext* ctx) {
//     if (wframe1_flag) {
//         // DSP_LOG("wframe1 read start\n");
//         wframe1_flag = 0;

//         // 通用化：一次调用完成裁剪/旋转/缩放/转换，并记录变换参数
//         Transform tfm;
//         preprocess_to_160x120_rgb(ctx->wframe1_buffer,
//                                   ctx->snapshot_width,
//                                   ctx->snapshot_height,
//                                   bgr320_buffer1,
//                                   &tfm);

//         int face_count = face_detect_rgb(bgr320_buffer1);
//         if (face_count) {
//             // 使用通用逆变换还原所有检测框到原图坐标
//             restore_faces_with_transform(faces_result, face_count, &tfm);
//             FaceRect *face_get = &faces_result[0];
//             DSP_LOG("restored face[0]: %d,%d,%d,%d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
//             mailbox_write_data((uint32_t)face_get);
//         }

//         // 可选：处理wframe0标志
//         if (wframe0_flag) {
//             // DSP_LOG("wframe0 read start\n");
//             wframe0_flag = 0;
//             REG32(DSP_MM_BASE + 0x38) = 1;
//         }

//         REG32(DSP_MM_BASE + 0x3C) = 1;
//     }
// }

int main(void)
{
    /* Test start */
    uint32_t dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;
    dd |= 0x1 << 16;
    _out(_cpm, dd, 0x924);
    dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;

//    DSP_LOG("[S300 DSP][DisplayDemo] Booting..!\n");
//    DSP_LOG("This program was compiled on %s at %s\n", __DATE__, __TIME__);

    // rt_kprintf("Hello, world!\n");
    // rt_kprintf("Integer: %d\n", 123);
    // rt_kprintf("Hex: %x\n", 0xABCD);
    // rt_kprintf("Float: %s\n", float_to_string_simple(3.012345));
    // rt_kprintf("Float: %s\n", float_to_string_simple(0.123456));
    // rt_kprintf("String: %s\n", "Embedded");
    extern int face_recognition();
    face_recognition();
    while (1);
   
//     // 运行期上下文
//     PipelineContext ctx = {0};

//     while (1)
//     {
//         // 心跳打印与握手检测
//         if (times_cycles % 10000000 == 0) {
//             times_count++;
//             times_cycles = 0;
// //            DSP_LOG("times_count = %ld\n", times_count);
//             mailbox_setup_if_needed(&ctx);
//         }

//         // 帧处理
//         process_wframe1_if_flagged(&ctx);

//         times_cycles++;
//     }
    return 0;
}
