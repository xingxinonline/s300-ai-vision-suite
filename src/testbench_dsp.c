
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
#include "debug.h"

#include "sram.h"
#include "psram.h"
#include "flash.h"
#include "axi_dma.h"
#include "ahb_dma.h"
#include "ahb_spi.h"
#include "sdio.h"
#include "gpio.h"
#include "i2c.h"
#include "i2s.h"
#include "uart.h"
#include "kernel.h"
#include "dsp_rcc.h"
#include "dsp_mailbox.h"
#include "dsp_sctrl.h"
#include "dsp_pmss.h"

#define TEST_RUN(test_num) debug_test_##test_num()

#define TEST_ALL		        1

#if TEST_ALL
	#define TEST_SRAM           1
	#define TEST_PSRAM          1
	#define TEST_FLASH          1
	#define TEST_AXI_DMA        1
	#define TEST_AHB_DMA        1
	#define TEST_AHB_SPI        1
	#define TEST_SDIO           1
	#define TEST_GPIO           1
	#define TEST_I2C            1
	#define TEST_I2S            1
	#define TEST_UART           1
	#define TEST_KERNEL         1
	#define TEST_DSP_RCC        1
	#define TEST_DSP_MAILBOX    1
	#define TEST_DSP_SCTRL      1
	#define TEST_DSP_PMSS       1
#else
	#define TEST_SRAM           0
	#define TEST_PSRAM          0
	#define TEST_FLASH          0
	#define TEST_AXI_DMA        0
	#define TEST_AHB_DMA        0
	#define TEST_AHB_SPI        0
	#define TEST_SDIO           0
	#define TEST_GPIO           0
	#define TEST_I2C            0
	#define TEST_I2S            0
	#define TEST_UART           1
	#define TEST_KERNEL         0
	#define TEST_DSP_RCC        1
	#define TEST_DSP_MAILBOX    1
	#define TEST_DSP_SCTRL      1
	#define TEST_DSP_PMSS       1
#endif


int main(void)
{
    /* Test start */
	debug_start();
    
#if TEST_SRAM
    TEST_RUN(sram);
#endif
#if TEST_PSRAM
    TEST_RUN(psram);
#endif
#if TEST_FLASH
    TEST_RUN(flash);
#endif
#if TEST_AXI_DMA
    TEST_RUN(axi_dma);
#endif
#if TEST_AHB_DMA
    TEST_RUN(ahb_dma);
#endif
#if TEST_AHB_SPI
    TEST_RUN(ahb_spi);
#endif
#if TEST_SDIO
    TEST_RUN(sdio);
#endif
#if TEST_GPIO
    TEST_RUN(gpio);
#endif
#if TEST_I2C
    TEST_RUN(i2c);
#endif
#if TEST_I2S
    TEST_RUN(i2s);
#endif
#if TEST_UART
    TEST_RUN(uart);
#endif
#if TEST_KERNEL
    TEST_RUN(kernel);
#endif
#if TEST_DSP_RCC
    TEST_RUN(dsp_rcc);
#endif
#if TEST_DSP_MAILBOX
    TEST_RUN(dsp_mailbox);
#endif
#if TEST_DSP_SCTRL
    TEST_RUN(dsp_sctrl);
#endif
#if TEST_DSP_PMSS
    TEST_RUN(dsp_pmss);
#endif

    /* Test finished */
    debug_stop();

    return 0;
}
