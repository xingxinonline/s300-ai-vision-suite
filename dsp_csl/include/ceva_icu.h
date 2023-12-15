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
#ifndef CEVA_ICU_H_
#define CEVA_ICU_H_
/*********************************************************************************************
 * @module			ICU
 * @file			ceva_icu.h
 * @author			Anat Keidar
 * @date			25/01/2021
 * @brief			Define the structure, configuration values and function of
					the ICU (Interrupt Configuration Unit) Programming model registers
**********************************************************************************************/
#include "ceva_hw_conf.h"
#ifdef CSL_ICU_SUPPORTED

#include "ceva_assert.h"

    
    #ifndef NUMBER_OF_INTERNAL_INTERRUPTS
        #define NUMBER_OF_INTERNAL_INTERRUPTS   9
    #endif



	CSL_CPP_START


	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	ICU Programming Model Registers Structures
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/


	/*********************************************************************************************
	 * @struct		T_IGMR
	 * @register	IGMR
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t gm0				:  1; // Group Mask 0
			uint32_t gm1				:  1; // Group Mask 1
			uint32_t gm2				:  1; // Group Mask 2
			uint32_t gm3				:  1; // Group Mask 3
			uint32_t gm4				:  1; // Group Mask 4
			uint32_t gm5				:  1; // Group Mask 5
			uint32_t gm6				:  1; // Group Mask 6
			uint32_t gm7				:  1; // Group Mask 7
			uint32_t    				:  8; // Reserved
			uint32_t cil				:  1; // Critical Interrupt configuration Lock
			uint32_t cilp				:  1; // CIL Protection
			uint32_t    				: 13; // Reserved
			uint32_t icue				:  1; // ICU Enable bit
		}fields;
		uint32_t value;
	}T_IGMR;



	/*********************************************************************************************
	 * @struct		T_ICFGx
	 * @register	ICFG
	 **********************************************************************************************/
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
			uint32_t ipr				:  3; // Interrupt Priority
			uint32_t    				: 17; // Reserved
		}fields;
		uint32_t value;
	}T_ICFGx;


	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	ICU Programming Model Configuration Values
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/


	/*********************************************************************************************
	 * @enum		E_ICFG_imod
	 * @register	ICFG
	 * @field		IMOD
	 * @brief		Interrupt Mode
	 **********************************************************************************************/
	typedef enum
	{
		ICFG_IMOD_POSITIVE_EDGE			= 0,
		ICFG_IMOD_NEGAITIVE_EDGE		= 1,
		ICFG_IMOD_LEVEL_SENSITIVE		= 2,
		ICFG_IMOD_MAX_VALUE				= 2
	} E_ICFG_imod;



	/*********************************************************************************************
	 * @enum		E_ICFG_pwu
	 * @register	ICFG
	 * @field		PWU
	 * @brief		PSU Wake-Up
	 **********************************************************************************************/
	typedef enum
	{
		ICFG_PWU_INTERRUPT_NOT_WAKEUP_PSU	= 0,
		ICFG_PWU_INTERRUPT_WAKEUP_PSU		= 1
	} E_ICFG_pwu;



	/*********************************************************************************************
	 * @enum		E_ICFG_ipr
	 * @register	ICFG
	 * @field		IPR
	 * @brief		Interrupt Priority values
	 **********************************************************************************************/
	typedef enum
	{
		ICFG_IPR_NO_PRIORITY			= 0,
		ICFG_IPR_NORMAL_PRIORITY_1		= 1,
		ICFG_IPR_NORMAL_PRIORITY_2		= 2,
		ICFG_IPR_NORMAL_PRIORITY_3		= 3,
		ICFG_IPR_NORMAL_PRIORITY_4		= 4,
		ICFG_IPR_NORMAL_PRIORITY_5		= 5,
		ICFG_IPR_NORMAL_PRIORITY_6		= 6,
		ICFG_IPR_CRITICAL_PRIORITY		= 7
	} E_ICFG_ipr;


	/*********************************************************************************************
	 * @enum		E_IGMR_icue
	 * @register	IGMR
	 * @field		ICUE
	 * @brief		ICU Enable bit
	 **********************************************************************************************/
	typedef enum
	{
		IGMR_ICU_DISABLE 	= 0,
		IGMR_ICU_ENABLE 	= 1
	}E_IGMR_icue;



	/*********************************************************************************************
	 * @enum		E_ICU_interrupt_types
	 * @brief		Each value is an ICFGx index
	 **********************************************************************************************/
	typedef enum
	{
	   ICU_CRITICAL_NS_ERRORS     = 0,
	   ICU_NORMAL_NS_ERRORS       = 1,
	   ICU_MCCI_NS                = 2,
	   ICU_BMAN_SN_INT_NS         = 3,
	   ICU_DMA_NS                 = 4,
	   ICU_TIMERS_NS_WD           = 5,
	   ICU_TIMERS_NS_EVENT        = 6,
	   ICU_DEBUG_UNIT             = 7,
	   ICU_POSTED_CORE_INTERRUPTS = 8
	} E_ICU_interrupt_types;




	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	ICU Programming Model Driver Functions
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/


	/*********************************************************************************************
	 * @function	ICU_set_interrupt_configuration
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Set the given interrupt configuration in the given interrupt number.
	 * @param	interrupt_num: 	The interrupt number.
	 * @param	icfgx: A given interrupt configuration.
	 * @param	iva_id: IVA allocation ID
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
E_csl_status ICU_set_interrupt_configuration(uint8_t interrupt_num, T_ICFGx icfgx, T_csl_allocation_id iva_id) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	 * @function	ICU_activation
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Enable or disable interrupts.
	 * @param	enable: 	If true ICU enables the ICU, if false disables the ICU.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_activation(bool enable) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	 * @function	ICU_is_enabled
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Returns true if the ICU is enabled, returns false if the ICU is disabled.
	 * @param	void
	 * @return	true if ICU is enable, l if ICU is disabled.
	*********************************************************************************************/
	bool ICU_is_enabled(void) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_lock_critical_interrupt_conf
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Lock the interrupt configuration
	 * @param	lock: If true locks, if false unlocks the critical interrupt configuration
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status ICU_lock_critical_interrupt_conf(bool lock) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_mask_interrupt_group
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Mask or unmask all interrupts in the given group.
	 * @param	group_number: 	The interrupt group number. A number between 0 and CSL_HW_CONFIG_NUM_ICU_GROUPS.
	 * @param	mask: 			Mask if true, unmask if false.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_mask_interrupt_group(uint8_t group_number, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_set_group_mask
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Set the given mask in the given interrupt group.
	 * @param	group_number: 	The interrupt group number. A number between 0 and CSL_HW_CONFIG_NUM_ICU_GROUPS.
	 * @param	group_mask: 	Each bit in the mask is corresponding to an interrupt in the group.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_set_group_mask(uint8_t group_number, uint32_t group_mask ) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	 * @function	ICU_mask_interrupt
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Mask or unmask the given interrupt.
	 * @param	interrupt: 	The interrupt number. A number between 0 and CSL_HW_CONFIG_NUM_INTERRUPTS.
	 * @param	mask: 		Mask if true, unmask if false.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_mask_interrupt(uint8_t interrupt, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_generate_interrupt
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Generates the given interrupt.
	 * @param	interrupt: 	The interrupt number. A number between 0 and CSL_HW_CONFIG_NUM_INTERRUPTS.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_generate_interrupt(uint8_t interrupt) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_clear_interrupt
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Clears the given interrupt.
	 * @param	interrupt: 	The interrupt number. A number between 0 and CSL_HW_CONFIG_NUM_INTERRUPTS.
	 * @return	CSL_SUCCESS or CSL failure code 
	*********************************************************************************************/
	E_csl_status ICU_clear_interrupt(uint8_t interrupt) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	 * @function	ICU_is_pending_interrupt
	 * @author	Anat Keidar
	 * @date 	27/01/2021
	 * @brief	Check it the given interrupt is pending.
	 * @param	interrupt: 	The interrupt number. A number between 0 and CSL_HW_CONFIG_NUM_INTERRUPTS.
	 * @return	true if the interrupt is pending, false if the interrupt is not pending.
	*********************************************************************************************/
	bool ICU_is_pending_interrupt(uint8_t interrupt ) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_IVA_allocate
	 * @author	Anat Keidar
	 * @date 	10/02/2021
	 * @brief	Allocates the first available interrupt vector address and sets the given ISR address.
	 * @param	isr_address: The address for the interrupt vector
	 * @return	Return the id number of the allocated IVA if there is available IVA, otherwise return CSL_ALLOCATION_FAILURE.
	*********************************************************************************************/
	T_csl_allocation_id ICU_IVA_allocate(uint32_t isr_address) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	ICU_IVA_deallocate
	 * @author	Anat Keidar
	 * @date 	10/02/2021
	 * @brief	Deallocates the given IVA.
	 * @param	iva_id: The allocation ID of the given IVA
	 * @return	Return CSL_SUCCESS if deallocation was successful, returns failure status if not.
	*********************************************************************************************/
	E_csl_status ICU_IVA_deallocate(T_csl_allocation_id iva_id) PRAGMA_CSECT("CSL_CODE_SECTION");




	CSL_CPP_END


#endif // #ifdef CSL_ICU_SUPPORTED
#endif /* CEVA_ICU_H_ */

