/*
 * i2s.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "i2s.h"
#include "debug.h"

int debug_test_i2s(void)
{
	/* Test start */
	debug_init(TEST_CODE_I2S);

	/* Test 1: i2s0 config read 0x445701A0*/
    debug_new_case();
	uint32_t version0 = I2S_COMP_TYPE(I2S0);
	if (version0 != 0x445701A0)
	{
		debug_case_set_failed(version0);
	}

    /* Test 2: i2s1 config  */
    debug_new_case();
    I2S_IER(I2S0) = 0x1;
    uint32_t en_status0 = I2S_IER(I2S0);
	if (en_status0 != 0x1)
	{
		debug_case_set_failed(en_status0);
	}

    /* Test 3: i2s1 config read 0x445701A0*/
    debug_new_case();
	uint32_t version1 = I2S_COMP_TYPE(I2S1);
	if (version1 != 0x445701A0)
	{
		debug_case_set_failed(version1);
	}

    /* Test 4: i2s1 config  */
    debug_new_case();
    I2S_IER(I2S1) = 0x1;
    uint32_t en_status1 = I2S_IER(I2S1);
	if (en_status1 != 0x1)
	{
		debug_case_set_failed(en_status1);
	}

	/* Test finished */
	debug_finish();

	return 0;
}
