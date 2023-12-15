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
#ifndef CEVA_SAFETY_H_
#define CEVA_SAFETY_H_
/*********************************************************************************************
 * @module			SAFETY
 * @file			ceva_safety.h
 * @author			Ephi Frankel
 * @date			06/04/2021
 * @brief			Define shared Safety registers/macros/registers
**********************************************************************************************/
#include "ceva_aux.h"
#include "ceva_assert.h"
#include "ceva_memory_map.h"

#ifdef SENSPRO

	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	Safety Programming Model Registers Structures
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/

	/*********************************************************************************************
	  * @struct		T_P_LPCS
	  * @register	P_LPCS
	  **********************************************************************************************/
	typedef union T_P_LPCS
	{
		struct
		{
			uint32_t ts		   :1;  // trigger set
			uint32_t 		   :3;  // Reserved
			uint32_t wsel 	   :2;  // way selected
			uint32_t 		   :26; // Reserved
		} fields;
		uint32_t value;
	} T_P_LPCS;

	/*********************************************************************************************
	  * @struct		T_P_CSERR_S
	  * @register	P_CSERR_S
	  **********************************************************************************************/
	typedef union T_P_CSERR_S
	{
		struct
		{
			uint32_t 		   		   :1;  // Reserved
			uint32_t p_ecc_cor_s	   :1;
			uint32_t p_ctecc_cor_s 	   :1;
			uint32_t p_btbecc_cor_s	   :1;
			uint32_t		   		   :28; // Reserved
		} fields;
		uint32_t value;
	} T_P_CSERR_S;

	/*********************************************************************************************
	  * @struct		T_P_UCSERR_S
	  * @register	P_UCSERR_S
	  **********************************************************************************************/
	typedef union T_P_UCSERR_S
	{
		struct
		{
			uint32_t 		   		   :5;  // Reserved
			uint32_t p_core_perr_s	   :1;
			uint32_t p_mss_perr_s 	   :1;
			uint32_t		   		   :24; // Reserved
		} fields;
		uint32_t value;
	} T_P_UCSERR_S;

	/*********************************************************************************************
	  * @struct		T_D_CSERR_S
	  * @register	D_CSERR_S
	  **********************************************************************************************/
	typedef union T_D_CSERR_S
	{
		struct
		{
			uint32_t 		   		   :1;  // Reserved
			uint32_t d_ecc_cor_s	   :1;
			uint32_t		   		   :30; // Reserved
		} fields;
		uint32_t value;
	} T_D_CSERR_S;

	/*********************************************************************************************
	  * @struct		T_D_UCSERR_S
	  * @register	D_UCSERR_S
	  **********************************************************************************************/
	typedef union T_D_UCSERR_S
	{
		struct
		{
			uint32_t 		   		   :1;  // Reserved
			uint32_t d_ecc_err_s	   :1;
			uint32_t		   		   :7; // Reserved
			uint32_t d_mss_perr_s	   :1;
			uint32_t		   		   :22; // Reserved
		} fields;
		uint32_t value;
	} T_D_UCSERR_S;

	/*********************************************************************************************
	  * @struct		T_C_UCPERR_S
	  * @register	C_UCPERR_S
	  **********************************************************************************************/
	typedef union T_C_UCPERR_S
	{
		struct
		{
			uint32_t 		   		   :1;  // Reserved
			uint32_t p_ecc_err_s	   :1;
			uint32_t		   		   :30; // Reserved
		} fields;
		uint32_t value;
	} T_C_UCPERR_S;

	typedef struct
	{
		T_D_CSERR_S 	d_cserr_s;
		T_D_UCSERR_S 	d_ucserr_s;
		T_P_CSERR_S 	p_cserr_s;
		T_P_UCSERR_S 	p_ucserr_s;
		T_C_UCPERR_S 	c_ucperr_s;

	} T_safety_shadow_regs;

	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	Safety Programming Model Configuration Values
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/
	#define IGNORE_PTRN_CFG 0xFFFFFFFFU

	/*******************************************
	 * @enum		E_p_lpcs_wsel
	 * @register	P_LPCS
	 * @field		WSEL
	 * @brief		prefetch way selected.
	 ********************************************/
	typedef enum
	{
		P_LPCS_WSEL_WAY_0	= 0,
		P_LPCS_WSEL_WAY_1	= 1,
		P_LPCS_WSEL_WAY_2	= 2,
		P_LPCS_WSEL_WAY_3	= 3,
	}E_p_lpcs_wsel;

	/*********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************
	 *
	 *	Safety Programming Model Driver Functions
	 *
	 *********************************************************************************************
	 *********************************************************************************************
	 *********************************************************************************************/

	/*********************************************************************************************
	 * @function	SAFETY_write_pmss_acs_code
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Writes the PMSS access code to the control register
	 * @return	CSL_SUCCESS or CSL_FAILURE (If CSL assertions are disabled returns void)
	*********************************************************************************************/
	E_csl_status SAFETY_write_pmss_acs_code( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function	SAFETY_write_dbg_acs_code
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Writes the DBG access code to the control register
	 * @return	CSL_SUCCESS or CSL_FAILURE (If CSL assertions are disabled returns void)
	*********************************************************************************************/
	E_csl_status SAFETY_write_dbg_acs_code( void ) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	 * @function  SAFETY_arm_err_data_injection
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Arms the injection patterns onto the datga SAFETY registers
	 * @param	pattern:     The 32-bit pattern such that each set bit will cause the matching bit in the test read data to be flipped
	 * @param	ecc_pattern: The 16-bit pattern such that each set bit will cause the matching bit in the ECC bus to be flipped
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_arm_err_data_injection( uint32_t pattern, uint32_t ecc_pattern ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function  SAFETY_arm_prog_cache_tag_err_injection
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Arms the injection ecc pattern onto the program cache TAG SAFETY registers
	 * @param	ecc_pattern: The 16-bit pattern such that each set bit will cause the matching bit in the ECC bus to be flipped
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_arm_prog_cache_tag_err_injection( uint32_t ecc_pattern ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function  SAFETY_arm_prog_err_injection
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Arms the injection patterns onto the program SAFETY registers
	 * @param	pattern:     The 32-bit pattern such that each set bit will cause the matching bit in the test read data to be flipped
	 * @param	ecc_pattern: The 16-bit pattern such that each set bit will cause the matching bit in the ECC bus to be flipped
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_arm_prog_err_injection( uint32_t pattern, uint32_t ecc_pattern ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function  SAFETY_arm_btb_err_injection
	 * @author	Idan Pollak
	 * @date 	09/08/2022
	 * @brief	Arms the injection patterns onto the BTB SAFETY registers
	 * @param	ecc_pattern: The 16-bit pattern such that each set bit will cause the matching bit in the ECC bus to be flipped
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_arm_btb_err_injection( uint32_t ecc_pattern ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_get_correctable_program_err_cnt
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Gets the number of correctble program errors that were fixed
	 * @return	The number of correctble program errors
	*********************************************************************************************/
	uint32_t SAFETY_get_correctable_program_err_cnt( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_clr_program_correctable_indication
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Clears the correctable program error indication and counter
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_clr_program_correctable_indication( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function	SAFETY_clear_program_uncorrectable_error
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Clear the program uncorrectable error
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status SAFETY_clear_program_uncorrectable_error( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_clr_general_data_err_event
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Clears the data correctable/uncorrectable error indication and counter
	 * @param	err_reg_adr: The address of the correctable error in memory register
	 * @return	CSL_SUCCESS or CSL_FAILURE (If CSL assertions are disabled returns void)
	*********************************************************************************************/
	E_csl_status SAFETY_clr_general_data_err_event( uint32_t err_reg_adr ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_clr_data_correctable_indication
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Clears the correctable data error indication and counter
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_clr_data_correctable_indication( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_clr_data_uncorrectable_indication
	 * @author	Eran Rebenshtok
	 * @date 	08/08/2022
	 * @brief	Clears the correctable data error indication and counter
	 * @return	CSL_SUCCESS or CSL_FAILURE
	*********************************************************************************************/
	E_csl_status SAFETY_clr_data_uncorrectable_indication( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function SAFETY_set_prefetch_way_selected
	 * @author	Ravid Rzaev
	 * @date 	09/08/2022
	 * @brief	sets the pre-fetch way selected.
	 * @param	way_selected:	 one of defined E_p_lpcs_wsel values.
	 * @return	CSL_SUCCESS or CSL_FAILURE (If CSL assertions are disabled returns void)
	*********************************************************************************************/
	E_csl_status SAFETY_set_prefetch_way_selected( E_p_lpcs_wsel way_selected ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	 * @function	SAFETY_set_shadow_registers
	 * @author	Idan Pollak
	 * @date 	09/08/2022
	 * @brief	Sets safety shadow registers.
	 * @param	shadow_reg: 	Pointer to structure of the safety shadow registers.
	 * @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status SAFETY_set_shadow_registers(T_safety_shadow_regs *p_shadow_reg) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* SENSPRO */

/*********************************************************************************************
 * @function	SAFETY_write_wd_acs_code
 * @author	Eran Rebenshtok
 * @date 	08/08/2022
 * @brief	Writes the WD access code to the control register
 * @return	CSL_SUCCESS or CSL_FAILURE (If CSL assertions are disabled returns void)
*********************************************************************************************/
E_csl_status SAFETY_write_wd_acs_code( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* CEVA_SAFETY_H_ */
