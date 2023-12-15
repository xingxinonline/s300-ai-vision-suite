/*
 * dsp_pmss.c
 *
 *  Created on: 2023年12月14日
 *      Author: xinhao
 */

#include "dsp_pmss.h"

uint8_t pdma_dst_func() PRAGMA_CSECT("internal_c_test");
uint8_t pdma_src_func() PRAGMA_CSECT("external_c_test9");

uint8_t pdma_dst_func()
{
    int a = 1, b = 2;
    return (a + b);
}

uint8_t pdma_src_func()
{
    int a = 2, b = 2;
    return (a + b);
}

int debug_test_dsp_pmss(void)
{
    /* Test start */
    debug_init(TEST_CODE_DSP_MAILBOX);
    {
        debug_new_case();
        uint8_t (*volatile f_pointer)()  = &pdma_dst_func;
        uint8_t val = f_pointer();
        if (val != pdma_dst_func())
        {
            debug_case_set_failed(val);
        }
        mss_load_internal_program((uint32_t)pdma_dst_func, (uint32_t)pdma_src_func, 0x60);
        val = f_pointer();
        if (val != pdma_src_func())
        {
            debug_case_set_failed(val);
        }
        case_finish();
    }
    debug_finish();
    return 0;
}
