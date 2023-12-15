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
#ifndef CEVA_QMAN_CONFIG_H_
#define CEVA_QMAN_CONFIG_H_
#include "ceva_hw_conf.h"
#ifdef CSL_QMAN_SUPPORTED
/*********************************************************************************************
 * @module			QMAN
 * @file			ceva_qman_config.h
 * @author			Anat Keidar
 * @date			28/02/2021
 * @brief			Define the configuration registers, values and functions of the Queue-Manager programming model
**********************************************************************************************/
#include "ceva_assert.h"
#include "ceva_qman_task_descriptor.h"

CSL_CPP_START


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Configuration Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/



/*************************
 * @struct		T_Qx_EN_DEPTH
 * @register	Qx_EN_DEPTH 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_depth		: 13;
		uint32_t				: 3;
        uint32_t qx_pri_abs		: 4;
        uint32_t qx_abs_sel		: 1;
        uint32_t qx_auto		: 1;
        uint32_t qx_cex_pause	: 1;
		uint32_t 				: 7;
        uint32_t qx_cont_frame	: 1;
        uint32_t qx_en			: 1;
    } fields;
    uint32_t value;
} T_Qx_EN_DEPTH;


/*************************
 * @struct		T_Qx_FIRST_ADDR
 * @register	Qx_FIRST_ADDR 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_first_addr	: 32;
    } fields;
    uint32_t value;
} T_Qx_FIRST_ADDR;


/*************************
 * @struct		T_Qx_BASE_PTR
 * @register	Qx_BASE_PTR 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_base_ptr	: 32;
    } fields;
    uint32_t value;
} T_Qx_BASE_PTR;


/*************************
 * @struct		T_Qx_CHNK_SIZE
 * @register	Qx_CHNK_SIZE 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_chnk_size	: 14;

	#ifdef CEVABX
		uint32_t				: 18;
	#else
		uint32_t				:  2;
		uint32_t qx_chnk_lines	: 16;
	#endif
    } fields;
    uint32_t value;
} T_Qx_CHNK_SIZE;


/*************************
 * @struct		T_Qx_DSC_EN_INC0
 * @register	Qx_DSC_EN_INC0 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_en_inc_val0		: 11;
		uint32_t					: 5;
        uint32_t qx_dsc_en0			: 1;
	#ifdef CEVABX
		uint32_t 					: 1;
	#else
		uint32_t qx_dsc_cnt_cfg_0	: 1;
	#endif
        uint32_t					: 13;
        uint32_t qx_en_cnt_dis0		: 1;
    } fields;
    uint32_t value;
} T_Qx_DSC_EN_INC0;


/*************************
 * @struct		T_Qx_STATUS
 * @register	Qx_STATUS 
 *************************/
typedef union
{
    struct
    {
		uint32_t			: 30;
#ifdef CEVABX
        uint32_t 			: 1;
#else
        uint32_t qx_wd_wait	: 1;
#endif
        uint32_t qx_status	: 1;
    } fields;
    uint32_t value;
} T_Qx_STATUS;


/*************************
 * @struct		T_Qx_RPTR_INT
 * @register	Qx_RPTR_INT 
 *************************/
typedef union
{
    struct
    {
		uint32_t qx_rptr_int	: 18;
        uint32_t				: 14;
    } fields;
    uint32_t value;
} T_Qx_RPTR_INT;


/*************************
 * @struct		T_Qx_DSC_CFG
 * @register	Qx_DSC_CFG 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_cfg	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_CFG;


/*************************
 * @struct		T_Qx_DSC_SRCP
 * @register	Qx_DSC_SRCP 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_srcp	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_SRCP;


/*************************
 * @struct		T_Qx_DSC_DSTP
 * @register	Qx_DSC_DSTP 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_dstp	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_DSTP;


/*************************
 * @struct		T_Qx_DSC_DMASZ
 * @register	Qx_DSC_DMASZ 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_dmasz	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_DMASZ;


/*************************
 * @struct		T_Qx_DSC_SRC
 * @register	Qx_DSC_SRC 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_src	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_SRC;


/*************************
 * @struct		T_Qx_DSC_LINE
 * @register	Qx_DSC_LINE 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_line	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_LINE;


/*************************
 * @struct		T_Qx_DSC_DST
 * @register	Qx_DSC_DST 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_dsc_dst	: 32;
    } fields;
    uint32_t value;
} T_Qx_DSC_DST;


/*************************
 * @struct		T_Qx_DSC_HGHT
 * @register	Qx_DSC_HGHT 
 *************************/
typedef union
{
 	struct
	{
		uint32_t qx_dsc_hght : 32;
	} fields;
	uint32_t value;
} T_Qx_DSC_HGHT;


/*************************
 * @struct		T_Qx_DSC_EN_INC1
 * @register	Qx_DSC_EN_INC1 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_en_inc_val1		: 11;
		uint32_t					: 5;
        uint32_t qx_dsc_en1			: 1;
        uint32_t qx_dsc_cnt_cfg_1	: 1;
        uint32_t					: 13;
        uint32_t qx_en_cnt_dis1		: 1;
    } fields;
    uint32_t value;
} T_Qx_DSC_EN_INC1;


/*************************
 * @struct		T_Qx_EN_CNT
 * @register	Qx_EN_CNT 
 *************************/
typedef union
{
    struct
    {
        uint32_t qx_en_cnt0	: 14;
		uint32_t			: 2;
        uint32_t qx_en_cnt1	: 14;
        uint32_t qx_wd_wait	: 1;
        uint32_t			: 1;
    } fields;
    uint32_t value;
} T_Qx_EN_CNT;



/*************************
 * @struct	T_QMAN_config
 * Registers: 
 *		- Qx_FIRST_ADDR 
 *		- Qx_BASE_PTR 
 *		- Qx_CHNK_SIZE 
 *		- Qx_DSC_EN_INC0 
 *		- Qx_DSC_EN_INC1 
 *		- Qx_EN_DEPTH 
 *************************/
typedef union
{
	struct
	{
		// Qx_FIRST_ADDR
		uint32_t qx_first_addr		:32;
		// Qx_BASE_PTR
        uint32_t qx_base_ptr		:32;
		// Qx_CHNK_SIZE
        uint32_t qx_chnk_size		:14;
		uint32_t					: 2;
        uint32_t qx_chnk_lines		:16;
		// Qx_DSC_EN_INC0
        uint32_t qx_en_inc_val0		:11;
		uint32_t					: 5;
        uint32_t qx_dsc_en0			: 1;
        uint32_t qx_dsc_cnt_cfg_0	: 1;
        uint32_t					:13;
        uint32_t qx_en_cnt_dis0		: 1;
		// Qx_DSC_EN_INC1
        uint32_t qx_en_inc_val1		:11;
		uint32_t					: 5;
        uint32_t qx_dsc_en1			: 1;
        uint32_t qx_dsc_cnt_cfg_1	: 1;
        uint32_t					:13;
        uint32_t qx_en_cnt_dis1		: 1;
		// Qx_EN_DEPTH
        uint32_t qx_depth			:13;
		uint32_t					: 3;
        uint32_t qx_pri_abs			: 4;
        uint32_t qx_abs_sel			: 1;
        uint32_t qx_auto			: 1;
        uint32_t qx_cex_pause		: 1;
		uint32_t 					: 7;
        uint32_t qx_cont_frame		: 1;
        uint32_t qx_en				: 1;
	} fields;
	struct
	{
		T_Qx_FIRST_ADDR 	qx_first_addr;
		T_Qx_BASE_PTR 		qx_base_ptr;
		T_Qx_CHNK_SIZE 	 	qx_chnk_size;
		T_Qx_DSC_EN_INC0 	qx_dsc_en_inc0;
		T_Qx_DSC_EN_INC1 	qx_dsc_en_inc1;
		T_Qx_EN_DEPTH 	 	qx_en_depth;	
	} registers;
} T_QMAN_config;





/************************************************
 * @struct		T_Queue_pointers
 * Description: Contains the QMAN shared pointers (aka the QMAN base pointers)
 ************************************************/
#define GET_QUEUE_ADDRESS(_qman_num) cpm_out1(QX_FIRST_ADDR(qman_num))
#define GET_QUEUE_POINTERS(_qman_num) ((T_QMAN_base_ptrs*)(cpm_out1(QX_BASE_PTR(qman_num))))









/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	T_QMAN_config Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/******************************************************
 * @enum 			E_QMAN_config_qx_pri_abs
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_PRI_ABS
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_PRI_ABS_0			= 0,
	QMAN_CONFIG_QX_PRI_ABS_1			= 1,
	QMAN_CONFIG_QX_PRI_ABS_2			= 2,
	QMAN_CONFIG_QX_PRI_ABS_3			= 3,
	QMAN_CONFIG_QX_PRI_ABS_4			= 4,
	QMAN_CONFIG_QX_PRI_ABS_5			= 5,
	QMAN_CONFIG_QX_PRI_ABS_6			= 6,
	QMAN_CONFIG_QX_PRI_ABS_7			= 7,
	QMAN_CONFIG_QX_PRI_ABS_HEIGHST		= QMAN_CONFIG_QX_PRI_ABS_0,
	QMAN_CONFIG_QX_PRI_ABS_LOWEST		= QMAN_CONFIG_QX_PRI_ABS_7
}E_QMAN_config_qx_pri_abs;


/******************************************************
 * @enum 			E_QMAN_config_qx_pri_abs_sel
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_PRI_ABS_SEL
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_PRI_ABS_SEL_TASK			= 0,
	QMAN_CONFIG_QX_PRI_ABS_SEL_QUEUE		= 1
}E_QMAN_config_qx_pri_abs_sel;


/******************************************************
 * @enum 			E_QMAN_config_qx_en_chnk_size
 * @config_group	T_QMAN_config
 * @register 		Qx_CHNK_SIZE
 * @brief			Reset values
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_CHNK_SIZE_RESET_VAlUE		= 0x10,
	QMAN_CONFIG_QX_CHNK_LINE_RESET_VAlUE		= 0x10
}E_QMAN_config_qx_en_chnk_size;


/******************************************************
 * @enum 			E_QMAN_config_qx_auto
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_AUTO
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_AUTO_ENABLE_TASK_COUNTER		= 0,
	QMAN_CONFIG_QX_AUTO_CONTINOUOS_EXECUTION	= 1
}E_QMAN_config_qx_auto;


/******************************************************
 * @enum 			E_QMAN_config_qx_cex_pause
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_CEX_PAUSE
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_CEX_RESUME	= 0,
	QMAN_CONFIG_QX_CEX_PAUSE	= 1
}E_QMAN_config_qx_cex_pause;


/******************************************************
 * @enum 			E_QMAN_config_qx_cont_frame
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_CONT_FRAME
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_CONT_FRAME_STALL		= 0, // Stall the next task frame until the last task in the current frame is completed
	QMAN_CONFIG_QX_CONT_FRAME_NO_STALL	= 1  // Continue reading tasks without waiting for the last task in the previous frame
}E_QMAN_config_qx_cont_frame;


/******************************************************
 * @enum 			E_QMAN_config_qx_en
 * @config_group	T_QMAN_config
 * @register 		Qx_EN_DEPTH
 * @field			Qx_EN
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_QX_EN_DISABLE 		= 0,
	QMAN_CONFIG_QX_EN_ENABLE		= 1
}E_QMAN_config_qx_en;



/******************************************************
 * @enum 			E_qman_config_qx_end_cnt_number
 * @registers 		Qx_EN_CNT_x
 ******************************************************/
typedef enum
{
	QMAN_CONFIG_ENABLED_TASK_COUNTER0      = 0,
	QMAN_CONFIG_ENABLED_TASK_COUNTER1      = 1
}E_qman_config_qx_en_cnt_number;






/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Configuration Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/





#ifdef CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED
	/*********************************************************************************
	 * @function	QMAN_allocate
	 * @author	Anat Keidar
	 * @date 	01/03/2021
	 * @brief	Allocate a QMAN and configures with the given parameters and reset values.
	 * @param	queue:			   Pointer to the task descriptors queue
	 * @param	absolute_priority: The absolute priority for queue
	 * @param	queue_size:		   The queue size
	 * @param	continuous_mode:   Activate a queue in continuous mode
	 * @return	QMAN Allocation ID or CSL_ALLOCATION_FAILURE
	**********************************************************************************/
	T_csl_allocation_id QMAN_allocate(T_QMAN_task_descriptor* queue, uint8_t absolute_priority, uint16_t queue_size, E_QMAN_config_qx_auto continuous_mode ) PRAGMA_CSECT("CSL_CODE_SECTION");
#else // #ifdef CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED
	/*********************************************************************************
	 * @function	QMAN_allocate
	 * @author	Anat Keidar
	 * @date 	01/03/2021
	 * @brief	Allocate a QMAN and configures with the given parameters and reset values.
	 * @param	queue:			   Pointer to the task descriptors queue
	 * @param	absolute_priority: The absolute priority for queue
	 * @param	queue_size:		   The queue size
	 * @param	continuous_mode:   Activate a queue in continuous mode
	 * @return	QMAN Allocation ID or CSL_ALLOCATION_FAILURE
	**********************************************************************************/
	T_csl_allocation_id QMAN_allocate(T_QMAN_task_descriptor* queue, uint8_t absolute_priority, uint16_t queue_size ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif // #else // #ifdef CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED





/*********************************************************************************
 * @function	QMAN_deallocate
 * @author	Anat Keidar
 * @date 	20/12/2020
 * @brief	Deallocate and disable the given QMAN hardware.
 * @param	qman_id: The allocation ID of the QMAN
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_deallocate(T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");





/*********************************************************************************
 * @function	QMAN_enable
 * @author	Anat Keidar
 * @date 	25/05/2022
 * @brief	Enable the QMAN operation
 * @param	qman_id: The allocation ID of the QMAN
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_enable(T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************
 * @function	QMAN_disable
 * @author	Anat Keidar
 * @date 	25/05/2022
 * @brief	Disable the QMAN operation
 * @param	qman_id: The allocation ID of the QMAN
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_disable(T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");





/*********************************************************************************************
 * @function			QMAN_is_sync_point_reached
 * @author			Anat Keidar
 * @date 			08/03/2021
 * @brief			Check if the sync point of the given QMAN has reached the given value.
 * @param			qman_id	- QMAN allocation id
 * @param 			sync_point_value - The expected sync point value.
 * @return			CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status QMAN_is_sync_point_reached(T_csl_allocation_id qman_id, uint32_t sync_point_value ) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************************
 * @function	QMAN_reset_sync_point
 * @author	Anat Keidar
 * @date 	08/03/2021
 * @brief	Reset the given QMAN sync mechanism.
 * @param	qman_id	- QMAN allocation did
 * @return	CSL_SUCCESS or CSL failure code
*********************************************************************************************/
E_csl_status QMAN_reset_sync_point(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");




	#ifdef CEVA

		/*********************************************************************************
		 * @function	QMAN_set_chunk_size_config
		 * @author	Anat Keidar
		 * @date 	20/12/2020
		 * @brief	Set the give chunk size in the configuration of the given QMAN.
		 * @param	qman_id: The allocation ID of the QMAN
		 * @param	chunk_size: For linear DDMA transactions indicates the size of a chunk used for activating the DDMA.
		 *						The chunk size is taken as QX_CHNK_SIZE * 128 Bytes
		 * @param	chunk_lines: For two dimensional DDMA determines the size of the chunk used for activating the DDMA.
		 *						 The chunk size is taken as QX_CHNK_LINES*TILE_WIDTH. (Supported cores: SensPro, XM6, XM4)
		 *						 Note: QX_CHNK_LINES must be larger than 0x0.
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		#ifdef CEVABX
			E_csl_status QMAN_set_chunk_size_config(T_csl_allocation_id qman_id, uint16_t chunk_size) PRAGMA_CSECT("CSL_CODE_SECTION");
		#else // #ifdef CEVABX
			E_csl_status QMAN_set_chunk_size_config(T_csl_allocation_id qman_id, uint16_t chunk_size, uint16_t  chunk_lines) PRAGMA_CSECT("CSL_CODE_SECTION");
		#endif // #else // #ifdef CEVABX





		/*********************************************************************************
		 * @function	QMAN_set_cont_frame
		 * @author	Anat Keidar
		 * @date 	01/12/2021
		 * @brief	Set the given qman with the QX_CONT_FRAME configuration:
		 * 				QMAN_CONFIG_QX_CONT_FRAME_STALL 	- stall the next task frame until the last task in the current frame is completed
		 * 				QMAN_CONFIG_QX_CONT_FRAME_NO_STALL 	- continue reading tasks without waiting for the last task in the previous frame
		 * 				Notice: Enabling this option does not support the sync point APIs
		 * @param	qman_id: The allocation ID of the QMAN
		 * @param	cont_frame: QMAN_CONFIG_QX_CONT_FRAME_STALL or QMAN_CONFIG_QX_CONT_FRAME_NO_STALL
		 * @return	CSL_SUCCESS or CSL failure code
		**********************************************************************************/
		E_csl_status QMAN_set_cont_frame (T_csl_allocation_id qman_id, E_QMAN_config_qx_cont_frame cont_frame) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************
		 * @function	QMAN_get_active_tasks_number
		 * @author	Eran Rebensthok
		 * @date 	09/06/2021
		 * @brief	Gets the number of active tasks in the queue
		 * @param	qman_id: The allocation ID of the QMAN
		 * @return	Number of active descriptor in queue or CSL_FAILURE code
		**********************************************************************************/
        uint32_t QMAN_get_active_tasks_number( T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");


	#endif /* CEVA */








CSL_CPP_END




#endif // #ifdef CSL_QMAN_SUPPORTED
#endif /* CEVA_QMAN_CONFIG_H_ */
