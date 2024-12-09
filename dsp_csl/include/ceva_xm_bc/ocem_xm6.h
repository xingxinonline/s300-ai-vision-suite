/*****************************************************************************\
* CEVA Confidential property.
* Copyright (C) Ceva Inc. All rights reserved.
*
* This file constitutes proprietary and confidential information of CEVA Inc.
* Any use or copying of this file or any information contained in this file other
* than as expressly approved in writing by Ceva, Inc. is strictly prohibited.
* Any disclosure or distribution of this file or any information contained in
* this file except to the intended recipient is strictly prohibited.
\*****************************************************************************/

#ifndef _INCLUDE_OCEM_XM6_H_
#define _INCLUDE_OCEM_XM6_H_


#include "ceva_csl_defs.h"

#ifdef XM6

#include "cpm_io.h"
#include "ceva_profiler.h"

#define PROF_COUNTER_EVENT_PMSS_MIS_CNT PROF_COUNTER_EVENT_PMSS_MISS_CNT

/**
* @addtogroup OCEM_DRIVER OCEM Driver
* @{
* @brief CEVA-XM6 OCEM (On-Chip Emulation Module) driver
*
* The OCEM driver is used to configure the XM6 On-Chip Emulation Module hardware.
* @}
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup OCEM_DRIVER_REGS OCEM Register Map
* @ingroup OCEM_DRIVER
* @{
*/

 /**
 * @brief OCEM registers' addresses
 */

typedef enum
{
    OCEM_MSS_CONFIG_ADDR        = 0x15C,                        /**< MSS_CONFIG Register */
    OCEM_CORE_VERSION_ADDR      = 0x174,                        /**< CORE_VERSION Register */
    OCEM_CORE_ID_ADDR           = 0x178,                        /**< CORE_ID Register */
    OCEM_CORE_CONFIG_ADDR       = 0x17C,                        /**< CORE_CONFIG  Register */
    OCEM_PROF_RESET_ADDR        = 0x300,                        /**< PROF_RESET */
    OCEM_PROF_PAUSE_ADDR        = 0x304,                        /**< PROF_PAUSE */
    OCEM_PROF_CTRL0_ADDR        = 0x308,                        /**< PROF_CTRL0 */
    OCEM_PROF_CTRL1_ADDR        = 0x30C,                        /**< PROF_CTRL1 */
    OCEM_PROF_FRCC_ADDR         = 0x310,                        /**< PROF_FRCC */
    OCEM_PROF_CNT0_ADDR         = 0x320,                        /**< PROF_CNT0 */
    OCEM_PROF_CNT1_ADDR         = OCEM_PROF_CNT0_ADDR + 4,      /**< PROF_CNT1 */
    OCEM_PROF_CNT2_ADDR         = OCEM_PROF_CNT1_ADDR + 4,      /**< PROF_CNT2 */
    OCEM_PROF_CNT3_ADDR         = OCEM_PROF_CNT2_ADDR + 4,      /**< PROF_CNT3 */
    OCEM_PROF_CNT4_ADDR         = OCEM_PROF_CNT3_ADDR + 4,      /**< PROF_CNT4 */
    OCEM_PROF_CNT5_ADDR         = OCEM_PROF_CNT4_ADDR + 4,      /**< PROF_CNT5 */
    OCEM_PROF_CNT6_ADDR         = OCEM_PROF_CNT5_ADDR + 4,      /**< PROF_CNT6 */
    OCEM_PROF_CNT7_ADDR         = OCEM_PROF_CNT6_ADDR + 4,      /**< PROF_CNT7 */
    OCEM_PROF_LOW_ADD0_ADDR     = 0x340,                        /**< PROF_LOW_ADD0 */
    OCEM_PROF_LOW_ADD1_ADDR     = OCEM_PROF_LOW_ADD0_ADDR + 4,  /**< PROF_LOW_ADD1 */
    OCEM_PROF_LOW_ADD2_ADDR     = OCEM_PROF_LOW_ADD1_ADDR + 4,  /**< PROF_LOW_ADD2 */
    OCEM_PROF_LOW_ADD3_ADDR     = OCEM_PROF_LOW_ADD2_ADDR + 4,  /**< PROF_LOW_ADD3 */
    OCEM_PROF_LOW_ADD4_ADDR     = OCEM_PROF_LOW_ADD3_ADDR + 4,  /**< PROF_LOW_ADD4 */
    OCEM_PROF_LOW_ADD5_ADDR     = OCEM_PROF_LOW_ADD4_ADDR + 4,  /**< PROF_LOW_ADD5 */
    OCEM_PROF_LOW_ADD6_ADDR     = OCEM_PROF_LOW_ADD5_ADDR + 4,  /**< PROF_LOW_ADD6 */
    OCEM_PROF_LOW_ADD7_ADDR     = OCEM_PROF_LOW_ADD6_ADDR + 4,  /**< PROF_LOW_ADD7 */
    OCEM_PROF_HI_ADD0_ADDR      = 0x360,                        /**< PROF_HI_ADD0 */
    OCEM_PROF_HI_ADD1_ADDR      = OCEM_PROF_HI_ADD0_ADDR + 4,   /**< PROF_HI_ADD1 */
    OCEM_PROF_HI_ADD2_ADDR      = OCEM_PROF_HI_ADD1_ADDR + 4,   /**< PROF_HI_ADD2 */
    OCEM_PROF_HI_ADD3_ADDR      = OCEM_PROF_HI_ADD2_ADDR + 4,   /**< PROF_HI_ADD3 */
    OCEM_PROF_HI_ADD4_ADDR      = OCEM_PROF_HI_ADD3_ADDR + 4,   /**< PROF_HI_ADD4 */
    OCEM_PROF_HI_ADD5_ADDR      = OCEM_PROF_HI_ADD4_ADDR + 4,   /**< PROF_HI_ADD5 */
    OCEM_PROF_HI_ADD6_ADDR      = OCEM_PROF_HI_ADD5_ADDR + 4,   /**< PROF_HI_ADD6 */
    OCEM_PROF_HI_ADD7_ADDR      = OCEM_PROF_HI_ADD6_ADDR + 4    /**< PROF_HI_ADD7 */
} ocem_regs_addr_e;



   /**
     * @brief Special value for disabling address range condition on profiling events
     */
#define PROF_COUNTER_ADDRESS_RANGE_DISABLE   (0)

    /**
     * @brief Configures a profiling counter in OCEM block. <BR> This functionality in not supported in simulation.
     * @param[in] counter_id Counter ID
     * @param[in] counter_event Counter event
     * @param[in] low_address  Lower program address (low_address <= high_address)
     * @param[in] high_address Upper program address (pass 0 to disable address range check)
     * @returns void
     */

#define prof_counter_config(_counter_number, _event, _low_address, _high_address) \
		PROFILER_config_event_counter(_counter_number, _event)



#define prof_full_counter_config( _counter_number, _event)						  \
		PROFILER_config_event_counter(_counter_number, _event)

/**
 * @brief Resets the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to reset (see \link prof_counter_mask_e \endlink)
 */
#define PROF_RESET(_mask)     PROFILER_reset_counter(_mask)

/**
 * @brief Pauses the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to pause (see \link prof_counter_mask_e \endlink)
 */
#define PROF_PAUSE(_mask)     PROFILER_pause_counter(_mask)

/**
 * @brief Resumes the counting of the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to resume (see \link prof_counter_mask_e \endlink)
 */
#define PROF_RESUME(_mask)    PROFILER_resume_counter(_mask)

/**
 * @brief Restarts the counting of the selected profiling counters
 * @param[in] mask The bit-mask for selecting the counters to restart (see \link prof_counter_mask_e \endlink)
 */
#define PROF_START(_mask)    PROFILER_start_counter(_mask)

/**
 * @brief Reads the value of a profiling counter in OCEM block
 * @param[in] id Counter ID (see \link prof_counter_id_e \endlink)
 * @return the value of the counter
 */
#define PROF_READ_CNT(_counter_number)    PROFILER_read_counter_value(_counter_number)

/**
 * @brief Reads the value of the FRCC counter in OCEM block
 * @return the value of the counter
 */

/** @}*/

#ifdef __cplusplus
}
#endif

#endif  /* XM6 */
#endif /* _INCLUDE_OCEM_XM6_H_ */
