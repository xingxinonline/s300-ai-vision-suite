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
#ifndef CEVA_QMAN_CTRL_H_
#define CEVA_QMAN_CTRL_H_
#include "ceva_hw_conf.h"
#ifdef CSL_QMAN_SUPPORTED
/*********************************************************************************************
* @module	QMAN
* @file		ceva_qman_ctrl.h
* @author	Anat Keidar
* @date		28/02/2021
* @brief	Define the configuration registers, values and functions of the Queue-Ctrl programming model
**********************************************************************************************/
#include "ceva_assert.h"


CSL_CPP_START


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Queue-Ctrl Programming Model Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

#ifdef SENSPRO


	/*************************
	 * @struct		T_QMAN_IDM_CROSS
	 * @register	QMAN_IDM_CROSS
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qx_idm_cros	:  8;
			uint32_t 				: 24;
		} fields;
		uint32_t value;
	} T_QMAN_IDM_CROSS;


	/*************************
	 * @struct		T_QMAN_ACTIVE
	 * @register	QMAN_ACTIVE
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qx_active	:  8;
			uint32_t 			: 24;
		} fields;
		uint32_t value;
	} T_QMAN_ACTIVE;



	/*************************
	 * @struct		T_QMAN_VI_MASK
	 * @register	QMAN_VI_MASK
	 *************************/
	typedef union
	{
		struct
		{

			uint32_t 					: 31; // Reserved
			uint32_t fnum_vi_mask 		: 1;
		} fields;
		uint32_t value;
	} T_QMAN_VI_MASK;



	/*************************
	 * @struct		T_QMAN_IRQ_STATUS
	 * @register	QMAN_IRQ_STATUS
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t empty_vi		: 8;
			uint32_t 				:23; // Reserved
			uint32_t fnum_vi		: 1;
		} fields;
		uint32_t value;
	} T_QMAN_IRQ_STATUS;




	/*************************
	 * @struct		T_QMAN_RST
	 * @register	QMAN_RST
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qx_rst		: 8;
			uint32_t 			:24; // Reserved
		} fields;
		uint32_t value;
	} T_QMAN_RST;




	/*************************
	 * @struct		T_QMAN_QFULL
	 * @register	QMAN_QFULL
	 *************************/
	typedef union
	{
	    struct
	    {
	 		uint32_t qx_full		: 8;
			uint32_t 				:24; // Reserved
	    } fields;
	    uint32_t value;
	} T_QMAN_QFULL;


	/*************************
	 * @struct		T_QMAN_QFULL_MASK
	 * @register	QMAN_QFULL_MASK
	 *************************/
	typedef union
	{
	    struct
	    {
	 		uint32_t qx_full_mask		: 8;
			uint32_t 					:24; // Reserved
	    } fields;
	    uint32_t value;
	} T_QMAN_QFULL_MASK;


	/*************************
	 * @struct		T_QMAN_PAUSE
	 * @register	QMAN_PAUSE
	 *************************/
	typedef union
	{
		struct
		{

			uint32_t qman_pause			: 1;
			uint32_t qman_pause_status 	: 1;
			uint32_t 				 	: 30; // Reserved
		} fields;
		uint32_t value;
	} T_QMAN_PAUSE;




	/*************************
	 * @struct	T_QMAN_violations
	 * Registers:
	 *		- QMAN_IDM_CROSS
	 *		- QMAN_IRQ_STATUS
	 *		- QMAN_QFULL
	 *************************/
	typedef union
	{
		struct
		{
			// QMAN_IDM_CROSS
			uint32_t qx_idm_cros	: 8;
			uint32_t 				:24;
			// QMAN_IRQ_STATUS
	 		uint32_t empty_vi		: 8;
			uint32_t 				:23; // Reserved
	        uint32_t fnum_vi		: 1;
			// QMAN_QFULL
	 		uint32_t qx_full		: 8;
			uint32_t 				:24; // Reserved
		} fields;
		struct
		{
			T_QMAN_IDM_CROSS 	qman_idm_cross;
			T_QMAN_IRQ_STATUS 	qman_irq_status;
			T_QMAN_QFULL 		qman_qfull;
		} registers;
	} T_QMAN_violations;



#elif defined(CEVABX)



	/*************************
	 * @struct		T_QMAN_ACTIVE
	 * @register	QMAN_ACTIVE
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qx_idm_cros:  4;
			uint32_t 			: 12;
			uint32_t qx_active	:  4;
			uint32_t 			: 12;
		} fields;
		uint32_t value;
	} T_QMAN_ACTIVE;



	/*************************
	 * @struct		T_QMAN_VI_MASK
	 * @register	QMAN_VI_MASK
	 *************************/
	typedef union
	{
		struct
		{

			uint32_t 					: 16; // Reserved
			uint32_t fnum_vi_mask 		:  1;
			uint32_t 					: 15; // Reserved
		} fields;
		uint32_t value;
	} T_QMAN_VI_MASK;



	/*************************
	 * @struct		T_QMAN_IRQ_STATUS
	 * @register	QMAN_IRQ_STATUS
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t empty_vi		: 4;
			uint32_t 				: 26; // Reserved
			uint32_t bman_irq_status: 1;
			uint32_t fnum_vi		: 1;
		} fields;
		uint32_t value;
	} T_QMAN_IRQ_STATUS;



	/*************************
	 * @struct		T_QMAN_RST
	 * @register	QMAN_RST
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qx_rst		: 4;
			uint32_t 			: 28; // Reserved
		} fields;
		uint32_t value;
	} T_QMAN_RST;




	/*************************
	 * @struct	T_QMAN_violations
	 * Registers:
	 *		- QMAN_IDM_CROSS
	 *		- QMAN_IRQ_STATUS
	 *		- QMAN_QFULL
	 *************************/
	typedef union
	{
		struct
		{
			// T_QMAN_ACTIVE
			uint32_t qx_idm_cros	: 4;
			uint32_t 				:28;
			// QMAN_IRQ_STATUS
	 		uint32_t empty_vi		: 4;
			uint32_t 				:27; // Reserved
	        uint32_t fnum_vi		: 1;
		} fields;
		struct
		{
			T_QMAN_ACTIVE 		qman_active;
			T_QMAN_IRQ_STATUS 	qman_irq_status;
		} registers;
	} T_QMAN_violations;



#endif /* defined(CEVABX) || defined(SENSPRO) */






/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	Queue-Ctrl Programming Model Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/



#ifdef CEVA



	#ifdef CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED
		 /*********************************************************************************
		 * @function	QMAN_start_continuous_execution
		 * @author	Eran Rebenshtok
		 * @date 	09/06/2021
		 * @brief	Start queue continuous execution
		 * @param	qman_id: 			QMAN allocation ID
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		E_csl_status QMAN_start_continuous_execution( T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");




		/*********************************************************************************
		 * @function	QMAN_is_continuous_execution_started
		 * @author	Anat Keidar
		 * @date 	17/03/2022
		 * @brief	Check if the given qman continuous execution is started
		 * @param	qman_id: 			QMAN allocation ID
		 * @return	CSL_TRUE or CSL_FALSE
		**********************************************************************************/
		bool QMAN_is_continuous_execution_started( T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");




		 /*********************************************************************************
		 * @function	QMAN_pause_continuous_execution
		 * @author	Eran Rebenshtok
		 * @date 	09/06/2021
		 * @brief	Pause queue continuous execution
		 * @param	qman_id: 			QMAN allocation ID
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		E_csl_status QMAN_pause_continuous_execution( T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");





		/*********************************************************************************
		 * @function	QMAN_is_continuous_execution_paused
		 * @author	Anat Keidar
		 * @date 	30/12/2021
		 * @brief	Check if the given qman continuous execution is paused
		 * @param	qman_id: 			QMAN allocation ID
		 * @return	CSL_TRUE or CSL_FALSE
		**********************************************************************************/
		bool QMAN_is_continuous_execution_paused( T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



	#endif /* CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED */

	#ifdef SENSPRO

		/*********************************************************************************
		 * @function	QMAN_pause_all
		 * @author	Anat Keidar
		 * @date 	20/12/2020
		 * @brief	Pause all the QMANs.
		 * @param	void
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		E_csl_status QMAN_pause_all(void) PRAGMA_CSECT("CSL_CODE_SECTION");





		/*********************************************************************************
		 * @function	QMAN_resume_all
		 * @author	Anat Keidar
		 * @date 	20/12/2020
		 * @brief	Resume all the QMANs.
		 * @param	void
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		E_csl_status QMAN_resume_all(void) PRAGMA_CSECT("CSL_CODE_SECTION");





		/*********************************************************************************
		 * @function	QMAN_is_all_paused
		 * @author	Anat Keidar
		 * @date 	20/12/2020
		 * @brief	Checks if the all QMANs operation are paused.
		 * @param	void
		 * @return	CEVA_TRUE or CEVA_FALSE
		**********************************************************************************/
		bool QMAN_is_all_paused(void) PRAGMA_CSECT("CSL_CODE_SECTION");



	    /*********************************************************************************
	     * @function	QMAN_is_queue_full
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Return and clear the queue full status for the given QMAN.
	    * @param	qman_id: 			QMAN allocation ID
	    * @return	CSL_TRUE or CSL_FALSE
	    **********************************************************************************/
	    bool QMAN_is_queue_full(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");





	    /*********************************************************************************
	     * @function	QMAN_mask_queue_full_interrupt
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Mask the queue full violation interrupt for the given QMAN.
	    * @param	qman_id: 			QMAN allocation ID
	     * @param	mask: 	The violation is:
	     *						- masked when CEVA_TRUE
	     *						- unmasked when CEVA_FALSE
	     * @return	CSL_SUCCESS or CSL failure code
	    **********************************************************************************/
	    E_csl_status QMAN_mask_queue_full_interrupt(T_csl_allocation_id qman_id, bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");





	    /*********************************************************************************
	     * @function	QMAN_mask_all_queue_full_interrupts
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Mask the queue full violation interrupt for all QMANs.
	     * @param	mask: 	The violation is:
	     *						- masked when CEVA_TRUE
	     *						- unmasked when CEVA_FALSE
	     * @return	CSL_SUCCESS or CSL failure code
	    **********************************************************************************/
	    E_csl_status QMAN_mask_all_queue_full_interrupts(bool mask) PRAGMA_CSECT("CSL_CODE_SECTION");





	#endif /* SENSPRO */



	#if defined(SENSPRO) || defined(CEVABX)

	    /*********************************************************************************
	    * @function	QMAN_is_idm_cross_violation
	    * @author	Anat Keidar
	    * @date 	20/12/2020
	    * @brief	Return and clear the IDM cross violation status for the given QMAN.
	    * @param	qman_id: 			QMAN allocation ID
	    * @return	CSL_TRUE or CSL_FALSE
	    **********************************************************************************/
	    bool QMAN_is_idm_cross_violation(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");





	    /*********************************************************************************
	     * @function	QMAN_is_queue_empty_violation
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Return and clear the empty violation status for the given QMAN.
	    * @param	qman_id: 			QMAN allocation ID
	    * @return	CSL_TRUE or CSL_FALSE
	    **********************************************************************************/
	    bool QMAN_is_queue_empty_violation(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");






	    /*********************************************************************************
	     * @function	QMAN_get_all_violations
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Return the current status of all QMAN violations
	     * @param	qman_violations: 	Pointer to T_QMAN_Violations structure
	     * @return	CSL_SUCCESS or CSL failure code
	    **********************************************************************************/
	    E_csl_status QMAN_get_all_violations(T_QMAN_violations *qman_violations) PRAGMA_CSECT("CSL_CODE_SECTION");





	    /*********************************************************************************
	     * @function	QMAN_clear_all_violationssss
	     * @author	Anat Keidar
	     * @date 	20/12/2020
	     * @brief	Clear the current status of all QMAN violations
	     * @return	CSL_SUCCESS or CSL failure code
	    **********************************************************************************/
	    E_csl_status QMAN_clear_all_violations(void) PRAGMA_CSECT("CSL_CODE_SECTION");


	#endif /* defined(SENSPRO) || defined(CEVABX) */



	/*********************************************************************************
	 * @function	QMAN_is_active
	 * @author	Anat Keidar
	 * @date 	20/12/2020
	 * @brief	Check if the QMAN is currently executing a task.
	 *			NOTICE: Not supported in simulation
	 * @param	qman_id: 			QMAN allocation ID
	 * @return	CEVA_TRUE or CEVA_FALSE
	**********************************************************************************/
	bool QMAN_is_active(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");




#endif /* CEVA */




CSL_CPP_END



#endif /* CSL_QMAN_SUPPORTED */
#endif /* CEVA_QMAN_CTRL_H_ */
