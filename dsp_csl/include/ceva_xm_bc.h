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
/*********************************************************************************************
 * File:			ceva_xm_bc.h
 * Created on: 		25/01/2021
 * Author: 			Anat Keidar
 * Description: 	All function definitions required to connect the CSL safety version to the BC version.
**********************************************************************************************/
#ifndef CEVA_CSL_BC_H_
#define CEVA_CSL_BC_H_
#include "ceva_csl.h"

#ifdef _BACKWARD_COMPATIBILITY

CSL_CPP_START

/** @brief DMA return status enumeration */
typedef enum
{
	DMA_STATUS_OK,                              /**< Status OK */
	DMA_STATUS_ERROR_PARAMS,                    /**< Error in function parameters */
	DMA_STATUS_ALLOC_FAILED,                    /**< Failed to allocate queue */
	DMA_STATUS_ENQUEUE_FAILED,                  /**< Failed to send new task to queue */
	DMA_STATUS_MANAGER_FAILURE,                 /**< Queue manager failure */
	DMA_STATUS_NOT_IMPLEMENTED,                 /**< Function not implemented yet */
	DMA_STATUS_WARNING_PARAMS					 /**< Function parameters may not be considered */
} dma_status_e;


#ifdef CSL_QMAN_SUPPORTED
	/** @} */

	/**
	*   @addtogroup DMA_DRIVER_TYPES QMAN/DDMA Driver Data Types
	*    @ingroup DMA_DRIVER
	*   @{
	*/

	/** @brief DMA task descriptor data structure (opaque) */
	typedef union
	{
		uint8_t bytes[sizeof(T_QMAN_task_descriptor)];
		T_QMAN_task_descriptor task_descriptor;
	} dma_desc_t;


	/** @brief DMA queue base structure */
	typedef struct dma_queue_base_t
	{
		uint32_t read_ptr;                          /**< current read pointer */
		uint32_t last_core_id;                      /**< last core ID */
		uint32_t write_ptr;                         /**< current write pointer */
		uint32_t id;                                /**< the queue's ID */
		uint32_t start_address;                     /**< pointer to the memory of the queue */
		uint32_t queue_depth_register;              /**< depth register */
		volatile uint32_t current_sync_value;       /**< current sync point value */
		uint32_t sync_counter;                      /**< current sync point counter */
		dma_desc_t sync_message_desc;               /**< sync point descriptor */
		T_csl_allocation_id allocation_id;
		uint32_t frame_length; 		// When set indicate that a tasks frame has started to be pushed and had not ended yet. Contains the remaining number of tasks to be pushed.
	} dma_queue_base_t;

#endif // #ifdef CSL_QMAN_SUPPORTED



#ifdef CEVA
	
	#if defined(CSL_ICU_SUPPORTED)
	typedef enum
	{
		ICU_OPOERATION_MASK 	= IMR0,
		ICU_OPOERATION_CLEAR 	= ICR0,
		ICU_OPOERATION_GENERATE = IGR0
	}e_icu_operation;

	
	/*********************************************************************************************
	 * @function	ICU_IVA_allocate_bc
	 * @author	Anat Keidar
	 * @date 	10/02/2021
	 * @brief	Allocates the first available interrupt vector address and sets the given ISR address.
	 * @param	isr_address: The address for the interrupt vector
	 * @return	Return the id number of the allocated IVA if there is available IVA, otherwise return CSL_ALLOCATION_FAILURE.
	*********************************************************************************************/
	T_csl_allocation_id ICU_IVA_allocate_bc(uint32_t isr_address) PRAGMA_CSECT("CSL_CODE_SECTION");

	/*********************************************************************************************
	* @function	ICU_interrupts_operation_bc
	* @author	Anat Keidar
	* @date 	27/01/2021
	* @brief	Set the given operation in the selected interrupts.
	* @param	operation: 		The operation to perform
	* @param	interrupts: 	Pointer to an array with the index of the selected interrupts.
	* @param	num_interrupts: The number of interrupts in the given interrupt array.
	* @param	set: 			set if true, clear if false.
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
		E_csl_status ICU_interrupts_operation_bc(e_icu_operation operation, uint8_t * interrupts, uint8_t num_interrupts, bool set) PRAGMA_CSECT("CSL_CODE_SECTION");
	#endif
    
    
    #if defined(CSL_TIMERS_SUPPORTED)
    
    //Timer Configuration Structure
    typedef union
    {
    	struct // T_TIMERx_CFG Configuration Register
    	{
    		uint32_t ts : 2; // Time Scale: 00 - TIMERx clock is divided by 1, 01 - TIMERx clock is divided by 2,
    								 // 10 - TIMERx clock is divided by 4, 11 - TIMERx clock is divided by 16
    		uint32_t cm : 3; // Count Mode
    		uint32_t es : 1; // Event Source
    		uint32_t tp : 1; // TIMERx_OUT Polarity
    		uint32_t tm : 2; // TIMERx_OUT Mode
    		uint32_t trest_en : 1; // Enables the effect of the TIMERx_REST input bit
    		uint32_t cas : 1; // Cascade Mode
    		uint32_t : 5; // reserved
    		uint32_t res : 1; // Restart
    		uint32_t pc : 1; // Pause Count - stops the counter
    		uint32_t ct : 1; // Clear TIMERx_OUT
    		uint32_t ru : 1; // Read-time Count Update
    		uint32_t bpen : 1; // DEBUG Enable - places the TIMERx unit in pause when core is in debug mode
    		uint32_t : 11; // Reserved
    	} ;
    	T_TIMERx_CFG timer_cfg;
    
    } T_TimerConfiguation;


	/*********************************************************************************************
	 * @function	TIMER_allocate_bc
	 * @author	Ravid Rzaev
	 * @date 	08/02/2021
	 * @brief	allocates the first available timer using the configuration.
	 * @param	timer_config: 	Timer configuration to allocate timer by.
	 * @return	Return the id number of the allocated timer if there is available timer, otherwise an CSL_ASSERT_CODE_TYPE_ALLOCATION_FAILURE is returned.
	*********************************************************************************************/
		uint32_t TIMER_allocate_bc(T_TIMERx_CFG timer_config) PRAGMA_CSECT("CSL_CODE_SECTION");
	#endif



	/*********************************************************************************************
	* @function	PMSS_set_region_attributes_bc
	* @author	Ravid Rzaev
	* @date 	25/02/2021
	* @brief	Set the attributes for given region with given configuration.
	* @param	region_num: 	Instruction region number.
	* @param	p_region_attributes: 	Pointer to the program memory region settings structure.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PMSS_set_region_attributes_bc(uint8_t region_num, T_pmss_region_attributes p_region_attributes) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	* @function	PMSS_enable_global_program_cache_bc
	* @author	Ravid Rzaev
	* @date 	01/03/2021
	* @brief	Enables program cache in region 0.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status PMSS_enable_global_program_cache_bc( void ) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	 * @function	PMSS_set_pdma_task_bc
	 * @author	Ravid Rzaev
	 * @date 	28/02/2021
	 * @brief	Write and execute a PDMA task.
	 * @param	p_pdma_task: pointer to PDMA task structure.
	 * @return	CEVA_SUCCESS or CEVA_FAIL.
	*********************************************************************************************/
	E_csl_status PMSS_set_pdma_task_bc(uint32_t int_address, uint32_t ext_address, uint32_t size, uint8_t en_interrupt) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* CEVA */


#if !defined(CEVA) && defined(SENSPRO)
	/*********************************************************************************************
	* @function	CSL_start_bc
	* @author	Eran Rebenshtok
	* @date 	08/03/2021
	* @brief	CSL initialization function. Starts the DMA Simulator if is active.
	* @param	core_type	The target core type
	* @return	CSL_SUCCESS or CSL failure code
	*********************************************************************************************/
	dma_status_e CSL_start_bc( E_DSP_sim_type *core_type ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif // #if !defined(CEVA) && defined(SENSPRO)





#ifdef CSL_QMAN_SUPPORTED

	/*********************************************************************************
	 * @function	QMAN_allocate_bc
	 * @author	Anat Keidar
	 * @date 	01/03/2021
	 * @brief	Allocate a QMAN and configures with the given parameters and reset values.
	 * @param	queue:			   Pointer to the task descriptors queue
	 * @param	absolute_priority: The absolute priority for queue
	 * @param	queue_size:		   The queue size
	 * @param	continuous_mode:   Activate a queue in continuous mode
	 * @return	QMAN Allocation ID or CSL_ALLOCATION_FAILURE
	**********************************************************************************/
#if defined(SENSPRO)
	T_csl_allocation_id QMAN_allocate_bc(T_QMAN_task_descriptor* queue, uint8_t absolute_priority, uint16_t queue_size, E_QMAN_config_qx_auto continuous_mode ) PRAGMA_CSECT("CSL_CODE_SECTION");
#else // #if defined(SENSPRO)
	T_csl_allocation_id QMAN_allocate_bc(T_QMAN_task_descriptor* queue, uint8_t absolute_priority, uint16_t queue_size ) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif // #if defined(SENSPRO)



/*********************************************************************************
 * @function	QMAN_deallocate_bc
 * @author	Anat Keidar
 * @date 	20/12/2020
 * @brief	Deallocate and disable the given QMAN hardware.
 * @param	qman_id: The allocation ID of the QMAN
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_deallocate_bc(T_csl_allocation_id qman_id ) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
* @function	QMAN_create_internal_message_task_bc
* @author	Anat Keidar
* @date 	04/03/2021
* @brief	Create and verify a QMAN task for message download.
* @param	task_descriptor: Pointer to a QMAN task descriptor.
* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
*********************************************************************************************/
dma_status_e QMAN_create_internal_message_task_bc(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





/*********************************************************************************************
* @function	QMAN_create_external_message_task_bc
* @author	Anat Keidar
* @date 	04/03/2021
* @brief	Create and verify a QMAN task for message upload.
* @param	task_descriptor: Pointer to a QMAN task descriptor.
* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
*********************************************************************************************/
dma_status_e QMAN_create_external_message_task_bc(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






/*********************************************************************************************
* @function	QMAN_create_linear_task_bc
* @author	Anat Keidar
* @date 	04/03/2021
* @brief	Create and verify a QMAN task for linear transfer.
* @param	task_descriptor: Pointer to a QMAN task descriptor.
* @param     length - number of bytes to copy
* @param     dir - direction of the transfer
* @param     tr_type - internal memory access type
* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
*********************************************************************************************/
dma_status_e QMAN_create_linear_task_bc(T_QMAN_task_descriptor *task_descriptor, uint32_t length, E_QMAN_task_descriptor_dup dir, E_QMAN_task_descriptor_trtyp tr_type) PRAGMA_CSECT("CSL_CODE_SECTION");






/*********************************************************************************************
* @function	QMAN_create_multi_di_task_bc
* @author	Anat Keidar
* @date 	04/03/2021
* @brief	Create and verify a QMAN task for linear transfer.
* @param	task_descriptor: Pointer to a QMAN task descriptor.
* @param     width - number of bytes in a row to copy
* @param     height - number of rows to copy
* @param     src_stride - source stride in bytes
* @param     dst_stride - destination stride in bytes
* @param     dir - direction of the transfer
* @param     tr_type - internal memory access type
* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
*********************************************************************************************/
dma_status_e QMAN_create_multi_di_task_bc(T_QMAN_task_descriptor *task_descriptor, uint16_t width,
	uint16_t height, uint16_t num_planes, uint16_t src_stride,
	uint16_t dst_stride, uint32_t src_plane_stride,
	uint32_t dst_plane_stride, E_QMAN_task_descriptor_dup dir, E_QMAN_task_descriptor_trtyp tr_type) PRAGMA_CSECT("CSL_CODE_SECTION");





#ifndef XM4


	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR



		/*********************************************************************************************
		* @function	QMAN_create_image_bc
		* @author	Anat Keidar
		* @date 	04/03/2021
		* @brief	Create and verify a QMAN task for linear transfer.
		* @param	virtual_descriptor: Image descriptor (to be constructed).
		* @param	i_start: 			Pointer to an image start address (first plane).
		* @param	i_height:			Height of image (in number of lines). Used only if: is_clip_enabled == true.
		* @param	i_width:			Width of image (number of pixels in each plane). Used only if: is_clip_enabled == true.
		* @param	i_line_stride:		Plane line stride (in bytes). Must be aligned to element_size.
		* @param	i_plane_stride:		Plane stride (in bytes). Must be aligned to element_size.
		* @param	pad_val:			Padding value (in bytes). Used only if: is_clip_enabled == true. Actual value is in accordance to element_size.
		* @param	element_size:		Pixel size (see element_size_e)
		* @param	num_channels:		Number of pixel channels (see elements_number_e)
		* @param	is_clip_enabled:	Clipping value enable (see clip_enable_e)
		* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
		*********************************************************************************************/
		dma_status_e QMAN_create_image_bc(T_QMAN_virtual_descriptor* virtual_descriptor, void*         i_start         , uint16_t i_height, uint16_t       i_width     ,
				uint16_t          i_line_stride, uint32_t      i_plane_stride  , uint32_t pad_val , E_qman_virtual_element_sz element_size,
				E_qman_virtual_num_ch num_channels , E_qman_virtual_clip_en is_clip_enabled ) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_create_image_task_bc
		* @author	Anat Keidar
		* @date 	04/03/2021
		* @brief	Create and verify a QMAN task for linear transfer.
		* @param	task_descriptor: QMAN task descriptor (to be constructed).
		* @param	src: 			Source image descriptor.
		* @param	dst:			Destination image descriptor.
		* @param	tile_width:		Width of a sub image (number of pixels).
		* @param	tile_height:	Height of a sub image (number of lines).
		* @param	num_planes:		Number of planes.
		* @param	unpack:			Number of channel elements to be unpacked (see channel_unpack_e).
		* @return	DMA_STATUS_OK or DMA_STATUS_ERROR_PARAMS.
		*********************************************************************************************/
		dma_status_e QMAN_create_image_task_bc(T_QMAN_task_descriptor *task_descriptor,  T_QMAN_virtual_descriptor*  src        , T_QMAN_virtual_descriptor* dst       ,
				uint16_t         tile_width, uint16_t           tile_height, uint16_t          num_planes,
				E_qman_task_chn_unpack unpack	  ) PRAGMA_CSECT("CSL_CODE_SECTION");



	#endif /* CSL_QMAN_VIRTUAL_DESCRIPTOR */




	/**
	* @brief Updates the tile dimensions in a three-dimensional transfer task descriptor
	* @param[in,out] desc - pointer to the descriptor to update
	* @param[in]     height - number of rows in tile
	* @param[in]     width - number of bytes in a tile width
	* @param[in]     num_planes - number of planes
	* @return #dma_status_e status code
	* @retval #DMA_STATUS_OK - the task descriptor was updated successfully
	* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
	*/
	dma_status_e dma_update_3d_desc_size(dma_desc_t* desc, uint16_t height, uint16_t width, uint16_t num_planes) PRAGMA_CSECT("CSL_CODE_SECTION");



#endif /* !XM4 */

/**
* @brief Waits for a sync point
*
* The function blocks until the expected sync point value is obtained. The function uses a busy-wait polling loop.
* @param[in]     queue - pointer to the queue base structure
* @param[in]     value - expected sync point value (obtained from #dma_enqueue_sync_point)
* @return #dma_status_e status code
* @retval #DMA_STATUS_OK - no error
* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue
*/
dma_status_e dma_wait_sync_point(dma_queue_base_t* queue, uint32_t value) PRAGMA_CSECT("CSL_CODE_SECTION");

/**
* @brief Updates the length parameter of a one-dimensional transfer task descriptor
* @param[in,out] desc - pointer to the descriptor to update
* @param[in]     length - number of bytes to copy
* @return #dma_status_e status code
* @retval #DMA_STATUS_OK - the the task descriptor was updated successfully
* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
*/
dma_status_e dma_update_1d_desc_size(dma_desc_t* desc, uint32_t length) PRAGMA_CSECT("CSL_CODE_SECTION");




/**
* @brief Updates the tile dimensions in a two-dimensional transfer task descriptor
* @param[in,out] desc - pointer to the descriptor to update
* @param[in]     height - number of rows in tile
* @param[in]     width - number of bytes int a tile width
* @return #dma_status_e status code
* @retval #DMA_STATUS_OK - the task descriptor was updated successfully
* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
*/
dma_status_e dma_update_2d_desc_size(dma_desc_t* desc, uint16_t height, uint16_t width) PRAGMA_CSECT("CSL_CODE_SECTION");



#endif // #ifdef CSL_TIMERS_SUPPORTED




CSL_CPP_END




#endif /* _BACKWARD_COMPATIBILITY */
#endif /* CEVA_CSL_BC_H_ */
