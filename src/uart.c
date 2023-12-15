/*
 * uart.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */


#include "uart.h"
#include "debug.h"

#include "gpio.h"
#include "axi_dma.h"

int uart_init(uint32_t uartx, uint32_t clock, uint32_t uart_baudrate)
{
    uint32_t temp;

    UART_LCR(uartx) = 0;
    temp = UART_RBR(uartx);
    temp = UART_LSR(uartx);
    temp = UART_MSR(uartx);
    while(UART_USR(uartx) & (1<<0));
    UART_FCR(uartx) = 0x0;
    UART_LCR_EXT(uartx) = 0x0;
    UART_TCR(uartx) = 0x0;
    UART_IER(uartx) = 0x0;
    UART_HTX(uartx) = 0x0;
    UART_DMASA(uartx) = 0x0;
    UART_LCR(uartx) = 0x0
                    | 0 << 5
                    | 0 << 4
                    | 0 << 3
                    | 0 << 2
                    | 3     ;
    UART_MCR(uartx) = 0x0;
    UART_FCR(uartx) = 0x0
    | 1 << 6
    | 2 << 4
    | 1 << 3
    | 1 << 2
    | 1 << 1
    | 1 << 0;
    UART_LCR(uartx) |= 0x80;
    temp = clock / (16 * uart_baudrate);
    UART_DLL(uartx) = temp & 0xff;
    UART_DLH(uartx) = (temp >> 8) & 0xff;
    temp = (clock - (temp * (16 * uart_baudrate))) / uart_baudrate;
    UART_DLF(uartx) = temp & 0xff;
    UART_LCR(uartx) &= ~0x80;
    temp = UART_LCR(uartx);

    while(UART_USR(uartx) & (1<<0));
    UART_IER(uartx) |= 0x15;
    temp = UART_IIR(uartx);
    return 0;
}

int debug_test_uart(void)
{
	/* Test start */
	debug_init(TEST_CODE_UART);

	/* Test 1: uart0 config read */
    debug_new_case();
	uint32_t version0 = UART_CTR(UART0);
	if (version0 != 0x44570110)
	{
		debug_case_set_failed(version0);
	}
	case_finish();

    /* Test 2: uart0 config  */
    debug_new_case();
    UART_IER(UART0) = 0x1;
    uint32_t en_statuts0 = UART_IER(UART0);
	if (en_statuts0 != 0x1)
	{
		debug_case_set_failed(en_statuts0);
	}
	case_finish();

    /* Test 3: uart1 config read */
    debug_new_case();
	uint32_t version1 = UART_CTR(UART1);
	if (version1 != 0x44570110)
	{
		debug_case_set_failed(version1);
	}
	case_finish();

    /* Test 4: uart1 config  */
    debug_new_case();
    UART_IER(UART1) = 0x1;
    uint32_t en_statuts1 = UART_IER(UART1);
	if (en_statuts1 != 0x1)
	{
		debug_case_set_failed(en_statuts1);
	}
	case_finish();

    /* Test 5: uart2 config read */
    debug_new_case();
	uint32_t version2 = UART_CTR(UART2);
	if (version2 != 0x44570110)
	{
		debug_case_set_failed(version2);
	}
	case_finish();

    /* Test 6: uart2 config  */
    debug_new_case();
    UART_IER(UART2) = 0x1;
    uint32_t en_statuts2 = UART_IER(UART2);
	if (en_statuts2 != 0x1)
	{
		debug_case_set_failed(en_statuts2);
	}
	case_finish();

    /* Test 7: uart3 config read */
    debug_new_case();
	uint32_t version3 = UART_CTR(UART3);
	if (version3 != 0x44570110)
	{
		debug_case_set_failed(version3);
	}
	case_finish();

    /* Test 8: uart3 config  */
    debug_new_case();
    UART_IER(UART3) = 0x1;
    uint32_t en_statuts3 = UART_IER(UART3);
	if (en_statuts3 != 0x1)
	{
		debug_case_set_failed(en_statuts3);
	}
	case_finish();

//    /* Test 9: uart axi dma send & recv */
//    debug_new_case();
//    axi_dma_enable(DSP_DMA);
//    uint8_t *data_src = (uint8_t *)0x44040000;
//    uint8_t *data_dst = (uint8_t *)0x44041000;
//    for (size_t i = 0; i < 16; i++)
//    {
//        /* code */
//        REG8(data_src++) = i + 1;
//    }
//
//    set_gpio(0, 1, 0);
//    set_gpio(0, 3, 0);
//    set_gpio(0, 16, 3);
//    set_gpio(0, 17, 3);
//    uart_init(UART0, 10000000, 115200);
//    uart_init(UART1, 10000000, 115200);
//    axi_dma_init(DSP_DMA, AXI_DMA_CH1, 16, 1, 1);
//    axi_dma_init(DSP_DMA, AXI_DMA_CH2, 16, 1, 1);
//    axi_dma_init(DSP_DMA, AXI_DMA_CH3, 16, 1, 1);
//    AXI_DMA_CHX_CFG(DSP_DMA, AXI_DMA_CH1) |= AXI_DMA_CHX_CFG_TT_FC_M2P_DMA << 32;
//    AXI_DMA_CHX_CFG(DSP_DMA, AXI_DMA_CH2) |= AXI_DMA_CHX_CFG_TT_FC_P2P_DMA << 32;
//    AXI_DMA_CHX_CFG(DSP_DMA, AXI_DMA_CH3) |= AXI_DMA_CHX_CFG_TT_FC_P2M_DMA << 32;
//    while((UART_USR(UART0) & UART_USR_TFE) == 0);
//
//    axi_dma_start(DSP_DMA, AXI_DMA_CH1, 0x44040000, UART_STHR(UART0));
////    axi_dma_start(DSP_DMA, AXI_DMA_CH2, UART_SRBR(UART1), UART_STHR(UART1));
////    axi_dma_start(DSP_DMA, AXI_DMA_CH3, UART_SRBR(UART0), 0x44041000);
//    while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (AXI_DMA_CH1 - 1))));
////    while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (AXI_DMA_CH2 - 1))));
////    while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (AXI_DMA_CH3 - 1))));
////    for (size_t i = 0; i < 16; i++)
////    {
////        /* code */
////        if (data_dst[i] != data_src[i])
////        {
////            /* code */
////            debug_case_set_failed(data_dst[i]);
////        }
////
////    }
//
//    case_finish();
	/* Test finished */
	debug_finish();

	return 0;
}
