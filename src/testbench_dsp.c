
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

#include "reg.h"
#include "kernel.h"
#include "dsp_mm.h"
#include "vec-c.h"
#include "face_detect.h"
#include "dsp_mailbox.h"

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
uint32_t face_detect_count  __attribute__((used, section(".sram1_data"), aligned(16))) = 0;

int32_t face_pos = 80;
int32_t face_pos_last = 80;

typedef uint16_t PIXEL565; // BGR565像素类型，2字节

PIXEL565 bgr565_buffer1[160 * 128] __attribute__((used, section(".face_data"), aligned(16))) ;

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

int main(void)
{

    /* Test start */
    uint32_t dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;
    dd |= 0x1 << 16;
    _out(_cpm, dd, 0x924);
    dd = _in(_cpm, 0x924);
    REG32(0x44040000) = dd;

    rt_kprintf("Hello, world!\n");
    rt_kprintf("Integer: %d\n", 123);
    rt_kprintf("Hex: %x\n", 0xABCD);
    rt_kprintf("Float: %s\n", float_to_string_simple(3.012345));
    rt_kprintf("Float: %s\n", float_to_string_simple(0.123456));
    rt_kprintf("String: %s\n", "Embedded");

    rt_kprintf("This program was compiled on %s at %s\n", __DATE__, __TIME__);

//    face_detect(wframe1_buffer);

//    REG32(DSP_MM_BASE + 0x1E0) = 1;
    while (1)
    {
    	/* code */

    	if (times_cycles % 10000000 == 0)
    	{
    		times_count++;
    		times_cycles = 0;
    		rt_kprintf("times_count = %ld\n", times_count);
    		if (mailbox_is_empty() == false)
    		{
    			uint32_t recv_data = mailbox_read_data();
    			rt_kprintf("mailbox_recv = 0x%x\n", recv_data);
    			if (recv_data == 0x5A5A5A5A)
    			{
    				wframe0_addr = REG32(DSP_MM_BASE + 0x30);
					wframe1_addr = REG32(DSP_MM_BASE + 0x34);
					rframe0_addr = REG32(DSP_MM_BASE + 0x40);
					rframe1_addr = REG32(DSP_MM_BASE + 0x44);
					alpha0_addr = REG32(DSP_MM_BASE + 0x48);
					alpha1_addr = REG32(DSP_MM_BASE + 0x4C);
					rt_kprintf("wframe0_addr = 0x%p, rframe0_addr = 0x%p, alpha0_addr = 0x%p\n", wframe0_addr, rframe0_addr, alpha0_addr);
					rt_kprintf("wframe1_addr = 0x%p, rframe1_addr = 0x%p, alpha1_addr = 0x%p\n", wframe1_addr, rframe1_addr, alpha1_addr);

					wframe0_buffer = (uint16_t *)wframe0_addr;
					wframe1_buffer = (uint16_t *)wframe1_addr;
					rframe0_buffer = (uint16_t *)rframe0_addr;
					rframe1_buffer = (uint16_t *)rframe1_addr;
					alpha0_buffer = (uint8_t *)alpha0_addr;
					alpha1_buffer = (uint8_t *)alpha1_addr;

					display_width = REG32(DSP_MM_BASE + 0x20) & 0x7FF;
					display_height = (REG32(DSP_MM_BASE + 0x20) & 0x3FF0000) >> 16;
					snapshot_width = REG32(DSP_MM_BASE + 0x28) & 0x7FF;
					snapshot_height = (REG32(DSP_MM_BASE + 0x28) & 0x3FF0000) >> 16;

					rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);

//					for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT); i++)
//					{
//						/* code */
//						alpha0_buffer[i] = 0x00;
//						alpha1_buffer[i] = 0x00;
//					}
					for (size_t i = 0; i < (SNAP_IMAGE_WIDTH * SNAP_IMAGE_HEIGHT); i++)
					{
						/* code */
						wframe0_buffer[i] = 0xFFFF;
						wframe1_buffer[i] = 0xFFFF;
//						rframe0_buffer[i] = 0xFFFF;
//						rframe1_buffer[i] = 0xFFFF;
					}
					rt_kprintf("init mm memory\n");

					debug_test_dsp_mm();
    				REG32(DSP_MM_BASE + 0x70) = 1;
					REG32(DSP_MM_BASE + 0x1E0) = 1;
					face_pos_last = face_pos = 80;
					mailbox_write_data(face_pos);

    			}
    		}
//    		else
//    		{
//    			rt_kprintf("mailbox_is_empty\n");
//    		}
    	}
    	times_cycles++;
    	if (wframe0_flag)
		{
			/* code */
			rt_kprintf("wframe0 read start\n");
			wframe0_flag = 0;
			int face_count = 0;
			if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
			{
				rotate_ccw90(wframe0_buffer, bgr565_buffer1);
				face_count = face_detect(bgr565_buffer1);
			}
			else
			{
				face_count = face_detect(wframe0_buffer);
			}

//			uint64_t *alpha0_buffer_addr = (uint64_t *)alpha0_buffer;
//			for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT / 8); i++)
//			{
//				/* code */
//				alpha0_buffer_addr[i] = 0x00;
//			}
			face_pos = 80;
			if (face_count)
			{
				FaceRect *face_get = &faces_result[0];

				if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
				{
					restore_coordinates(&face_get->x1, &face_get->y1, &face_get->x2, &face_get->y2);
					rt_kprintf("restore_coordinates %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				}
				face_pos = (face_get->y1 + face_get->y2) / 2;
			}
			if ((abs(face_pos - face_pos_last) >= 16) || ((face_pos == 80) && (face_pos_last != 80)))
			{
				rt_kprintf("pos = %d, pos_last = %d\n", face_pos, face_pos_last);
				mailbox_write_data(face_pos);
				face_pos_last = face_pos;
			}
//			for (int i = 0; i < face_count; i++)
//			{
//				FaceRect *face_get = &faces_result[i];
//
//				if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
//				{
//					restore_coordinates(&face_get->x1, &face_get->y1, &face_get->x2, &face_get->y2);
//				}
//				face_pos = (face_get->y1 + face_get->y2) / 2;
//				if (abs(face_pos - face_pos_last) >= 16)
//				{
//					rt_kprintf("x1 = %d, y1 = %d, x2 = %d, y2 = %d, pos = %d, pos_last = %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2, face_pos, face_pos_last);
//					mailbox_write_data(face_pos);
//					face_pos_last = face_pos;
//				}
////				clamp_face_rect(face_get);
//
////				face_get->x1 *= 2;
////				face_get->y1 *= 2;
////				face_get->x2 *= 2;
////				face_get->y2 *= 2;
////				rt_kprintf("wframe0 draw_green_box %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////				if (face_get->x1 < face_get->x2)
////				{
////					draw_green_box(rframe0_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////					draw_alpha_box(alpha0_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////				}
////				else
////				{
////					draw_green_box(rframe0_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
////					draw_alpha_box(alpha0_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
////				}
////				for (int p = 0; p < 5; p++)
////				{
////					int x = (int)face_get->lm[2 * p];
////					int y = (int)face_get->lm[2 * p + 1];
////					if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
////					{
//////						rt_kprintf("restore_pixel %d, %d\n", x, y);
////						restore_pixel(&x, &y);
////					}
////
////					draw_green_3x3(rframe0_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, x, y);
////					draw_alpha_3x3(alpha0_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, x, y);
////				}
//			}
//			if (rframe0_ready)
//			{
//				REG32(DSP_MM_BASE + 0x50) = 1;
//			}

			REG32(DSP_MM_BASE + 0x38) = 1;
		}
		if (wframe1_flag)
		{
			rt_kprintf("wframe1 read start\n");
			wframe1_flag = 0;

			int face_count = 0;
			if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
			{
				rotate_ccw90(wframe1_buffer, bgr565_buffer1);
				face_count = face_detect(bgr565_buffer1);
			}
			else
			{
				face_count = face_detect(wframe1_buffer);
			}

//			uint64_t *alpha1_buffer_addr = (uint64_t *)alpha1_buffer;
//			for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT / 8); i++)
//			{
//				/* code */
//				alpha1_buffer_addr[i] = 0x00;
//			}
			face_pos = 80;
			if (face_count)
			{
				FaceRect *face_get = &faces_result[0];

				if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
				{
					restore_coordinates(&face_get->x1, &face_get->y1, &face_get->x2, &face_get->y2);
					rt_kprintf("restore_coordinates %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				}
				face_pos = (face_get->y1 + face_get->y2) / 2;
			}
			if ((abs(face_pos - face_pos_last) >= 16) || ((face_pos == 80) && (face_pos_last != 80)))
			{
				rt_kprintf("pos = %d, pos_last = %d\n", face_pos, face_pos_last);
				mailbox_write_data(face_pos);
				face_pos_last = face_pos;
			}
//			for (int i = 0; i < face_count; i++)
//			{
//				FaceRect *face_get = &faces_result[i];
//
//				if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
//				{
//					restore_coordinates(&face_get->x1, &face_get->y1, &face_get->x2, &face_get->y2);
////					rt_kprintf("restore_coordinates %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
//				}
//				face_pos = (face_get->y1 + face_get->y2) / 2;
//				if (abs(face_pos - face_pos_last) >= 16)
//				{
//					rt_kprintf("x1 = %d, y1 = %d, x2 = %d, y2 = %d, pos = %d, pos_last = %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2, face_pos, face_pos_last);
//					mailbox_write_data(face_pos);
//					face_pos_last = face_pos;
//				}
////				clamp_face_rect(face_get);
////				face_get->x1 *= 2;
////				face_get->y1 *= 2;
////				face_get->x2 *= 2;
////				face_get->y2 *= 2;
////				rt_kprintf("wframe1 draw_red %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////				if (face_get->x1 < face_get->x2)
////				{
////					draw_green_box(rframe1_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////					draw_alpha_box(alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
////				}
////				else
////				{
////					draw_green_box(rframe1_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
////					draw_alpha_box(alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
////				}
////				for (int p = 0; p < 5; p++)
////				{
////					int x = (int)face_get->lm[2 * p];
////					int y = (int)face_get->lm[2 * p + 1];
////					if (SNAP_IMAGE_WIDTH < SNAP_IMAGE_HEIGHT)
////					{
//////						rt_kprintf("restore_pixel %d, %d\n", x, y);
////						restore_pixel(&x, &y);
////					}
////
////					draw_green_3x3(rframe1_buffer, SNAP_IMAGE_WIDTH, SNAP_IMAGE_HEIGHT, x, y);
////					draw_alpha_3x3(alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, x, y);
////				}
//			}
//			if (rframe1_ready)
//			{
//				REG32(DSP_MM_BASE + 0x54) = 1;
//			}

			REG32(DSP_MM_BASE + 0x3C) = 1;
		}
    }
    return 0;
}
