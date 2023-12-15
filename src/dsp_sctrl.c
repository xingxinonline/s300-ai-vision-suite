/*
 * dsp_sctrl.c
 *
 *  Created on: 2023年12月12日
 *      Author: xinhao
 */

#include "dsp_sctrl.h"

int debug_test_dsp_sctrl(void)
{
    uint32_t temp;
    /* Test start */
    debug_init(TEST_CODE_DSP_SCTRL);
    /* Test 1: reg read & write*/
    {
        debug_new_case();
        uint32_t core_id = DSP_SCTRL_CORE_ID;
        DSP_SCTRL_CORE_ID = 0xFFFFFFFF;
        temp = DSP_SCTRL_CORE_ID;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        DSP_SCTRL_CORE_ID = 0;
        temp = DSP_SCTRL_CORE_ID;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        DSP_SCTRL_CORE_ID = core_id;
        temp = DSP_SCTRL_CORE_ID;
        if (temp != core_id)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 2: reg read & write*/
    {
        debug_new_case();
        uint32_t addr = DSP_SCTRL_INT_RESET_ADDR;
        DSP_SCTRL_INT_RESET_ADDR = 0xFFFFFFFF;
        temp = DSP_SCTRL_INT_RESET_ADDR;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        DSP_SCTRL_INT_RESET_ADDR = 0;
        temp = DSP_SCTRL_INT_RESET_ADDR;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        DSP_SCTRL_INT_RESET_ADDR = addr;
        temp = DSP_SCTRL_INT_RESET_ADDR;
        if (temp != addr)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 2: reg read & write*/
    {
        debug_new_case();
        uint32_t addr = DSP_SCTRL_INT_RESET_ADDR;
        DSP_SCTRL_INT_RESET_ADDR = 0xFFFFFFFF;
        temp = DSP_SCTRL_INT_RESET_ADDR;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        DSP_SCTRL_INT_RESET_ADDR = addr;
        temp = DSP_SCTRL_INT_RESET_ADDR;
        if (temp != addr)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 4: reg read & write*/
    {
        debug_new_case();
        uint32_t addr = DSP_SCTRL_INT_RESET_ADDR;
        (void)addr;
        case_finish();
    }
    debug_finish();
    return 0;
}
