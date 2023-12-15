/*
 * kernel.h
 *
 *  Created on: 2023年11月29日
 *      Author: xinhao
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "debug.h"

#define DSP_EDAP DSP_EDAP_BASE

#define DSP_MULTICORE_CONFIGURATION             (0x00000000U) // 0x00000000 ~ 0x000000a8
#define DSP_PROGRAM_MEMORY_SUBSYSTEM            (0x00000400U) // 0x00000400 ~ 0x0000057c
#define DSP_PMSS_SAFETY                         (0x00000580U) // 0x00000580 ~ 0x000005fc
#define DSP_DATA_MEMORY_SUBSYSTEM               (0x00000600U) // 0x00000600 ~ 0x000006ec
#define DSP_WATCHDOG                            (0x00000700U) // 0x00000700 ~ 0x0000074c
#define DSP_CORE_SAFETY                         (0x00000750U) // 0x00000750 ~ 0x0000075c
#define DSP_ERROR_CORRECTION_CODES              (0x00000780U) // 0x00000780 ~ 0x00000798
#define DSP_DMSS_SAFETY                         (0x000007b0U) // 0x000007b0 ~ 0x000007fc
#define DSP_INTERFACE_CONFIGURATION             (0x00000900U) // 0x00000900 ~ 0x00000b28
#define DSP_ACCESS_PROTECTION                   (0x00000c80U) // 0x00000c80 ~ 0x00000c88
#define DSP_HARDWARE_EXCEPTIONS                 (0x00000d00U) // 0x00000d00 ~ 0x00000dcc
#define DSP_POWER_SCALING_UNIT                  (0x00000e50U) // 0x00000e50 ~ 0x00000e64
#define DSP_ROUND_ROBIN_ARBITER                 (0x00000fa0U) // 0x00000fa0 ~ 0x00000fb0
#define DSP_QUEUE_DESCRIPTOR                    (0x00001100U) // 0x00001100 ~ 0x00001120
#define DSP_QMAN_CNTRL                          (0x00001180U) // 0x00001180 ~ 0x000011bc
#define DSP_QUEUE_MANAGER                       (0x00001200U) // 0x00001200 ~ 0x00001df8
#define DSP_TIMERS                              (0x00002000U) // 0x00002000 ~ 0x0000203c
#define DSP_INTERRUPT_CONTROL                   (0x00002100U) // 0x00002100 ~ 0x000026fc

/* MCCI */
#define DSP_MCCI_COM_REG(x)		                (DSP_MULTICORE_CONFIGURATION + 0x00U + 0x04 * (x))
#define DSP_MCCI_COM_STS  	                    (DSP_MULTICORE_CONFIGURATION + 0x80U)
#define DSP_MCCI_COM_INT_EN			            (DSP_MULTICORE_CONFIGURATION + 0x84U)
#define DSP_MCCI_START_ADDR(x)		            (DSP_MULTICORE_CONFIGURATION + 0x90U + 0x08 * (x))
#define DSP_MCCI_TOP_ADDR(x)			        (DSP_MULTICORE_CONFIGURATION + 0x94U + 0x08 * (x))
#define DSP_MCCI_SNOOP_CSR(x)			        (DSP_MULTICORE_CONFIGURATION + 0x98U + 0x08 * (x))

/* PMSS */
#define DSP_PMSS_MSS_PCR_REG 	                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x000U)
#define DSP_PMSS_P_SYS_OU_C 		            (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x004U)
#define DSP_PMSS_P_HDCFG 		                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x008U)
#define DSP_PMSS_P_PDEA 			            (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x010U)
#define DSP_PMSS_P_PDIA 			            (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x014U)
#define DSP_PMSS_P_PDTC 			            (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x018U)
#define DSP_PMSS_P_PORT_ID 		                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x01cU)
#define DSP_PMSS_P_ADD0_START(x)                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x020U + 0x08 * (x))
#define DSP_PMSS_P_ADD0_ATT(x) 	                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x024U + 0x08 * (x))
#define DSP_PMSS_P_CCOSAR_REG 	                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0X0E0U)
#define DSP_PMSS_P_CCOCR_REG 	                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0X0E4U)
#define DSP_PMSS_P_ECADD_REG 	                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x0f0U)
#define DSP_PMSS_PMSSACS 		                (DSP_PROGRAM_MEMORY_SUBSYSTEM + 0x140U)

/* DMSS */
#define DSP_DMSS_MSS_DMBA                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x000U)              
#define DSP_DMSS_MSS_DMBE                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x004U)                                    
#define DSP_DMSS_MSS_HDCFG                      (DSP_DATA_MEMORY_SUBSYSTEM + 0x01cU)               
#define DSP_DMSS_MSS_GPIN                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x020U)              
#define DSP_DMSS_MSS_GPOUT                      (DSP_DATA_MEMORY_SUBSYSTEM + 0x024U)               
#define DSP_DMSS_MSS_DACC                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x028U)              
#define DSP_DMSS_MSS_SDCFG                      (DSP_DATA_MEMORY_SUBSYSTEM + 0x02cU)               
#define DSP_DMSS_MSS_BARRIER                    (DSP_DATA_MEMORY_SUBSYSTEM + 0x038U)                 
#define DSP_DMSS_D_DMAB                         (DSP_DATA_MEMORY_SUBSYSTEM + 0x03cU)            
#define DSP_DMSS_DBG_WRC0                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x044U)              
#define DSP_DMSS_DBG_WRC1                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x048U)              
#define DSP_DMSS_DBG_WRC2                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x04cU)              
#define DSP_DMSS_MSS_DDTC                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x058U)              
#define DSP_DMSS_MSS_2DCFG1                     (DSP_DATA_MEMORY_SUBSYSTEM + 0x060U)                
#define DSP_DMSS_MSS_2DCFG2                     (DSP_DATA_MEMORY_SUBSYSTEM + 0x064U)                
#define DSP_DMSS_MSS_2DCFG3                     (DSP_DATA_MEMORY_SUBSYSTEM + 0x068U)                
#define DSP_DMSS_MSS_CEVA_INTERNAL_0            (DSP_DATA_MEMORY_SUBSYSTEM + 0x06cU)                         
#define DSP_DMSS_MSS_CEVA_INTERNAL_1            (DSP_DATA_MEMORY_SUBSYSTEM + 0x070U)                         
#define DSP_DMSS_MSS_CEVA_INTERNAL_2            (DSP_DATA_MEMORY_SUBSYSTEM + 0x074U)                         
#define DSP_DMSS_MSS_DDQS                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x078U)              
#define DSP_DMSS_MSS_DDEA                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x080U)              
#define DSP_DMSS_MSS_DDIA                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x084U)              
#define DSP_DMSS_MSS_DDCL                       (DSP_DATA_MEMORY_SUBSYSTEM + 0x08cU)              
#define DSP_DMSS_DDMA_PAUSE                     (DSP_DATA_MEMORY_SUBSYSTEM + 0x090U)                
#define DSP_DMSS_MSS_DDESC_ID                   (DSP_DATA_MEMORY_SUBSYSTEM + 0x0a0U)                  
#define DSP_DMSS_MSS_DDESC_OV                   (DSP_DATA_MEMORY_SUBSYSTEM + 0x0a4U)                  
#define DSP_DMSS_MSTR_TASK_ID                   (DSP_DATA_MEMORY_SUBSYSTEM + 0x0a8U)                  
#define DSP_DMSS_QMAN_TASK_ID(x)                (DSP_DATA_MEMORY_SUBSYSTEM + 0x0b0U + 0x04 * (x))             

int debug_test_kernel(void);

#endif /* KERNEL_H_ */
