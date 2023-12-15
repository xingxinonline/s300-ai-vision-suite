/*************************************************************************************\
* Copyright (C) CEVA(R) Inc. All rights reserved                                      *
*                                                                                     *
* This information embodies materials and concepts, which are proprietary and         *
* confidential to CEVA Inc., and is made available solely pursuant to the terms       *
* of a written license agreement, or NDA, or another written agreement, as            *
* applicable ("CEVA Agreement"), with CEVA Inc. or any of its subsidiaries ("CEVA").  *
*                                                                                     *
* This information can be used only with the written permission from CEVA, in         *
* accordance with the terms and conditions stipulated in the CEVA Agreement, under    *
* which the information has been supplied and solely as expressly permitted for       *
* the purpose specified in the CEVA Agreement.                                        *
*                                                                                     *
* This information is made available exclusively to licensees or parties that have    *
* received express written authorization from CEVA to download or receive the         *
* information and have agreed to the terms and conditions of the CEVA Agreement.      *
*                                                                                     *
* IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE CEVA          *
* AGREEMENT, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS INFORMATION.                   *
*                                                                                     *
* The information contained in this document is subject to change without notice      *
* and does not represent a commitment on any part of CEVA. Unless specifically        *
* agreed otherwise in the CEVA Agreement, CEVA make no warranty of any kind with      *
* regard to this material, including, but not limited to implied warranties of        *
* merchantability and fitness for a particular purpose whether arising out of law,    *
* custom, conduct or otherwise.                                                       *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA assumes no   *
* responsibility for any errors or omissions contained herein, and assumes no         *
* liability for special, direct, indirect or consequential damage, losses, costs,     *
* charges, claims, demands, fees or expenses, of any nature or kind, which are        *
* incurred in connection with the furnishing, performance or use of this material.    *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may     *
* be reproduced, photocopied, or translated into another language without the prior   *
* written consent of CEVA.                                                            *
\*************************************************************************************/
#ifndef CEVA_TIMERS_H_
#define CEVA_TIMERS_H_
/*********************************************************************************************
 * @module			TIMERS
 * @file			ceva_timers.h
 * @author			Ravid Rzaev
 * @date			09/02/2021
 * @brief			Define the structure, configuration values and function of
					the Timers Programming model registers
**********************************************************************************************/
#include "ceva_hw_conf.h"
#ifdef CSL_TIMERS_SUPPORTED


CSL_CPP_START
#include "ceva_assert.h"



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Timers Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


typedef union
{
	struct // T_TIMERx_CFG Configuration Register
	{
		uint32_t ts 		: 2; // Time Scale: 00 - TIMERx clock is divided by 1, 01 - TIMERx clock is divided by 2,
							 	 // 10 - TIMERx clock is divided by 4, 11 - TIMERx clock is divided by 16
		uint32_t cm 		: 3; // Count Mode
		uint32_t es 		: 1; // Event Source
		uint32_t tp 		: 1; // TIMERx_OUT Polarity
		uint32_t tm 		: 2; // TIMERx_OUT Mode
		uint32_t trest_en 	: 1; // Enables the effect of the TIMERx_REST input bit
		uint32_t cas 		: 1; // Cascade Mode
		uint32_t 			: 5; // reserved
		uint32_t res 		: 1; // Restart
		uint32_t pc 		: 1; // Pause Count - stops the counter
		uint32_t ct 		 :1; // Clear TIMERx_OUT
		uint32_t ru 		: 1; // Read-time Count Update
		uint32_t bpen 		: 1; // DEBUG Enable - places the TIMERx unit in pause when core is in debug mode
		uint32_t			:11; // Reserved
	} fields;
	uint32_t value;
} T_TIMERx_CFG;

typedef union
{
	struct // T_TIMERx_EW Register
	{
		uint32_t ew 		: 1;  // Even count
#ifdef CEVABX
		uint32_t wd_rst_sts : 1;  // Watchdog Reset Status Bit
		uint32_t			:30;  // Reserved
#else
		uint32_t			:31;  // Reserved
#endif
	} fields;
	uint32_t value;
} T_TIMERx_EW;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Timers Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/***********************************************
 * E_timer_cfg_ts
 * 		Register: TIMERx_CFG
 * 		Field: TS
 *		Description: Time Scale - The ratio of counter clock: counter clock = core clock(DIV_1), 2*(core clock) = counter clock
 *                                       4*(core clock) = counter clock,   16*(core clock) = counter clock
 ************************************************/
typedef enum
{
	 TIMER_CFG_TS_CLK_DIV_1  = 0,
	 TIMER_CFG_TS_CLK_DIV_2  = 1,
	 TIMER_CFG_TS_CLK_DIV_4  = 2,
	 TIMER_CFG_TS_CLK_DIV_16 = 3
} E_timer_cfg_ts;


/***********************************************
 * E_timer_cfg_cm
 * 		Register: TIMERx_CFG
 * 		Field: CM
 *		Description: Count Mode
 ************************************************/
typedef enum
{
	TIMER_CFG_CM_SINGLE_COUNT = 0,
	TIMER_CFG_CM_AUTO_RESTART = 1,
	TIMER_CFG_CM_FREE_RUNNING = 2,
	TIMER_CFG_CM_EVENT_COUNT  = 3,
#ifdef CEVABX
	TIMER_CFG_CM_WD_SUB_MODE_ONE  = 4,
	TIMER_CFG_CM_WD_SUB_MODE_TWO  = 5
#endif
} E_timer_cfg_cm;



/***********************************************
 * E_timer_cfg_es
 * 		Register: TIMERx_CFG
 * 		Field: ES
 *		Description: When TIMERx is in Event Count mode, source if one of the bellow
 ************************************************/
typedef enum
{
	TIMER_CFG_ES_INTERNAL_EVENT = 0,
	TIMER_CFG_ES_EXTERNAL_EVENT = 1
}E_timer_cfg_es;


/***********************************************
 * E_timer_cfg_tp
 * 		Register: TIMERx_CFG
 * 		Field: TP
 *		Description: At end of count event, sets the polarity of the TIMERx_OUT signal
 *						ACTIVE_HIGH - TIMERx_OUT signal is low expect for: at the end of count event, TIMERx_OUT is raised (active high)
 *		          		For the number of cycles defined by TIMERx_CFG.TM, afterwards, the signal is low again
 *						ACTIVE_LOW -  TIMERx_OUT signal is high expect for: at the end of count event, TIMERx_OUT is cleared (active low)
 *		          	    for the number of cycles defined by TIMERx_CFG.TM, afterwards, the signal is high again
 ************************************************/
typedef enum
{
    TIMER_CFG_TP_ACTIVE_HIGH = 0,
	TIMER_CFG_TP_ACTIVE_LOW  = 1
}E_timer_cfg_tp;


/***********************************************
 * E_timer_cfg_tm
 * 		Register: TIMERx_CFG
 * 		Field: TM
 *		Description: selects the "active" period of the TIMERx_OUT signal
 ************************************************/
typedef enum
{
   TIMER_CFG_TM_EXPLICIT_CLEAR_TIMER_OUT = 0,	 //TIMERx_OUT signal is active until TIMERx_CFG.CT is set
   TIMER_CFG_TM_CNTR_CLK_CYCLES_2 = 1, //TIMERx_OUT signal is active for 2 counter clock cycles
   TIMER_CFG_TM_CNTR_CLK_CYCLES_4 = 2, //TIMERx_OUT signal is active for 4 counter clock cycles
   TIMER_CFG_TM_CNTR_CLK_CYCLES_8 = 3  //TIMERx_OUT signal is active for 8 counter clock cycles
}E_timer_cfg_tm;


/***********************************************
 * E_timer_cfg_cas
 * 		Register: TIMERx_CFG
 * 		Field: CAS
 *		Description: Selects Cascade mode for Timer configuration
 ************************************************/
typedef enum
{
    TIMER_CFG_CAS_INDEPENTENT_CNT = 0,
	TIMER_CFG_CAS_CASCADE_CNT     = 1
}E_timer_cfg_cas;


/***********************************************
 * E_timer_cfg_ru
 * 		Register: TIMERx_CFG
 * 		Field: RU
 *		Description: Read-time Count Update
 ************************************************/
typedef enum
{
	TIMER_CFG_RU_COUNT_LATCH 	= 0,
	TIMER_CFG_RU_COUNT_UNLATCH  = 1
}E_timer_cfg_ru;

/***********************************************
 * E_timer_cfg_trest_en
 * 		Register: TIMERx_CFG
 * 		Field: TREST_EN
 *		Description: Enables the effect of the TIMERx_REST input bit
 ************************************************/
typedef enum
{
	TIMER_CFG_TREST_EN_NOT_AFFECT = 0,
	TIMER_CFG_TREST_EN_AFFECT     = 1
}E_timer_cfg_trest_en;


/***********************************************
 * E_timer_cfg_res
 * 		Register: TIMERx_CFG
 * 		Field: RES
 *		Description: Restart timer. Clears after one cycle.
 ************************************************/
typedef enum
{
	TIMER_CFG_RES_RESTART = 1
}E_timer_cfg_res;



/***********************************************
 * E_timer_cfg_pc
 * 		Register: TIMERx_CFG
 * 		Field: PC
 *		Description: Pause count.
 ************************************************/
typedef enum
{
	TIMER_CFG_PC_RESUME_COUNT = 0,
	TIMER_CFG_PC_PAUSE_COUNT = 1
}E_timer_cfg_pc;



/***********************************************
 * E_timer_cfg_ct
 * 		Register: TIMERx_CFG
 * 		Field: CT
 *		Description: Clear TIMERx_OUT. Bit clears after one cycle.
 ************************************************/
typedef enum
{
	TIMER_CFG_CT_CLEAR_TIMERX_OUT = 1
}E_timer_cfg_ct;



/***********************************************
 * E_timer_cfg_bpen
 * 		Register: TIMERx_CFG
 * 		Field: BPEN
 *		Description: Stop or Continue in Debug mode
 ************************************************/
typedef enum
{
   TIMER_CFG_BPEN_CONTINUE_IN_DEBUG = 0,
   TIMER_CFG_BPEN_STOP_IN_DEBUG     = 1
}E_timer_cfg_bpen;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Timers Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
 * @function	TIMER_latch
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Latch the given timer.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_latch(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_unlatch
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Unlatch the given timer.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_unlatch(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_allocate32
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Allocates a 32bit width Timer.
 * @param	timer_config: 	Timer configuration.
 * @return	Return the id number of the allocated timer if there is available timer, otherwise an CSL_ALLOCATION_FAILURE is returned.
*********************************************************************************************/
T_csl_allocation_id TIMER_allocate32(T_TIMERx_CFG timer_config ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_allocate64
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Allocates a 64bit width Timer
 * @param	timer_config: 	Timer configuration to allocate timer by.
 * @return	Return the id number of the first allocated timer if there are available timers, otherwise an CSL_ALLOCATION_FAILURE is returned.
*********************************************************************************************/
T_csl_allocation_id TIMER_allocate64(T_TIMERx_CFG timer_config ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_deallocate
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Deallocates timer by an allocated timer id.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_deallocate(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_reset
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Resets the count of a given timer, if timer is already running it is first paused.
 * @param	timer_id: 	Timer allocation ID
 * @param	timer_sc :  The Timer start count value.
 *						For a 32bit width timer only  the 32 LSBs are used.
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_reset(T_csl_allocation_id timer_id, uint64_t timer_sc ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_resume
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Resumes the count of a given timer.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_resume(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_pause
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Pauses the count of a given timer.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_pause(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_progress_counter
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	When timer is in event count mode, use this function to decrease the timer counter for one cycle.
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_progress_counter(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_read32
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Reads the 32 bit value of timer's counter.
 * @param	timer_id: 	 Timer allocation ID
 * @return	32 bit value of timer's counter.
*********************************************************************************************/
uint32_t TIMER_read32(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_read64
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Reads the 64 bit value of timer's counter, this only available for counters in cascade mode.
 * @param	timer_id: 	Timer allocation ID
 * @return	64 bit value of timer's counter.
*********************************************************************************************/
uint64_t TIMER_read64(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
 * @function	TIMER_out_signal_clear
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	When timer is configured with TimerOutMode = CT_SET,
 *			use this function to clear the TIMER_OUT signal
 * @param	timer_id: 	Timer allocation ID
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status TIMER_out_signal_clear(T_csl_allocation_id timer_id ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifdef CEVABX
/*********************************************************************************************
 * @function	TIMER_WD_is_reached_end_of_count
 * @author	Ravid Rzaev
 * @date 	08/02/2021
 * @brief	Return indication if Watchdog end-of-count event has
			occurred.
 * @param	timer_id: 	The timer id.
 * @return	CEVA_TRUE or CEVA_FALSE
*********************************************************************************************/
E_csl_status TIMER_WD_is_reached_end_of_count(T_csl_allocation_id timer_id );

#endif /* CEVABX */


	CSL_CPP_END


#endif /* CSL_TIMERS_SUPPORTED */
#endif /* CEVA_TIMERS_H_ */
