/*
 * @Author       : panxinhao
 * @Date         : 2023-11-22 13:47:29
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-11-22 14:40:49
 * @FilePath     : \\ceva_no_ecc_test_ext_4m\\test_data_ext_mem\\src\\debug.c
 * @Description  :
 *
 * Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved.
 */

/*
 * debug.c
 *
 *  Created on: 2023年11月22日
 *      Author: xinhao
 */

#include "debug.h"

int debug_init(int case_num)
{
#if DBG_ENABLED
    REG32(DBG_TEST_ADDR) = 0xDDDD0000 + case_num;
    REG32(DBG_CASE_ADDR) = 0x0;
    REG32(DBG_CHECK_ADDR) = 0x0;
    REG32(DBG_STOP_ADDR) = 0x0;
#endif
    return 0;
}

int case_finish(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = CASE_END_CODE;
#endif
    return 0;
}

int debug_finish(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = TEST_END_CODE;
#endif
    return 0;
}

int debug_start(void)
{
#if DBG_ENABLED
    REG32(DBG_TEST_ADDR) = 0;
#endif
    return 0;
}

int debug_stop(void)
{
#if DBG_ENABLED
    REG32(DBG_STOP_ADDR) = DBG_STOP_CODE;
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
#endif
    return 0;
}
