/*
 * flash.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "flash.h"
#include "debug.h"

int debug_test_flash(void)
{
    while (!(FLASH_OSPI_CONFIG & 0x80000000));
    FLASH_OSPI_CONFIG &= ~0x81;
    FLASH_OSPI_ISR = 0xF7FFF;
	/* Test start */
	debug_init(TEST_CODE_FLASH);

	/* Test 1: OSPI config read 0x04000300*/
    debug_new_case();
	uint32_t version = FLASH_OSPI_MIR;
	if (version != 0x04000300)
	{
		debug_case_set_failed(version);
	}

    /* Test 2: OSPI config  */
    debug_new_case();
    FLASH_OSPI_CONFIG |= 0x1;
    uint32_t en_status = FLASH_OSPI_CONFIG;
	if ((en_status & 0x1) == 0)
	{
		debug_case_set_failed(en_status);
	}

	/* Test finished */
	debug_finish();

	return 0;
}
