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
#ifndef CEVA_ASSERT_H
#define CEVA_ASSERT_H
/*********************************************************************************************
 * File:			cava_assert.h
 * Created on: 		26/01/2021
 * Author: 			Anat Keidar
 * Description: 	CSL assertions definitions for safety verifications and report.
 **********************************************************************************************/
#include "ceva_user_conf.h"



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	CSL Assert Structure Definitions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/
 
 /*
  * If all assert operations are disabled then the CSL_ASSRTIONS is disabled.
  * */
 #define CSL_ASSRTIONS (CSL_USER_CONF_ASSERT_PRINT | CSL_USER_CONF_ASSERT_TRAPE | CSL_USER_CONF_ASSERT_SET_CODE)



/*********************************************************************************************
 * CSL critical section definitions
 * Description: The following definitions are used to declare entering and exiting a critical section.
 * 				CSL_ENTER_CRITICAL_SECTION:		Should be used at the beginning of a critical section.
 * 				CSL_EXIT_CRITICAL_SECTION: 		Should be used at the end of a critical section.
 *********************************************************************************************/


	/*
	 * csl_in_critical_section
	 * 	Mechanism to support assertions inside a critical section
	 *
	 */
#if defined( SENSPRO ) && defined(CEVA)
	void csl_enter_critical_section( void ) PRAGMA_CSECT("CSL_CODE_SECTION") __attribute__( ( naked ) );
	void csl_exit_critical_section( void ) PRAGMA_CSECT("CSL_CODE_SECTION") __attribute__( ( naked ) );
#endif /* SENSPRO */    

#if (CSL_MULTI_PROCESS_ENVIRONEMENT == CSL_CONFIG_ENABLED) && defined(SENSPRO)

	#define CSL_ENTER_CRITICAL_SECTION	csl_enter_critical_section();

	#define CSL_EXIT_CRITICAL_SECTION	csl_exit_critical_section();



#else /* !((CSL_MULTI_PROCESS_ENVIRONEMENT == CSL_CONFIG_ENABLED) && defined(SENSPRO)) */


	#define CSL_ENTER_CRITICAL_SECTION

	#define CSL_EXIT_CRITICAL_SECTION



#endif /* (CSL_MULTI_PROCESS_ENVIRONEMENT == CSL_CONFIG_ENABLED) && defined(SENSPRO) */


 
 
 
/*********************************************************************************************
 * @name	E_csl_status
 * @brief	E_csl_status defines the CSL SW reported failures.
 * 			Function: Each failure is reported in two symmetric bits (in the higher and lower part of the 32bits value)
 *
 *			Activation: If CSL_USER_CONF_ASSERT_SET_CODE is CSL_CONFIG_ENABLED the CSL assert code is set.
 *						Each assertion can be individually disabled in the ceva_user_conf.h file.
 *
 *			Getting the failure code: The user can get the status by calling CSL_get_assert_failure_code()
 *					which returns a 64 bits value where the lower 32 bits are the failure type code
 *					and the height 32 bits are the failure source unit code.
 *					The code is then cleared.
 *			Naming:
 *				CSL_ASSERT_CODE_TYPE_<DESCRIPTION> describes the failure.
 *				CSL_ASSERT_CODE_UNIT_<SOURCE_UNIT> describes the unit which initiated the assertion.
 *
 *			Adding new failure code:
 *				Use one of the free spots: CSL_ASSERT_CODE_UNIT_UNDEFINED_##
 *				Replace it with the new unit name: CSL_ASSERT_CODE_UNIT_<SOURCE_UNIT>
 *				Define and use the corresponding define in ceva_user_config.h: CSL_USER_CONF_ASSERT_UNIT_<NAME>
 *				Add the unit name in assert.c in the corresponding slot
 **********************************************************************************************/


/*
 * Invalid values
 * */
#define CSL_VALUES_UNINITIALIZED 0xFFFFFFFFU

/* Assertion Code */
/*****************/

#define CSL_USER_CONF_ASSERT_UNDEFINED 					0
#define CSL_ASSERT_NUMBER_OF_CATEGORIES					2 /* Two assert code categories defined: Type and Unit */
#define CSL_ASSERT_CATEGORY_TYPE_INDEX					0
#define CSL_ASSERT_CATEGORY_UNIT_INDEX					1
#define CSL_ASSERT_NUMBER_OF_ASSERTIONS	 				15
#define CSL_ASSERT_MESSAGE_LENGTH						50

/*
 * Category: Failure types
 * */
typedef enum
{
	CSL_SUCCESS										= 0x00000000U,
	CSL_FAILURE										= 0x00008000U,
	CSL_ASSERT_CODE_TYPE_READ_AFTER_WRITE_FAIL		= (0x00010001U*CSL_USER_CONF_ASSERT_TYPE_READ_AFTER_WRITE_FAIL),
	CSL_ASSERT_CODE_TYPE_DSP_NOT_READY				= (0x00020002U*CSL_USER_CONF_ASSERT_TYPE_DSP_NOT_READY),
	CSL_ASSERT_CODE_TYPE_INVALID_PARAMETER			= (0x00040004U*CSL_USER_CONF_ASSERT_TYPE_INVALID_PARAMETER),
	CSL_ASSERT_CODE_TYPE_ALLOCATION_FAILURE			= (0x00080008U*CSL_USER_CONF_ASSERT_TYPE_ALLOCATION_FAILURE),
	CSL_ASSERT_CODE_TYPE_INVALID_ALLOCATION_ID		= (0x00100010U*CSL_USER_CONF_ASSERT_TYPE_INVALID_ALLOCATION_ID),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_6				= (0x04000020U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_7				= (0x04000040U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_CPM_READ_UNEXPECTED_VALUE	= (0x00800080U*CSL_USER_CONF_ASSERT_TYPE_CPM_READ_UNEXPECTED_VALUE),
	CSL_ASSERT_CODE_TYPE_INVALID_OPERATION			= (0x01000100U*CSL_USER_CONF_ASSERT_TYPE_INVALID_OPRATION),
	CSL_ASSERT_CODE_TYPE_INVALID_COMPILATION		= (0x02000200U*CSL_USER_CONF_ASSERT_TYPE_INVALID_COMPILATION),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_11				= (0x04000400U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_12				= (0x08000800U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_13				= (0x10001000U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_14				= (0x30002000U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ASSERT_CODE_TYPE_UNDEFINED_15				= (0x70004000U*CSL_USER_CONF_ASSERT_UNDEFINED),
	CSL_ALLOCATION_FAILURE							= 0x7FFFFFFFU
}E_csl_status;


/*
 * Category: Failure source
 * */
#define CSL_ASSERT_CODE_UNIT_DMSS				        ( uint32_t )(0x00010001U*CSL_USER_CONF_ASSERT_UNIT_DMSS)
#define CSL_ASSERT_CODE_UNIT_PMSS				        ( uint32_t )(0x00020002U*CSL_USER_CONF_ASSERT_UNIT_PMSS)
#define CSL_ASSERT_CODE_UNIT_QMAN				        ( uint32_t )(0x00040004U*CSL_USER_CONF_ASSERT_UNIT_QMAN)
#define CSL_ASSERT_CODE_UNIT_TIMER				        ( uint32_t )(0x00080008U*CSL_USER_CONF_ASSERT_UNIT_TIMER)
#define CSL_ASSERT_CODE_UNIT_ICU				        ( uint32_t )(0x00100010U*CSL_USER_CONF_ASSERT_UNIT_ICU)
#define CSL_ASSERT_CODE_UNIT_HWEXPT				        ( uint32_t )(0x00200020U*CSL_USER_CONF_ASSERT_UNIT_HWEXPT)
#define CSL_ASSERT_CODE_UNIT_PROFILER			        ( uint32_t )(0x00400040U*CSL_USER_CONF_ASSERT_UNIT_PROFILER)
#define CSL_ASSERT_CODE_UNIT_WATCHDOG			        ( uint32_t )(0x00800080U*CSL_USER_CONF_ASSERT_UNIT_WATCHDOG)
#define CSL_ASSERT_CODE_UNIT_SAFETY			            ( uint32_t )(0x01000100U*CSL_USER_CONF_ASSERT_UNIT_SAFETY)
#define CSL_ASSERT_CODE_UNIT_CSL			            ( uint32_t )(0x02000200U*CSL_USER_CONF_ASSERT_UNIT_CSL)
#define CSL_ASSERT_CODE_UNIT_HW_CONF					( uint32_t )(0x04000400U*CSL_USER_CONF_ASSERT_UNIT_HW_CONF)
#define CSL_ASSERT_CODE_UNIT_MCCI						( uint32_t )(0x08000800U*CSL_USER_CONF_ASSERT_UNIT_MCCI)
#define CSL_ASSERT_CODE_UNIT_GPIO						( uint32_t )(0x10001000U*CSL_USER_CONF_ASSERT_UNIT_GPIO)
#ifdef CEVABX
	#define CSL_ASSERT_CODE_UNIT_DC						( uint32_t )(0x30002000U*CSL_USER_CONF_ASSERT_UNIT_DC)
	#define CSL_ASSERT_CODE_UNIT_BMAN					( uint32_t )(0x70004000U*CSL_USER_CONF_ASSERT_UNIT_BMAN)
#else /* ifdef CEVABX */
	#define CSL_ASSERT_CODE_UNIT_UNDEFINED_14			( uint32_t )(0x88002000U*CSL_USER_CONF_ASSERT_UNDEFINED)
	#define CSL_ASSERT_CODE_UNIT_UNDEFINED_15			( uint32_t )(0x90004000U*CSL_USER_CONF_ASSERT_UNDEFINED)
#endif /* else ifdef CEVABX */





#if (CSL_USER_CONF_ASSERT_SET_CODE == CSL_CONFIG_ENABLED) || (CSL_USER_CONF_ASSERT_PRINT == CSL_CONFIG_ENABLED)
	/*********************************************************************************************
	* @function	CSL_set_assert_failure_code
	* @author	Anat Keidar
	* @date 	08/03/2021
	* @brief	Set the given code type and source unit code.
	* @param	csl_asset_code_type:	CSL status failure type code
	* @param	csl_asset_code_unit:	CSL status failure source unit code
	*********************************************************************************************/
	void CSL_set_assert_failure_code(uint32_t csl_asset_code_unit, E_csl_status csl_asset_code_type) PRAGMA_CSECT("CSL_CODE_SECTION");



	 /*********************************************************************************************
	 * @function	CSL_get_assert_failure_code_type
	 * @author	Anat Keidar
	 * @date 	08/03/2021
	 * @brief	Get the CSL failure type code
	 * @return	Failure type code
	 *********************************************************************************************/
	uint32_t CSL_get_assert_failure_code_type(void) PRAGMA_CSECT("CSL_CODE_SECTION");
	 /*********************************************************************************************
	 * @function	CSL_get_assert_failure_code_unit
	 * @author	Anat Keidar
	 * @date 	08/03/2021
	 * @brief	Get the CSL failure source unit code
	 * @return	Failure type code
	 *********************************************************************************************/
	uint32_t CSL_get_assert_failure_code_unit(void) PRAGMA_CSECT("CSL_CODE_SECTION");

	char* CSL_get_assert_failure_message(uint8_t message_num) PRAGMA_CSECT("CSL_CODE_SECTION");
	char* CSL_get_assert_unit_message(uint8_t message_num) PRAGMA_CSECT("CSL_CODE_SECTION");

#else /*  (CSL_USER_CONF_ASSERT_SET_CODE == CSL_CONFIG_ENABLED) || (CSL_USER_CONF_ASSERT_PRINT == CSL_CONFIG_ENABLED) */


	#define CSL_set_assert_failure_code(_csl_asset_code_type, _csl_asset_code_unit)


	/*********************************************************************************************
	* @function	CSL_get_assert_failure_code
	* @author	Anat Keidar
	* @date 	08/03/2021
	* @brief	Get the CSL failure status which returns a 64 bits value,
	* 			where the lower 32 bits are the failure type code
	*			and the height 32 bits are the failure source unit code.
	*			The code is then cleared.
	* @param	core_type	The target core type
	* @return	64 bits value where the lower 32 bits are the failure type code
	* 			and the height 32 bits are the failure source unit code.
	*********************************************************************************************/
	#define CSL_get_assert_failure_message(_message_num) ""
	#define CSL_get_assert_unit_message(_message_num) ""

#endif







/*********************************************************************************************
 * CSL Allocation definition service
 * Description: The following definitions are used to support the CSL resource mechanism.
 * 				CSL_ASSERT_CODE_TYPE_INVALID_ALLOCATION_ID enabled: allocation is assigned with a UUID
 * 				CSL_ASSERT_CODE_TYPE_INVALID_ALLOCATION_ID disabled: allocation is indicated with true of false only
 *********************************************************************************************/
#define CSL_RESOURCE_NOT_ALLOCATED							0xFFFFFFFFU

/* 	CSL_ALLOCATION_ID_RESET - Used as the reset value of the CSL allocation UUID */
#define CSL_ALLOCATION_ID_RESET 							0x00030000U

/* 	CSL_GET_RESOURCE_NUM - returns the hardware number of the resource from the allocation UUID */
#define CSL_GET_RESOURCE_NUM(_allocation_id)				((uint16_t)(((uint32_t)_allocation_id) & 0x0000FFFFU))

#define CSL_UNIT_ALLOCATION_ID_CREATE_NEXT(_csl_unit_allocation_id)	 	(_csl_unit_allocation_id += ( uint32_t )0x00020000U)



#define CSL_IS_RESOUCE_ALLOCATED(_allocated, _allocation_id)			((_allocated == _allocation_id) && (CSL_RESOURCE_NOT_ALLOCATED != _allocated))


#define CSL_SIZEOF_REGISTER_GROUP(_register_group) 							sizeof(_register_group)


#define CSL_START_CODE ( ( uint32_t )0x03E701E2U )


typedef uint32_t T_csl_allocation_id;






/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	CSL Assertions Definition
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/


/*********************************************************************************************
 * @name	CSL_ASSERT_PRINT
 * @type	macro
 * @brief	CSL_ASSERTs will display a message to the consul if CSL_USER_CONF_ASSERT_PRINT is CSL_CONFIG_ENABLED
 **********************************************************************************************/
#if (CSL_USER_CONF_ASSERT_PRINT == CSL_CONFIG_ENABLED)
	#include <stdio.h>
	char* CSL_get_assert_failure_message(uint8_t message_num) PRAGMA_CSECT("CSL_CODE_SECTION");
	#define CSL_ASSERT_PRINT(_csl_asset_code_unit, _func_name, _csl_asset_code_type) \
			printf("CSL Error: %s: %s: %s \n", CSL_get_assert_unit_message(ceva_ffb(_csl_asset_code_unit)), _func_name, CSL_get_assert_failure_message(ceva_ffb(_csl_asset_code_type)) );
#else
	#define CSL_ASSERT_PRINT(_csl_asset_code_unit, _func_name, _csl_asset_code_type)
#endif


/*********************************************************************************************
 * @name	CSL_ASSERT_TRAP
 * @type	macro
 * @brief	CSL_ASSERTs will execute the trap if CSL_USER_CONF_ASSERT_TRAP is CSL_CONFIG_ENABLED
 **********************************************************************************************/
#if (CSL_USER_CONF_ASSERT_TRAPE == CSL_CONFIG_ENABLED)

	/* trape is not supported in the simulator in release mode */
	#define CSL_ASSERT_TRAP	__asm__ volatile( "trape\n nop" );

#else /* trape disabled */
	#define CSL_ASSERT_TRAP
#endif

/*********************************************************************************************
 * @name	CSL_USER_CONF_ASSERT_SET_CODE
 * @type	macro
 * @brief	CSL_ASSERTs will set the CSL_ASSERT_CODE in the g_csl_assert_failure_code with an or operation.
 **********************************************************************************************/
#if (CSL_USER_CONF_ASSERT_SET_CODE == CSL_CONFIG_ENABLED)
	#define CSL_ASSERT_SET_CODE(_csl_asset_code_unit, _csl_asset_code)	CSL_set_assert_failure_code(_csl_asset_code_unit, _csl_asset_code);
#else
	#define CSL_ASSERT_SET_CODE(_csl_asset_code_unit, _csl_asset_code)
#endif


/*********************************************************************************************
 * @name	CSL_ASSERT
 * @type	macro_group
 * @brief	Assert will execute if the given type assertion code is CSL_CONFIG_ENABLED
 *			Assert will execute if the given unit assertion code is CSL_CONFIG_ENABLED
 *			Assert will display the assert message if CSL_USER_CONF_ASSERT_PRINT is CSL_CONFIG_ENABLED
 *			Assert will set CSL assert code in the g_csl_assert_failure_code if CSL_USER_CONF_ASSERT_SET_CODE is CSL_CONFIG_ENABLED
 *			Assert will execute trap if CSL_USER_CONF_ASSERT_TRAP is CSL_CONFIG_ENABLED
 *	@param	_cond: if true the assert is executed.
 *	@param	_func_name: the name of the function which initiated the assertion.
 *	@param  _csl_asset_code_unit: the csl assert unit code (CSL_ASSERT_CODE_UNIT_<UNIT_NAME>)
 *	@param  _csl_asset_code_unit: the csl assert type code (CSL_ASSERT_CODE_TYPE_<ERROR_TYPE>)
 **********************************************************************************************/
#if	(CSL_ASSRTIONS == CSL_CONFIG_ENABLED)

	/*********************************************************************************************
	 * @name	READ_REGISTER
	 * @type	macro
	 * @brief	Read the given CPM register address
	 *
	 **********************************************************************************************/
	#define READ_REGISTER(_cpm_reg_addr) cpm_in(_cpm_reg_addr)


	/*********************************************************************************************
	 * @name	CSL_ASSERT_COND
	 * @type	macro
	 * @brief	Execute all assertion enabled operations
	 *
	 **********************************************************************************************/
	#define CSL_ASSERT_OPERATION(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type) 	\
					CSL_ASSERT_PRINT(_csl_asset_code_unit, _func_name, _csl_asset_code_type); 		\
					CSL_ASSERT_SET_CODE(_csl_asset_code_unit, _csl_asset_code_type); 				\
					CSL_ASSERT_TRAP;

	/*********************************************************************************************
	 * @name	CSL_ASSERT_RET_FAIL_VAL
	 * @type	macro
	 * @brief	Assert will execute if the given condition (_cond) is true
	 * 			The initiating function will return with the given fail value.
	 *
	 **********************************************************************************************/
	#define CSL_ASSERT_RET_FAIL_VAL(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _fail_value) \
			do \
			{ \
				if((_csl_asset_code_unit && _csl_asset_code_type && !(_cond))) \
				{ \
					CSL_ASSERT_OPERATION(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type); \
					CSL_EXIT_CRITICAL_SECTION; \
					return (_fail_value); \
				} \
			} while(0);


	/*********************************************************************************************
	 * @name	CSL_ASSERT_RETVAL
	 * @type	macro
	 * @brief	Assert will execute if the given condition (_cond) is true
	 * 			The initiating function will return with the CSL assert code.
	 *			
	 **********************************************************************************************/
	#define CSL_ASSERT_RETVAL(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type)  \
			CSL_ASSERT_RET_FAIL_VAL(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _csl_asset_code_type);


	/*********************************************************************************************
	 * @name	CSL_ASSERT_RAW_RET_FAIL_VAL
	 * @type	macro
	 * @brief	Assert will will execute if the register is set with the expected value in the masked bits.
	 *			The initiating function will return with the given return value.
	 *			
	 **********************************************************************************************/
	#define CSL_ASSERT_RAW_RET_FAIL_VAL(_register_addr, _reg_expected, _reg_mask, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _fail_value) \
			do \
			{ \
				if((_csl_asset_code_unit && _csl_asset_code_type && ((((uint32_t)_reg_expected) ^ cpm_in(_register_addr)) & _reg_mask))) \
				{ \
					CSL_ASSERT_OPERATION(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type); \
					CSL_EXIT_CRITICAL_SECTION; \
					return _fail_value; \
				} \
			} while(0);


	/*********************************************************************************************
	 * @name	CSL_ASSERT_RAW_RETVAL
	 * @type	macro
	 * @brief	Assert will will execute if the register is set with the expected value in the masked bits.
	 *			The initiating function will return with the CSL assert code.
	 *
	 **********************************************************************************************/
	#define CSL_ASSERT_RAW_RETVAL(_register_addr, _reg_expected, _reg_mask, _func_name, _csl_asset_code_unit, _csl_asset_code_type) \
		CSL_ASSERT_RAW_RET_FAIL_VAL(_register_addr, _reg_expected, _reg_mask, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _csl_asset_code_type);

	/*********************************************************************************************
	 * @name	CSL_ASSERT_FUNC_CALL
	 * @type	macro
	 * @brief	Assert the function execution CSL status
	 *			The initiating function will return the status returned for the function call
	 *
	 **********************************************************************************************/
	#define CSL_ASSERT_FUNC_CALL(_func_call) \
		do \
		{ \
			E_csl_status _status_ = _func_call; \
			if(_status_) return (_status_); \
		} while(0);




#else
	/*********************************************************************************************
	 * when both ((CSL_USER_CONF_ASSERT_PRINT | CSL_USER_CONF_ASSERT_TRAP) == 1)
	 * No action is taken.
	 **********************************************************************************************/
	#define CSL_ASSERT_RETVAL(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type)
	#define CSL_ASSERT_RET_FAIL_VAL(_cond, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _fail_value)
	#define CSL_ASSERT_RAW_RETVAL(_register_addr, _reg_expected, _reg_mask, _func_name, _csl_asset_code_unit, _csl_asset_code_type)
	#define CSL_ASSERT_RAW_RET_FAIL_VAL(_register_addr, _reg_expected, _reg_mask, _func_name, _csl_asset_code_unit, _csl_asset_code_type, _fail_value)
	#define CSL_ASSERT_FUNC_CALL(_func_call) _func_call
	#define READ_REGISTER(_cpm_reg_addr)

#endif 


#ifdef CEVA

	/*********************************************************************************************
	* @function	CSL_is_it_simulator
	* @author	Ravid Rzaev
	* @date 	28/02/2021
	* @brief	return the indication if the code run in the simulator.
	* @return	CSL_TRUE or CSL_FALSE
	*********************************************************************************************/
	bool CSL_is_it_simulator(void) PRAGMA_CSECT("CSL_CODE_SECTION");



	/*********************************************************************************************
	; @function CSL_is_supervisor (Internal asm)
	; @author  Anat Keidar
	; @date    07/07/2022
	; @brief    True if the DSP is in supervisor mode
	; @return   True if the DSP is in supervisor mode, False if the DSP is in user mode
	*********************************************************************************************/
	bool CSL_is_supervisor(void) PRAGMA_CSECT("CSL_CODE_SECTION");


#endif /* CEVA */






#endif /* CEVA_ASSERT_H */
