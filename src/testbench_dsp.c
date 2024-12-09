
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

#include "custom_printf.h"
#include "dsp_mailbox.h"

#define DISP_IMAGE_WIDTH            (160)
#define DISP_IMAGE_HEIGHT           (128)

extern uint8_t bgr320_buffer1[160 * 120 * 3];
uint16_t *wframe0_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 8));
uint16_t *wframe1_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 8));
uint16_t *rframe0_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 4));
uint16_t *rframe1_buffer = (uint16_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 4));
uint8_t *alpha0_buffer = (uint8_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 2));
uint8_t *alpha1_buffer = (uint8_t *)(0x44080000 - (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT * 2));

uint32_t times_count  = 0;
uint32_t face_detect_count  __attribute__((used, section(".sram1_data"), aligned(16))) = 0;

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
    mailbox_isr_enable();
    rt_kprintf("mailbox_isr_enable\n");
    debug_test_dsp_mm();

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

		if (wframe0_flag)
		{
			/* code */
//			rt_kprintf("wframe0 read start\n");
//			wframe0_flag = 0;
//			wframe0_addr = REG32(DSP_MM_BASE + 0x30);
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
//			if (face_get)
//			{
////				face_detect_count++;
//				rt_kprintf("wframe1 draw_red %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
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
//			if (rframe0_ready)
//			{
//				REG32(DSP_MM_BASE + 0x50) = 1;
//			}

			REG32(DSP_MM_BASE + 0x38) = 1;
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
//				rt_kprintf("wframe1_addr = 0x%x, rframe1_addr = 0x%x, alpha1_addr = 0x%x\n", wframe1_addr, rframe1_addr, alpha1_addr);
//		//				rt_kprintf("wframe1 read finish\n");
//		//			debug_new_case();
//			uint16_t *bgr565Image = (uint16_t *)wframe1_addr;
////
//			color565 *frame_start = (color565 *)0x4405E000;
//			uint8_t *frame_alpha_start = (uint8_t *)0x44070000;
//				rt_kprintf("bgr565Image = %p, frame_start = 0x%p, frame_alpha_start = 0x%p \n", bgr565Image, frame_start, frame_alpha_start);
//			rt_kprintf("display_width = %d, display_height = %d, snapshot_width = %d, snapshot_height = %d\n", display_width, display_height, snapshot_width, snapshot_height);

////				cropAndConvertImage(bgr565Image, bgr320_buffer1, 160, 128, 120);

			FaceRect *face_get = face_detect(wframe1_buffer);
			uint64_t *alpha1_buffer_addr = (uint64_t *)alpha1_buffer;
			for (size_t i = 0; i < (DISP_IMAGE_WIDTH * DISP_IMAGE_HEIGHT / 8); i++)
			{
				/* code */
				alpha1_buffer_addr[i] = 0x00;
			}
			if (face_get)
			{
				rt_kprintf("wframe1 draw_red %d, %d, %d, %d\n", face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				if (face_get->x1 < face_get->x2)
				{
					draw_green_box(rframe1_buffer, alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x1, face_get->y1, face_get->x2, face_get->y2);
				}
				else
				{
					draw_green_box(rframe1_buffer, alpha1_buffer, DISP_IMAGE_WIDTH, DISP_IMAGE_HEIGHT, face_get->x2, face_get->y2, face_get->x1, face_get->y1);
				}
			}
			if (rframe0_ready)
			{
				REG32(DSP_MM_BASE + 0x50) = 1;
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
