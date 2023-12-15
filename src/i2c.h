/*
 * i2c.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef I2C_H_
#define I2C_H_

#include "reg.h"

#define I2C0                    I2C0_BASE
#define I2C1                    I2C1_BASE
#define I2C2                    I2C2_BASE
#define I2C3                    I2C3_BASE

#define I2C_IC_ENABLE(i2cx)     REG32((i2cx) + 0x006c)
#define I2C_IC_COMP_TYPE(i2cx)  REG32((i2cx) + 0x00fc)

int debug_test_i2c(void);

#endif /* I2C_H_ */
