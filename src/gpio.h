/*
 * gpio.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "reg.h"

#define GPIO_MATRIX_CFG(gpiox)  REG32(IO_MATRIX_BASE + (gpiox) * 0x0004)
#define GPIO_MUX_CFG(gpiox)     REG32(IO_MUX_BASE + (gpiox) * 0x0004)

#define GPIO_ID_CODE            REG32(GPIO_BASE + 0x0064)
#define GPIO_VER_ID_CODE        REG32(GPIO_BASE + 0x006C)

#define GPIO_SWPOR_DR(portx)    REG32(GPIO_BASE + 0x0000 + (portx) * 12)
#define GPIO_SWPOR_DDR(portx)   REG32(GPIO_BASE + 0x0004 + (portx) * 12)
#define GPIO_SWPOR_CTL(portx)   REG32(GPIO_BASE + 0x0008 + (portx) * 12)
#define GPIO_EXT_PORT(portx)    REG32(GPIO_BASE + 0x0050 + (portx) * 4)

int set_gpio(uint32_t portx, uint32_t pinx, uint32_t func);
int debug_test_gpio(void);

#endif /* GPIO_H_ */
