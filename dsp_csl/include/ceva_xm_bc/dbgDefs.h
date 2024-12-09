/*************************************************************************************\
*                                                                                     *
* Copyright (C) CEVA(R) Inc. All rights reserved                                      *
*                                                                                     *
*                                                                                     *
* This product or Software is made available exclusively to licensees that have       *
* received express written authorization from CEVA to download or receive the product *
* or Software and have agreed to the End User License Agreement (EULA).  If you have  *
* not received such express authorization and agreed to the CEVA EULA, you may not    *
* download, install or use this product or Software.                                  *
*                                                                                     *
* The information contained in this document is subject to change without notice and  *
* does not represent a commitment on any part of CEVA(R), Inc. CEVA(R), Inc. and its  *
* subsidiaries make no warranty of any kind with regard to this material, including,  *
* but not limited to implied warranties of merchantability and fitness for a          *
* particular purpose whether arising out of law, custom, conduct or otherwise.        *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA(R), Inc.     *
* assumes no responsibility for any errors or omissions contained herein, and         *
* assumes no liability for special, direct, indirect or consequential damage,         *
* losses, costs, charges, claims, demands, fees or expenses, of any nature or kind,   *
* which are incurred in connection with the furnishing, performance or use of this    *
* material.                                                                           *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may be  *
* reproduced, photocopied, or translated into another language without the prior      *
* written consent of CEVA(R), Inc.                                                    *
*                                                                                     *
\*************************************************************************************/
#ifndef HDR_DBGDEFS_H_
#define HDR_DBGDEFS_H_ 




//**********************************************************
//********************** Includes **************************
//**********************************************************
#include "ceva_csl_defs.h"
#include "ceva_hw_exceptions.h"






//**********************************************************
//*********************** Enums ****************************
//**********************************************************
typedef enum E_DMA_BREAKPOINT_TYPE
{
	DMA_BP_T_DISABLE 		  = 0,
	DMA_BP_T_INTADD_INT_EXT   = 1,
	DMA_BP_T_INTADD_EXT_INT   = 2,
	DMA_BP_T_INTADD_R_INT_INT = 3,
	DMA_BP_T_INTADD_W_INT_INT = 4,
	DMA_BP_T_EXTADD_INT_EXT   = 5,
	DMA_BP_T_EXTADD_EXT_INT   = 6,
	DMA_BP_T_TWO_MATCH 		  = 7
}E_DMA_BREAKPOINT_TYPE;
// Note: For more details, please see DBG_DDS register at the Arch_Spec_Vol_III

//**********************************************************
//************** Functions Decelerations *******************
//**********************************************************
/***********************************************************
 * DBG_configure_DMA_breakpoint
 *
 * Written by: ER 10/6/2020
 * Description: Set the DMA breakpoint and enable it.
 *
 * Input:
 * 		1. The address to which to perform the breakpoint
 * 		2. The DMA breakpoint type
 * 	Output:
 * 		Breakpoint was set:
 * 						0 - Success
 * 						Else - Failed
 ***********************************************************/
#define DBG_configure_DMA_breakpoint( _dma_address_bp, _dma_type_bp ) \
			HW_EXCPTIONS_set_dma_break_point(_dma_address_bp, (E_DBG_DDS_dmadamst)_dma_type_bp);

/***********************************************************
 * DBG_clear_DMA_breakpoint
 *
 * Written by: ER 10/6/2020
 * Description: Clear the DMA breakpoint.
 *
 * Input:
 * 		None.
 * 	Output:
 * 		DMA Breakpoint type
 ***********************************************************/
#define DBG_clear_DMA_breakpoint() \
			HW_EXCPTIONS_clear_dma_break_point();






#endif /* HDR_DBGDEFS_H_ */
