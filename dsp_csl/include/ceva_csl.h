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
#ifndef CEVA_CSL_H_
#define CEVA_CSL_H_
/*********************************************************************************************
 * File:			ceva_csl.h
 * Created on: 		28/02/2021
 * Author: 			Anat Keidar
 * Description: 	Include all CSL definitions
**********************************************************************************************/
/*
 * Included header files
 */
#include "ceva_hw_conf.h"
#include "ceva_csl_defs.h" 
#include "ceva_assert.h"
#include "ceva_profiler.h"
CSL_CPP_START






#ifdef CEVA

	#include "ceva_memory_map.h"
	#include "ceva_dcu.h"
	#include "ceva_dmss.h"
	#include "ceva_pmss.h"
	#include "ceva_hw_exceptions.h"
	#include "ceva_mcci.h"
	#ifndef CEVABX
	   #include "ceva_watchdog.h"
	#endif


	#ifdef CSL_TIMERS_SUPPORTED
		 #include "ceva_timers.h"
	#endif // #ifdef CSL_TIMERS_SUPPORTED

	#ifdef CSL_ICU_SUPPORTED
		#include "ceva_icu.h"
	#endif // CSL_ICU_SUPPORTED

	#ifdef CEVABX
		#include "ceva_dc.h"
	#endif /* CEVABX */
	
	
#endif /* CEVA */

#ifdef CSL_QMAN_SUPPORTED
	#include "ceva_qman.h"
#endif // #ifdef CSL_QMAN_SUPPORTED
#ifdef CSL_BMAN_SUPPORTED
	#include "ceva_bman.h"
#endif // #ifdef CSL_BMAN_SUPPORTED

/*********************************************************************************************
*********************************************************************************************
*********************************************************************************************
*
* CSL Auxiliary Function Deceleration
*
*********************************************************************************************
*********************************************************************************************
*********************************************************************************************/



#ifndef CEVA

	/*************************
	 * @enum	E_DSP_sim_type
	 * @brief   DMA simulator configuration
	 *************************/
	typedef enum
	{
		DMA_SIM_TYPE_SP50 = 1,
		DMA_SIM_TYPE_SP100,
		DMA_SIM_TYPE_SP250,
		DMA_SIM_TYPE_SP500,
		DMA_SIM_TYPE_SP1000,
		DMA_SIM_TYPE_SP_v11,
		DMA_SIM_TYPE_GEN_CEVA,
		DMA_SIM_TYPE_NUMBER
	}E_DSP_sim_type;


	/*********************************************************************************************
	* @function	CSL_start
	* @author	Eran Rebenshtok
	* @date 	08/03/2021
	* @brief	CSL initialization function.
	* @param	dsp_core_version: DSP Core version (Supported for DMA simulator)
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status CSL_start(E_DSP_sim_type dsp_core_version) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	register_dma_isr
	* @author	Ravid Rzaev
	* @date 	13/01/2021
	* @brief	Initialize the DMAֹ_SIMULATOR with a completion interrupt
	* @params	Interrupt function
	* @return	true or false.
	*********************************************************************************************/
	int register_dma_isr(void(*isr_handler)(void));
	
#else /* CEVA */

	/*********************************************************************************************
	* @function	CSL_start
	* @author	Anat Keidar
	* @date 	08/03/2021
	* @brief	CSL initialization function.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status CSL_start( void ) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* !CEVA */



/*********************************************************************************************
* @function	CSL_stop
* @author	Anat Keidar
* @date 	08/03/2021
* @brief	Stop the CSL DMA Simulator. Deallocation all CSL resources (QMANs, Timers, IVAs).
* @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status CSL_stop(void) PRAGMA_CSECT("CSL_CODE_SECTION");




#ifdef CEVA


	/*********************************************************************************************
	* @function	CSL_is_it_iss
	* @author	Ravid Rzaev
	* @date 	28/02/2021
	* @brief	return the indication if the code run in the ISS simulator.
	* @return	TRUE or FALSE.
	*********************************************************************************************/
	bool CSL_is_it_iss(void) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	* @function	CSL_set_power_save_mode
	* @author	Ravid Rzaev
	* @date 	21/02/2021
	* @brief	Sets the core's power saving mode.
	* @param	mode:		 power saving mode.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	E_csl_status CSL_set_power_save_mode(E_psvm_pmod mode);



#if defined (CEVABX) || defined (SENSPRO)
	/*********************************************************************************************
	* @function	CSL_btb_clear
	* @author	Ravid Rzaev
	* @date 	31/03/2022
	* @brief	Clears the Branch Prediction
	* @return	void
	*********************************************************************************************/
	void CSL_btb_clear(void);
#endif /* defined (CEVABX) || defined (SENSPRO) */

#endif /* CEVA */

	CSL_CPP_END

#endif //CEVA_CSL_H_
