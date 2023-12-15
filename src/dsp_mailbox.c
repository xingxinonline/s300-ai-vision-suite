/*
 * dsp_mailbox.c
 *
 *  Created on: 2023年12月7日
 *      Author: xinhao
 */

#include "dsp_mailbox.h"

int debug_test_dsp_mailbox(void)
{
    uint32_t temp;
    /* Test start */
    debug_init(TEST_CODE_DSP_MAILBOX);
    /* Test 1: reg read & write*/
    {
        debug_new_case();
        DSP_MAILBOX_WRDATA = 0x0;
        DSP_MAILBOX_WRDATA = 0xFFFFFFFF;
        DSP_MAILBOX_WRDATA = 0x0;
        case_finish();
    }

    /* Test 2: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_RDDATA;
        (void)status;
        case_finish();
    }

    /* Test 3: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_STATUS;
        (void)status;
        case_finish();
    }

    /* Test 4: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_ERROR;
        (void)status;
        case_finish();
    }

    /* Test 5: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_SIT;

        DSP_MAILBOX_SIT = 0x0;
        temp = DSP_MAILBOX_SIT;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_SIT = 0xFFFFFFFF;
        temp = DSP_MAILBOX_SIT;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_SIT = status;
        temp = DSP_MAILBOX_SIT;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 6: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_RIT;

        DSP_MAILBOX_RIT = 0x0;
        temp = DSP_MAILBOX_RIT;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_RIT = 0xFFFFFFFF;
        temp = DSP_MAILBOX_RIT;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_RIT = status;
        temp = DSP_MAILBOX_RIT;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 7: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_IS;

        DSP_MAILBOX_IS = 0x0;
        temp = DSP_MAILBOX_IS;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_IS = 0xFFFFFFFF;
        temp = DSP_MAILBOX_IS;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_IS = status;
        temp = DSP_MAILBOX_IS;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 8: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_IE;

        DSP_MAILBOX_IE = 0x0;
        temp = DSP_MAILBOX_IE;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_IE = 0xFFFFFFFF;
        temp = DSP_MAILBOX_IE;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_IE = status;
        temp = DSP_MAILBOX_IE;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    /* Test 9: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_IP;
        (void)status;
        case_finish();
    }

    /* Test 8: reg read & write*/
    {
        debug_new_case();
        uint32_t status = DSP_MAILBOX_CTRL;

        DSP_MAILBOX_CTRL = 0x0;
        temp = DSP_MAILBOX_CTRL;
        if (temp != 0)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_CTRL = 0xFFFFFFFF;
        temp = DSP_MAILBOX_CTRL;
        if (temp != 0xFFFFFFFF)
        {
            /* code */
            debug_case_set_failed(temp);
        }

        DSP_MAILBOX_CTRL = status;
        temp = DSP_MAILBOX_CTRL;
        if (temp != status)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }

    debug_finish();
	return 0;
}
