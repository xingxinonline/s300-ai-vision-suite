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
/*********************************************************************************************
 * File:			ceva_icu.h
 * Created on: 		25/01/2021
 * Author: 			Anat Keidar
 * Description: 	Provides a backward computability package for
					the ICU (Interrupt Configuration Unit) Programming model
**********************************************************************************************/
#ifndef HEADERS_CEVA_ICU_H_
#define HEADERS_CEVA_ICU_H_


#include "ceva_csl_defs.h"


#ifdef SENSPRO

#include "ceva_xm_bc.h"
#include "ceva_icu.h"
#include "ceva_senspro_memory_map.h"


typedef union
{
	struct
	{
		uint32_t isr				:  1; // Interrupt Status Register
		uint32_t imr				:  1; // Interrupt Mask Register
		uint32_t imod				:  2; // Interrupt Mode
		uint32_t    				:  1; // Reserved
		uint32_t pwu				:  1; // PSU Wake-Up
		uint32_t ivi				:  3; // Interrupt Vector Index
		uint32_t    				:  3; // Reserved
		uint32_t priority			:  3; // Interrupt Priority
		uint32_t    				: 17; // Reserved
	};
	T_ICFGx icfg;
}T_ICFGx_bc;


#define T_Internal_Interrupt_Configuration T_ICFGx_bc
#define T_External_Interrupt_Configuration T_ICFGx_bc
#ifndef NUMBER_OF_INTERNAL_INTERRUPTS
#define NUMBER_OF_INTERNAL_INTERRUPTS   9
#endif
#define POSTED_CORE_INTERRUPTS ICU_POSTED_CORE_INTERRUPTS





/* ICU_Configure_Internal_Int
 * Description: Configures ICU internal interrupt
 * Input:  	_internal_interrupt
 * 		 	_internal_int_config
 * 			_imod
 * Output:      N/A
 */
#define ICU_Configure_Internal_Int(_internal_interrupt, _internal_int_config, _imod) \
	(_internal_int_config).icfg.fields.imod = _imod; \
	ICU_set_interrupt_configuration(_internal_interrupt, (_internal_int_config).icfg, (_internal_int_config).ivi);




/* ICU_Configure_NORMAL_ERR_Internal_Int
 * Description: Configures ICU interrupt for normal errors
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_NORMAL_ERR_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_NORMAL_NS_ERRORS, *(_internal_int_config), 2)

			
/* ICU_Configure_CRTICAL_ERR_Internal_Int
 * Description: Configures ICU interrupt for critical errors
 * 				Note: Critical errors interrupt will assert regardless of this configuration, unless masked by gm=0
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_CRTICAL_ERR_Internal_Int(_internal_int_config) \
	(_internal_int_config)->priority = 7; \
	ICU_Configure_Internal_Int(ICU_CRITICAL_NS_ERRORS, *(_internal_int_config), 2);


/* ICU_Configure_MCCI_Internal_Int
 * Description: Configures ICU interrupt for MCCI
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_MCCI_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_MCCI_NS, *(_internal_int_config), 2)


/* ICU_Configure_DMA_Internal_Int
 * Description: Configures ICU interrupt for DMA
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_DMA_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_DMA_NS, (*(_internal_int_config)), 2)


/* ICU_Configure_QMAN_SNOOP_Internal_Int
 * Description: Configures ICU interrupt for QMAN buffers errors/External Slave access to Snooping range in the IDM (SN_INT)
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_QMAN_SNOOP_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_BMAN_SN_INT_NS, *(_internal_int_config), 2)


/* ICU_Configure_POSTED_CORE_Internal_Int
 * Description: Configures ICU interrupt for posted interrupts
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_POSTED_CORE_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_POSTED_CORE_INTERRUPTS, *(_internal_int_config), 2)


/* ICU_Configure_TIMER_WD_Internal_Int
 * Description: Configures ICU interrupt for System Watchdog timer
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_TIMER_WD_Internal_Int(_internal_int_config) \
	(_internal_int_config)->priority = 7; \
	ICU_Configure_Internal_Int(ICU_TIMERS_NS_WD, *(_internal_int_config), 2);


/* ICU_Configure_TIMER_Internal_Int
 * Description: Configures ICU interrupt for MSS Timers
 * Input:       internal_int_config - internal interrupt configuration structure
 * Output:      N/A
 */
#define ICU_Configure_TIMER_Internal_Int(_internal_int_config) \
	ICU_Configure_Internal_Int(ICU_TIMERS_NS_EVENT, *(_internal_int_config), 2)


/* ICU_Configure_External_Int
 * Description: Configures an external interrupt in the ICU
 * Input:       external_int_config - external interrupt configuration structure
 *              external_int_number - external interrupt number to configure
 *                                    Note: external interrupt numbering for configuration starts with 0.
 * Output:      N/A
 */
#define ICU_Configure_External_Int(_external_int_config, _external_int_number) \
	ICU_set_interrupt_configuration((_external_int_number + NUMBER_OF_INTERNAL_INTERRUPTS), (_external_int_config)->icfg, (_external_int_config)->ivi)


/* ICU_Mask_Interrupts
 * Description: Masks interrupts assertion
 * Input:       interrupts - An array of interrupt numbers to perform masking for.
 *                           Note:  External interrupt numbers are from 9 upwards.
 *                           Note2: SW interrupts are not mask-able.
 *                           Note3: Critical interrupts are not mask-able
 *                                  (unless masked by gm=0, however if critical interrupt configuration lock is active for interrupts in this group they will be masked by gm masking).
 *		        size       - The size of interrupts array.
 * Output:      N/A
 */ 
#define ICU_Mask_Interrupts(_interrupts, _size) \
		ICU_interrupts_operation_bc(ICU_OPOERATION_MASK, _interrupts, _size, CSL_TRUE)


/* ICU_Mask_Interrupts_Groups
 * Description: Masks interrupts by group number association
 * Input:       gm - the group number of interrupts to perform mask operation for. 
 *                   Note:  if gm=0, all interrupts will be masked with the exception of critical interrupts when critical interrupt locking is active.
 * Output:      N/A
 */
#define ICU_Mask_Interrupts_Groups(_gm) \
		ICU_mask_interrupt_group(_gm, CSL_TRUE)


/* ICU_Unmask_Interrupts_Groups
 * Description: Unmasks interrupts by group number association
 * Input:       gm - the group number of interrupts to perform unmask operation for. gm = { 0, 1, ... , ((NUM_OF_INTERRUPTS/32)-1) }
 * Output:      N/A
 */
#define ICU_Unmask_Interrupts_Groups(_gm) \
		ICU_mask_interrupt_group(_gm, CSL_FALSE)


/* ICU_Unmask_Interrupts
 * Description: Unmasks interrupts assertion
 * Input:       interrupts - An array of interrupt numbers to perform unmasking for.
 		        size       - The size of interrupts array.
 * Output:      N/A
 */
#define ICU_Unmask_Interrupts(_interrupts, _size) \
		ICU_interrupts_operation_bc(ICU_OPOERATION_MASK, _interrupts, _size, CSL_FALSE)


/* ICU_Is_Pending_Interrupt
 * Description: Reports if an interrupt is in pending state. Note: External interrupt numbers are from 9 upwards
 * Input:       The interrupt number to report the pending state for
 * Output:      1 - if the provided interrupt is in pending state, 0 - otherwise.
 */
#define ICU_Is_Pending_Interrupt(_interrupt) \
		ICU_is_pending_interrupt(_interrupt)

/* ICU_Clear_Pending_Interrupts
 * Description: Clear pending state of interrupts
 * Input:       interrupts - An array of interrupt numbers to clear pending state for. Note: External interrupt numbers are from 9 upwards
 		        size       - The size of interrupts array.
 * Output:      N/A
 */
#define ICU_Clear_Pending_Interrupts(_interrupts, _size) \
		ICU_interrupts_operation_bc(ICU_OPOERATION_CLEAR, _interrupts, _size, CSL_TRUE)


/* ICU_Lock_Critical_Interrupt_Configuration
 * Description: Locks configuration of critical interrupts. Note: Critical interrupts are interrupts configured with priority 7 (IPR=7)
 * Input:       N/A
 * Output:      N/A
 */
#define ICU_Lock_Critical_Interrupt_Configuration() \
		ICU_lock_critical_interrupt_conf(CSL_TRUE)


/* ICU_Unlock_Critical_Interrupt_Configuration
 * Description: Unlocks configuration of critical interrupts. Note: Critical interrupts are interrupts configured with priority 7
 * Input:       N/A
 * Output:      N/A
 */
#define ICU_Unlock_Critical_Interrupt_Configuration() \
		ICU_lock_critical_interrupt_conf(CSL_FALSE)


/* ICU_Generate_Interrupts
 * Description: Generates SW interrupts via the ICU. Note: SW interrupts are never masked
 * Input:       interrupts - An array of interrupt numbers to generated. Note: External interrupt numbers are from 9 upwards
 * 				size       - The size of interrupts array.
 * Output:      N/A
 */
#define ICU_Generate_Interrupts(_interrupts, _size) \
		ICU_interrupts_operation_bc(ICU_OPOERATION_GENERATE, _interrupts, _size, CSL_TRUE)



/* ICU_Enable_Posted_interrupt
 * Description: Enables posted interrupts on the ICU
 * Input:       The posted interrupt number to enable
 * Output:      N/A
 */
#define ICU_Enable_Posted_interrupt( _posted_interrupt_num) \
		HW_EXCPTIONS_enable_posted_interrupt(_posted_interrupt_num)

/* ICU_Disable_Posted_Interrupt
 * Description: Disables posted interrupts on the ICU
 * Input:       The posted interrupt number to disable
 * Output:      N/A
 */
#define ICU_Disable_Posted_Interrupt( _posted_interrupt_num) \
		HW_EXCPTIONS_disable_posted_interrupt(_posted_interrupt_num)

/* ICU_Is_Posted_Interrupt_Pending
 * Description: Reports if a posted interrupt is in pending state
 * Input:       The posted interrupt number to report the pending state for
 * Output:      1 - if the provided posted interrupt is in pending state, 0 - otherwise.
 */
#define ICU_Is_Posted_Interrupt_Pending( _posted_interrupt_num) HW_EXCPTIONS_get_posted_interrupt_pending(_posted_interrupt_num)

/* ICU_Clear_Posted_interrupt_Pending
 * Description: Clears posted interrupt pending status
 * Input:       The posted interrupt number to clear pending state for
 * Output:      N/A
 */
#define ICU_Clear_Posted_interrupt_Pending( _posted_interrupt_num) HW_EXCPTIONS_clear_posted_interrupt_pending(_posted_interrupt_num)


/*
 * ICU_Interrupts_Installed_Count
 * Description: Returns the number of support interrupts
 * Input:       N/A
 * Output:      The number of interrupts supported by IP
 */
#define ICU_Interrupts_Installed_Count() \
		CSL_HW_CONFIG_NUM_INTERRUPTS

/* ICU_Is_Enabled
 * Description: Reports if mss ICU feature is enabled
 * Input:       N/A
 * Output:      1 if the ICU is enabled, 0 otherwise
 */
#define ICU_Is_Enabled \
	ICU_is_enabled

/* ICU_Is_Critical_Interrupt_Configuration_Locked
 * Description: Reports if critical interrupt configuration is locked
 * Input:       N/A
 * Output:      1 if the critical interrupt configuration is locked, 0 otherwise
 */
#define ICU_Is_Critical_Interrupt_Configuration_Locked() \
		ICU_lock_critical_interrupt_conf(CSL_TRUE);

/* ICU_Enable
 * Description: Enables the mss ICU feature
 * Input:       N/A
 * Output:      N/A
 */
#define ICU_Enable() \
		ICU_activation(CSL_TRUE)


/* ICU_Disable
 * Description: Disables the mss ICU feature
 * Input:       N/A
 * Output:      N/A
 */
 
#define ICU_Disable() \
		ICU_activation(CSL_FALSE)



/* ICU_IVA_Allocate
 * Description: allocates IVA register with an ISR address
 * Input:       ISR address to allocate IVA for
 * Output:      Upon success the 2<= IVI < 7 allocated number, upon failure -1
 *
 */
#define ICU_IVA_Allocate(_isr_address) \
		((uint8_t) ICU_IVA_allocate_bc(_isr_address))


/* ICU_IVA_Deallocate
 * Description: Deallocates IVA register by IVI
 * Input:       Allocated IVI
 * Output:      N/A
 * **/
#define ICU_IVA_Deallocate(_ivi) \
		ICU_IVA_deallocate(_ivi)





#endif /* SENSPRO */
#endif /* HEADERS_CEVA_ICU_H_ */
