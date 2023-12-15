/*
 * sdio.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "sdio.h"
#include "debug.h"

int debug_test_sdio(void)
{
	/* Test start */
	debug_init(TEST_CODE_AHB_SDIO);

	/* Test 1: sdio0 config read 0x5342250A*/
    debug_new_case();
	uint32_t version0 = SDIO_VERID(SDIO0);
	if (version0 != 0x5342250A)
	{
		debug_case_set_failed(version0);
	}

    /* Test 2: sdio0 power enable  */
    debug_new_case();
    SDIO_PWREN(SDIO0) = 0x1;
    uint32_t en_status0 = SDIO_PWREN(SDIO0);
	if (en_status0 != 0x1)
	{
		debug_case_set_failed(en_status0);
	}

    /* Test 3: sdio1 config read 0x5342250A*/
    debug_new_case();
	uint32_t version1 = SDIO_VERID(SDIO1);
	if (version1 != 0x5342250A)
	{
		debug_case_set_failed(version1);
	}

    /* Test 4: sdio1 power enable  */
    debug_new_case();
    SDIO_PWREN(SDIO1) = 0x1;
    uint32_t en_status1 = SDIO_PWREN(SDIO1);
	if (en_status1 != 0x1)
	{
		debug_case_set_failed(en_status1);
	}

	/* Test finished */
	debug_finish();

	return 0;
}

