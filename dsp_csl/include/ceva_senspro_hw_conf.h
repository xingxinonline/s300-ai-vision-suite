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
#ifndef CEVA_SENSPRO_HW_CONF_H_
#define CEVA_SENSPRO_HW_CONF_H_
/*********************************************************************************************
 * File:			ceva_senspro_hw_conf.h
 * Created on: 		02/01/2022
 * Author: 			Anat Keidar
 * Description: 	Defines the hardware configuration for SensPro. 
**********************************************************************************************/
#include "ceva_user_conf.h"
#ifdef SENSPRO

	#if defined(SENSPRO1000) || defined(SENSPRO500) || defined(SENSPRO250) || defined(SENSPRO100) || defined(SENSPRO50)

		/* @name	SENSPRO_V1_2
		 * @type	hw_conf
		 * @breif	The core is of the SensPro RTL 1.2 family
		 * */
		#define SENSPRO_V1_2

	#endif




/*********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Configurations Programming Model functions
 *
 *********************************************************************************************
 *********************************************************************************************/

#ifdef CEVA

	/*********************************************************************************************
	* @function	HW_CONF_get_idm_size
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the IDM size in KBs from the MSS.
	* @return	the IDM size in KBs
	*********************************************************************************************/
	uint32_t HW_CONF_get_idm_size(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_CONF_get_num_blks
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the number of blocks from the MSS.
	* @return	The number of blocks configured.
	*********************************************************************************************/
	uint32_t HW_CONF_get_num_blks(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_CONF_get_num_timer
	* @author	Raid Rzaev
	* @date 	28/02/2022
	* @brief	Gets the number of TIMERS.
	* @return	The number of TIMERS configured.
	*********************************************************************************************/
	uint32_t HW_CONF_get_num_timer( void ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_CONF_get_bnks_pr_blk
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the number of banks per block
	* @return	The number of banks per block configured.
	*********************************************************************************************/
	uint32_t HW_CONF_get_bnks_pr_blk(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	HW_CONF_get_ipm_size
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the size of the IPM from the MSS.
	* @return	The size of the IPM in KBs.
	*********************************************************************************************/
	uint32_t HW_CONF_get_ipm_size(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	HW_CONF_get_code_cache_size
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the size of the code cache from the MSS.
	* @return	The size of the code cache in bytes.
	*********************************************************************************************/
	uint32_t HW_CONF_get_code_cache_size(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	HW_CONF_get_qman_num
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the number of QMANs supported from the MSS.
	* @return	The number of QMANs that are supported.
	*********************************************************************************************/
	uint32_t HW_CONF_get_qman_num(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	HW_CONF_get_icu_grps_num
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the number of ICU groups that are supported from the MSS.
	* @return	The number of ICU groups that are supported.
	*********************************************************************************************/
	uint32_t HW_CONF_get_icu_grps_num(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	HW_CONF_get_vcu_units_num
	* @author	Ephi Frankel
	* @date 	02/05/2021
	* @brief	Gets the number of VCU units that are installed from the MSS.
	* @return	The number of VCU units that are installed.
	*********************************************************************************************/
	uint32_t HW_CONF_get_vcu_units_num(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_CONF_get_btb_ways
	* @author	Ephi Frankel
	* @date 	24/05/2021
	* @brief	Get the number of btb ways supported.
	* @return	The number of btb ways
	*********************************************************************************************/
	uint32_t HW_CONF_get_btb_ways(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_CONF_get_mss_hdcfg
	* @author	Anat Keidar
	* @date 	12/01/2022
	* @brief	Get the value of the given MSS_HDCFG field
	* @param	hdcfg_field:  E_HW_CONF_mss_hdcnf_filed
	* @return	The value of the given filed in the MSS_HDCFG register
	*********************************************************************************************/
	typedef enum
	{
		HW_CONF_MSS_HDCFG_BLK_NUM				= 0,
		HW_CONF_MSS_HDCFG_TCM_SIZE				= 1,
		HW_CONF_MSS_HDCFG_EDAP_AXI_WID			= 2,
		HW_CONF_MSS_HDCFG_EDP_AXI_WID			= 3,
		HW_CONF_MSS_HDCFG_AXIS0_WID				= 4,
		HW_CONF_MSS_HDCFG_AXIS1_WID				= 5,
		HW_CONF_MSS_HDCFG_AXIS2_WID				= 6,
#ifdef SENSPRO_V1_2
		HW_CONF_MSS_HDCFG_AXI_M0_WID			= 7,
		HW_CONF_MSS_HDCFG_AXI_M1_WID			= 8,
		HW_CONF_MSS_HDCFG_NUM_VCU				= 9
#else /* !SENSPRO_V1_2 */
		HW_CONF_MSS_HDCFG_BNK_NUM				= 7,
		HW_CONF_MSS_HDCFG_AXI_M_WID				= 8
#endif /* SENSPRO_V1_2 */
	}E_HW_CONF_mss_hdcnf_filed;
	uint32_t HW_CONF_get_mss_hdcfg( E_HW_CONF_mss_hdcnf_filed hdcfg_field) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	* @function	HW_CONF_get_p_hdcfg
	* @author	Anat Keidar
	* @date 	12/01/2022
	* @brief	Get the value of the given P_HDCFG field
	* @param	hdcfg_field:  E_HW_CONF_p_hdcnf_filed
	* @return	The value of the given filed in the P_HDCFG register
	*********************************************************************************************/
	typedef enum
	{
		HW_CONF_P_HDCFG_PTCM_SZE				= 0,
		HW_CONF_P_HDCFG_PCAC_SZE				= 1,
		HW_CONF_P_HDCFG_PECC					= 2,
		HW_CONF_P_HDCFG_EPP_AXI_WID				= 3,
		HW_CONF_P_HDCFG_L1ICA					= 4
	}E_HW_CONF_p_hdcnf_filed;
	uint32_t HW_CONF_get_p_hdcfg( E_HW_CONF_p_hdcnf_filed hdcfg_field) PRAGMA_CSECT("CSL_CODE_SECTION");



#endif /* CEVA */



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


/*********************************************************************************************
 *********************************************************************************************
 *
 *	 External Macro Definitions
 *
 *********************************************************************************************
 *********************************************************************************************/




//
// Core Configuration
//
///////////////

#ifndef HW_CONFIG_NUM_VCU_UNITS
	#define CSL_HW_CONFIG_NUM_VCU_UNITS            			HW_CONF_get_vcu_units_num( )
#else
	#define CSL_HW_CONFIG_NUM_VCU_UNITS            			HW_CONFIG_NUM_VCU_UNITS
#endif

#ifndef HW_CONFIG_BTB_WAYS
	#define CSL_HW_CONFIG_BTB_WAYS            				2
#else
	#define CSL_HW_CONFIG_BTB_WAYS            				HW_CONFIG_BTB_WAYS
#endif




//
// Data Memory
//
///////////////

#ifndef HW_CONFIG_NUM_BLOCKS
	#define CSL_HW_CONFIG_NUM_BLOCKS           				HW_CONF_get_num_blks( )
#else
	#define CSL_HW_CONFIG_NUM_BLOCKS            			HW_CONFIG_NUM_BLOCKS
#endif


#ifndef HW_CONFIG_NUM_BANKS_PER_BLOCK
	#define CSL_HW_CONFIG_NUM_BANKS_PER_BLOCK            	HW_CONF_get_bnks_pr_blk( )
#else
	#define CSL_HW_CONFIG_NUM_BANKS_PER_BLOCK            	HW_CONFIG_NUM_BANKS_PER_BLOCK
#endif


#ifndef HW_CONFIG_IDM_SIZE
	#define CSL_HW_CONFIG_IDM_SIZE            				HW_CONF_get_idm_size( )
#else
	#define CSL_HW_CONFIG_IDM_SIZE            				HW_CONFIG_IDM_SIZE
#endif


#ifndef HW_CONFIG_AXIS0_PRESENT
	#define CSL_HW_CONFIG_AXIS0_PRESENT           				HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXIS0_WID)
	#define CSL_NENSIRQ_AXIS0									0x00000000
#else
	#define CSL_HW_CONFIG_AXIS0_PRESENT           				HW_CONFIG_AXIS0_PRESENT
	#define CSL_NENSIRQ_AXIS0									0x00000300
#endif

#ifndef HW_CONFIG_AXIS1_PRESENT
	#define CSL_HW_CONFIG_AXIS1_PRESENT           				HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXIS1_WID)
	#define CSL_NENSIRQ_AXIS1									0x00000000
#else
	#define CSL_HW_CONFIG_AXIS1_PRESENT           				HW_CONFIG_AXIS1_PRESENT
	#define CSL_NENSIRQ_AXIS1									0x00000c00
#endif

#ifndef HW_CONFIG_AXIS2_PRESENT
	#define CSL_HW_CONFIG_AXIS2_PRESENT           				HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXIS2_WID)
	#define CSL_NENSIRQ_AXIS2									0x00000000
#else
	#define CSL_HW_CONFIG_AXIS2_PRESENT           				HW_CONFIG_AXIS2_PRESENT
	#define CSL_NENSIRQ_AXIS2									0x00003000
#endif

#ifndef HW_CONFIG_EDAP_PRESENT
	#define CSL_HW_CONFIG_EDAP_PRESENT           				HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_EDAP_AXI_WID)
	#define CSL_NENSIRQ_EDAP									0x00000000
#else
	#define CSL_HW_CONFIG_EDAP_PRESENT           				HW_CONFIG_EDAP_PRESENT
	#define CSL_NENSIRQ_EDAP									0x0000c000
#endif

#ifndef HW_CONFIG_AXIM0_PRESENT
	#ifdef SENSPRO_V1_2
		#define CSL_HW_CONFIG_AXIM0_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXI_M0_WID)
	#else
		#define CSL_HW_CONFIG_AXIM0_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXI_M_WID)
	#endif
#else
	#define CSL_HW_CONFIG_AXIM0_PRESENT           				HW_CONFIG_AXIM0_PRESENT
#endif

#ifndef HW_CONFIG_AXIM1_PRESENT
	#ifdef SENSPRO_V1_2
		#define CSL_HW_CONFIG_AXIM1_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXI_M1_WID)
	#else
		#define CSL_HW_CONFIG_AXIM1_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_AXI_M_WID)
	#endif
#else
	#define CSL_HW_CONFIG_AXIM1_PRESENT           				HW_CONFIG_AXIM1_PRESENT
#endif


#define CSL_HW_CONFIG_DATA_CACHE_SIZE							0




//
// Queue Manager (QMAN)
//
///////////////

#ifndef HW_CONFIG_NUM_QMANS

	#ifdef CEVA
		#define CSL_HW_CONFIG_NUM_QMANS 							HW_CONF_get_qman_num( )
		#define CSL_HW_CONFIG_DYNAMIC
		// CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE: The maximum number of QMANs
		#define CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE    			8

	#else
		#define CSL_HW_CONFIG_NUM_QMANS								8
		// CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE: The maximum number of QMANs
		#define CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE    			CSL_HW_CONFIG_NUM_QMANS
	#endif

#else

	#define CSL_HW_CONFIG_NUM_QMANS            						HW_CONFIG_NUM_QMANS

	// CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE: The maximum number of QMANs
	#if	(0 == HW_CONFIG_NUM_QMANS)
		#define CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE    			4
	#else /* (0 == HW_CONFIG_NUM_QMANS) */
		#define CSL_HW_CONFIG_NUM_QMANS_RESOURCE_SIZE    			CSL_HW_CONFIG_NUM_QMANS
	#endif /* (0 == HW_CONFIG_NUM_QMANS) */

#endif	




//
// Buffer Manager (BMAN)
//
///////////////

#ifndef HW_CONFIG_NUM_BMANS
	#define CSL_HW_CONFIG_NUM_BMANS            				0
#else
	#define CSL_HW_CONFIG_NUM_BMANS            				HW_CONFIG_NUM_BMANS
#endif





//
// Program Memory
//
///////////////


#ifndef HW_CONFIG_IPM_SIZE
	#define CSL_HW_CONFIG_IPM_SIZE            				HW_CONF_get_ipm_size( )
#else
	#define CSL_HW_CONFIG_IPM_SIZE            				HW_CONFIG_IPM_SIZE
#endif


#ifndef HW_CONFIG_CODE_CACHE_SIZE
	#define CSL_HW_CONFIG_CODE_CACHE_SIZE            		HW_CONF_get_code_cache_size( )
#else
	#define CSL_HW_CONFIG_CODE_CACHE_SIZE            		HW_CONFIG_CODE_CACHE_SIZE
#endif

#ifndef HW_CONFIG_NUM_TIMERS
	#define CSL_HW_CONFIG_NUM_TIMERS 						HW_CONF_get_num_timer( )
#else
	#define CSL_HW_CONFIG_NUM_TIMERS 						HW_CONFIG_NUM_TIMERS
#endif

#ifndef HW_CONFIG_PCAC_WAYS
	#define CSL_HW_CONFIG_PCAC_WAYS            				4
#else
	#define CSL_HW_CONFIG_PCAC_WAYS            				HW_CONFIG_PCAC_WAYS
#endif


#ifndef HW_CONFIG_EPP_PRESENT
	#define CSL_HW_CONFIG_EPP_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_P_HDCFG_EPP_AXI_WID)
	#define CSL_NENSIRQ_EPP									0x00000000
#else
	#define CSL_HW_CONFIG_EPP_PRESENT           			HW_CONFIG_EPP_PRESENT
	#define CSL_NENSIRQ_EPP									0x00040000
#endif

#ifndef HW_CONFIG_EDP_PRESENT
	#define CSL_HW_CONFIG_EDP_PRESENT           			HW_CONF_get_mss_hdcfg(HW_CONF_MSS_HDCFG_EDP_AXI_WID)
#else
	#define CSL_HW_CONFIG_EDP_PRESENT           			HW_CONFIG_EDP_PRESENT
#endif



//
// Interrupt Control Unit (ICU)
//
///////////////

#define CSL_HW_CONFIG_NUM_ICU_GROUPS_MAX						2
#ifndef HW_CONFIG_NUM_ICU_GROUPS
	#define CSL_HW_CONFIG_NUM_ICU_GROUPS 					HW_CONF_get_icu_grps_num()
#else
	#define CSL_HW_CONFIG_NUM_ICU_GROUPS 					HW_CONFIG_NUM_ICU_GROUPS
#endif
















/*********************************************************************************************
 *********************************************************************************************
 *
 *	 Internal Macro Definitions
 *
 *********************************************************************************************
 *********************************************************************************************/




//
// Data Memory
//
///////////////


/* @name	CSL_HW_CONFIG_BANK_ALIGN
 * @type	hw_conf
 * @breif	The alignment mask value for dma one bank transfer
 * */
#define CSL_HW_CONFIG_BANK_ALIGN 						0x7


/* @name	CSL_HW_CONFIG_BANK_WIDTH
 * @type	hw_conf
 * @breif	Configuration: Bank width size hardware configuration
 * */
#define CSL_HW_CONFIG_BANK_WIDTH					0x8


	
	#ifdef SENSPRO_V1_2
		/* @name	CSL_HW_CONFIG_DMA_DUP_BANK_TRANSFER_ALIGN
		 * @type	hw_conf
		 * @breif	The alignment mask value for dma dupliacte bank transfer
		 * */
		#define CSL_HW_CONFIG_DMA_DUP_BANK_TRANSFER_ALIGN 	((CSL_HW_CONFIG_BLOCK_WIDTH >> (CSL_HW_CONFIG_NUM_VCU_UNITS - 1)) - 1)
	#else
	
		/* @name	CSL_HW_CONFIG_DMA_DUP_BANK_TRANSFER_ALIGN
		 * @type	hw_conf
		 * @breif	The alignment mask value for dma dupliacte bank transfer
		 * */
		#define CSL_HW_CONFIG_DMA_DUP_BANK_TRANSFER_ALIGN 	CSL_HW_CONFIG_BANK_ALIGN
	
	#endif 	
	



//
// Queue Manageer (QMAN)
//
///////////////

#ifdef CSL_QMAN_SUPPORTED
	
	/* @name	CSL_HW_CONFIG_QMAN_MAX_TASK_ENABLED
	 * @type	hw_conf
	 * @breif	Maximum number of tasks enabled in one operation
	 * */
	#define	CSL_HW_CONFIG_QMAN_MAX_TASK_ENABLED				0x7FF


	/* @name	CSL_HW_CONFIG_QMAN_TASK_MULTI_DI_BANK_LINE_STRIDE
	 * @type	hw_conf
	 * @breif	The bank line stride in multi dimentions transfers
	 * */
	#define CSL_HW_CONFIG_QMAN_TASK_MULTI_DI_BANK_LINE_STRIDE 		( CSL_HW_CONFIG_BLOCK_WIDTH / CSL_HW_CONFIG_NUM_VCU_UNITS )

#endif // #ifdef CSL_QMAN_SUPPORTED





//
// Program Memory
//
///////////////


/* @name	CSL_HW_CONFIG_CODE_CACHE_FETCH_LINE_ALIGN
 * @type	hw_conf
 * @breif	The alignment mask value for code cache line
 * */
#define CSL_HW_CONFIG_CODE_CACHE_FETCH_LINE_ALIGN 		0x1FU




//
// Interrupt Control Unit (ICU)
//
///////////////

#ifdef CSL_ICU_SUPPORTED

	/* @name	CSL_HW_CONFIG_NUM_INTERRUPTS
	 * @type	hw_conf
	 * @breif	Configuration: ICU, Number of interrupts defined in the ICU.
	 *			value 32: define HW_CONFIG_NUM_ICU_GROUPS 1
	 *			value 64: define HW_CONFIG_NUM_ICU_GROUPS 2
	 * */
	#define CSL_HW_CONFIG_NUM_INTERRUPTS 			(CSL_HW_CONFIG_NUM_ICU_GROUPS * CSL_HW_CONFIG_NUM_INTERRUPTS_IN_ICU_GROUP)


	/* @name	CSL_HW_CONFIG_FISRT_INTERRUPT_VECTOR
	 * @type	hw_conf
	 * @breif	The first IVA available for configuration
	 * */
	#define CSL_HW_CONFIG_FISRT_INTERRUPT_VECTOR		2


	/* @name	CSL_HW_CONFIG_NUM_INTERRUPT_VECTORS
	 * @type	hw_conf
	 * @breif	Number of Interrupt Vector Address registers (IVAx) hardware configuration
	 * */
	#define CSL_HW_CONFIG_NUM_INTERRUPT_VECTORS			8
	
#endif // #ifdef CSL_ICU_SUPPORTED







#endif // #ifdef SENSPRO
#endif /*CEVA_SENSPRO_HW_CONF_H_*/
