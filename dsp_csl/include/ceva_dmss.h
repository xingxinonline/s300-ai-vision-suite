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
#ifndef CEVA_DMSS_H_
#define CEVA_DMSS_H_
/*********************************************************************************************
 * @module          DMSS
 * @file            ceva_dmss.h
 * @author          Ravid Rzaev
 * @date            02/03/2021
 * @brief           Define the structure, configuration values and function of
                    the DMSS Programming model registers
**********************************************************************************************/
/**********************************************************
 ********************** Includes **************************
 **********************************************************/
#include "ceva_assert.h"
#include "ceva_memory_map.h"


CSL_CPP_START



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	DMSS Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

 /***********************
 * Name: T_MSS_BARRIER
 * Register: MSS_BARRIER
 ************************/
 typedef union T_D_BARRIER
{
	struct
	{
		uint32_t 				: 7; // Reserved
		uint32_t int_act 		: 1;
		uint32_t 				: 24; // Reserved
	} fields;
	uint32_t value;
} T_MSS_BARRIER;


 /***********************
 * Name: T_D_DTAP
 * Register: D_DTAP
 ************************/
 typedef union T_D_DTAP
{
	struct
	{
		uint32_t ap				: 3;
		uint32_t  				: 29; // Reserved
	} fields;
	uint32_t value;
} T_D_DTAP;


/*************************
 * Name: T_MSS_DDEA
 * Register: MSS_DDEA
 *************************/
typedef union
{
	struct
	{
		uint32_t ddea 			:32; // External Address
	} fields;
	uint32_t value;
} T_MSS_DDEA;

/*************************
 * Name: T_MSS_DDIA
 * Register: MSS_DDIA
 *************************/
typedef union
{
	struct
	{
		uint32_t ddia 			:32; // Internal Address
	} fields;
	uint32_t value;
} T_MSS_DDIA;


/*************************
 * Name: T_MSS_DDTC
 * Register: MSS_DDTC
 *************************/
typedef union
{
	struct
	{
#ifdef DDCL_DESCRIPTOR
	#ifndef XM4
		uint32_t ddtc 			:22; // Size of the DMA transfer, in bytes
		uint32_t				:10;
	#else
		uint32_t ddtc 			:20; // Size of the DMA transfer, in bytes
		uint32_t				:12;
	#endif
#else /* (XM4 & RTL < 120) || (BX)*/
#ifndef CEVABX
		uint32_t ddtc 			:21; // Size of the DMA transfer, in bytes
#else /* CEVABX */
		uint32_t ddtc 			:20; // Size of the DMA transfer, in bytes
		uint32_t pdl 			:1; // Size of the DMA transfer, in bytes
#endif /* ! CEVABX */
		uint32_t iit			:1; // Internal-to-internal transfer
		uint32_t trid			:3;
		uint32_t bsz			:4; // maximum burst length
		uint32_t ddst			:1; // status
		uint32_t extw			:1;
		uint32_t ddie			:1; // interrupt enable
#endif
	} fields;
	uint32_t value;
} T_MSS_DDTC;

#ifndef CEVABX

/*************************
 * Name: T_MSS_2DCFG1
 * Register: MSS_2DCFG1
 *************************/
typedef union
{
	struct
	{
#ifndef XM4
		uint32_t tdt 		:1;
		uint32_t 	 		:1;
#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		uint32_t clip_en 	:2;
#else
		uint32_t 	 		:2;
#endif
		uint32_t trtyp 		:3;
		uint32_t 	 		:1;
#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		uint32_t unpack 	:4;
		uint32_t element_sz	:2;
		uint32_t ch_num		:2;
#else
		uint32_t 	 		:8;
#endif
		uint32_t 	 		:16;
#else /*XM4*/
	#ifdef DDCL_DESCRIPTOR
		uint32_t tdt 			:1;
		uint32_t 	 			:3;
		uint32_t trtyp 			:3;
		uint32_t 	 			:25;
	#else
		uint32_t tile_width 	:10;
		uint32_t				:6; // Reserved
		uint32_t tile_height 	:10;
		uint32_t				:2; // Reserved
		uint32_t trtyp 			:3;
		uint32_t tdt 			:1;
	#endif
#endif
	} fields;
	uint32_t value;
} T_MSS_2DCFG1;


/*************************
 * Name: T_MSS_2DCFG2
 * Register: MSS_2DCFG2
 *************************/
typedef union
{
	struct
	{
#ifdef DDCL_DESCRIPTOR
		uint32_t tile_width  :16;
		uint32_t tile_height :16;
#else  /* XM4 & RTL < 120 */
		uint32_t int_stride		:10;
		uint32_t				:6; // Reserved
		uint32_t ext_stride 	:16;
#endif
	} fields;
	uint32_t value;
} T_MSS_2DCFG2;



#ifdef DDCL_DESCRIPTOR
/*************************
 * Name: T_MSS_2DCFG3
 * Register: MSS_2DCFG3
 *************************/
typedef union
{
	struct
	{
		uint32_t int_stride :16;
		uint32_t ext_stride :16;
	} fields;
	uint32_t value;
} T_MSS_2DCFG3;



#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
/*************************
 * Name: T_MSS_2DCFG4
 * Register: MSS_2DCFG4
 *************************/
typedef union
{
	struct
	{
		uint32_t padval 	:32;
	} fields;
	uint32_t value;
} T_MSS_2DCFG4;


/*************************
 * Name: T_MSS_2DCFG5
 * Register: MSS_2DCFG5
 *************************/
typedef union
{
	struct
	{
		uint32_t tclip		:16;
		uint32_t bclip		:16;
	} fields;
	uint32_t value;
} T_MSS_2DCFG5;


/*************************
 * Name: T_MSS_2DCFG6
 * Register: T_MSS_2DCFG6
 *************************/
typedef union
{
	struct
	{
		uint32_t lclip		:16;
		uint32_t rclip		:16;
	} fields;
	uint32_t value;
} T_MSS_2DCFG6;

#endif /* CSL_DDMA_VIRTUAL_DESCRIPTOR */


/*************************
 * Name: T_MSS_DDCL
 * Register: MSS_DDCL
 *************************/
typedef union
{
	struct
	{
		uint32_t iit 			:1; // Internal-to-internal transfer
		uint32_t trid 			:3;
		uint32_t bsz			:4; // maximum burst length
		uint32_t ddst       	:1;	// status
		uint32_t extw			:1; //
		uint32_t ddie 			:1; // interrupt enable
		uint32_t 				:5; // Reserved
		uint32_t message 		:1;	// message transfer
		uint32_t 				:7; //Reserved
		uint32_t ddma_task_id	:7;
		uint32_t 				:1; // Reserved
	} fields;
	uint32_t value;
} T_MSS_DDCL;

#endif /* DDCL_DESCRIPTOR */

#endif /* !CEVABX */

/*************************
 * Name: T_MSS_DDQS
 * Register: MSS_DDQS
 *************************/
typedef union
{
	struct
	{
		uint32_t qempty		:1;
		uint32_t qfull		:1;
#ifndef CEVABX
		uint32_t qcount		:2;
		uint32_t 			:2;
#else /* !CEVABX */
		uint32_t 			:2;
		uint32_t qcount		:2;
#endif /* CEVABX */
		uint32_t qauto		:1;
		uint32_t qovfl		:1;
#ifndef CEVABX
		uint32_t sts0		:2;
		uint32_t sts1		:2;
		uint32_t sts2		:2;
		uint32_t 			:2;
		uint32_t lsid		:2;
		uint32_t 			:14;
#else /* !CEVABX */
		uint32_t 			:8;
		uint32_t cfg_busy	:2;
		uint32_t 			:15;
#endif /* CEVABX */
	} fields;
	uint32_t value;
} T_MSS_DDQS;

#ifdef SENSPRO
/*************************
 * Name: T_DDMA_PAUSE
 * Register: DDMA_PAUSE
 *************************/
typedef union
{
	struct
	{
		uint32_t ddma_pause 	   :1; // Pause all DDMA  transfers
		uint32_t ddma_pause_status :1; // status
		uint32_t 				   :30; // Reserved
	} fields;
	uint32_t value;
} T_DDMA_PAUSE;

#endif

/*************************
 * Name: T_MSS_DMBA
 * Register: MSS_DMBA
 *************************/
typedef union
{
	struct
	{
		uint32_t DMBA 	   			:32; // Data memory base address of the IDM.
	} fields;
	uint32_t value;
} T_MSS_DMBA;





/*************************
 * Name: T_MSS_DMBE
 * Register: MSS_DMBE
 *************************/
typedef union
{
	struct
	{
		uint32_t wbe 			:1;
		uint32_t ewbe	 		:1;
		uint32_t edpe 			:1;
		uint32_t dmss_idle 		:1;
		uint32_t adlb 			:1;
		uint32_t axim0wbe 		:1;
		uint32_t axim1wbe 		:1;
		uint32_t axip 			:1;
		uint32_t dma 			:1; //Status
		uint32_t qman 			:1; //Status
		uint32_t axim0e 		:1;
		uint32_t axim1e 		:1;
		uint32_t 				:4;  // Reserved
		uint32_t l1wbb 			:1;
#ifndef CEVABX
		uint32_t 				:15; // Reserved
#else /* !CEVABX */
		uint32_t bf 			:1;
		uint32_t ewbb 			:1;
		uint32_t csoub 			:1;
		uint32_t       			:12;
#endif /* CEVABX */

	} fields;
	uint32_t value;
} T_MSS_DMBE;


#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

/*************************
 * Name: T_MSS_DACC
 * Register: MSS_DACC
 *************************/
typedef union
{
	struct
	{
#if defined(CEVABX)
		uint32_t dpraw	 		:1;
		uint32_t 	 			:3; // Reserved
#else /* !CEVABX */
		uint32_t 	 			:4; // Reserved
#endif /* CEVABX */
		uint32_t dol			:4;// DDMA AXI Download outstanding limit
		uint32_t uol			:3;// DDMA AXI Upload outstanding limit
		uint32_t 				:21;// Reserved
	} fields;
	uint32_t value;
} T_MSS_DACC;

#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */


/***********************
 * Name: T_MSS_SDCFG
 * Register: MSS_SDCFG
 ************************/
 typedef union
{
	struct
	{
#ifdef CEVABX
		uint32_t d_ac_s	 		: 1;
		uint32_t 	 			: 15; // Reserved
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
		uint32_t slv_pri_blk0	: 1;
		uint32_t slv_pri_blk1	: 1;
#else /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t 	 			: 2; // Reserved
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t slv_pri_blk2	: 1;
		uint32_t slv_pri_blk3	: 1;
		uint32_t 				: 5; // Reserved
#else /* !CEVABX */
		uint32_t 				: 22; // Reserved
#ifndef SENSPRO_V1_2
		uint32_t dape	 		: 1;
#else /* SENSPRO_V1_2 */
		uint32_t 		 		: 1; // Reserved
#endif /* !SENSPRO_V1_2 */
		uint32_t 		 		: 2; // Reserved
#endif /* CEVABX */
		uint32_t edap_ds		: 1;
		uint32_t axisx_ds		: 1;
		uint32_t 				: 5; // Reserved
	} fields;
	uint32_t value;
} T_MSS_SDCFG;


#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

/***********************
* Name: T_D_PORT_RID
* Register: D_PORT_RID
************************/
typedef union T_D_PORT_RID
{
	struct
	{
#if defined(SENSPRO)
		uint32_t ls0_id			: 4;
		uint32_t ls1_id			: 4;
		uint32_t 				: 8; // Reserved
		uint32_t ddma_id		: 4;
		uint32_t qman_id		: 4;
		uint32_t 				: 8; // Reserved
#elif defined(CEVABX)
		uint32_t l_id			: 4;
		uint32_t 				: 8; // Reserved
		uint32_t l1dc_id		: 4;
		uint32_t ddma_id		: 4;
		uint32_t qman_id		: 4;
		uint32_t pdma_id		: 4;
		uint32_t p_id			: 4;
#elif defined(XM6) || defined(XM4)
		uint32_t ls0_id			: 4;
		uint32_t ls1_id			: 4;
		uint32_t 				: 8; // Reserved
		uint32_t ddma_id		: 4;
		uint32_t qman_id		: 4;
		uint32_t pdma_id		: 4;
		uint32_t p_id			: 4;
#endif
	} fields;
	uint32_t value;
} T_D_PORT_RID;



/***********************
* Name: T_D_PORT_WID
* Register: D_PORT_WID
************************/
typedef union T_D_PORT_WID
{
	struct
	{
#if defined(SENSPRO)
		uint32_t wb_id			: 4;
		uint32_t wbu_id			: 4;
		uint32_t 				: 8; // Reserved
		uint32_t ddma_n_wid		: 4;
		uint32_t qman_wid		: 4;
		uint32_t 				: 8; // Reserved
#elif defined(CEVABX)
		uint32_t wb_id			: 4;
		uint32_t 				:12; // Reserved
		uint32_t ddma_wns_wid	: 4;
		uint32_t qman_wid		: 4;
		uint32_t 				: 4; // Reserved
		uint32_t ocem_id		: 4;
#elif defined(XM6)
		uint32_t wb_id			: 4;
		uint32_t wbu_id			: 4;
		uint32_t 				: 8; // Reserved
		uint32_t ddma_n_wid		: 4;
		uint32_t qman_wid		: 4;
		uint32_t 				: 4; // Reserved
		uint32_t ocem_id		: 4;
#elif defined(XM4)
		uint32_t wb_id			: 4;
		uint32_t 				:12; // Reserved
		uint32_t ddma_n_wid		: 4;
		uint32_t qman_wid		: 4;
		uint32_t 				: 4; // Reserved
		uint32_t ocem_id		: 4;
#endif
	} fields;
	uint32_t value;
} T_D_PORT_WID;

#ifdef CEVABX
	#define T_PORT_RID T_D_PORT_RID
	#define T_PORT_WID T_D_PORT_WID
#endif
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */

/***********************
* Name: T_D_ADDx_START
* Register: D_ADDx_START
************************/
typedef union T_D_ADDx_START
{
	struct // ADDx_START Configuration Register
	{
		uint32_t region_start	: 20;	// 4KB start block of address region
#ifdef CEVABX
		uint32_t region_mid		: 4;	// Master ID of region
		uint32_t 				: 4; // Reserved
#else /* CEVABX */
		uint32_t region_mid		: 8;	// Master ID of region
#endif /* !CEVABX*/
		uint32_t inactive		: 1;	// Set if this region is inactive
#if defined(XM4) || defined(CEVABX)
		uint32_t				: 1;	// Reserved
#else /* !XM4 && !CEVABX */
		uint32_t dpraw			: 1;	// Data protection RAW/SO indication for this memory region
#endif /* XM4 || CEVABX */
		uint32_t				: 2;	// Reserved
	} fields;
	uint32_t value;
} T_D_ADDx_START;

/***********************
* Name: T_D_ADDx_ATT0
* Register: D_ADDx_ATT0
************************/
typedef union T_D_ADDx_ATT0
{
	struct
		{
#ifdef CEVABX
		uint32_t l1dc			: 1;	// L1DC cacheable
		uint32_t hwpf			: 1;	// L1DC HW PF
		uint32_t 				: 1;	// Reserved
		uint32_t l1w			: 1;	// L1DC write policy
		uint32_t l2a_c_wr		: 4;	// L2 Cache Policy for write accesses
		uint32_t l2a_c_rd		: 4;	// L2 Cache Policy for cacheable read accesses
		uint32_t l2a_swop		: 4;	// L2 Cache Policy for cache software operations read accesses
#else /* !CEVABX */
		uint32_t				: 16;	// Reserved
#endif /* CEVABX */
		uint32_t mom			: 1;	// Memory Ordering Model
		uint32_t ap				: 3;	// Access Protection
		uint32_t				: 4;	// Reserved
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
		uint32_t rqos			: 4;	// Read transaction Quality of Service
		uint32_t wqos			: 4;	// Write transaction Quality of Service
#else /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t				: 8;	// Reserved
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		} fields;
	uint32_t value;
} T_D_ADDx_ATT0;

/***********************
* Name: T_D_ADDx_ATT1
* Register: D_ADDx_ATT1
************************/
typedef union T_D_ADDx_ATT1
{
	struct
	{
#ifdef CEVABX
		uint32_t			: 1;	// Reserved
#else
		uint32_t exact_rd	: 1;	// DDMA external port read transactions pursues an exact read
#endif
		uint32_t l2a_wr	:	 4;	// L2 Cache Policy for write accesses
		uint32_t l2a_rd		: 4;	// L2 cache policy for read accesses
		uint32_t dabsz		: 4;	// Data DMA maximum burst size. When 0, determined in the DDTC of the task
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
		uint32_t dadol		: 4;	// DDMA Download Outstanding Limit
		uint32_t			: 1;	// Reserved
		uint32_t dauol		: 3;	// DDMA Upload Outstanding Limit
#else /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t				: 8;	// Reserved
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t 			: 11;	// Reserved
	} fields;
	uint32_t value;
} T_D_ADDx_ATT1;





/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	DMSS Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/




/*****************************************************
 * E_mss_ddcl_bsz
 * 		Register: MSS_DDCL
 * 		Field: BSZ
 *		Description: data maximum burst size
 *****************************************************/
typedef enum
{
	DDCL_BSZ_INCREMENT_BURST_SINGLE = 0,	// Single (1) transfer INCR
	DDCL_BSZ_FIXED_BURST_SINGLE 	= 1,	// single (1) transfer FIXED
	DDCL_BSZ_FIXED_BURST_4		 	= 2,	// 4 transfers FIXED
	DDCL_BSZ_FIXED_BURST_8		 	= 3,	// 8 transfers FIXED
	DDCL_BSZ_FIXED_BURST_16			= 4,	// 16 transfers FIXED
	DDCL_BSZ_INCREMENT_BURST_32		= 5,	// 32 transfers INCR
	DDCL_BSZ_INCREMENT_BURST_4	 	= 6,	// 4 transfers INCR
	DDCL_BSZ_INCREMENT_BURST_64		= 7,	// 64 transfers INCR
	DDCL_BSZ_INCREMENT_BURST_128   	= 8,	// 128 transfers INCR
	DDCL_BSZ_INCREMENT_BURST_256   	= 9,	// 256 transfers INCR
	DDCL_BSZ_INCREMENT_BURST_8	 	= 10,	// 8 transfers INCR
#ifdef CEVABX
	DDCL_BSZ_INCREMENT_BURST_2	 	= 11,	// 2 transfers INCR. for program transfer only
#endif /* CEVABX */
	DDCL_BSZ_INCREMENT_BURST_16		= 14,	// 16 transfers INCR
#ifndef DDCL_DESCRIPTOR
	BSZ_MESSAGE						= 15	// MESSAGE
#endif
} E_mss_ddcl_bsz;


#ifdef CEVABX
/*****************************************************
 * E_mss_ddtc_pdl
 * 		Register: MSS_DDTC
 * 		Field: PDL
 *		Description: Program memory or data memory transaction.
 *****************************************************/
typedef enum
{
	DDTC_PDL_DATA_TRANSFER 		= 0,	// Data memory DMA transaction
	DDTC_PDL_PROGRAM_TRANSFER 	= 1,	// Program memory DMA transaction
} E_mss_ddtc_pdl;

#endif /* CEVABX */


/*****************************************************
 * E_d_dtap_ap
 *   	Register: D_DTAP
 * 		Field: AP
 *		Description: IDM access protection level
 *****************************************************/
typedef enum
{
	D_DTAP_AP_SV_RW_U_RW = 0x0,
    D_DTAP_AP_SV_RW_U_RO = 0x1,
    D_DTAP_AP_SV_RW_U_NA = 0x2,
    D_DTAP_AP_SV_RO_U_RO = 0x3,
    D_DTAP_AP_SV_RO_U_NA = 0x4,
    D_DTAP_AP_TOTAL 	 = 0x5
} E_d_dtap_ap;


/*****************************************************
 * E_mss_ddcl_extw
 *   	Register: MSS_DDCL
 * 		Field: EXTW
 *		Description: Transfer Direction
 *****************************************************/
typedef enum
{
	DDCL_DDST_DMA_NOT_BUSY = 0,
	DDCL_DDST_DMA_BUSY = 1
} E_mss_ddcl_ddst;


/*****************************************************
 * E_mss_ddcl_extw
 *   	Register: MSS_DDCL
 * 		Field: EXTW
 *		Description: Transfer Direction
 *****************************************************/
typedef enum
{
	DDCL_EXTW_DOWNLOAD = 0,
	DDCL_EXTW_UPLOAD = 1
} E_mss_ddcl_extw;


/*****************************************************
 * E_mss_ddcl_ddie
 *   	Register: MSS_DDCL
 * 		Field: DDIE
 *		Description: Enable interrupt in the end of transfer
 *****************************************************/
typedef enum
{
	DDCL_DDIE_DISABLE_INTERRUPT = 0,
	DDCL_DDIE_ENABLE_INTERRUPT = 1
} E_mss_ddcl_ddie;


/*****************************************************
 * E_ddma_message_size
 *		Description: Message transfer size
 *****************************************************/
typedef enum
{
#ifdef DDCL_DESCRIPTOR
	DDMA_MESSAGE_SIZE= 4
#else /* !DDCL_DESCRIPTOR */
	DDMA_MESSAGE_SIZE= 0
#endif /* DDCL_DESCRIPTOR */
} E_ddma_message_size;


/*****************************************************
 * E_mss_ddcl_iit
 * 		Register: MSS_DDCL
 * 		Field: IIT
 *		Description: Internal / External transfer
 *****************************************************/
typedef enum
{
	DDCL_IIT_DMA_NOT_INTERNAL_TRANSFER	= 0,
	DDCL_IIT_DMA_INTERNAL_TRANSFER	    = 1
} E_mss_ddcl_iit;

#ifndef CEVABX
/*****************************************************
 * E_mss_ddcl_message
 * 		Register: MSS_DDCL
 * 		Field: MESSAGE
 *		Description: Message transfer
 *****************************************************/
typedef enum
{
	DDCL_MESSAGE_DMA_NOT_MESSAGE = 0,
	DDCL_MESSAGE_DMA_MESSAGE	 = 1
} E_mss_ddcl_message;


/*****************************************************
 * E_mss_ddcl_message
 * 		Register: MSS_2DCFG1
 * 		Field: TRTYP
 *		Description: Indicates a bank access to IDM
 *****************************************************/
typedef enum
{
	MSS_2DCFG1_TRTYP_LINEAR_OR_TWO_DIMENSION = 0,
	MSS_2DCFG1_TRTYP_ONE_BANK_READ = 2,
#ifndef SENSPRO
	MSS_2DCFG1_TRTYP_TWO_BANK_READ = 3,
#endif
	MSS_2DCFG1_TRTYP_DUPLICATE_ONE_BANK_WRITE = 4,
#ifndef SENSPRO
	MSS_2DCFG1_TRTYP_DUPLICATE_TWO_BANK_WRITE = 5,
#endif

	MSS_2DCFG1_TRTYP_ONE_BANK_WRITE = 6,
#ifndef SENSPRO
	MSS_2DCFG1_TRTYP_TWO_BANK_WRITE = 7,
#endif

} E_mss_2dcfg1_trtyp;


/*****************************************************
 * E_mss_2dcfg1_tdt
 * 		Register: MSS_2DCFG1
 * 		Field: TDT
 *		Description: Two dimension transfer indication
 *****************************************************/
typedef enum
{
	MSS_2DCFG1_TDT_LINEAR_TRANSFER = 0,
	MSS_2DCFG1_TDT_2D_TRANSFER = 1
} E_mss_2dcfg1_tdt;

#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
/*****************************************************
 * E_mss_2dcfg1_clip_en
 * 		Register: MSS_2DCFG1
 * 		Field: CLIP_EN
 *		Description: Clipping indication
 *****************************************************/
typedef enum
{
	MSS_2DCFG1_CLIP_EN_NO_CLIPPING = 0,
	MSS_2DCFG1_CLIP_EN_WRITTEN_IN_PADVAL = 1,
	MSS_2DCFG1_CLIP_EN_MASKED = 2
} E_mss_2dcfg1_clip_en;

/*****************************************************
 * E_mss_2dcfg1_unpack
 * 		Register: MSS_2DCFG1
 * 		Field: UNPACK
 *		Description: Indicates the channel in the
 *						2D tile to be written
 *****************************************************/
typedef enum
{
	MSS_2DCFG1_UNPACK_WRITE_ALL = 0xF,
	MSS_2DCFG1_UNPACK_WRITE_ELEMENT_1 = 1,
	MSS_2DCFG1_UNPACK_WRITE_ELEMENT_2 = 2,
	MSS_2DCFG1_UNPACK_WRITE_ELEMENT_3 = 4,
	MSS_2DCFG1_UNPACK_WRITE_ELEMENT_4 = 8
} E_mss_2dcfg1_unpack;


/*****************************************************
 * E_mss_2dcfg1_ch_num
 * 		Register: MSS_2DCFG1
 * 		Field: CH_NUM
 *		Description: Indicates the number of channels in a tile.
 ******************************************************/
typedef enum
{
	MSS_2DCFG1_CH_NUM_1_CHANEL = 0,
	MSS_2DCFG1_CH_NUM_2_CHANELS = 1,
	MSS_2DCFG1_CH_NUM_3_CHANELS = 2,
	MSS_2DCFG1_CH_NUM_4_CHANELS = 3
} E_mss_2dcfg1_ch_num;



/*****************************************************
 * E_mss_2dcfg1_ch_num
 * 		Register: MSS_2DCFG1
 * 		Field: ELEMENT_SZ
 *		Description: Indicates the size of each element, in bytes.
 ******************************************************/
typedef enum
{
	MSS_2DCFG1_ELEMENT_SZ_1_BYTE = 0,
	MSS_2DCFG1_ELEMENT_SZ_2_BYTE = 1,
	MSS_2DCFG1_ELEMENT_SZ_4_BYTE = 3
} E_mss_2dcfg1_element_sz;
#endif /*CSL_DDMA_VIRTUAL_DESCRIPTOR*/

#endif /*CEVABX*/

#if !(defined(SENSPRO_V1_2) || defined(CEVABX))
/*****************************************************
 * E_mss_sdcfg_dape
 * 		Register: MSS_SDCFG
 * 		Field: dape
 *		Description: Data access protection
 *****************************************************/
typedef enum
{
	SDCFG_DAPE_AP_ENABLE 		= 1,
	SDCFG_DAPE_AP_DISABLE 		= 0
}E_mss_sdcfg_dape;
#endif /* !(defined(SENSPRO_V1_2) || defined(CEVABX)) */

#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
/*****************************************************
 * E_mss_dacc_dol
 * 		Register: MSS_DACC
 * 		Field: dol
 *		Description: DDMA AXI Download Outstanding Limit
 *****************************************************/
typedef enum
{
	DACC_DOL_4_READ_BURSTS 					= 0,
	DACC_DOL_5_READ_BURSTS 					= 1,
	DACC_DOL_6_READ_BURSTS 					= 2,
	DACC_DOL_7_READ_BURSTS 					= 3,
	DACC_DOL_8_READ_BURSTS 					= 4,
	DACC_DOL_9_READ_BURSTS 					= 5,
	DACC_DOL_10_READ_BURSTS					= 6,
	DACC_DOL_11_READ_BURSTS 				= 7,
	DACC_DOL_12_READ_BURSTS 				= 8,
	DACC_DOL_13_READ_BURSTS 				= 9,
	DACC_DOL_14_READ_BURSTS 				= 10,
	DACC_DOL_15_READ_BURSTS 				= 11,
	DACC_DOL_16_READ_BURSTS 				= 12
} E_mss_dacc_dol;


/*****************************************************
 * E_mss_dacc_uol
 * 		Register: MSS_DACC
 * 		Field: uol
 *		Description: DDMA Upload Outstanding Limit when using EDP
 *****************************************************/
typedef enum
{
	DACC_UOL_4_WRITE_BURSTS 					= 0,
	DACC_UOL_8_WRITE_BURSTS 					= 1,
	DACC_UOL_16_WRITE_BURSTS 					= 2,
	DACC_UOL_32_WRITE_BURSTS 					= 3
} E_mss_dacc_uol;

#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */

/*****************************************************
 * E_addstart_region_mid
 * 		Register: D_ADDx_START
 * 		Field: region_mid
 *		Description: Region master id
 *****************************************************/
typedef enum
{
	ADDSTART_REGION_MID_EDP = 0x1,
	ADDSTART_REGION_MID_AXIm0 = 0x2,
	ADDSTART_REGION_MID_AXIm1 = 0x4,
#ifndef CEVABX
	ADDSTART_REGION_MID_BLANK = 0x80
#else /*CEVABX*/
	ADDSTART_REGION_MID_BLANK = 0x8
#endif /* !CEVABX */
} E_addstart_region_mid;

/*****************************************************
 * E_addstart_inactive
 * 		Register: D_ADDx_START
 * 		Field: inactive
 *		Description: DACU Region activation
 *****************************************************/
typedef enum
{
	ADDSTART_INACTIVE_ACTIVATE = 0,
	ADDSTART_INACTIVE_NOT_ACTIVATE = 1
} E_addstart_inactive;



/*****************************************************
 * E_addstart_dpraw
 * 		Register: D_ADDx_START
 * 		Field: dpraw
 *		Description: DACU Region Data Protection Read AfterWrite
 *****************************************************/
typedef enum
{
	ADDSTART_DPRAW_DISABLED = 0,
	ADDSTART_DPRAW_ENABLED = 1
} E_addstart_dpraw;


/*****************************************************
 * E_addatt0_mom
 * 		Register: D_ADDx_ATT0
 * 		Field: mom
 *		Description: Memory ordering model
 *****************************************************/
typedef enum
{
	ADDATT0_MOM_TOTAL_STORE_ORDERING	= 0,
	ADDATT0_MOM_STRONG_ORDERING 		= 1
} E_addatt0_mom;

/*****************************************************
 * E_addatt0_ap
 * 		Register: D_ADDx_ATT0
 * 		Field: AP
 *		Description: Region Access Protection
 *****************************************************/
typedef enum
{
	ADDATT0_AP_ALL_READ_WRITE 					= 0,
	ADDATT0_AP_SUPER_ALL_USER_READ_ONLY 		= 1,
	ADDATT0_AP_SUPER_ALL_USER_NO_ACCESS 		= 2,
	ADDATT0_AP_ALL_READ_ONLY 					= 3,
	ADDATT0_AP_SUEPER_READ_ONLY_USER_NO_ACCESS  = 4,
	ADDATT0_AP_ALL_NO_ACCESS 					= 7
} E_addatt0_ap;


#ifdef CEVABX

/*****************************************************
 * E_addatt0_l1dc
 * 		Register: D_ADDx_ATT0
 * 		Field: L1DC
 *		Description: L1DC Cacheable
 *****************************************************/
typedef enum
{
	ADDATT0_L1DC_CACHE_DISABLE 			= 0,
	ADDATT0_L1DC_CACHE_ENABLE 			= 1
} E_addatt0_l1dc;


/*****************************************************
 * E_addatt0_l1dc
 * 		Register: D_ADDx_ATT0
 * 		Field: HWPF
 *		Description: L1DC HWPF
 *****************************************************/
typedef enum
{
	ADDATT0_L1DC_HWPF_DISABLE 			= 0,
	ADDATT0_L1DC_HWPF_ENABLE 			= 1
} E_addatt0_hwpf;

/*****************************************************
 * E_addatt0_l1w
 * 		Register: D_ADDx_ATT0
 * 		Field: L1W
 *		Description: L1DC Write Policy
 *****************************************************/
typedef enum
{
	ADDATT0_L1W_WRITE_THROUGH			= 0,
	ADDATT0_L1W_COPY_BACK			= 1
} E_addatt0_l1w;

/*****************************************************
 * E_addatt0_l2a_c_wr
 * 		Register: ADDATT0
 * 		Field: L2A_C_WR
 *		Description:AXI Bus: L2 Cache Policy for write accesses
 *****************************************************/
typedef enum
{
	ADDATT0_L2A_NON_BUFFERABLE 						= 0x0,
	ADDATT0_L2A_BUFFERABLE 							= 0x1,
	ADDATT0_L2A_NON_CACHEABLE_NON_BUFFERABLE		= 0x2,
	ADDATT0_L2A_NON_CACHEABLE_BUFFERABLE			= 0x3,
	ADDATT0_L2A_WRITE_THROUGH_NO_ALLOCATE			= 0x6,
	ADDATT0_L2A_WRITE_THROUGH_READ_ALLOCATE			= 0x6,
	ADDATT0_L2A_WRITE_BACK_NO_ALLOCATE				= 0x7,
	ADDATT0_L2A_WRITE_BACK_READ_ALLOCATE 			= 0x7,
	ADDATT0_L2A_WRITE_THROUGH_WRITE_ALLOCATE		= 0xe,
	ADDATT0_L2A_WRITE_THROUGH_READ_WRITE_ALLOCATE	= 0xe,
	ADDATT0_L2A_WRITE_BACK_WRITE_ALLOCATE 			= 0xf,
	ADDATT0_L2A_WRITE_BACK_READ_WRITE_ALLOCATE 		= 0xf
} E_addatt0_l2a_c_wr;


/*****************************************************
 * E_addatt0_l2a_c_rd
 * 		Register: ADDATT0
 * 		Field: L2A_C_RD
 *		Description:AXI Bus: L2 Cache Policy for read accesses
 *****************************************************/
typedef enum
{
	ADDATT0_L2A_C_NON_BUFFERABLE 						= 0x0,
	ADDATT0_L2A_C_BUFFERABLE 							= 0x1,
	ADDATT0_L2A_C_NON_CACHEABLE_NON_BUFFERABLE	 		= 0x2,
	ADDATT0_L2A_C_NON_CACHEABLE_BUFFERABLE 				= 0x3,
	ADDATT0_L2A_C_WRITE_THROUGH_NO_ALLOCATE				= 0xa,
	ADDATT0_L2A_C_WRITE_THROUGH_WRITE_ALLOCATE			= 0xa,
	ADDATT0_L2A_C_WRITE_BACK_NO_ALLOCATE				= 0xb,
	ADDATT0_L2A_C_WRITE_BACK_WRITE_ALLOCATE 			= 0xb,
	ADDATT0_L2A_C_WRITE_THROUGH_READ_ALLOCATE			= 0xe,
	ADDATT0_L2A_C_WRITE_THROUGH_READ_WRITE_ALLOCATE		= 0xe,
	ADDATT0_L2A_C_WRITE_BACK_READ_ALLOCATE 				= 0xf,
	ADDATT0_L2A_C_WRITE_BACK_READ_WRITE_ALLOCATE 		= 0xf
} E_addatt0_l2a_c_rd;



/*****************************************************
 * E_addatt0_l2a_swop
 * 		Register: ADDATT0
 * 		Field: L2A_C_RD
 *		Description:AXI Bus: L2 cache software operations read accesses
 *****************************************************/
typedef enum
{
	ADDATT0_L2A_SWOP_NON_BUFFERABLE 						= 0x0,
	ADDATT0_L2A_SWOP_BUFFERABLE 							= 0x1,
	ADDATT0_L2A_SWOP_NON_CACHEABLE_NON_BUFFERABLE 			= 0x2,
	ADDATT0_L2A_SWOP_NON_CACHEABLE_BUFFERABLE 				= 0x3,
	ADDATT0_L2A_SWOP_WRITE_THROUGH_NO_ALLOCATE				= 0xa,
	ADDATT0_L2A_SWOP_WRITE_THROUGH_WRITE_ALLOCATE			= 0xa,
	ADDATT0_L2A_SWOP_WRITE_BACK_NO_ALLOCATE					= 0xb,
	ADDATT0_L2A_SWOP_WRITE_BACK_WRITE_ALLOCATE 				= 0xb,
	ADDATT0_L2A_SWOP_WRITE_THROUGH_READ_ALLOCATE			= 0xe,
	ADDATT0_L2A_SWOP_WRITE_THROUGH_READ_WRITE_ALLOCATE		= 0xe,
	ADDATT0_L2A_SWOP_WRITE_BACK_READ_ALLOCATE 				= 0xf,
	ADDATT0_L2A_SWOP_WRITE_BACK_READ_WRITE_ALLOCATE 		= 0xf
} E_addatt0_l2a_swop;

#endif /* CEVABX */

/*****************************************************
 * E_addatt1_l2a_wr
 * 		Register: D_ADDx_ATT1
 * 		Fields: L2A_WR
 *		Description: L2 Cache policy for non-cacheable write access
 *****************************************************/
typedef enum
{
	ADDATT1_L2A_WR_DEVICE_NON_BUFFERABLE					 	= 0x0,
	ADDATT1_L2A_WR_DEVICE_BUFFERABLE						 	= 0x1,
	ADDATT1_L2A_WR_NORMAL_NON_CACHEABLE_NON_BUFFERABLE		 	= 0x2,
	ADDATT1_L2A_WR_NORMAL_NON_CACHEABLE_BUFFERABLE		 		= 0x3,
	ADDATT1_L2A_WR_WRITE_THROUGH_NO_ALLOCATE				 	= 0x6,
	ADDATT1_L2A_WR_WRITE_THROUGH_READ_ALLOCATE		 			= 0x6,
	ADDATT1_L2A_WR_WRITE_THROUGH_WRITE_ALLOCATE		 			= 0xe,
	ADDATT1_L2A_WR_WRITE_THROUGH_READ_AND_WRITE_ALLOCATE		= 0xe,
	ADDATT1_L2A_WR_WRITE_BACK_NO_ALLOCATE						= 0x7,
	ADDATT1_L2A_WR_WRITE_READ_ALLOCATE							= 0x7,
	ADDATT1_L2A_WR_WRITE_BACK_WRITE_ALLOCATE					= 0xf,
	ADDATT1_L2A_WR_WRITE_BACK_READ_AND_WRITE_ALLOCATE			= 0xf
} E_addatt1_l2a_wr;




/*****************************************************
 * E_addatt1_l2a_rd
 * 		Register: D_ADDx_ATT1
 * 		Fields: L2A_RD
 *		Description: L2 Cache policy for non-cacheable read access
 *****************************************************/
typedef enum
{
	ADDATT1_L2A_RD_DEVICE_NON_BUFFERABLE					 	= 0x0,
	ADDATT1_L2A_RD_DEVICE_BUFFERABLE						 	= 0x1,
	ADDATT1_L2A_RD_NORMAL_NON_CACHEABLE_NON_BUFFERABLE		 	= 0x2,
	ADDATT1_L2A_RD_NORMAL_NON_CACHEABLE_BUFFERABLE		 		= 0x3,
	ADDATT1_L2A_RD_WRITE_THROUGH_NO_ALLOCATE				 	= 0xa,
	ADDATT1_L2A_RD_WRITE_THROUGH_READ_ALLOCATE		 			= 0xe,
	ADDATT1_L2A_RD_WRITE_THROUGH_WRITE_ALLOCATE		 			= 0xa,
	ADDATT1_L2A_RD_WRITE_THROUGH_READ_AND_WRITE_ALLOCATE		= 0xe,
	ADDATT1_L2A_RD_WRITE_BACK_NO_ALLOCATE						= 0xb,
	ADDATT1_L2A_RD_WRITE_READ_ALLOCATE							= 0xf,
	ADDATT1_L2A_RD_WRITE_BACK_WRITE_ALLOCATE					= 0xb,
	ADDATT1_L2A_RD_WRITE_BACK_READ_AND_WRITE_ALLOCATE			= 0xf
} E_addatt1_l2a_rd;



#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

/*****************************************************
 * E_addatt1_dabsz
 * 		Register: D_ADDx_ATT1
 * 		Field: dabsz
 *		Description: data maximum burst size
 *****************************************************/
typedef enum
{
	ADDATT1_DABSZ_CONFIGURED_AT_DDMA_TASK 	= 0x0,
	ADDATT1_DABSZ_FIXED_1 					= 0x1,
	ADDATT1_DABSZ_FIXED_4 					= 0x2,
	ADDATT1_DABSZ_FIXED_8 					= 0x3,
	ADDATT1_DABSZ_FIXED_16 					= 0x4,
	ADDATT1_DABSZ_INCREMENTED_1 			= 0x8,
	ADDATT1_DABSZ_INCREMENTED_4 			= 0x9,
	ADDATT1_DABSZ_INCREMENTED_8 			= 0xa,
	ADDATT1_DABSZ_INCREMENTED_16 			= 0xb,
	ADDATT1_DABSZ_INCREMENTED_32 			= 0xc,
	ADDATT1_DABSZ_INCREMENTED_64 			= 0xd,
	ADDATT1_DABSZ_INCREMENTED_128 			= 0xe,
	ADDATT1_DABSZ_INCREMENTED_256 			= 0xf
} E_addatt1_dabsz;

#else /* HW_CONFIG_BUS_PROTOCOL_AHB */

/*****************************************************
 * E_addatt1_dabsz
 * 		Register: D_ADDx_ATT1
 * 		Field: dabsz
 *		Description: data maximum burst size
 *****************************************************/
typedef enum
{
	ADDATT1_DABSZ_CONFIGURED_AT_DDMA_TASK 	= 0x0,
	ADDATT1_DABSZ_INCREMENTED_4 			= 0x6,
	ADDATT1_DABSZ_INCREMENTED_8 			= 0xa,
	ADDATT1_DABSZ_INCREMENTED_16 			= 0xe
} E_addatt1_dabsz;

#endif /* !HW_CONFIG_BUS_PROTOCOL_AHB */

#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB

/*****************************************************
 * E_addatt1_dadol
 * 		Register: D_ADDx_ATT1
 * 		Field: dadol
 *		Description: Download Outstanding Limit
 *****************************************************/
typedef enum
{
	ADDATT1_DADOL_TAKEN_FROM_DOL 	= 0x0,
	ADDATT1_DADOL_2 				= 0x1,
	ADDATT1_DADOL_3 				= 0x2,
	ADDATT1_DADOL_4 				= 0x3,
	ADDATT1_DADOL_5 				= 0x4,
	ADDATT1_DADOL_6 				= 0x5,
	ADDATT1_DADOL_7 				= 0x6,
	ADDATT1_DADOL_8 				= 0x7,
	ADDATT1_DADOL_9 				= 0x8,
	ADDATT1_DADOL_10				= 0x9,
	ADDATT1_DADOL_11 				= 0xa,
	ADDATT1_DADOL_12 				= 0xb,
	ADDATT1_DADOL_13 				= 0xc,
	ADDATT1_DADOL_14 				= 0xd,
	ADDATT1_DADOL_15 				= 0xe,
	ADDATT1_DADOL_16 				= 0xf
} E_addatt1_dadol;

/*****************************************************
 * E_addatt1_dauol
 * 		Register: D_ADDx_ATT1
 * 		Field: dauol
 *		Description: Upload Outstanding Limit
 *****************************************************/
typedef enum
{
	ADDATT1_DAUOL_TAKEN_FROM_UOL 	= 0x0,
	ADDATT1_DAUOL_4 				= 0x2,
	ADDATT1_DAUOL_8 				= 0x3,
	ADDATT1_DAUOL_16 				= 0x4,
	ADDATT1_DAUOL_32 				= 0x5
} E_addatt1_dauol;


#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */

/****************************************************
 * T_ddma_Task
 * 		contains attributes configuration registers for DMA transfers
 ****************************************************/
typedef union
{
	struct{
		// MSS_DDEA
		uint32_t ddea			:32;
		// MSS_DDIA
		uint32_t ddia			:32;
#if !defined(XM4) && !defined(CEVABX)
		// MSS_DDTC
		uint32_t ddtc 			:22; // Size of the DMA transfer, in bytes
		uint32_t				:10;

		// MSS_2DCFG1
		uint32_t tdt 			:1;
		uint32_t 	 			:1;
#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		uint32_t clip_en 		:2;
#else /* !CSL_DDMA_VIRTUAL_DESCRIPTOR */
		uint32_t 	 			:2;
#endif /* CSL_DDMA_VIRTUAL_DESCRIPTOR */
		uint32_t trtyp 			:3;
		uint32_t 	 			:1;
#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		uint32_t unpack 		:4;
		uint32_t element_sz		:2;
		uint32_t ch_num			:2;
#else /* !CSL_DDMA_VIRTUAL_DESCRIPTOR */
		uint32_t 	 			:8;
#endif /* CSL_DDMA_VIRTUAL_DESCRIPTOR */
		uint32_t 	 			:16;
		// MSS_2DCFG2
		uint32_t tile_width 	:16;
		uint32_t tile_height 	:16;
		// MSS_2DCFG3
		uint32_t int_stride		:16;
		uint32_t ext_stride 	:16;
#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		// MSS_2DCFG4
		uint32_t padval			:32;
		// MSS_2DCFG5
		uint32_t tclip			:16;
		uint32_t bclip			:16;
		// MSS_2DCFG6
		uint32_t lclip			:16;
		uint32_t rclip			:16;
#endif /* CSL_DDMA_VIRTUAL_DESCRIPTOR */
		//T_MSS_DDCL
		uint32_t iit 			:1; // Internal-to-internal transfer
		uint32_t trid 			:3;
		uint32_t bsz			:4; // maximum burst length
		uint32_t ddst       	:1;	// status
		uint32_t extw			:1; // Reserved
		uint32_t ddie 			:1; // interrupt enable
		uint32_t 				:5; // Reserved
		uint32_t message 		:1;	// message transfer
		uint32_t 				:7; // Reserved
		uint32_t ddma_task_id	:7;
		uint32_t 				:1; // Reserved
#else /* XM4 || CEVABX */
	#ifdef DDCL_DESCRIPTOR
		uint32_t ddtc 			:20; // Size of the DMA transfer, in bytes
		uint32_t				:12;
		// MSS_2DCFG1
		uint32_t tdt 			:1;
		uint32_t 	 			:3;
		uint32_t trtyp 			:3;
		uint32_t 	 			:25;
		// MSS_2DCFG2
		uint32_t tile_width 	:16;
		uint32_t tile_height 	:16;
		// MSS_2DCFG3
		uint32_t int_stride		:16;
		uint32_t ext_stride 	:16;
		//T_MSS_DDCL
		uint32_t iit 			:1; // Internal-to-internal transfer
		uint32_t trid 			:3;
		uint32_t bsz			:4; // maximum burst length
		uint32_t ddst       	:1;	// status
		uint32_t extw			:1; // Reserved
		uint32_t ddie 			:1; // interrupt enable
		uint32_t 				:5; // Reserved
		uint32_t message 		:1;	// message transfer
		uint32_t 				:15; // Reserved
	#else /* (XM4 & RTL < 120) || (CEVABX)*/
	#ifdef CEVABX
		uint32_t ddtc 			:20; // Size of the DMA transfer, in bytes
		uint32_t pdl			:1; // Program memory or data memory transaction
	#else
		uint32_t ddtc 			:21; // Size of the DMA transfer, in bytes
	#endif
		uint32_t iit			:1; // Internal-to-internal transfer
		uint32_t trid			:3;
		uint32_t bsz			:4; // maximum burst length
		uint32_t ddst			:1; // status
		uint32_t extw			:1;
		uint32_t ddie			:1; // interrupt enable
	#ifndef CEVABX
		// MSS_2DCFG1
		uint32_t tile_width 	:10;
		uint32_t				:6; // Reserved
		uint32_t tile_height 	:10;
		uint32_t				:2; // Reserved
		uint32_t trtyp 			:3;
		uint32_t tdt 			:1;
		// MSS_2DCFG2
		uint32_t int_stride		:10;
		uint32_t				:6; // Reserved
		uint32_t ext_stride 	:16;
	#endif /* !CEVABX */

	#endif/* DDCL_DESCRIPTOR */
#endif /*!defined(XM4) && !defined(CEVABX)*/
	}fields;
	struct{
		T_MSS_DDEA ddea;  	// external address pointer
		T_MSS_DDIA ddia;  	// internal address pointer
		T_MSS_DDTC ddtc;	// number of bytes transfered
#ifndef CEVABX
		T_MSS_2DCFG1 mss_2dcfg1;
		T_MSS_2DCFG2 mss_2dcfg2;
#ifdef DDCL_DESCRIPTOR
		T_MSS_2DCFG3 mss_2dcfg3;
	#ifdef CSL_DDMA_VIRTUAL_DESCRIPTOR
		T_MSS_2DCFG4 mss_2dcfg4;
		T_MSS_2DCFG5 mss_2dcfg5;
		T_MSS_2DCFG6 mss_2dcfg6;
	#endif /* CSL_DDMA_VIRTUAL_DESCRIPTOR */
		T_MSS_DDCL ddcl;
#endif /*DDCL_DESCRIPTOR*/
#endif
	}registers;
} T_ddma_task;

/****************************************************
 * T_dmss_region_attributes: Data region attributes:
 * 		contains attributes configuration registers
 ****************************************************/
typedef union
{
	struct{
		//T_D_ADDx_START
		uint32_t region_start	: 20;	// 4KB start block of address region
#ifdef CEVABX
		uint32_t region_mid		: 4;	// Master ID of region
		uint32_t 				: 4; // Reserved
#else /* CEVABX */
		uint32_t region_mid		: 8;	// Master ID of region
#endif /* !CEVABX*/
		uint32_t inactive		: 1;	// Set if this region is inactive
#if defined(XM4) || defined(CEVABX)
		uint32_t				: 1;	// Reserved
#else /* !XM4 && !CEVABX */
		uint32_t dpraw			: 1;	// Data protection RAW/SO indication for this memory region
#endif /* XM4 || CEVABX */
		uint32_t				: 2;	// Reserved
		//T_D_ADDx_ATT0
#ifdef CEVABX
		uint32_t l1dc			: 1;	// L1DC cacheable
		uint32_t hwpf			: 1;	// L1DC HW PF
		uint32_t 				: 1;	// Reserved
		uint32_t l1w			: 1;	// L1DC write policy
		uint32_t l2a_c_wr		: 4;	// L2 Cache Policy for write accesses
		uint32_t l2a_c_rd		: 4;	// L2 Cache Policy for cacheable read accesses
		uint32_t l2a_swop		: 4;	// L2 Cache Policy for cache software operations read accesses
#else /* !CEVABX */
		uint32_t				: 16;	// Reserved
#endif /* CEVABX */
		uint32_t mom			: 1;	// Memory Ordering Model
		uint32_t ap				: 3;	// Access Protection
		uint32_t				: 4;	// Reserved
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
		uint32_t rqos			: 4;	// Read transaction Quality of Service
		uint32_t wqos			: 4;	// Write transaction Quality of Service
#else /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t				: 8;	// Reserved
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		//T_D_ADDx_ATT1
#ifdef CEVABX
		uint32_t				: 1;	// Reserved
#else /* !CEVABX */
		uint32_t exact_rd		: 1;	// DDMA external port read transactions pursues an exact read
#endif /* CEVABX */
		uint32_t l2a_wr			: 4;	// L2 Cache Policy for write accesses
		uint32_t l2a_rd			: 4;	// L2 cache policy for read accesses
		uint32_t dabsz			: 4;	// Data DMA maximum burst size. When 0, determined in the DDTC of the task
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
		uint32_t dadol			: 4;	// DDMA Download Outstanding Limit
		uint32_t				: 1;	// Reserved
		uint32_t dauol			: 3;	// DDMA Upload Outstanding Limit
#else /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t				: 8;	// Reserved
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */
		uint32_t 				: 11;	// Reserved
	}fields;
	struct{
		T_D_ADDx_START 	region_start;
		T_D_ADDx_ATT0 	region_att0;
		T_D_ADDx_ATT1	region_att1;
	}registers;
} T_dmss_region_attributes;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	DMSS - DDMA Task Descriptor Configuration Macros
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

#ifndef CEVABX

// CSL Internal macro DDMA_2D_SIMPLE_CONFIG
#define DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)\
		memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 									\
		_task_descriptor.fields.ddea = _dst_address;													\
		_task_descriptor.fields.ddia = _src_address;													\
		_task_descriptor.fields.tile_width = _tile_width;												\
		_task_descriptor.fields.tile_height = _tile_height;												\
		_task_descriptor.fields.int_stride = _src_stride;												\
		_task_descriptor.fields.ext_stride = _dst_stride
#endif /* CEVABX */

// CSL Internal macro DDMA_SIMPLE_CONFIG
#define DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size)				\
		memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 									\
		_task_descriptor.fields.ddtc = _transfer_size;													\
		_task_descriptor.fields.ddea = _dst_address;													\
		_task_descriptor.fields.ddia = _src_address

/*********************************************************************************************
* @macro	DDMA_CONFIG_MESSAGE_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as message download.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#ifdef DDCL_DESCRIPTOR
#define DDMA_CONFIG_MESSAGE_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)	do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);			  		\
		_task_descriptor.fields.message = DDCL_MESSAGE_DMA_MESSAGE;											\
		}while(0);
#else
#define DDMA_CONFIG_MESSAGE_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)	do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);			  		\
		_task_descriptor.fields.bsz = BSZ_MESSAGE;											\
		_task_descriptor.fields.ddtc = DDMA_MESSAGE_SIZE;													\
		}while(0);


#endif /*DDCL_DESCRIPTOR*/

/*********************************************************************************************
* @macro	DDMA_CONFIG_MESSAGE_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as message upload.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#ifdef DDCL_DESCRIPTOR
#define DDMA_CONFIG_MESSAGE_UPLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)	do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);			  		\
		_task_descriptor.fields.message = DDCL_MESSAGE_DMA_MESSAGE;										  	\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;													\
		} while(0);
#else
#define DDMA_CONFIG_MESSAGE_UPLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)	do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);			  		\
		_task_descriptor.fields.bsz = BSZ_MESSAGE;											\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;													\
		_task_descriptor.fields.ddtc = DDMA_MESSAGE_SIZE;													\
		} while(0);

#endif /*DDCL_DESCRIPTOR*/

/*********************************************************************************************
* @macro	DDMA_CONFIG_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size) do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);			  		\
		_task_descriptor.fields.iit = (uint8_t) DDCL_IIT_DMA_INTERNAL_TRANSFER; 										\
		}while(0);

/*********************************************************************************************
* @macro	DDMA_CONFIG_LINEAR_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as linear download.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_LINEAR_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size) do{	\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);			  	\
		}while(0);

/*********************************************************************************************
* @macro	DDMA_CONFIG_LINEAR_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as linear upload.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_LINEAR_UPLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)	do{		\
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);			  	\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;												\
		}while(0);

#ifndef CEVABX

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_SRC_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as bank source linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_SRC_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size) do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);					  		\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_READ;												\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_SRC_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as two bank destination linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_SRC_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);  							\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_READ;								 		 		\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DST_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as bank destination linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DST_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size)  do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);					  		\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_WRITE;											\
		}while(0);


#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DST_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as two bank destination linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DST_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);  							\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_WRITE;								 		 		\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DUP_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as bank duplicate linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DUP_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size)  do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);					  		\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_ONE_BANK_WRITE;									\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DUP_LINEAR_INTERNAL
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as two bank linear internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DUP_LINEAR_INTERNAL(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);  							\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 									  	 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_TWO_BANK_WRITE;								 		 		\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_LINEAR_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank linear download.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_LINEAR_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)   	do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);					 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_WRITE;											\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_LINEAR_DOWNLOAD
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as one-bank linear upload.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_LINEAR_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);				 		 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_WRITE;								 		 		\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_LINEAR_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank linear upload.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_LINEAR_UPLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);				 		 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_READ;								 		 		\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;															\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_LINEAR_UPLOAD
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as two-bank linear upload.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_LINEAR_UPLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _transfer_size);				 		 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_READ;								 		 		\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;															\
		}while(0);
#endif
/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DUP_LINEAR_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank duplicate linear download.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DUP_LINEAR_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size)  do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);					 		\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_ONE_BANK_WRITE;									\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DUP_LINEAR_DOWNLOAD
* @author	Ravid Rzaev
* @date 	30/05/2021
* @brief	Configure the given task as two-bank duplicate linear download.
* @params	(_task_descriptor, _src_address, _dst_address, _transfer_size)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DUP_LINEAR_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _transfer_size) 		do{ \
		DDMA_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _transfer_size);				 		 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_TWO_BANK_WRITE;									\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_2D_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_2D_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _tile_width, _tile_height, _dst_stride, _src_stride);	\
		_task_descriptor.fields.tdt = 1;																								\
		}while(0);


/*********************************************************************************************
* @macro	DDMA_CONFIG_2D_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as 2D upload.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_2D_UPLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride) do{  \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride);	\
		_task_descriptor.fields.tdt = 1;																								\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;																			\
		}while(0);


/*********************************************************************************************
* @macro	DDMA_CONFIG_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as 2D internal.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride) do{  \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride);		\
		_task_descriptor.fields.tdt = 1;																								\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER;																	\
		}while(0);


/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_2D_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_2D_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride)  do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _tile_width, _tile_height, 0, _src_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_WRITE;															\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_2D_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as two-bank 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_2D_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride)  do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _tile_width, _tile_height, 0, _src_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_WRITE;															\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_2D_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank 2D upload.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_2D_UPLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _dst_stride) 	do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, 0, _dst_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;																			\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_READ;																\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_2D_UPLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as two-bank 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_2D_UPLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _dst_stride)   do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, 0, _dst_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.extw = DDCL_EXTW_UPLOAD;																			\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_READ;															\
		}while(0);
#endif


/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DUP_2D_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank dup 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DUP_2D_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _tile_width, _tile_height, 0, _src_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_ONE_BANK_WRITE;													\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DUP_2D_DOWNLOAD
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank dup 2D download.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DUP_2D_DOWNLOAD(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _dst_address, _src_address, _tile_width, _tile_height, 0, _src_stride);				\
		_task_descriptor.fields.tdt = 1;																							\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_TWO_BANK_WRITE;													\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_SRC_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank source 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_SRC_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _dst_stride)  do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, 0, _dst_stride);					\
		_task_descriptor.fields.tdt = 1;																								\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 											\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_READ;																	\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_SRC_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as two-bank source 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_SRC_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _dst_stride)  do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, 0, _dst_stride);					\
		_task_descriptor.fields.tdt = 1;																								\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 											\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_READ;																	\
		}while(0);

#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DST_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank destination 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DST_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, 0);		\
		_task_descriptor.fields.tdt = 1;														\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_ONE_BANK_WRITE;						\
		}while(0);

#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DST_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as two-bank destination 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DST_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, 0);		\
		_task_descriptor.fields.tdt = 1;														\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_TWO_BANK_WRITE;						\
		}while(0);
#endif

/*********************************************************************************************
* @macro	DDMA_CONFIG_ONE_BANK_DUP_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as one-bank duplicate 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_ONE_BANK_DUP_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, 0);	\
		_task_descriptor.fields.tdt = 1;														\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_ONE_BANK_WRITE;				\
		}while(0);


#ifndef SENSPRO
/*********************************************************************************************
* @macro	DDMA_CONFIG_TWO_BANK_DUP_2D_INTERNAL
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Configure the given task as two-bank duplicate 2D internal transfer.
* @params	(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, _dst_stride)
*********************************************************************************************/
#define DDMA_CONFIG_TWO_BANK_DUP_2D_INTERNAL(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride) do{ \
		DDMA_2D_SIMPLE_CONFIG(_task_descriptor, _src_address, _dst_address, _tile_width, _tile_height, _src_stride, 0);	\
		_task_descriptor.fields.tdt = 1;														\
		_task_descriptor.fields.iit = DDCL_IIT_DMA_INTERNAL_TRANSFER; 						 	\
		_task_descriptor.fields.trtyp = MSS_2DCFG1_TRTYP_DUPLICATE_TWO_BANK_WRITE;				\
		}while(0);
#endif

#endif /* !CEVABX */

/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	DMSS Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/
#ifndef  HW_CONFIG_BUS_PROTOCOL_AHB
/*********************************************************************************************
* @function	DMSS_set_port_rid
* @author	Ravid Rzaev
* @date 	07/11/2021
* @brief	Set the DATA AXI port read id (Each value in the D_PORT_WID and D_PORT_RID fields must be unique).
* @param	port_rid: 	Structure of PORT_RID register.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_set_port_rid(T_D_PORT_RID port_rid) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_set_port_wid
* @author	Ravid Rzaev
* @date 	07/11/2021
* @brief	Set the DATA AXI port write id (Each value in the D_PORT_WID and D_PORT_RID fields must be unique).
* @param	port_wid: 	Structure of PORT_WID register.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_set_port_wid(T_D_PORT_WID port_wid) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_set_ddma_global_max_outstanding
* @author	Ravid Rzaev
* @date 	03/03/2021
* @brief	Set the maximum number of outstanding AXI bursts used by DDMA.
* @param	outstanding_download: 	Download Outstanding Limit.
* @param	outstanding_upload: 	Upload Outstanding Limit.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_set_ddma_global_max_outstanding(E_mss_dacc_dol outstanding_download, E_mss_dacc_uol outstanding_upload ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* #ifndef  HW_CONFIG_BUS_PROTOCOL_AHB */

#if !(defined(SENSPRO_V1_2) || defined(CEVABX))
/***********************************************************
* @function	DMSS_set_access_protection
* @author	Ravid Rzaev
* @date 	03/03/2021
* @brief	Sets the policy for data access protection.
* @param	access_protection: Data access protection value.
* @return	CSL_SUCCESS or CSL_FAILURE.
 ***********************************************************/
E_csl_status DMSS_set_access_protection(E_mss_sdcfg_dape access_protection ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* !(defined(SENSPRO_V1_2) || defined(CEVABX)) */



/***********************************************************
* @function	DMSS_get_idm_base_address
* @author	Ravid Rzaev
* @date 	03/03/2021
* @brief	Returns the IDM base address.
* @return	IDM base address value.
 ***********************************************************/
uint32_t DMSS_get_idm_base_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");

/***********************************************************
* @function	DMSS_set_idm_access_protection_level
* @author	Eran Rebenshtok
* @date 	08/08/2022
* @param	idm_access_level: 			The IDM access protection level
* @brief	Sets the IDM access protection level for core load/store and slave port transactions.
* @return	CSL_SUCCESS or CSL_FAILURE.
 ***********************************************************/
E_csl_status DMSS_set_idm_access_protection_level( E_d_dtap_ap idm_access_level ) PRAGMA_CSECT( "CSL_CODE_SECTION" );

/***********************************************************
* @function	DMSS_get_idm_access_protection_level
* @author	Eran Rebenshtok
* @date 	08/08/2022
* @brief	Returns the IDM access protection level for core load/store and slave port transactions.
* @return	The IDM access protection level
 ***********************************************************/
E_d_dtap_ap DMSS_get_idm_access_protection_level( void ) PRAGMA_CSECT( "CSL_CODE_SECTION" );


/***********************************************************
* @function	DMSS_set_internal_barrier
* @author	Ravid Rzaev
* @date 	04/03/2021
* @brief	Sets an internal barrier.
* @return	CSL_SUCCESS or CSL_FAILURE.
 ***********************************************************/
E_csl_status DMSS_set_internal_barrier(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_set_region_attributes
* @author	Ravid Rzaev
* @date 	25/02/2021
* @brief	Set the attributes for given region with given configuration.
* @param	region_num: 			data (DACU) region number.
* @param	p_region_attributes: 	Pointer to the data memory (DACU) region settings structure.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_set_region_attributes(uint8_t region_num, T_dmss_region_attributes *p_region_attributes ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
* @function	DMSS_get_region_attributes
* @author	Ravid Rzaev
* @date 	25/02/2021
* @brief	Reads the current value of DACU region attributes registers.
* @param	region_num: 			data (DACU) region number.
* @param	p_region_attributes: 	Pointer to the data memory (DACU) region settings structure.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_get_region_attributes(uint8_t region_num, T_dmss_region_attributes *p_region_attributes ) PRAGMA_CSECT("CSL_CODE_SECTION");


#if (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)


	/*********************************************************************************************
	* @function	DMSS_verify_message_download
	* @author	Ravid Rzaev
	* @date 	04/03/2021
	* @brief	Verifies the given DDMA task for message download.
	* @param	p_dma_task: Pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_message_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_message_upload
	* @author	Ravid Rzaev
	* @date 	04/03/2021
	* @brief	Verifies the given DDMA task for message upload.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_message_upload(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_linear_upload
	* @author	Ravid Rzaev
	* @date 	04/03/2021
	* @brief	Verifies the given DDMA task for linear upload.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_linear_upload(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_linear_download
	* @author	Ravid Rzaev
	* @date 	04/03/2021
	* @brief	Verifies the given DDMA task for linear download.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_linear_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_linear_internal
	* @author	Ravid Rzaev
	* @date 	04/03/2021
	* @brief	Verifies the given DDMA task for internal Linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_linear_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef CEVABX

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_src_linear_internal
	* @author	Ravid Rzaev
	* @date 	07/03/2021
	* @brief	Verifies the given DDMA one bank internal-to-internal linear transfer (bank access by src_adr).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @param	size: 		transfer size (must be multiple of 8).
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_src_linear_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_src_linear_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA two bank internal-to-internal linear transfer (bank access by src_adr).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @param	size: 		transfer size (must be multiple of 16).
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_src_linear_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_dst_linear_internal
	* @author	Ravid Rzaev
	* @date 	07/03/2021
	* @brief	Verifies the given DDMA one bank internal-to-internal linear transfer (bank access by dst_adr).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_dst_linear_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_dst_linear_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA two bank internal-to-internal linear transfer (bank access by dst_adr).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_dst_linear_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_dup_linear_internal
	* @author	Ravid Rzaev
	* @date 	07/03/2021
	* @brief	Verifies the given DDMA duplicate one bank internal-to-internal linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_dup_linear_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_dup_linear_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA duplicate two bank internal-to-internal linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_dup_linear_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_linear_download
	* @author	Ravid Rzaev
	* @date 	07/03/2021
	* @brief	Verifies the given DDMA one bank download linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_linear_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_linear_download
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA two bank download linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_linear_download(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_linear_upload
	* @author	Ravid Rzaev
	* @date 	07/03/2021
	* @brief	Verifies the given DDMA one bank upload linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_linear_upload(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_linear_upload
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA two bank upload linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_linear_upload(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_one_bank_dup_linear_download
	* @author	Ravid Rzaev
	* @date 	08/03/2021
	* @brief	Verifies the given DDMA duplicate one bank download linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_one_bank_dup_linear_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_two_bank_dup_linear_download
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a DDMA duplicate two bank download linear transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_two_bank_dup_linear_download(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_upload
	* @author	Ravid Rzaev
	* @date 	08/03/2021
	* @brief	Verifies the given DDMA 2d upload transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_upload(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	DMSS_verify_2d_download
	* @author	Ravid Rzaev
	* @date 	08/03/2021
	* @brief	Verifies the given DDMA 2d download transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_2d_internal
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verifies the given DDMA  2d internal transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");


	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_download
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verifies the given DDMA  2d download one bank transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_download
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d download two bank transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_download(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_upload
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verifies the given DDMA  2d upload one bank transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_upload(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_upload
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d upload two bank transferm.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_upload(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_dup_download
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verifies the given DDMA  2d download one bank transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_dup_download(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_dup_download
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d download two bank transfer.
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_dup_download(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_src_internal
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verify a DDMA  2d one bank internal-to-internal transfer
	* 			(bank access by source address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_src_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_src_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d two bank internal-to-internal transfer
	* 			(bank access by source address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_src_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_dst_internal
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verify a DDMA  2d one bank internal-to-internal transfer task
	* 			(bank access by destination address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_dst_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_dst_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d two bank internal-to-internal transfer task
	* 			(bank access by destination address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_dst_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

	/*********************************************************************************************
	* @function	DMSS_verify_2d_one_bank_dup_internal
	* @author	Ravid Rzaev
	* @date 	09/03/2021
	* @brief	Verify a DDMA  2d duplicate one bank
	* 			internal-to-internal transfer (bank access by destination address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_one_bank_dup_internal(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

#ifndef SENSPRO
	/*********************************************************************************************
	* @function	DMSS_verify_2d_two_bank_dup_internal
	* @author	Ravid Rzaev
	* @date 	30/05/2021
	* @brief	Verify a ddma 2d duplicate two bank
	* 			internal-to-internal transfer (bank access by destination address).
	* @param	p_dma_task: pointer to DDMA task structure.
	* @return	CSL_SUCCESS or CSL_FAILURE.
	*********************************************************************************************/
	E_csl_status DMSS_verify_2d_two_bank_dup_internal(T_ddma_task *p_dma_task) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif

#endif /* !CEVABX */


#else // (CSL_ASSRTIONS == CSL_CONFIG_DISABLED)


	#define DMSS_verify_message_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_message_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_linear_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_linear_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_src_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_dst_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_dup_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_linear_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_linear_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_one_bank_dup_linear_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_dup_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_src_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_dst_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_one_bank_dup_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_src_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_dst_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_dup_linear_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_linear_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_linear_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_two_bank_dup_linear_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_upload(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_dup_download(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_src_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_dst_internal(_p_dma_task )  CSL_SUCCESS
	#define DMSS_verify_2d_two_bank_dup_internal(_p_dma_task )  CSL_SUCCESS

#endif // (CSL_ASSRTIONS == CSL_CONFIG_DISABLED)


/*********************************************************************************************
* @function	DMSS_is_ddma_queue_full
* @author	Ravid Rzaev
* @date 	08/03/2021
* @brief	Returns an indication if the DDMA queue is full.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
bool DMSS_is_ddma_queue_full(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_execute_ddma_task
* @author	Ravid Rzaev
* @date 	10/03/2021
* @brief	Write and execute a DDMA task.
* @param	p_dma_task: pointer to DDMA task structure.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_execute_ddma_task(T_ddma_task *p_dma_task ) PRAGMA_CSECT("CSL_CODE_SECTION");

/*********************************************************************************************
* @function	DMSS_is_ddma_busy
* @author	Ravid Rzaev
* @date 	28/02/2021
* @brief	Return the DDMA status.
* @return	 CSL_TRUE or CSL_FALSE.
*********************************************************************************************/
bool DMSS_is_ddma_busy(void) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
* @function	DMSS_get_idle_indication
* @author	Anat Keidar
* @date 	15/06/2022
* @brief	Return the DMSS Idle status.
* @return	Register MSS_DMBE
*********************************************************************************************/
T_MSS_DMBE DMSS_get_idle_indication(void) PRAGMA_CSECT("CSL_CODE_SECTION");




#ifdef SENSPRO

/*********************************************************************************************
* @function	DMSS_pause_ddma
* @author	Ravid Rzaev
* @date 	10/03/2021
* @brief	Pause all DDMA transfers.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_pause_ddma(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_unpause_ddma
* @author	Ravid Rzaev
* @date 	10/03/2021
* @brief	Unpause the DDMA.
* @return	CSL_SUCCESS or CSL_FAILURE.
*********************************************************************************************/
E_csl_status DMSS_unpause_ddma(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	DMSS_is_ddma_paused
* @author	Ravid Rzaev
* @date 	10/03/2021
* @brief	Check if the DDMA is paused.
* @return	CSL_TRUE for paused, CSL_FALSE for not.
*********************************************************************************************/
bool DMSS_is_ddma_paused(void) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* SENSPRO */

CSL_CPP_END



#endif /* CEVA_DMSS_H_ */
