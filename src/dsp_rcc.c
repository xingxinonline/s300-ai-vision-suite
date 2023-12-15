/*
 * dsp_rcc.c
 *
 *  Created on: 2023年12月4日
 *      Author: xinhao
 */

#include "dsp_rcc.h"

int debug_test_dsp_rcc(void)
{
    uint32_t temp;
    /* Test start */
    debug_init(TEST_CODE_DSP_RCC);
    /* Test 1: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_SYS_CLKEN;

        DSP_SYS_CLKEN = 1;
        temp = DSP_SYS_CLKEN;
        if (temp != 1)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_CLKEN = 0xFFFFFFFF;
        temp = DSP_SYS_CLKEN;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_CLKEN = status;
        temp = DSP_SYS_CLKEN;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 2: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_PERF_CLKEN;

        DSP_PERF_CLKEN = (1 << 0) | (1 << 1) |  (1 << 2) | (1 << 3);
        temp = DSP_PERF_CLKEN;
        if (temp != ((1 << 0) | (1 << 1) |  (1 << 2) | (1 << 3)))
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PERF_CLKEN = 0xFFFFFFFF;
        temp = DSP_PERF_CLKEN;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PERF_CLKEN = status;
        temp = DSP_PERF_CLKEN;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 3: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_SYS_RSTN_CTL;

        DSP_SYS_RSTN_CTL = 0;
        temp = DSP_SYS_RSTN_CTL;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_RSTN_CTL = 0xFFFFFFFF;
        temp = DSP_SYS_RSTN_CTL;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_RSTN_CTL = status;
        temp = DSP_SYS_RSTN_CTL;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

        /* Test 4: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_PERF_RSTN_CTL;

        DSP_PERF_RSTN_CTL = (1 << 0) | (1 << 1) |  (1 << 2) | (1 << 3);
        temp = DSP_PERF_RSTN_CTL;
        if (temp != ((1 << 0) | (1 << 1) |  (1 << 2) | (1 << 3)))
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PERF_RSTN_CTL = 0xFFFFFFFF;
        temp = DSP_PERF_RSTN_CTL;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PERF_RSTN_CTL = status;
        temp = DSP_PERF_RSTN_CTL;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 5: reg read & write*/
    {
        debug_new_case();

        DSP_PLL_CRL = 0;
        temp = DSP_PLL_CRL;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PLL_CRL = 0xFFFFFFFF;
        temp = DSP_PLL_CRL;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_PLL_CRL = 0x01000000;
        temp = DSP_PLL_CRL;
        if (temp != 0x01000000)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 6: reg read & write*/
    {
        debug_new_case();
        uint32_t pll_val = DSP_PLL_CRL2;
        pll_val &= ~(1UL << 31);
        DSP_PLL_CRL2 = pll_val;
        while((DSP_PLOCK_STATUS & 0x1) == 0);
        uint32_t status = DSP_SYS_CLK_SEL;

        DSP_SYS_CLK_SEL = 1;
        temp = DSP_SYS_CLK_SEL;
        if (temp != 1)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_CLK_SEL = 0xFFFFFFFE;
        temp = DSP_SYS_CLK_SEL;
        if (temp != 0xFFFFFFFE)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_SYS_CLK_SEL = status;
        temp = DSP_SYS_CLK_SEL;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        pll_val |= (1UL << 31);
        DSP_PLL_CRL2 = pll_val;
        while((DSP_PLOCK_STATUS & 0x1) == 1);
        case_finish();
    }

    debug_finish();
	return 0;
}
