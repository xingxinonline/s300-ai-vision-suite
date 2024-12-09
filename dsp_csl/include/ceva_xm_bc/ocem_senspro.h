/*****************************************************************************\
* CEVA Confidential property.
 * Copyright (C) Ceva Inc. All rights reserved.
 *
 * This file constitutes proprietary and confidential information of CEVA Inc.
 * Any use or copying of this file or any information contained in this file other
 * than as expressly approved in writing by Ceva, Inc. is strictly prohibited.
 * Any disclosure or distribution of this file or any information contained in
 * this file except to the intended recipient is strictly prohibited.
 \*****************************************************************************/

#ifndef _INCLUDE_OCEM_SENSPRO_H_
#define _INCLUDE_OCEM_SENSPRO_H_


#include "ceva_csl_defs.h"

#ifdef SENSPRO

#include "cpm_io.h"
#include "ceva_profiler.h"

#define PROF_COUNTER_EVENT_PMSS_MIS_CNT PROF_COUNTER_EVENT_PMSS_MISS_CNT

/**
 * @addtogroup OCEM_DRIVER OCEM Driver
 * @{
 * @brief CEVA-XM6 OCEM (On-Chip Emulation Module) driver
 *
 * The OCEM driver is used to configure the senspro On-Chip Emulation Module hardware.
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup OCEM_DRIVER_REGS OCEM Register Map
 * @ingroup OCEM_DRIVER
 * @{
 */

/**
 * @brief OCEM registers' addresses
 */
typedef enum {
	OCEM_MSS_CONFIG_ADDR = 0x15C, /**< MSS_CONFIG Register */
	OCEM_CORE_VERSION_ADDR = 0x174, /**< CORE_VERSION Register */
	OCEM_CORE_ID_ADDR = 0x178, /**< CORE_ID Register */
	OCEM_CORE_CONFIG_ADDR = 0x17C, /**< CORE_CONFIG  Register */
	OCEM_PROF_RESET_ADDR = 0x300, /**< PROF_RESET */
	OCEM_PROF_PAUSE_ADDR = 0x304, /**< PROF_PAUSE */
	OCEM_PROF_CTRL0_ADDR = 0x308, /**< PROF_CTRL0 */
	OCEM_PROF_CTRL1_ADDR = 0x30C, /**< PROF_CTRL1 */
	OCEM_PROF_FRCC_ADDR = 0x310, /**< PROF_FRCC */
	OCEM_PROF_CNT0_ADDR = 0x320, /**< PROF_CNT0 */
	OCEM_PROF_CNT1_ADDR = OCEM_PROF_CNT0_ADDR + 4, /**< PROF_CNT1 */
	OCEM_PROF_CNT2_ADDR = OCEM_PROF_CNT1_ADDR + 4, /**< PROF_CNT2 */
	OCEM_PROF_CNT3_ADDR = OCEM_PROF_CNT2_ADDR + 4, /**< PROF_CNT3 */
	OCEM_PROF_CNT4_ADDR = OCEM_PROF_CNT3_ADDR + 4, /**< PROF_CNT4 */
	OCEM_PROF_CNT5_ADDR = OCEM_PROF_CNT4_ADDR + 4, /**< PROF_CNT5 */
	OCEM_PROF_CNT6_ADDR = OCEM_PROF_CNT5_ADDR + 4, /**< PROF_CNT6 */
	OCEM_PROF_CNT7_ADDR = OCEM_PROF_CNT6_ADDR + 4, /**< PROF_CNT7 */
	OCEM_PROF_EV_MASK0_ADDR = 0x380, /**< PROF_EV_MASK0 */
	OCEM_PROF_EV_MASK1_ADDR = OCEM_PROF_EV_MASK0_ADDR + 4, /**< PROF_EV_MASK1 */
	OCEM_PROF_EV_MASK2_ADDR = OCEM_PROF_EV_MASK1_ADDR + 4, /**< PROF_EV_MASK2 */
	OCEM_PROF_EV_MASK3_ADDR = OCEM_PROF_EV_MASK2_ADDR + 4, /**< PROF_EV_MASK3 */
	OCEM_PROF_EV_MASK4_ADDR = OCEM_PROF_EV_MASK3_ADDR + 4, /**< PROF_EV_MASK4 */
	OCEM_PROF_EV_MASK5_ADDR = OCEM_PROF_EV_MASK4_ADDR + 4, /**< PROF_EV_MASK5 */
	OCEM_PROF_EV_MASK6_ADDR = OCEM_PROF_EV_MASK5_ADDR + 4, /**< PROF_EV_MASK6 */
	OCEM_PROF_EV_MASK7_ADDR = OCEM_PROF_EV_MASK6_ADDR + 4, /**< PROF_EV_MASK7 */
} ocem_regs_addr_e;


typedef union {
	struct {
		union {
			struct {
				uint8_t non_btb_able :1;
				uint8_t btb_able :1;
				uint8_t loop_branch :1;
				uint8_t call :1;
				uint8_t ret :1;
				uint8_t calls :1;
				uint8_t :2;
			};
			uint8_t : 8;
		} branch_type;

		union {
			struct {
				uint8_t btb_hit :1;
				uint8_t btb_miss :1;
				uint8_t correct_btb_hits :1;
				uint8_t incorrect_btb_misses :1;
				uint8_t :4;
			};
			uint8_t : 8;
		} btb_stats;

		union {
			struct {
				uint8_t conditonal :1;
				uint8_t non_conditonal :1;
				uint8_t :2;
				uint8_t taken :1;
				uint8_t not_taken :1;
				uint8_t :2;
			};
			uint8_t : 8;
		} branch_condition_outcome;
		uint8_t :8;
	};
	uint32_t overlay;
	T_profiler_branch_event_mask_attributes branch_event_attributes;
} prof_branch_event_mask_attributes_t;


typedef union {
	struct {
		union {
			struct {
				uint8_t cnd_brnch_to_uncnd_brnch_bubbles :1;
				uint8_t func_call_and_ret_bubbles :1;
				uint8_t predicate_calc_to_use_bubbles :1;
				uint8_t ld_to_ld_or_st_bubbles :1;
				uint8_t calc_to_brrcmp_bubbles :1;
				uint8_t ld_to_exec_bubbles :1;
				uint8_t :2;
			};
			uint8_t : 8;
		} core_bubbles;
		uint8_t : 8;
		uint8_t : 8;
		uint8_t : 8;
	};
	uint32_t overlay;
	T_profiler_core_bubbles_mask_attributes core_bubbles_attributes;
} prof_core_bubbles_mask_attributes_t;

/**
 * @}
 */

/**
 * @addtogroup OCEM_DRIVER_API OCEM Profiling Counters API
 * @ingroup OCEM_DRIVER
 * @{
 */


/**
 * @brief Special value for disabling address range condition on profiling events
 */
#define PROF_COUNTER_ADDRESS_RANGE_DISABLE   (1)



/***********************************************************
 * prof_configurate_recommended_branch_distribution_profiling_group
 *
 * Written by: EF 16/07/2020
 * Description: Configurates Profiler Counter with Branch Event by its index
 *              with recommended branch distribution profiling group
 *
 * Input:
 * 		1. Profiler counter event mask index that matches branch event profiler counter index
 *      2. recommended branch distribution profiling group configuration
 * 	Output:
 * 		0 - profiler counter masking has been configurated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_configurate_recommended_branch_distribution_profiling_group(_counter_num, _group_config) \
		PROFILER_config_std_branch_distribution(_counter_num, _group_config)

/***********************************************************
 * prof_configurate_recommended_branch_predication_summary_profiling_group
 *
 * Written by: EF 16/07/2020
 * Description: Configurates Profiler Counter with Branch Event by its index
 *              with recommended branch predication summary profiling group
 *
 * Input:
 * 		1. Profiler counter event mask index that matches branch event profiler counter index
 *      2. recommended branch predication summary profiling group configuration
 * 	Output:
 * 		0 - profiler counter masking has been configurated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_configurate_recommended_branch_predication_summary_profiling_group(_counter_num, _group_config) \
		PROFILER_config_std_branch_predication_summary(_counter_num, _group_config)

/***********************************************************
 * prof_configurate_recommended_btb_performance_profiling_group
 *
 * Written by: EF 16/07/2020
 * Description: Configurates Profiler Counter with Branch Event by its index
 *              with recommended BTB performance profiling group
 *
 * Input:
 * 		1. Profiler counter event mask index that matches branch event profiler counter index
 *      2. recommended BTB performance group configuration
 * 	Output:
 * 		0 - profiler counter masking has been configurated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_configurate_recommended_btb_performance_profiling_group(_counter_num, _group_config) \
		PROFILER_config_std_btb_performance(_counter_num, _group_config)

/***********************************************************
 * prof_configurate_recommended_loop_performance_summary_profiling_group
 *
 * Written by: EF 16/07/2020
 * Description: Configurates Profiler Counter with Branch Event by its index
 *              with recommended loop performance summary profiling group
 *
 * Input:
 * 		1. Profiler counter event mask index that matches branch event profiler counter index
 *      2. recommended loop performance summary profiling group configuration
 * 	Output:
 * 		0 - profiler counter masking has been configurated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_configurate_recommended_loop_performance_summary_profiling_group(_counter_num, _group_config) \
		PROFILER_config_std_loop_performance_summary(_counter_num, _group_config)

/***********************************************************
 * prof_configurate_recommended_non_loop_btb_able_performance_profiling_group
 *
 * Written by: EF 16/07/2020
 * Description: Configurates Profiler Counter with Branch Event by its index
 *              with recommended non loop BTB-able performance profiling group
 *
 * Input:
 * 		1. Profiler counter event mask index that matches branch event profiler counter index
 *      2. recommended non-loop-BTBable performance profiling group configuration
 * 	Output:
 * 		0 - profiler counter masking has been configurated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_configurate_recommended_non_loop_btb_able_performance_profiling_group(_counter_num, _group_config) \
		PROFILER_config_std_non_loop_btb_able_performance(_counter_num, _group_config)


/***********************************************************
 * prof_read_branch_event_mask_attributes
 *
 * Written by: EF 16/07/2020
 * Description: Reads branch event mask attributes into brnEvntMskAttrs
 *
 * Input:
 * 		1. Profiler counter event mask index that contains attributes for profiler branch event
 *      2. brnEvntMskAttrs - pointer to updates branch event mask attributes
 * 	Output:
 * 		0 - profiler counter masking has been read successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_read_branch_event_mask_attributes(_counter_num, _branch_event_attributes) \
		PROFILER_get_branch_event_mask_attributes(_counter_num, _branch_event_attributes.branch_event_attributes)


/***********************************************************
 * ProfilerUpdateBranchEventMaskAttributes
 *
 * Written by: EF 16/07/2020
 * Description: updates branch event mask attributes with brnEvntMskAttrs value
 *
 * Input:
 * 		1. Profiler counter event mask index that contains attributes for profiler branch event
 *      2. brnEvntMskAttrs - updates branch event mask attributes
 * 	Output:
 * 		0 - profiler counter masking has been updated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_update_branch_event_mask_attributes(_counter_num, _branch_event_attributes) \
		PROFILER_set_branch_event_mask_attributes(_counter_num, _branch_event_attributes.branch_event_attributes)


/***********************************************************
 * prof_update_core_bubbles_event_mask_attributes
 *
 * Written by: EF 19/07/2020
 * Description: updates core bubbles event mask attributes with creBlbsEvntMskAttrs value
 *
 * Input:
 * 		1. Profiler counter event mask index that contains attributes for profiler core bubbles event
 *      2. branch distribution profiling group configuration
 * 	Output:
 * 		0 - profiler counter masking has been updated successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_update_core_bubbles_event_mask_attributes(_counter_num, _core_bubbles_attributes) \
		PROFILER_set_core_bubbles_event_mask_attributes(_counter_num, _core_bubbles_attributes)

/***********************************************************
 * prof_read_core_bubbles_event_mask_attributes
 *
 * Written by: EF 16/07/2020
 * Description: Reads core bubbles event mask attributes into creBlbsEvntMskAttrs
 *
 * Input:
 * 		1. Profiler counter event mask index that contains attributes for profiler branch event
 *      2. creBlbsEvntMskAttrs - pointer to updates branch event mask attributes
 * 	Output:
 * 		0 - profiler counter masking has been read successfully
 * 		1 - otherwise
 ***********************************************************/
#define prof_read_core_bubbles_event_mask_attributes(_counter_num, _core_bubbles_attributes) \
		PROFILER_get_core_bubbles_event_mask_attributes(_counter_num, _core_bubbles_attributes)

/**
 * @brief Configures a profiling counter in OCEM block. <BR> This functionality in not supported in simulation.
 * @param[in] counter_id Counter ID
 * @param[in] counter_event Counter event
 * @param[in] low_address  Lower program address (low_address <= high_address)
 * @param[in] high_address Upper program address (pass 0 to disable address range check)
 * @returns void
 */

#define prof_counter_config(_counter_number, _event, _low_address, _high_address) \
		PROFILER_config_event_counter(_counter_number, _event)

#define prof_full_counter_config( _counter_number, _event)						  \
		PROFILER_config_event_counter(_counter_number, _event)

#define prof_branch_counter_config(_counter_number, _branch_type) 					  \
		PROFILER_config_branch_counter(_counter_number, _branch_type);

/**
 * @brief Resets the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to reset (see \link prof_counter_mask_e \endlink)
 */
#define PROF_RESET(_mask)     PROFILER_reset_counter(_mask)

/**
 * @brief Pauses the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to pause (see \link prof_counter_mask_e \endlink)
 */
#define PROF_PAUSE(_mask)     PROFILER_pause_counter(_mask)

/**
 * @brief Resumes the counting of the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to resume (see \link prof_counter_mask_e \endlink)
 */
#define PROF_RESUME(_mask)    PROFILER_resume_counter(_mask)

/**
 * @brief Restarts the counting of the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to restart (see \link prof_counter_mask_e \endlink)
 */
#define PROF_START(_mask)    PROFILER_start_counter(_mask)

/**
 * @brief Reads the value of a profiling counter in OCEM block
 * @param[in] id Counter ID (see \link prof_counter_id_e \endlink)
 * @return the value of the counter
 */
#define PROF_READ_CNT(_counter_number)    PROFILER_read_counter_value(_counter_number)


/** @}*/

#ifdef __cplusplus
}
#endif

#endif /* SENSPRO */
#endif /* _INCLUDE_OCEM_SENSPRO_H_ */
