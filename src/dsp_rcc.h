/*
 * dsp.rcc.h
 *
 *  Created on: 2023年12月4日
 *      Author: xinhao
 */

#ifndef DSP_RCC_H_
#define DSP_RCC_H_

#include "reg.h"
#include "debug.h"

#define DSP_RCC DSP_RCC_BASE

#define DSP_SYS_CLKEN       REG32(DSP_RCC + 0x00)
#define DSP_PERF_CLKEN      REG32(DSP_RCC + 0x04)
#define DSP_SYS_RSTN_CTL    REG32(DSP_RCC + 0x08)
#define DSP_PERF_RSTN_CTL   REG32(DSP_RCC + 0x0C)
#define DSP_WARM_RSTN       REG32(DSP_RCC + 0x10)
#define DSP_SYS_CLK_SEL     REG32(DSP_RCC + 0x14)
#define DSP_CEVA_RST_CRZL   REG32(DSP_RCC + 0x18)
#define DSP_PLL_CRL         REG32(DSP_RCC + 0x1C)
#define DSP_PLL_CRL2        REG32(DSP_RCC + 0x20)
#define DSP_PLOCK_STATUS    REG32(DSP_RCC + 0x24)
#define DSP_CEVA_STATUS     REG32(DSP_RCC + 0x28)

int debug_test_dsp_rcc(void);

#endif /* DSP_RCC_H_ */
