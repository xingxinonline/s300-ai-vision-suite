/*
 * @Author       : panxinhao
 * @Date         : 2023-11-22 15:32:24
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-11-22 16:02:54
 * @FilePath     : \\ceva_no_ecc_test_ext_4m\\test_data_ext_mem\\src\\helloworld.c
 * @Description  :
 *
 * Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "sram.h"
#include "axi_dma.h"
#include "debug.h"
#include "psram.h"

extern char __malloc_end;
uint64_t *code_end_addr = (uint64_t *) &__malloc_end;

int debug_test_sram(void)
{
    /* Test start */
    debug_init(TEST_CODE_SRAM0);
    /* Test 1: sram0 write read uint8*/
    {
        debug_new_case();
        uint8_t *sram0_addr_8 = (uint8_t *)(DSP_RAM0_BASE + 0x3FF00);
        for (size_t i = 0; i < 0x10 / sizeof(uint8_t); i++)
        {
            /* code */
            sram0_addr_8[i] = i;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint8_t); i++)
        {
            /* code */
            if (sram0_addr_8[i] != i)
            {
                /* code */
                debug_case_set_failed(sram0_addr_8[i]);
            }
        }
        case_finish();
    }
    /* Test 2: sram0 write read uint16*/
    {
        debug_new_case();
        uint16_t *sram0_addr_16 = (uint16_t *)(DSP_RAM0_BASE + 0x3FE00);
        for (size_t i = 0; i < 0x10 / sizeof(uint16_t); i++)
        {
            /* code */
            sram0_addr_16[i] = i;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint16_t); i++)
        {
            /* code */
            if (sram0_addr_16[i] != i)
            {
                /* code */
                debug_case_set_failed(sram0_addr_16[i]);
            }
        }
        case_finish();
    }
    /* Test 3: sram0 write read uint32*/
    {
        debug_new_case();
        uint32_t *sram0_addr_32 = (uint32_t *)(DSP_RAM0_BASE + 0x3FC00);
        for (size_t i = 0; i < 0x10 / sizeof(uint16_t); i++)
        {
            /* code */
            sram0_addr_32[i] = i;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint16_t); i++)
        {
            /* code */
            if (sram0_addr_32[i] != i)
            {
                /* code */
                debug_case_set_failed(sram0_addr_32[i]);
            }
        }
        case_finish();
    }
    /* Test 4: sram0 write read uint64*/
    {
        debug_new_case();
        uint64_t *sram0_addr_64 = (uint64_t *)(DSP_RAM0_BASE + 0x38000);
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram0_addr_64[i] = i;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram0_addr_64[i] != i)
            {
                /* code */
                debug_case_set_failed(sram0_addr_64[i]);
            }
        }
        case_finish();
    }
    /* Test 5: sram0 write read 0xFF */
    code_end_addr = (uint64_t *)(DSP_RAM0_BASE + 0x39000);
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            code_end_addr[i] = 0xFFFFFFFFFFFFFFFF;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (code_end_addr[i] != 0xFFFFFFFFFFFFFFFF)
            {
                /* code */
                debug_case_set_failed(code_end_addr[i]);
            }
        }
        case_finish();
    }
    /* Test 6: sram0 write read 0x55 */
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            code_end_addr[i] = 0x5555555555555555;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (code_end_addr[i] != 0x5555555555555555)
            {
                /* code */
                debug_case_set_failed(code_end_addr[i]);
            }
        }
        case_finish();
    }
    /* Test 7: sram0 write read 0xAA */
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            code_end_addr[i] = 0xAAAAAAAAAAAAAAAA;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (code_end_addr[i] != 0xAAAAAAAAAAAAAAAA)
            {
                /* code */
                debug_case_set_failed(code_end_addr[i]);
            }
        }
        case_finish();
    }
    /* Test 8: sram0 write read 0x00 */
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            code_end_addr[i] = 0;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (code_end_addr[i] != 0)
            {
                /* code */
                debug_case_set_failed(code_end_addr[i]);
            }
        }
        case_finish();
    }
    /* Test 9: dma ch8 sram0 sram0 */
    axi_dma_enable(DSP_DMA);
    uint64_t *data32_sram0_src = (uint64_t *)(DSP_RAM0_BASE);
    {
        debug_new_case();
        for (size_t chx = 1;  chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_sram0 = (uint64_t *)(DSP_RAM0_BASE + 0x3FF00);
            axi_dma_start(DSP_DMA, chx, (uint64_t)data32_sram0_src, (uint64_t)data32_sram0);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_sram0[i] != data32_sram0_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_sram0[i]);
                }
            }
        }
        case_finish();
    }
    /* Test 10: dma ch6 sram0 sram1 */
    {
        debug_new_case();
        for (size_t chx = 1;  chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_sram01 = (uint64_t *)(DSP_RAM1_BASE + 0x39000);
            axi_dma_start(DSP_DMA, chx, (uint64_t)data32_sram0_src, DSP_RAM1_BASE + 0x39000);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_sram01[i] != data32_sram0_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_sram01[i]);
                }
            }
        }
        case_finish();
    }
    uint32_t sys_clock = 50000000;
    uint32_t psram_clock = 10000000;
    REG32(SCTRL_BASE + 0x0c) &= ~1; //disable psram xip
    ospi_init_xip(OSPI0, sys_clock, psram_clock);
    REG32(SCTRL_BASE + 0x0c) |= 1; //enable psram xip
    /* Test 11: dma ch7 sram0 psram */
    {
        debug_new_case();
        for (size_t chx = 1;  chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_psram0 = (uint64_t *)(PSRAM_BASE + 0x10000);
            axi_dma_start(DSP_DMA, chx, (uint64_t)data32_sram0_src, PSRAM_BASE + 0x10000);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_psram0[i] != data32_sram0_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_psram0[i]);
                }
            }
        }
        case_finish();
    }
    /* Test finished */
    debug_finish();
    /* Test start */
    debug_init(TEST_CODE_SRAM1);
    /* Test 1: sram1 write read uint8*/
    {
        debug_new_case();
        uint8_t *sram1_addr_8 = (uint8_t *)(DSP_RAM1_BASE + 0x3FE00);
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            sram1_addr_8[i] = i;
        }
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            if (sram1_addr_8[i] != i)
            {
                /* code */
                debug_case_set_failed(sram1_addr_8[i]);
            }
        }
        case_finish();
    }
    /* Test 2: sram1 write read uint16*/
    {
        debug_new_case();
        uint16_t *sram1_addr_16 = (uint16_t *)(DSP_RAM1_BASE + 0x3FD00);
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            sram1_addr_16[i] = i;
        }
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            if (sram1_addr_16[i] != i)
            {
                /* code */
                debug_case_set_failed(sram1_addr_16[i]);
            }
        }
        case_finish();
    }
    /* Test 3: sram1 write read uint32*/
    {
        debug_new_case();
        uint32_t *sram1_addr_32 = (uint32_t *)(DSP_RAM1_BASE + 0x3FC00);
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            sram1_addr_32[i] = i;
        }
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            if (sram1_addr_32[i] != i)
            {
                /* code */
                debug_case_set_failed(sram1_addr_32[i]);
            }
        }
        case_finish();
    }
    /* Test 4: sram1 write read uint64*/
    {
        debug_new_case();
        uint64_t *sram1_addr_64 = (uint64_t *)(DSP_RAM1_BASE + 0x3FB00);
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram1_addr_64[i] = i;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram1_addr_64[i] != i)
            {
                /* code */
                debug_case_set_failed(sram1_addr_64[i]);
            }
        }
        case_finish();
    }
    /* Test 5: sram1 write read 0xFF*/
    uint64_t *sram1_addr_64 = (uint64_t *)(DSP_RAM1_BASE);
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram1_addr_64[i] = 0xFFFFFFFFFFFFFFFF;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram1_addr_64[i] != 0xFFFFFFFFFFFFFFFF)
            {
                /* code */
                debug_case_set_failed(sram1_addr_64[i]);
            }
        }
        case_finish();
    }
    /* Test 6: sram1 write read 0xAA*/
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram1_addr_64[i] = 0xAAAAAAAAAAAAAAAA;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram1_addr_64[i] != 0xAAAAAAAAAAAAAAAA)
            {
                /* code */
                debug_case_set_failed(sram1_addr_64[i]);
            }
        }
        case_finish();
    }
    /* Test 7: sram1 write read 0x55*/
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram1_addr_64[i] = 0x5555555555555555;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram1_addr_64[i] != 0x5555555555555555)
            {
                /* code */
                debug_case_set_failed(sram1_addr_64[i]);
            }
        }
        case_finish();
    }
    /* Test 8: sram1 write read 0x00*/
    {
        debug_new_case();
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            sram1_addr_64[i] = 0;
        }
        for (size_t i = 0; i < 0x10 / sizeof(uint64_t); i++)
        {
            /* code */
            if (sram1_addr_64[i] != 0)
            {
                /* code */
                debug_case_set_failed(sram1_addr_64[i]);
            }
        }
        case_finish();
    }
    uint64_t *data32_sram1_src = (uint64_t *)(DSP_RAM1_BASE);
    for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
    {
        /* code */
        data32_sram1_src[i] = i;
    }
    /* Test 9: dma ch5 sram1 sram0 */
    axi_dma_enable(DSP_DMA);
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_sram10 = (uint64_t *)(DSP_RAM0_BASE + 0x39000);
            axi_dma_start(DSP_DMA, chx, DSP_RAM1_BASE, DSP_RAM0_BASE + 0x39000);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_sram10[i] != data32_sram1_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_sram10[i]);
                }
            }
        }
        case_finish();
    }
    /* Test 10: dma ch4 sram1 sram1 */
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_sram11 = (uint64_t *)(DSP_RAM1_BASE + 0x3FE00);
            axi_dma_start(DSP_DMA, chx, DSP_RAM1_BASE, (uint64_t)data32_sram11);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_sram11[i] != data32_sram1_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_sram11[i]);
                }
            }
        }
        case_finish();
    }
    /* Test 11: dma ch3 sram1 psram */
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint64_t *data32_psram1 = (uint64_t *)(PSRAM_BASE + 0x20000);
            axi_dma_start(DSP_DMA, chx, DSP_RAM1_BASE, PSRAM_BASE + 0x20000);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x80 / sizeof(uint64_t); i++)
            {
                /* code */
                if (data32_psram1[i] != data32_sram1_src[i])
                {
                    /* code */
                    debug_case_set_failed(data32_psram1[i]);
                }
            }
        }
        case_finish();
    }
    /* Test finished */
    debug_finish();
    return 0;
}
