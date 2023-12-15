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
#ifndef CEVA_HW_CONF_H_
#define CEVA_HW_CONF_H_
/*********************************************************************************************
 * File:			ceva_hw_conf.h
 * Created on: 		25/01/2020
 * Author: 			Anat Keidar
 * Description: 	Defines the hardware configuration. 
 *					It is the responsibility of the user to define the hardware configuration 
 *					values when not using CSL compilation script.
**********************************************************************************************/
#include "ceva_user_conf.h"



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*****************************************************
 * E_D_HDCFG_tcm_size
 * 		Register: D_HDCFG
 * 		Field: XM: TCM_SIZE; BX: IDM_SIZE
 *		Description: Data TCM size
 *****************************************************/
typedef enum
{
	DATA_TCM_64KB 		= 64,
	DATA_TCM_128KB 		= 128,
	DATA_TCM_256KB 		= 256,
	DATA_TCM_512KB 		= 512,
	DATA_TCM_1024KB 	= 1024,
	DATA_TCM_UNKNOWN 	= -1
} E_mss_hdcfg_tcm_size;


/*****************************************************
 * E_P_HDCFG_ptcm_sze
 * 		Register: P_HDCFG
 * 		Field: XM: PTCM_SZE; BX: IPM_SZE
 *		Description: Program TCM memory size
 *****************************************************/
typedef enum
{
	NO_PROGRAM_TCM 		= 0,
	PROGRAM_TCM_8KB 	= 8,
	PROGRAM_TCM_32KB 	= 32,
	PROGRAM_TCM_64KB 	= 64,
	PROGRAM_TCM_128KB 	= 128,
	PROGRAM_TCM_256KB 	= 256,
	PROGRAM_TCM_UNKNOWN = -1
} E_p_hdcfg_ptcm_sze;


/*****************************************************
 * E_P_HDCFG_ptcm_sze
 * 		Register: P_HDCFG
 * 		Field: PTCM_SZE
 *		Description: Instruction cache size
 *****************************************************/
typedef enum
{
	NO_INSTRUCTION_CACHE 		= 0,
	INSTRUCTION_CACHE_32KB 		= 32,
	INSTRUCTION_CACHE_64KB 		= 64,
	INSTRUCTION_CACHE_128KB 	= 128,
	INSTRUCTION_CACHE_256KB 	= 256,
	INSTRUCTION_CACHE_UNKNOWN 	= -1
} E_p_hdcfg_pcac_sze;


#ifdef CEVABX

	/*****************************************************
	 * E_mss_memcfg_l1dcs
	 * 		Register: MSS_MEMCFG
	 * 		Field: L1DCS
	 *		Description: Data cache size
	 *****************************************************/
	typedef enum
	{
		NO_DATA_CACHE 		= 0,
		DATA_CACHE_4KB 		= 4,
		DATA_CACHE_8KB 		= 8,
		DATA_CACHE_16KB 	= 16,
		DATA_CACHE_32KB		= 32,
		DATA_CACHE_64KB 	= 64,
		DATA_CACHE_UNKNOWN 	= -1
	} E_mss_memcfg_l1dcs;

#endif /* CEVABX */




/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Configuration Values
 *
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/*********************************************************************************************
 *********************************************************************************************
 *
 *	External Macro Definitions
 *
 *********************************************************************************************
 *********************************************************************************************
 *	The following is a list of all the target configurations macro definition which are
 *		derived from the target type and configuration, and which should be defined
 *		as part of the project symbols. if _ALLOW_DYNAMIC_HW_CONFIGS is defined, then any not defined HW_CONFIG_* will
 *		automatically be defined as a function which reads that configuration from the MSS. Also when _ALLOW_DYNAMIC_HW_CONFIGS
 *		if specific HW_CONFIG_* is not defined which is required for resource allocation, a maximal value will be used.
 *********************************************************************************************
 	HW_CONFIG_IDM_SIZE
 	HW_CONFIG_NUM_BLOCKS
 	HW_CONFIG_NUM_BANKS_PER_BLOCK
 	HW_CONFIG_IPM_SIZE
 	HW_CONFIG_CODE_CACHE_SIZE
 	HW_CONFIG_NUM_QMANS
 	HW_CONFIG_NUM_BMAN (BX, XC16)
 	HW_CONFIG_NUM_ICU_GROUPS (SensPro, BX, XC16)
 	HW_CONFIG_NUM_VCU_UNITS
 	HW_CONFIG_BTB_WAYS
 *********************************************************************************************/

#ifdef HW_CONFIG_BUS_PROTOCOL_AHB
	#define CSL_HW_CONFIG_BUS_PROTOCOL_AHB
#endif /* ifdef HW_CONFIG_BUS_PROTOCOL_AHB */


/*********************************************************************************************
 *********************************************************************************************
 *
 *	 External Macro Definitions
 *
 *********************************************************************************************
 *********************************************************************************************/

/*
 * Multi-Core Configuration
 *
 **************************/

/* @name	CSL_HW_CONFIG_MCCI_NUM
 * @type	hw_conf
 * @brief	Configuration: number of MCCI registers
 * */
#ifndef HW_CONFIG_MCCI_NUM
	#define CSL_HW_CONFIG_MCCI_NUM 						32
#else
	#define CSL_HW_CONFIG_MCCI_NUM 						HW_CONFIG_MCCI_NUM
#endif


/*
 * Timers
 *
 **************************/

/* @name	CSL_HW_CONFIG_NUM_TIMERS_MAX
 * @brief	Number of MAX timers hardware configuration
 * */
#define CSL_HW_CONFIG_NUM_TIMERS_MAX				4
#define CSL_HW_CONFIG_NUM_TIMERS_RESOURCE_SIZE 		CSL_HW_CONFIG_NUM_TIMERS_MAX





/*********************************************************************************************
 *
 * Created on: 		28/02/2021
 * Author: 			Anat Keidar
 * Description: 	Defined features with have value grater then zero in the hardware configuration or not which are supported by the DSP
 *
 **********************************************************************************************/
#if (( defined(XM6) && ( CEVA_DSP_RTL >= 130 ) ) || defined( SENSPRO ) || defined(CEVABX))
	#define CSL_TIMERS_SUPPORTED
#endif
#if (defined( SENSPRO ) || defined(CEVABX))
	#define CSL_ICU_SUPPORTED
#endif
#if !defined(HW_CONFIG_BUS_PROTOCOL_AHB)
	#define CSL_QMAN_SUPPORTED
#endif
#if defined(CSL_QMAN_SUPPORTED) && defined(CEVA) && !defined(HW_CONFIG_BUS_PROTOCOL_AHB) && defined(CEVABX)
	#define CSL_BMAN_SUPPORTED
#endif

#if ( defined( SENSPRO ) || (defined(CEVABX) &&!defined(HW_CONFIG_BUS_PROTOCOL_AHB)) )
	#define CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED
#endif



/*********************************************************************************************
 *********************************************************************************************
 *
 *	Include hardware configurations per core
 *
 *********************************************************************************************
 *********************************************************************************************/
#ifdef SENSPRO
	#include "ceva_senspro_hw_conf.h"
#elif defined(XM4)
	#include "ceva_xm4_hw_conf.h"
#elif defined(XM6)
	#include "ceva_xm6_hw_conf.h"
#elif defined CEVABX
    #include "ceva_bx_hw_conf.h"
#endif






/*********************************************************************************************
 *********************************************************************************************
 *
 *	 Internal Macro Definitions
 *
 *********************************************************************************************
 *********************************************************************************************/
#define CSL_KILOBYTE 1024


/*
 * Data Memory
 *
 **************************/


/* @name	CSL_HW_CONFIG_NUM_DACU_REGIONS
 * @type	hw_conf
 * @brief	Number of data regions in DACU hardware configuration
 * */
#define CSL_HW_CONFIG_NUM_DACU_REGIONS					8


/* @name	CSL_HW_CONFIG_FIRST_DACU_REGIONS
 * @type	hw_conf
 * @brief	The first data region in DACU hardware configuration
 * */
#define CSL_HW_CONFIG_FIRST_DACU_REGIONS 				0


/* @name	CSL_HW_CONFIG_BLOCK_WIDTH
 * @type	hw_conf
 * @brief	Configuration: Block width size hardware configuration
 * */
#define CSL_HW_CONFIG_BLOCK_WIDTH					(CSL_HW_CONFIG_BANK_WIDTH * CSL_HW_CONFIG_NUM_BANKS_PER_BLOCK)


/* @name	CSL_HW_CONFIG_BLOCK_SIZE
 * @type	hw_conf
 * @brief	Configuration: Block size hardware configuration
 * */
#define CSL_HW_CONFIG_BLOCK_SIZE					(CSL_HW_CONFIG_IDM_SIZE*0x400/CSL_HW_CONFIG_NUM_BLOCKS)


/* @name	CSL_HW_CONFIG_IDM_LAST_ADDRESS
 * @type	hw_conf
 * @brief	Last address of the Internal Data hardware configuration
 * */
#define CSL_HW_CONFIG_IDM_LAST_ADDRESS				( DMSS_get_idm_base_address() + ( ( uint32_t )CSL_HW_CONFIG_IDM_SIZE * ( uint32_t )CSL_KILOBYTE ) )
#define CSL_HW_CONFIG_IPM_LAST_ADDRESS				( CSL_HW_CONFIG_IPM_SIZE * 1024 )


#ifdef CEVA
	#define CSL_HW_CONFIG_IS_INTERNAL( _address )				( CSL_HW_CONFIG_IDM_LAST_ADDRESS >= ( uint32_t )( _address ) )
	#define CSL_HW_CONFIG_IS_EXTERNAL( _address )				( CSL_HW_CONFIG_IDM_LAST_ADDRESS <  ( uint32_t )( _address ) )
	#define CSL_HW_CONFIG_IS_PROGRAM_INTERNAL( _address )		( CSL_HW_CONFIG_IPM_LAST_ADDRESS >= ( uint32_t )( _address ) )
	#define CSL_HW_CONFIG_IS_PROGRAM_EXTERNAL( _address )		( CSL_HW_CONFIG_IPM_LAST_ADDRESS <  ( uint32_t )( _address ) )
#else /* !CEVA */
	#define CSL_HW_CONFIG_IS_INTERNAL( _address )			    1
	#define CSL_HW_CONFIG_IS_EXTERNAL( _address )				1
	#define CSL_HW_CONFIG_IS_PROGRAM_EXTERNAL( _address )		1
	#define CSL_HW_CONFIG_IS_PROGRAM_INTERNAL( _address )		1
#endif /* CEVA */




/*
 * Queue Manager (QMAN)
 *
 **************************/
#ifdef CSL_HW_CONFIG_DYNAMIC
#elif (CSL_HW_CONFIG_NUM_QMANS == 0)
	#undef CSL_QMAN_SUPPORTED
	#undef CSL_BMAN_SUPPORTED
#endif
#if (CSL_HW_CONFIG_NUM_BMANS == 0)
	#undef CSL_BMAN_SUPPORTED
#endif


#ifdef CSL_QMAN_SUPPORTED

	/* @name	CSL_HW_CONFIG_QMAN_MAX_QUEUE_SIZE
	 * @type	hw_conf
	 * @brief	Maximum QMAN queue size.
	 * */
	#define	CSL_HW_CONFIG_QMAN_MAX_QUEUE_SIZE				0x2000


	/* @name	CSL_HW_CONFIG_QMAN_MAX_DEPTH
	 * @type	hw_conf
	 * @brief	Maximum number of tasks in a QMAN queue
	 * */
	#define	CSL_HW_CONFIG_QMAN_MAX_DEPTH 					(CSL_HW_CONFIG_QMAN_MAX_QUEUE_SIZE - 1)


	/* @name	CSL_HW_CONFIG_QMAN_MIN_QUEUE_SIZE
	 * @type	hw_conf
	 * @brief	Minimum QMAN queue size.
	 * */
	#define	CSL_HW_CONFIG_QMAN_MIN_QUEUE_SIZE				3

#endif /* ifdef CSL_QMAN_SUPPORTED */




/*
 * Program Memory
 *
 **************************/


/* @name	CSL_HW_CONFIG_IACU_FIRST_REGION
 * @type	hw_conf
 * @brief	The first IACU region
 * */
#define CSL_HW_CONFIG_IACU_FIRST_REGION 0



/* @name	CSL_HW_CONFIG_NUM_IACU_REGIONS
 * @type	hw_conf
 * @brief	Number of region in IACU hardware configuration
 * */
#define CSL_HW_CONFIG_NUM_IACU_REGIONS					8


/* @name	CSL_HW_CONFIG_CODE_CACHE_LINE_SIZE
 * @type	hw_conf
 * @brief	Configuration: Code Cache Line Size hardware configuration
 * */
#define CSL_HW_CONFIG_CODE_CACHE_LINE_SIZE			64 /* bytes */


/* @name	CSL_HW_CONFIG_CODE_CACH_SIZE_BYTES
 * @type	hw_conf
 * @brief	The code cache size in bytes
 * */
#define CSL_HW_CONFIG_CODE_CACH_SIZE_BYTES				(CSL_HW_CONFIG_CODE_CACHE_SIZE * CSL_KILOBYTE)


/* @name	CSL_HW_CONFIG_MAX_OF_CODE_CACHE_LINES
 * @type	hw_conf
 * @brief	The maximum number of code cache lines
 * */
#define CSL_HW_CONFIG_MAX_OF_CODE_CACHE_LINES				(CSL_HW_CONFIG_CODE_CACH_SIZE_BYTES / CSL_HW_CONFIG_CODE_CACHE_LINE_SIZE)





/*
 * Interrupt Control Unit (ICU)
 *
 **************************/

#ifdef CSL_ICU_SUPPORTED

	/* @name	CSL_HW_CONFIG_NUM_INTERRUPTS_IN_ICU_GROUP
	 * @type	hw_conf
	 * @brief	Internal Data Size hardware configuration
	 * */
	#define CSL_HW_CONFIG_NUM_INTERRUPTS_IN_ICU_GROUP	32



	/* @name	CSL_HW_CONFIG_NUM_POTED_INTERRUPTS
	 * @type	hw_conf
	 * @brief	Number of posted interrupts
	 * */
	#define CSL_HW_CONFIG_NUM_POSTED_INTERRUPTS			4


	/* @name	CSL_HW_CONFIG_NUM_ICU_GROUPS_RESOURCE_SIZE
	 * @type	hw_conf
	 * @brief	The size of the ICU resource
	 * */
	#define CSL_HW_CONFIG_NUM_ICU_GROUPS_RESOURCE_SIZE 		(CSL_HW_CONFIG_NUM_INTERRUPTS_IN_ICU_GROUP * CSL_HW_CONFIG_NUM_ICU_GROUPS_MAX)

#endif /* ifdef CSL_ICU_SUPPORTED */






/*
 * Profiler
 *
 **************************/


/* @name	CSL_HW_CONFIG_PROFILER_NUM_COUNTERS
 * @type	hw_conf
 * @brief	Number of profiler counters hardware configuration
 * */
#define CSL_HW_CONFIG_PROFILER_NUM_COUNTERS			8









#endif /* CEVA_HW_CONF_H_ */
