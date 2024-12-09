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
#ifndef __CSL_DRIVER_H__
#define __CSL_DRIVER_H__


/**
*
* @file csl.h
* @brief The main header file for the CEVA-XM CSL (Core Support Library)
*/

#include "ceva_xm_bc.h"
#include "dma_driver.h"
#include "ocem.h"


#ifdef CEVA

	// This functionality is not available in MSVS simulation
	#include "cpm_io.h"
	#include "mss.h"
    #include "dbgDefs.h"

	#ifdef SENSPRO
		#include "icu.h"
	#endif /* SENSPRO */

	#if  defined(SENSPRO) || (defined(XM6) && (CEVA_DSP_RTL >= 130))
		#include "timers.h"
	#endif /* defined(SENSPRO) || (defined(XM6) && (CEVA_DSP_RTL >= 130)) */

#endif // CEVA



#endif //__CSL_DRIVER_H__
