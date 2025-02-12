
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
#include "axi_dma.h"
#include "face_detect.h"

#include "custom_printf.h"
#include "dsp_mailbox.h"

#define DISP_IMAGE_WIDTH            (320)
#define DISP_IMAGE_HEIGHT           (240)

extern uint8_t bgr320_buffer1[160 * 120 * 3];
uint16_t *wframe0_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 3));
uint16_t *wframe1_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 3));
uint16_t *rframe0_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 5));
uint16_t *rframe1_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 5));
uint8_t *alpha0_buffer = (uint8_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 1));
uint8_t *alpha1_buffer = (uint8_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 1));

uint32_t times_count  = 0;
uint32_t face_detect_count  __attribute__((used, section(".sram1_data"), aligned(16))) = 0;

typedef uint16_t PIXEL565; // BGR565像素类型，2字节

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


#define TEST_SIZE 100 * 1024 * 1024  // 测试总数据量 (1MB)
#define ALIGNMENT 16           // 地址对齐要求
#define DMA_BASE 0x10000000ULL // 假设 DMA 基地址
#define SYSTEM_CLOCK_FREQ 300000000.0f // 系统时钟频率 (400 MHz)
#define TIMER_DIVISOR 16       // 分频值

// 模拟内存区域
uint8_t *dtcm = (uint8_t *)0x20000; // DTCM
uint8_t *sram = (uint8_t *)0x44060000; // SRAM
uint16_t *psram = (uint16_t *)0x80000000; // PSRAM
uint8_t *dtcm_dst = (uint8_t *)0x30000; // DTCM
uint8_t *sram_dst = (uint8_t *)0x44070000; // SRAM
uint16_t *psram_dst = (uint16_t *)0x80001000; // PSRAM

// 计算性能指标
void calculate_performance(size_t total_size, uint32_t start, uint32_t end) {
	// 恢复到系统时钟的原始周期
	uint64_t cycles = (end - start) * TIMER_DIVISOR;
	float total_seconds = (float)cycles / SYSTEM_CLOCK_FREQ; // 总时间 (秒)
	float cycles_per_MB = (float)cycles / (total_size / (1024.0f * 1024.0f)); // 每MB所需的系统时钟周期
	float seconds_per_MB = cycles_per_MB / SYSTEM_CLOCK_FREQ; // 每MB所需的时间 (秒)
	float mb_per_second = 1.0f / seconds_per_MB; // 每秒传输的 MB 数据量

	// 打印结果
	rt_kprintf("总 cycles: %lu\n", cycles);
	rt_kprintf("总时间: %s 秒\n", float_to_string_simple(total_seconds));
	rt_kprintf("每MB 数据需要 cycles: %s\n", float_to_string_simple(cycles_per_MB));
	rt_kprintf("每MB 数据需要时间: %s 秒\n", float_to_string_simple(seconds_per_MB));
	rt_kprintf("传输速度: %s MB/s\n", float_to_string_simple(mb_per_second));
}

// 测试函数
void test_dma(uint64_t dmax, void *src, void *dst, size_t total_size, int src_bit_width, int dst_bit_width) {
    size_t max_transfer_size = 2048 * (src_bit_width / 8);
    size_t transferred = 0;
    uint32_t start, end;

    // 初始化 DMA
    axi_dma_init(DSP_DMA, AXI_DMA_CH1, max_transfer_size, src_bit_width / 8, dst_bit_width / 8);

    // 测试写性能
    rt_kprintf("性能测试 (src_bit_width: %d-bit, dst_bit_width: %d-bit)\n", src_bit_width, dst_bit_width);
    start = get_cycles_start();
    while (transferred < total_size) {
        size_t size = (total_size - transferred) > max_transfer_size ? max_transfer_size : (total_size - transferred);
        axi_dma_start(DSP_DMA, AXI_DMA_CH1, (uint64_t)src, (uint64_t)dst);
        while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN << (AXI_DMA_CH1 - 1))); // 等待通道完成
        transferred += size;
    }
    end = get_cycles_end();
    calculate_performance(total_size, start, end);

//    // 测试读性能
//    rt_kprintf("测试读性能 (位宽: %d-bit)\n", bit_width);
//    transferred = 0;
//    start = get_cycles_start();
//    while (transferred < total_size) {
//        size_t size = (total_size - transferred) > max_transfer_size ? max_transfer_size : (total_size - transferred);
//        axi_dma_start(dmax, 1, (uint64_t)dst, (uint64_t)src);
//        while (AXI_DMA_CHEN(dmax) & (0x01ULL << 0)); // 等待通道完成
//        transferred += size;
//    }
//    end = get_cycles_end();
//    calculate_performance(total_size, start, end);
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
//    for (int i = 0; i < 32 * 1024; i++)
//    {
//    	dtcm[i] = i;
//    }
//    axi_dma_enable(DSP_DMA);
//    rt_kprintf("TEST_SIZE %dMB\n", TEST_SIZE / 1024 / 1024);
//    // 测试不同内存区域之间的搬运
//    rt_kprintf("\n\n测试 DTCM -> DTCM\n");
//	test_dma(DMA_BASE, dtcm, dtcm_dst, TEST_SIZE, 128, 128);
//
//	rt_kprintf("\n\n测试 DTCM -> SRAM\n");
//	test_dma(DMA_BASE, dtcm, sram, TEST_SIZE, 128, 128);
//
//	rt_kprintf("\n\n测试 DTCM -> PSRAM\n");
//	test_dma(DMA_BASE, dtcm, psram, TEST_SIZE, 128, 32);
//
//	rt_kprintf("\n\n测试 SRAM -> SRAM\n");
//	test_dma(DMA_BASE, sram, sram_dst, TEST_SIZE, 128, 128);
//
//	rt_kprintf("\n\n测试 SRAM -> DTCM\n");
//	test_dma(DMA_BASE, sram, dtcm_dst, TEST_SIZE, 128, 128);
//
//	rt_kprintf("\n\n测试 SRAM -> PSRAM\n");
//	test_dma(DMA_BASE, sram, psram_dst, TEST_SIZE, 128, 32);
//
//	rt_kprintf("\n\n测试 PSRAM -> PSRAM\n");
//	test_dma(DMA_BASE, psram, psram_dst, TEST_SIZE, 32, 32);
//
//	rt_kprintf("\n\n测试 PSRAM -> DTCM\n");
//	test_dma(DMA_BASE, psram, dtcm_dst, TEST_SIZE, 32, 128);
//
//	rt_kprintf("\n\n测试 PSRAM -> SRAM\n");
//	test_dma(DMA_BASE, psram, sram_dst, TEST_SIZE, 32, 128);
//
//	while(1);

//    color565 *frame_start = (color565 *)0x44040000;
//	uint8_t *frame_alpha_start = (uint8_t *)0x44068000;
//				rt_kprintf("bgr565Image = %p, frame_start = 0x%p, frame_alpha_start = 0x%p \n", frame_start, frame_alpha_start);
////				rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);
//	for (size_t i = 0; i < (120 * 160); i++)
//	{
//		/* code */
//		REG8(frame_alpha_start++) = 0x00;
////		rt_kprintf("%x ", REG8(frame_alpha_start));
//	}
//	rt_kprintf("Integer: %d\n", 123);
//	draw_green_box(frame_start, alpha0_buffer, 160, 120, 10, 10, 50, 50);
//
//	for (size_t i = 0; i < (120 * 160); i++)
//	{
//		/* code */
////		REG8(frame_alpha_start++) = 0x00;
//		if (REG8(frame_alpha_start++))
//			rt_kprintf("i = %d, %x ", i, REG8(frame_alpha_start));
//	}
//	frame_start = (color565 *)0x4405E000;
//	frame_alpha_start = (uint8_t *)0x44070000;
//	rt_kprintf("bgr565Image = %p, frame_start = 0x%p, frame_alpha_start = 0x%p \n", frame_start, frame_alpha_start);
////	rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);
//	for (size_t i = 0; i < (120 * 160); i++)
//	{
//		/* code */
//		REG8(frame_alpha_start++) = 0x00;
//	}
//	draw_red_box(frame_start, alpha1_buffer, 160, 120, 50, 50, 100, 100);
//	for (size_t i = 0; i < (120 * 160); i++)
//		{
//			/* code */
//	//		REG8(frame_alpha_start++) = 0x00;
//			if (REG8(frame_alpha_start++))
//				rt_kprintf("i = %d, %x ", i, REG8(frame_alpha_start));
//		}
//    debug_start();
//    debug_test_kernel();
//    mailbox_isr_enable();
//    rt_kprintf("mailbox_isr_enable\n");
    debug_test_dsp_mm();
//    face_detect(wframe1_buffer);

//    REG32(DSP_MM_BASE + 0x1E0) = 1;
    while (1)
    {
    	/* code */

    	if (times_count % 10000000 == 0)
    	{
    		rt_kprintf("times_count = %d\n", times_count);
    		if (times_count == 10000000)
    		{
    			REG32(DSP_MM_BASE + 0x70) = 1;
    			REG32(DSP_MM_BASE + 0x1E0) = 1;
    		}
//    		FaceRect *face_get = face_detect(NULL);
//			if (face_get)
//			{
//				rt_kprintf("wframe0 draw_green %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
//				if (face_get->x1 < face_get->x2)
//				{
//					draw_green_box(rframe0_buffer, alpha0_buffer, snapshot_width, snapshot_height, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
//				}
//				else
//				{
//					draw_green_box(rframe1_buffer, alpha1_buffer, snapshot_width, snapshot_height, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
//				}
//			}
    	}
    	times_count++;
    	if(mailbox_recv)
		{
			mailbox_recv = 0;
			uint32_t received_data = mailbox_read_data();
			rt_kprintf("IIS_RIT_FLAG Recv: 0x%x \r\n", received_data);
			// Read the data from the mailbox
//			uint32_t received_data = mailbox_read();

			// Validate the received task ID to prevent accidental triggering
			uint32_t task_id = received_data & MAILBOX_TASK_ID_MASK;
			switch (task_id) {
				case MAILBOX_TASK_ID_1:
					// Handle Task 1
					rt_kprintf("mm reset msg from cm4\r\n");
					wframe0_flag = 0;
					wframe1_flag = 0;
					rframe0_ready = 1;
					rframe1_ready = 1;
					rframe0_flag = 0;
					rframe1_flag = 0;
					break;
				case MAILBOX_TASK_ID_2:
					// Handle Task 2
//					handle_task_2(received_data & 0xFFFF);
//					npu_test();
					break;
				case MAILBOX_TASK_ID_3:
					// Handle Task 3
//					handle_task_3(received_data & 0xFFFF);
//					face_detect((uint16_t *)0x80300000);
					break;
				default:
					// Unknown task ID, handle appropriately (e.g., log an error)
//					handle_unknown_task(task_id);
					rt_kprintf("unknown task id %d\r\n", task_id & 0xffff);
					break;
			}
		}


		if (wframe1_flag)
		{
			wframe1_flag = 0;
//			rt_kprintf("wframe1 read start\n");

//			wframe1_addr = REG32(DSP_MM_BASE + 0x34);
//			rframe1_addr = REG32(DSP_MM_BASE + 0x44);
//			alpha1_addr = REG32(DSP_MM_BASE + 0x4C);
//			display_width = REG32(DSP_MM_BASE + 0x20) & 0x7FF;
//			display_height = (REG32(DSP_MM_BASE + 0x20) & 0x3FF0000) >> 16;
//			snapshot_width = REG32(DSP_MM_BASE + 0x28) & 0x7FF;
//			snapshot_height = (REG32(DSP_MM_BASE + 0x28) & 0x3FF0000) >> 16;
//			rt_kprintf("wframe1_addr = 0x%x, rframe1_addr = 0x%x, alpha1_addr = 0x%x\n", wframe1_addr, rframe1_addr, alpha1_addr);
//		//				rt_kprintf("wframe1 read finish\n");
//		//			debug_new_case();
//			uint16_t *bgr565Image = (uint16_t *)wframe1_addr;
////
//			color565 *frame_start = (color565 *)0x4405E000;
//			uint8_t *frame_alpha_start = (uint8_t *)0x44070000;
//				rt_kprintf("bgr565Image = %p, frame_start = 0x%p, frame_alpha_start = 0x%p \n", bgr565Image, frame_start, frame_alpha_start);
//			rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);

////				cropAndConvertImage(bgr565Image, bgr320_buffer1, 160, 128, 120);
//			rt_kprintf("wframe1_buffer hexdump start:\n");
//			for (int i = 0; i < (320 * 240); i++)
//			{
//				rt_kprintf("%d, ", wframe1_buffer[i]);
//			}
//			rt_kprintf("\nwframe1_buffer hexdump end:\n");
			in_place_downscale_bgr565(wframe1_buffer, 320, 240, 160, 120);
//			rt_kprintf("wframe1_buffer_downscale hexdump start:\n");
//			for (int i = 0; i < (320 * 240); i++)
//			{
//				rt_kprintf("%d, ", wframe1_buffer[i]);
//			}
//			rt_kprintf("\nwframe1_buffer_downscale hexdump end:\n");
			FaceRect *face_get = face_detect(wframe1_buffer);
			uint64_t *alpha1_buffer_addr = (uint64_t *)alpha1_buffer;
			for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT / 8); i++)
			{
				/* code */
				alpha1_buffer_addr[i] = 0x00;
			}
			if (face_get)
			{
				face_get->x1 *= 2;
				face_get->y1 *= 2;
				face_get->x2 *= 2;
				face_get->y2 *= 2;
//				rt_kprintf("wframe1 draw_red %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				if (face_get->x1 < face_get->x2)
				{
					draw_green_box(rframe1_buffer, alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				}
				else
				{
					draw_green_box(rframe1_buffer, alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
				}
			}
			if (wframe0_flag)
			{
				/* code */
//				rt_kprintf("wframe0 read start\n");
				wframe0_flag = 0;
//				wframe0_addr = REG32(DSP_MM_BASE + 0x30);
	//			rframe1_addr = REG32(DSP_MM_BASE + 0x44);
	//			alpha1_addr = REG32(DSP_MM_BASE + 0x4C);
	//			display_width = REG32(DSP_MM_BASE + 0x20) & 0x7FF;
	//			display_height = (REG32(DSP_MM_BASE + 0x20) & 0x3FF0000) >> 16;
	//			snapshot_width = REG32(DSP_MM_BASE + 0x28) & 0x7FF;
	//			snapshot_height = (REG32(DSP_MM_BASE + 0x28) & 0x3FF0000) >> 16;
	//				rt_kprintf("wframe1_addr = 0x%x, rframe1_addr = 0x%x, alpha1_addr = 0x%x\n", wframe1_addr, rframe1_addr, alpha1_addr);
	//		//				rt_kprintf("wframe1 read finish\n");
	//		//			debug_new_case();
	//			uint16_t *bgr565Image = (uint16_t *)wframe0_buffer;
	//
	//			color565 *frame_start = (color565 *)0x4405E000;
	//			uint8_t *frame_alpha_start = (uint8_t *)0x44070000;
	//				rt_kprintf("bgr565Image = %p, frame_start = 0x%p, frame_alpha_start = 0x%p \n", bgr565Image, frame_start, frame_alpha_start);
	//			rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);

	////				cropAndConvertImage(bgr565Image, bgr320_buffer1, 160, 128, 120);

	//			FaceRect *face_get = face_detect(wframe0_buffer);
	//			uint64_t *alpha0_buffer_addr = (uint64_t *)alpha0_buffer;
	//			for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT / 8); i++)
	//			{
	//				/* code */
	//				alpha0_buffer_addr[i] = 0x00;
	//			}
	//			if (face_get)
	//			{
	////				face_detect_count++;
	//				rt_kprintf("wframe0 draw_green %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
	//				for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT); i++)
	//				{
	//					/* code */
	//					alpha0_buffer[i] = 0x00;
	//				}
	//				if (face_get->x1 < face_get->x2)
	//				{
	//					draw_green_box(rframe0_buffer, alpha0_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
	//				}
	//				else
	//				{
	//					draw_green_box(rframe0_buffer, alpha0_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
	//				}
	//			}
				if (rframe0_ready)
				{
					REG32(DSP_MM_BASE + 0x50) = 1;
				}

				REG32(DSP_MM_BASE + 0x38) = 1;
			}
			if (rframe1_ready)
			{
				REG32(DSP_MM_BASE + 0x54) = 1;
			}

			REG32(DSP_MM_BASE + 0x3C) = 1;
		}
    }
    return 0;
}
