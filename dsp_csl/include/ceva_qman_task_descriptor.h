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
#ifndef CEVA_QMAN_TASK_DESCRIPTOR_H_
#define CEVA_QMAN_TASK_DESCRIPTOR_H_
#include "ceva_hw_conf.h"
#ifdef CSL_QMAN_SUPPORTED
/*********************************************************************************************
* @module	QMAN
* @file		ceva_qman_ctrl.h
* @author	Anat Keidar
* @date		28/02/2021
* @brief	Define the configuration registers, values and functions of the Queue-Descriptor programming model
**********************************************************************************************/
#include "ceva_assert.h"
#include <string.h>

CSL_CPP_START



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Task Descriptor Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/






#if ( ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) ) || defined(CEVABX) )


	/*************************
	 * @struct		T_QPUSH_DSC_EXT_PTR
	 * @register	QPUSH_DSC_EXT_PTR 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t ext_message	        : 32;
		} message_download;	
		struct 
		{
			uint32_t ext_ptr	      		: 32;
		} message_upload;	
		struct 
		{
			uint32_t ext_ptr	          	: 32;
		} linear;	
		#ifdef XM4
			struct 
			{
				uint32_t ext_ptr	       : 32;
			} multi_dimensional;		
		#endif
		
		uint32_t value;
		
	} T_QPUSH_DSC_EXT_PTR;



	/*************************
	 * @struct		T_QPUSH_DSC_INT_PTR
	 * @register	QPUSH_DSC_INT_PTR 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t int_ptr	        	: 20;
			uint32_t						: 12;
		} message_download;	
		struct 
		{
			uint32_t message	      		: 32;
		} message_upload;	
		struct 
		{
			uint32_t int_ptr	          	: 20;
			uint32_t                        :  1;
			uint32_t wd_wait        		:  1;
			uint32_t pri_abs        		:  4;
			uint32_t extw           		:  1;
			uint32_t ddie           		:  1;
			uint32_t bsz            		:  4;
		} linear;	
		#ifdef XM4
			struct 
			{
				uint32_t int_ptr	        : 20;
				uint32_t tframe_len     	:  4;
				uint32_t pri_frame_order	:  8;
			} multi_dimensional;		
		#endif
		
		uint32_t value;
		
	} T_QPUSH_DSC_INT_PTR;


	/*************************
	 * @struct		T_QPUSH_DSC_TCTL
	 * @register	QPUSH_DSC_TCTL 
	 *************************/
	typedef union
	{
			struct 
			{
				uint32_t 			                : 6;
				uint32_t pri_abs	             	: 4;
				uint32_t extw     	         		: 1;
				uint32_t ddie     	         		: 1;
				uint32_t bsz     	         		: 4;
				uint32_t 			                : 5;
				uint32_t floc     	         		: 1;
				uint32_t int_type        			: 2;
				uint32_t pri_frame_order 			: 8;
			} message_download;	
			struct 
			{
				uint32_t 			                : 5;
				uint32_t wd_wait	             	: 1;
				uint32_t pri_abs    	         	: 4;
				uint32_t extw     	         		: 1;
				uint32_t ddie     	         		: 1;
				uint32_t bsz     	         		: 4;
				uint32_t 			                : 5;
				uint32_t floc     	         		: 1;
				uint32_t int_type        			: 2;
				uint32_t pri_frame_order 			: 8;
			} message_upload;	
			struct 
			{
				uint32_t dma_size             		: 20;
				uint32_t iit 	             		:  1;
				uint32_t floc    	         		:  1;
				uint32_t qman_int_type        		:  2;
				uint32_t pri_frame_order 			:  8;
			} linear;	
		#ifdef XM4
			struct 
			{
				uint32_t tile_width           		: 10;
				uint32_t ddie     	         		:  1;
				uint32_t wd_wait	             	:  1;
				uint32_t iit                  		:  1;
				uint32_t                           	:  3;
				uint32_t tile_height          		: 10;
				uint32_t pri_abs              		:  4;
				uint32_t pri_frame_no         		:  2;
			} multi_dimensional;    		
		#endif
					
		uint32_t value;
		
	} T_QPUSH_DSC_TCTL;


	/*************************
	 * @struct		T_QPUSH_TFRAME_LEN
	 * @register	QPUSH_TFRAME_LEN 
	 *************************/
	typedef union
	{
		#ifdef CEVABX
			struct 
			{
				uint32_t pri_frame_no	     			 :  2;
				uint32_t qman_ext_type	     			 :  2;
				uint32_t tframe_len	     				 :  4;
				uint32_t 	                             : 24;
			} fileds;		
		#else /* !CEVABX */
			struct 
			{
				uint32_t pri_frame_no	     			 : 2;
				uint32_t qman_ext_type	     			 : 2;
				uint32_t tframe_len	     				 : 4;
				uint32_t 	                             : 24;
			} message;	
			struct 
			{
				uint32_t pri_frame_no	     			: 2;
				uint32_t qman_ext_type	     			: 2;
				uint32_t tframe_len	     				: 4;
				uint32_t 	                            : 3;
				uint32_t tdt	             			: 1;
				uint32_t 	                            : 20;
			} linear;	
			struct 
			{
				uint32_t int_stride	     				: 10;
				uint32_t floc	             			: 1;
				uint32_t tdt	             			: 1;
				uint32_t extw               			: 1;
				uint32_t trtyp	             			: 3;
				uint32_t stride             			: 16;
			} multi_dimensional;
		#endif /* CEVABX */
		
		uint32_t value;
	} T_QPUSH_TFRAME_LEN;




	/*************************
	 * @config_group	T_QMAN_task_descriptor
	 * @brief:
	 * 		Task descriptor types:
	 *		- download_message 
	 *		- upload_message 
	 *		- linear 
	 *		- multi_dimensional (Not supported on BX)
	 * 		Registers: 
	 *			- QPUSH_DSC_EXT_PTR 
	 *			- QPUSH_DSC_INT_PTR 
	 *			- QPUSH_DSC_TCTL 
	 *			- QPUSH_TFRAME_LEN 
	 *************************/
	typedef union
	{
		struct 
		{
			// QPUSH_DSC_EXT_PTR
			uint32_t message         : 32;
			// QPUSH_DSC_INT_PTR
	#ifdef CEVA        
			uint32_t int_ptr         : 20;
			uint32_t                 : 12;
	#else /* !CEVA */
			uint32_t int_ptr         : 32;
	#endif /* CEVA */        
			// QPUSH_DSC_TCTL
			uint32_t                 : 6;
			uint32_t pri_abs         : 4;
			uint32_t extw            : 1;
			uint32_t ddie            : 1;
	#ifdef CEVABX
			uint32_t 	             : 4;
	#else /* !CEVABX */
			uint32_t bsz             : 4;
	#endif /* CEVABX */
			uint32_t                 : 4;
			uint32_t                 : 1;
			uint32_t floc            : 1;
			uint32_t qman_int_type   : 2;
			uint32_t pri_frame_order : 8;
			// QPUSH_DSC_TFRAME_LEN
			uint32_t pri_frame_no    : 2;
			uint32_t qman_ext_type   : 2;
			uint32_t tframe_len      : 4;
	#ifdef CEVABX        
			uint32_t                 : 4;
	#else /* CEVABX */
			uint32_t                 : 3;
			uint32_t tdt             : 1;
	#endif /* !CEVABX */        
			uint32_t                 : 20;
		} download_message;
		struct 
		{
			// QPUSH_DSC_EXT_PTR
			uint32_t ext_ptr         : 32;
			// QPUSH_DSC_INT_PTR
			uint32_t message         : 32;
			// QPUSH_DSC_TCTL
			uint32_t                 : 5;
			uint32_t wd_wait         : 1;
			uint32_t pri_abs         : 4;
			uint32_t extw            : 1;
			uint32_t ddie            : 1;
	#ifdef CEVABX
			uint32_t 	             : 4;
	#else // #ifndef CEVABX
			uint32_t bsz             : 4;
	#endif // #ifndef CEVABX
			uint32_t                 : 4;
			uint32_t                 : 1;
			uint32_t floc            : 1;
			uint32_t qman_int_type   : 2;
			uint32_t pri_frame_order : 8;
			// QPUSH_TFRAME_LEN
			uint32_t pri_frame_no    : 2;
			uint32_t qman_ext_type   : 2;
			uint32_t tframe_len      : 4;
	#ifdef CEVABX        
			uint32_t                 : 4;
	#else /* CEVABX */
			uint32_t                 : 3;        
			uint32_t tdt             : 1;
	#endif /* !CEVABX */     
			uint32_t                 : 20;
		} upload_message;
		struct 
		{
			// QPUSH_DSC_EXT_PTR
			uint32_t ext_ptr         : 32;
			// QPUSH_DSC_INT_PTR
	#ifdef CEVA        
			uint32_t int_ptr         : 20;			
			uint32_t                 : 1;	 
			uint32_t wd_wait         : 1;		
			uint32_t pri_abs         : 4;			
			uint32_t extw            : 1;
			uint32_t ddie            : 1;
			uint32_t bsz             : 4;
	#else /* !CEVA */
			uint32_t int_ptr         : 32;
	#endif /* CEVA */          	
			// QPUSH_DSC_TCTL
			uint32_t dma_size        : 20;
			uint32_t iit             : 1;
			uint32_t floc            : 1;
			uint32_t qman_int_type   : 2;
			uint32_t pri_frame_order : 8;
			// QPUSH_TFRAME_LEN
			uint32_t pri_frame_no    : 2;
			uint32_t qman_ext_type   : 2;
	#ifndef CEVA
			uint32_t reserved1 : 1;
			uint32_t wd_wait : 1;
			uint32_t extw : 1;
			uint32_t ddie : 1;
	#else /* CEVA */
			uint32_t tframe_len : 4;		//Removed field from MSVS simulation
	#endif /* !CEVA */
	#ifdef CEVABX
			uint32_t dup             : 3; 	//  CSL driver field over reserved fields
			uint32_t trtyp           : 1;	//	CSL driver field over reserved fields
	#else /* CEVABX */
			uint32_t trtyp           : 3;        
			uint32_t tdt             : 1;
	#endif /* !CEVABX */             
			uint32_t                 : 20;
		} linear;
	#if ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) )
		struct 
		{
			// QPUSH_DSC_EXT_PTR
			uint32_t ext_ptr         : 32;
			// QPUSH_DSC_INT_PTR
	#ifdef CEVA        
			uint32_t int_ptr         : 20;
			uint32_t tframe_len      : 4;
			uint32_t pri_frame_order : 8;
	#else /* !CEVA */
			uint32_t int_ptr         : 32;
	#endif /* CEVA */         
			uint32_t tile_width      : 10;
			uint32_t ddie            : 1;
			uint32_t wd_wait         : 1;
			uint32_t iit             : 1;
			uint32_t                 : 3;
			uint32_t tile_height     : 10;
			// QPUSH_DSC_TCTL
			uint32_t pri_abs         : 4;
			uint32_t pri_frame_no    : 2;
			uint32_t int_stride      : 10;
			uint32_t floc            : 1;
			uint32_t tdt             : 1;
			uint32_t extw            : 1;
			uint32_t trtyp           : 3;
			uint32_t ext_stride      : 16;
		} multi_dimensional;
	#endif /* ( defined(XM4) && CEVA_DSP_RTL < 120 ) */
		struct
		{
			uint32_t 		        qpush_dsc_ext_ptr;
			T_QPUSH_DSC_INT_PTR 	qpush_dsc_int_ptr;
			T_QPUSH_DSC_TCTL 		qpush_dsc_tctl;
			T_QPUSH_TFRAME_LEN 		qpush_dsc_tframe_len;
		} registers;
	} T_QMAN_task_descriptor;    



#endif /* ( ( defined(XM4) && CEVA_DSP_RTL < 120 ) || defined(CEVABX) ) */




	/*************************
	 * @struct		T_QPUSH_NUM
	 * @register	QPUSH_NUM
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t qpush_num			: 5;
			uint32_t					: 1;
			#ifdef CEVABX
			uint32_t 					: 1;
			#else /* !CEVABX */
			uint32_t qpush_auto_inc		: 1;
			#endif /* CEVABX */
			uint32_t 			 		: 9;
			uint32_t qpush_status_rls	: 1;
			uint32_t qpush_status		: 1;
			uint32_t					: 14;
		} fields;
		uint32_t value;
	} T_QPUSH_NUM;





#if ( ( defined(XM4) && (CEVA_DSP_RTL >= 120) ) || defined(XM6) || defined(SENSPRO) )


	/*************************
	 * @struct		T_QPUSH_DSC_CFG
	 * @register	QPUSH_DSC_CFG 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t floc			:  1;
			uint32_t pri_abs		:  4;
			uint32_t pri_frame_no	:  2;
			uint32_t pri_frame_order:  8;
			uint32_t tframe_len		:  4;
			uint32_t qman_src_type	:  2;
			uint32_t qman_dst_type	:  2;
			uint32_t wd_wait		:  1;
			uint32_t dup			:  2;
			uint32_t ddie			:  1;
			uint32_t tdt			:  1;
        #ifdef SENSPRO    
			uint32_t ddma_task_id_lsb	:  4;
        #else /* !SENSPRO */
            uint32_t 	                :  4;
        #endif /* SENSPRO */        
		} fields;
		uint32_t value;
	} T_QPUSH_DSC_CFG;


	/*************************
	 * @struct		T_QPUSH_DSC_SRCP
	 * @register	QPUSH_DSC_SRCP 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t qpush_dsc_src	: 32;
		} fields;
		uint32_t value;
	} T_QPUSH_DSC_SRCP;


	/*************************
	 * @struct		T_QPUSH_DSC_DSTP
	 * @register	QPUSH_DSC_DSTP 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t qpush_dsc_dst	: 32;
		} field;	
		uint32_t value;
	} T_QPUSH_DSC_DSTP;


	/*************************
	 * @struct		T_QPUSH_DSC_DMASZ
	 * @register	QPUSH_DSC_DMASZ 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t dma_size			: 22;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
			uint32_t bsz				:  4;
			uint32_t trtyp				:  3;
		} tdt0;
		struct 
		{
			uint32_t num_planes		: 16;
			uint32_t tile_width		: 16;
		} tdt1;	
		uint32_t value;
	} T_QPUSH_DSC_DMASZ;


	/*************************
	 * @struct		T_QPUSH_DSC_SRC
	 * @register	QPUSH_DSC_SRC 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t src_plane_stride	: 32;
		} fields;
		uint32_t value;
	} T_QPUSH_DSC_SRC;


	/*************************
	 * @struct		T_QPUSH_DSC_LINE
	 * @register	QPUSH_DSC_LINE 
	 *************************/
	typedef union
	{
		struct
		{
			uint32_t src_line_stride	: 16;
			uint32_t dst_line_stride	: 16;
		} multi_dimensional;
	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR
		struct
		{
			uint32_t src_z 				: 16;
			uint32_t dst_x 				: 16;
		} image;
	#endif /* CSL_QMAN_VIRTUAL_DESCRIPTOR */
		uint32_t value;
	} T_QPUSH_DSC_LINE;


	/*************************
	 * @struct		T_QPUSH_DSC_DST
	 * @register	QPUSH_DSC_DST 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t dst_plane_stride	: 32;
		} multi_dimensional;
	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR
		struct
		{
			uint32_t dst_y 				: 16;
			uint32_t dst_z 				: 16;
		} image;
	#endif /* CSL_QMAN_VIRTUAL_DESCRIPTOR */
		uint32_t value;
	} T_QPUSH_DSC_DST;


	/*************************
	 * @struct		T_QPUSH_DSC_HGHT
	 * @register	QPUSH_DSC_HGHT 
	 *************************/
	typedef union
	{
		struct 
		{
			uint32_t tile_height		: 16;
			uint32_t src_typ			:  1;
			uint32_t dst_typ			:  1;
			uint32_t bsz				:  4;
			uint32_t trtyp				:  3;
			uint32_t 					:  4; // Reserved
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
		} multi_dimensional;
	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR
		struct
		{
			uint32_t tile_height		: 16;
			uint32_t src_typ			:  1;
			uint32_t dst_typ			:  1;
			uint32_t bsz				:  4;
			uint32_t trtyp				:  3;
			uint32_t chn_unpack			:  4;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
		} image;
	#endif /* CSL_QMAN_VIRTUAL_DESCRIPTOR */
		uint32_t value;
	} T_QPUSH_DSC_HGHT;
    

	/*************************
	 * @config_group	T_QMAN_task_descriptor
	 * @brief:
	 * 		Task descriptor types:
	 *		- message 
	 *		- linear 
	 *		- multi_dimensional
	 *		- image
	 * 		Registers: 
	 *			- QPUSH_DSC_CFG 
	 *			- QPUSH_DSC_SRCP 
	 *			- QPUSH_DSC_DSTP 
	 *			- QPUSH_DSC_DMASZ 
	 *			- QPUSH_DSC_SRC 
	 *			- QPUSH_DSC_LINE 
	 *			- QPUSH_DSC_DST 
	 *			- QPUSH_DSC_HGHT
	 *************************/
	typedef union
	{
		struct
		{
			// QPUSH_DSC_CFG
			uint32_t floc			:  1;
			uint32_t pri_abs		:  4;
			uint32_t pri_frame_no	:  2;
			uint32_t pri_frame_order:  8;
			uint32_t tframe_len		:  4;
			uint32_t qman_src_type	:  2;
			uint32_t qman_dst_type	:  2;
			uint32_t wd_wait		:  1;
			uint32_t dup			:  2;
			uint32_t ddie			:  1;
			uint32_t tdt			:  1;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_lsb	:  4;
        #else /* !SENSPRO */
            uint32_t 	                :  4;
        #endif /* SENSPRO */ 
			// QPUSH_DSC_SRCP
			uint32_t message		: 32;
			// QPUSH_DSC_DSTP
			uint32_t dst_ptr		: 32;
			// QPUSH_DSC_DMASZ
			uint32_t dma_size		: 22;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
			uint32_t bsz			:  4;
			uint32_t 				:  3; // Reserved
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved          
		} message;
		struct
		{
			// QPUSH_DSC_CFG
			uint32_t floc			:  1;
			uint32_t pri_abs		:  4;
			uint32_t pri_frame_no	:  2;
			uint32_t pri_frame_order:  8;
			uint32_t tframe_len		:  4;
			uint32_t qman_src_type	:  2;
			uint32_t qman_dst_type	:  2;
			uint32_t wd_wait		:  1;
			uint32_t dup			:  2;
			uint32_t ddie			:  1;
			uint32_t tdt			:  1;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_lsb	:  4;
        #else /* !SENSPRO */
            uint32_t 	                :  4;
        #endif /* SENSPRO */ 
			// QPUSH_DSC_SRCP
			uint32_t src_ptr		: 32;
			// QPUSH_DSC_DSTP
			uint32_t dst_ptr		: 32;
			// QPUSH_DSC_DMASZ
			uint32_t dma_size		: 22;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
			uint32_t bsz			:  4;
			uint32_t trtyp			:  3;
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved
			uint32_t 				: 32; // Reserved
		} linear;
		struct
		{
			// QPUSH_DSC_CFG
			uint32_t floc				:  1;
			uint32_t pri_abs			:  4;
			uint32_t pri_frame_no		:  2;
			uint32_t pri_frame_order	:  8;
			uint32_t tframe_len			:  4;
			uint32_t qman_src_type		:  2;
			uint32_t qman_dst_type		:  2;
			uint32_t wd_wait			:  1;
			uint32_t dup				:  2;
			uint32_t ddie				:  1;
			uint32_t tdt				:  1;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_lsb	:  4;
        #else /* !SENSPRO */
            uint32_t 	                :  4;
        #endif /* SENSPRO */ 
			// QPUSH_DSC_SRCP
			uint32_t src_ptr			: 32;
			// QPUSH_DSC_DSTP
			uint32_t dst_ptr			: 32;
			// QPUSH_DSC_DMASZ
			uint32_t num_planes			: 16;
			uint32_t tile_width			: 16;
			// QPUSH_DSC_SRC
			uint32_t src_plane_stride	: 32;
			// QPUSH_DSC_LINE
			uint32_t src_line_stride	: 16;
			uint32_t dst_line_stride	: 16;
			// QPUSH_DSC_DST
			uint32_t dst_plane_stride	: 32;
			// QPUSH_DSC_HGHT
			uint32_t tile_height		: 16;
			uint32_t 					:  2;
			uint32_t bsz				:  4;
			uint32_t trtyp				:  3;
			uint32_t 					:  4; // Reserved
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
		} multi_dimensional;

	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR
		struct {
			// QPUSH_DSC_CFG
			uint32_t floc				:  1;
			uint32_t pri_abs			:  4;
			uint32_t pri_frame_no		:  2;
			uint32_t pri_frame_order	:  8;
			uint32_t tframe_len			:  4;
			uint32_t qman_src_type		:  2;
			uint32_t qman_dst_type		:  2;
			uint32_t wd_wait			:  1;
			uint32_t dup				:  2;
			uint32_t ddie				:  1;
			uint32_t tdt				:  1;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_lsb	:  4;
        #else /* !SENSPRO */
            uint32_t 	                :  4;
        #endif /* SENSPRO */ 
			// QPUSH_DSC_SRCP
			uint32_t src_ptr			: 32;
			// QPUSH_DSC_DSTP
			uint32_t dst_ptr			: 32;
			// QPUSH_DSC_DMASZ
			uint32_t num_planes			: 16;
			uint32_t tile_width			: 16;

			// Image source or destination type:
			union
			{
				// Image Source Type
				struct
				{
					// QPUSH_DSC_SRC
					int32_t src_x 				: 16;
					int32_t src_y 				: 16;
					// QPUSH_DSC_LINE
					uint32_t src_z 				: 16;
					uint32_t dst_line_stride	: 16;
					// QPUSH_DSC_DST
					uint32_t dst_plane_stride	: 32;
				}image_type_src;


				// Image Destination Type
				struct
				{
					// QPUSH_DSC_SRC
					uint32_t src_plane_stride	: 32;
					// QPUSH_DSC_LINE
					uint32_t src_line_stride	: 16;
					int32_t dst_x 				: 16;
					// QPUSH_DSC_DST
					int32_t dst_y 				: 16;
					uint32_t dst_z 				: 16;
				}image_type_dst;
				
				// 2 Side Image
				struct
				{
					// QPUSH_DSC_SRC
					int32_t src_x 				: 16;
					int32_t src_y 				: 16;
					// QPUSH_DSC_LINE
					uint32_t src_z 				: 16;
					int32_t dst_x 				: 16;
					// QPUSH_DSC_DST
					int32_t dst_y 				: 16;
					uint32_t dst_z 				: 16;
				}image_type_2_side;
			};
			// QPUSH_DSC_HGHT
			uint32_t tile_height		: 16;
			uint32_t src_typ			:  1;
			uint32_t dst_typ			:  1;
			uint32_t bsz				:  4;
			uint32_t trtyp				:  3;
			uint32_t chn_unpack			:  4;
		#ifdef SENSPRO    
			uint32_t ddma_task_id_msb	:  3;
        #else /* !SENSPRO */
            uint32_t 	                :  3;
        #endif /* SENSPRO */ 
		} image;
	#endif // CSL_QMAN_VIRTUAL_DESCRIPTOR

		struct
		{
			T_QPUSH_DSC_CFG 		qpush_dsc_cfg;
			uint32_t 				src_ptr;
			uint32_t 				dst_ptr;
			T_QPUSH_DSC_DMASZ 		qpush_dsc_dmasz;
			T_QPUSH_DSC_SRC 		qpush_dsc_src;
			T_QPUSH_DSC_LINE 		qpush_dsc_line;
			T_QPUSH_DSC_DST 		qpush_dsc_dst;
			T_QPUSH_DSC_HGHT 		qpush_dsc_hght;
		} registers;
	} T_QMAN_task_descriptor;




	/*
	 * If CSL_QMAN_VIRTUAL_DESCRIPTOR is defined
	 * 		Defining virtual descriptor support.
	 */
	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR


		/**************************************************
		 * @config_group	T_QMAN_virtual_descriptor
		 * @brief:			virtual descriptor fields
		 **************************************************/
		typedef union
		{
			struct
			{
				uint32_t istart			:32;
				uint32_t 				:16;
				uint32_t iheight		:16;
				uint32_t iwidth			:16;
				uint32_t iline_stride	:16;
				uint32_t iplane_stride	:32;
				uint32_t padval			:32;
				uint32_t element_sz		: 4;
				uint32_t num_ch			: 4;
				uint32_t clip_en		: 1;
				uint32_t 				:23;
			} fields;
			struct
			{
				uint32_t values[6];
			} csl;
		} T_QMAN_virtual_descriptor;


	#endif // ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR

#endif // if ( defined(XM4) && (CEVA_DSP_RTL >= 120) ) || defined(XM6) || defined(SENSPRO)



/************************************************
 * @struct		T_QMAN_base_ptrs
 * Description: Contains the QMAN shared pointers (aka the QMAN base pointers)
 ************************************************/
typedef struct
{
	uint32_t queue_rptr;
	uint32_t queue_last_core_id;
	uint32_t queue_wptr;
	uint32_t qman_num;
} T_QMAN_base_ptrs;


/*****************************************************************************
 * @struct	T_QMAN_resource
 * @brief	QMAN resource information.
 *****************************************************************************/
#define PADDING_SIZE(_padding) 		(_padding)

#if ( ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) ) )
	#define ALLIGNMENT_PADDING uint32_t padding[PADDING_SIZE(2)];
#elif defined(CEVABX)
	#define ALLIGNMENT_PADDING uint32_t padding[PADDING_SIZE(1)];
#elif defined(SENSPRO)
	#define ALLIGNMENT_PADDING uint32_t padding[PADDING_SIZE(5)];
#elif ( ( defined(XM4) && ( CEVA_DSP_RTL >= 120 ) ) || defined(XM6))
	#define ALLIGNMENT_PADDING uint32_t padding[PADDING_SIZE(6)];
#else
	CSL_ERROR_UNSUPPORTED_CORE
#endif

typedef struct
{
	// QMAN addresses
	T_QMAN_base_ptrs base_pointers;				// [0  - 16] Queue base pointers (read and write pointers)
	T_QMAN_task_descriptor *queue;				// [16 - 20] Queue start address
	uint32_t last_address;              		// [20 - 24] Queue last address (queue depth * task descriptor size)

	// TFrame data
	uint16_t queue_size;						// [24 - 26] Maximum number of task descriptor in the queue
	uint8_t frame_length; 						// [26 - 27] When set indicating the size of that frame currently being pushed to the queue
	uint8_t frame_counter; 						// [27 - 28] When set indicate that a tasks frame has started to be pushed and had not ended yet. Contains the remaining number of tasks to be pushed.

	// Sync point data
	volatile uint32_t current_sync_value;       // [28 - 32] current sync point value - sync_message_desc destination
	uint32_t sync_counter; 						// [32 - 36] sync point descriptor	- sync_message_desc message
	T_QMAN_task_descriptor sync_message_desc; 	// [36 - 68] sync point descriptor with interrupt

	// Allocation ID
	T_csl_allocation_id allocation_id;			// [68 - 72]

	// Continuous execution mode
#ifdef CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED
	uint32_t is_continuous_execution;			// [72 - 76] True is the queue is used in continuous execution mode (Qx_AUTO = 1)
#endif /* CSL_QMAN_CONTINUOUS_EXECUTION_SUPPORTED */
	ALLIGNMENT_PADDING							// [Aligned to 8]
} T_QMAN_resource;




/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Task Descriptor Configuration Macros
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

#if ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) )

	// CSL Internal macro QMAN_CONFIG    
	#define QMAN_CONFIG(_task_descriptor_parse, _direction, _transfer_type)		                \
			memset((&(_task_descriptor_parse)), 0, sizeof(_task_descriptor_parse)); 	        \
			_task_descriptor_parse.trtyp		= _transfer_type;                               \
			_task_descriptor_parse.floc 		= QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	        \
			_task_descriptor_parse.iit 	        = ( _direction == QMAN_TASK_DUP_INTERNAL );     \
			_task_descriptor_parse.extw 	    = ( _direction == QMAN_TASK_DUP_UPLOAD );
			
#elif defined(CEVABX)

	// CSL Internal macro QMAN_CONFIG
	#define QMAN_CONFIG(_task_descriptor_parse, _direction)		                				\
			memset((&(_task_descriptor_parse)), 0, sizeof(_task_descriptor_parse)); 	        \
			_task_descriptor_parse.floc 		= QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	        \
			_task_descriptor_parse.iit 	        = ( _direction == QMAN_TASK_DUP_INTERNAL );     \
			_task_descriptor_parse.extw 	    = ( _direction == QMAN_TASK_DUP_UPLOAD );


#else /* !( defined(CEVABX) || ( defined(XM4) && CEVA_DSP_RTL < 120 ) ) */

	// CSL Internal macro QMAN_CONFIG
	#define QMAN_CONFIG(_task_descriptor_parse, _direction, _transfer_type)		                \
			( void )memset((&(_task_descriptor_parse)), 0, sizeof(_task_descriptor_parse)); 	\
			_task_descriptor_parse.floc 		= ( uint8_t )QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME;\
			_task_descriptor_parse.dup 			= ( uint8_t )_direction; 						\
			_task_descriptor_parse.trtyp		= ( uint8_t )_transfer_type;
			
#endif /* !( defined(CEVABX) || ( defined(XM4) && CEVA_DSP_RTL < 120 ) ) */



#ifdef XM4

	#if  ( CEVA_DSP_RTL < 120 )
	
		
		// CSL Internal macro QMAN_CONFIG_MULTI_DI_TRANFER_SIZE    
		#define QMAN_CONFIG_MULTI_DI_TRANFER_SIZE(_task_descriptor, _width, _height)	       	\
				(_task_descriptor).multi_dimensional.tile_width 	= _width;					\
				(_task_descriptor).multi_dimensional.tile_height 	= _height;

		/*********************************************************************************************
		* @function	QMAN_CONFIG_MULTI_DI_STRIDE
		* @author	Eran Rebenshtok
		* @date		26/05/2021
		* @brief	Set stride for multi dimentions transfers
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @param	direction: Direction of the transfer.
		* @param	src_stride: Source Transfer.
		* @param	dst_stride: Destination Transfer.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_CONFIG_MULTI_DI_STRIDE( T_QMAN_task_descriptor *task_descriptor, uint32_t direction, uint32_t src_stride, uint32_t dst_stride )  PRAGMA_CSECT("CSL_CODE_SECTION");
			
	#else /* !( CEVA_DSP_RTL < 120 ) */

		// CSL Internal macro QMAN_CONFIG_MULTI_DI_TRANFER_SIZE  
		#define QMAN_CONFIG_MULTI_DI_TRANFER_SIZE(_task_descriptor, _width, _height)	            \
				(_task_descriptor).multi_dimensional.tile_width 	= _width;						\
				(_task_descriptor).multi_dimensional.tile_height 	= _height;						\
				(_task_descriptor).multi_dimensional.num_planes 	= 1; 
				
		// CSL Internal macro QMAN_CONFIG_MULTI_DI_STRIDE  
		#define QMAN_CONFIG_MULTI_DI_STRIDE(_task_descriptor, _src_stride, _dst_stride)	            \
				(_task_descriptor).multi_dimensional.src_line_stride		= _src_stride; 			\
				(_task_descriptor).multi_dimensional.dst_line_stride		= _dst_stride;			\
				(_task_descriptor).multi_dimensional.src_plane_stride 	    = 0;		            \
				(_task_descriptor).multi_dimensional.dst_plane_stride 	    = 0; 
			
	#endif /* ( CEVA_DSP_RTL < 120 ) */ 
	
#endif /* !XM4 */


#if defined(XM6) || defined(SENSPRO)


	// CSL Internal macro QMAN_CONFIG_MULTI_DI_TRANFER_SIZE 
	#define QMAN_CONFIG_MULTI_DI_TRANFER_SIZE(_task_descriptor, _width, _height, _num_planes)	\
			(_task_descriptor).multi_dimensional.tile_width 	= _width;						\
			(_task_descriptor).multi_dimensional.tile_height 	= _height;						\
			(_task_descriptor).multi_dimensional.num_planes 	= _num_planes;

	// CSL Internal macro QMAN_CONFIG_MULTI_DI_STRIDE
	#define QMAN_CONFIG_MULTI_DI_STRIDE(_task_descriptor, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride)	\
			(_task_descriptor).multi_dimensional.src_line_stride		= _src_stride; 			\
			(_task_descriptor).multi_dimensional.dst_line_stride		= _dst_stride;			\
			(_task_descriptor).multi_dimensional.src_plane_stride 	    = _src_plane_stride;	\
			(_task_descriptor).multi_dimensional.dst_plane_stride 	    = _dst_plane_stride; 

#endif // if defined(XM6) || defined(SENSPRO)

       

#ifdef SENSPRO
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_INTERRUPT
	* @author	Ravid Rzaev
	* @date 	16/01/2021
	* @brief	Configure (Enable / Disable ) the interrupt at the end of transfer.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_ddie _enable)
	*********************************************************************************************/
	#define QMAN_CONFIG_INTERRUPT(_task_descriptor, _enable) do{	\
			(_task_descriptor).message.ddie 	= _enable;									\
		}while(false);
#elif defined( CEVABX )
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_INTERRUPT
	* @author	Ravid Rzaev
	* @date 	16/01/2021
	* @brief	Configure (Enable / Disable ) the interrupt at the end of message transfer.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_ddie _enable)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_INTERRUPT(_task_descriptor, _enable) do{	\
			(_task_descriptor).download_message.ddie 	= _enable;									\
		}while(0);

	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR_INTERRUPT
	* @author	Ravid Rzaev
	* @date 	16/01/2021
	* @brief	Configure (Enable / Disable ) the interrupt at the end of linear transfer.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_ddie _enable)
	*********************************************************************************************/
	#define QMAN_CONFIG_LINEAR_INTERRUPT(_task_descriptor, _enable) do{	\
			(_task_descriptor).linear.ddie 	= _enable;									\
		}while(0);
#endif

#if ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) )
	



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD
	* @author	Eran Rebenshtok
	* @date 	24/05/2021
	* @brief	Configure the given task as internal message task.
	* @params	(_task_descriptor)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_DOWNLOAD(_task_descriptor) do{ 								            \
			memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 						        \
			(_task_descriptor).download_message.floc 			= QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).download_message.qman_ext_type 	= QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).download_message.qman_int_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR;		\
			(_task_descriptor).download_message.bsz 	        = QMAN_MESSAGE_CONSTANT;				\
			(_task_descriptor).download_message.message 	    = 1;		                            \
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given message download task with a message and internal pointer.
	* @params	(_task_descriptor, _message, _int_ptr)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES(_task_descriptor, _message, _int_ptr) do{ 		\
		(_task_descriptor).download_message.message 		= _message; 							\
		(_task_descriptor).download_message.int_ptr 		= _int_ptr; 							\
		}while(0);

		
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_UPLOAD
	* @author	Eran Rebenshtok
	* @date 	24/05/2021
	* @brief	Configure the given task as external message task.
	* @params	(_task_descriptor)
	*********************************************************************************************/  
	#define QMAN_CONFIG_MESSAGE_UPLOAD(_task_descriptor) do{ 								            \
			memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 						        \
			(_task_descriptor).upload_message.floc 			    = QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).upload_message.qman_ext_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR; 		\
			(_task_descriptor).upload_message.qman_int_type 	= QMAN_TASK_PTR_TYPE_MESSAGE;		    \
			(_task_descriptor).upload_message.extw              = QMAN_TASK_EXTW_FROM_DDIA_TO_DDEA;     \
			(_task_descriptor).upload_message.bsz 	            = QMAN_MESSAGE_CONSTANT;				\
			(_task_descriptor).upload_message.ext_ptr 	        = 2;		                            \
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_UPLOAD_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given message upload task with a message and external pointer.
	* @params	(_task_descriptor)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_UPLOAD_ADDRESSES(_task_descriptor, _message, _ext_ptr) do{ 			\
		(_task_descriptor).upload_message.message 		= _message; 								\
		(_task_descriptor).upload_message.ext_ptr 		= _ext_ptr; 								\
		}while(0);



		
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR
	* @author	Eran Rebenshtok
	* @date 	24/05/2021
	* @brief	Configure the given task as linear (1D) task.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_dup _direction, uint32_t _transfer_size, E_QMAN_task_descriptor_trtyp _transfer_type)
	*********************************************************************************************/    
	#define QMAN_CONFIG_LINEAR(_task_descriptor, _direction, _transfer_size, _transfer_type) do{	\
			QMAN_CONFIG(((_task_descriptor).linear), _direction, _transfer_type);					\
			(_task_descriptor).linear.qman_ext_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR; 		    \
			(_task_descriptor).linear.qman_int_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR;		    \
			(_task_descriptor).linear.dma_size 	        = _transfer_size;		                    \
			(_task_descriptor).linear.ext_ptr 	        = (_direction == QMAN_TASK_DUP_DOWNLOAD );  \
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given linear task external and internal pointers.
	* @params	(_task_descriptor, _ext_ptr, _int_ptr)
	*********************************************************************************************/
	#define QMAN_CONFIG_LINEAR_ADDRESSES(_task_descriptor, _ext_ptr, _int_ptr) do{ 				\
		(_task_descriptor).linear.ext_ptr 			= _ext_ptr; 								\
		(_task_descriptor).linear.int_ptr 			= _int_ptr; 								\
		}while(0);


	
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MULTI_DI
	* @author	Eran Rebenshtok
	* @date 	24/05/2021
	* @brief	Configure the given transfer task as a multidimensional transfer task.
	* @params	(T_QMAN_task_descriptor, E_QMAN_task_descriptor_dup, E_QMAN_task_descriptor_trtyp, _width, _height, _src_stride, _dst_stride)
	*********************************************************************************************/
	#define QMAN_CONFIG_MULTI_DI(_task_descriptor, _direction, _transfer_type, _width, _height, _src_stride, _dst_stride) do{ 	\
			QMAN_CONFIG(((_task_descriptor).multi_dimensional), _direction, _transfer_type); 	                \
			QMAN_CONFIG_MULTI_DI_TRANFER_SIZE((_task_descriptor), _width, _height);                             \
			QMAN_CONFIG_MULTI_DI_STRIDE(&(_task_descriptor), _direction, _src_stride, _dst_stride);             \
			(_task_descriptor).multi_dimensional.floc 			    = QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	    \
			(_task_descriptor).multi_dimensional.tdt 	            = QMAN_TASK_TDT_MULTI_DI;		            \
			(_task_descriptor).multi_dimensional.ext_ptr 	        = (_direction == QMAN_TASK_DUP_DOWNLOAD );  \
		}while(0);
			

		/*********************************************************************************************
		* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES
		* @author	Anat Keidar
		* @date 	01/11/2021
		* @brief	Configure the given message download task with a message and internal pointer.
		* @params	(_task_descriptor, _message, _int_ptr)
		*********************************************************************************************/
		#define QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES(_task_descriptor, _message, _int_ptr) do{ 		\
			(_task_descriptor).download_message.message 		= _message; 							\
			(_task_descriptor).download_message.int_ptr 		= _int_ptr; 							\
			}while(0);


#elif defined(CEVABX)



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given task as internal message task.
	* @params	(_task_descriptor)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_DOWNLOAD(_task_descriptor) do{ 			            \
			memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 						        \
			(_task_descriptor).download_message.floc 			= QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).download_message.qman_ext_type 	= QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).download_message.qman_int_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR;		\
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given message download task with a message and internal pointer.
	* @params	(_task_descriptor, _message, _int_ptr)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_DOWNLOAD_ADDRESSES(_task_descriptor, _message, _int_ptr) do{ 		\
		(_task_descriptor).download_message.message 		= _message; 							\
		(_task_descriptor).download_message.int_ptr 		= _int_ptr; 							\
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_UPLOAD
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given task as external message task.
	* @params	(_task_descriptor)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_UPLOAD(_task_descriptor) do{ 				        \
			memset((&(_task_descriptor)), 0, sizeof(_task_descriptor)); 						        \
			(_task_descriptor).upload_message.floc 			    = QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).upload_message.qman_ext_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR; 		\
			(_task_descriptor).upload_message.qman_int_type 	= QMAN_TASK_PTR_TYPE_MESSAGE;		    \
			(_task_descriptor).upload_message.extw              = QMAN_TASK_EXTW_FROM_DDIA_TO_DDEA;     \
		}while(0);



	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_UPLOAD_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given message upload task with a message and external pointer.
	* @params	(_task_descriptor, _message, _ext_ptr)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_UPLOAD_ADDRESSES(_task_descriptor, _message, _ext_ptr) do{ 		\
		(_task_descriptor).upload_message.message 		= _message; 								\
		(_task_descriptor).upload_message.ext_ptr 		= _ext_ptr; 								\
		}while(0);





	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given task as linear (1D) task.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_dup _direction, uint32_t _transfer_size)
	*********************************************************************************************/
	#define QMAN_CONFIG_LINEAR(_task_descriptor, _direction, _transfer_size) do{					\
			QMAN_CONFIG(((_task_descriptor).linear), _direction);									\
			(_task_descriptor).linear.qman_ext_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR; 		    \
			(_task_descriptor).linear.qman_int_type 	= QMAN_TASK_PTR_TYPE_DIRECT_ADDR;		    \
			(_task_descriptor).linear.dma_size 	        = _transfer_size;		                    \
		}while(0);





	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR_ADDRESSES
	* @author	Anat Keidar
	* @date 	01/11/2021
	* @brief	Configure the given linear task external and internal pointers.
	* @params	(_task_descriptor, _ext_ptr, _int_ptr)
	*********************************************************************************************/
	#define QMAN_CONFIG_LINEAR_ADDRESSES(_task_descriptor, _ext_ptr, _int_ptr) do{ 				\
		(_task_descriptor).linear.ext_ptr 			= _ext_ptr; 								\
		(_task_descriptor).linear.int_ptr 			= _int_ptr; 								\
		}while(0);




#elif ( ( defined(XM4) && (CEVA_DSP_RTL >= 120) ) || defined(XM6) || defined(SENSPRO) )




	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_DOWNLOAD
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Configure the given task as internal message task.
	* @params	(_task_descriptor, _message, _destination)
	*********************************************************************************************/
	#define QMAN_CONFIG_MESSAGE_DOWNLOAD(_task_descriptor) do{ 									            \
			( void )memset((&(_task_descriptor)), 0, ( uint32_t )sizeof(_task_descriptor)); 				\
			(_task_descriptor).message.floc 			= ( uint8_t )QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).message.qman_src_type 	= ( uint8_t )QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).message.qman_dst_type 	= ( uint8_t )QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).message.dup 				= ( uint8_t )QMAN_TASK_DUP_DOWNLOAD; 				\
			(_task_descriptor).message.dma_size 		= ( uint32_t )sizeof(uint32_t);						\
		}while(false);
		
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_MESSAGE_UPLOAD
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Configure the given task as external message task.
	* @params	(_task_descriptor, _message, _destination)
	*********************************************************************************************/    
	#define QMAN_CONFIG_MESSAGE_UPLOAD(_task_descriptor) do{ 		                                        \
			( void )memset((&(_task_descriptor)), 0, ( uint32_t )sizeof(_task_descriptor)); 				\
			(_task_descriptor).message.floc 			= ( uint8_t )QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME; 	\
			(_task_descriptor).message.qman_src_type 	= ( uint8_t )QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).message.qman_dst_type 	= ( uint8_t )QMAN_TASK_PTR_TYPE_MESSAGE; 			\
			(_task_descriptor).message.dup 				= ( uint8_t )QMAN_TASK_DUP_UPLOAD; 				    \
			(_task_descriptor).message.dma_size 		= ( uint32_t )sizeof(uint32_t);						\
		}while(false);
		
	/*********************************************************************************************
	* @macro	QMAN_CONFIG_LINEAR
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Configure the given task as linear (1D) task.
	* @params	(T_QMAN_task_descriptor _task_descriptor, E_QMAN_task_descriptor_dup _direction, uint32_t _transfer_size, E_QMAN_task_descriptor_trtyp _transfer_type)
	*********************************************************************************************/
	#define QMAN_CONFIG_LINEAR(_task_descriptor, _direction, _transfer_size, _transfer_type) do{	\
			QMAN_CONFIG(((_task_descriptor).linear), ( _direction ), ( _transfer_type ) );   		\
			(_task_descriptor).linear.dma_size 	= _transfer_size;									\
		}while(false);  


	/*********************************************************************************************
	* @macro	QMAN_CONFIG_ADDRESSES
	* @author	Ravid Rzaev
	* @date 	07/10/2021
	* @brief	Configure the surce and destination ptr.
	* @params	(_task_descriptor, _src, _dst)
	*********************************************************************************************/
	#define QMAN_CONFIG_ADDRESSES(_task_descriptor, _src, _dst) do{ 	\
			(_task_descriptor).registers.src_ptr 			= _src; 	\
			(_task_descriptor).registers.dst_ptr 			= _dst; 	\
		}while(false);


	#if ( defined(XM4) && (CEVA_DSP_RTL >= 120) )

		/*********************************************************************************************
		* @macro	QMAN_CONFIG_MULTI_DI
		* @author	Eran Rebenshtok
		* @date 	24/05/2021
		* @brief	Configure the given transfer task as a multidimensional transfer task.
		* @params	(T_QMAN_task_descriptor, E_QMAN_task_descriptor_dup, E_QMAN_task_descriptor_trtyp, _width, _height, _src_stride, _dst_stride)
		*********************************************************************************************/ 
		#define QMAN_CONFIG_MULTI_DI(_task_descriptor, _direction, _transfer_type, _width, _height, _src_stride, _dst_stride) do{ 	\
				QMAN_CONFIG(((_task_descriptor).multi_dimensional), _direction, _transfer_type); 					\
				(_task_descriptor).multi_dimensional.tdt = QMAN_TASK_TDT_MULTI_DI;									\
				QMAN_CONFIG_MULTI_DI_TRANFER_SIZE((_task_descriptor), _width, _height);								\
				QMAN_CONFIG_MULTI_DI_STRIDE((_task_descriptor), _src_stride, _dst_stride);		                    \
			}while(0);  
		
	#else /* !( defined(XM4) && (CEVA_DSP_RTL >= 120) ) */
		/*********************************************************************************************
		* @macro	QMAN_CONFIG_MULTI_DI
		* @author	Anat Keidar
		* @date 	04/03/2021
		* @brief	Configure the given transfer task as a multidimensional transfer task.
		* @params	(T_QMAN_task_descriptor, E_QMAN_task_descriptor_dup, E_QMAN_task_descriptor_trtyp, _width, _hight, _num_planes, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride)
		*********************************************************************************************/
		#define QMAN_CONFIG_MULTI_DI(_task_descriptor, _direction, _transfer_type, _width, _height, _num_planes, _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride) do{ 	\
				QMAN_CONFIG(((_task_descriptor).multi_dimensional), _direction, _transfer_type); 								    \
				(_task_descriptor).multi_dimensional.tdt = ( uint8_t )QMAN_TASK_TDT_MULTI_DI;							            \
				QMAN_CONFIG_MULTI_DI_TRANFER_SIZE((_task_descriptor), _width, _height, _num_planes);								\
				QMAN_CONFIG_MULTI_DI_STRIDE((_task_descriptor), _src_stride, _dst_stride, _src_plane_stride, _dst_plane_stride);	\
			}while(false);
	#endif /* ( defined(XM4) && (CEVA_DSP_RTL >= 120) ) */



	#ifdef CSL_QMAN_VIRTUAL_DESCRIPTOR


		/*********************************************************************************************
		* @macro	QMAN_CONFIG_IMAGE_TRANSFER
		* @author	Anat Keidar
		* @date 	04/03/2021
		* @brief	Configure the given task descriptor (image transfer) with the given parameters.
		* @params	(_task_descripto, _direction, _source, _destination, _tile_width, _tile_height, _num_planes, _unpack)
		*********************************************************************************************/
		#define QMAN_CONFIG_IMAGE_TRANSFER(_task_descriptor, _direction, _src_vdesc, _dst_vdesc, _tile_width, _tile_height, _num_planes, _unpack) do{	\
				QMAN_CONFIG((_task_descriptor).image, _direction, QMAN_TASK_TRTYP_MULTI_DI);	\
				(_task_descriptor).image.tdt 			= QMAN_TASK_TDT_MULTI_DI;		        \
				(_task_descriptor).image.tile_width 	= _tile_width;					        \
				(_task_descriptor).image.tile_height 	= _tile_height;					        \
				(_task_descriptor).image.num_planes 	= _num_planes;					        \
				(_task_descriptor).image.src_ptr	 	= _src_vdesc;					        \
				(_task_descriptor).image.dst_ptr		= _dst_vdesc;					        \
				(_task_descriptor).image.chn_unpack 	= _unpack;  					        \
				(_task_descriptor).image.src_typ 		= QMAN_TASK_PTR_TYP_VIRTUAL_DESCRIPTOR_ADDRESS;  				\
				(_task_descriptor).image.dst_typ 		= QMAN_TASK_PTR_TYP_VIRTUAL_DESCRIPTOR_ADDRESS;  				\
			}while(0);


			/*********************************************************************************************
			* @macro	QMAN_CONFIG_IMAGE_EXTENSION
			* @author	Anat Keidar
			* @date 	04/03/2021
			* @brief	Configure the given virtual descriptor (image configuration) with the given parameters.
			* @params	(_virtual_descriptor, _istart, _iheight, _iwidth, _iline_stride, _iplane_stride, _pad_val, _element_size, _num_channels, _clip_enabled)
			*********************************************************************************************/
			#define QMAN_CONFIG_IMAGE_EXTENSION(_virtual_descriptor, _istart, _iheight, _iwidth, _iline_stride, _iplane_stride, _pad_val, _element_size, _num_channels, _clip_enabled) do{	\
					memset((&(_virtual_descriptor)), 0, sizeof(_virtual_descriptor)); 	\
					_virtual_descriptor.fields.istart        = _istart;					\
					_virtual_descriptor.fields.iheight       = _iheight;				\
					_virtual_descriptor.fields.iwidth        = _iwidth;					\
					_virtual_descriptor.fields.iline_stride  = _iline_stride;			\
					_virtual_descriptor.fields.iplane_stride = _iplane_stride;			\
					_virtual_descriptor.fields.padval	     = _pad_val;				\
					_virtual_descriptor.fields.element_sz    = _element_size;			\
					_virtual_descriptor.fields.num_ch        = _num_channels;			\
					_virtual_descriptor.fields.clip_en       = _clip_enabled;			\
				}while(0);



	#endif // CSL_QMAN_VIRTUAL_DESCRIPTOR
	
	

#endif /* ( defined(XM4) && (CEVA_DSP_RTL >= 120) ) || defined(XM6) || defined(SENSPRO) || defined(CEVABX) || ( defined(XM4) && CEVA_DSP_RTL < 120 ) */



#ifdef CSL_BMAN_SUPPORTED

		/*********************************************************************************************
		*********************************************************************************************
		*********************************************************************************************
		*
		*	QMAN BMAN Functions
		*
		*********************************************************************************************
		*********************************************************************************************
		*********************************************************************************************/




		/*********************************************************************************************
		* @macro	QMAN_CONFIG_BMAN_ADDRESSES
		* @author	Anat Keidar
		* @date 	04/03/2021
		* @brief	Configure the given task linear external and internal pointers.
		* @params	(T_QMAN_task_descriptor _task_descriptor,  E_QMAN_task_descriptor_ptr_type _qman_ext_type, uint32_t _ext_ptr, E_QMAN_task_descriptor_ptr_type _qman_int_type, _int_ptr)
		*********************************************************************************************/
		#define QMAN_CONFIG_BMAN_ADDRESSES(_task_descriptor, _qman_ext_type, _ext_ptr, _qman_int_type, _int_ptr) do{		\
					(_task_descriptor).linear.qman_ext_type 	= _qman_ext_type; 		    				\
					(_task_descriptor).linear.ext_ptr 			= (uint32_t)((QMAN_TASK_PTR_TYPE_DIRECT_ADDR == _qman_ext_type)?(_ext_ptr):(CSL_GET_RESOURCE_NUM(_ext_ptr)));	\
					(_task_descriptor).linear.qman_int_type 	= _qman_int_type;		    				\
					(_task_descriptor).linear.int_ptr 			= (uint32_t)((QMAN_TASK_PTR_TYPE_DIRECT_ADDR == _qman_int_type)?(_int_ptr):(CSL_GET_RESOURCE_NUM(_int_ptr)));	\
				}while(0);

#endif /* CSL_BMAN_SUPPORTED */

/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	T_QMAN_task_descriptor Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

#if ( ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) ) || defined(CEVABX) )


	/******************************************************
	 * @macro QMAN_MESSAGE_CONSTANT
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		
	 * @field			BSZ
	 ******************************************************/
	#define QMAN_MESSAGE_CONSTANT      0xF // According to Spec XM4 RTL < 120 (MSS)


	/******************************************************
	 * @enum 			E_QMAN_task_descriptor_extw
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		QPUSH_DSC_INT_PTR
	 * @field			EXTW
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_EXTW_FROM_DDIA_TO_DDEA		= 1,
		QMAN_TASK_EXTW_FROM_DDEA_TO_DDIA	    = 0
	}E_QMAN_task_descriptor_extw;


	/******************************************************
	 * @enum 			E_QMAN_task_descriptor_iit
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		QPUSH_DSC_TCTL
	 * @field			IIT
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_IIT_EXTERNAL_PORT_UNUSED		= 1,
		QMAN_TASK_IIT_EXTERNAL_PORT_USED	    = 0
	}E_QMAN_task_descriptor_iit;


#endif /* ( ( defined(XM4) && CEVA_DSP_RTL < 120 ) || defined(CEVABX) ) */




/******************************************************
 * @enum 			E_QMAN_task_descriptor_floc
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [XM4 RTL110 and BX]: QPUSH_DSC_TCTL
 * @field			FLOC
 ******************************************************/
typedef enum
{
	QMAN_TASK_FLOC_FIRST_TASK_IN_FRAME		= 1,
	QMAN_TASK_FLOC_NOT_FIRST_TASK_IN_FRAME	= 0
}E_QMAN_task_descriptor_floc;


 
/******************************************************
 * @enum 			E_QMAN_task_descriptor_ptr_type
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [XM4 RTL110 and BX]: QPUSH_DSC_TCTL
 * @field			QMAN_SRC_TYPE and QMAN_DST_TYPE
 ******************************************************/
typedef enum
{
	QMAN_TASK_PTR_TYPE_DIRECT_ADDR			= 0,
#ifdef CEVABX
	QMAN_TASK_PTR_TYPE_BMAN_STORE_AND_FW	= 1,
	QMAN_TASK_PTR_TYPE_BMAN_CUT_THROUGH		= 2,
#endif /* CEVABX */
	QMAN_TASK_PTR_TYPE_MESSAGE 				= 3
}E_QMAN_task_descriptor_ptr_type;



/******************************************************
 * @enum 			E_QMAN_task_descriptor_wd_wait
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [XM4 RTL110 and BX]: QPUSH_DSC_TCTL
 * @field			WD_WAIT
 ******************************************************/
typedef enum{
	  QMAN_TASK_WD_WAIT_WAIT_FOR_TASK_TO_COMPLETE_DISABLE = 0,
	  QMAN_TASK_WD_WAIT_WAIT_FOR_TASK_TO_COMPLETE_ENABLE = 1
}E_QMAN_task_descriptor_wd_wait;


#ifndef CEVABX
/******************************************************
 * @enum 			E_QMAN_task_descriptor_tdt
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [XM4 RTL110]: QPUSH_DSC_TCTL
 * @field			TDT
 ******************************************************/
typedef enum
{
	QMAN_TASK_TDT_1D				= 0,
	QMAN_TASK_TDT_MULTI_DI			= 1
}E_QMAN_task_descriptor_tdt;
#endif // CEVABX


/******************************************************
 * @enum 			E_QMAN_task_descriptor_dup
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [BX]: driver addition; [XM4 rtl<120]: drive optionn
 * @field			DUP
 ******************************************************/
typedef enum
{
	QMAN_TASK_DUP_UPLOAD 		= 0,
	QMAN_TASK_DUP_DOWNLOAD		= 1,
	QMAN_TASK_DUP_INTERNAL		= 2
}E_QMAN_task_descriptor_dup;


/******************************************************
 * @enum 			E_QMAN_task_descriptor_ddie
 * @config_group	T_QMAN_task_descriptor
 * @register 		[XM4 RTL120 and up]: QPUSH_DSC_CFG; [XM4 RTL110]: QPUSH_DSC_TCTL
 * @field			DDIE
 ******************************************************/
typedef enum
{
	QMAN_TASK_DDIE_DDMA_INTERRUPT_DISABLED 	= 0,
	QMAN_TASK_DDIE_DDMA_INTERRUPT_ENABLED 	= 1
}E_QMAN_task_descriptor_ddie;



/******************************************************
 * @enum 			E_QMAN_task_descriptor_bsz
 * @config_group	T_QMAN_task_descriptor
 * @register 		For message and linear: QPUSH_DSC_CFG; For three_dimensional QPUSH_DSC_HGHT; For BX linear QPUSH_DSC_TCTL
 * @field			BSZ
 ******************************************************/
typedef enum
{
	QMAN_TASK_BSZ_INCREMENT_1			= 0,
	QMAN_TASK_BSZ_FIXED_1				= 1,
	QMAN_TASK_BSZ_FIXED_4				= 2,
	QMAN_TASK_BSZ_FIXED_8				= 3,
	QMAN_TASK_BSZ_FIXED_16				= 4,
	QMAN_TASK_BSZ_INCREMENT_32			= 5,
	QMAN_TASK_BSZ_INCREMENTED_4			= 6,
	QMAN_TASK_BSZ_INCREMENTED_64		= 7,
	QMAN_TASK_BSZ_INCREMENTED_128		= 8,
	QMAN_TASK_BSZ_INCREMENTED_256		= 9,
	QMAN_TASK_BSZ_INCREMENTED_8			= 10,
	QMAN_TASK_BSZ_INCREMENTED_16		= 14
} E_QMAN_task_descriptor_bsz;

/******************************************************
 * @enum 			E_QMAN_task_descriptor_pri_abs
 * @config_group	T_QMAN_task_descriptor
 * @register 		[ SENSPRO ] Qx_en_depth
 * @field			pri_abs
 ******************************************************/
typedef enum
{
	QMAN_TASK_HEIGHEST_PRIORITY_0 = 0,
	QMAN_TASK_PRIORITY_1 = 1,
	QMAN_TASK_PRIORITY_2 = 2,
	QMAN_TASK_PRIORITY_3 = 3,
	QMAN_TASK_PRIORITY_4 = 4,
	QMAN_TASK_PRIORITY_5 = 5,
	QMAN_TASK_PRIORITY_6 = 6,
	QMAN_TASK_PRIORITY_7 = 7,
	QMAN_TASK_PRIORITY_8 = 8,
	QMAN_TASK_PRIORITY_9 = 9,
	QMAN_TASK_PRIORITY_10 = 10,
	QMAN_TASK_PRIORITY_11 = 11,
	QMAN_TASK_PRIORITY_12 = 12,
	QMAN_TASK_PRIORITY_13 = 13,
	QMAN_TASK_PRIORITY_14 = 14,
	QMAN_TASK_LOWEST_PRIORITY_15 = 15
}E_QMAN_task_descriptor_pri_abs;

#ifndef CEVABX
	/******************************************************
	 * @enum 			E_QMAN_task_descriptor_trtyp
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		QPUSH_DSC_HGHT
	 * @field			TRTYP
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_TRTYP_LINEAR 					= 0,
		QMAN_TASK_TRTYP_MULTI_DI	 			= 0,
	#if ((defined XM6) || (defined XM4))
		QMAN_TASK_TRTYP_TWO_BANK_SRC 			= 3,
		QMAN_TASK_TRTYP_TWO_BANK_DUPLICATED_DST	= 5,
		QMAN_TASK_TRTYP_TWO_BANK_DST 			= 7,
	#endif
		QMAN_TASK_TRTYP_ONE_BANK_SRC 			= 2,
		QMAN_TASK_TRTYP_ONE_BANK_DUPLICATED_DST	= 4,
		QMAN_TASK_TRTYP_ONE_BANK_DST 			= 6
	}E_QMAN_task_descriptor_trtyp;
#endif /* !CEVABX */




#ifndef CSL_QMAN_VIRTUAL_DESCRIPTOR


	/******************************************************
	 * @enum 			E_QMAN_task_descriptor_extended_ptr_type
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		QPUSH_DSC_HGHT
	 * @field			SRC_TYP and DST_TYP
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_PTR_TYP_TRANSFER_ADDRESS = 0,
	}E_QMAN_task_descriptor_extended_ptr_type;

#else // ifndef CSL_QMAN_VIRTUAL_DESCRIPTOR




	/******************************************************
	 * @enum 			E_QMAN_task_descriptor_extended_ptr_type
	 * @config_group	T_QMAN_task_descriptor
	 * @register 		QPUSH_DSC_HGHT
	 * @field			SRC_TYP and DST_TYP
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_PTR_TYP_TRANSFER_ADDRESS = 0,
		QMAN_TASK_PTR_TYP_VIRTUAL_DESCRIPTOR_ADDRESS = 1
	}E_QMAN_task_descriptor_extended_ptr_type;



	/******************************************************
	 * @enum 			E_qman_virtual_clip_en
	 * @config_group	T_qman_virtual_descriptor
	 * @register 		MSS_2DCFG1
	 * @field			CLIP_EN
	 ******************************************************/
	typedef enum
	{
		QMAN_VIRTUAL_CLIP_ENABLE_FLASE       = 0,
		QMAN_VIRTUAL_CLIP_ENABLE_TRUE        = 1
	}E_qman_virtual_clip_en;

	/******************************************************
	 * @enum 			E_qman_virtual_element_size
	 * @config_group	T_qman_virtual_descriptor
	 * @register 		MSS_2DCFG1
	 * @field			ELEMENT_SZ
	 ******************************************************/
	typedef enum
	{
		QMAN_VIRTUAL_ELEMENT_SZ_ONE_BYTE  = 1,
		QMAN_VIRTUAL_ELEMENT_SZ_TWO_BYTES  = 2,
		QMAN_VIRTUAL_ELEMENT_SZ_FOUR_BYTES = 4
	}E_qman_virtual_element_sz;

	/******************************************************
	 * @enum 			E_qman_virtual_element_size
	 * @config_group	T_qman_virtual_descriptor
	 * @register 		MSS_2DCFG1
	 * @field			NUM_CH
	 ******************************************************/
	typedef enum
	{
		QMAN_VIRTUAL_NUM_CH_ONE_CHANNEL     = 1,
		QMAN_VIRTUAL_NUM_CH_TWO_CHANNEL     = 2,
		QMAN_VIRTUAL_NUM_CH_THREE_CHANNEL   = 4,
		QMAN_VIRTUAL_NUM_CH_FOUR_CHANNEL    = 8
	}E_qman_virtual_num_ch;

	/******************************************************
	 * @enum 			E_qman_task_chn_unpack
	 * @config_group	T_qman_task_descriptor
	 * @field			CHN_UNPACK
	 ******************************************************/
	typedef enum
	{
		QMAN_TASK_CHN_UNPACK_ALL      = 0,
		QMAN_TASK_CHN_UNPACK_ONE      = 1,
		QMAN_TASK_CHN_UNPACK_TWO      = 2,
		QMAN_TASK_CHN_UNPACK_THREE    = 4,
		QMAN_TASK_CHN_UNPACK_FOUR     = 8
	}E_qman_task_chn_unpack;

#endif // CSL_QMAN_VIRTUAL_DESCRIPTOR




















/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Task Descriptor Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/




#if (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)

	#if !( (defined(XM4) && (CEVA_DSP_RTL < 120)) || defined(CEVABX) )

		/*********************************************************************************************
		* @function	QMAN_verify_addresses
		* @author	Ravid Rzaev
		* @date 	25/10/2021
		* @brief	verify a QMAN task addresses for all transactions types.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_addresses(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");
	#endif /* !( defined(XM4) && CEVA_DSP_RTL < 120 ) */


	/*********************************************************************************************
	* @function	QMAN_verify_message_upload
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Verify a QMAN task for message upload.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_verify_message_upload(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");




	/*********************************************************************************************
	* @function	QMAN_verify_message_download
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Verify a QMAN task for message download.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_verify_message_download(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	* @function	QMAN_verify_linear_upload
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Verify a QMAN task for linear upload.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_verify_linear_upload(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	* @function	QMAN_verify_linear_download
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Verify a QMAN task for linear download.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_verify_linear_download(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	* @function	QMAN_verify_linear_internal
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Verify a QMAN task for internal linear transfer.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_verify_linear_internal(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





	#ifndef CEVABX
	
		/*********************************************************************************************
		* @function	QMAN_verify_linear_internal_one_bank_src
		* @author	Anat Keidar
		* @date 	07/03/2021
		* @brief	Verify a QMAN task for internal linear transfer from one bank.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_linear_internal_one_bank_src(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_linear_internal_one_bank_dst
		* @author	Anat Keidar
		* @date 	07/03/2021
		* @brief	Verify a QMAN task for internal linear transfer to one bank (duplicated or not duplicated).
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_linear_internal_one_bank_dst(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_linear_download_one_bank_dst
		* @author	Anat Keidar
		* @date 	08/03/2021
		* @brief	Verify a QMAN task for linear download transfer to one bank (duplicated or not duplicated).
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_linear_download_one_bank_dst(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_linear_upload_one_bank_src
		* @author	Anat Keidar
		* @date 	07/03/2021
		* @brief	Verify a QMAN task for linear upload transfer from one bank.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_linear_upload_one_bank_src(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");







		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_upload
		* @author	Anat Keidar
		* @date 	08/03/2021
		* @brief	Verify a QMAN upload task for multidimensional transfer.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_upload(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_download
		* @author	Anat Keidar
		* @date 	08/03/2021
		* @brief	Verify a QMAN download task for multidimensional transfer.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_download(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_multi_d_internal
		* @author	Anat Keidar
		* @date 	11/03/2021
		* @brief	Verify a QMAN internal task for multidimensional transfer.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_internal(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_internal_one_bank_src
		* @author	Anat Keidar
		* @date 	11/03/2021
		* @brief	Verify a QMAN task for internal multidimensional transfer from one bank.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_internal_one_bank_src(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");







		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_internal_one_bank_dst
		* @author	Anat Keidar
		* @date 	11/03/2021
		* @brief	Verify a QMAN task for internal multidimensional transfer to one bank (duplicated or not duplicated).
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_internal_one_bank_dst(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_download_one_bank_dst
		* @author	Anat Keidar
		* @date 	11/03/2021
		* @brief	Verify a QMAN task for multidimensional download transfer to one bank (duplicated or not duplicated).
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_download_one_bank_dst(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






		/*********************************************************************************************
		* @function	QMAN_verify_multi_di_upload_one_bank_src
		* @author	Anat Keidar
		* @date 	11/03/2021
		* @brief	Verify a QMAN task for multidimensional upload transfer from one bank.
		* @param	task_descriptor: Pointer to a QMAN task descriptor.
		* @return	CSL_SUCCESS or CSL failure code.
		*********************************************************************************************/
		E_csl_status QMAN_verify_multi_di_upload_one_bank_src(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");



	

		#if ((defined XM6) || (defined XM4))

			/*********************************************************************************************
			* @function	QMAN_verify_linear_internal_two_bank_src
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for internal linear transfer from two bank.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_linear_internal_two_bank_src(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_linear_internal_two_bank_dst
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for internal linear transfer to two bank (duplicated or not duplicated).
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_linear_internal_two_bank_dst(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_linear_download_two_bank_dst
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for linear download transfer to two bank (duplicated or not duplicated).
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_linear_download_two_bank_dst(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_linear_upload_two_bank_src
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for linear upload transfer from two bank.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_linear_upload_two_bank_src(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");




			/*********************************************************************************************
			* @function	QMAN_verify_multi_di_internal_two_bank_src
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for internal multidimensional transfer from two bank.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_multi_di_internal_two_bank_src(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");







			/*********************************************************************************************
			* @function	QMAN_verify_multi_di_internal_two_bank_dst
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for internal multidimensional transfer to two bank (duplicated or not duplicated).
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_multi_di_internal_two_bank_dst(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_multi_di_download_two_bank_dst
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for multidimensional download transfer to two bank (duplicated or not duplicated).
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_multi_di_download_two_bank_dst(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_multi_di_upload_two_bank_src
			* @author	Eran Rebenshtok
			* @date 	20/05/2021
			* @brief	Verify a QMAN task for multidimensional upload transfer from two bank.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_multi_di_upload_two_bank_src(T_QMAN_task_descriptor *task_descriptor ) PRAGMA_CSECT("CSL_CODE_SECTION");


		#endif /* ((defined XM6) || (defined XM4)) */



		#if (defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && defined(XM6))


			/*********************************************************************************************
			* @function	QMAN_verify_image_upload
			* @author	Anat Keidar
			* @date 	08/03/2021
			* @brief	Verify a QMAN task for image upload transfer.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_image_upload(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");





			/*********************************************************************************************
			* @function	QMAN_verify_image_download
			* @author	Anat Keidar
			* @date 	08/03/2021
			* @brief	Verify a QMAN task for image download transfer.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_image_download(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");






			/*********************************************************************************************
			* @function	QMAN_verify_image_internal
			* @author	Anat Keidar
			* @date 	11/03/2021
			* @brief	Verify a QMAN task for internal image transfer.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code.
			*********************************************************************************************/
				E_csl_status QMAN_verify_image_internal(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");



		#endif // defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && defined(XM6))
	
	#endif // ifndef CEVABX
	#ifdef CSL_BMAN_SUPPORTED

			/*********************************************************************************************
			*********************************************************************************************
			*********************************************************************************************
			*
			*	QMAN BMAN Functions
			*
			*********************************************************************************************
			*********************************************************************************************
			*********************************************************************************************/




			/*********************************************************************************************
			* @function	QMAN_verify_bman_task
			* @author	Anat Keidar
			* @date 	26/10/2021
			* @brief	Verify a QMAN task for linear BMAN transfer.
			* @param	task_descriptor: Pointer to a QMAN task descriptor.
			* @return	CSL_SUCCESS or CSL failure code
			*********************************************************************************************/
			E_csl_status QMAN_verify_bman_task(T_QMAN_task_descriptor *task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");


	#endif /* CSL_BMAN_SUPPORTED */




#else // (CSL_ASSRTIONS == CSL_CONFIG_DISABLED)


	#define QMAN_verify_addresses(_task_descriptor )  CSL_SUCCESS
	#define QMAN_verify_message_upload(_task_descriptor )  	CSL_SUCCESS
	#define QMAN_verify_message_download(_task_descriptor ) CSL_SUCCESS
	#define QMAN_verify_linear_upload(_task_descriptor )  	CSL_SUCCESS
	#define QMAN_verify_linear_download(_task_descriptor )  CSL_SUCCESS
	#define QMAN_verify_linear_internal(_task_descriptor )  CSL_SUCCESS
	#ifndef CEVABX   
		#define QMAN_verify_linear_internal_one_bank_src(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_internal_one_bank_dst(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_download_one_bank_dst(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_upload_one_bank_src(_task_descriptor )  	CSL_SUCCESS
		#define QMAN_verify_linear_internal_two_bank_src(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_internal_two_bank_dst(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_download_two_bank_dst(_task_descriptor ) CSL_SUCCESS
		#define QMAN_verify_linear_upload_two_bank_src(_task_descriptor )  	CSL_SUCCESS
		#define QMAN_verify_multi_di_upload(_task_descriptor )  	CSL_SUCCESS
		#define QMAN_verify_multi_di_download(_task_descriptor )  	CSL_SUCCESS
		#define QMAN_verify_multi_di_internal(_task_descriptor )  	CSL_SUCCESS
		#define QMAN_verify_multi_di_internal_one_bank_src(_task_descriptor )  CSL_SUCCESS
		#define QMAN_verify_multi_di_internal_one_bank_dst(_task_descriptor )  CSL_SUCCESS
		#define QMAN_verify_multi_di_download_one_bank_dst(_task_descriptor )  CSL_SUCCESS
		#define QMAN_verify_multi_di_upload_one_bank_src(_task_descriptor )  	CSL_SUCCESS
		#if ((defined XM6) || (defined XM4))
			#define QMAN_verify_multi_di_internal_two_bank_src(_task_descriptor )  CSL_SUCCESS
			#define QMAN_verify_multi_di_internal_two_bank_dst(_task_descriptor )  CSL_SUCCESS
			#define QMAN_verify_multi_di_download_two_bank_dst(_task_descriptor )  CSL_SUCCESS
			#define QMAN_verify_multi_di_upload_two_bank_src(_task_descriptor )  	CSL_SUCCESS
		#endif // ((defined XM6) || (defined XM4))
		#if defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && (defined(XM6) || defined(SENSPRO))
			#define QMAN_verify_image_upload(_task_descriptor )  	CSL_SUCCESS
			#define QMAN_verify_image_download(_task_descriptor )  	CSL_SUCCESS
			#define QMAN_verify_image_internal(_task_descriptor )  	CSL_SUCCESS
		#endif // defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && (defined(XM6) || defined(SENSPRO))
	#else /* CEVABX */
		#define QMAN_verify_bman_task(_task_descriptor )  	CSL_SUCCESS
	#endif /* !CEVABX */

#endif // (CSL_ASSRTIONS == CSL_CONFIG_ENABLED)



/*********************************************************************************************
* @function	QMAN_update_linear_transfer_size
* @author	Anat Keidar
* @date 	04/03/2021
* @brief	Update linear transfer size and verify the task.
* @param	task_descriptor: 	Pointer to a QMAN task descriptor.
* @param	transfer_size: 		The size of the transfer in bytes
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status QMAN_update_linear_transfer_size(T_QMAN_task_descriptor *task_descriptor, uint32_t transfer_size) PRAGMA_CSECT("CSL_CODE_SECTION");





#ifndef CEVABX

	/*********************************************************************************************
	* @function	QMAN_update_multi_di_transfer_size
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update multidimensional transfer size and verify the task.
	* @param	task_descriptor: 	Pointer to a QMAN task descriptor.
	* @param	tile_width: 		Tile width in byes
	* @param	tile_height: 		Number of lines
	* @param	num_planes: 		Number of planes
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	#if ( defined(XM4) && (CEVA_DSP_RTL < 120) )
		E_csl_status QMAN_update_multi_di_transfer_size(T_QMAN_task_descriptor *task_descriptor, uint16_t tile_width, uint16_t tile_height)  PRAGMA_CSECT("CSL_CODE_SECTION");
	#else /* ( defined(XM4) && CEVA_DSP_RTL < 120 ) */
		E_csl_status QMAN_update_multi_di_transfer_size(T_QMAN_task_descriptor *task_descriptor, uint16_t tile_width, uint16_t tile_height, uint16_t num_planes)  PRAGMA_CSECT("CSL_CODE_SECTION");
	#endif /* !( defined(XM4) && CEVA_DSP_RTL < 120 ) */






	/*********************************************************************************************
	* @function	QMAN_update_multi_di_stride
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update multidimensional transfer stride and verify the task.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @param	src_line_stride: 		Number of bytes to the next line in the source
	* @param	src_plane_stride: 		Number of bytes to the next plane in the source
	* @param	dst_line_stride: 		Number of bytes to the next line in the destination
	* @param	dst_plane_stride: 		Number of bytes to the next plane in the destination
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	#if ( defined(XM4) && (CEVA_DSP_RTL < 120) )
		E_csl_status QMAN_update_multi_di_stride(T_QMAN_task_descriptor *task_descriptor, uint16_t src_line_stride, uint16_t dst_line_stride) PRAGMA_CSECT("CSL_CODE_SECTION");
	#else /* ( defined(XM4) && CEVA_DSP_RTL < 120 ) */
		E_csl_status QMAN_update_multi_di_stride(T_QMAN_task_descriptor *task_descriptor, uint16_t src_line_stride, uint32_t src_plane_stride, uint16_t dst_line_stride, uint32_t dst_plane_stride) PRAGMA_CSECT("CSL_CODE_SECTION");
	#endif /* !( defined(XM4) && CEVA_DSP_RTL < 120 ) */


#endif /* !defined( CEVABX ) */



#if (defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && defined(XM6))


	/*********************************************************************************************
	* @function	QMAN_update_image_transfer_size
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update image transfer size and verify the task.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @param	tile_width: 		Tile width in byes
	* @param	tile_height: 		Number of lines
	* @param	num_planes: 		Number of planes
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_update_image_transfer_size(T_QMAN_task_descriptor *task_descriptor, uint16_t tile_width, uint16_t tile_height, uint16_t num_planes) PRAGMA_CSECT("CSL_CODE_SECTION");






	/*********************************************************************************************
	* @function	QMAN_update_image_tile_size
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update image tile size and verify the task.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @param	tile_width: 		Tile width in byes
	* @param	tile_height: 		Number of lines
	* @param	num_planes: 		Number of planes
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
		E_csl_status QMAN_update_image_tile_size(T_QMAN_task_descriptor *task_descriptor, uint16_t tile_width, uint16_t tile_height) PRAGMA_CSECT("CSL_CODE_SECTION");






	/*********************************************************************************************
	* @function	QMAN_update_image_source
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update image source and verify the task.
	* @param	task_descriptor: 		Pointer to a QMAN task descriptor.
	* @param	source_image: 			The address of the source image
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_update_image_source(T_QMAN_task_descriptor *task_descriptor, uint32_t source_image) PRAGMA_CSECT("CSL_CODE_SECTION");






	/*********************************************************************************************
	* @function	QMAN_update_image_destination
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update image destination and verify the task.
	* @param	task_descriptor:		Pointer to a QMAN task descriptor.
	* @param	destination_image: 		The address of the destination image
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_update_image_destination(T_QMAN_task_descriptor *task_descriptor, uint32_t destination_image) PRAGMA_CSECT("CSL_CODE_SECTION");






	/*********************************************************************************************
	* @function	QMAN_update_image_stride
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Update image transfer stride and verify the task.
	* @param	task_descriptor: Pointer to a QMAN task descriptor.
	* @param	src_line_stride: 		Number of bytes to the next line in the source
	* @param	src_plane_stride: 		Number of bytes to the next plane in the source
	* @param	dst_line_stride: 		Number of bytes to the next line in the destination
	* @param	dst_plane_stride: 		Number of bytes to the next plane in the destination
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_update_image_stride(T_QMAN_task_descriptor *task_descriptor, uint16_t src_line_stride, uint32_t src_plane_stride, uint16_t dst_line_stride, uint32_t dst_plane_stride) PRAGMA_CSECT("CSL_CODE_SECTION");





	/*********************************************************************************************
	* @function	QMAN_enqueue_image_task
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief	Set the given parameters in the image transfer task push and enable task execution.
	* @param	qman_id	- QMAN allocation did
	* @param	task_descriptor:		Pointer to a QMAN task descriptor.
	* @param	src_x, src_y, src_z: 	Source coordinates
	* @param	dst_x, dst_x, dst_x: 	Destination coordinates
	* @return	CSL_SUCCESS or CSL failure code.
	*********************************************************************************************/
	E_csl_status QMAN_enqueue_image_task(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor,
			int16_t src_x, int16_t src_y, int16_t src_z,
			int16_t dst_x, int16_t dst_y, int16_t dst_z) PRAGMA_CSECT("CSL_CODE_SECTION");
		
		
#endif // if defined(CSL_QMAN_VIRTUAL_DESCRIPTOR) && defined(XM6))






/*********************************************************************************************
 * @function	QMAN_enqueue_sync_point
 * @author	Anat Keidar
 * @date 	04/03/2021
 * @brief	Push the next sync task descriptor for the given queue and enable the task execution.
 * @params	r0: qman_id 	- QMAN allocation ID
 * @params	r1: p_sync_counter - Pointer to sync value - will be set with the new sync counter value
 * @return	CSL_SUCCESS or CSL failure code.
 *********************************************************************************************/
E_csl_status QMAN_enqueue_sync_point(T_csl_allocation_id qman_id, uint32_t* p_sync_counter) PRAGMA_CSECT("CSL_CODE_SECTION");




#if ( defined(XM4) && ( CEVA_DSP_RTL < 120 ) )

	/*********************************************************************************************
	* @function	QMAN_enqueue_task
	* @author	Anat Keidar
	* @date 	04/03/2021
	* @brief: Pushes a given task descriptor to the queue (by direct write to the queue) and executes the task.
	*		If QMAN_WAIT_WHILE_QMAN_BUSY is enabled waits for the QMAN to send that task to the DMA.
	* @params	r0: qman_id 			- QMAN allocation ID
	* @params	r1: p_task_descriptor 	- Pointer to a configured QMAN task descriptor
	* @params	r2: src					- The transfer task source address
	* @params	r3: dst 				- The transfer task destination address
	* @return	CSL_SUCCESS or CSL failure code.
	* *********************************************************************************************/
	E_csl_status QMAN_enqueue_task(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor, uint32_t* src, uint32_t* dst) PRAGMA_CSECT("CSL_CODE_SECTION");


#else /* !( defined(XM4) && CEVA_DSP_RTL < 120 ) */

	/*********************************************************************************************
	 * @function	QMAN_enqueue_task
	 * @author	Anat Keidar
	 * @date 	01/11/2021
	 * @brief: Pushes a given task descriptor to the queue (by direct write to the queue) and executes the task.
	 *		If QMAN_WAIT_WHILE_QMAN_BUSY is enabled waits for the QMAN to send that task to the DMA.
	 * @params	r0: qman_id 			- QMAN allocation ID
	 * @params	r1: p_task_descriptor 	- Pointer to a configured QMAN task descriptor
	 * @return	CSL_SUCCESS or CSL failure code.
	 * *********************************************************************************************/

	E_csl_status QMAN_enqueue_task(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");



#endif  /* ( defined(XM4) && CEVA_DSP_RTL < 120 ) */

#if ( defined(SENSPRO) || defined(CEVABX) )

	/*********************************************************************************************
	 * @function	QMAN_push_task
	 * @author	Anat Keidar
	 * @date 	01/11/2021
	 * @brief: Pushes a given task descriptor to the queue (by direct write to the queue).
	 * @params	r0: qman_id 			- QMAN allocation ID
	 * @params	r1: p_task_descriptor 	- Pointer to a configured QMAN task descriptor
	 * @return	CSL_SUCCESS or CSL failure code.
	 * *********************************************************************************************/

		E_csl_status QMAN_push_task(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");

#endif /* defined(SENSPRO) || defined(CEVABX) */



 /*********************************************************************************************
 *********************************************************************************************
 *
 *	QMAN Frame Support
 *
 *********************************************************************************************
 *********************************************************************************************/




/*********************************************************************************
 * @function	QMAN_push_frame_start
 * @author	Anat Keidar
 * @date 	01/12/2021
 * @brief	Push the first task in a tasks frame of the given length. This should be followed by QMAN_push_frame_mid and completed with QMAN_push_frame_end
 * @param	qman_id: 			QMAN allocation ID
 * @param	p_task_descriptor: 	Pointer to the first task descriptor in the frame
 * @param	frame_length: 		The number of tasks in the frame
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_push_frame_start(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor, uint16_t frame_length) PRAGMA_CSECT("CSL_CODE_SECTION");





/*********************************************************************************
 * @function	QMAN_push_frame_mid
 * @author	Anat Keidar
 * @date 	01/12/2021
 * @brief	Push a task in the mid of the current tasks frame. This should be proceeded by QMAN_push_frame_start and followed by QMAN_push_frame_end to complete the frame.
 * @param	qman_id: 			QMAN allocation ID
 * @param	p_task_descriptor: 	Pointer to the a task descriptor in the middle of the frame
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_push_frame_mid(T_csl_allocation_id qman_id, T_QMAN_task_descriptor *p_task_descriptor) PRAGMA_CSECT("CSL_CODE_SECTION");




/*********************************************************************************
 * @function	QMAN_push_frame_end
 * @author	Anat Keidar
 * @date 	01/12/2021
 * @brief	End the current tasks frame: enable the frame execution. This should be proceeded by QMAN_push_frame_mid.
 * @param	qman_id: 			QMAN allocation ID
 * @return	CSL_SUCCESS or CSL failure code
**********************************************************************************/
E_csl_status QMAN_push_frame_end(T_csl_allocation_id qman_id) PRAGMA_CSECT("CSL_CODE_SECTION");










CSL_CPP_END




#endif /* CSL_QMAN_SUPPORTED */
#endif /* CEVA_QMAN_TASK_DESCRIPTOR_H_ */
