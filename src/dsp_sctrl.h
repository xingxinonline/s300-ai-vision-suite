/*
 * dsp_sctrl.h
 *
 *  Created on: 2023年12月12日
 *      Author: xinhao
 */

#ifndef DSP_SCTRL_H_
#define DSP_SCTRL_H_

#include "debug.h"

#define DSP_SCTRL  DSP_SYSCTL_BASE

#define DSP_SCTRL_CORE_ID           REG32(DSP_SCTRL + 0x00)
#define DSP_SCTRL_INT_RESET_ADDR    REG32(DSP_SCTRL + 0x04)
#define DSP_SCTRL_CEVA_CONFIG       REG32(DSP_SCTRL + 0x08)
#define DSP_SCTRL_CEVA_STATUS       REG32(DSP_SCTRL + 0x0C)

int debug_test_dsp_sctrl(void);

#endif /* DSP_SCTRL_H_ */
