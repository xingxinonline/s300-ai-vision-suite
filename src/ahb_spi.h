/*
 * spi.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef AHB_SPI_H_
#define AHB_SPI_H_

#include "reg.h"

#define AHB_SPI0                        AHB_SPI0_BASE
#define AHB_SPI1                        AHB_SPI1_BASE


#define AHB_SPI_SSIENR(spix)            REG32((spix) + 0x0008)
#define AHB_SPI_SSIC_VERSION_ID(spix)   REG32((spix) + 0x005c)

int debug_test_ahb_spi(void);

#endif /* AHB_SPI_H_ */
