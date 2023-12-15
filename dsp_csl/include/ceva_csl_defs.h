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
#ifndef CEVA_CSL_DEFS_H_
#define CEVA_CSL_DEFS_H_
/*********************************************************************************************
 * File:			ceva_csl_defs.h
 * Created on: 		27/06/2021
 * Author: 			Eran Rebesnshtok
 * Description: 	General CSL defines and macros
**********************************************************************************************/
/*
 * Included header files
 */
#include "cevaxm.h"




#if ( defined( VECC_XM4 ) || defined( XM4 ) || defined( VECC_XM6 ) || defined( XM6 ) || defined( VECC_SENSPRO ) || defined( SENSPRO ) )

	#ifndef _BACKWARD_COMPATIBILITY
	   #define _BACKWARD_COMPATIBILITY
	#endif /* !_BACKWARD_COMPATIBILITY */

	#if defined( VECC_XM6 ) || defined( XM6 )
		#define CSL_QMAN_VIRTUAL_DESCRIPTOR
		#define CSL_DDMA_VIRTUAL_DESCRIPTOR
	#endif /* XM6 */

#endif /* #if ( defined( VECC_XM4 ) || defined( XM4 ) || defined( VECC_XM6 ) || defined( XM6 ) || defined( VECC_SENSPRO ) || defined( SENSPRO ) ) */




/*
 * Offline macro definition
 */
#ifndef CEVA

    #ifdef VECC_XM4
        #ifndef XM4
           #define XM4
       #endif /* !XM4 */
    #endif /* VECC_XM4 */

    #ifdef VECC_XM6
        #ifndef XM6
			#define XM6
        #endif /* !XM6 */    
    #endif /* VECC_XM6 */

    #ifdef VECC_SENSPRO
        #ifndef SENSPRO
            #define SENSPRO
        #endif /* !SENSPRO */    
    #endif /* VECC_SENSPRO */

#endif /* !CEVA */ 




#endif /* CEVA_CSL_DEFS_H_ */
