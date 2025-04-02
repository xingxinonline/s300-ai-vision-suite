/*
 * dsp_mm.c
 *
 *  Created on: 2024年3月22日
 *      Author: xinhao
 */

#include "dsp_mm.h"

//#include "axi_dma.h"
//#include "psram.h"
#include "kernel.h"



volatile uint8_t wframe0_flag = 0;
volatile uint8_t wframe1_flag = 0;
volatile uint8_t rframe0_ready = 1;
volatile uint8_t rframe1_ready = 1;
volatile uint8_t rframe0_flag = 0;
volatile uint8_t rframe1_flag = 0;

volatile uint32_t allocated_ivi_mm = 0;

void wframe0_interrupt_hook() PRAGMA_CSECT(".external_wframe0_interrupt") __attribute__((interrupt));
void wframe1_interrupt_hook() PRAGMA_CSECT(".external_wframe1_interrupt") __attribute__((interrupt));
void rframe0_interrupt_hook() PRAGMA_CSECT(".external_rframe0_interrupt") __attribute__((interrupt));
void rframe1_interrupt_hook() PRAGMA_CSECT(".external_rframe1_interrupt") __attribute__((interrupt));

void wframe0_interrupt_hook()
{
    wframe0_flag = 1;
}

void wframe1_interrupt_hook()
{
    wframe1_flag = 1;
}

void rframe0_interrupt_hook()
{
    rframe0_ready = 1;
}

void rframe1_interrupt_hook()
{
    rframe1_ready = 1;
}

// 定义绿色和红色的RGB565值
#define GREEN_RGB565  0x07E0  // 与BGR565相同，因为绿色部分不变
#define RED_RGB565    0xF800  // 与BGR565不同，因为红色和蓝色的位位置相同

// 绘制绿色方框函数，使用 16-bit 存储两个 8-bit Alpha 值
void draw_green_box(uint16_t *img_data, int width, int height, int x1, int y1, int x2, int y2) {
    if (img_data == NULL) {
    	rt_kprintf("Error: Image data is NULL.\n");
        return;
    }

    // 绘制上边缘和下边缘
    for (int x = x1; x <= x2; x++) {
        if (y1 >= 0 && y1 < height) {
            img_data[y1 * width + x] = GREEN_RGB565;  // 上边缘
        }
        if (y2 >= 0 && y2 < height) {
            img_data[y2 * width + x] = GREEN_RGB565;  // 下边缘
        }
    }
    // 绘制左边缘和右边缘
    for (int y = y1; y <= y2; y++) {
        if (x1 >= 0 && x1 < width) {
            img_data[y * width + x1] = GREEN_RGB565;  // 左边缘
        }
        if (x2 >= 0 && x2 < width) {
            img_data[y * width + x2] = GREEN_RGB565;  // 右边缘
        }
    }
}

void draw_alpha_box(uint8_t *alphaImage, int width, int height, int x1, int y1, int x2, int y2) {
    if (alphaImage == NULL) {
    	rt_kprintf("Error: alphaImage data is NULL.\n");
        return;
    }

    // 绘制上边缘和下边缘
    for (int x = x1; x <= x2; x++) {
        if (y1 >= 0 && y1 < height) {
        	alphaImage[y1 * width + x] = 0xFF;  // 上边缘
        }
        if (y2 >= 0 && y2 < height) {
        	alphaImage[y2 * width + x] = 0xFF;  // 下边缘
        }
    }
    // 绘制左边缘和右边缘
    for (int y = y1; y <= y2; y++) {
        if (x1 >= 0 && x1 < width) {
        	alphaImage[y * width + x1] = 0xFF;  // 左边缘
        }
        if (x2 >= 0 && x2 < width) {
        	alphaImage[y * width + x2] = 0xFF;  // 右边缘
        }
    }
}

// 绘制红色方框函数
void draw_red_box(uint16_t *img_data, uint8_t *alphaImage, int width, int height, int x1, int y1, int x2, int y2) {
    if (img_data == NULL) {
    	rt_kprintf("Error: Image data is NULL.\n");
        return;
    }

    // 绘制上边缘和下边缘
	for (int x = x1; x <= x2; x++) {
		if (y1 >= 0 && y1 < height) {
			img_data[y1 * width + x] = RED_RGB565;  // 上边缘

			alphaImage[y1 * width + x] = 0xFF;
		}
		if (y2 >= 0 && y2 < height) {
			img_data[y2 * width + x] = RED_RGB565;  // 下边缘
			alphaImage[y2 * width + x] = 0xFF;
		}
	}
	// 绘制左边缘和右边缘
	for (int y = y1; y <= y2; y++) {
		if (x1 >= 0 && x1 < width) {
			img_data[y * width + x1] = RED_RGB565;  // 左边缘
			alphaImage[y * width + x1] = 0xFF;
		}
		if (x2 >= 0 && x2 < width) {
			img_data[y * width + x2] = RED_RGB565;  // 右边缘
			alphaImage[y * width + x2] = 0xFF;
		}
	}
}

size_t process_pic_max = 1;

//int mm_axi_dma(size_t data_size, uint64_t src_addr, uint64_t dst_addr)
//{
//    if (data_size <= MM_AXI_DMA_TRANS_MAX)
//    {
//        /* code */
//        axi_dma_init(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, data_size, 16, 16);
//        axi_dma_start(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, src_addr, dst_addr);
//        while (AXI_DMA_CHEN(MM_AXI_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (MM_AXI_DMA_CHANNEL - 1))));
//    }
//    else
//    {
//        /* code */
//        size_t data_remain = data_size;
//        uint64_t src_offset = 0;
//        uint64_t dst_offset = 0;
//        do
//        {
//            /* code */
//            axi_dma_init(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, MM_AXI_DMA_TRANS_MAX, 16, 16);
//            axi_dma_start(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, src_addr + src_offset, dst_addr + dst_offset);
//            while (AXI_DMA_CHEN(MM_AXI_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (MM_AXI_DMA_CHANNEL - 1))));
////            debug_printf("src_addr = 0x%llx, src_offset = 0x%llx, dst_addr = 0x%llx, dst_offset = 0x%llx\r\n", src_addr, src_offset, dst_addr, dst_offset);
////            debug_printf("src_addr + src_offset = 0x%llx\n", *(uint64_t *)(src_addr + src_offset));
//            src_offset += MM_AXI_DMA_TRANS_MAX;
//            dst_offset += MM_AXI_DMA_TRANS_MAX;
//            data_remain -= MM_AXI_DMA_TRANS_MAX;
//        }
//        while (data_remain > MM_AXI_DMA_TRANS_MAX);
//        axi_dma_init(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, data_remain, 16, 16);
//        axi_dma_start(MM_AXI_DMA, MM_AXI_DMA_CHANNEL, src_addr + src_offset, dst_addr + dst_offset);
////        debug_printf("src_addr = 0x%llx, src_offset = 0x%llx, dst_addr = 0x%llx, dst_offset = 0x%llx\r\n", src_addr, src_offset, dst_addr, dst_offset);
////        debug_printf("src_addr + src_offset = 0x%llx\n", *(uint64_t *)(src_addr + src_offset));
//        while (AXI_DMA_CHEN(MM_AXI_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (MM_AXI_DMA_CHANNEL - 1))));
//    }
//    return 0;
//}

uint32_t pic_cnt = 0;

int debug_test_dsp_mm(void)
{
	TEST_ASSERT_EQUAL(CSL_SUCCESS, ICU_Disable());
	__asm__ volatile("dint\n"
						 "nop");
	T_Internal_Interrupt_Configuration interrupt_config = { 0 };
	allocated_ivi_mm = ICU_IVA_Allocate((uint32_t) wframe0_interrupt_hook);
	interrupt_config.priority = 6;
	interrupt_config.imod = ICFG_IMOD_POSITIVE_EDGE;
	interrupt_config.ivi = allocated_ivi_mm;
	ICU_Configure_External_Int(&interrupt_config, ICU_EXT_WFRAME0_FINISH);
	allocated_ivi_mm = ICU_IVA_Allocate((uint32_t) wframe1_interrupt_hook);
	interrupt_config.priority = 6;
	interrupt_config.imod = ICFG_IMOD_POSITIVE_EDGE;
	interrupt_config.ivi = allocated_ivi_mm;
	ICU_Configure_External_Int(&interrupt_config, ICU_EXT_WFRAME1_FINISH);
	allocated_ivi_mm = ICU_IVA_Allocate((uint32_t) rframe0_interrupt_hook);
	interrupt_config.priority = 6;
	interrupt_config.imod = ICFG_IMOD_POSITIVE_EDGE;
	interrupt_config.ivi = allocated_ivi_mm;
	ICU_Configure_External_Int(&interrupt_config, ICU_EXT_RFRAME0_REQ);
	allocated_ivi_mm = ICU_IVA_Allocate((uint32_t) rframe1_interrupt_hook);
	interrupt_config.priority = 6;
	interrupt_config.imod = ICFG_IMOD_POSITIVE_EDGE;
	interrupt_config.ivi = allocated_ivi_mm;
	ICU_Configure_External_Int(&interrupt_config, ICU_EXT_RFRAME1_REQ);
	TEST_ASSERT_EQUAL(CSL_SUCCESS, ICU_Enable());
	int icu_enabled = ICU_Is_Enabled();
	rt_kprintf("ICU_Enable %d\r\n", icu_enabled);
	__asm__ volatile("eint\n"
		                         "nop");
    return 0;
}
