/********************************************************************************************************************************************************
Copyright (C) CEVA(R) Inc. All rights reserved

This information embodies materials and concepts, which are proprietary and confidential to CEVA Inc., and is made available solely pursuant to the
terms of a written license agreement, or NDA, or another written agreement, as applicable (閹诲寷VA Agreement閿燂拷), with CEVA Inc. or any of its subsidiaries
(閹诲寷VA閿燂拷).

This information can be used only with the written permission from CEVA, in accordance with the terms and conditions stipulated in the CEVA Agreement,
under which the information has been supplied and solely as expressly permitted for the purpose specified in the CEVA Agreement.
This information is made available exclusively to licensees or parties that have received express written authorization from CEVA to download or receive
the information and have agreed to the terms and conditions of the CEVA Agreement.
IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE CEVA AGREEMENT, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS INFORMATION.

The information contained in this document is subject to change without notice and does not represent a commitment on any part of CEVA. Unless
specifically agreed otherwise in the CEVA Agreement, CEVA make no warranty of any kind with regard to this material, including, but not limited to
implied warranties of merchantability and fitness for a particular purpose whether arising out of law, custom, conduct or otherwise.

While the information contained herein is assumed to be accurate, CEVA assumes no responsibility for any errors or omissions contained herein,
and assumes no liability for special, direct, indirect or consequential damage, losses, costs, charges, claims, demands, fees or expenses, of any nature
or kind, which are incurred in connection with the furnishing, performance or use of this material.

This document contains proprietary information, which is protected by U.S. and international copyright laws. All rights reserved.
No part of this document may be reproduced, photocopied, or translated into another language without the prior written consent of CEVA.
********************************************************************************************************************************************************/


#ifndef _CSL_TEST_H_
#define _CSL_TEST_H_

#include "ceva_csl_defs.h"

#if defined(CEVAXM) && defined(_BACKWARD_COMPATIBILITY)
    #include "ceva_xm_bc/csl.h"
#else // define(CEVAXM) && defined(_BACKWARD_COMPATIBILITY)
    #include "ceva_csl.h"
#endif


#if defined(CSL_TIMERS_SUPPORTED) && (!defined(HW_CONFIG_NUM_TIMERS) || (HW_CONFIG_NUM_TIMERS > 0))
    #define CSL_TESTER_TIMERS_SUPPORTED
#endif
#if defined(CSL_ICU_SUPPORTED) && (!defined(HW_CONFIG_NUM_ICU_GROUPS) || (HW_CONFIG_NUM_ICU_GROUPS > 0))
    #define CSL_TESTER_ICU_SUPPORTED
#endif
#if defined(CSL_QMAN_SUPPORTED) && (!defined(HW_CONFIG_NUM_QMANS) || (HW_CONFIG_NUM_QMANS > 0))
    #define CSL_TESTER_QMAN_SUPPORTED
#endif
#if defined(CSL_BMAN_SUPPORTED) && (!defined(HW_CONFIG_NUM_BMANS) || (HW_CONFIG_NUM_BMANS > 0))
    #define CSL_TESTER_BMAN_SUPPORTED
#endif




#define MEM_BUFF_INTERNAL_SIZE          0x1
#define MEM_BUFF_EXTERNAL_SIZE          0x1
#define MEM_BUFF_EXTERNAL_DBG_SIZE      0x1
#define MEM_BUFF_EXTERNAL_CACHE_SIZE    0x8


// Number of banks per block in the IDM
#ifdef SENSPRO1000
    #define NUMBER_OF_BANKS     32
#elif SENSPRO500
    #define NUMBER_OF_BANKS     16
#elif SENSPRO250
    #define NUMBER_OF_BANKS     8
#elif SENSPRO100
    #define NUMBER_OF_BANKS     4
#elif SENSPRO50
    #define NUMBER_OF_BANKS     2
#else /* SP500 V1.1 */
    #define NUMBER_OF_BANKS     16
#endif


#ifdef SENSPRO
    #define BUFF_ALIGN                      (CSL_HW_CONFIG_BANK_WIDTH * NUMBER_OF_BANKS)
#else
    #define BUFF_ALIGN                      CSL_HW_CONFIG_BLOCK_WIDTH
#endif

// please un-mark to enable
//#define PRINT_PROFILER_INFO

void reset_memory(uint8_t *src, uint32_t size);
void set_memory_inc(uint8_t *dst, uint32_t size);
void set_memory_dec(uint8_t *dst, uint32_t size);

#if ((defined( SENSPRO ) || ( defined( CEVABX )) && (HW_CONFIG_IPM_SIZE != 0 )) )
    E_csl_status HW_EXCPTIONS_move_to_user_mode(void);
    E_csl_status HW_EXCPTIONS_move_to_supervisor_mode(void);
#endif


//#define CSL_TESTER_IS_TRAPE_SUPPORTED (!CSL_is_it_simulator()) // Trape not supported by simulation
#define CSL_TESTER_IS_TRAPE_SUPPORTED CSL_FALSE // Disable trape tests


#endif /* _CSL_TEST_H_ */
