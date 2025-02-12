/*
 * debug.c
 *
 *  Created on: 2023��12��18��
 *      Author: xinhao
 */

#include "debug.h"
#include "uart.h"
#include "reg.h"
#include "kernel.h"
#include "custom_printf.h"
#include "vec-c.h"
#include <stdint.h>

// 定义 FRCC 的最大值（32 位计数器）
#define FRCC_MAX 0xFFFFFF00U

uint32_t get_cycles(void)
{
	return WATCHDOG_get_counter_value();
}

uint32_t get_cycles_start(void)
{
	WATCHDOG_set_threshold(1, 0xFFFFFFFE);
	WATCHDOG_enable();
	return WATCHDOG_get_counter_value();
}

uint32_t get_cycles_end(void)
{
	WATCHDOG_disable();
	return WATCHDOG_get_counter_value();
}


/**
 * @brief 计算 FRCC 计数器的周期数
 * @param start 初始计数值（FRCC_start）
 * @param end   结束计数值（FRCC_end）
 * @return      总周期数
 */
uint32_t calculate_cycles(uint32_t start, uint32_t end) {
    uint32_t total_cycles = 0;

    if (end >= start) {
        // 未发生溢出
        total_cycles = (end - start);
    } else {
        // 发生溢出
        total_cycles = (uint64_t)((FRCC_MAX) - start + 1) + end;
    }

    return total_cycles;
}

/**
 * @brief 将周期数转换为时间（秒）
 * @param cycles      总周期数
 * @param clock_freq  核心时钟频率（Hz）
 * @return            耗时（秒）
 */
float cycles_to_time(uint64_t cycles, float clock_freq) {
    return cycles / clock_freq;
}


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


