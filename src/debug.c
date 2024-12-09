/*
 * debug.c
 *
 *  Created on: 2023��12��18��
 *      Author: xinhao
 */

#include "debug.h"
#include "uart.h"
#include "custom_printf.h"

int debug_init(int case_num)
{
#if DBG_ENABLED
    REG32(DBG_TEST_ADDR) = 0xDDDD0000 + case_num;
    REG32(DBG_CASE_ADDR) = 0x0;
    REG32(DBG_CHECK_ADDR) = 0x0;
    REG32(DBG_STOP_ADDR) = 0x0;
    rt_kprintf("debug_init \n");
#endif
    return 0;
}

int case_finish(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = CASE_END_CODE;
    rt_kprintf("case_finish \n");
#endif
    return 0;
}

int debug_finish(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = TEST_END_CODE;
    rt_kprintf("debug_finish \n");
#endif
    return 0;
}

int debug_start(void)
{
#if DBG_ENABLED
    REG32(DBG_TEST_ADDR) = 0;
    rt_kprintf("debug_start \n");
#endif
    return 0;
}

int debug_stop(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = DBG_STOP_CODE;
    rt_kprintf("debug_stop \n");
#endif
    return 0;
}

int debug_new_case(void)
{
#if DBG_ENABLED
    uint32_t case_num;
    uint16_t case_flag;
    case_num = REG32(DBG_CASE_ADDR);
    case_flag = case_num & 0xff;
    case_num = (case_num >> 16) & 0xff;
    case_num++;
    case_num = (case_num << 16) | case_flag;
    REG32(DBG_CASE_ADDR) = case_num;
    REG32(DBG_STOP_ADDR) = 0x0;
    REG32(DBG_CHECK_ADDR) = 0x0;
    rt_kprintf("debug_new_case case_num = 0x%x\n", case_num);

#endif
    return 0;
}

int debug_case_set_failed(uint32_t err)
{
#if DBG_ENABLED
    uint32_t case_num;
    case_num = REG32(DBG_CASE_ADDR);
    case_num |=  1 << (((case_num >> 16) & 0xff) - 1);
    REG32(DBG_CASE_ADDR) = case_num;
    REG32(DBG_CHECK_ADDR) = err;
    rt_kprintf("debug_case_set_failed err = 0x%x\n", err);
#endif
    return 0;
}

void TestAssert(const uint32_t condition, const uint32_t lineNumber)
{
    if (!condition)
    {
    	rt_kprintf("TestAssert lineNumber %d \n", lineNumber);
    }
    return;
}

void TestAssertEqualNumber(const uint32_t expected, const uint32_t actual, const uint32_t lineNumber)
{
//    debug_case_set_failed(lineNumber);
    if (expected != actual)
    {
    	rt_kprintf("TestAssert expected = %d actual = %d lineNumber = %d \n", expected, actual, lineNumber);
    }
    else
    {
    	rt_kprintf("TestAssert actual = expected = %d \n", expected);
    }
    return;
}

void TestAssertNotEqualNumber(const uint32_t expected, const uint32_t actual, const uint32_t lineNumber)
{
//    debug_case_set_failed(lineNumber);
    if (expected == actual)
    {
    	rt_kprintf("TestAssert expected = %d actual = %d lineNumber = %d \n", expected, actual, lineNumber);
    }
    else
    {
    	rt_kprintf("TestAssert actual = expected = %d \n", expected);
    }
    return;
}


