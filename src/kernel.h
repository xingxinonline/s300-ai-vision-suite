/*
 * kernel.h
 *
 *  Created on: 2023年11月29日
 *      Author: xinhao
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "vec-c.h"
#include "csl.h"
#include "csl_test.h"
#include "ceva_csl.h"
#include "ceva_assert.h"
#include "ceva_csl_defs.h"
#include "custom_printf.h"
#include "debug.h"


/*
ICU Group1 0~8 is defined in ceva_icu.h
*  typedef enum
*  {
*      ICU_CRITICAL_NS_ERRORS     = 0,
*      ICU_NORMAL_NS_ERRORS       = 1,
*      ICU_MCCI_NS                = 2,
*      ICU_BMAN_SN_INT_NS         = 3,
*      ICU_DMA_NS                 = 4,
*      ICU_TIMERS_NS_WD           = 5,
*      ICU_TIMERS_NS_EVENT        = 6,
*      ICU_DEBUG_UNIT             = 7,
*      ICU_POSTED_CORE_INTERRUPTS = 8
*  } E_ICU_interrupt_types;
*/
typedef enum
{
    /* ICU Group1 9~31 */
    ICU_EXT_MAILBOX            = 0,
    ICU_EXT_RESERVED1          = 1,
    ICU_EXT_AXI_DMA            = 2,
    ICU_EXT_RESERVED3          = 3,
    ICU_EXT_DSP_FCM4           = 4,
    ICU_EXT_RESERVED5          = 5,
    ICU_EXT_RESERVED6          = 6,
    ICU_EXT_RESERVED7          = 7,
    ICU_EXT_RESERVED8          = 8,
    ICU_EXT_RESERVED9          = 9,
    ICU_EXT_RESERVED10         = 10,
    ICU_EXT_RESERVED11         = 11,
    ICU_EXT_RESERVED12         = 12,
    ICU_EXT_RESERVED13         = 13,
    ICU_EXT_RESERVED14         = 14,
    ICU_EXT_RESERVED15         = 15,
    ICU_EXT_RESERVED16         = 16,
    ICU_EXT_RESERVED17         = 17,
    ICU_EXT_RESERVED18         = 18,
    ICU_EXT_RESERVED19         = 19,
    ICU_EXT_RESERVED20         = 20,
    ICU_EXT_RESERVED21         = 21,
    ICU_EXT_RESERVED22         = 22,
    /* ICU Group2 0~31 */
    ICU_EXT_WFRAME0_FINISH     = 23,
    ICU_EXT_WFRAME1_FINISH     = 24,
    ICU_EXT_RFRAME0_REQ        = 25,
    ICU_EXT_RFRAME1_REQ        = 26,
    ICU_EXT_PIM_FINISH         = 27,
    ICU_EXT_NPU_ERR            = 28,
    ICU_EXT_NPU_FINISH         = 29,
    ICU_EXT_NPU_EXCEPTION      = 30,
    ICU_EXT_RESERVED31         = 31,
    ICU_EXT_RESERVED32         = 32,
    ICU_EXT_RESERVED33         = 33,
    ICU_EXT_RESERVED34         = 34,
    ICU_EXT_RESERVED35         = 35,
    ICU_EXT_RESERVED36         = 36,
    ICU_EXT_RESERVED37         = 37,
    ICU_EXT_RESERVED38         = 38,
    ICU_EXT_RESERVED39         = 39,
    ICU_EXT_RESERVED40         = 40,
    ICU_EXT_RESERVED41         = 41,
    ICU_EXT_RESERVED42         = 42,
    ICU_EXT_RESERVED43         = 43,
    ICU_EXT_RESERVED44         = 44,
    ICU_EXT_RESERVED45         = 45,
    ICU_EXT_RESERVED46         = 46,
    ICU_EXT_RESERVED47         = 47,
    ICU_EXT_RESERVED48         = 48,
    ICU_EXT_RESERVED49         = 49,
    ICU_EXT_RESERVED50         = 50,
    ICU_EXT_RESERVED51         = 51,
    ICU_EXT_RESERVED52         = 52,
    ICU_EXT_RESERVED53         = 53,
    ICU_EXT_RESERVED54         = 54,
} E_ICU_ext_interrupt_types;


#endif /* KERNEL_H_ */
