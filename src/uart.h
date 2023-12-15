/*
 * uart.h
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#ifndef UART_H_
#define UART_H_

#include "reg.h" 

#define UART0       UART0_BASE
#define UART1       UART1_BASE
#define UART2       UART2_BASE
#define UART3       UART3_BASE

#define UART_RBR(uartx)         REG32((uartx) + 0x0000)
#define UART_THR(uartx)         REG32((uartx) + 0x0000)
#define UART_DLL(uartx)         REG32((uartx) + 0x0000)
#define UART_IER(uartx)         REG32((uartx) + 0x0004)
#define UART_DLH(uartx)         REG32((uartx) + 0x0004)
#define UART_IIR(uartx)         REG32((uartx) + 0x0008)
#define UART_FCR(uartx)         REG32((uartx) + 0x0008)
#define UART_LCR(uartx)         REG32((uartx) + 0x000c)
#define UART_MCR(uartx)         REG32((uartx) + 0x0010)
#define UART_LSR(uartx)         REG32((uartx) + 0x0014)
#define UART_MSR(uartx)         REG32((uartx) + 0x0018)
#define UART_SCR(uartx)         REG32((uartx) + 0x001c)
#define UART_LPDLL(uartx)       REG32((uartx) + 0x0020)
#define UART_LPDLH(uartx)       REG32((uartx) + 0x0024)
#define UART_SRBR(uartx)        REG32((uartx) + 0x0030)
#define UART_STHR(uartx)        REG32((uartx) + 0x0030)
#define UART_FAR(uartx)         REG32((uartx) + 0x0070)
#define UART_TFR(uartx)         REG32((uartx) + 0x0074)
#define UART_RFW(uartx)         REG32((uartx) + 0x0078)
#define UART_USR(uartx)         REG32((uartx) + 0x007c)
#define UART_TFL(uartx)         REG32((uartx) + 0x0080)
#define UART_RFL(uartx)         REG32((uartx) + 0x0084)
#define UART_SRR(uartx)         REG32((uartx) + 0x0088)
#define UART_SRTS(uartx)        REG32((uartx) + 0x008c)
#define UART_SBCR(uartx)        REG32((uartx) + 0x0090)
#define UART_SDMAM(uartx)       REG32((uartx) + 0x0094)
#define UART_SFE(uartx)         REG32((uartx) + 0x0098)
#define UART_SRT(uartx)         REG32((uartx) + 0x009c)
#define UART_STET(uartx)        REG32((uartx) + 0x00a0)
#define UART_HTX(uartx)         REG32((uartx) + 0x00a4)
#define UART_DMASA(uartx)       REG32((uartx) + 0x00a8)
#define UART_TCR(uartx)         REG32((uartx) + 0x00ac)
#define UART_DE_EN(uartx)       REG32((uartx) + 0x00b0)
#define UART_RE_EN(uartx)       REG32((uartx) + 0x00b4)
#define UART_DET(uartx)         REG32((uartx) + 0x00b8)
#define UART_TAT(uartx)         REG32((uartx) + 0x00bc)
#define UART_DLF(uartx)         REG32((uartx) + 0x00c0)
#define UART_RAR(uartx)         REG32((uartx) + 0x00c4)
#define UART_TAR(uartx)         REG32((uartx) + 0x00c8)
#define UART_LCR_EXT(uartx)     REG32((uartx) + 0x00cc)
#define UART_CPR(uartx)         REG32((uartx) + 0x00f4)
#define UART_UCV(uartx)         REG32((uartx) + 0x00f8)
#define UART_CTR(uartx)         REG32((uartx) + 0x00fc)

#define UART_USR_RFFT           BIT(4)
#define UART_USR_RFNE           BIT(3)
#define UART_USR_TFE            BIT(2)
#define UART_USR_TFNF           BIT(1)
#define UART_USR_BUSY           BIT(0)

int debug_test_uart(void);

#endif /* UART_H_ */
