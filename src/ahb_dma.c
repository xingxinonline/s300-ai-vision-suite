/*
 * ahp_dma.c
 *
 *  Created on: 2023年11月24日
 *      Author: xinhao
 */

#include "ahb_dma.h"
#include "debug.h"

int debug_test_ahb_dma(void)
{
	/* Test start */
	debug_init(TEST_CODE_AHB_DMA);

	/* Test 1: read dma0 id 0x****44571110 */
	debug_new_case();

	uint32_t id0 = AHB_DMA_COMPONENT_ID(AHB_DMA0);
    if ((id0 & 0xffffffff) != 0x44571110)
    {
        debug_case_set_failed(id0);
    }
    case_finish();

    /* Test 2: read dma0 id 0x****44571110 */
	debug_new_case();

	uint32_t id1 = AHB_DMA_COMPONENT_ID(AHB_DMA1);
    if ((id1 & 0xffffffff) != 0x44571110)
    {
        debug_case_set_failed(id1);
    }
    case_finish();

    /* Test 3: dma0 reg write read*/
	debug_new_case();

	AHB_DMA_EN(AHB_DMA0) = 1;
    uint32_t en_status0 = AHB_DMA_EN(AHB_DMA0);
    if (en_status0 != 1)
    {
        /* code */
        debug_case_set_failed(en_status0);
    }
    case_finish();
    
    /* Test 4: dma1 reg write read*/
	debug_new_case();

	AHB_DMA_EN(AHB_DMA1) = 1;
    uint32_t en_status1 = AHB_DMA_EN(AHB_DMA1);
    if (en_status1 != 1)
    {
        /* code */
        debug_case_set_failed(en_status1);
    }
    case_finish();

	/* Test finished */
	debug_finish();

	return 0;
}
