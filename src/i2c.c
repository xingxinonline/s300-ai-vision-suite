/*
 * i2c.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "i2c.h"
#include "debug.h"

int debug_test_i2c(void)
{
	/* Test start */
	debug_init(TEST_CODE_I2C);

	/* Test 1: i2c0 config read 0x44570140*/
    debug_new_case();
	uint32_t version0 = I2C_IC_COMP_TYPE(I2C0);
	if (version0 != 0x44570140)
	{
		debug_case_set_failed(version0);
	}

    /* Test 2: i2c0 enable  */
    debug_new_case();
    I2C_IC_ENABLE(I2C0) = 0x1;
    uint32_t en_status0 = I2C_IC_ENABLE(I2C0);
	if (en_status0 != 0x1)
	{
		debug_case_set_failed(en_status0);
	}
	/* Test 3: i2c1 config read 0x44570140*/
    debug_new_case();
	uint32_t version1 = I2C_IC_COMP_TYPE(I2C1);
	if (version1 != 0x44570140)
	{
		debug_case_set_failed(version1);
	}

    /* Test 4: i2c1 enable  */
    debug_new_case();
    I2C_IC_ENABLE(I2C1) = 0x1;
    uint32_t en_status1 = I2C_IC_ENABLE(I2C1);
	if (en_status1 != 0x1)
	{
		debug_case_set_failed(en_status1);
	}
	/* Test 5: i2c2 config read 0x44570140*/
    debug_new_case();
	uint32_t version2 = I2C_IC_COMP_TYPE(I2C2);
	if (version2 != 0x44570140)
	{
		debug_case_set_failed(version2);
	}

    /* Test 6: i2c2 enable  */
    debug_new_case();
    I2C_IC_ENABLE(I2C2) = 0x1;
    uint32_t en_status2 = I2C_IC_ENABLE(I2C2);
	if (en_status2 != 0x1)
	{
		debug_case_set_failed(en_status2);
	}
	/* Test 7: i2c3 config read 0x44570140*/
    debug_new_case();
	uint32_t version3 = I2C_IC_COMP_TYPE(I2C3);
	if (version3 != 0x44570140)
	{
		debug_case_set_failed(version3);
	}

    /* Test 8: i2c3 enable  */
    debug_new_case();
    I2C_IC_ENABLE(I2C3) = 0x1;
    uint32_t en_status3 = I2C_IC_ENABLE(I2C3);
	if (en_status3 != 0x1)
	{
		debug_case_set_failed(en_status3);
	}

	/* Test finished */
	debug_finish();

	return 0;
}
