/*
 * kernel.c
 *
 *  Created on: 2023年11月29日
 *      Author: xinhao
 */


#include "kernel.h"

int debug_test_kernel(void)
{
    /* Test start */
    debug_init(TEST_CODE_KERNEL);
    uint32_t temp = 0;
    /* Test 1: DMSS*/
    {
        debug_new_case();
        uint32_t old_val = REG32(DSP_DMSS_MSS_DMBA);
        REG32(DSP_DMSS_MSS_DMBA) = 0xFFFFFFFF;
        temp = REG32(DSP_DMSS_MSS_DMBA);
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DMBA) = 0;
        temp = REG32(DSP_DMSS_MSS_DMBA);
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DMBA) = old_val;
        temp = REG32(DSP_DMSS_MSS_DMBA);
        if (temp != old_val)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        temp = DSP_DMSS_MSS_DMBE;
        temp = DSP_DMSS_MSS_HDCFG;
        old_val = REG32(DSP_DMSS_MSS_SDCFG);
        REG32(DSP_DMSS_MSS_SDCFG) = 0xFFFFFFFF;
        temp = REG32(DSP_DMSS_MSS_SDCFG);
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_SDCFG) = 0;
        temp = REG32(DSP_DMSS_MSS_SDCFG);
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_SDCFG) = old_val;
        temp = REG32(DSP_DMSS_MSS_SDCFG);
        if (temp != old_val)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        old_val = REG32(DSP_DMSS_MSS_DDEA);
        REG32(DSP_DMSS_MSS_DDEA) = 0xFFFFFFFF;
        temp = REG32(DSP_DMSS_MSS_DDEA);
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DDEA) = 0;
        temp = REG32(DSP_DMSS_MSS_DDEA);
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DDEA) = old_val;
        temp = REG32(DSP_DMSS_MSS_DDEA);
        if (temp != old_val)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        old_val = REG32(DSP_DMSS_MSS_DDIA);
        REG32(DSP_DMSS_MSS_DDIA) = 0xFFFFFFFF;
        temp = REG32(DSP_DMSS_MSS_DDIA);
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DDIA) = 0;
        temp = REG32(DSP_DMSS_MSS_DDIA);
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_DMSS_MSS_DDIA) = old_val;
        temp = REG32(DSP_DMSS_MSS_DDIA);
        if (temp != old_val)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 2: EDAP*/
    {
        debug_new_case();
        uint32_t old_val = REG32(DSP_EDAP + DSP_MCCI_COM_REG(0));
        REG32(DSP_EDAP + DSP_MCCI_COM_REG(0)) = 0xFFFFFFFF;
        temp = REG32(DSP_EDAP + DSP_MCCI_COM_REG(0));
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_EDAP + DSP_MCCI_COM_REG(0)) = 0;
        temp = REG32(DSP_EDAP + DSP_MCCI_COM_REG(0));
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        REG32(DSP_EDAP + DSP_MCCI_COM_REG(0)) = old_val;
        temp = REG32(DSP_EDAP + DSP_MCCI_COM_REG(0));
        if (temp != old_val)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test finished */
    debug_finish();
    return 0;
}
