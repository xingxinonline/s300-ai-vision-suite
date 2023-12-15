/*
 * @Author       : panxinhao
 * @Date         : 2023-03-06 18:33:49
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-08-04 19:38:44
 * @FilePath     : \\testbench_base\\riscv64_default\\dma.c
 * @Description  :
 *
 * Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved.
 */

#include "axi_dma.h"

#include "psram.h"

int axi_dma_enable(uint64_t dmax)
{
    AXI_DMA_CFG(dmax) = AXI_DMA_CFG_INT_EN | AXI_DMA_CFG_EN;
    return 0;
}
int axi_dma_init(uint64_t dmax, uint64_t chx, size_t data_size, size_t src_tr_width, size_t dst_tr_width)
{
    size_t src_result = 1, dst_result = 1, src_width = 0, dst_width = 0;
    while (src_result != src_tr_width)
    {
        src_result *= 2;
        src_width++;
    }
    while (dst_result != dst_tr_width)
    {
        dst_result *= 2;
        dst_width++;
    }
    AXI_DMA_CHX_BLOCK_TS(dmax, chx) = AXI_DMA_CHX_BLOCK_TS_MASK & (data_size / src_tr_width - 1);
    AXI_DMA_CHX_CTL(dmax, chx) = AXI_DMA_CHX_CTL_DST_STAT_EN
                                 | AXI_DMA_CHX_CTL_SRC_STAT_EN
                                 | (AXI_DMA_CHX_CTL_AWLEN & (0x03ULL << 48))
                                 | AXI_DMA_CHX_CTL_AWLEN_EN
                                 | (AXI_DMA_CHX_CTL_ARLEN & (0x03ULL << 39))
                                 | AXI_DMA_CHX_CTL_ARLEN_EN
                                 | (AXI_DMA_CHX_CTL_AW_CACHE & (0x00ULL << 26))
                                 | (AXI_DMA_CHX_CTL_AR_CACHE & (0x00ULL << 22))
                                 | (AXI_DMA_CHX_CTL_DST_MSIZE & ((128ULL / 8 / dst_tr_width) << 18))    //最大16，但是fifo最大为8
                                 | (AXI_DMA_CHX_CTL_SRC_MSIZE & ((128ULL / 8 / src_tr_width) << 14))
                                 | (AXI_DMA_CHX_CTL_DST_TR_WIDTH & (dst_width << 11))
                                 | (AXI_DMA_CHX_CTL_SRC_TR_WIDTH & (src_width << 8));
    AXI_DMA_CHX_CFG(dmax, chx) = (AXI_DMA_CHX_CFG_CH_PRIOR & (0x03ULL << 49))
                                 | AXI_DMA_CHX_CFG_HS_SEL_DST
                                 | AXI_DMA_CHX_CFG_HS_SEL_SRC;
    AXI_DMA_CHX_INTSTATUS_ENABLE(dmax, chx) = 0x0ULL;
    AXI_DMA_CHX_INTSIGNAL_ENABLE(dmax, chx) = 0x0ULL;
    return 0;
}

int axi_dma_lli_enable(uint64_t dmax, uint64_t chx)
{
    return 0;
}

int axi_dma_lli_init(size_t data_size, size_t tr_width, uint64_t burst_len, uint64_t burst_en, uint64_t src_addr, uint64_t dst_addr, uint64_t is_last, struct axi_dma_lli *lli_list)
{
    size_t result = 1, width = 0;
    while (result != tr_width)
    {
        result *= 2;
        width++;
    }
    lli_list->block_ts = AXI_DMA_CHX_BLOCK_TS_MASK & (data_size / tr_width - 1);
    lli_list->ctl = (AXI_DMA_CHX_CTL_LLI_VAID & (0x1ULL << 63))
                    | (AXI_DMA_CHX_CTL_LLI_LAST & (is_last << 62))
                    | AXI_DMA_CHX_CTL_DST_STAT_EN
                    | AXI_DMA_CHX_CTL_SRC_STAT_EN
                    | (AXI_DMA_CHX_CTL_AWLEN & ((burst_len - 1) << 48))
                    | (AXI_DMA_CHX_CTL_AWLEN_EN & (burst_en << 47))
                    | (AXI_DMA_CHX_CTL_ARLEN & ((burst_len - 1) << 39))
                    | (AXI_DMA_CHX_CTL_ARLEN_EN & (burst_en << 38))
                    | (AXI_DMA_CHX_CTL_AW_CACHE & (0x00ULL << 26))
                    | (AXI_DMA_CHX_CTL_AR_CACHE & (0x00ULL << 22))
                    | (AXI_DMA_CHX_CTL_DST_MSIZE & ((128ULL / 8 / tr_width) << 18))    //最大16，但是fifo最大为8
                    | (AXI_DMA_CHX_CTL_SRC_MSIZE & ((128ULL / 8 / tr_width) << 14))
                    | (AXI_DMA_CHX_CTL_DST_TR_WIDTH & (width << 11))
                    | (AXI_DMA_CHX_CTL_SRC_TR_WIDTH & (width << 8));
    lli_list->sar = src_addr;
    lli_list->dar = dst_addr;
    if ((is_last == 0) && (lli_list + 1 != NULL))
    {
        /* code */
        lli_list->llp = (uint64_t)(lli_list + 1) & 0xffffffffffffffc0;
    }
    return 0;
}

int axi_dma_lli_start(uint64_t dmax, uint64_t chx, struct axi_dma_lli *lli_list)
{
    /* data */
    AXI_DMA_CHX_CFG(dmax, chx) = (AXI_DMA_CHX_CFG_CH_PRIOR & (0x03ULL << 49))
                                 | AXI_DMA_CHX_CFG_HS_SEL_DST
                                 | AXI_DMA_CHX_CFG_HS_SEL_SRC
                                 | (AXI_DMA_CHX_CFG_DST_MULTBLK_TYPE & (0x3ULL << 2))
                                 | (AXI_DMA_CHX_CFG_SRC_MULTBLK_TYPE & (0x3ULL << 0));
    AXI_DMA_CHX_LLP(dmax, chx) = (uint64_t)lli_list;
    AXI_DMA_CHEN(dmax) = (AXI_DMA_CHEN_CH_EN_WE & ((0x01ULL << (chx - 1)) << 8))
                         | (AXI_DMA_CHEN_CH_EN & ((0x01ULL << (chx - 1)) << 0));
    return 0;
}

int axi_dma_interrupt_enable(uint64_t dmax, uint64_t chx)
{
    AXI_DMA_CHX_INTSTATUS_ENABLE(dmax, chx) = 0xFFFFFFFFFFFFFFFFULL;
    AXI_DMA_CHX_INTSIGNAL_ENABLE(dmax, chx) = 0xFFFFFFFFFFFFFFFFULL;
    return 0;
}

int axi_dma_interrupt_disable(uint64_t dmax, uint64_t chx)
{
    AXI_DMA_CHX_INTSTATUS_ENABLE(dmax, chx) = 0x0ULL;
    AXI_DMA_CHX_INTSIGNAL_ENABLE(dmax, chx) = 0x0ULL;
    return 0;
}

int axi_dma_start(uint64_t dmax, uint64_t chx, uint64_t src_addr, uint64_t dst_addr)
{
    AXI_DMA_CHX_SAR(dmax, chx) = (uint64_t)src_addr;
    AXI_DMA_CHX_DAR(dmax, chx) = (uint64_t)dst_addr;
    AXI_DMA_CHEN(dmax) = (AXI_DMA_CHEN_CH_EN_WE & ((0x01ULL << (chx - 1)) << 8))
                         | (AXI_DMA_CHEN_CH_EN & ((0x01ULL << (chx - 1)) << 0));
    return 0;
}

#include "debug.h"

int debug_test_axi_dma(void)
{
    /* Test start */
    debug_init(TEST_CODE_AXI_DMA);
    axi_dma_enable(DSP_DMA);
    uint32_t sys_clock = 50000000;
    uint32_t psram_clock = 10000000;
    REG32(SCTRL_BASE + 0x0c) &= ~1; //disable psram xip
    ospi_init_xip(OSPI0, sys_clock, psram_clock);
    REG32(SCTRL_BASE + 0x0c) |= 1; //enable psram xip
    struct axi_dma_lli *link_list = (struct axi_dma_lli *)(DSP_RAM0_BASE + 0x3FF00);
    /* Test 1 ~ 8: DMA LLI Static */
    {
        for (size_t chx = 1; chx <= 8; chx++)
        {
            /* code */
            debug_new_case();
            uint32_t *data_lli0_src = (uint32_t *)(PSRAM_BASE);
            uint32_t *data_lli0_dst = (uint32_t *)(PSRAM_BASE + 0x0FFFFF0);
            for (size_t i = 0; i < 0x10 / sizeof(uint32_t); i++)
            {
                /* code */
                data_lli0_src[i] = i;
            }
            axi_dma_lli_init(0x10, 2, 4, 1, (uint64_t)data_lli0_src, (uint64_t)data_lli0_dst, 1, &link_list[0]);
            axi_dma_lli_start(DSP_DMA, chx, &link_list[0]);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x10 / sizeof(uint32_t); i++)
            {
                /* code */
                if (data_lli0_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli0_dst[i]);
                }
            }
            data_lli0_src = (uint32_t *)(PSRAM_BASE + 0x0FFFFF0);
            data_lli0_dst = (uint32_t *)(PSRAM_BASE);
            axi_dma_lli_init(0x10, 2, 4, 1, (uint64_t)data_lli0_src, (uint64_t)data_lli0_dst, 1, &link_list[0]);
            axi_dma_lli_start(DSP_DMA, chx, &link_list[0]);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x10 / sizeof(uint32_t); i++)
            {
                /* code */
                if (data_lli0_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli0_dst[i]);
                }
            }
            data_lli0_src = (uint32_t *)(DSP_RAM1_BASE + 0x0F);
            data_lli0_dst = (uint32_t *)(DSP_RAM1_BASE + 0x1F);
            for (size_t i = 0; i < 0x40; i++)
            {
                /* code */
                REG8(DSP_RAM1_BASE + i) = 0;
            }
            
            for (size_t i = 0; i < 0x10 / sizeof(uint32_t); i++)
            {
                /* code */
                data_lli0_src[i] = i;
            }
            axi_dma_lli_init(0x10, 1, 4, 1, (uint64_t)data_lli0_src, (uint64_t)data_lli0_dst, 1, &link_list[0]);
            axi_dma_lli_start(DSP_DMA, chx, &link_list[0]);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x10 / sizeof(uint32_t); i++)
            {
                /* code */
                if (data_lli0_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli0_dst[i]);
                }
            }
            case_finish();
        }
    }
    /* Test 9 ~ 16: DMA LLI Static 2 */
    {
        uint32_t *data_sram1_lli_src = (uint32_t *)(DSP_RAM1_BASE);
        for (size_t i = 0; i < 0x800 / sizeof(uint32_t); i++)
        {
            /* code */
            data_sram1_lli_src[i] = i;
        }
        uint32_t *data_lli1_dst = (uint32_t *)(DSP_RAM1_BASE + 0x3F000);
        axi_dma_lli_init(0x800, 1, 4, 1, (uint64_t)data_sram1_lli_src, (DSP_RAM1_BASE + 0x3F000), 0, &link_list[1]);
        uint32_t *data_lli2_dst = (uint32_t *)(DSP_RAM1_BASE + 0x3FA00);
        axi_dma_lli_init(0x20, 2, 5, 1, (uint64_t)data_sram1_lli_src, (DSP_RAM1_BASE + 0x3FA00), 0, &link_list[2]);
        uint32_t *data_lli3_dst = (uint32_t *)(DSP_RAM1_BASE + 0x3FC00);
        axi_dma_lli_init(0x20, 4, 4, 1, (uint64_t)data_sram1_lli_src, (DSP_RAM1_BASE + 0x3FC00), 0, &link_list[3]);
        uint32_t *data_lli4_dst = (uint32_t *)(DSP_RAM1_BASE + 0x3FE00);
        axi_dma_lli_init(0x20, 8, 4, 0, (uint64_t)data_sram1_lli_src, (DSP_RAM1_BASE + 0x3FE00), 1, &link_list[4]);
        for (size_t chx = 1; chx <= 8; chx++)
        {
            /* code */
            debug_new_case();
            axi_dma_lli_start(DSP_DMA, chx, &link_list[1]);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x8; i++)
            {
                /* code */
                if (data_lli1_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli1_dst[i]);
                }
            }
            for (size_t i = 0; i < 0x8; i++)
            {
                /* code */
                if (data_lli2_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli2_dst[i]);
                }
            }
            for (size_t i = 0; i < 0x8; i++)
            {
                /* code */
                if (data_lli3_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli3_dst[i]);
                }
            }
            for (size_t i = 0; i < 0x8; i++)
            {
                /* code */
                if (data_lli4_dst[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data_lli4_dst[i]);
                }
            }
            case_finish();
        }
    }
    /* Test finished */
    debug_finish();
    return 0;
}
