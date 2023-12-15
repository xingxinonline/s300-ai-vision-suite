/*
 * i2s.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef I2S_H_
#define I2S_H_

#include "reg.h"

#define I2S0 I2S0_BASE
#define I2S1 I2S1_BASE

#define I2S_IER(i2sx)       REG32((i2sx) + 0x0000)
#define I2S_COMP_TYPE(i2sx) REG32((i2sx) + 0x01fc)

int debug_test_i2s(void);

#endif /* I2S_H_ */
