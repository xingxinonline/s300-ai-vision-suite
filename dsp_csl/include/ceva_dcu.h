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
#ifndef CEVA_DCU_H_
#define CEVA_DCU_H_
/*********************************************************************************************
 * File:			ceva_dcu.h
 * Created on: 		17/02/2021
 * Author: 			Anat Keidar
 * Description: 	Define the structure, configuration values and function of
					the DCU Programming model registers
**********************************************************************************************/



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	DCU Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/***********************
* Name: T_OCM_SA_BP_EN
* Register: OCM_SA_BP_EN
************************/
typedef union T_OCM_SA_BP_EN
{
	struct
	{
		uint32_t sa_ext     :2; // Enable BP for external request
		uint32_t		    :1;
		uint32_t dma_da_e   :1; // Enable BP for DMA request
		uint32_t sa_pa	    :2; // Enable program address BP
		uint32_t		    :2;
		uint32_t sa_da_rd   :1; // Enable data address BP for read access
		uint32_t		    :3;
		uint32_t sa_da_wr   :1; // Enable data address BP for write access
		uint32_t co_a_en    :1; // Enable address BP counter
		uint32_t co_d_en    :1; // Enable data BP counter
		uint32_t 		    :2;
		uint32_t sa_dvm     :1; // Enable data value match BP
		uint32_t sa_comb_rd :1; // Enable combined data address and data value match BP read access
		uint32_t sa_comb_wr :1; // Enable combined data address and data value match BP write access
		uint32_t 		    :12;
	} fields;

	uint32_t value;
} T_OCM_SA_BP_EN;










#endif /* CEVA_DCU_H_ */
