/*
 * dsp_mm.h
 *
 *  Created on: 2024年3月22日
 *      Author: xinhao
 */

#ifndef DSP_MM_H_
#define DSP_MM_H_

#include "kernel.h"

//#define MM_AXI_DMA              (DSP_DMA)
//#define MM_AXI_DMA_CHANNEL      (AXI_DMA_CH1)
//#define MM_AXI_DMA_TRANS_MAX    ((AXI_DMA_BLOCK_TS_MAX_VAL + 1) * 16)

#define PIC_WIDTH       160
#define PIC_HEIGHT      120

// 定义颜色类型
typedef uint16_t color565;

extern volatile uint8_t wframe0_flag;
extern volatile uint8_t wframe1_flag;
extern volatile uint8_t rframe0_ready;
extern volatile uint8_t rframe1_ready;
extern volatile uint8_t rframe0_flag;
extern volatile uint8_t rframe1_flag;

int debug_test_dsp_mm(void);
void draw_green_box(uint16_t *img_data, int width, int height, int x1, int y1, int x2, int y2);
void draw_alpha_box(uint8_t *alphaImage, int width, int height, int x1, int y1, int x2, int y2);
void draw_red_box(uint16_t *img_data, uint8_t *alphaImage, int width, int height, int x1, int y1, int x2, int y2);

#endif /* DSP_MM_H_ */
