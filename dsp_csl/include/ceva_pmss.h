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
#ifndef CEVA_PMSS_H_
#define CEVA_PMSS_H_
/*********************************************************************************************
 * @module          PMSS
 * @file            ceva_pmss.h
 * @author          Ravid Rzaev
 * @date            25/02/2021
 * @brief           Define the structure, configuration values and function of
                    the PMSS Programming model registers
**********************************************************************************************/
//**********************************************************
//********************** Includes **************************
//**********************************************************
#include "ceva_assert.h"

#ifdef __cplusplus
extern "C" {
#endif



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	PMSS Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

	#ifndef SENSPRO_V1_2
		#define PAPE	pape
	#else
		#define  PAPE
	#endif // NOT SENSPRO_V1_2

/**********************
 * Name: T_MSS_PCR
 * Register: MSS_PCR
 **********************/
typedef union
{
	struct
	{
		uint32_t PAPE 			:1;	// Access Protection Enable
		uint32_t 				:1; // Reserved
		uint32_t cac_pfe 		:1;	// Cache Pre-fetch Enable
		uint32_t ipme 			:1;	// Program TCM Enable
		uint32_t 				:2;	// Reserved
		uint32_t clbe			:1;	// Cache line buffer enable
		uint32_t pcac_en 		:1;	// Program Cache Enable
		uint32_t hwpf_sz 		:2;	// Program Cache Hardware Pre-fetch depth
		uint32_t 				:2;	// Reserved
		uint32_t cac_wpe 		:1;	// Cache Way Prediction Enable
		uint32_t 				:19;// Reserved
	} fields;
	uint32_t value;
} T_MSS_PCR;


#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

/***********************
 * Name: T_P_SYS_OU_C
 * Register: P_SYS_OU_C
 ***********************/
typedef union
{
	struct
	{
		uint32_t total_os  		:4;	// total outstanding requests
		uint32_t pdma_os   		:4;	// pdma  qutstanding requests
		uint32_t sw_os     		:4;	// sw pre-fetch outstanding requests
#ifndef CEVABX
		uint32_t pdma_bsz  		:2;	// burst size for PDMA transactions
#else /* CEVABX */
		uint32_t           		:2; // Reserved
#endif /* !CEVABX */
		uint32_t           		:18;// Reserved
	} fields;
	uint32_t value;
} T_P_SYS_OU_C;

#endif /* #if ( HW_IS_BUS_PROTOCOL_AHB == 0 ) */


#ifndef CEVABX

/***********************
 * Name: T_P_PDTC
 * Register: P_PDTC
 ***********************/
typedef union
{
	struct
	{
		uint32_t pdtc 			:19;//PDMA transfer count
		uint32_t 	  			:10;// Reserved
		uint32_t pdst 			:1;	// Read only:  PDMA status: "1" - busy, 0 - "not busy"
		uint32_t 	  			:1;	// Reserved
		uint32_t pdie 			:1;	// PDMA interrupt enable
	} fields;
	uint32_t value;
} T_P_PDTC;


/***********************
 * Name: T_P_PDEA
 * Register: P_PDEA
 ***********************/
typedef union
{
	struct
	{
		uint32_t 	  			:5;	// Reserved
		uint32_t pdea 			:27; // External Address
	} fields;
	uint32_t value;
} T_P_PDEA;

/***********************
 * Name: T_P_PDIA
 * Register: P_PDIA
 ***********************/
typedef union
{
	struct
	{
		uint32_t 	  			:5;	 // Reserved
		uint32_t pdia 			:13; // Internal Address
		uint32_t 	  			:14; // Reserved
	} fields;
	uint32_t value;
} T_P_PDIA;


/***********************
 * Name: T_P_PORT_ID
 * Register: P_PORT_ID
 ***********************/
typedef union
{
	struct
	{
		uint32_t pdma_id 		:4;
		uint32_t pf_id   		:4;
		uint32_t ocem_id		:4;
		uint32_t  		 		:20; // Reserved
	} fields;
	uint32_t value;
} T_P_PORT_ID;

#endif /* !CEVABX */

/*************************
 * Name: T_P_ADDx_START
 * Register: P_ADDx_START
 *************************/
typedef union
{
	struct
	{
		uint32_t p_region_start :20; // 4KB start block of address region
		uint32_t 				:8;	 // Reserved
		uint32_t inactive 		:1;	 // Set if this region is inactive
		uint32_t 				:3;	 // Reserved
	} fields;
	uint32_t value;
} T_P_ADDx_START;

/************************
 * Name: T_P_ADDx_ATT0
 * Register: P_ADDx_ATT0
 ************************/
typedef union
{
	struct
	{
		uint32_t l1ic 			:1;	// L1IC cache-ability
		uint32_t l1ic_lock 		:1;	// L1IC lock after cache-line fill attribute
		uint32_t 				:2;	// Reserved
#if defined(SENSPRO) || defined(CEVABX)
		uint32_t p_ap 			:2;	// Access Protection
		uint32_t 				:2;	// Reserved
#else
		uint32_t p_ap 			:3;	// Access Protection
		uint32_t 				:1;	// Reserved
#endif
		uint32_t p_l2a 			:4;	// L2 Cache Policy for read accesses
		uint32_t 				:12;	// Reserved
		uint32_t p_rqos 		:4;	// Read transaction Quality of Service
		uint32_t 				:4;	// Reserved
	} fields;
	uint32_t value;
} T_P_ADDx_ATT0;

/***********************
 * Name: T_P_CCOSAR
 * Register: P_CCOSAR
 ***********************/
typedef union
{
	struct
	{
		uint32_t 				: 6;	// Reserved
		uint32_t p_ccosa		: 26;	// Instruction cache Operations Start Address
	} fields;
	uint32_t value;
} T_P_CCOSAR;

/***********************
 * Name: T_P_CCOCR
 * Register: P_CCOCR
 ***********************/
typedef union
{
	struct
	{
#if defined(SENSPRO) || defined(CEVABX)
		uint32_t p_active		: 1;	// L1 Intruction cache operation activeness
#else
		uint32_t 				: 1;	// Reserved
#endif
		uint32_t p_l1ico	: 1;	// L1 Intruction Cache operation completeness
		uint32_t p_ot		: 4;	// Operation Type
		uint32_t 			: 1;	// Reserved
		uint32_t p_os		: 1;	// Operation Size
		uint32_t 			: 8;	// Reserved
		uint32_t p_nobpl	: 16;	// Number of cache lines
	} fields;
	uint32_t value;
} T_P_CCOCR;

#ifndef CEVABX
/***********************
 * Name: T_P_ECADD
 * Register: P_ECADD
 ***********************/
typedef union
{
	struct
	{
		uint32_t 			: 5; // Reserved
		uint32_t ecadd		: 27; // Address of last 256 bits fetch-lines containing an ECC error
	} fields;
	uint32_t value;
} T_P_ECADD;

/***********************
 * Name: T_PMSSACS
 * Register: PMSSACS
 ***********************/
typedef union
{
	struct
	{
		uint32_t pmss_acs		: 16; // Enable access to PMSS shadow and safety management registers
		uint32_t p_ccosa		: 26;
	} fields;
	uint32_t value;
} T_PMSSACS;


#endif /* !CEVABX */


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	PMSS Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*****************************************************
 * E_p_sys_ou_c_total_os
 * 		Register: P_SYS_OU_C
 * 		Field: TOTAL_OS
 *		Description: Total Outstanding Request
 *****************************************************/
typedef enum
{
	P_SYS_OU_C_TOTAL_OS_ONE_OUTSTANDING  = 1,
	P_SYS_OU_C_TOTAL_OS_TWO_OUTSTANDING  = 2,
	P_SYS_OU_C_TOTAL_OS_FOUR_OUTSTANDING = 3,
	P_SYS_OU_C_TOTAL_OS_EIGHT_OUSTANDING = 4
} E_p_sys_ou_c_total_os;

#ifndef CEVABX
/*****************************************************
 * E_p_sys_ou_c_pdma_bsz
 * 		Register: P_SYS_OU_C
 * 		Field: PDMA_BSZ
 *		Description: Burst size for PDMA transaction
 *****************************************************/
typedef enum
{
  SYS_OU_C_PDMA_BSZ_TWO_BEATS     = 0,
  SYS_OU_C_PDMA_BSZ_FOUR_BEATS    = 1,
  SYS_OU_C_PDMA_BSZ_EIGHT_BEATS   = 2,
  SYS_OU_C_PDMA_BSZ_SIXTEEN_BEATS = 3
} E_p_sys_ou_c_pdma_bsz;

#endif /* !CEVABX */

/*****************************************************
 * E_p_addatt0_p_ap
 * 		Register: P_ADDx_ATT0
 * 		Field: P_AP
 *		Description: Access Protection
 *****************************************************/
typedef enum
{
	P_ADDATT0_AP_SUPER_READ_USER_READ	= 0,
	P_ADDATT0_AP_SUPER_READ_USER_NO_ACC	= 1,
	P_ADDATT0_AP_NO_ACCESS				= 3
} E_p_addatt0_p_ap;


/*****************************************************
 * E_mss_pcr_hwpf_sz
 * 		Register: MSS_PCR
 * 		Field: HWPF_SZ
 *		Description: Program Cache Hardware Pre-fetch depth
 *****************************************************/
typedef enum
{
	P_PCR_HWPF_SIZE_ONE_CACHE_LINE		= 0,
	P_PCR_HWPF_SIZE_TWO_CACHE_LINE		= 1,
	P_PCR_HWPF_SIZE_THREE_CACHE_LINE	= 2,
	P_PCR_HWPF_SIZE_FOUR_CACHE_LINE		= 3
} E_mss_pcr_hwpf_sz;

#ifndef SENSPRO_V1_2
/*****************************************************
 * E_mss_pcr_pape
 * 		Register: MSS_PCR
 * 		Field: pape
 *		Description: Access Protection Enable
 *****************************************************/
typedef enum
{
	P_PCR_PAPE_ACCESS_PROTECTION_DISABLE		= 0,
	P_PCR_PAPE_ACCESS_PROTECTION_ENABLE			= 1
} E_mss_pcr_pape;
#endif

/*****************************************************
 * E_mss_pcr_cac_pfe
 * 		Register: MSS_PCR
 * 		Field: cac_pfe
 *		Description: Cache Pre-fetch Enable
 *****************************************************/
typedef enum
{
	P_PCR_CAC_PFE_DISABLE		= 0,
	P_PCR_CAC_PFE_ENABLE		= 1
} E_mss_pcr_cac_pfe;

/*****************************************************
 * E_mss_pcr_cac_wpe
 * 		Register: MSS_PCR
 * 		Field: cac_wpe
 *		Description: Cache way prediction Enable
 *****************************************************/
typedef enum
{
	P_PCR_CAC_WPE_DISABLE		= 0,
	P_PCR_CAC_WPE_ENABLE		= 1
} E_mss_pcr_cac_wpe;

/*****************************************************
 * E_p_ccocr_p_os
 * 		Register: P_CCOCR
 * 		Field: P_OS
 *		Description: Operation Size
 *****************************************************/
typedef enum
{
	P_CCOCR_P_OS_ADDRESS_BASED		= 0,
	P_CCOCR_P_OS_ENTIRE_CACHE		= 1,
} E_p_ccocr_p_os;

/*****************************************************
 * E_CCOCR_p_ot
 * 		Register: P_CCOCR
 * 		Field: P_OT
 *		Description: Operation Type
 *****************************************************/
typedef enum
{
	P_CCOCR_OT_SW_PRE_FETCH		= 1,
	P_CCOCR_OT_LOCK				= 2,
	P_CCOCR_OT_UNLOCK			= 3,
	P_CCOCR_OT_INVALIDATE		= 4
} E_p_ccocr_p_ot;

/*****************************************************
 * E_p_addatt0_l1ic
 * 		Register: P_ADDATT0
 * 		Field: L1IC
 *		Description: L1IC cache-ability
 *****************************************************/
typedef enum
{
	P_ADDATT0_L1IC_CACHE_DISABLE = 0,
	P_ADDATT0_L1IC_CACHE_ENABLE = 1
} E_p_addatt0_l1ic;


/*****************************************************
 * E_p_addatt0_l1ic_lock
 * 		Register: P_ADDATT0
 * 		Field: L1IC_LOCK
 *		Description: L1IC lock after cache-line fill attribute
 *****************************************************/
typedef enum
{
	P_ADDATT0_L1IC_LOCK_AFTER_FILL_DISABLE = 0,
	P_ADDATT0_L1IC_LOCK_AFTER_FILL_ENABLE = 1
} E_p_addatt0_l1ic_lock;


/*****************************************************
 * E_p_addatt0_l1ic_lock
 * 		Register: P_ADDATT0
 * 		Field: L1IC_LOCK
 *		Description:AXI Bus: L2 Cache Policy for read accesses
 *****************************************************/
typedef enum
{
	P_ADDATT0_L2A_NON_BUFFERABLE = 0,
	P_ADDATT0_L2A_BUFFERABLE = 1,
	P_ADDATT0_L2A_NON_CACHEABLE_NON_BUFFERABLE = 2,
	P_ADDATT0_L2A_NON_CACHEABLE_BUFFERABLE = 3,
	P_ADDATT0_L2A_WRITE_THROUGH_NO_ALLOCATE= 10,
	P_ADDATT0_L2A_WRITE_THROUGH_READ_ALLOCATE= 14,
	P_ADDATT0_L2A_WRITE_THROUGH_WRITE_ALLOCATE= 10,
	P_ADDATT0_L2A_WRITE_THROUGH_READ_WRITE_ALLOCATE= 14,
	P_ADDATT0_L2A_WRITE_BACK_NO_ALLOCATE= 11,
	P_ADDATT0_L2A_WRITE_BACK_READ_ALLOCATE = 15,
	P_ADDATT0_L2A_WRITE_BACK_WRITE_ALLOCATE = 11,
	P_ADDATT0_L2A_WRITE_BACK_READ_WRITE_ALLOCATE = 15,
} E_p_addatt0_p_l2a;


/*****************************************************
 * E_pdma_pdtc_pdie
 * 		Register: PDTC
 * 		Field: PDIE
 *		Description: Program Task Interrupt Enable
 *****************************************************/
 typedef enum
 {
	PDMA_PDIE_INTERRUPT_DISABLE 	= 0,
	PDMA_PDIE_INTERRUPT_ENABLE 		= 1
 } E_pdma_pdtc_pdie;

#ifndef CEVABX
/****************************************************
 * PDMA Descriptor:
 * 		contains attributes configuration registers for PDMA transfers
 ****************************************************/
typedef union
{
	struct{
		uint32_t p_pdea			:32;
		uint32_t p_pdia			:32;
		uint32_t pdtc 			:19;//PDMA transfer count
		uint32_t 	  			:10;// Reserved
		uint32_t pdst 			:1;	// Read only:  PDMA status: "1" - busy, 0 - "not busy"
		uint32_t 	  			:1;	// Reserved
		uint32_t pdie 			:1;	// PDMA interrupt enable
	}fields;
	struct{
		uint32_t p_pdea;  			//external address
		uint32_t p_pdia;			//internal address
		T_P_PDTC p_pdtc;			//number of bytes transfered
	}registers;
} T_pdma_task;


#endif /* !CEVABX */

/****************************************************
 * Program region attributes:
 * 		contains attributes configuration registers
 ****************************************************/
typedef union
{
	struct
	{
		// P_ADDx_START
		uint32_t p_region_start :20; // 4KB start block of address region
		uint32_t 				:8;	 // Reserved
		uint32_t inactive 		:1;	 // Set if this region is inactive
		uint32_t 				:3;	 // Reserved
		// P_ADDx_ATT0
		uint32_t l1ic 			:1;	// L1IC cache-ability
		uint32_t l1ic_lock 		:1;	// L1IC lock after cache-line fill attribute
		uint32_t 				:2;	// Reserved
#if defined(SENSPRO) || defined(CEVABX)
		uint32_t p_ap 			:2;	// Access Protection
		uint32_t 				:2;	// Reserved
#else
		uint32_t p_ap 			:3;	// Access Protection
		uint32_t 				:1;	// Reserved
#endif
		uint32_t p_l2a 			:4;	// L2 Cache Policy for read accesses
		uint32_t 				:12;// Reserved
		uint32_t p_rqos 		:4;	// Read transaction Quality of Service
		uint32_t 				:4;	// Reserved
	}fields;
	struct{
		T_P_ADDx_START region_start; // the region start address
		T_P_ADDx_ATT0 region_att0; 	// region attributes
	}registers;
} T_pmss_region_attributes;

/****************************************************
 * Program cache attributes:
 * 		contains program cache attributes configuration registers
 ****************************************************/
typedef union
{
	struct{
		// P_CCOSAR
		uint32_t 				: 6;	// Reserved
		uint32_t p_ccosa		: 26;	// Instruction cache Operations Start Address
		//P_CCOCR
#if defined(SENSPRO) || defined(CEVABX)
		uint32_t p_active		: 1;	// L1 Intruction cache operation activeness
#else
		uint32_t 				: 1;	// Reserved
#endif
		uint32_t p_l1ico		: 1;	// L1 Intruction Cache operation completeness
		uint32_t p_ot			: 4;	// Operation Type
		uint32_t 				: 1;	// Reserved
		uint32_t p_os			: 1;	// Operation Size
		uint32_t 				: 8;	// Reserved
		uint32_t p_nobpl		: 16;	// Number of cache lines
	}fields;
	struct{
		T_P_CCOSAR p_ccosar; // Instruction cache operation start address
		T_P_CCOCR p_ccocr; // instruction cache attributes
	}registers;
} T_pmss_cache_swop_attributes;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	PMSS Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
* @function	PMSS_set_region_attributes
* @author	Anat Keidar
* @date 	24/07/2022
* @brief	Set the attributes for given region with given configuration.
*			NOTICE: It is the responsibility of the user to disable pre-fetch (PMSS_set_pre_fetch(P_PCR_CAC_PFE_DISABLE)) and invalidate the cache (PMSS_set_swop_entire_cache(P_CCOCR_OT_INVALIDATE))
*					before using PMSS_set_region_attributes.
* @param	region_num: 	Instruction region number.
* @param	p_region_attributes: 	Pointer to the program memory region settings structure.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_region_attributes(uint8_t region_num, T_pmss_region_attributes p_region_attributes ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_get_region_attributes
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Reads the current value of region attributes registers.
* @param	region_num: 			Instruction region number.
* @param	p_region_attributes: 	Pointer to the program memory region settings structure.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_get_region_attributes(uint8_t region_num, T_pmss_region_attributes *p_region_attributes ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_set_swop_address_based
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Sets a software operation that is address-based for the instruction cache.
* @param	start_address:	Start address for the operation.
* @param	operation_type:	Type of operation.
* @param	cache_lines_num: Number of cache lines for the operation.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_swop_address_based(uint32_t start_address, E_p_ccocr_p_ot operation_type, uint16_t cache_lines_num ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_set_swop_entire_cache
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Sets a software operation that is executed over the entire instruction cache.
* 		***NOTE: Software Pre-Fetch operation type not supported for entire cache software operation***
* @param	operation_type:	Type of operation.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_swop_entire_cache(E_p_ccocr_p_ot operation_type ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_enable_global_program_cache
* @author	Anat Keidar
* @date 	01/03/2021
* @brief	Enables program cache in all currently active regions.
*			NOTICE: It is the responsibility of the user to disable pre-fetch (PMSS_set_pre_fetch(P_PCR_CAC_PFE_DISABLE)) and invalidate the cache (PMSS_set_swop_entire_cache(P_CCOCR_OT_INVALIDATE))
*					before using PMSS_enable_global_program_cache.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_enable_global_program_cache(void) PRAGMA_CSECT("CSL_CODE_SECTION");


#ifndef SENSPRO_V1_2
/*********************************************************************************************
* @function	PMSS_set_access_protection
* @author	Ravid Rzaev
* @date 	28/02/2021
* @brief	Sets the policy for program access protection.
* @param	access_protection: Program access protection value.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_access_protection(E_mss_pcr_pape access_protection ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

/*********************************************************************************************
* @function	PMSS_set_pre_fetch_size
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Sets the program cache hardware pre_fetch size.
* @param	size:	 one of defined pre_fetch size.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_pre_fetch_size(E_mss_pcr_hwpf_sz size ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_set_pre_fetch
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Sets the program cache hardware pre_fetch (enable / disable).
* @param	set_prefetch:	 one of defined E_mss_pcr_cac_pfe values.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_pre_fetch(E_mss_pcr_cac_pfe set_prefetch) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_set_way_prediction
* @author	Ravid Rzaev
* @date 	08/08/2022
* @brief	sets the program cache way prediction (enable / disable).
* @param	set_way_prediction:	 one of defined E_mss_pcr_cac_wpe values.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_way_prediction(E_mss_pcr_cac_wpe set_way_prediction) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_is_cache_operation_active
* @author	Ravid Rzaev
* @date 	01/03/2021
* @brief	Check if the program cache is active.
* @return	CSL_TRUE or CSL_FALSE.
*********************************************************************************************/
bool PMSS_is_cache_operation_active(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	PMSS_set_pdma_download_task
* @author	Ravid Rzaev
* @date 	28/02/2021
* @brief	Configure, write and execute a PDMA task.
* @param	int_address: 	Internal destination program address
* @param	ext_address: 	External source program address
* @param	size: 			Transfer size
* @param	en_interrupt: 	Enable interrupt indication
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status PMSS_set_pdma_task(uint32_t int_address, uint32_t ext_address, uint32_t size, E_pdma_pdtc_pdie en_interrupt) PRAGMA_CSECT("CSL_CODE_SECTION");

/*********************************************************************************************
 * @function	PMSS_is_pdma_busy
 * @author	Ravid Rzaev
 * @date 	28/02/2021
 * @brief	Returns the PDAM status.
 * @return	 CSL_TRUE or CSL_FALSE.
*********************************************************************************************/
bool PMSS_is_pdma_busy(void) PRAGMA_CSECT("CSL_CODE_SECTION");


CSL_CPP_END


#endif /* CEVA_PMSS_H_ */

