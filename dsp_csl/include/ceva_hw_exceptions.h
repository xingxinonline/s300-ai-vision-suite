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
#ifndef CEVA_XM_HW_EXCEPTIONS
#define CEVA_XM_HW_EXCEPTIONS
/*********************************************************************************************
 * File:			ceva_hw_exceptions.h
 * Created on: 		16/02/2021
 * Author: 			Anat Keidar
 * Description: 	Define the structure, configuration values and function of
					the Hardware Exceptions Programming model
**********************************************************************************************/
#include "ceva_assert.h"


CSL_CPP_START




/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Exceptions Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/





/*********************************************************************************************
  * @struct		T_MAPAR
  * @register	MAPAR
  **********************************************************************************************/
typedef union T_MAPAR
{
	struct
	{
		uint32_t mapa   :32; // Memory Access Protection Address (DATA)
	} fields;
	uint32_t value;
} T_MAPAR;


/*********************************************************************************************
  * @struct		T_DBG_DDAM
  * @register	DBG_DDAM
  **********************************************************************************************/
typedef union T_DBG_DDAM
{
	struct
	{
		uint32_t dmadam   :32; // DMA data address match (to initial a breakpoint)
	} fields;
	uint32_t value;
} T_DBG_DDAM;


/*********************************************************************************************
 * @struct		T_DBG_DDS
 * @register	DBG_DDS
 **********************************************************************************************/
typedef union T_DBG_DDS
{
	struct
	{
		uint32_t dmadamst :3;  // Indicates a DMA address match occurrence (according to type)
		uint32_t 		  :29;
	} fields;
	uint32_t value;
} T_DBG_DDS;


/*********************************************************************************************
 * @struct		T_DBG_DDC
 * @register	DBG_DDC
 **********************************************************************************************/
typedef union T_DBG_DDC
{
	struct
	{
		uint32_t dmadams :3;  // DMA breakpoint match type selection
		uint32_t 		 :29;
	} fields;
	uint32_t value;
} T_DBG_DDC;



/*********************************************************************************************
 * @struct		T_XCI_COR
 * @register	XCI_COR
 **********************************************************************************************/
typedef union
{
	struct
	{
		uint32_t int_count  	: 4;
		uint32_t 			  	:28;
	} fields;
	uint32_t value;
} T_XCI_COR;




/*********************************************************************************************
 * 
 *			XM4 , XM6
 * 
 **********************************************************************************************/
#if defined(XM4) || defined(XM6)

	/*********************************************************************************************
	 * @struct		T_DBG_GEN
	 * @register	DBG_GEN
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t gvi				: 1;
			uint32_t er_iop				: 1;
			uint32_t er_epp				: 1;
			uint32_t er_edp				: 1;
			uint32_t					: 1;
			uint32_t er_exok			: 1;
			uint32_t edap_r_oor			: 1;
			uint32_t edap_w_oor			: 1;
			uint32_t axis0_r_oor		: 1;
			uint32_t axis0_w_oor		: 1;
			uint32_t axis1_r_oor		: 1;
			uint32_t axis1_w_oor		: 1;
			uint32_t axis2_r_oor		: 1;
			uint32_t axis2_w_oor		: 1;
			uint32_t 					: 3;
			uint32_t ddam_rg_cros		: 1;
			uint32_t lsu_rd_rg_cros		: 1;
			uint32_t lsu_wr_rg_cros		: 1;
			uint32_t ddam_idm_cros		: 1;
			uint32_t lsu_idm_cros		: 1;
			uint32_t wb_idm_cros		: 1;
			uint32_t hist_no_tcm		: 1;
			uint32_t qman_idm_cros		: 1;
			uint32_t 					: 1;
			uint32_t unmapped_excptn	: 1;
			uint32_t stack_viol_excptn	: 1;
			uint32_t orflw_excptn		: 1;
			uint32_t 					: 1;
			uint32_t er_axim0			: 1;
			uint32_t er_axim1			: 1;
		} fields;
		uint32_t value;
	} T_DBG_GEN;
		
	typedef T_DBG_GEN T_DBG_GEN_MASK;



	/*********************************************************************************************
	 * @struct		T_DBG_GEN2
	 * @register	DBG_GEN2
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t ld_blank_acc		: 1;
			uint32_t st_blank_acc		: 1;
			uint32_t					: 1;
			uint32_t ddma_blank_acc		: 1;
			uint32_t qman_blank_acc		: 1;
			uint32_t exc_e				: 1;
			uint32_t hist_overflow		: 1;
			uint32_t hist_ov			: 1;
			uint32_t wdog_min			: 1;
			uint32_t wdog_max			: 1;
			uint32_t eppwdog_v			: 1;
			uint32_t edpwdog_v			: 1;
			uint32_t iopwdog_v			: 1;
			uint32_t am0wdog_v			: 1;
			uint32_t am1wdog_v			: 1;
			uint32_t 					: 1;
			uint32_t div_0_v			: 1;
			uint32_t undef_opc			: 1;
			uint32_t 					: 1;
			uint32_t p_mapv				: 1;
			uint32_t d_mapv				: 1;
			uint32_t qman_v				: 1;
			uint32_t 					: 8;
			uint32_t gvi_noncr			: 1;
			uint32_t gvi_cr			    : 1;
		} fields;
		uint32_t value;
	} T_DBG_GEN2;

	typedef T_DBG_GEN2 T_DBG_GEN2_MASK;



	typedef union T_P_MAPAR
	{
		struct
		{
			uint32_t mapa   :32; // Memory Access Protection Address (PROGRAM)
		} fields;
		uint32_t value;
	} T_P_MAPAR;

	typedef union T_P_MAPSR
	{
		struct
		{
			uint32_t mapv   :1; // Memory Access violation
			uint32_t om	    :2; // Operation mode
			uint32_t  	    :29; // Operation mode
		} fields;
		uint32_t value;
	} T_P_MAPSR;


	typedef union T_MAPSR
	{
		struct
		{
			uint32_t mapv   :1; // Memory Access violation
			uint32_t om	    :2; // Operation mode
			uint32_t ap	    :3; // Access protection
			uint32_t at	    :2; // Access type
			uint32_t  	    :24; // Operation mode
		} fields;
		uint32_t value;
	} T_MAPSR;


	
	/*********************************************************************************************
	 * @struct		T_hw_exceptions_violation_status
	 * @registers	DBG_GEN, DBG_GEN2
	 **********************************************************************************************/
	typedef struct
	{
		T_DBG_GEN dbg_gen;
		T_DBG_GEN2 dbg_gen2;
	} T_hw_exceptions_violation_status;


#endif /* defined(XM4) || defined(XM6) */











/*********************************************************************************************
 * 
 *			CEVABX
 * 
 **********************************************************************************************/

#ifdef CEVABX


		/*********************************************************************************************
		 * @struct		T_DBG_GEN
		 * @register	DBG_GEN
		 **********************************************************************************************/
		typedef union
		{
			struct
			{
				uint32_t 					: 1;
				uint32_t er_iop				: 1;
				uint32_t er_epp				: 1;
				uint32_t er_edp				: 1;
				uint32_t					: 1;
				uint32_t er_exok			: 1;
				uint32_t 					: 11;
				uint32_t ddam_rg_cros		: 1;
				uint32_t lsu_rd_rg_cros		: 1;
				uint32_t lsu_wr_rg_cros		: 1;
				uint32_t ddam_idm_cros		: 1;
				uint32_t lsu_idm_cros		: 1;
				uint32_t wb_idm_cros		: 1;
				uint32_t 					: 1;
				uint32_t qman_idm_cros		: 1;
				uint32_t er_bman_pktsize	: 1;
				uint32_t unmapped_excptn	: 1;
				uint32_t 					: 3;
				uint32_t er_axim0			: 1;
				uint32_t er_axim1			: 1;
			} fields;
			uint32_t value;
		} T_DBG_GEN;

		typedef T_DBG_GEN T_DBG_GEN_MASK;


	/*********************************************************************************************
	 * @struct		T_hw_exceptions_violation_status
	 * @registers	DBG_GEN
	 **********************************************************************************************/
	typedef struct
	{
		T_DBG_GEN dbg_gen;
	} T_hw_exceptions_violation_status;



	/*********************************************************************************************
	 * @struct		T_CENSIRQ
	 * @register	CENSIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct 
		{
			uint32_t cnse				: 1;
			uint32_t cnsipv				: 1;
			uint32_t cnsilop			: 1;
			uint32_t 					: 1;
			uint32_t cnsire				: 1;
			uint32_t					: 1;
			uint32_t div_0_v 			: 1;
			uint32_t stack_viol_excptn  : 1;
			uint32_t					: 6;
			uint32_t in_priv			: 1;
			uint32_t out_priv			: 1;
			uint32_t ld_priv_acc		: 1;
			uint32_t st_priv_acc		: 1;
			uint32_t ld_blank_acc		: 1;
			uint32_t st_blank_acc		: 1;
			uint32_t ddma_blank_acc		: 1;
			uint32_t qman_blank_acc		: 1;
			uint32_t exc_e				: 1;
			uint32_t 					: 9;
		} fields;
		uint32_t value;
	} T_CENSIRQ;

	typedef  T_CENSIRQ T_M_CENSIRQ;




	/*********************************************************************************************
	 * @struct		T_NENSIRQ
	 * @register	NENSIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 				: 1;
			uint32_t div_0_v 		: 1;
			uint32_t ovrflw_excptn  : 1;
			uint32_t 				: 5;
			uint32_t axis0_r_oor	: 1;
			uint32_t axis0_w_oor	: 1;
			uint32_t axis1_r_oor	: 1;
			uint32_t axis1_w_oor	: 1;
			uint32_t axis2_r_oor	: 1;
			uint32_t axis2_w_oor	: 1;
			uint32_t edap_r_oor		: 1;
			uint32_t edap_w_oor		: 1;
			uint32_t 				: 16;
		} fields;
		uint32_t value;
	} T_NENSIRQ;


	/*********************************************************************************************
	 * @struct		T_NENSIRQ_M
	 * @register	NENSIRQ_M
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 				: 1;
			uint32_t div_0_v 		: 1;
			uint32_t ovrflw_excptn  : 1;
			uint32_t 				: 5;
			uint32_t axis0_r_oor	: 1;
			uint32_t axis0_w_oor	: 1;
			uint32_t axis1_r_oor	: 1;
			uint32_t axis1_w_oor	: 1;
			uint32_t axis2_r_oor	: 1;
			uint32_t axis2_w_oor	: 1;
			uint32_t edap_r_oor		: 1;
			uint32_t edap_w_oor		: 1;
			uint32_t 				: 2;
			uint32_t 				: 1;
			uint32_t 				:13;
		} fields;
		uint32_t value;
	} T_NENSIRQ_M;

	typedef T_NENSIRQ_M T_M_NENSIRQ;




	/*********************************************************************************************
	 * @struct		T_TIMER_IRQ
	 * @register	TIMER_IRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t timer0_irq 	:1; // TIMER0 interrupt
			uint32_t timer1_irq 	:1; // TIMER1 interrupt
			uint32_t timer2_irq 	:1; // TIMER2 interrupt
			uint32_t timer3_irq 	:1; // TIMER3 interrupt
			uint32_t 				:4; // Reserved
			uint32_t timer0_mask 	:1; // TIMER0 interrupt mask
			uint32_t timer1_mask 	:1; // TIMER1 interrupt mask
			uint32_t timer2_mask 	:1; // TIMER2 interrupt mask
			uint32_t timer3_mask 	:1; // TIMER3 interrupt mask
			uint32_t 				:20; // Reserved
		} fields;
		struct
		{
			uint32_t timerx_irq 	:4; // TIMERx interrupt
			uint32_t 				:4; // Reserved
			uint32_t timerx_mask 	:4; // TIMERx interrupt mask
			uint32_t 				:20; // Reserved
		};
		uint32_t value;
	} T_TIMER_IRQ;

	typedef T_TIMER_IRQ T_TIMER_IRQ_M;


	/*********************************************************************************************
	 * @struct		T_DBG_DESC_ID
	 * @register	DBG_DESC_ID
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t q0_blank_acc	: 1;
			uint32_t q1_blank_acc	: 1;
			uint32_t q2_blank_acc	: 1;
			uint32_t q3_blank_acc	: 1;
			uint32_t 				: 27;
			uint32_t mstr_task	 	: 1; // DDMA interrupt indication
		} fields;
		uint32_t value;
	} T_DBG_DESC_ID;

		typedef T_DBG_DESC_ID T_MSS_DDESC_ID;

	/*********************************************************************************************
	 * @struct		T_DBG_QMAN_ID
	 * @register	DBG_QMAN_ID
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t q0_blank_acc	: 1;
			uint32_t q1_blank_acc	: 1;
			uint32_t q2_blank_acc	: 1;
			uint32_t q3_blank_acc	: 1;
			uint32_t 				: 4;
			uint32_t 				: 24;
		} fields;
		uint32_t value;
	} T_DBG_QMAN_ID;


	/*********************************************************************************************
	 * @struct		T_DBG_DUNMPD
	 * @register	DBG_DUNMPD
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t dexcptn_unmapd  			: 8;
			uint32_t 					  		: 24;
		} fields;
		uint32_t value;
	} T_DBG_DUNMPD;

	typedef T_DBG_DUNMPD T_DBG_DUNMPD_MSK;



#endif /* CEVABX */







/*********************************************************************************************
 * 
 *			SENSPRO
 * 
 **********************************************************************************************/

#if defined(SENSPRO)

	/*********************************************************************************************
	 * @struct		T_CENSIRQ
	 * @register	CENSIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct 
		{
			uint32_t cnse				: 1;
			uint32_t cnsipv				: 1;
			uint32_t cnsilop			: 1;
			uint32_t 					: 1;
			uint32_t cnsire				: 1;
			uint32_t					: 3;
			uint32_t in_priv			: 1;
			uint32_t out_priv			: 1;
			uint32_t ld_priv_acc		: 1;
			uint32_t st_priv_acc		: 1;
			uint32_t ld_blank_acc		: 1;
			uint32_t st_blank_acc		: 1;
			uint32_t ld_rg_cros			: 1;
			uint32_t st_rg_cros			: 1;
			uint32_t unmapped_excptn	: 1;
			uint32_t stack_viol_excptn	: 1;
			uint32_t exc_e				: 1;
			uint32_t er_exok			: 1;
			uint32_t ld_idm_cros		: 1;
			uint32_t st_idm_cros		: 1;
			uint32_t vld_adr_err		: 1;
			uint32_t vst_adr_err		: 1;
			uint32_t hist_idm_cros		: 1;
			uint32_t wld_err			: 1;
			uint32_t 					: 6;
		} fields;
		uint32_t value;
	} T_CENSIRQ;



	/*********************************************************************************************
	 * @struct		T_CENSIRQ_S
	 * @register	CENSIRQ_S
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 					: 1;
			uint32_t cnsipv				: 1;
			uint32_t cnsilop			: 1;
			uint32_t 					: 1;
			uint32_t cnsire				: 1;
			uint32_t					: 3;
			uint32_t in_priv			: 1;
			uint32_t out_priv			: 1;
			uint32_t ld_priv_acc		: 1;
			uint32_t st_prit_acc		: 1;
			uint32_t ld_blank_acc		: 1;
			uint32_t st_blank_acc		: 1;
			uint32_t ld_rg_cros			: 1;
			uint32_t st_rg_cros			: 1;
			uint32_t 					: 1;
			uint32_t stack_viol_excptn	: 1;
			uint32_t exc_e				: 1;
			uint32_t er_exok			: 1;
			uint32_t ld_idm_cros		: 1;
			uint32_t st_idm_cros		: 1;
			uint32_t vld_adr_err		: 1;
			uint32_t vst_adr_err		: 1;
			uint32_t hist_idm_cros		: 1;
			uint32_t wld_err			: 1;
			uint32_t 					: 6;
		} fields;
		uint32_t value;
	} T_CENSIRQ_S;



	/*********************************************************************************************
	 * @struct		T_CENSIRQ2
	 * @register	CENSIRQ2
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 					: 1;
			uint32_t ddma_err_acc		: 1;
			uint32_t qman_err_acc		: 1;
			uint32_t qman_idm_cros		: 1;
			uint32_t 					: 3;
			uint32_t ddma_rg_cros		: 1;
			uint32_t ddma_idm_cros		: 1;
			uint32_t 					: 1;
			uint32_t er_iop				: 1;
			uint32_t er_epp_dma			: 1;
			uint32_t er_edp				: 1;
			uint32_t er_axim0			: 1;
			uint32_t er_axim1	 		: 1;
			uint32_t 					:15;
			uint32_t d_ucserr			: 1;
			uint32_t p_ucserr			: 1;
		} fields;
		uint32_t value;
	} T_CENSIRQ2;

	/*********************************************************************************************
	 * @struct		T_CENSIRQ2_S
	 * @register	CENSIRQ2_S
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 					: 7;
			uint32_t ddma_rg_cros		: 1;
			uint32_t ddma_idm_cros		: 1;
			uint32_t 					: 1;
			uint32_t er_iop				: 1;
			uint32_t er_epp_dma			: 1;
			uint32_t er_edp				: 1;
			uint32_t er_axim0			: 1;
			uint32_t er_axim1	 		: 1;
			uint32_t 					:17;
		} fields;
		uint32_t value;
	} T_CENSIRQ2_S;




	/*********************************************************************************************
	 * @struct		T_CWDOGIRQ
	 * @register	CWDOGIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t cnse				: 1;
			uint32_t 					:15;
			uint32_t wdog_max			: 1;
			uint32_t wdog_min			: 1;
			uint32_t 					: 2;
			uint32_t icuwd				: 1;
			uint32_t 					: 6;
			uint32_t am1wdog_v			: 1;
			uint32_t am0wdog_v			: 1;
			uint32_t iopwdog_v			: 1;
			uint32_t edpwdog_v			: 1;
			uint32_t eppwdog_v	 		: 1;
		} fields;
		uint32_t value;
	} T_CWDOGIRQ;



	/*********************************************************************************************
	 * @struct		T_CWDOGIRQ_S
	 * @register	CWDOGIRQ_S
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 					:16;
			uint32_t wdog_max			: 1;
			uint32_t wdog_min			: 1;
			uint32_t 					: 2;
			uint32_t icuwd				: 1;
			uint32_t 					: 6;
			uint32_t am1wdog_v			: 1;
			uint32_t am0wdog_v			: 1;
			uint32_t iopwdog_v			: 1;
			uint32_t edpwdog_v			: 1;
			uint32_t eppwdog_v	 		: 1;
		} fields;
		uint32_t value;
	} T_CWDOGIRQ_S;





	/*********************************************************************************************
	 * @struct		T_NENSIRQ
	 * @register	NENSIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t nnse 			: 1;
			uint32_t div_0_v 		: 1;
			uint32_t ovrflw_excptn  : 1;
			uint32_t 				: 5;
			uint32_t axis0_r_oor	: 1;
			uint32_t axis0_w_oor	: 1;
			uint32_t axis1_r_oor	: 1;
			uint32_t axis1_w_oor	: 1;
			uint32_t axis2_r_oor	: 1;
			uint32_t axis2_w_oor	: 1;
			uint32_t edap_r_oor		: 1;
			uint32_t edap_w_oor		: 1;
			uint32_t 				: 16;
		} fields;
		uint32_t value;
	} T_NENSIRQ;


	/*********************************************************************************************
	 * @struct		T_NENSIRQ_M
	 * @register	NENSIRQ_M
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t nnse 			: 1;
			uint32_t div_0_v 		: 1;
			uint32_t ovrflw_excptn  : 1;
			uint32_t 				: 5;
			uint32_t axis0_r_oor	: 1;
			uint32_t axis0_w_oor	: 1;
			uint32_t axis1_r_oor	: 1;
			uint32_t axis1_w_oor	: 1;
			uint32_t axis2_r_oor	: 1;
			uint32_t axis2_w_oor	: 1;
			uint32_t edap_r_oor		: 1;
			uint32_t edap_w_oor		: 1;
			uint32_t 				: 2;
			uint32_t 				: 1;
			uint32_t 				:13;
		} fields;
		uint32_t value;
	} T_NENSIRQ_M;


	/*********************************************************************************************
	 * @struct		T_NENSIRQ_S
	 * @register	NENSIRQ_S
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t 	 			: 1;
			uint32_t div_0_v 		: 1;
			uint32_t ovrflw_excptn  : 1;
			uint32_t 				: 5;
			uint32_t axis0_r_oor	: 1;
			uint32_t axis0_w_oor	: 1;
			uint32_t axis1_r_oor	: 1;
			uint32_t axis1_w_oor	: 1;
			uint32_t axis2_r_oor	: 1;
			uint32_t axis2_w_oor	: 1;
			uint32_t edap_r_oor		: 1;
			uint32_t edap_w_oor		: 1;
			uint32_t 				: 2;
			uint32_t epp_cf_err		: 1;
			uint32_t 				:13;
		} fields;
		uint32_t value;
	} T_NENSIRQ_S;




	/*********************************************************************************************
	 * @struct		T_TIMER_IRQ
	 * @register	TIMER_IRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t timer0_irq 	:1; // TIMER0 interrupt
			uint32_t timer1_irq 	:1; // TIMER1 interrupt
			uint32_t timer2_irq 	:1; // TIMER2 interrupt
			uint32_t timer3_irq 	:1; // TIMER3 interrupt
			uint32_t 				:28; // Reserved
		} fields;
		struct
		{
			uint32_t timerx_irq 	:4; // TIMERx interrupt
			uint32_t 				:28; // Reserved
		};
		uint32_t value;
	} T_TIMER_IRQ;


	/*********************************************************************************************
	 * @struct		T_TIMER_IRQ_M
	 * @register	TIMER_IRQ_M
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t timer0_irq 	:1; // TIMER0 interrupt
			uint32_t timer1_irq 	:1; // TIMER1 interrupt
			uint32_t timer2_irq 	:1; // TIMER2 interrupt
			uint32_t timer3_irq 	:1; // TIMER3 interrupt
			uint32_t 				:28; // Reserved
		} fields;
		struct
		{
			uint32_t timerx_mask 	:4; // TIMERx interrupt mask
			uint32_t 				:28; // Reserved
		};
		uint32_t value;
	} T_TIMER_IRQ_M;

	/*********************************************************************************************
	 * @struct		T_TIMER_IRQ_S
	 * @register	TIMER_IRQ_S
	 **********************************************************************************************/
	typedef T_TIMER_IRQ T_TIMER_IRQ_S;



	/*********************************************************************************************
	 * @struct		T_DMA_IRQ
	* @register	DMA_IRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t ddma_irq 	:1; // Data DMA interrupt
			uint32_t pdma_irq 	:1; // Program DMA interrupt
			uint32_t 			:30;// Reserved
		} fields;
		uint32_t value;
	} T_DMA_IRQ;

	/*********************************************************************************************
	 * @struct		T_DMA_IRQ_S
	 * @register	DMA_IRQ_S
	 **********************************************************************************************/
	typedef T_DMA_IRQ T_DMA_IRQ_S;



	/*********************************************************************************************
	 * @struct		T_NQBIRQ
	 * @register	NQBIRQ
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t nqbirq 			: 1;
			uint32_t qman_irq_status 	: 1;
			uint32_t qman_qfull		 	: 1;
			uint32_t					: 5;
			uint32_t snoop_csr0		 	: 1;
			uint32_t snoop_csr1		 	: 1;
			uint32_t 					:22;
		} fields;
		uint32_t value;
	} T_NQBIRQ;

	/*********************************************************************************************
	 * @struct		T_NQBIRQ_M
	 * @register	NQBIRQ_M
	 **********************************************************************************************/
	typedef T_NQBIRQ T_NQBIRQ_M;



	typedef struct
	{
		T_CENSIRQ_S censirq_s;
		T_CENSIRQ2_S censirq2_s;
		T_CWDOGIRQ_S cwdogirq_s;
		T_NENSIRQ_S nensirq_s;
		T_TIMER_IRQ_S timer_irq_s;
		T_DMA_IRQ_S dma_irq_s;
	} T_hw_exceptions_shadow_irq_regs;

#endif /* defined( SENSPRO ) */






/*********************************************************************************************
 * 
 *			SENSPRO, CEVABX
 * 
 **********************************************************************************************/

#if defined(SENSPRO) || defined(CEVABX)


	/*********************************************************************************************
	 * @struct		T_hw_exceptions_critical_irq_status
	 * @registers	CENSIRQ, CENSIRQ2
	 **********************************************************************************************/
	typedef struct
	{
		T_CENSIRQ censirq;
		
		#ifdef SENSPRO
			T_CENSIRQ2 censirq2;
		#endif /* SENSPRO */

	} T_hw_exceptions_critical_irq_status;




	/*********************************************************************************************
	 * @struct		T_POSCINT
	 * @register	POSCINT
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t pcint0en 	:1; // Enable posted core interrupt 0
			uint32_t pcint1en 	:1; // Enable posted core interrupt 1
			uint32_t pcint2en 	:1; // Enable posted core interrupt 2
			uint32_t pcint3en 	:1; // Enable posted core interrupt 3
			uint32_t 			:4; // Reserved
			uint32_t pcint0st 	:1; // Status of posted core interrupt 0
			uint32_t pcint1st 	:1; // Status of posted core interrupt 1
			uint32_t pcint2st 	:1; // Status of posted core interrupt 2
			uint32_t pcint3st 	:1; // Status of posted core interrupt 3
			uint32_t 			:20; // Reserved
		} fields;
		struct
		{
			uint32_t pcintxen	: 4;  // Enable posted core interrupts
			uint32_t 		 	: 4;  // Reserved
			uint32_t pcintxst 	: 4;  // Status of posted core interrupts
			uint32_t 			:20;  // Reserved
		} group_fields;
		uint32_t value;
	} T_POSCINT;
	
	
#endif // defined((SENSPRO) || defined(CEVABX)





/*********************************************************************************************
 * 
 *			SENSPRO, XM4 , XM6
 * 
 **********************************************************************************************/
#if defined(XM4) || defined(XM6) || defined(SENSPRO)


	/*********************************************************************************************
	 * @struct		T_UOP_STS
	 * @register	UOP_STS
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t syuop	 			: 1;
			uint32_t ls0uop			 	: 1;
			uint32_t ls1uop			 	: 1;
			uint32_t sclrop				: 1;
			uint32_t 					: 3;
			uint32_t pcuop				: 1;
			uint32_t vpu0op				: 1;
			uint32_t vpu1op				: 1;
			uint32_t mav			 	: 1;
			uint32_t lvpuop			 	: 1;
			uint32_t 					:20;
		} fields;
		uint32_t value;
	} T_UOP_STS;



	/*********************************************************************************************
	 * @struct		T_DBG_DESC_ID
	 * @register	DBG_DESC_ID
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t q0_blank_acc	: 1;
			uint32_t q1_blank_acc	: 1;
			uint32_t q2_blank_acc	: 1;
			uint32_t q3_blank_acc	: 1;
			uint32_t q4_blank_acc	: 1;
			uint32_t q5_blank_acc	: 1;
			uint32_t q6_blank_acc	: 1;
			uint32_t q7_blank_acc	: 1;
			uint32_t 				: 8;
			uint32_t mstr_blank_acc	: 1;
			uint32_t 				: 15;
		} fields;
		uint32_t value;
	} T_DBG_DESC_ID;


	/*********************************************************************************************
	 * @struct		T_DBG_QMAN_ID
	 * @register	DBG_QMAN_ID
	 **********************************************************************************************/
	typedef union
	{
		struct
		{
			uint32_t q0_blank_acc	: 1;
			uint32_t q1_blank_acc	: 1;
			uint32_t q2_blank_acc	: 1;
			uint32_t q3_blank_acc	: 1;
			uint32_t q4_blank_acc	: 1;
			uint32_t q5_blank_acc	: 1;
			uint32_t q6_blank_acc	: 1;
			uint32_t q7_blank_acc	: 1;
			uint32_t 				: 24;
		} fields;
		uint32_t value;
	} T_DBG_QMAN_ID;

#endif /* defined(XM4) || defined(XM6) || defiened(SENSPRO) */










/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Exceptions Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
 * @enum		E_acs_access_code
 * @brief		Access code for shadow registers (part of safety management register)
 **********************************************************************************************/
typedef enum
{
	ACS_ACCESS_CODE_PMSS			= 0xDAC5U,
	ACS_ACCESS_CODE_DBG 			= 0xDAC5U,
    ACS_ACCESS_CODE_WD  			= 0xCE7AU,
} E_acs_access_code;



/*******************************************
 * @enum		E_DBG_DDS_dmadamst
 * @register	DBG_DDS
 * @field		DMADAMST
 * @brief		Indicates a DMA address match occurrence.
 ********************************************/
typedef enum
{
	DBG_DDS_DMA_BP_T_DISABLE 		  = 0,
	DBG_DDS_DMA_BP_T_INTADD_INT_EXT   = 1,
	DBG_DDS_DMA_BP_T_INTADD_EXT_INT   = 2,
	DBG_DDS_DMA_BP_T_INTADD_R_INT_INT = 3,
	DBG_DDS_DMA_BP_T_INTADD_W_INT_INT = 4,
	DBG_DDS_DMA_BP_T_EXTADD_INT_EXT   = 5,
	DBG_DDS_DMA_BP_T_EXTADD_EXT_INT   = 6,
	DBG_DDS_DMA_BP_T_TWO_MATCH 		  = 7
}E_dbg_dds_dmadamst;



/**
* @brief PSU power save modes
*/
/*******************************************
 * @enum		E_psvm_pmod
 * @register	DBG_DDS
 * @field		DMADAMST
 * @brief		Indicates a DMA address match occurrence.
 ********************************************/
typedef enum
{
	PSVM_PMOD_FREE_RUN 		= 0,          // All clocks are enabled
	PSVM_PMOD_DYNAMIC 		= 1,          // Dynamic Power Save - automatic clock gating for active units
	PSVM_PMOD_LIGHT_SLEEP 	= 2,          // The core and WB clocks are shut down
	PSVM_PMOD_STANDBY     	= 3           // All clock are shut down and can also be shut down externally
} E_psvm_pmod;

/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Hardware Exceptions Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
* @function	HW_EXCPTIONS_set_stack_limits
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Set the given stack limits in order to detect stack violations.
* @param	stack_start: 	The start address of the stack (The higher address)
* @param	stack_end: 		The end address of the stack (The lower address)
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_set_stack_limits(uint32_t stack_start, uint32_t stack_end ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************************
* @function	HW_EXCPTIONS_set_dma_break_point
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Set the DMA breakpoint and enable it.
* @param	dma_address_bp: 	The address to which to perform the breakpoint
* @param	dma_type_bp: 		The DMA breakpoint type
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_set_dma_break_point( uint32_t dma_address_bp, E_dbg_dds_dmadamst dma_type_bp  ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_dma_break_point
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Clear the DMA breakpoint.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_dma_break_point(void) PRAGMA_CSECT("CSL_CODE_SECTION");



#if defined( SENSPRO ) || defined( CEVABX )

/*********************************************************************************************
* @function	HW_EXCPTIONS_get_critical_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Get the current critical IRQ status
* @return	Critical IRQ status - 64 bits indication of critical IRQ status, the lower 32 bits are CENSIRQ, the higher 32 bits are CENSIRQ2
*********************************************************************************************/
T_hw_exceptions_critical_irq_status HW_EXCPTIONS_get_critical_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_critical_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Clear the current critical IRQ status.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_critical_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifdef CEVABX
/*********************************************************************************************
 * @function	HW_EXCPTIONS_mask_critical_irq
 * @author	Ravid Rzaev
 * @date 	03/11/2021
 * @brief	Masks / Unmasks the selected critical IRQ status.
 * @param	censirq_var: 	Each critical IRQ corresponding to a set bit will be masked.
 * @param	mask: 			Masks if true, unmasks if false.
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_mask_critical_irq(T_M_CENSIRQ censirq_var, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* CEVA_BX */

/*********************************************************************************************
* @function	HW_EXCPTIONS_get_normal_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Get the current normal IRQ status.
* @return	Normal IRQ status
*********************************************************************************************/
T_NENSIRQ HW_EXCPTIONS_get_normal_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_normal_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Clear the current normal IRQ status.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_normal_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	HW_EXCPTIONS_mask_normal_irq
 * @author	Ravid Rzaev
 * @date 	03/11/2021
 * @brief	Masks / Unmasks the selected normal IRQ status.
 * @param	nensirq_var: 	Each normal IRQ corresponding to a set bit will be masked.
 * @param	mask: 			Masks if true, unmasks if false.
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_mask_normal_irq(T_NENSIRQ_M nensirq_var, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");




#ifdef SENSPRO

	/*********************************************************************************************
	* @function	HW_EXCPTIONS_get_buffers_irq_status
	* @author	Ravid Rzaev
	* @date 	04/11/2021
	* @brief	Get the current normal QMAN and Buffers IRQ status.
	* @return	QMAN and Buffers IRQ status
	*********************************************************************************************/
	T_NQBIRQ HW_EXCPTIONS_get_buffers_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	 * @function	HW_EXCPTIONS_mask_buffers_irq
	 * @author	Ravid Rzaev
	 * @date 	04/11/2021
	 * @brief	Masks / Unmasks the selected normal QMAN and Buffers IRQ status.
	 * @param	nqbirq_var: 	Each Normal QMAN and Buffers Interrupt corresponding to a set bit will be masked.
	 * @param	mask: 			Masks if true, unmasks if false.
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_mask_buffers_irq(T_NQBIRQ_M nqbirq_var, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function	HW_EXCPTIONS_set_shadow_irq
	 * @author	Ravid Rzaev
	 * @date 	08/08/2022
	 * @brief	Sets shadow irq registers.
	 * @param	shadow_irq: 	Pointer to structure of the shadow IRQ registers.
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_set_shadow_irq(T_hw_exceptions_shadow_irq_regs* p_shadow_irq) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* SENSPRO */





/*********************************************************************************************
* @function	HW_EXCPTIONS_get_timers_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Get the current timers IRQ status.
* @param	void
* @return	The Timers IRQ status.
*********************************************************************************************/
uint32_t HW_EXCPTIONS_get_timers_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_timers_irq_status
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Clear the selected timers IRQ status.
* @param	timer_irq_var: Each timer corresponding to a set bit will be cleared.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_timers_irq_status(T_TIMER_IRQ timer_irq_var ) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	HW_EXCPTIONS_mask_timers_irq
 * @author	Ravid Rzaev
 * @date 	03/11/2021
 * @brief	Masks / Unmasks the selected timers IRQ status.
 * @param	timer_irq_var: 	Each timer corresponding to a set bit will be masked.
 * @param	mask: 			Masks if true, unmasks if false.
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_mask_timers_irq(T_TIMER_IRQ_M timer_irq_var, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");


#ifdef SENSPRO
/*********************************************************************************************
* @function	HW_EXCPTIONS_get_watchdog_irq_status
* @author	Ravid Rzaev
* @date 	21/03/2021
* @brief	Get the current watchdog IRQ status.
* @param	void
* @return	The watchdog IRQ status.
*********************************************************************************************/
T_CWDOGIRQ HW_EXCPTIONS_get_watchdog_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
	* @function	HW_EXCPTIONS_clear_watchdog_irq_status
	* @author	Anat Keidar
	* @date 	13/05/2021
	* @brief	Clear the current watchdog IRQ status.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/

E_csl_status HW_EXCPTIONS_clear_watchdog_irq_status(T_CWDOGIRQ wd_irq) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* SENSPRO */

#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

	/*********************************************************************************************
	* @function	HW_EXCPTIONS_get_ddma_irq_status
	* @author	Anat Keidar
	* @date 	13/05/2021
	* @brief	Get the current DDMA IRQ status.
	* @return	Return CSL_TRUE is DDMA interrupt is pending, return CSL_FALSE otherwise
	*********************************************************************************************/
	bool  HW_EXCPTIONS_get_ddma_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_EXCPTIONS_clear_ddma_irq_status
	* @author	Anat Keidar
	* @date 	13/05/2021
	* @brief	Clear the current DDMA IRQ status.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status  HW_EXCPTIONS_clear_ddma_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	* @function	HW_EXCPTIONS_get_pdma_irq_status
	* @author	Anat Keidar
	* @date 	13/05/2021
	* @brief	Get the current PDMA IRQ status.
	* @return	Return CSL_TRUE is PDMA interrupt is pending, return CSL_FALSE otherwise
	*********************************************************************************************/
	bool HW_EXCPTIONS_get_pdma_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	* @function	HW_EXCPTIONS_clear_pdma_irq_status
	* @author	Anat Keidar
	* @date 	13/05/2021
	* @brief	Clear the current PDMA IRQ status.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_clear_pdma_irq_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */

/*********************************************************************************************
* @function	HW_EXCPTIONS_enable_posted_interrupt
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Enables posted interrupts.
* @param	posted_interrupt_num: 	The posted interrupt number.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_enable_posted_interrupt(uint8_t posted_interrupt_num ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************************
* @function	HW_EXCPTIONS_disable_posted_interrupt
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Disable the posted interrupt.
* @param	posted_interrupt_num: 	The posted interrupt number.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_disable_posted_interrupt(uint8_t posted_interrupt_num ) PRAGMA_CSECT("CSL_CODE_SECTION");





/*********************************************************************************************
* @function	HW_EXCPTIONS_get_posted_interrupt_pending
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Return the posted interrupt status.
* @param	posted_interrupt_num: 	The posted interrupt number.
* @return	If the given posted interrupt if pending return CSL_TRUE, in not return false.
*********************************************************************************************/
bool HW_EXCPTIONS_get_posted_interrupt_pending(uint8_t posted_interrupt_num ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_posted_interrupt_pending
* @author	Anat Keidar
* @date 	17/02/2021
* @brief	Clears posted interrupt pending status.
* @param	posted_interrupt_num: 	The posted interrupt number.
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_posted_interrupt_pending(uint8_t posted_interrupt_num ) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* SENSPRO  || CEVABX */

#if defined(XM4) || defined(XM6) || defined(CEVABX)

	/*********************************************************************************************
	* @function	HW_EXCPTIONS_get_violation_status
	* @author	Ravid Rzaev
	* @date 	09/06/2021
	* @brief	Gets the current general violation status
	* @return	General violation status - 64 bits indication of general violation status,
	* 			the lower 32 bits are DBG_GEN, the higher 32 bits are DBG_GEN2
	*********************************************************************************************/
	T_hw_exceptions_violation_status HW_EXCPTIONS_get_violation_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_EXCPTIONS_clear_violation_status
	* @author	Ravid Rzaev
	* @date 	09/06/2021
	* @brief	Clears the current general violation status.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_clear_violation_status(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_EXCPTIONS_mask_violation_status
	* @author	Ravid Rzaev
	* @date 	15/05/2022
	* @brief	Masks / Unmasks the selected violation status
    * @param	regs_val: 	Indicate which bits in the violation status to apply to operation on.
	* @param	mask: 		When CSL_TRUE the bits will be masked, when CSL_FALSE the bits will be unmasked
	* @return	General violation status - 64 bits indication of general violation status,
	* 			the lower 32 bits are DBG_GEN, the higher 32 bits are DBG_GEN2
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_mask_violation_status(T_hw_exceptions_violation_status regs_val, bool mask);

#endif /* if defined(XM4) || defined(XM6) || defined(CEVABX) */






/*********************************************************************************************
* @function	HW_EXCPTIONS_get_data_access_violation_address
* @author	Ravid Rzaev
* @date 	23/05/2021
* @brief	Gets the address of the data access violation and clear the violation.
* @param	void
* @return	The address value.
*********************************************************************************************/
uint32_t HW_EXCPTIONS_get_data_access_violation_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	HW_EXCPTIONS_clear_data_access_violation_address
* @author	Ravid Rzaev
* @date 	21/03/2021
* @brief	Clears the address of the data access violation.
* @param	void
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_clear_data_access_violation_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");




#if defined(XM4) || defined(XM6)

	/*********************************************************************************************
	* @function	HW_EXCPTIONS_get_program_access_violation_address
	* @author	Ravid Rzaev
	* @date 	23/05/2021
	* @brief	Gets the address of the program access violation.
	* @param	void
	* @return	The address value.
	*********************************************************************************************/
	uint32_t HW_EXCPTIONS_get_program_access_violation_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	HW_EXCPTIONS_clear_program_access_violation_address
	* @author	Ravid Rzaev
	* @date 	23/05/2021
	* @brief	Clears the address of the program access violation.
	* @param	void
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status HW_EXCPTIONS_clear_program_access_violation_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* if defined(XM4) || defined(XM6) */





CSL_CPP_END

#endif /* CEVA_XM_HW_EXCEPTIONS */
