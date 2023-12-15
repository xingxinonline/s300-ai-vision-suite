/*
 * spi.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "ahb_spi.h"
#include "debug.h"

int debug_test_ahb_spi(void)
{
	/* Test start */
	debug_init(TEST_CODE_AHB_SPI);

	/* Test 1: SPI0 config read 0x3130332A*/
    debug_new_case();
	uint32_t version0 = AHB_SPI_SSIC_VERSION_ID(AHB_SPI0);
	if (version0 != 0x3130332A)
	{
		debug_case_set_failed(version0);
	}

    /* Test 2: SPI1 config read 0x3130332A*/
    debug_new_case();
	uint32_t version1 = AHB_SPI_SSIC_VERSION_ID(AHB_SPI1);
	if (version1 != 0x3130332A)
	{
		debug_case_set_failed(version1);
	}

    /* Test 3: spi0 config  */
    debug_new_case();
    AHB_SPI_SSIENR(AHB_SPI0) = 0x1;
    uint32_t en_status0 = AHB_SPI_SSIENR(AHB_SPI0);
	if (en_status0 != 0x1)
	{
		debug_case_set_failed(en_status0);
	}

    /* Test 3: spi1 config  */
    debug_new_case();
    AHB_SPI_SSIENR(AHB_SPI1) = 0x1;
    uint32_t en_status1 = AHB_SPI_SSIENR(AHB_SPI1);
	if (en_status1 != 0x1)
	{
		debug_case_set_failed(en_status1);
	}

	/* Test finished */
	debug_finish();

	return 0;
}
