/*
 * debug.h
 *
 *  Created on: 2023��12��18��
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
#define TEST_CODE_DSP_EDAP     	(18)
#define TEST_CODE_DSP_DMSS     	(19)
#define TEST_CODE_AON        	(20)
#define TEST_CODE_SEC        	(21)
#define TEST_CODE_DSP_PIM       (22)
#define TEST_CODE_DSP_MM        (23)

#define TEST_END_CODE           0xAAAAAAAA
#define DBG_STOP_CODE           0xBBBBBBBB
#define CASE_END_CODE           0xCCCCCCCC
#define DBG_TEST_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x10)
#define DBG_CASE_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x0C)
#define DBG_CHECK_ADDR          (DSP_RAM1_BASE + DSP_RAM_LEN - 0x08)
#define DBG_STOP_ADDR           (DSP_RAM1_BASE + DSP_RAM_LEN - 0x04)

/* Boolean */
#define TEST_ASSERT(condition)                     TestAssert((condition), __LINE__)
#define TEST_ASSERT_TRUE(condition)                TestAssert((condition), __LINE__)
#define TEST_ASSERT_UNLESS(condition)              TestAssert(!(condition), __LINE__)
#define TEST_ASSERT_FALSE(condition)               TestAssert(!(condition), __LINE__)
#define TEST_ASSERT_NULL(pointer)                  TestAssert(((pointer) == NULL), __LINE__)
#define TEST_ASSERT_NOT_NULL(pointer)              TestAssert(((pointer) != NULL), __LINE__)
#define TEST_ASSERT_NOT_EQUAL(expected, actual)    TestAssertNotEqualNumber((expected),(actual), __LINE__)
#define TEST_ASSERT_EQUAL(expected, actual)        TestAssertEqualNumber((expected), (actual), __LINE__)

int case_finish(void);
int debug_init(int case_num);
int debug_finish(void);
int debug_new_case(void);
int debug_case_set_failed(uint32_t err);
int debug_start(void);
int debug_stop(void);
void debug_printf(const char *format, ...);
void TestAssert(const uint32_t condition, const uint32_t lineNumber);
void TestAssertEqualNumber(const uint32_t expected, const uint32_t actual, const uint32_t lineNumber);
void TestAssertNotEqualNumber(const uint32_t expected, const uint32_t actual, const uint32_t lineNumber);

#endif /* DEBUG_H_ */
