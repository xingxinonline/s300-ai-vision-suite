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
#ifndef CEVA_PROFILER_H_
#define CEVA_PROFILER_H_
/*********************************************************************************************
 * @module          PROFILER
 * @file            ceva_profiler.h
 * @author          Ravid Rzaev
 * @date            16/03/2021
 * @brief		 	Define the structure, configuration values and function of
					the Profiler counters Programming model registers
**********************************************************************************************/
#include "ceva_assert.h"
#ifdef CEVA
#ifdef SENSPRO
#include "ceva_senspro_memory_map.h"
#elif defined XM6
#include "ceva_xm6_memory_map.h"
#elif defined XM4
#include "ceva_xm4_memory_map.h"
#elif defined CEVABX
#include "ceva_bx_memory_map.h"
#endif
#endif /* CEVA */



CSL_CPP_START


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Profiler counters Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/***********************
 * Name: T_PROF_CTL
 * Register: PROF_CTL
 ***********************/
typedef union
{
	struct
	{
		uint32_t frcc_rst		: 1;
		uint32_t prof_cnt0_rst	: 1;
		uint32_t prof_cnt1_rst	: 1;
		uint32_t prof_cnt2_rst	: 1;
		uint32_t prof_cnt3_rst	: 1;
		uint32_t prof_cnt4_rst	: 1;
		uint32_t prof_cnt5_rst	: 1;
		uint32_t prof_cnt6_rst	: 1;
		uint32_t prof_cnt7_rst	: 1;
		uint32_t            	: 22; //Reserved
		uint32_t nsad          	: 1;
	} fields;
	uint32_t value;
} T_PROF_CTL;

/***********************
 * Name: T_PROF_PAUSE
 * Register: PROF_PAUSE
 ***********************/
typedef union
{
	struct
	{
		uint32_t frcc_pause			: 1;
		uint32_t prof_cnt0_pause	: 1;
		uint32_t prof_cnt1_pause	: 1;
		uint32_t prof_cnt2_pause	: 1;
		uint32_t prof_cnt3_pause	: 1;
		uint32_t prof_cnt4_pause	: 1;
		uint32_t prof_cnt5_pause	: 1;
		uint32_t prof_cnt6_pause	: 1;
		uint32_t prof_cnt7_pause	: 1;
		uint32_t					: 23; //Reserved
	} fields;
	uint32_t value;
} T_PROF_PAUSE;

/***********************
 * Name: T_PROF_CTRL0
 * Register: PROF_CTRL0
 ***********************/
typedef union
{
	struct
	{
		uint32_t prof_cnt0_sel	: 8;
		uint32_t prof_cnt1_sel	: 8;
		uint32_t prof_cnt2_sel	: 8;
		uint32_t prof_cnt3_sel	: 8;
	} fields;
	uint32_t value;
} T_PROF_CTRL0;

/***********************
 * Name: T_PROF_CTRL1
 * Register: PROF_CTRL1
 ***********************/
typedef union
{
	struct
	{
	    uint32_t prof_cnt4_sel	: 8;
	    uint32_t prof_cnt5_sel	: 8;
	    uint32_t prof_cnt6_sel	: 8;
	    uint32_t prof_cnt7_sel	: 8;
	} fields;
	uint32_t value;
} T_PROF_CTRL1;

/***********************
 * Name: T_FRCC
 * Register: FRCC
 ***********************/
typedef union
{
	struct
	{
	    uint32_t frcc	: 32;
	} fields;
	uint32_t value;
} T_FRCC;

/***********************
 * Name: T_PROF_CNTx
 * Register: PROF_CNTx
 ***********************/
typedef struct
{
	uint32_t prof_cntx	: 32;

}T_PROF_CNTx;


/***********************
 * Name: T_PROF_EV_MASKx
 * Register: PROF_EV_MASKx
 ***********************/
typedef union
{
	struct
	{
	uint32_t prof_mf0	:  8;
	uint32_t prof_mf1	:  8;
	uint32_t prof_mf2	:  4;
	uint32_t prof_mf3	:  4;
	uint32_t prof_mf4	:  4;
	uint32_t prof_mf5	:  4;
	} fields;
	uint32_t value;
}T_PROF_EV_MASKx;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Profiler counters Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/
#define PROFILER_ALL_COUNTERS 0x1FF


/********************
 * E_profiler_counters_number
 * Description:  configurable profiling counters
 ********************/
typedef enum {
	PROF_COUNTER_CNT0 = 0,
	PROF_COUNTER_CNT1 = 1,
	PROF_COUNTER_CNT2 = 2,
	PROF_COUNTER_CNT3 = 3,
	PROF_COUNTER_CNT4 = 4,
	PROF_COUNTER_CNT5 = 5,
	PROF_COUNTER_CNT6 = 6,
	PROF_COUNTER_CNT7 = 7
} E_profiler_counter_number;



/********************
 * E_profiler_counters_number
 * Description: vlues for selecting the
 * 				controlled profiling counters
 ********************/
typedef enum {
	PROF_COUNTER_MASK_FRCC = 0x00010001U,
	PROF_COUNTER_MASK_CNT0 = 0x00020002U,
	PROF_COUNTER_MASK_CNT1 = 0x00040004U,
	PROF_COUNTER_MASK_CNT2 = 0x00080008U,
	PROF_COUNTER_MASK_CNT3 = 0x00100010U,
	PROF_COUNTER_MASK_CNT4 = 0x00200020U,
	PROF_COUNTER_MASK_CNT5 = 0x00400040U,
	PROF_COUNTER_MASK_CNT6 = 0x00800080U,
	PROF_COUNTER_MASK_CNT7 = 0x01000100U,
	PROF_COUNTER_MASK_ALL = 0x01ff01ffU
} E_profiler_counter_mask;


/*****************************************************
 * E_profiler_control_values
 *		Description: Profiler events control values
 *****************************************************/
typedef enum
{
	PROFILER_SECOND_SECTION_OF_EVENTS		 = 4,
	PROFILER_EVENT_SHIFT 					 = 8
} E_profiler_control_values;


#if defined(SENSPRO) || defined(CEVABX)


/*****************************************************
 * E_profiler_branch_configurations
 * 		Register: PROF_EV_MASKx
 *		Description: Profiling configurations of branch and
 *					 btb events
 *****************************************************/
typedef enum {
	//Branch Distribution Profiling Groups
	PROF_TOTAL_BRANCHES 												= 0x00000000,
	PROF_TOTAL_LOOP_BRANCHES 											= 0x00000004,
	PROF_TOTAL_NON_LOOP_BTB_BRANCHES 									= 0x0000003A,
	PROF_TOTAL_NON_BTB_BRANCHES 										= 0x00000001,
	PROF_TOTAL_CALL_BRANCHES 											= 0x00000028,
	//Branch Prediction Summary Groups
	PROF_CORRECTLY_PREDICTATED_LOOPS_BRANCHES							= 0x00000404,
	PROF_INCORRECTLY_PREDICTATED_LOOPS_BRANCHES							= 0x00000804,
	PROF_CORRECTLY_PREDICTATED_NON_LOOPS_BTB_BRANCHES					= 0x0000043A,
	PROF_INCORRECTLY_PREDICTATED_NON_LOOPS_BTB_BRANCHES					= 0x0000083A,
	PROF_CORRECTLY_PREDICTATED_NON_LOOPS_CONDITIONAL_BRANCHES			= 0x0001043B,
	PROF_INCORRECTLY_PREDICTATED_NON_LOOPS_CONDITIONAL_BRANCHES			= 0x0001083B,
	//BTB Performance Profiling Groups
	PROF_TOTAL_BTB_HITS 												= 0x00000100,
	PROF_TOTAL_BTB_MISSES 												= 0x00000200,
	PROF_TOTAL_BTB_HITS_CORRECTLY_PREDICATED							= 0x00000500,
	PROF_TOTAL_BTB_HITS_INCORRECTLY_PREDICATED							= 0x00000900,
	PROF_TOTAL_NON_LOOP_BTB_HITS_CORRECTLY_PREDICATED					= 0x0000053A,
	PROF_TOTAL_NON_LOOP_BTB_HITS_INCORRECTLY_PREDICATED					= 0x0000093A,
	//Loop Performance Summary Groups
	PROF_TOTAL_LOOP_BRANCHES_TAKEN										= 0x00100004,
	PROF_TOTAL_LOOP_BRANCHES_BTB_HITS									= 0x00000104,
	PROF_TOTAL_LOOP_BRANCHES_BTB_MISSES									= 0x00000204,
	//Non-Loop BTB Performance Profiling Groups
	PROF_TOTAL_BTB_BRANCHES_TAKEN										= 0x0010003A,
	PROF_TOTAL_BTB_BRANCHES_BTB_HITS									= 0x0000013A,
	PROF_TOTAL_BTB_BRANCHES_BTB_MISSES									= 0x0000023A
} E_profiler_branch_configurations;

#endif // defined(SENSPRO) || defined(BX)

#ifdef SENSPRO

	/*****************************************************
	 * E_prof_ctrl_prof_cnt_sel
	 * 		Register: PROF_CTRL0 / PROF_CTRL1
	 * 		Field: PROF_CNTx_SEL
	 *		Description: Profiler Events
	 *****************************************************/
	typedef enum
	{
		PROF_COUNTER_EVENT_FIRST_EVENT 				= 1, /**<  The value of the first event */
		PROF_COUNTER_EVENT_FRCC 					= 1, /**<  Light sleep counter. */
		PROF_COUNTER_EVENT_CORE_LS 					= 4, /**<  Light sleep counter. */
		PROF_COUNTER_EVENT_LD_LS0_NC_CNT			= 5, /**<  Core ls0 Non-Cache/write-through Load counter. */
		PROF_COUNTER_EVENT_LD_LS1_NC_CNT			= 6, /**<  Core ls1 Non-Cache/write-through Load counter. */
		PROF_COUNTER_EVENT_LD_LS0_TCM_CNT			= 7, /**<  LS0 TCM Load counter */
		PROF_COUNTER_EVENT_LD_LS1_TCM_CNT			= 8, /**<  LS1 TCM Load counter */
		PROF_COUNTER_EVENT_ST_NC_CNT				= 14, /**<  LS1 Cache Store counter */
		PROF_COUNTER_EVENT_ST_TCM_CNT				= 16, /**<  LS1 TCM Store counter */
		PROF_COUNTER_EVENT_TDRC						= 17, /**<  Read Strobe Cycles counter */
		PROF_COUNTER_EVENT_TDWC						= 18, /**<  Write Strobe Cycles counter */
		PROF_COUNTER_EVENT_EDP_W_MAX_OS				= 23, /**<  Bus wait cycles due to reaching the max outstanding write burst on EDP */
		PROF_COUNTER_EVENT_AXIM0_W_MAX_OS			= 24, /**<  Bus wait cycles due to reaching the max outstanding write burst on AXIM0 */
		PROF_COUNTER_EVENT_AXIM1_W_MAX_OS			= 25, /**<  Bus wait cycles due to reaching the max outstanding write burst on AXIM1 */
		PROF_COUNTER_EVENT_EDP_WB_PRAW_BF			= 27, /**<  Cycles that the write buffer is blocked due to PRAW buffer full on EDP port */
		PROF_COUNTER_EVENT_EPP_R_CNT				= 32, /**<  EPP burst read counter.  */
		PROF_COUNTER_EVENT_EDP_R_CNT				= 33, /**<  EDP burst read counter.  */
		PROF_COUNTER_EVENT_AXIM0_R_CNT				= 34, /**<  AXIM0 burst read counter.  */
		PROF_COUNTER_EVENT_AXIM1_R_CNT				= 35, /**<  AXIM1 burst read counter.  */
		PROF_COUNTER_EVENT_EDP_W_CNT				= 36, /**<  EDP burst finish write counter.  */
		PROF_COUNTER_EVENT_AXIM0_W_CNT				= 37, /**<  AXIM0 burst finish write counter.  */
		PROF_COUNTER_EVENT_AXIM1_W_CNT				= 38, /**<  AXIM1 burst finish write counter.  */
		PROF_COUNTER_EVENT_EDP_PRAW_LS_WAIT			= 49, /**<  Core wait cycles due to LS0/1 load addresses in EDP counter.  */
		PROF_COUNTER_EVENT_EDAP_R_CNT				= 51, /**<  EDAP burst read counter.  */
		PROF_COUNTER_EVENT_AXIS0_R_CNT				= 52, /**<  AXIs0 burst read counter.  */
		PROF_COUNTER_EVENT_AXIS1_R_CNT				= 53, /**<  AXIs1 burst read counter.  */
		PROF_COUNTER_EVENT_AXIS2_R_CNT				= 54, /**<  AXIs2 burst read counter.  */
		PROF_COUNTER_EVENT_EDAP_W_CNT				= 55, /**<  EDAP burst write counter.  */
		PROF_COUNTER_EVENT_AXIS0_W_CNT				= 56, /**<  AXIs0 burst write counter.  */
		PROF_COUNTER_EVENT_AXIS1_W_CNT				= 57, /**<  AXIs1 burst write counter.  */
		PROF_COUNTER_EVENT_AXIS2_W_CNT				= 58, /**<  AXIs2 burst write counter.  */
		PROF_COUNTER_EVENT_PMSS_HIT_CNT				= 64, /**<  PMSS cache hit counter.  */
		PROF_COUNTER_EVENT_PMSS_MISS_CNT			= 65, /**<  PMSS cache miss counter. */
		PROF_COUNTER_EVENT_PMSS_NC_CNT				= 66, /**<  PMSS load access not cachable counter. */
		PROF_COUNTER_EVENT_PMSS_TCM_CNT				= 67, /**<  PMSS TCM read counter */
		PROF_COUNTER_EVENT_PMSS_ECCCOR_CNT			= 69, /**<  PTCM ECC correctable counter */
		PROF_COUNTER_EVENT_PMSS_RR_CNT				= 70,
		PROF_COUNTER_EVENT_PMSS_CLB_HIT				= 71,
		PROF_COUNTER_EVENT_WAIT_CNT					= 80,
		PROF_COUNTER_EVENT_DC_EDP_RD_WAIT			= 83,
		PROF_COUNTER_EVENT_DC_AXIM0_RD_WAIT			= 84,
		PROF_COUNTER_EVENT_DC_AXIM1_RD_WAIT			= 85,
		PROF_COUNTER_EVENT_TCM_RD_WAIT				= 86,
		PROF_COUNTER_EVENT_ST_BUF_FULL				= 87,
		PROF_COUNTER_EVENT_RAW_WAIT					= 88, /**<  Waits due to RAW counter */
		PROF_COUNTER_EVENT_PSEQ_WAIT				= 90,
		PROF_COUNTER_EVENT_PCU_COF_WAIT				= 92,
		PROF_COUNTER_EVENT_NOP_PACKET				= 94,
		PROF_COUNTER_EVENT_BR_TO_ISR				= 95, /**<  Branch to ISR counter */
		PROF_COUNTER_EVENT_RET_FROM_ISR				= 96, /**<  Return from ISR counter */
		PROF_COUNTER_EVENT_ISR_CYCLE_CNT			= 97, /**<  Non-wait cycles in ISR counter */
		PROF_COUNTER_EVENT_REP_CNT					= 98, /**<  Foldback events in SL counter*/
		PROF_COUNTER_EVENT_REP_INST_CNT				= 99, /**<  SL packet instructions counter*/
		PROF_COUNTER_EVENT_REP_INST_LP_BUFF_CNT		= 100, /**<  SL packet instructions from loop buffer counter*/
		PROF_COUNTER_EVENT_BR_BTB_CNT				= 105, /**<  Branches and BTB event group counter*/
		PROF_COUNTER_EVENT_CORE_BUBBLES_CNT			= 106, /**<  Core bubbles event group counter*/
	#ifdef 	SENSPRO_V1_1
		PROF_COUNTER_EVENT_LAST_EVENT				= PROF_COUNTER_EVENT_CORE_BUBBLES_CNT
	#else /* SENSPRO_V1_2 */
		PROF_COUNTER_EVENT_VLD_LS0_INST_EXT			= 119, /**<  Core bubbles event group counter*/
		#ifdef SENSPRO1000
		PROF_COUNTER_EVENT_VLD_LS1_INST_EXT			= 120, /**<  Vector load instructions from LS1 going to the external memory; includes vld and vpop. Applicable only in SP1000.*/
		#endif /* SENSPRO1000 */
		PROF_COUNTER_EVENT_VST_INST_EXT				= 121, /**<  Vector store instructions going to the external memory*/
		PROF_COUNTER_EVENT_VPLD_STALL_CYC			= 122, /**<  Vector parallel load (vpld) absolute bank contention cycle.*/
		PROF_COUNTER_EVENT_VPST_STALL_CYC			= 123, /**<  Vector parallel store (vpld) absolute bank contention cycle.*/
		PROF_COUNTER_EVENT_IDM_CONT_CYC_ALL			= 124, /**<  IDM memory bank contention stall cycle*/
		PROF_COUNTER_EVENT_IDM_CONT_CYC_DMA			= 125, /**<  IDM memory bank contention stall cycle*/
		PROF_COUNTER_EVENT_VLD_NALGN_CYC			= 126, /**<  vld non-alignment stall cycle*/
		PROF_COUNTER_EVENT_VST_NALGN_CYC			= 127, /**<  vst non-alignment stall cycle*/
		PROF_COUNTER_EVENT_LAST_EVENT				= PROF_COUNTER_EVENT_VST_NALGN_CYC
	#endif /* SENSPRO_V1_2 */
	} E_prof_counter_event;






	/*****************************************************
	 * E_profiler_std_branch_distribution
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling branch distribution profiling groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BRANCHES,
		TOTAL_LOOP_INSTRUCTIONS,
		TOTAL_NON_LOOP_BTBABLE_BRANCHES,
		TOTAL_NON_BTBABLE_BRANCHES,
		TOTAL_CALL_BRANCHES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BRANCH_DISTRIBUTION_GROUP_CONFIGURATIONS = 5
	}  E_profiler_std_branch_distribution;


	/*****************************************************
	 * E_profiler_std_branch_predication_summary
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling branch predication summary profiling groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_PREDICATED_BRANCHES = 0,
		CORRECTLY_PREDICATED_LOOPS,
		INCORRECTLY_PREDICATED_LOOPS,
		CORRECTLY_PREDICATED_NON_LOOP_BTBABLE_BRANCHES,
		INCORRECTLY_PREDICATED_NON_LOOP_BTBABLE_BRANCHES,
		CORRECTLY_PREDICATED_NON_LOOP_CONDITIONAL_BRANCHES,
		INCORRECTLY_PREDICATED_NON_LOOP_CONDITIONAL_BRANCHES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BRANCH_PREDICATION_SUMMARY_GROUP_CONFIGURATIONS = 7
	} E_profiler_std_branch_predication_summary;


	/*****************************************************
	 * E_profiler_std_btb_performance
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended btb performance groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BTB_HITS = 0,
		TOTAL_BTB_MISSES,
		TOTAL_BTB_HITS_CORRECTLY_PREDICATED,
		TOTAL_BTB_HITS_INCORRECTLY_PREDICATED,
		TOTAL_NON_LOOP_BTB_HITS_CORRECTLY_PREDICATED,
		TOTAL_NON_LOOP_BTB_HITS_INCORRECTLY_PREDICATED,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BTB_PERFORMANCE_GROUP_CONFIGURATAIONS = 6
	} E_profiler_std_btb_performance;

	/*****************************************************
	 * E_profiler_std_loop_performance_summary
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended loop performance summary groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_LOOP_ITERATIONS = 0,
		TOTAL_LOOP_ITERATIONS_TAKEN,
		TOTAL_LOOP_ITERATIONS_PREDICATED_CORRECTLY,
		TOTAL_LOOP_INSTRUCTIONS_BTB_HITS,
		TOTAL_LOOP_INSTRUCTIONS_BTB_MISSES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_LOOP_PERFORMANCE_SUMMARY_GROUP_CONFIGURATIONS = 5
	}E_profiler_std_loop_performance_summary;

	/*****************************************************
	 * E_profiler_std_non_loop_btb_able_performance
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended non loop btb performance groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BTBABLE_BRANCH_EVENTS = 0,
		TOTAL_BTBABLE_BRANCHES_TAKEN,
		TOTAL_BTBABLE_BRANCHES_PREDICATED_CORRECTLY,
		TOTAL_BTBABLE_BRANCHES_BTB_HITS,
		TOTAL_BTBABLE_BRANCHES_BTB_MISSES,
		TOTAL_BTBABLE_BRANCHES_BTB_HIT_CORRECTLY_PREDICATED,
		TOTAL_BTBABLE_BRANCHES_BTB_HIT_INCORRECTLY_PREDICATED,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_NON_LOOP_BTB_ABLE_PERFORMANCE_GROUP_CONFIGURATIONS = 7
	}E_profiler_std_non_loop_btb_able_performance;




	/*****************************************************
	 * T_profiler_branch_event_mask_attributes
	 * Description: supported attributes of the branch event, and the mapping to the
	 *				MFx fields and mask bits in PROF_EV_MASKx register.
	 *****************************************************/
	typedef union
	{
		struct
		{
			union
			{
				struct
				{
					uint32_t non_btb_able 			:1;
					uint32_t btb_able 				:1;
					uint32_t loop_branch 			:1;
					uint32_t call 					:1;
					uint32_t ret 					:1;
					uint32_t calls 					:1;
					uint32_t 						:2; // Reserved
				};
				uint32_t : 8;
			} branch_type;

			union
			{
				struct
				{
					uint32_t btb_hit 				:1;
					uint32_t btb_miss 				:1;
					uint32_t correct_btb_hits		:1;
					uint32_t incorrect_btb_misses 	:1;
					uint32_t 						:4; // Reserved
				};
				uint32_t : 8;
			} btb_statistics;

			union
			{
				struct
				{
					uint32_t conditional 			:1;
					uint32_t non_conditional 		:1;
					uint32_t						:2; // Reserved
					uint32_t taken 					:1;
					uint32_t not_taken 				:1;
					uint32_t 						:2; // Reserved
				};
				uint32_t : 8;
			} branch_condition_and_outcome;
			uint32_t :8;
		};
		uint32_t value;
	} T_profiler_branch_event_mask_attributes;


	/*****************************************************
	 * T_profiler_core_bubbles_mask_attributes
	 * Description: attribute mapping of the core bubble attributed event in
	 * 				MFx fields in PROF_EV_MASKx register.
	 *****************************************************/
	typedef union
	{
		struct
		{
			uint32_t cond_branch_to_uncond_branch_bubbles 	: 1;
			uint32_t func_call_and_ret_bubbles 			 	: 1;
			uint32_t predicate_calc_to_use_bubbles 		 	: 1;
			uint32_t ld_to_ld_or_st_bubbles				 	: 1;
			uint32_t calc_to_brrcmp_bubbles				 	: 1;
			uint32_t ld_to_execute_bubbles				 	: 1;
			uint32_t 										:26;	// Reserved
		};
		uint32_t value;
	} T_profiler_core_bubbles_mask_attributes;


#elif defined XM6

	typedef enum {
		PROF_COUNTER_EVENT_FIRST_EVENT 				= 1,	/**<  The value of the first event */
		PROF_COUNTER_EVENT_WAIT_CNT 				= 1,	/**<  Wait counter.*/
		PROF_COUNTER_EVENT_DBLK_CONF_CNT			= 3,	/**<  DMSS block conflict counter. */
		PROF_COUNTER_EVENT_OSFC						= 4,	/**<  Output stage full counter. */
		PROF_COUNTER_EVENT_TDRC						= 5,	/**<  TCM DMSS read counter.  */
		PROF_COUNTER_EVENT_DATA_INT_READ_CNT		= PROF_COUNTER_EVENT_TDRC, 	/**<  Data internal read counter (alias for TDRC). */
		PROF_COUNTER_EVENT_TDWC						= 6,	/**<  TCM DMSS write counter. */
		PROF_COUNTER_EVENT_DATA_INT_WRITE_CNT		= PROF_COUNTER_EVENT_TDWC,  	/**<  Data internal write counter (alias for TDWC). */
		PROF_COUNTER_EVENT_ERWC						= 7,	/**<  EDP read wait counter.  */
		PROF_COUNTER_EVENT_PMSS_HIT_CNT				= 17,	/**<  PMSS cache hit counter.  */
		PROF_COUNTER_EVENT_PMSS_MISS_CNT			= 18,	/**<  PMSS cache miss counter. */
		PROF_COUNTER_EVENT_PWCWC					= 19,	/**<  Parallel write contention wait counter. */
		PROF_COUNTER_EVENT_NOP_PACKET				= 28,	/**<  NOP packet. */
		PROF_COUNTER_EVENT_BRANCH_BTB				= 29,	/**<  Branch and BTB event group. */
		PROF_COUNTER_EVENT_DATA_EXT_WRITE_CNT		= 30,  	/**<  Data external write counter. */
		PROF_COUNTER_EVENT_DATA_EXT_READ_CNT		= 31,  	/**<  Data external read counter. */
		PROF_COUNTER_EVENT_LAST_EVENT						= PROF_COUNTER_EVENT_DATA_EXT_READ_CNT
	} E_prof_counter_event;

#elif defined XM4

	typedef enum {
		PROF_COUNTER_EVENT_FIRST_EVENT 	= 0,	/**<  The value of the first event */
		PROF_COUNTER_EVENT_WAIT_CNT 	= 0,	/**<  Wait counter.*/
		PROF_COUNTER_EVENT_VPU_STL_CNT,   /**<  VPU stall counter. */
		PROF_COUNTER_EVENT_DBLK_CONF_CNT, /**<  DMSS block conflict counter. */
		PROF_COUNTER_EVENT_OSFC,          /**<  Output stage full counter. */
		PROF_COUNTER_EVENT_TDRC,          /**<  TCM DMSS read counter.  */
		PROF_COUNTER_EVENT_TDWC,          /**<  TCM DMSS write counter. */
		PROF_COUNTER_EVENT_ERWC,          /**<  EDP read wait counter.  */
		PROF_COUNTER_EVENT_VPU0_NOP_INST, /**<  VPU0 nop instruction. */
		PROF_COUNTER_EVENT_VPU1_NOP_INST, /**<  VPU1 nop instruction. */
		PROF_COUNTER_EVENT_PCU_NOP_INST,  /**<  PCU  nop instruction.  */
		PROF_COUNTER_EVENT_SPU0_NOP_INST, /**<  SPU0 nop instruction. */
		PROF_COUNTER_EVENT_SPU1_NOP_INST, /**<  SPU1 nop instruction. */
		PROF_COUNTER_EVENT_SPU2_NOP_INST, /**<  SPU2 nop instruction. */
		PROF_COUNTER_EVENT_SPU3_NOP_INST, /**<  SPU3 nop instruction. */
		PROF_COUNTER_EVENT_LSU0_NOP_INST, /**<  LSU0 nop instruction. */
		PROF_COUNTER_EVENT_LSU1_NOP_INST, /**<  LSU1 nop instruction. */
		PROF_COUNTER_EVENT_PMSS_HIT_CNT,  /**<  PMSS hit counter.  */
		PROF_COUNTER_EVENT_PMSS_MISS_CNT,  /**<  PMSS miss counter. */
		PROF_COUNTER_EVENT_PWCWC,         /**<  Parallel write contention wait counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT0,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT1,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT2,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT3,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT4,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT5,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT6,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_P_ADD_COUNT7,    /**<  Program address range counter. */
		PROF_COUNTER_EVENT_LAST_EVENT		= PROF_COUNTER_EVENT_P_ADD_COUNT7
	} E_prof_counter_event;


#elif defined CEVABX

	/*****************************************************
	 * E_prof_counter_event
	 * 		Register: PROF_CTRL0 / PROF_CTRL1
	 * 		Field: PROF_CNTx_SEL
	 *		Description: Profiler Events
	 *****************************************************/
	typedef enum
	{
		PROF_COUNTER_EVENT_FIRST_EVENT 					= 1,             /**<  The value of the first event */
		PROF_COUNTER_EVENT_DC_ACCESS 					= 1, /**<  Light sleep counter. */
		PROF_COUNTER_EVENT_DC_CACHE_MISS				= 3,  /**<  Light sleep counter. */
		PROF_COUNTER_EVENT_CORE_LS						= 4, /**<  Light sleep counter. */
		PROF_COUNTER_EVENT_LD_LS0_NC_CNT				= 5, /**<  Core ls0 Non-Cache/write-through Load counter. */
		PROF_COUNTER_EVENT_LD_LS0_TCM_CNT				= 7, /**<  LS0 TCM Load counter */
		PROF_COUNTER_EVENT_ST_NC_CNT					= 14, /**<  LS1 Cache Store counter */
		PROF_COUNTER_EVENT_ST_TCM_CNT					= 16, /**<  LS1 TCM Store counter */
		PROF_COUNTER_EVENT_TDRC							= 17, /**<  Read Strobe Cycles counter */
		PROF_COUNTER_EVENT_TDWC							= 18, /**<  Write Strobe Cycles counter */
		PROF_COUNTER_EVENT_DC_EVICT_CNT					= 19, /**<  Number of cache-lines evicted from data cache */
		PROF_COUNTER_EVENT_EDP_W_MAX_OS					= 23, /**<  Bus wait cycles due to reaching the max outstanding write burst on EDP */
		PROF_COUNTER_EVENT_AXIM0_W_MAX_OS				= 24, /**<  Bus wait cycles due to reaching the max outstanding write burst on AXIM0 */
		PROF_COUNTER_EVENT_AXIM1_W_MAX_OS				= 25, /**<  Bus wait cycles due to reaching the max outstanding write burst on AXIM1 */
		PROF_COUNTER_EVENT_EDP_EWB_PRAW_BF				= 26, /**<  Cycles that the Eviction Write Buffer is blocked due to PRAW buffer full on EDP port */
		PROF_COUNTER_EVENT_EDP_WB_PRAW_BF				= 27, /**<  Cycles that the write buffer is blocked due to PRAW buffer full on EDP port */
		PROF_COUNTER_EVENT_EWB_FULL_CNT					= 28, /**<  Cycles that Eviction Write Buffer is full */
		PROF_COUNTER_EVENT_EPP_R_CNT					= 32, /**<  EPP burst read counter.  */
		PROF_COUNTER_EVENT_EDP_R_CNT					= 33, /**<  EDP burst read counter.  */
		PROF_COUNTER_EVENT_AXIM0_R_CNT					= 34, /**<  AXIM0 burst read counter.  */
		PROF_COUNTER_EVENT_AXIM1_R_CNT					= 35, /**<  AXIM1 burst read counter.  */
		PROF_COUNTER_EVENT_EDP_W_CNT					= 36, /**<  EDP burst finish write counter.  */
		PROF_COUNTER_EVENT_AXIM0_W_CNT					= 37, /**<  AXIM0 burst finish write counter.  */
		PROF_COUNTER_EVENT_AXIM1_W_CNT					= 38, /**<  AXIM1 burst finish write counter.  */
		PROF_COUNTER_EVENT_EDP_R_ISS_CNT				= 39, /**<  EDP burst read counter.  */
		PROF_COUNTER_EVENT_AXIM0_R_ISS_CNT				= 40, /**<  AXIM0 burst read counter.  */
		PROF_COUNTER_EVENT_AXIM1_R_ISS_CNT				= 41, /**<  AXIM1 burst read counter.  */
		PROF_COUNTER_EVENT_EDP_W_ISS_CNT				= 42, /**<  EDP burst issued write counter.  */
		PROF_COUNTER_EVENT_AXIM0_W_ISS_CNT				= 43, /**<  AXIM0 burst issued write counter.  */
		PROF_COUNTER_EVENT_AXIM1_W_ISS_CNT				= 44, /**<  AXIM1 burst issued write counter.  */
		PROF_COUNTER_EVENT_EDP_PRAW_LS_WAIT				= 49, /**<  Core wait cycles due to LS0/1 load addresses in EDP counter.  */
		PROF_COUNTER_EVENT_EDP_PRAW_L1DC_WAIT			= 50, /**<  Core wait-cycles due to data cache block fill address matching any outstanding store addresses in PRAW buffer in EDP.  */
		PROF_COUNTER_EVENT_EDAP_R_CNT					= 51, /**<  EDAP burst read counter.  */
		PROF_COUNTER_EVENT_AXIS0_R_CNT					= 52, /**<  AXIs0 burst read counter.  */
		PROF_COUNTER_EVENT_AXIS1_R_CNT					= 53, /**<  AXIs1 burst read counter.  */
		PROF_COUNTER_EVENT_AXIS2_R_CNT					= 54, /**<  AXIs2 burst read counter.  */
		PROF_COUNTER_EVENT_EDAP_W_CNT					= 55, /**<  EDAP burst write counter.  */
		PROF_COUNTER_EVENT_AXIS0_W_CNT					= 56, /**<  AXIs0 burst write counter.  */
		PROF_COUNTER_EVENT_AXIS1_W_CNT					= 57, /**<  AXIs1 burst write counter.  */
		PROF_COUNTER_EVENT_AXIS2_W_CNT					= 58, /**<  AXIs2 burst write counter.  */
		PROF_COUNTER_EVENT_PMSS_HIT_CNT					= 64, /**<  PMSS cache hit counter.  */
		PROF_COUNTER_EVENT_PMSS_MISS_CNT				= 65, /**<  PMSS cache miss counter. */
		PROF_COUNTER_EVENT_PMSS_NC_CNT					= 66, /**<  PMSS load access not cachable counter. */
		PROF_COUNTER_EVENT_PMSS_TCM_CNT					= 67, /**<  PMSS TCM read counter */
		PROF_COUNTER_EVENT_PMSS_ECCCOR_CNT				= 69, /**<  PTCM ECC correctable counter */
		PROF_COUNTER_EVENT_PMSS_RR_CNT					= 70,
		PROF_COUNTER_EVENT_PMSS_CLB_HIT					= 71,
		PROF_COUNTER_EVENT_WAIT_CNT						= 80,
		PROF_COUNTER_EVENT_DC_RD_MISS_WAIT				= 81,
		PROF_COUNTER_EVENT_DC_RD_CONT_WAIT				= 82,
		PROF_COUNTER_EVENT_DC_EDP_RD_WAIT				= 83,
		PROF_COUNTER_EVENT_DC_AXIM0_RD_WAIT				= 84,
		PROF_COUNTER_EVENT_DC_AXIM1_RD_WAIT				= 85,
		PROF_COUNTER_EVENT_TCM_RD_WAIT					= 86,
		PROF_COUNTER_EVENT_ST_BUF_FULL					= 87,
		PROF_COUNTER_EVENT_RAW_WAIT						= 88, /**<  Waits due to RAW counter */
		PROF_COUNTER_EVENT_PSEQ_WAIT					= 90,
		PROF_COUNTER_EVENT_PCU_COF_WAIT					= 92,
		PROF_COUNTER_EVENT_NOP_PACKET					= 94,
		PROF_COUNTER_EVENT_BR_TO_ISR					= 95, /**<  Branch to ISR counter */
		PROF_COUNTER_EVENT_RET_FROM_ISR					= 96, /**<  Return from ISR counter */
		PROF_COUNTER_EVENT_ISR_CYCLE_CNT				= 97, /**<  Non-wait cycles in ISR counter */
		PROF_COUNTER_EVENT_REP_CNT						= 98, /**<  Foldback events in SL counter*/
		PROF_COUNTER_EVENT_REP_INST_CNT					= 99, /**<  SL packet instructions counter*/
		PROF_COUNTER_EVENT_REP_INST_LP_BUFF_CNT			= 100, /**<  SL packet instructions from loop buffer counter*/
		PROF_COUNTER_EVENT_BR_BTB_CNT					= 105, /**<  Branches and BTB event group counter*/
		PROF_COUNTER_EVENT_CORE_BUBBLES_CNT				= 106, /**<  Core bubbles event group counter*/
		PROF_COUNTER_EVENT_LAST_EVENT					= PROF_COUNTER_EVENT_CORE_BUBBLES_CNT
	} E_prof_counter_event;





	/*****************************************************
	 * E_profiler_std_branch_distribution
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling branch distribution profiling groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BRANCHES,
		TOTAL_LOOP_INSTRUCTIONS,
		TOTAL_NON_LOOP_BTBABLE_BRANCHES,
		TOTAL_NON_BTBABLE_BRANCHES,
		TOTAL_CALL_BRANCHES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BRANCH_DISTRIBUTION_GROUP_CONFIGURATIONS = 5
	}  E_profiler_std_branch_distribution;


	/*****************************************************
	 * E_profiler_std_branch_predication_summary
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling branch predication summary profiling groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_PREDICATED_BRANCHES = 0,
		CORRECTLY_PREDICATED_LOOPS,
		INCORRECTLY_PREDICATED_LOOPS,
		CORRECTLY_PREDICATED_NON_LOOP_BTBABLE_BRANCHES,
		INCORRECTLY_PREDICATED_NON_LOOP_BTBABLE_BRANCHES,
		CORRECTLY_PREDICATED_NON_LOOP_CONDITIONAL_BRANCHES,
		INCORRECTLY_PREDICATED_NON_LOOP_CONDITIONAL_BRANCHES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BRANCH_PREDICATION_SUMMARY_GROUP_CONFIGURATIONS = 7
	} E_profiler_std_branch_predication_summary;


	/*****************************************************
	 * E_profiler_std_btb_performance
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended btb performance groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BTB_HITS = 0,
		TOTAL_BTB_MISSES,
		TOTAL_BTB_HITS_CORRECTLY_PREDICATED,
		TOTAL_BTB_HITS_INCORRECTLY_PREDICATED,
		TOTAL_NON_LOOP_BTB_HITS_CORRECTLY_PREDICATED,
		TOTAL_NON_LOOP_BTB_HITS_INCORRECTLY_PREDICATED,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_BTB_PERFORMANCE_GROUP_CONFIGURATAIONS = 6
	} E_profiler_std_btb_performance;

	/*****************************************************
	 * E_profiler_std_loop_performance_summary
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended loop performance summary groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_LOOP_ITERATIONS = 0,
		TOTAL_LOOP_ITERATIONS_TAKEN,
		TOTAL_LOOP_ITERATIONS_PREDICATED_CORRECTLY,
		TOTAL_LOOP_INSTRUCTIONS_BTB_HITS,
		TOTAL_LOOP_INSTRUCTIONS_BTB_MISSES,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_LOOP_PERFORMANCE_SUMMARY_GROUP_CONFIGURATIONS = 5
	}E_profiler_std_loop_performance_summary;

	/*****************************************************
	 * E_profiler_std_non_loop_btb_able_performance
	 * 		Register: PROF_EV_MASKx
	 *		Description: Profiling recommended non loop btb performance groups
	 *****************************************************/
	typedef enum
	{
		TOTAL_BTBABLE_BRANCH_EVENTS = 0,
		TOTAL_BTBABLE_BRANCHES_TAKEN,
		TOTAL_BTBABLE_BRANCHES_PREDICATED_CORRECTLY,
		TOTAL_BTBABLE_BRANCHES_BTB_HITS,
		TOTAL_BTBABLE_BRANCHES_BTB_MISSES,
		TOTAL_BTBABLE_BRANCHES_BTB_HIT_CORRECTLY_PREDICATED,
		TOTAL_BTBABLE_BRANCHES_BTB_HIT_INCORRECTLY_PREDICATED,
		TOTAL_SIZE_OF_PROFILER_RECOMMENDED_NON_LOOP_BTB_ABLE_PERFORMANCE_GROUP_CONFIGURATIONS = 7
	}E_profiler_std_non_loop_btb_able_performance;




	/*****************************************************
	 * T_profiler_branch_event_mask_attributes
	 * Description: supported attributes of the branch event, and the mapping to the
	 *				MFx fields and mask bits in PROF_EV_MASKx register.
	 *****************************************************/
	typedef union
	{
		struct
		{
			union
			{
				struct
				{
					uint32_t non_btb_able 			:1;
					uint32_t btb_able 				:1;
					uint32_t loop_branch 			:1;
					uint32_t call 					:1;
					uint32_t ret 					:1;
					uint32_t calls 					:1;
					uint32_t 						:2; // Reserved
				};
				uint32_t : 8;
			} branch_type;

			union
			{
				struct
				{
					uint32_t btb_hit 				:1;
					uint32_t btb_miss 				:1;
					uint32_t correct_btb_hits		:1;
					uint32_t incorrect_btb_misses 	:1;
					uint32_t 						:4; // Reserved
				};
				uint32_t : 8;
			} btb_statistics;

			union
			{
				struct
				{
					uint32_t conditional 			:1;
					uint32_t non_conditional 		:1;
					uint32_t						:2; // Reserved
					uint32_t taken 					:1;
					uint32_t not_taken 				:1;
					uint32_t 						:2; // Reserved
				};
				uint32_t : 8;
			} branch_condition_and_outcome;
			uint32_t :8;
		};
		uint32_t value;
	} T_profiler_branch_event_mask_attributes;


	/*****************************************************
	 * T_profiler_core_bubbles_mask_attributes
	 * Description: attribute mapping of the core bubble attributed event in
	 * 				MFx fields in PROF_EV_MASKx register.
	 *****************************************************/
	typedef union
	{
		struct
		{
			uint32_t cond_branch_to_uncond_branch_bubbles 	: 1;
			uint32_t func_call_and_ret_bubbles 			 	: 1;
			uint32_t predicate_calc_to_use_bubbles 		 	: 1;
			uint32_t ld_to_ld_or_st_bubbles				 	: 1;
			uint32_t calc_to_brrcmp_bubbles				 	: 1;
			uint32_t ld_to_execute_bubbles				 	: 1;
			uint32_t 										:26;	// Reserved
		};
		uint32_t value;
	} T_profiler_core_bubbles_mask_attributes;

#endif /* SENSPRO / XM4 / XM6 / CEVABX */
/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Profiler counters Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/*********************************************************************************************
 * @macro	PROF_READ_FRCC
 * @author	Ravid Rzaev
 * @date 	16/03/2021
 * @brief	Reads the value of the FRCC counter.
 * @return	value of the counter.
*********************************************************************************************/
#ifdef CEVA
#define PROF_READ_FRCC()     cpm_in( FRCC )
#else /* !CEVA */
#define PROF_READ_FRCC()     (0)
#endif /* CEVA */  


/*********************************************************************************************
 * @function	PROFILER_read_counter_value
 * @author	Ravid Rzaev
 * @date 	16/03/2021
 * @brief	Reads a specific counter value.
 * @param	counter_number: 	 one of the counters number.
 * @return	value of the counter.
*********************************************************************************************/
uint32_t PROFILER_read_counter_value(E_profiler_counter_number counter_number) PRAGMA_CSECT("CSL_CODE_SECTION");

/*********************************************************************************************
 * @function	PROFILER_resume_counter
 * @author	Ravid Rzaev
 * @date 	16/03/2021
 * @brief	Starts a selected profiling counters. The counter will start counting a specific event
 * 			according to its event type programming.
 * @param	counter_mask: 	 bit-mask for selecting the counters to resume.
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PROFILER_resume_counter(E_profiler_counter_mask counter_mask) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	PROFILER_reset_counter
 * @author	Ravid Rzaev
 * @date 	16/03/2021
 * @brief	Resets the selected profiling counters. Upon reset, the counter value is reset to 0.
 * @param	counter_mask: 		bit-mask for selecting the counters to reset.
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PROFILER_reset_counter(E_profiler_counter_mask counter_mask) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	PROFILER_pause_counter
 * @author	Ravid Rzaev
 * @date 	16/03/2021
 * @brief	Pause the selected profiling counters.
 * 			The counter value will freeze on its current value, but will not reset.
 * @param	counter_mask: 		bit-mask for selecting the counters to pause.
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PROFILER_pause_counter(E_profiler_counter_mask counter_mask) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	PROFILER_start_counter
 * @author	Ravid Rzaev
 * @date 	12/04/2021
 * @brief	Start the selected profiling counters.
 * 			The counter value will reset and resume.
 * @param	counter_mask: 		bit-mask for selecting the counters to pause.
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PROFILER_start_counter(E_profiler_counter_mask counter_mask) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	PROFILER_config_event_counter
 * @author	Ravid Rzaev
 * @date 	17/03/2021
 * @brief	Updates the event type, which is measured by the profiler counter.
 * @param	counter_number:  		one of the counters number.
 * @param	event: 					one of the profilers event.
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PROFILER_config_event_counter(E_profiler_counter_number counter_number, E_prof_counter_event event) PRAGMA_CSECT("CSL_CODE_SECTION");




#if defined(SENSPRO) || defined(CEVABX)

	/*********************************************************************************************
	 * @function	PROFILER_config_branch_counter
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configure the specific branch type counter, which is measured by the profiler counter.
	 * @param	counter_number:  		one of the counters number.
	 * @param	branch_type: 			one of the profilers branch types.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_branch_counter(E_profiler_counter_number counter_number, E_profiler_branch_configurations branch_type) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_config_std_branch_distribution
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configures Profiler Counter with Branch Event by its index
	 *              with recommended branch distribution profiling group.
	 * @param	counter_number:  		one of the counters number.
	 * @param	group_config: 			one of the recommended branch distribution profiling group configuration.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_std_branch_distribution(E_profiler_counter_number counter_number, E_profiler_std_branch_distribution group_config) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_config_std_branch_predication_summary
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configures Profiler Counter with Branch Event by its index
	 *          with recommended branch predication summary profiling group.
	 * @param	counter_number:  		one of the counters number.
	 * @param	group_config: 			one of the recommended branch predication summary profiling group configuration.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_std_branch_predication_summary(E_profiler_counter_number counter_number, E_profiler_std_branch_predication_summary group_config) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_config_std_btb_performance
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configures Profiler Counter with Branch Event by its index
	 *          with recommended BTB performance profiling group.
	 * @param	counter_number:  		one of the counters number.
	 * @param	group_config: 			one of the recommended BTB performance group configuration.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_std_btb_performance(E_profiler_counter_number counter_number, E_profiler_std_btb_performance group_config) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_config_std_loop_performance_summary
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configures Profiler Counter with Branch Event by its index
	 *          with recommended loop performance summary profiling group.
	 * @param	counter_number:  		one of the counters number.
	 * @param	group_config: 			one of the recommended BTB performance group configuration.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_std_loop_performance_summary(E_profiler_counter_number counter_number, E_profiler_std_loop_performance_summary group_config) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_config_std_non_loop_btb_able_performance
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Configures Profiler Counter with Branch Event by its index
	 *          with recommended non loop BTB-able performance profiling group.
	 * @param	counter_number:  		one of the counters number.
	 * @param	group_config: 			one of the recommended non-loop-BTBable performance profiling group configuration.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_config_std_non_loop_btb_able_performance(E_profiler_counter_number counter_number, E_profiler_std_non_loop_btb_able_performance group_config) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_get_branch_event_mask_attributes
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Reads branch event mask attributes.
	 * @param	counter_number:  			one of the counters number.
	 * @param	branch_event_attributes: 	pointer to branch event mask attributes structure.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_get_branch_event_mask_attributes(E_profiler_counter_number counter_number, T_profiler_branch_event_mask_attributes *branch_event_attributes) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_set_branch_event_mask_attributes
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Updates branch event mask attributes with a given structure.
	 * @param	counter_number:  			one of the counters number.
	 * @param	branch_event_attributes: 	branch event mask attributes structure.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_set_branch_event_mask_attributes(E_profiler_counter_number counter_number, T_profiler_branch_event_mask_attributes branch_event_attributes) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_get_core_bubbles_event_mask_attributes
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Gets core bubbles event mask attributes.
	 * @param	counter_number:  			one of the counters number.
	 * @param	core_bubbles_attributes: 	Pointer to core bubbles event mask attributes structure.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_get_core_bubbles_event_mask_attributes(E_profiler_counter_number counter_number, T_profiler_core_bubbles_mask_attributes *core_bubbles_attributes) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	PROFILER_set_core_bubbles_event_mask_attributes
	 * @author	Ravid Rzaev
	 * @date 	17/03/2021
	 * @brief	Sets branch event mask attributes with a given structure.
	 * @param	counter_number:  			one of the counters number.
	 * @param	core_bubbles_attributes: 	Core bubbles mask attributes structure.
	 * @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PROFILER_set_core_bubbles_event_mask_attributes(E_profiler_counter_number counter_number, T_profiler_core_bubbles_mask_attributes core_bubbles_attributes) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif // #if defined(SENSPRO) || defined(CEVABX)



CSL_CPP_END



#endif /* CEVA_PROFILER_H_ */
