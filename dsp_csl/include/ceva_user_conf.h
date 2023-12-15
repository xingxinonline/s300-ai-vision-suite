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
#ifndef CEVA_USER_CONF_H_
#define CEVA_USER_CONF_H_
/*********************************************************************************************
 * File:            ceva_user_conf.h
 * Created on:      25/01/2020
 * Author:          Anat Keidar
 * Description:     This header contains all definition which are configurable by the CSL user:
 *                      - Hardware configuration
 *                      - Assertions configuration
**********************************************************************************************/
#include "ceva_aux.h"


/*********************************************************************************************
 *********************************************************************************************
 *
 *  CSL Backward Compatibility
 *
 *********************************************************************************************
 *********************************************************************************************
 *  Defining _BACKWARD_COMPATIBILITY will compile the code to support the CSL version prior
 *      to the CSL 01/05/2021 release
 *********************************************************************************************/




/*********************************************************************************************
 *********************************************************************************************
 *
 *  Assertion Configuration
 *
 *********************************************************************************************
 *********************************************************************************************
 *                          ***     IMPORTANT    ***
 *
 *   The configuration the CSL assertions effect the efficiency vs. safety.
 *
 *   It is the responsibility of the user to define the assertion behavior to meet his needs.
 *
 *********************************************************************************************/

#ifndef CEVA
    #if defined(_DEBUG)
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_ENABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_ENABLED
    #else
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_DISABLED
    #endif
#else /* !CEVA */
    #if defined(_DEBUG) || defined(_DMA_API_CHECK_)
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_ENABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_ENABLED
    #elif defined(_RELEASE) ||  defined(_RELEASE_HIGH_PERFORMANCE)
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_DISABLED
    #elif defined _RELEASE_SAFETY
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_ENABLED
    #else
        #define CSL_USER_CONF_ASSERT_PRINT                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_TRAPE                          CSL_CONFIG_DISABLED
        #define CSL_USER_CONF_ASSERT_SET_CODE                       CSL_CONFIG_DISABLED
    #endif
#endif /* CEVA */

/*********************************************************************************************
 *  Individual assertion may be disabled, per assertion type or per unit by setting the
 *  corresponding configuration. When
 *  By default all assertions are enabled.
 *********************************************************************************************/

#define CSL_USER_CONF_SUPPORT_MULTI_PROCESS_ENVIRONEMENT            CSL_CONFIG_DISABLED

// Assert Type
#define CSL_USER_CONF_ASSERT_TYPE_INVALID_ALLOCATION_ID             CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_READ_AFTER_WRITE_FAIL             CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_DSP_NOT_READY                     CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_INVALID_PARAMETER                 CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_ALLOCATION_FAILURE                CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_DMA_SIMUL_OPERATION_FAILED        CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_CPM_READ_UNEXPECTED_VALUE         CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_INVALID_OPRATION                  CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_TYPE_INVALID_COMPILATION               CSL_CONFIG_DISABLED

// Assert Unit
#define CSL_USER_CONF_ASSERT_UNIT_DMSS                      CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_PMSS                      CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_QMAN                      CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_TIMER                     CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_WATCHDOG                  CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_ICU                       CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_HWEXPT                    CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_PROFILER                  CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_SAFETY                    CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_CSL                       CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_HW_CONF                   CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_MCCI                      CSL_CONFIG_DISABLED
#define CSL_USER_CONF_ASSERT_UNIT_GPIO                      CSL_CONFIG_DISABLED
#ifdef CEVABX
    #define CSL_USER_CONF_ASSERT_UNIT_DC                        CSL_CONFIG_ENABLED
    #define CSL_USER_CONF_ASSERT_UNIT_BMAN                      CSL_CONFIG_ENABLED
#endif /* CEVABX */


/*
 * CSL_MULTI_PROCESS_ENVIRONEMENT
 *      This define should be enabled when executing in a multi-process environment.
 *      Enabling this protection will add CSL support in critical sections.
 */
#ifdef CEVA
    #define CSL_MULTI_PROCESS_ENVIRONEMENT      CSL_USER_CONF_SUPPORT_MULTI_PROCESS_ENVIRONEMENT
#else
    #define CSL_MULTI_PROCESS_ENVIRONEMENT      CSL_CONFIG_DISABLED
#endif


/*********************************************************************************************
 *********************************************************************************************
 *
 *  QMAN Configurations
 *
 *********************************************************************************************/


/*
 * QMAN_WAIT_WHILE_QMAN_BUSY
 *      When enabled the CSL waits after a QMAN task execution for the QMAN to not be busy.
 */
#if !( defined( SNESPRO1000 ) || defined( SNESPRO500 ) || defined( SNESPRO250 ) || defined( SNESPRO100 ) )
    #define QMAN_WAIT_WHILE_QMAN_BUSY           CSL_CONFIG_ENABLED
#else
    #define QMAN_WAIT_WHILE_QMAN_BUSY           CSL_CONFIG_DISABLED
#endif



#endif /*CEVA_USER_CONF_H_*/
