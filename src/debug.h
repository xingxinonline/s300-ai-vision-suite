/*** 
 * @Author       : panxinhao
 * @Date         : 2023-11-22 13:47:20
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-11-22 14:40:13
 * @FilePath     : \\ceva_no_ecc_test_ext_4m\\test_data_ext_mem\\src\\debug.h
 * @Description  : 
 * @
 * @Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved. 
 */

/*
 * debug.h
 *
 *  Created on: 2023年11月22日
 *      Author: xinhao
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "reg.h"

#define DBG_ENABLED             1

#define TEST_CODE_SRAM0         (1)
#define TEST_CODE_SRAM1         (2)
#define TEST_CODE_PSRAM 	    (3)
#define TEST_CODE_FLASH 	    (4)
#define TEST_CODE_AXI_DMA 	    (5)
#define TEST_CODE_AHB_DMA 	    (6)
#define TEST_CODE_AHB_SPI 	    (7)
#define TEST_CODE_AHB_SDIO 	    (8)
#define TEST_CODE_GPIO 		    (9)
#define TEST_CODE_I2C 		    (10)
#define TEST_CODE_I2S 		    (11)
#define TEST_CODE_UART		    (12)
#define TEST_CODE_KERNEL        (13)
#define TEST_CODE_DSP_RCC       (14)
#define TEST_CODE_DSP_MAILBOX   (15)
#define TEST_CODE_DSP_SCTRL     (16)
#define TEST_CODE_DSP_PMSS     	(17)

#define TEST_END_CODE           0xAAAAAAAA
#define DBG_STOP_CODE           0xBBBBBBBB   
#define CASE_END_CODE           0xCCCCCCCC  
#define DBG_TEST_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x10)
#define DBG_CASE_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x0C)
#define DBG_CHECK_ADDR          (DSP_RAM1_BASE + DSP_RAM_LEN - 0x08)
#define DBG_STOP_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x04)

int case_finish(void);
int debug_init(int case_num);
int debug_finish(void);
int debug_new_case(void);
int debug_case_set_failed(uint32_t err);
int debug_start(void);
int debug_stop(void);

#endif /* DEBUG_H_ */
