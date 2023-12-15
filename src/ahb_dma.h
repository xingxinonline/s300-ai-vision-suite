/*
 * ahb_dma.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef AHB_DMA_H_
#define AHB_DMA_H_

#include "reg.h"

#define AHB_DMA0                    AHB_DMA0_BASE
#define AHB_DMA1                    AHB_DMA1_BASE

#define AHB_DMA_EN(dmax)            REG64((dmax) + 0x0398)    
#define AHB_DMA_COMPONENT_ID(dmax)  REG64((dmax) + 0x03f8)

int debug_test_ahb_dma(void);

#endif /* AHB_DMA_H_ */
