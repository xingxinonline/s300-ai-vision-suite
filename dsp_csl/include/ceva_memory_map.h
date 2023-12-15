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
#ifndef CEVAXM_MEMORY_MAP_H_
#define CEVAXM_MEMORY_MAP_H_
/*********************************************************************************************
 * File:			ceva_memory_map.h
 * Created on: 		25/01/2021
 * Author: 			Anat Keidar
 * Description: 	Defines the CEVA CPM memory map per Program Model
**********************************************************************************************/
#include "ceva_csl_defs.h"
#include "ceva_assert.h"


#ifdef SENSPRO
	#include "ceva_senspro_memory_map.h"
#elif defined XM6
	#include "ceva_xm6_memory_map.h"
#elif defined XM4
	#include "ceva_xm4_memory_map.h"
#elif defined CEVABX
    #include "ceva_bx_memory_map.h"    
#endif


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	CPM Registers Masks
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/
#define CSL_MASK_ALL_0XFFFFFFFFU 		    0xFFFFFFFFU
#define CSL_MASK_ALL_BUT_BIT0_0XFFFFFFFEU 	0xFFFFFFFEU
#define CSL_MASK_ALL_BUT_BIT1_0XFFFFFFFDU 	0xFFFFFFFDU
#define CSL_MASK_ALL_BUT_BIT31_0X7FFFFFFEU 	0x7FFFFFFEU
#define CSL_MASK_ONLY_BIT0_0X00000001U 	    0x00000001U
#define CSL_MASK_ONLY_BIT1_0X00000002U 	    0x00000002U
#define CSL_MASK_ONLY_BIT31_0x80000000U 	0x80000000U
#define CSL_SET_ALL_0xFFFFFFFFU 		    0xFFFFFFFFU
#define CSL_CLEAR_ALL_0X00000000U		    0x00000000U
#define CSL_SET_ONLY_BIT0_0X00000001U 		0x00000001U

// QMAN
#define CSL_QMAN_INCREMENT_ENABLE_COUNTER	0x00010000U
#define CSL_QMAN_NUM_BIT_MASK						(( 1 << CSL_HW_CONFIG_NUM_QMANS ) - 1)
#define CSL_MASK_QX_EN_DEPTH_CONT_EXE 		0x80200000U

#if (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)

	// DMSS
	#define CSL_DDCL_MASK						0xFFFFFE01U

	// PDMA
	#define CSL_P_CCOCR_MASK					0xFFFF00BCU
	
	// Profiler
	#define CSL_PROF_PAUSE_MASK					0x000001FFU
	#define CSL_PROF_EV_MASK					0x00330F3FU

	// Timers
	#define CSL_TIMER_CFG_MASK 						0x01FA07FFU


#else  // (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)

	// DMSS
	#define CSL_DDCL_MASK

	// PDMA
	#define CSL_P_CCOCR_MASK

	// Profiler
	#define CSL_PROF_PAUSE_MASK
	#define CSL_PROF_EV_MASK

	// Timers
	#define CSL_TIMER_CFG_MASK

#endif // (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)











#endif // CEVAXM_MEMORY_MAP_H_
