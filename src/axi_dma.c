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

//#include "psram.h"

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
                                 | (AXI_DMA_CHX_CTL_AWLEN & ((chx - 1) << 48))
                                 | AXI_DMA_CHX_CTL_AWLEN_EN
                                 | (AXI_DMA_CHX_CTL_ARLEN & ((chx - 1) << 39))
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

