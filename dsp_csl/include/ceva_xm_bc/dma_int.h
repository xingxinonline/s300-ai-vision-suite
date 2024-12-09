#ifndef __DMA_INT_H__
#define __DMA_INT_H__




#include <stdint.h>
#include "ceva_csl_defs.h"


// Debug log definitions
//#define DEBUG_LOG_ENABLE
#if (!defined CEVA) && (defined DEBUG_LOG_ENABLE)
	#include <memory.h>
	#include <stdio.h>
	#include <windows.h>
	#include <stdio.h>
	char tracebuf[256];
	#define LOG_PREFIX "DMA Driver - "
	#define DEBUG_LOG(...) \
						{\
						sprintf(tracebuf, __VA_ARGS__); \
						OutputDebugString(tracebuf); \
																				}
#else // !CEVA
	#include <string.h>
	#define DEBUG_LOG(...)
#endif //!CEVA




#endif // __DMA_INT_H__
