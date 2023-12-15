/*
 * sdio.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef SDIO_H_
#define SDIO_H_

#include "reg.h"

#define SDIO0   AHB_SDIO0_BASE
#define SDIO1   AHB_SDIO1_BASE

#define SDIO_PWREN(sdiox)   REG32((sdiox) + 0x0004)
#define SDIO_VERID(sdiox)   REG32((sdiox) + 0x006c)

int debug_test_sdio(void);

#endif /* SDIO_H_ */
