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
#ifndef __DMA_DRIVER_H__
#define __DMA_DRIVER_H__



//**********************************************************
//********************** Includes **************************
//**********************************************************
#include "ceva_xm_bc.h"


	/**
	* @brief Initializes the Queue Manager driver
	* @return #dma_status_e status code
	* @retval #DMA_STATUS_OK - no error
	* @retval #DMA_STATUS_MANAGER_FAILURE - Queue Manager driver initialization failed
	*/
    #ifdef CEVA
        #ifndef SENSPRO
        	#define dma_init_manager()              ((CSL_SUCCESS == CSL_start()) ? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)
        #else /* !SENSPRO */
            #define dma_init_manager(_core_type) 	((CSL_SUCCESS == CSL_start()) ? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)
        #endif /* SENSPRO */
    #else /* !CEVA */
        #ifndef SENSPRO
        	#define dma_init_manager()              ((CSL_SUCCESS == CSL_start( DMA_SIM_TYPE_GEN_CEVA )) ? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)
        #else /* SENSPRO */
            #define dma_init_manager(_core_type) 	CSL_start_bc( ( E_DSP_sim_type* )( uint32_t* )_core_type )
        #endif /* !SENSPRO */
    #endif /* CEVA */

#ifdef CSL_QMAN_SUPPORTED

//**********************************************************
//*********************** Macros ***************************
//**********************************************************
#if defined(SENSPRO)
	//Follow the steps below to enable support of QMAN exception handling:
	//Uncomment the comments below:
	#define QMAN_SUPPORTS_EXCPTN_HANDLE
	//Follow the steps below to enable support of QMAN Pause support
	//Uncomment the comments below:
	#define QMAN_SUPPORTS_PAUSE
	#if CEVA_DSP_RTL >= 120
		//Allows QMAN descriptor to be enqueue without stalling the MSS
		#define	QMAN_UNSTALLED_MSS
	#endif
#endif

//After following these steps, when QMANs queue and buffers are located within the IDM
//The driver will automatically use QMANs simplified interface to push the descriptor
#if defined XM6 || defined VECC_XM6 || defined VECC_SENSPRO || defined SENSPRO
    #define CEVA_DMA_EXTENDED_DESC
    #define CEVA_DMA_SUPPORT_3D
#elif defined XM4 && CEVA_DSP_RTL >= 120
    #define CEVA_DMA_EXTENDED_DESC
#endif 

#ifdef CEVA_DMA_EXTENDED_DESC
#define DDMA_DESC_SIZE_BYTES 32
#define DMA_MAX_TILE_HEIGHT      ((1<<16)-1)    /**< Max tile height*/
#define DMA_MAX_TILE_WIDTH       ((1<<16)-1)    /**< Max tile width (bytes) */
#define DMA_MAX_1D_SIZE          ((1<<22)-1)    /**< Max transfer size for 1D (bytes) */
#define DMA_MAX_INTERNAL_STRIDE  ((1<<16)-1)    /**< Max stride for internal memory (bytes) */
#define DMA_MAX_EXTERNAL_STRIDE  ((1<<16)-1)    /**< Max stride for external memory (bytes) */
#else // !CEVA_DMA_EXTENDED_DESC
#define DDMA_DESC_SIZE_BYTES 16
// DMA transfer limits
#define DMA_MAX_TILE_HEIGHT      ((1<<10)-1)    /**< Max tile height*/
#define DMA_MAX_TILE_WIDTH       ((1<<10)-1)    /**< Max tile width (bytes) */
#define DMA_MAX_1D_SIZE          ((1<<20)-1)    /**< Max transfer size for 1D (bytes) */
#define DMA_MAX_INTERNAL_STRIDE  ((1<<10)-1)    /**< Max stride for internal memory (bytes) */
#define DMA_MAX_EXTERNAL_STRIDE  ((1<<16)-1)    /**< Max stride for external memory (bytes) */
#endif // !CEVA_DMA_EXTENDED_DESC



#define dma_ext_enqueue_desc dma_enqueue_desc

#define dma_ext_enqueue_sync_point dma_enqueue_sync_point


CSL_CPP_START
    /**
    @addtogroup DMA_DRIVER QMAN/DDMA Driver
    @{
    @brief This module provides the API for working with the Data DMA (DDMA) engine through QMAN (Queue Manager) hardware.

    The DMA driver lets the developer create, enqueue, and track DMA requests.

    It contains the following functionality:
    - Allocate and delete a task queue in the Queue Manager hardware
    - Create descriptors for various DMA tasks
    - Update descriptors' parameters, such as tile width and height
    - Enqueue descriptors to the task queues
    - Track the completion of the tasks by polling and interrupt-based synchronization mechanisms
    @}
    */


/**
*   @addtogroup DMA_DRIVER_API QMAN/DDMA Driver API
*    @ingroup DMA_DRIVER
*   @{
*/

//**********************************************************
//********************* Structures *************************
//**********************************************************
// IDMA
typedef enum channel_unpack_e
{
	CHANNEL_UNPACK_ALL      = 0,
	CHANNEL_UNPACK_ONE      = 1,
	CHANNEL_UNPACK_TWO      = 2,
	CHANNEL_UNPACK_THREE    = 4,
	CHANNEL_UNPACK_FOUR     = 8
}channel_unpack_e;

typedef enum elements_number_e
{
	ELEMENTS_NUMBER_ONE     = 1,
	ELEMENTS_NUMBER_TWO     = 2,
	ELEMENTS_NUMBER_THREE   = 4,
	ELEMENTS_NUMBER_FOUR    = 8
}elements_number_e;

typedef enum element_size_e
{
	ELEMENT_SIZE_ONE_BYTE  = 1,
	ELEMENT_SIZE_TWO_BYTES  = 2,
	ELEMENT_SIZE_FOUR_BYTES = 4
}element_size_e;

typedef enum clip_enable_e
{
	CLIP_ENABLE_FALSE       = 0,
	CLIP_ENABLE_TRUE        = 1
}clip_enable_e;

typedef enum QX_counter_e
{
	QX_COUNTER_0            = 0,
	QX_COUNTER_1            = 1
}QX_counter_e;


#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR
#if (defined XM6 || defined VECC_XM6) && defined CEVA_DMA_EXTENDED_DESC
/** @brief IDMA task descriptor data structure (opaque) */
typedef union {
    uint8_t bytes[sizeof(T_QMAN_task_descriptor)];
    T_QMAN_task_descriptor task_descriptor;
} dma_idma_desc_t;

/* QMAN_VIRTUAL_DESCRIPTOR */
typedef union
{
	struct
	{
		uint32_t ISTART        :32;
		uint32_t               :16;
		uint32_t IHEIGHT       :16;
		uint32_t IWIDTH        :16;
		uint32_t ILINE_STRIDE  :16;
		uint32_t IPLANE_STRIDE :32;
		uint32_t PADVAL        :32;
		uint32_t ELEMENT_SZ    : 4;
		uint32_t NUM_CH        : 4;
		uint32_t CLIP_EN       : 1;
	};
	T_QMAN_virtual_descriptor virtual_descriptor;
}dma_image_desc_t;
#endif
#endif /* CSL_QMAN_VIRTUAL_DESCRIPTOR */




/** @brief DMA task direction enumeration */
typedef enum
{
	DMA_DIR_INTERNAL_EXTERNAL,                  /**< Internal to External transfer */
	DMA_DIR_EXTERNAL_INTERNAL,                  /**< External to Internal transfer */
	DMA_DIR_INTERNAL_INTERNAL                   /**< Internal to Internal transfer */
} dma_transfer_dir_e;

/** @brief DMA task internal memory access enumeration */
typedef enum
{
    DMA_TYPE_LINEAR = 0,                        /**< Linear Transfer */
    DMA_TYPE_RESERVED,                          /**< Reserved */
    DMA_TYPE_ONE_BANK_READ,                     /**< Source of transfer is from internal one bank */
    DMA_TYPE_TWO_BANK_READ,                     /**< Source of transfer is from internal two consecutive banks */
    DMA_TYPE_DUPLICATE_ONE_BANK_WRITE,          /**< Destination of transfer is to internal one bank and should be duplicate to all other banks */
    DMA_TYPE_DUPLICATE_TWO_BANK_WRITE,          /**< Destination of transfer is to internal two consecutive banks and should be duplicate to all other consecutive banks */
    DMA_TYPE_ONE_BANK_WRITE,                    /**< Destination of transfer is to internal one bank */
    DMA_TYPE_TWO_BANK_WRITE                     /**< Destination of transfer is to internal two consecutive banks*/
} dma_transfer_type_e;

#if defined SENSPRO || defined VECC_SENSPRO
/** @brief DMA simulator configuration*/
typedef enum {
	DMA_SIM_SP50 = 1,
	DMA_SIM_SP100,
	DMA_SIM_SP250,
	DMA_SIM_SP500,
	DMA_SIM_SP1000,
    DMA_SIM_SP500_V11
}dma_simulator_configuration_e;

/*  backwards compatibility with undefined SP version*/
#define DMA_SIM_SINGLE_VCU DMA_SIM_SP500
#define DMA_SIM_DUAL_VCU   DMA_SIM_SP1000
#endif



	/** @brief DMA Driver internal definitions */

	/** @brief DMA Descriptor structure*/
	#ifdef CEVA_DMA_EXTENDED_DESC
		typedef union
		{
				struct
				{
				uint32_t floc : 1;
				uint32_t pri_abs : 4;
				uint32_t pri_frame_no : 2;
				uint32_t pri_frame_order : 8;
				uint32_t tframe_len : 4;
				uint32_t qman_src_type : 2;
				uint32_t qman_dst_type : 2;
				uint32_t wd_wait : 1;
				uint32_t dup : 2;
				uint32_t ddie : 1;
				uint32_t tdt : 1;
		#if defined SENSPRO
				uint32_t ddma_task_id : 4;
		#else
				uint32_t reserved1 : 4;
		#endif
				union {
					struct {
                                uint32_t message : 32;
                                uint32_t dst_ptr : 32;
                                uint32_t dma_size : 22;
		#if defined SENSPRO
                                uint32_t ddma_task_id : 3;
		#else
                                uint32_t reserved1 : 3;
		#endif

                                uint32_t bsz : 4;
                                uint32_t reserved2 : 3;
                            } message;

					struct {
                                uint32_t src_ptr : 32;
                                uint32_t dst_ptr : 32;
                                uint32_t dma_size : 22;
		#if defined SENSPRO
                                uint32_t ddma_task_id : 3;
		#else
                                uint32_t reserved1 : 3;
		#endif
                                uint32_t bsz : 4;
                                uint32_t trtyp : 3;
                            } single_dimension;

					struct {
                                uint32_t src_ptr : 32;
                                uint32_t dst_ptr : 32;
                                uint32_t num_planes : 16;
                                uint32_t tile_width : 16;
                                union {
                                    struct {
                                                 int32_t  src_x : 16;
                                                 int32_t  src_y : 16;
                                                 uint32_t src_z : 16;
                                                 int32_t  dst_x : 16;
                                                 int32_t  dst_y : 16;
                                                 uint32_t dst_z : 16;
                                            } pixel;
                                    struct {
                                                uint32_t src_plane_stride : 32;
                                                uint32_t src_line_stride : 16;
                                                uint32_t dst_line_stride : 16;
                                                uint32_t dst_plane_stride : 32;
                                            } absolute;
                                        } stride;
                                uint32_t tile_height : 16;
                                uint32_t src_typ : 1;
                                uint32_t dst_typ : 1;
                                uint32_t bsz : 4;
                                uint32_t trtyp : 3;
                                uint32_t chn_unpack : 4;
		#if defined SENSPRO
                                uint32_t ddma_task_id : 3;
		#else
                                uint32_t reserved : 3;
		#endif

                            } multi_dimension;
				} u0;
			};

			T_QMAN_task_descriptor task_descriptor;

		} dma_desc_int_t;

	#else //!CEVA_DMA_EXTENDED_DESC
		typedef struct {
			uint32_t message : 32;
		#ifndef CEVA
			uint32_t int_ptr : 32;
		#else
			uint32_t int_ptr : 20;
			uint32_t reserved1 : 12;
		#endif
			uint32_t reserved2 : 6;
			uint32_t pri_abs : 4;
			uint32_t extw : 1;
			uint32_t ddie : 1;
			uint32_t bsz : 4;
			uint32_t reserved3 : 4;
			uint32_t reserved4 : 1;
			uint32_t floc : 1;
			uint32_t qman_int_type : 2;
			uint32_t pri_frame_order : 8;
			uint32_t pri_frame_no : 2;
			uint32_t qman_ext_type : 2;
			uint32_t tframe_len : 4;
			uint32_t reserved5 : 3;
			uint32_t tdt : 1;
			uint32_t reserved6 : 20;
		} dma_internal_message_desc_t;

		typedef struct {
			uint32_t ext_ptr : 32;

			uint32_t message : 32;

			uint32_t reserved1 : 5;
			uint32_t wd_wait : 1;
			uint32_t pri_abs : 4;
			uint32_t extw : 1;
			uint32_t ddie : 1;
			uint32_t bsz : 4;
			uint32_t reserved2 : 4;
			uint32_t reserved3 : 1;
			uint32_t floc : 1;
			uint32_t qman_int_type : 2;
			uint32_t pri_frame_order : 8;
			uint32_t pri_frame_no : 2;
			uint32_t qman_ext_type : 2;
			uint32_t tframe_len : 4;
			uint32_t reserved4 : 3;
			uint32_t tdt : 1;
			uint32_t reserved5 : 20;
		} dma_external_message_desc_t;

		typedef struct {
		#ifndef CEVA
			uint32_t ext_ptr : 32;
			uint32_t int_ptr : 32;
		#else
			uint32_t ext_ptr : 32;
			uint32_t int_ptr : 20;			// The following fields are not supported in MSVS simulation
			uint32_t reserved1 : 1;
			uint32_t wd_wait : 1;
			uint32_t pri_abs : 4;
			uint32_t extw : 1;
			uint32_t ddie : 1;
			uint32_t bsz : 4;
		#endif
			uint32_t dma_size : 20;
			uint32_t iit : 1;
			uint32_t floc : 1;
			uint32_t qman_int_type : 2;
			uint32_t pri_frame_order : 8;
			uint32_t pri_frame_no : 2;
			uint32_t qman_ext_type : 2;
		#ifndef CEVA
			uint32_t reserved1 : 1;
			uint32_t wd_wait : 1;
			uint32_t extw : 1;
			uint32_t ddie : 1;
		#else
			uint32_t tframe_len : 4;		//Removed field from MSVS simulation
		#endif
			uint32_t trtyp : 3;
			uint32_t tdt : 1;
			uint32_t reserved3 : 20;
		} dma_1d_desc_t;

		typedef struct {
		#ifndef CEVA
			uint32_t ext_ptr : 32;
			uint32_t int_ptr : 32;
		#else
			uint32_t ext_ptr : 32;
			uint32_t int_ptr : 20;
			uint32_t tframe_len : 4;		//Removed field from MSVS simulation
			uint32_t pri_frame_order : 8;	//Removed field from MSVS simulation
		#endif
			uint32_t tile_width : 10;
			uint32_t ddie : 1;
			uint32_t wd_wait : 1;
			uint32_t iit : 1;
			uint32_t reserved1 : 3;
			uint32_t tile_height : 10;
			uint32_t pri_abs : 4;
			uint32_t pri_frame_no : 2;
			uint32_t int_stride : 10;
			uint32_t floc : 1;
			uint32_t tdt : 1;
			uint32_t extw : 1;
			uint32_t trtyp : 3;
			uint32_t ext_stride : 16;
		} dma_2d_desc_t;

		typedef struct {
			uint32_t	dw0;
			uint32_t	dw1;
			uint32_t	dw2;
			uint32_t	dw3;
		} dma_dw_t;

		typedef struct {
			uint16_t	w0;
			uint16_t	w1;
			uint16_t	w2;
			uint16_t	w3;
			uint16_t	w4;
			uint16_t	w5;
			uint16_t	w6;
			uint16_t	w7;
		} dma_w_t;

		/** @brief DMA task descriptor structure */
		typedef union
		{
			dma_dw_t	raw_dw;
			dma_w_t		raw_w;
			dma_internal_message_desc_t internal_message;
			dma_external_message_desc_t external_message;
			dma_1d_desc_t dma_1d;
			dma_2d_desc_t dma_2d;
		} dma_desc_int_t;
	#endif // !CEVA_DMA_EXTENDED_DESC

	#define DESC_PTR_CAST(p)	((dma_desc_int_t*)(p))

	/** @brief Queue Depth register structure */
	typedef union
	{
		struct
		{
			uint32_t depth : 13;
			uint32_t r1 : 3;
			uint32_t pri_abs : 4;
			uint32_t pri_abs_sel : 1;
			uint32_t r2 : 9;
			uint32_t cont_frame : 1;
			uint32_t enable : 1;
		};
		T_Qx_EN_DEPTH qx_en_depth;
	} dma_queue_depth_register_t;

	/** @brief Queue Depth register union */
	typedef union
	{
		dma_queue_depth_register_t fields;
		uint32_t overlay;
	} dma_queue_depth_t;

	/** @brief Maximum queue depth */
	#define QUEUE_MAX_DEPTH		16383
    
    #if defined XM6 || defined VECC_XM6 || defined VECC_SENSPRO || defined SENSPRO
    #define MSS_BARRIER_REGISTER_ADDR		0x638
    #else /* !( XM6 || VECC_XM6 || VECC_SENSPRO || SENSPRO ) */
    #define MSS_BARRIER_ADDR				0x64C
    #endif /* ( XM6 || VECC_XM6 || VECC_SENSPRO || SENSPRO ) */

	// QMAN registers
	#ifdef CEVA_DMA_EXTENDED_DESC

	#define INTERNAL_QMAN_BASE_ADDR			0x1200
	#define QX_EN_DEPTH						(INTERNAL_QMAN_BASE_ADDR + 0x00)
	#define QX_FIRST_ADDR					(INTERNAL_QMAN_BASE_ADDR + 0x04)
	#define QX_BASE_PTR						(INTERNAL_QMAN_BASE_ADDR + 0x08)
	#define QX_CHNK_SIZE					(INTERNAL_QMAN_BASE_ADDR + 0x0C)
	#define QX_DSC_EN_INC0					(INTERNAL_QMAN_BASE_ADDR + 0x10)
	#define QX_STATUS						(INTERNAL_QMAN_BASE_ADDR + 0x14)
	#define QX_DSC_EN_INC1					(INTERNAL_QMAN_BASE_ADDR + 0x40)
	#define QX_EN_CNT                       (INTERNAL_QMAN_BASE_ADDR + 0x44)

	#define QMAN_X_OFFSET_SHIFT				0x07
	#define QMAN_DESC_INC_VALUE				0x00030001
	#define QMAN_DESC_CHK_SIZE				0x00100010
	#define QMAN_DESC_INIT_INC_VALUE		0x80000000U

	#define QMAN_IDM_CROS_ADDR				0x1180
	#define QMAN_PAUSE_ADDR                 0x11b0
	#define QMAN_BASE_ADDR					0x1184
	#define QMAN_ACTIVE_ADDR				(QMAN_BASE_ADDR + 0x00)
	#define QMAN_VI_MASK_ADDR				(QMAN_BASE_ADDR + 0x10)
	#define QMAN_IRQ_STATUS_ADDR			(QMAN_BASE_ADDR + 0x14)
	#define QMAN_RST_ADDR					(QMAN_BASE_ADDR + 0x18)
	#define QMAN_QFULL_ADDR					(QMAN_BASE_ADDR + 0x20)
	#define QMAN_QFULL_MASK_ADDR			(QMAN_BASE_ADDR + 0x20)
	
	#define MSS_BARRIER_REGISTER_VALUE		0x80

	#else // !CEVA_DMA_EXTENDED_DESC

	#define INTERNAL_QMAN_BASE_ADDR			0x1100
	#define QX_EN_DEPTH						(INTERNAL_QMAN_BASE_ADDR + 0x00)
	#define QX_FIRST_ADDR					(INTERNAL_QMAN_BASE_ADDR + 0x04)
	#define QX_BASE_PTR						(INTERNAL_QMAN_BASE_ADDR + 0x08)
	#define QX_CHNK_SIZE					(INTERNAL_QMAN_BASE_ADDR + 0x0C)
	#define QX_DSC_EN_INC0					(INTERNAL_QMAN_BASE_ADDR + 0x10)
	#define QX_STATUS						(INTERNAL_QMAN_BASE_ADDR + 0x14)
	#define QX_DSC_EN_INC1					(INTERNAL_QMAN_BASE_ADDR + 0x2C)
	#define QX_EN_CNT                       (INTERNAL_QMAN_BASE_ADDR + 0x30)

	#define QMAN_X_OFFSET_SHIFT				0x06
	#define QMAN_DESC_INC_VALUE				0x00010001
	#define QMAN_DESC_CHK_SIZE				0x00100010
	#define QMAN_DESC_INIT_INC_VALUE		0x80000000

	#define QMAN_BASE_ADDR					0x10dc
	#define QMAN_ACTIVE_ADDR				(QMAN_BASE_ADDR + 0x00)
	#define QMAN_VI_MASK_ADDR				(QMAN_BASE_ADDR + 0x10)
	#define QMAN_RQ_STATUS_ADDR				(QMAN_BASE_ADDR + 0x14)
	#define QMAN_RST_ADDR					(QMAN_BASE_ADDR + 0x18)

	#define MSS_BARRIER_VAL					0x80


	#define DMA_TYPE_MESSAGE 3
	#endif // !CEVA_DMA_EXTENDED_DESC




//**********************************************************
//************** Functions Decelerations *******************
//**********************************************************


    /** @brief Enqueues a new task to queue
    * @param[in]     queue - pointer to the queue
    * @param[in]     desc - pointer to the descriptor
    * @param[in]     src - source address
    * @param[in]     dst - destination address
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the operation completed successfully
    * @retval #DMA_STATUS_ENQUEUE_FAILED - failed to enqueue the task, because the queue is full
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue or desc or there was an error in parameters
    * dma_status_e dma_enqueue_desc(dma_queue_base_t* queue, dma_desc_t* desc, void* src, void* dst);
    *
    */
	dma_status_e dma_enqueue_desc(dma_queue_base_t* queue, dma_desc_t* desc, void* src, void* dst) PRAGMA_CSECT("CSL_CODE_SECTION");


	/**
	* @brief Allocates a new queue and initialize its hardware resources
	* @param[out]    out_queue - pointer to the queue base structure (must be allocated in internal memory and aligned to 32 bytes)
	* @param[in]     start_address - pointer to the queue's start address (must be allocated in internal memory and aligned to 32 bytes)
	* @param[in]     priority - the queue's priority
	* @param[in]     depth - the number of descriptors in the queue (between 2 and 16383). This value is rounded down to the nearest power of two value.
	* @return #dma_status_e status code
	* @retval #DMA_STATUS_OK - a queue allocated successfully
	* @retval #DMA_STATUS_ALLOC_FAILED - failed to allocate a queue: no available queue found
	* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer in out_queue or there was an error in parameters
	*/
#ifdef SENSPRO    
	#define dma_allocate_queue(_out_queue, _start_address, _priority, _depth) \
		((CSL_ALLOCATION_FAILURE == ((_out_queue)->id = CSL_GET_RESOURCE_NUM(QMAN_allocate_bc((T_QMAN_task_descriptor*)_start_address, _priority, _depth, QMAN_CONFIG_QX_AUTO_ENABLE_TASK_COUNTER)))) ? DMA_STATUS_ERROR_PARAMS : DMA_STATUS_OK)
#else /* !SENSPRO */
	#define dma_allocate_queue(_out_queue, _start_address, _priority, _depth) \
		((CSL_ALLOCATION_FAILURE == ((_out_queue)->id = CSL_GET_RESOURCE_NUM(QMAN_allocate_bc((T_QMAN_task_descriptor*)_start_address, _priority, _depth)))) ? DMA_STATUS_ERROR_PARAMS : DMA_STATUS_OK)
#endif         

    /**
    * @brief Deletes the queue and free its hardware resources
    * @param[in]     queue - pointer to the queue base structure
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the queue was deleted successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer
    */
	#define dma_delete_queue(_queue) \
		((CSL_SUCCESS == QMAN_deallocate_bc((_queue)->id))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)

    /**
    * @brief Creates an internal message transfer task descriptor
    * @param[out]     desc - pointer to the descriptor to initialize
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the task descriptor was initialized successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer
    */
#define dma_create_internal_message_desc(_desc) \
		QMAN_create_internal_message_task_bc(&((_desc)->task_descriptor))

    /**
    * @brief Create an external message transfer task descriptor
    * @param[out]     desc - pointer to the descriptor to initialize
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the task descriptor was initialized successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer
    */
#define dma_create_external_message_desc(_desc) \
	QMAN_create_external_message_task_bc(&((_desc)->task_descriptor))



    /**
    * @brief Creates a one-dimensional transfer task descriptor
    * @param[out]    desc - pointer to the descriptor to initialize
    * @param[in]     length - number of bytes to copy
    * @param[in]     dir - direction of the transfer
    * @param[in]     tr_type - internal memory access type
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the task descriptor was initialized successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
    */
#define dma_create_1d_desc(_desc, _length, _dir, _tr_type)  \
		QMAN_create_linear_task_bc((&((_desc)->task_descriptor)), _length, ((E_QMAN_task_descriptor_dup)_dir), (E_QMAN_task_descriptor_trtyp)_tr_type)


    /**
    * @brief Creates a two-dimensional transfer task descriptor
    * @param[out]    desc - pointer to the descriptor to initialize
    * @param[in]     width - number of bytes in a row to copy
    * @param[in]     height - number of rows to copy
    * @param[in]     src_stride - source stride in bytes
    * @param[in]     dst_stride - destination stride in bytes
    * @param[in]     dir - direction of the transfer
    * @param[in]     tr_type - internal memory access type
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the task descriptor was initialized successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
    */
#define dma_create_2d_desc(_desc, _width, _height, _src_stride, _dst_stride, _dir, _tr_type) \
	QMAN_create_multi_di_task_bc((&((_desc)->task_descriptor)), _width, _height, 1, _src_stride, _dst_stride, (_height*_src_stride),  (_height*_dst_stride), ((E_QMAN_task_descriptor_dup)_dir), (E_QMAN_task_descriptor_trtyp)_tr_type)






    /**
    * @brief Updates the stride parameters in a two-dimensional transfer task descriptor
    * @param[in,out] desc - pointer to the descriptor to update
    * @param[in]     src_stride - source stride in bytes
    * @param[in]     dst_stride - destination stride in bytes
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the task descriptor was updated successfully
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
    */
#define dma_update_2d_desc_stride(_desc, _src_stride, _dst_stride) \
	((CSL_SUCCESS == QMAN_update_multi_di_stride(&((_desc)->task_descriptor), _src_stride, ((_desc)->task_descriptor.multi_dimensional.tile_height)*_src_stride, _dst_stride, ((_desc)->task_descriptor.multi_dimensional.tile_height)*_dst_stride))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)



#ifndef XM4
		/**
		* @brief Creates a three-dimensional transfer task descriptor
		* @param[out]    desc - pointer to the descriptor to initialize
		* @param[in]     width - number of bytes in a row to copy
		* @param[in]     height - number of rows to copy
		* @param[in]     num_planes - number of planes
		* @param[in]     src_stride - source line stride in bytes
		* @param[in]     dst_stride - destination line stride in bytes
		* @param[in]     src_plane_stride - source plane stride in bytes
		* @param[in]     dst_plane_stride - destination plane stride in bytes
		* @param[in]     dir - direction of the transfer
		* @param[in]     tr_type - internal memory access type
		* @return #dma_status_e status code
		* @retval #DMA_STATUS_OK - the task descriptor was initialized successfully
		* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
		*/

	#define dma_create_3d_desc(_desc, _width, _height, _num_planes, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride, _dir, _tr_type) \
		QMAN_create_multi_di_task_bc((&((_desc)->task_descriptor)),  _width, _height, _num_planes, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride, ((E_QMAN_task_descriptor_dup)_dir), (E_QMAN_task_descriptor_trtyp)_tr_type)



		/**
		* @brief Updates the stride parameters in a three-dimensional transfer task descriptor
		* @param[in,out] desc - pointer to the descriptor to update
		* @param[in]     src_stride - source line stride in bytes
		* @param[in]     dst_stride - destination line stride in bytes
		* @param[in]     src_plane_stride - source plane stride in bytes
		* @param[in]     dst_plane_stride - destination plane stride in bytes
		* @return #dma_status_e status code
		* @retval #DMA_STATUS_OK - the task descriptor was updated successfully
		* @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer or there was an error in parameters
		*/
	#define dma_update_3d_desc_stride(_desc, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride) \
		((CSL_SUCCESS == QMAN_update_multi_di_stride(&((_desc)->task_descriptor), _src_stride, _src_plane_stride, _dst_stride, _dst_plane_stride))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)




#endif /* !XM4 */






    /**
    * dma_status_e dma_enqueue_sync_point(dma_queue_base_t* queue, uint32_t* value);
    * @brief Enqueues a new sync point
    * @param[in]     queue - pointer to the queue base structure
    * @param[out]    value - pointer to the new sync point value, which can be used with #dma_wait_sync_point
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - enqueue operation completed successfully
    * @retval #DMA_STATUS_ENQUEUE_FAILED - failed to enqueue the sync point, because the queue is full
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue or value or there was an error in parameters
    */
    dma_status_e dma_enqueue_sync_point(dma_queue_base_t* queue, uint32_t* value) PRAGMA_CSECT("CSL_CODE_SECTION");



    /**
    * @brief Resets the sync point value and counter to 0
    * @param[in]     queue - pointer to the queue base structure
    * @retval #DMA_STATUS_OK - no error
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue
    */
#define dma_reset_sync_point(_queue) \
		((CSL_SUCCESS == QMAN_reset_sync_point((_queue)->id))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)






    /**
    * @brief Deinitializes the Queue Manager driver
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - no error
    * @retval #DMA_STATUS_MANAGER_FAILURE - Queue Manager driver deinitialization failed
    */
	#define dma_deinit_manager()\
        ((CSL_SUCCESS == CSL_stop()) ? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)

    /**
    * @brief Enables the queue
    * @param[in,out]     queue - pointer to the queue base structure
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - no error
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue
    */
	#define dma_enable_queue(_queue)\
			((CSL_SUCCESS == QMAN_enable((_queue)->id))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)


    /**
    * @brief Disables the queue
    * @param[in,out]     queue - pointer to the queue base structure
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - no error
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue
    */
	#define dma_disable_queue(_queue)\
			((CSL_SUCCESS == QMAN_disable((_queue)->id))? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS)





    /** @brief Enqueues a new task to the queue with the synchronization message to be read by the DDMA interrupt handler
    * @param[in]     queue - pointer to the queue base structure
    * @param[in]     desc - pointer to the task descriptor
    * @param[in]     src - source address
    * @param[in]     dst - destination address
    * @param[in]     message - synchronization message for the interrupt handler
    * @return #dma_status_e status code
    * @retval #DMA_STATUS_OK - the operation completed successfully
    * @retval #DMA_STATUS_ENQUEUE_FAILED - failed to enqueue the task, because the queue is full
    * @retval #DMA_STATUS_ERROR_PARAMS - if passed the NULL pointer to queue or desc or there was an error in the parameters
    * @note  Sync FIFO mechanism relies on 32-bit addresses and cannot be simulated on Win64
    */
#define dma_enqueue_desc_with_sync(_queue, _desc, _src, _dst, _message) \
		QMAN_enable_task_with_sync((T_QMAN_task_descriptor *)_queue, _desc, _src, _dst, _message)


    /** @brief Retrieves the next synchronization message
    *
    *  This function is intended to be invoked by the DDMA interrupt handler
    *  @param[out] p_message - pointer to the location for storing the synchronization message
    *  @retval non-zero if there is a synchronization message. When zero is returned, the value written to p_message should be ignored.
    */
#define  dma_get_sync_message(_p_message) \
		QMAN_get_sync_messge(_p_message)


#ifndef XM4
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Descriptors creation functions
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/***********************************************************
	 * dma_create_image
	 *
	 * Written by: ER 20/7/2020
	 * Description: Creates an image descriptor.
	 *
	 * Input:
	 * 		1.  Image descriptor (to be constructed).
	 *      2.  Pointer to an image start address (first plane).
	 *      3.  Height of image (in number of lines):
	 *              a. Used only if: is_clip_enabled == true.
	 *      4.  Width of image (number of pixels in each plane).
	 *              a. Used only if: is_clip_enabled == true.
	 *      5.  Plane line stride (in bytes):
	 *              a. Must be aligned to element_size.
	 *      6.  Plane stride (in bytes):
	 *              a. Must be aligned to element_size.
	 *      7.  Padding value (in bytes):
	 *              a. Used only if: is_clip_enabled == true.
	 *              b. Actual value is in accordance to element_size.
	 *      8.  Pixel size (see element_size_e)
	 *      9.  Number of pixel channels (see elements_number_e)
	 *      10. Clipping value enable (see clip_enable_e)
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_create_image( _idma , _i_start, _i_height, _i_width, _i_line_stride, _i_plane_stride  , _pad_val , _element_size, _num_channels , _is_clip_enabled ) \
		QMAN_create_image_bc((&((_idma)->virtual_descriptor)), _i_start, _i_height, _i_width, _i_line_stride, _i_plane_stride, _pad_val, (E_qman_virtual_element_sz)_element_size, (E_qman_virtual_num_ch)_num_channels, (E_qman_virtual_clip_en)_is_clip_enabled)


	/***********************************************************
	 * dma_create_idma_desc
	 *
	 * Written by: ER 20/7/2020
	 * Description: Creates an IDMA descriptor.
	 *
	 * Input:
	 * 		1.  IDMA descriptor (to be constructed).
	 *      2.  Source image descriptor.
	 *      3.  Destination image descriptor.
	 *      4.  Width of a sub image (number of pixels).
	 *      5.  Height of a sub image (number of lines).
	 *      6.  Number of planes.
	 *      7.  Number of channel elements to be unpacked (see channel_unpack_e).
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_create_idma_desc(_desc, _src, _dst, _tile_width, _tile_height, _num_planes, _unpack) \
		QMAN_create_image_task_bc((&((_desc)->task_descriptor)), (T_QMAN_virtual_descriptor *)_src, (T_QMAN_virtual_descriptor *)_dst, _tile_width, _tile_height, _num_planes, (E_qman_task_chn_unpack)_unpack)

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// En-queueing IDMA descriptors
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/***********************************************************
	 * dma_enqueue_idma_desc
	 *
	 * Written by: ER 20/7/2020
	 * Description: En-queue IDMA descriptor
	 *
	 * Input:
	 * 		1.  Queue to be used.
	 *      2.  IDMA descriptor to be executed.
	 *      3.  Source sub image X offset from i_start (in pixels)
	 *      4.  Source sub image Y offset from i_start (in number of lines)
	 *      5.  Source sub image Z offset from i_start (in number of planes)
	 *      6.  Destination sub image X offset from i_start (in pixels)
	 *      7.  Destination sub image Y offset from i_start (in number of lines)
	 *      8.  Destination sub image Z offset from i_start (in number of planes)
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_enqueue_idma_desc(_queue, _desc, _src_x, _src_y, _src_z, _dst_x, _dst_y, _dst_z) \
		((CSL_SUCCESS ==  QMAN_enqueue_image_task((_queue)->id, ((T_QMAN_task_descriptor *)_desc), _src_x, _src_y, _src_z, _dst_x, _dst_y, _dst_z)? DMA_STATUS_OK : DMA_STATUS_ENQUEUE_FAILED))




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Updating IDMA descriptors
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/***********************************************************
	 * dma_update_idma_desc_src
	 *
	 * Written by: ER 20/7/2020
	 * Description: Update the IDMA descriptor according to the source image descriptor.
	 *
	 * Input:
	 * 		1.  IDMA descriptor (to be updated).
	 *      2.  Source image descriptor.
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_update_idma_desc_src(_idma, _src_image) \
	(  ( CSL_SUCCESS == QMAN_update_image_source( &((_idma)->_task_descriptor), ((uint32_t)_src_image)) )? DMA_STATUS_OK : DMA_STATUS_ENQUEUE_FAILED  )

	/***********************************************************
	 * dma_update_idma_desc_dst
	 *
	 * Written by: ER 20/7/2020
	 * Description: Update the IDMA descriptor according to the destination image descriptor.
	 *
	 * Input:
	 * 		1.  IDMA descriptor (to be updated).
	 *      2.  Destination image descriptor.
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_update_idma_desc_dst(_idma, _dst_image) \
		(  ( CSL_SUCCESS == QMAN_update_image_destination( &((_idma)->_task_descriptor), ((uint32_t)_dst_image)) )? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS  )


	/***********************************************************
	 * dma_update_idma_desc_tile_size
	 *
	 * Written by: ER 20/7/2020
	 * Description: Update the IDMA descriptor with an updated tile width and height
	 *
	 * Input:
	 * 		1.  IDMA descriptor (to be updated).
	 *      2.  Width of a sub image (number of pixels).
	 *      3.  Height of a sub image (number of lines).
	 * 	Output:
	 * 		DMA status code (see DMA_driver.h for more details).
	 ***********************************************************/
	#define dma_update_idma_desc_tile_size(_idma, _tile_width, _tile_height) \
		(  ( CSL_SUCCESS == QMAN_update_image_tile_size( &((_idma)->_task_descriptor),_tile_width , _tile_height) )? DMA_STATUS_OK : DMA_STATUS_ERROR_PARAMS  )





#endif /* !XM4 */


CSL_CPP_END


#endif // #ifdef CSL_QMAN_SUPPORTED
#endif //__DMA_DRIVER_H__
