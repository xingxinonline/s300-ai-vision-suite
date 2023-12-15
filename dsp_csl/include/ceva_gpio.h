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
#ifndef CEVA_GPIO_H_
#define CEVA_GPIO_H_
/*********************************************************************************************
 * @module          GPIO
 * @file            ceva_gpio.h
 * @author          Ravid Rzaev
 * @date            24/11/2021
 * @brief           Define the structure, configuration values and function of
                    the General-purpose input/output Configuration Programming model registers
**********************************************************************************************/
//**********************************************************
//********************** Includes **************************
//**********************************************************
#include "ceva_assert.h"
#include "ceva_memory_map.h"

CSL_CPP_START



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	GPIO Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

 /***********************
 * Name: T_MSS_GPIN
 * Register: MSS_GPIN
 ************************/
 typedef union T_MSS_GPIN
{
	struct
	{
		uint32_t gpin	 		: 32; // General-purpose inputs
	} fields;
	uint32_t value;
} T_MSS_GPIN;


 /***********************
 * Name: T_MSS_GPOUT
 * Register: MSS_GPOUT
 ************************/
 typedef union T_MSS_GPOUT
{
	struct
	{
		uint32_t gpout	 		: 32; // General-purpose outputs
	} fields;
	uint32_t value;
} T_MSS_GPOUT;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	GPIO Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
* @function	GPIO_get_gpin_value
* @author	Ravid Rzaev
* @date 	24/11/2021
* @brief	Returns the value of GPIN
* @return	The value of GPIN
*********************************************************************************************/
uint32_t GPIO_get_gpin_value(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	GPIO_get_gpout_value
* @author	Ravid Rzaev
* @date 	24/11/2021
* @brief	Returns the value of GPOUT
* @return	The value of GPOUT
*********************************************************************************************/
uint32_t GPIO_get_gpout_value(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	GPIO_set_gpout_bit
* @author	Ravid Rzaev
* @date 	24/11/2021
* @brief	Sets the given bit number in MSS_GPOUT
* @param	bit_num:	the number of the bit to set
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status GPIO_set_gpout_bit(uint8_t bit_num) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	GPIO_clear_gpout_bit
* @author	Ravid Rzaev
* @date 	24/11/2021
* @brief	Clears the given bit number in MSS_GPOUT
* @param	bit_num:	the number of the bit to clear
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status GPIO_clear_gpout_bit(uint8_t bit_num) PRAGMA_CSECT("CSL_CODE_SECTION");


CSL_CPP_END

#endif /* CEVA_GPIO_H_ */
