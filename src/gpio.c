/*
 * gpio.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "gpio.h"
#include "debug.h"

int set_gpio(uint32_t portx, uint32_t pinx, uint32_t func)
{
    uint32_t temp, shift, index;
    temp = portx * 32 + pinx;
    temp <<= 1;
    index = temp / 32;
    shift = temp % 32;
    temp = GPIO_MATRIX_CFG(index);
    temp &= ~(0x3 << shift);
    temp |= func << shift;
    GPIO_MATRIX_CFG(index) = temp;
    return 0;
}

int debug_test_gpio(void)
{
	/* Test start */
	debug_init(TEST_CODE_GPIO);

    /* Test 1: MATRIX_CFG write&read */
    debug_new_case();
	GPIO_MATRIX_CFG(0) = 0xAAAAAAAA;
	GPIO_MATRIX_CFG(1) = 0xAAAAAAAA;
	GPIO_MATRIX_CFG(2) = 0xAAAAAAAA;

    if (GPIO_MATRIX_CFG(0) != 0xAAAAAAAA || GPIO_MATRIX_CFG(1) != 0xAAAAAAAA || GPIO_MATRIX_CFG(2) != 0xAAAAAAAA)
    {
        debug_case_set_failed(GPIO_MATRIX_CFG(0) | GPIO_MATRIX_CFG(1) | GPIO_MATRIX_CFG(2));
    }

    /* Test 2: MUX_CFG write&read */
    debug_new_case();
    GPIO_MUX_CFG(0) = 0xAAAAAAAA;
    GPIO_MUX_CFG(1) = 0xAAAAAAAA;
    GPIO_MUX_CFG(2) = 0xAAAAAAAA;
    if (GPIO_MUX_CFG(0) != 0xAAAAAAAA || GPIO_MUX_CFG(1) != 0xAAAAAAAA || GPIO_MUX_CFG(2) != 0xAAAAAAAA)
    {
        /* code */
        debug_case_set_failed(GPIO_MATRIX_CFG(0) | GPIO_MATRIX_CFG(1) | GPIO_MATRIX_CFG(2));
    }
    
	/* Test 3: read id*/
    debug_new_case();
    uint32_t id = GPIO_VER_ID_CODE;
    if (id != 0x3230392A)
    {
        /* code */
        debug_case_set_failed(id);
    }
    
    /* Test 4: reg write&read */
    debug_new_case();
    GPIO_SWPOR_DR(0) = 1;
    uint32_t dat = GPIO_SWPOR_DR(0);
    if (dat != 1)
    {
        /* code */
        debug_case_set_failed(dat);
    }

    /* Test finished */
	debug_finish();

    return 0;
    
}

