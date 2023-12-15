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
#ifndef CEVA_WATCHDOG_H_
#define CEVA_WATCHDOG_H_
/*********************************************************************************************
 * @module          WATCHDOG
 * @file            ceva_watchdog.h
 * @author          Ravid Rzaev
 * @date            18/03/2021
 * @brief		 	Define the structure, configuration values and function of
					the Watchdog Programming model registers
**********************************************************************************************/
#include "ceva_assert.h"

#ifndef CEVABX
CSL_CPP_START


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	System Watchdog Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/***********************
 * Name: T_WDOGACS
 * Register: WDOGACS
 ***********************/
typedef union
{
	struct
	{
		uint32_t wdog_acs 	:16; // Enable access to the System Watchdog
		uint32_t			:16; // Reserved
	} fields;
	uint32_t value;
} T_WDOGACS;


/***********************
 * Name: T_WDOGCFG
 * Register: WDOGCFG
 ***********************/
typedef union
{
	struct
	{
		uint32_t wdog_en	: 1; // Enable System Watchgod
		uint32_t			:31; // Reserved
	} fields;
	uint32_t value;
} T_WDOGCFG;


/***********************
 * Name: T_WDOGMIN
 * Register: WDOGMIN
 ***********************/
typedef union
{
	struct
	{
		uint32_t wdogmin	:32; // The minimum threshold is configured as 16xWDOGMIN (Writable when WDOG is enabled)
	} fields;
	uint32_t value;
} T_WDOGMIN;


/***********************
 * Name: T_WDOGMIN
 * Register: WDOGMIN
 ***********************/
typedef union
{
	struct
	{
		uint32_t wdogmax	:32; // The maximum threshold is configured as 16xWDOGMAX (Writable when WDOG is enabled)
	} fields;
	uint32_t value;
} T_WDOGMAX;

/***********************
 * Name: T_WDOGCNT
 * Register: WDOGCNT
 ***********************/
typedef union
{
	struct
	{
		uint32_t wdogcnt	:32; // Contains the 32 most significant bits of the Watchdog timer. Wd timer count = 16 x WDOGCNT
	} fields;
	uint32_t value;
} T_WDOGCNT;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 * Watchdog Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/***********************************************
 * E_wdogacs_wdog_acs
 * 		Register: WDOGACS
 * 		Field: WDOG_ACS
 *		Description: access code
 ************************************************/
typedef enum
{
	WATCHDOG_WDOGACS_ACCESS_CODE = 0xCE7AU
} E_wdogacs_wdog_acs;


	/***********************************************
	 * E_wdogacs_wdog_en
	 * 		Register: WDOGCFG
	 * 		Field: WDOG_EN
	 *		Description: Enable watchdog. Also reset the watchdog.
	 ************************************************/
	typedef enum
	{
		WATCHDOG_WDOGCFG_WDOG_EN_DISABLE 	= 0,
		WATCHDOG_WDOGCFG_WDOG_EN_ENABLE 	= 1
	} E_wdogacs_wdog_en;
/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 * Watchdog Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/*********************************************************************************************
 * @function	WATCHDOG_set_threshold
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Sets the watchdog with a minimum and maximum thresholds.
 * @param	threshold_min:  	The minimum threshold value
 * @param	threshold_max: 		The maximum threshold value
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status WATCHDOG_set_threshold(uint32_t threshold_min, uint32_t threshold_max) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	WATCHDOG_reset
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Reset the watchdog timer and enable the watchdog.
 * @param	void
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status WATCHDOG_reset(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	WATCHDOG_get_counter_value
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Get the current value of the Wachdog counter (wd timer count = 16 x WDOGCNT).
 * @param	void
 * @return	The current 64 bits value of the watchdog counter.
*********************************************************************************************/
uint32_t  WATCHDOG_get_counter_value(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	WATCHDOG_enable
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Enable watchdog in DMSS.
 * @param	void
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status WATCHDOG_enable(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
 * @function	WATCHDOG_disable
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Disable watchdog in DMSS.
 * @param	void
 * @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status WATCHDOG_disable(void) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO

/*********************************************************************************************
 * @function	WATCHDOG_get_mss_system_clock
 * @author	Ravid Rzaev
 * @date 	18/03/2021
 * @brief	Return the full mss system clock value.
 * 			*** NOTICE: this functionality not implemented for SENSPRO ***
 * @param	void
 * @return	Total clock counter.
*********************************************************************************************/
uint64_t WATCHDOG_get_mss_system_clock(void) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif





CSL_CPP_END

#endif /* NOT CEVABX */


#endif /* CEVA_WATCHDOG_H_ */
