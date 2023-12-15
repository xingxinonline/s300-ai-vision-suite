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
#ifndef INCLUDE_CEVA_AUX_H_
#define INCLUDE_CEVA_AUX_H_
/*********************************************************************************************
 * File:			ceva_aux.h
 * Created on: 		25/01/2020
 * Author: 			Anat Keidar
 * Description: 	Contains auxiliary include files and definitions for CSL.
**********************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "ceva_csl_defs.h"

#ifndef CEVA_PROJECT_SYMBOLS
	#include "ceva_symbols.h"
#endif /* CEVA_PROJECT_SYMBOLS */ 

#if ( ( !defined( SENSPRO ) ) &&  defined( CEVA ) )
	#include <vec-c.h>
#endif /* ( ( !defined( SENSPRO ) ) &&  defined( CEVA ) ) */

#define CSL_TRUE 1
#define CSL_FALSE 0

#define CSL_CONFIG_ENABLED 0x1U
#define CSL_CONFIG_DISABLED 0x0U

#ifdef __cplusplus
	#define CSL_CPP_START 	extern "C" {
	#define CSL_CPP_END 	}
#else /* __cplusplus */
	#define CSL_CPP_START
	#define CSL_CPP_END
#endif


#if ( defined( SENSPRO ) || !defined( CEVA ) )
	
	#ifdef __cplusplus
    extern "C" {
    #endif /* __cplusplus */
		uint32_t ceva_ffb( uint32_t number ) PRAGMA_CSECT("CSL_CODE_SECTION");
	#ifdef __cplusplus
    }
    #endif /* __cplusplus */
    
#elif ( defined( XM4 ) || defined( XM6 ) )
	#define ceva_ffb( _number )	ffb( set, lsb, ( unsigned int )_number )   
#elif defined( CEVABX )
	#define ceva_ffb( _number )	_ffb( _set, _lsb, ( unsigned int )_number )
#endif /* defined( SENSPRO ) || !defined( CEVA ) */








#endif /* INCLUDE_CEVA_AUX_H_ */
