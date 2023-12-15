/*
 * dsp_mailbox.h
 *
 *  Created on: 2023年12月7日
 *      Author: xinhao
 */

#ifndef DSP_MAILBOX_H_
#define DSP_MAILBOX_H_

#include "debug.h"

#define DSP_MAILBOX DSP_MAILBOX_BASE

#define DSP_MAILBOX_WRDATA          REG32(DSP_MAILBOX + 0x00)
#define DSP_MAILBOX_RESERVED0       REG32(DSP_MAILBOX + 0x04)      
#define DSP_MAILBOX_RDDATA          REG32(DSP_MAILBOX + 0x08)
#define DSP_MAILBOX_RESERVED1       REG32(DSP_MAILBOX + 0x0C)  
#define DSP_MAILBOX_STATUS          REG32(DSP_MAILBOX + 0x10)
#define DSP_MAILBOX_ERROR           REG32(DSP_MAILBOX + 0x14)
#define DSP_MAILBOX_SIT             REG32(DSP_MAILBOX + 0x18)   
#define DSP_MAILBOX_RIT             REG32(DSP_MAILBOX + 0x1C)   
#define DSP_MAILBOX_IS              REG32(DSP_MAILBOX + 0x20)
#define DSP_MAILBOX_IE              REG32(DSP_MAILBOX + 0x24)    
#define DSP_MAILBOX_IP              REG32(DSP_MAILBOX + 0x28)
#define DSP_MAILBOX_CTRL            REG32(DSP_MAILBOX + 0x2C)   

int debug_test_dsp_mailbox(void);

#endif /* DSP_MAILBOX_H_ */
