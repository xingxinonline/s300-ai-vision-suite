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
#ifndef CEVA_CPM_IO_H_
#define CEVA_CPM_IO_H_
/*********************************************************************************************
 * File:			cpm_io.h
 * Created on: 		16/02/2021
 * Author: 			Anat Keidar
 * Description: 	Defines cpm registers read and write access access functions.
**********************************************************************************************/
#include "ceva_csl_defs.h"
#include "ceva_aux.h"
#include "ceva_assert.h"

#ifdef CEVA


	#if ( defined(XM4) || defined(XM6) )
	
		#include <vec-c.h>

	    #define cpm_out1( _reg_addr, _val )	                out( cpm, _val , ( uint32_t* )_reg_addr     )
	    #define cpm_out2( _reg_addr, _val1, _val2 )	        out( cpm, _val1, ( uint32_t* )_reg_addr     );\
	                                                        out( cpm, _val2, ( uint32_t* )_reg_addr + 1 )
	    #define cpm_out3( _reg_addr, _val1, _val2, _val3 )	out( cpm, _val1, ( uint32_t* )_reg_addr     );\
	                                                        out( cpm, _val2, ( uint32_t* )_reg_addr + 1 );\
	                                                        out( cpm, _val3, ( uint32_t* )_reg_addr + 2 )
	    #define cpm_in( _reg_addr )	                        in ( cpm,        ( uint32_t* )_reg_addr     )

	#elif (defined(CEVABX))

		#include <vec-c.h>

	    #define cpm_out1( _reg_addr, _val )	                _out( _cpm, _val ,               ( uint32_t* )_reg_addr )
	    #define cpm_out2( _reg_addr, _val1, _val2 )	        _out( _cpm, _val1, _val2,        ( uint32_t* )_reg_addr )
	    #define cpm_out3( _reg_addr, _val1, _val2, _val3 )	_out( _cpm, _val1, _val2, _val3, ( uint32_t* )_reg_addr )
	    #define cpm_in( _reg_addr )	                        _in ( _cpm,                      ( uint32_t* )_reg_addr )

		
	#else // ( defined(XM4) || defined(XM6) || defined(CEVABX) )

		CSL_CPP_START
	
			/********************************************************************
			 @function cpm_out1
			 @author  Anat Keidar
			 @date    19/04/2021
			 @param    cpm_address
			 @param    value for register 1
			 @return   void
			 @brief    This function perform write operation to a register
			********************************************************************/
			void cpm_out1( uint32_t address, uint32_t value1) PRAGMA_CSECT("CSL_CODE_SECTION");


			/********************************************************************
			 @function cpm_out2
			 @author  Eran Rebenshtok
			 @date    21/12/2020
			 @param   cpm_address
			 @param   value for register 1
			 @param   value for register 2
			 @return  void
			 @brief   Set the two given values in the two consecutive cpm registers starting from the given address.
			********************************************************************/
			void cpm_out2( uint32_t address, uint32_t value1, uint32_t value2 )  PRAGMA_CSECT("CSL_CODE_SECTION");

			/********************************************************************
			 @function cpm_out3
			 @author  Eran Rebenshtok
			 @date    21/12/2020
			 @param   cpm_address
			 @param   value for register 1
			 @param   value for register 2
			 @param   value for register 3
			 @return  void
			 @brief   Set the three given values in the three consecutive cpm registers starting from the given address.
			********************************************************************/
			void cpm_out3( uint32_t address, uint32_t value1, uint32_t value2, uint32_t value3 )  PRAGMA_CSECT("CSL_CODE_SECTION");


			/********************************************************************
			 @function cpm_in
			 @author  Anat Keidar
			 @date    19/04/2021
			 @param   cpm_address
			 @return  the value in the given register
			 @brief   Return the current value of the register in the given cpm address.
			********************************************************************/
			uint32_t cpm_in( uint32_t address )  PRAGMA_CSECT("CSL_CODE_SECTION");
		CSL_CPP_END
        
        #ifdef BXCORES
        
            CSL_CPP_START
                /*******************************************************************
                 @function get_csr
                 @author  Ephi Frankel
                 @date    10/05/2021
                 @return   the 32-bit value of the csr register
                 @brief    gets the csr register of the core (for SensPro only)
                *******************************************************************/
                uint32_t get_csr( void )  PRAGMA_CSECT("CSL_CODE_SECTION");
		    CSL_CPP_END
        
        #endif /* BXCORES */

    #endif //  ( defined(XM4) || defined(XM6) || defined(CEVABX) )

#else // CEVA

	#define cpm_out1(reg_addr, val1)             				((void)0)
	#define cpm_out2(address, value1, value2 )             		((void)0)
	#define cpm_out3(address, value1, value2, value3 )          ((void)0)
	#define cpm_in(reg_addr) 									(0)

	#ifdef BXCORES
		#define get_csr( ) 	                             		(0)
	#endif /* BXCORES */

#endif // CEVA





#endif /* CEVA_CPM_IO_H_ */
