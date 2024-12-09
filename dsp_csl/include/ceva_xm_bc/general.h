/*
 * cevabx_general.h
 *
 *  Created on: Aug 25, 2019
 *      Author: ephif
 */
#ifndef HEADERS_CEVABX_GENERAL_H_
#define HEADERS_CEVABX_GENERAL_H_



#include <stdint.h>
#define CEVA_OCEM_MSS_CONFIG_NUM_TIMER_OFFSET   20
#define CEVA_OCEM_MSS_CONFIG_NUM_TIMER_MSK      (0x3 << CEVA_OCEM_MSS_CONFIG_NUM_TIMER_OFFSET)
#define CEVA_OCEM_MEM_CONFIG_REG                0x158
#define CEVA_OCEM_MSS_CONFIG_REG                0x15c
#define CEVA_OCEM_MSS_CONFIG_NUM_ICU_GRP_OFFSET 16
#define CEVA_OCEM_MSS_CONFIG_NUM_ICU_GRP_MSK    (0xF << CEVA_OCEM_MSS_CONFIG_NUM_ICU_GRP_OFFSET)

#include "ceva_csl_defs.h" 
#include "csl.h"
#include "ceva_csl.h"
#include "ceva_cpm_io.h"
// ==============================   Debug options   ====================================
// =====================================================================================
//
#if DRIVER_DEBUG_PRINT_TO_CONSOLE==1
	#include <stdio.h>
	#define ADD_PRINT(STR1) printf(STR1)
#else
	#define ADD_PRINT(STR1)
#endif

#if DRIVER_DEBUG_TRAP==1
	#define ADD_DEBUG_TRAP \
    asm volatile( "trape\n"\
                  "nop" );
#else
	#define ADD_DEBUG_TRAP
#endif
// debug code is only available in debug library
#ifdef _DEBUG
	#define CEVA_DRIVER_ASSERT(COND,STR) do {if(COND) {\
       ADD_PRINT(STR) ; ADD_DEBUG_TRAP ;} } while(0);
#endif // #ifdef _DEBUG
// debug code is not available in release library
#ifdef _RELEASE
	#define CEVA_DRIVER_ASSERT(COND,STR)
#endif // #ifdef _RELEASE


#define SIM_is_in_simulation() SIM_is_it_simulator();


typedef enum{
	DRIVER_FAIL = 0,
	DRIVER_OK = 1
} T_DriverResult;




#endif /* HEADERS_CEVABX_GENERAL_H_ */
