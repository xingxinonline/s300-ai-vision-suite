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
#ifndef CEVA_SENSPRO_MEMORY_MAP_H_
#define CEVA_SENSPRO_MEMORY_MAP_H_

#ifdef SENSPRO
/*********************************************************************************************
 * File:			ceva_senspro_memory_map.h
 * Created on: 		25/01/2021
 * Author: 			Anat Keidar
 * Description: 	Defines the CEVA-SensPro CPM memory map per Program Model
**********************************************************************************************/

#include "ceva_cpm_io.h"
#include "ceva_aux.h"
#include "ceva_hw_conf.h"


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	CPM Registers Memory Map 
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/




/*
 * @macro	Qx_<CPM_REGISTER_NAME>(_qman_num)
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Queue Manager Programming Model
 * */
#define QUEUE_MANAGER_CPM_BASE_ADDR 0x00001200U
#define QMAN_OFFSET              	0x00000080U
#define Qx_EN_DEPTH(_qman_num)		( uint32_t )(0x00000000U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_FIRST_ADDR(_qman_num)	( uint32_t )(0x00000004U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_BASE_PTR(_qman_num)		( uint32_t )(0x00000008U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_CHNK_SIZE(_qman_num)		( uint32_t )(0x0000000CU + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_EN_INC0(_qman_num)	( uint32_t )(0x00000010U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_STATUS(_qman_num)		( uint32_t )(0x00000014U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_RPTR_INT(_qman_num)		( uint32_t )(0x00000018U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_CFG(_qman_num)		( uint32_t )(0x0000001cU + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_SRCP(_qman_num)		( uint32_t )(0x00000020U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_DSTP(_qman_num)		( uint32_t )(0x00000024U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_DMASZ(_qman_num)		( uint32_t )(0x00000028U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_SRC(_qman_num)		( uint32_t )(0x0000002cU + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_LINE(_qman_num)		( uint32_t )(0x00000030U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_DST(_qman_num)		( uint32_t )(0x00000034U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_HGHT(_qman_num)		( uint32_t )(0x00000038U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_DSC_EN_INC1(_qman_num)	( uint32_t )(0x00000040U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))
#define Qx_EN_CNT(_qman_num)		( uint32_t )(0x00000044U + (QUEUE_MANAGER_CPM_BASE_ADDR) + ((QMAN_OFFSET) * (( uint32_t )_qman_num)))

#define DSC_EN_INC_ENABLE_TASK	0x00030001


/*
 * @macro	E_queue_descriptor_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Interrupt Control Programming Model CPM register addresses
 * */
#define INTERRUPT_CONTROL_CPM_BASE_ADDR 0x00002100U
 typedef enum
{
	ISR0 			= 0x000 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	ICR0 			= 0x020 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	IGR0 			= 0x040 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	IMR0 			= 0x060 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	IGMR			= 0x0e0 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	IVA0 			= 0x108 + INTERRUPT_CONTROL_CPM_BASE_ADDR,
	ICFG0 			= 0x200 + INTERRUPT_CONTROL_CPM_BASE_ADDR
}E_interrupt_control_cpm_addr;


#define ICU_REG_OFFSET 0x4
#define ICU_REGISTER_GROUP_ADDRESS(_group_base_address, _group_index) (_group_base_address + ( ICU_REG_OFFSET * _group_index ) )
#define ISRx(_isr_num)		((uint32_t)ISR0 + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_isr_num))
#define ICRx(_icr_num)		((uint32_t)ICR0 + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_icr_num))
#define IGRx(_igr_num)		((uint32_t)IGR0 + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_igr_num))
#define IMRx(_imr_num)		((uint32_t)IMR0 + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_imr_num))
#define IVAx(_ivr_num)		((uint32_t)IVA0  + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_ivr_num))
#define ICFGx(_icfg_num)	((uint32_t)ICFG0 + ((uint32_t)ICU_REG_OFFSET * (uint32_t)_icfg_num))




/*
 * @macro	TIMERx_<CPM_REGISTER_NAME>(_timer_num)
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Timers Programming Model CPM register addresses
 * */
#define TIMERS_CPM_BASE_ADDR 0x00002000U
#define TIMERS_REG_OFFSET 0x00000010U
#define TIMERx_CFG(_timer_num)		( uint32_t )(0X00000000U + (TIMERS_CPM_BASE_ADDR) + ((TIMERS_REG_OFFSET) * _timer_num))
#define TIMERx_EW(_timer_num)		( uint32_t )(0X00000004U + (TIMERS_CPM_BASE_ADDR) + ((TIMERS_REG_OFFSET) * _timer_num))
#define TIMERx_CC(_timer_num)		( uint32_t )(0X00000008U + (TIMERS_CPM_BASE_ADDR) + ((TIMERS_REG_OFFSET) * _timer_num))
#define TIMERx_SC(_timer_num)		( uint32_t )(0X0000000cU + (TIMERS_CPM_BASE_ADDR) + ((TIMERS_REG_OFFSET) * _timer_num))

//******************************
// Watchdog programming model
//******************************
#define WD_BASE_ADDR 0x00000700U
typedef enum
{
	WDOGACS = 0x0 + WD_BASE_ADDR,
	WDOGCFG = 0x4 + WD_BASE_ADDR,
	WDOGMIN = 0x8 + WD_BASE_ADDR,
	WDOGMAX = 0xc + WD_BASE_ADDR,
	WDOGCNT = 0x18 + WD_BASE_ADDR,
	MPWDOGCFG = 0x1c + WD_BASE_ADDR,
	MPWDOGT = 0x20 + WD_BASE_ADDR,
	EPPWDOGC = 0x28 + WD_BASE_ADDR,
	EDPWDOGC = 0x2c + WD_BASE_ADDR,
	AM0WDOGC = 0x30 + WD_BASE_ADDR,
	AM1WDOGC = 0x34 + WD_BASE_ADDR,
	ICUWDOGCFG = 0x40 + WD_BASE_ADDR,
	ICUWDOGT = 0x44 + WD_BASE_ADDR,
	SYSWDOGSIG = 0x48 + WD_BASE_ADDR,
	ICUWDOGC = 0x4c + WD_BASE_ADDR,
}E_WD_Regs_Addr;


/*
 * @enum	E_queue_descriptor_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Queue Descriptor Programming Model CPM register addresses
 * */
#define QUEUE_DESCRIPTOR_CPM_BASE_ADDR 0x00001100U
typedef enum
{
	QPUSH_DSC_CFG 			= 0x00 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_SRCP 			= 0x04 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_DSTP 			= 0x08 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_DMASZ 		= 0x0c + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_SRC 			= 0x10 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_LINE 			= 0x14 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_DST 			= 0x18 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_DSC_HGHT 			= 0x1c + QUEUE_DESCRIPTOR_CPM_BASE_ADDR,
	QPUSH_NUM 				= 0x20 + QUEUE_DESCRIPTOR_CPM_BASE_ADDR
}E_queue_descriptor_cpm_addr;




/*
 * @enum	E_qman_cntrl_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	QMAN Cntrl Programming Model CPM register addresses
 * */
#define QMAN_CNTRL_CPM_BASE_ADDR 0x00001180U
typedef enum
{
	QMAN_IDM_CROSS 			= 0x00 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_ACTIVE 			= 0x04 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_VI_MASK 			= 0x14 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_IRQ_STATUS 		= 0x18 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_RST 				= 0x1c + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_QFULL 				= 0x24 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_QFULL_MASK 		= 0x28 + QMAN_CNTRL_CPM_BASE_ADDR,
	QMAN_PAUSE 				= 0x30 + QMAN_CNTRL_CPM_BASE_ADDR
}E_qman_cntrl_cpm_addr;





/*
 * @enum	E_pmss_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Program Memory Subsystem (PMSS) Programming Model CPM register addresses
 * */
#define PMSS_CPM_BASE_ADDR 0x00000400U
typedef enum
{
	MSS_PCR_reg 	= 0x000 + PMSS_CPM_BASE_ADDR,
	P_SYS_OU_C 		= 0x004 + PMSS_CPM_BASE_ADDR,
	P_HDCFG 		= 0x008 + PMSS_CPM_BASE_ADDR,
	P_PDEA 			= 0x010 + PMSS_CPM_BASE_ADDR,
	P_PDIA 			= 0x014 + PMSS_CPM_BASE_ADDR,
	P_PDTC 			= 0x018 + PMSS_CPM_BASE_ADDR,
	P_PORT_ID 		= 0x01c + PMSS_CPM_BASE_ADDR,
	P_ADD0_START 	= 0x020 + PMSS_CPM_BASE_ADDR,
	P_ADD0_ATT0 	= 0x024 + PMSS_CPM_BASE_ADDR,
	P_CCOSAR_reg 	= 0x0e0 + PMSS_CPM_BASE_ADDR,
	P_CCOCR_reg 	= 0x0e4 + PMSS_CPM_BASE_ADDR,
	P_ECADD_reg 	= 0x0f0 + PMSS_CPM_BASE_ADDR,
	PMSSACS 		= 0x140 + PMSS_CPM_BASE_ADDR
}E_PMSS_Regs_Addr;
#define PMSS_REG_OFFSET ( ( uint32_t )0x8 )
#define P_ADDx_START(_pmss_region_num)	( ( uint32_t )P_ADD0_START + ( PMSS_REG_OFFSET * ( ( uint32_t )_pmss_region_num ) ) )
#define P_ADDx_ATT0(_pmss_region_num)	( ( uint32_t )P_ADD0_ATT0 + ( PMSS_REG_OFFSET * ( ( uint32_t )_pmss_region_num ) ) )




/*
 * @enum	E_dmss_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Data Memory Subsystem (DMSS) Programming Model CPM register addresses
 * */
#define	DMSS_CPM_BASE_ADDR 0x00000600U
typedef enum
{
	MSS_DMBA		 	= 0x000 + DMSS_CPM_BASE_ADDR,
	MSS_DMBE	 		= 0x004 + DMSS_CPM_BASE_ADDR,
	MSS_HDCFG 			= 0x01c + DMSS_CPM_BASE_ADDR,
	MSS_GPIN 			= 0x020 + DMSS_CPM_BASE_ADDR,
	MSS_GPOUT	 		= 0x024 + DMSS_CPM_BASE_ADDR,
	MSS_DACC	 		= 0x028 + DMSS_CPM_BASE_ADDR,
	MSS_SDCFG 			= 0x02c + DMSS_CPM_BASE_ADDR,
	MSS_BARRIER 		= 0x038 + DMSS_CPM_BASE_ADDR,
	D_DMAB 				= 0x03c + DMSS_CPM_BASE_ADDR,
	DBG_WRC0 			= 0x044 + DMSS_CPM_BASE_ADDR,
	DBG_WRC1			= 0x048 + DMSS_CPM_BASE_ADDR,
	DBG_WRC2 			= 0x04c + DMSS_CPM_BASE_ADDR,
	MSS_DDTC			= 0x058 + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG1			= 0x060 + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG2			= 0x064 + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG3 			= 0x068 + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG4 			= 0x06c + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG5 			= 0x070 + DMSS_CPM_BASE_ADDR,
	MSS_2DCFG6 			= 0x074 + DMSS_CPM_BASE_ADDR,
	MSS_DDQS 			= 0x078 + DMSS_CPM_BASE_ADDR,
	MSS_DDEA 			= 0x080 + DMSS_CPM_BASE_ADDR,
	MSS_DDIA 			= 0x084 + DMSS_CPM_BASE_ADDR,
	MSS_DDCL 			= 0x08c + DMSS_CPM_BASE_ADDR,
	DDMA_PAUSE 			= 0x090 + DMSS_CPM_BASE_ADDR,
	MSS_DDESC_ID 		= 0x0a0 + DMSS_CPM_BASE_ADDR,
	MSS_DDESC_OV 		= 0x0a4 + DMSS_CPM_BASE_ADDR,
	MSTR_TASK_ID 		= 0x0a8 + DMSS_CPM_BASE_ADDR,
	QMAN_TASK_ID0		= 0x0b0 + DMSS_CPM_BASE_ADDR
}E_dmss_cpm_addr;
#define QMAN_TASK_IDx_REG_OFFSET 0x4
#define QMAN_TASK_IDx(_qman_num)	(QMAN_TASK_ID0 + QMAN_TASK_IDx_REG_OFFSET * _qman_num)
#define BARRIER_ACTIVATE	0x00000080U
#define DDCL_DESCRIPTOR



/*
 * @enum	E_dacu_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Interface Configuration (DACU Regions) Programming Model CPM register addresses
 * */
#define	DACU_CPM_BASE_ADDR 0x00000900U
typedef enum
{
	D_PORT_RID 		= 0x00 + DACU_CPM_BASE_ADDR,
	D_PORT_WID 		= 0x04 + DACU_CPM_BASE_ADDR,
	D_ADD0_START 	= 0x20 + DACU_CPM_BASE_ADDR,
	D_ADD0_ATT0 	= 0x24 + DACU_CPM_BASE_ADDR,
	D_ADD0_ATT1 	= 0x28 + DACU_CPM_BASE_ADDR,
}E_dacu_cpm_addr;

#define DACU_REG_OFFSET 0x10
#define D_ADDx_START(_region_num)	((uint32_t)D_ADD0_START + ((uint32_t) DACU_REG_OFFSET * (uint32_t)_region_num ))
#define D_ADDx_ATT0(_region_num)	((uint32_t)D_ADD0_ATT0 + ((uint32_t) DACU_REG_OFFSET * (uint32_t)_region_num ))
#define D_ADDx_ATT1(_region_num)	((uint32_t)D_ADD0_ATT1 + ((uint32_t) DACU_REG_OFFSET * (uint32_t)_region_num ))



/*
 * @enum	E_access_protection_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Access Protection Programming Model CPM register addresses
 * */
#define	ACCESS_PROTECTION_CPM_BASE_ADDR 0x00000c80U
typedef enum
{
	MAPAR 		= 0x00 + ACCESS_PROTECTION_CPM_BASE_ADDR,
	D_DTAP 		= 0x08 + ACCESS_PROTECTION_CPM_BASE_ADDR,
}E_access_protection_cpm_addr;




/*
 * @enum	E_hardware_exceptions_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Hardware Execptions (DBG) Programming Model CPM register addresses
 * */
#define	HW_EXCEPTIONS_CPM_BASE_ADDR 0x00000d00U
typedef enum
{
	DBG_DDAM			= 0x00 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBGACS				= 0x04 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_DDC				= 0x08 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_DDS				= 0x0c + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CENSIRQ				= 0x10 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CENSIRQ2			= 0x14 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CWDOGIRQ			= 0x18 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	NENSIRQ				= 0x1C + HW_EXCEPTIONS_CPM_BASE_ADDR,
	TIMER_IRQ			= 0x20 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DMA_IRQ				= 0x24 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	POSCINT				= 0x28 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	NQBIRQ				= 0x30 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	NENSIRQ_M			= 0x3C + HW_EXCEPTIONS_CPM_BASE_ADDR,
	TIMER_IRQ_M			= 0x40 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	NQBIRQ_M			= 0x44 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_STACK_START		= 0x50 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_STACK_END		= 0x54 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_DUNMPD_MSK		= 0x58 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_DUNMPD			= 0x5C + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CENSIRQ_S			= 0x60 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CENSIRQ2_S			= 0x64 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	CWDOGIRQ_S			= 0x68 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	NENSIRQ_S			= 0x6C + HW_EXCEPTIONS_CPM_BASE_ADDR,
	TIMER_IRQ_S			= 0x70 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DMA_IRQ_S     		= 0x74 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	UOP_STS				= 0xa0 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	UOP_PAR				= 0xa4 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_DESC_ID			= 0xb0 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	DBG_QMAN_ID			= 0xb4 + HW_EXCEPTIONS_CPM_BASE_ADDR,
	XCI_COR				= 0xc0 + HW_EXCEPTIONS_CPM_BASE_ADDR
}E_hardware_exceptions_cpm_addr;





/*
 * @enum	E_psu_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Power Scaling Unit (PSU) Programming Model CPM register addresses
 * */
#define PSU_CPM_BASE_ADDR 0x00000e50U
typedef enum
{
	PSVM				= 0x00 + PSU_CPM_BASE_ADDR,
	PGR					= 0x04 + PSU_CPM_BASE_ADDR,
	STRET				= 0x08 + PSU_CPM_BASE_ADDR,
	SPRET				= 0x0c + PSU_CPM_BASE_ADDR,
	STSD				= 0x10 + PSU_CPM_BASE_ADDR,
	SPSD				= 0x14 + PSU_CPM_BASE_ADDR
}E_psu_cpm_addr;




/*
 * @enum	E_rra_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Round Robin Arbiter (RRA) Programming Model CPM register addresses
 * */
#define RRA_CPM_BASE_ADDR 0x00000fa0U
typedef enum
{
	RRA_SLT_LO			= 0x00 + RRA_CPM_BASE_ADDR,
	RR_SLT_HI			= 0x04 + RRA_CPM_BASE_ADDR,
	RRA_SLT_PRI			= 0x08 + RRA_CPM_BASE_ADDR,
	RRA_WEIGHT_LO		= 0x0c + RRA_CPM_BASE_ADDR,
	RRA_WEIGHT_HI		= 0x10 + RRA_CPM_BASE_ADDR
}E_rra_cpm_addr;




/*
 * @enum	E_dcu_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Debug Core Unit (DCU) Programming Model CPM register addresses
 * */
#define DU_CPM_BASE_ADDR 0x00000110U
typedef enum
{
	OCM_PADD1 		= 0x000 + DU_CPM_BASE_ADDR,
	OCM_PADD2 		= 0x004 + DU_CPM_BASE_ADDR,
	OCM_PCOUNT1 	= 0x010 + DU_CPM_BASE_ADDR,
	OCM_PCOUNT2		= 0x014 + DU_CPM_BASE_ADDR,
	CEVAX_A_PC 		= 0x020 + DU_CPM_BASE_ADDR,
	OCM_DADD_LOW 	= 0x024 + DU_CPM_BASE_ADDR,
	OCM_DADD_HIGH 	= 0x028 + DU_CPM_BASE_ADDR,
	OCM_ACOUNT 		= 0x030 + DU_CPM_BASE_ADDR,
	OCM_DCOUNT 		= 0x034 + DU_CPM_BASE_ADDR,
	OCM_DVM 		= 0x038 + DU_CPM_BASE_ADDR,
	OCM_CONTROL 	= 0x040 + DU_CPM_BASE_ADDR,
	OCM_SA_BP_EN 	= 0x044 + DU_CPM_BASE_ADDR,
	MEM_CONFIG		= 0x048 + DU_CPM_BASE_ADDR,
	MSS_CONFIG   	= 0x04c + DU_CPM_BASE_ADDR,
	OCM_STATUS   	= 0x050 + DU_CPM_BASE_ADDR,
	OCM_SA_BP_ST   	= 0x054 + DU_CPM_BASE_ADDR,
	M_CONFIG   		= 0x058 + DU_CPM_BASE_ADDR,
	S_CONFIG	   	= 0x05c + DU_CPM_BASE_ADDR,
	DEBUG_CONFIG   	= 0x060 + DU_CPM_BASE_ADDR,
	CORE_VERSION   	= 0x064 + DU_CPM_BASE_ADDR,
	CORE_ID   		= 0x068 + DU_CPM_BASE_ADDR,
	CORE_CONFIG		= 0x06c + DU_CPM_BASE_ADDR
} E_dcu_cpm_addr;




/*
 * @enum	E_profiler_cpm_addr
 * @author	Anat Keidar
 * @date 	25/01/2021
 * @brief	Debug Unit (DU) Programming Model CPM register addresses
 * */

#define PROFILER_CPM_BASE_ADDR 0x00000300U
typedef enum
{
	PROF_CTL  		= 0x00U + PROFILER_CPM_BASE_ADDR,
	PROF_PAUSE  	= 0x04U + PROFILER_CPM_BASE_ADDR,
	PROF_CTRL0  	= 0x08U + PROFILER_CPM_BASE_ADDR,
	PROF_CTRL1  	= 0x0cU + PROFILER_CPM_BASE_ADDR,
	FRCC			= 0x10U + PROFILER_CPM_BASE_ADDR,
	PROF_CNT0		= 0x20U + PROFILER_CPM_BASE_ADDR,
	PROF_EV_MASK0 	= 0x80U + PROFILER_CPM_BASE_ADDR
} E_profiler_cpm_addr;

#define PROFILER_REG_OFFSET 		0x4U
#define PROF_CNTx(_counter_num)		((uint32_t)PROF_CNT0 + (PROFILER_REG_OFFSET * (uint32_t)_counter_num))
#define PROF_EV_MASKx(_counter_num)	((uint32_t)PROF_EV_MASK0 + (PROFILER_REG_OFFSET * (uint32_t)_counter_num))


/*
 * @enum	E_ecc_cpm_addr
 * @author	Ephi Frankel
 * @date 	06/04/2021
 * @brief	Error correction cods (ECC) CPM Registers (Part of Safety support)
 * */
#define	ECC_CPM_BASE_ADDR 0x00000784U
typedef enum
{
	D_ECCCOR 	= 0x00 + ECC_CPM_BASE_ADDR,
	D_ECCERR 	= 0x04 + ECC_CPM_BASE_ADDR,
}E_ecc_cpm_addr;

/*
 * @enum	E_dmss_safety_cpm_addr
 * @author	Ephi Frankel
 * @date 	06/04/2021
 * @brief	DMSS Safety CPM Registers
 * */
#define	ECC_DMSS_SAFETY_BASE_ADDR 0x000007b0U
typedef enum
{
	D_UCSERR 	 = (0x00 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_CSERR 	 = (0x08 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_UCSERR_S 	 = (0x10 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_CSERR_S 	 = (0x14 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_CSERR_M 	 = (0x1c + ECC_DMSS_SAFETY_BASE_ADDR),
	D_ECC_TCFG 	 = (0x20 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_ECC_TCFG_2 = (0x24 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_SFT_SCPD_x = (0x30 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_UCSERR_CNT = (0x40 + ECC_DMSS_SAFETY_BASE_ADDR),
	D_CSERR_CNT  = (0x44 + ECC_DMSS_SAFETY_BASE_ADDR),
}E_dmss_safety_cpm_addr;
#define D_SFT_SCPD_REG_OFFSET 0x4
#define D_SFT_SCPD_x(_scpd_num)		(D_SFT_SCPD_x+ D_SFT_SCPD_REG_OFFSET * _scpd_num)

/*
 * @enum	E_pmss_safety_cpm_addr
 * @author	Ephi Frankel
 * @date 	06/04/2021
 * @brief	PMSS Safety CPM Registers
 * */

#define	ECC_PMSS_SAFETY_BASE_ADDR 0x00000580U
typedef enum
{
	P_UCSERR 	   = (0x00 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_CSERR 	   = (0x08 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_UCSERR_S 	   = (0x10 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_CSERR_S 	   = (0x14 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_CSERR_M 	   = (0x1c + ECC_PMSS_SAFETY_BASE_ADDR),
	P_ECC_TCFG 	   = (0x30 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_ECC_TCFG_2   = (0x34 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_CTECC_TCFG   = (0x40 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_BTBECC_TCFG  = (0x50 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_UCSERR_CNT   = (0x70 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_CSERR_CNT    = (0x74 + ECC_PMSS_SAFETY_BASE_ADDR),
	P_LPCS         = (0x78 + ECC_PMSS_SAFETY_BASE_ADDR),
}E_pmss_safety_cpm_addr;

/*
 * @enum	E_core_safety_cpm_addr
 * @author	Ephi Frankel
 * @date 	02/08/2021
 * @brief	Core Safety CPM Registers
 * */
#define	ECC_CORE_SAFETY_BASE_ADDR 0x000000750
typedef enum
{
	C_UCPERR 	 = (0x00 + ECC_CORE_SAFETY_BASE_ADDR),
	C_UCPERR_S 	 = (0x04 + ECC_CORE_SAFETY_BASE_ADDR)
}E_core_safety_cpm_addr;


/*
 * @enum	E_mcci_cpm_addr
 * @author	Ravid Rzaev
 * @date 	14/11/2021
 * @brief	Multi Core Configuration interface (MCCI) Programming Model CPM register addresses
 * */

#define MCCI_CPM_BASE_ADDR 0x00000000U
typedef enum
{
	COM_REG0		        = 0x00U + MCCI_CPM_BASE_ADDR,
	COM_STS  	        	= 0x80U + MCCI_CPM_BASE_ADDR,
	COM_INT_EN			  	= 0x84U + MCCI_CPM_BASE_ADDR,
	START_ADDR0			  	= 0x90U + MCCI_CPM_BASE_ADDR,
	TOP_ADDR0				= 0x94U + MCCI_CPM_BASE_ADDR,
	SNOOP_CSR0				= 0x98U + MCCI_CPM_BASE_ADDR,
} E_mcci_cpm_addr;

#define MCCI_REG_OFFSET 0x4U
#define MCCI_SNOOP_REG_OFFSET 0xcU
#define COM_REGx(_counter_num)			        ((uint32_t)COM_REG0 + ( MCCI_REG_OFFSET * (uint32_t)_counter_num ))
#define START_ADDRx(_counter_num)			    ((uint32_t)START_ADDR0 + ( MCCI_SNOOP_REG_OFFSET * (uint32_t)_counter_num ))
#define	TOP_ADDRx(_counter_num)			        ((uint32_t)TOP_ADDR0 + ( MCCI_SNOOP_REG_OFFSET * (uint32_t)_counter_num ))
#define	SNOOP_CSRx(_counter_num)			    ((uint32_t)SNOOP_CSR0 + ( MCCI_SNOOP_REG_OFFSET * (uint32_t)_counter_num ))



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	CPM Registers Masks
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/
// Hardware Exceptions
#define CSL_CENSIRQ_MASK_0X00010202U 	   			0x00010202U
#define CSL_CENSIRQ2_MASK_0X00010002U 	    		0x00010002U
#define CSL_NENSIRQ_MASK			 	    		0x0004FF06U
#define CSL_NENSIRQ_M_MASK			 	    		( 0x00000007U | CSL_NENSIRQ_AXIS0 | CSL_NENSIRQ_AXIS1 | CSL_NENSIRQ_AXIS2 | CSL_NENSIRQ_EDAP |  CSL_NENSIRQ_EPP )
#define CSL_CWDOGIRQ_MASK 							0xF8130001U

// DMSS
#define CSL_DMBE_PORT_RID_IDLE_MASK 				0x00000C04U
#define CSL_DMBE_PORT_WID_IDLE_MASK 				0x00000C05U
#define CSL_DMBE_PORT_ID_IDLE_MASK 					0x00000C04U

// DDMA
#define CSL_DDMA_PAUSE_MASK 						0x00000001U
#define CSL_DDMA_IRQ_MASK 							0x00000001U
	
// PDMA	
#define CSL_PDMA_IRQ_MASK							0x00000002U
	
// Core register
#define CSL_CSR_NIE_MASK 							0x00000008U
	
#if (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)
	
	// Data Regions
	#define CSL_ICFG_MASK							0xFFFFFFFCU

	// ICU
	#define CSL_IMR_MASK							0xFFFFFFDEU
	
	// Timers
	#define CSL_TIMER_IRQ_MASK_BITS_MASK			0x0000000FU

	// ICU
	#define CSL_ISR_ALIGNMENT_MASK					0x000000FFU

	// Power Scaling unit
	#define CSL_PSVM_MASK							0x00000003U

#else  // (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)

	// Data Regions
	#define CSL_ICFG_MASK

	// ICU
	#define CSL_IMR_MASK
	
	// Timers
	#define CSL_TIMER_IRQ_MASK_BITS_MASK					

#endif // (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)














#endif // SENSPRO
#endif // CEVA_SENSPRO_MEMORY_MAP_H_
