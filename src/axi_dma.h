/*** 
 * @Author       : panxinhao
 * @Date         : 2023-07-04 15:53:02
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-08-02 11:35:06
 * @FilePath     : \\testbench_base\\riscv64_default\\dma.h
 * @Description  : 
 * @
 * @Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved. 
 */

#ifndef _AXI_DMA_H_
#define _AXI_DMA_H_

#include "reg.h"

#define AXI_DMA_BASE                                DSP_AXI_DMA_BASE
#define DSP_DMA                                    (AXI_DMA_BASE)                  // device At 0x62400000

#define AXI_DMA_CH1                                 (0x0001ULL)
#define AXI_DMA_CH2                                 (0x0002ULL)
#define AXI_DMA_CH3                                 (0x0003ULL)
#define AXI_DMA_CH4                                 (0x0004ULL)
#define AXI_DMA_CH5                                 (0x0005ULL)
#define AXI_DMA_CH6                                 (0x0006ULL)
#define AXI_DMA_CH7                                 (0x0007ULL)
#define AXI_DMA_CH8                                 (0x0008ULL)


#define AXI_DMA_ID(dmax)                            REG64((dmax) + 0x000ULL)
#define AXI_DMA_COMPVER(dmax)                       REG64((dmax) + 0x008ULL)
#define AXI_DMA_CFG(dmax)                           REG64((dmax) + 0x010ULL)
#define AXI_DMA_CHEN(dmax)                          REG64((dmax) + 0x018ULL)
#define AXI_DMA_INTSTATUS(dmax)                     REG64((dmax) + 0x030ULL)
#define AXI_DMA_COMMON_INTCLEAR(dmax)               REG64((dmax) + 0x038ULL)
#define AXI_DMA_COMMON_INTSTATUS_ENABLE(dmax)       REG64((dmax) + 0x040ULL)
#define AXI_DMA_COMMON_INTSIGNAL_ENABLE(dmax)       REG64((dmax) + 0x058ULL)
#define AXI_DMA_COMMON_INTSTATUS(dmax)              REG64((dmax) + 0x050ULL)
#define AXI_DMA_RESET(dmax)                         REG64((dmax) + 0x058ULL)
#define AXI_DMA_CHX_SAR(dmax, chn)                  REG64((dmax) + (0x100ULL * (chn)) + 0x000ULL)
#define AXI_DMA_CHX_DAR(dmax, chn)                  REG64((dmax) + (0x100ULL * (chn)) + 0x008ULL)
#define AXI_DMA_CHX_BLOCK_TS(dmax, chn)             REG64((dmax) + (0x100ULL * (chn)) + 0x010ULL)
#define AXI_DMA_CHX_CTL(dmax, chn)                  REG64((dmax) + (0x100ULL * (chn)) + 0x018ULL)
#define AXI_DMA_CHX_CFG(dmax, chn)                  REG64((dmax) + (0x100ULL * (chn)) + 0x020ULL)
#define AXI_DMA_CHX_LLP(dmax, chn)                  REG64((dmax) + (0x100ULL * (chn)) + 0x028ULL)
#define AXI_DMA_CHX_STATUS(dmax, chn)               REG64((dmax) + (0x100ULL * (chn)) + 0x030ULL)
#define AXI_DMA_CHX_SWHSSRC(dmax, chn)              REG64((dmax) + (0x100ULL * (chn)) + 0x038ULL)
#define AXI_DMA_CHX_SWHSDST(dmax, chn)              REG64((dmax) + (0x100ULL * (chn)) + 0x040ULL)
#define AXI_DMA_CHX_BLK_TFR_RESUMEREQ(dmax, chn)    REG64((dmax) + (0x100ULL * (chn)) + 0x048ULL)
#define AXI_DMA_CHX_AXI_ID(dmax, chn)               REG64((dmax) + (0x100ULL * (chn)) + 0x050ULL)
#define AXI_DMA_CHX_AXI_QOS(dmax, chn)              REG64((dmax) + (0x100ULL * (chn)) + 0x058ULL)
#define AXI_DMA_CHX_SSTAT(dmax, chn)                REG64((dmax) + (0x100ULL * (chn)) + 0x060ULL)
#define AXI_DMA_CHX_DSTAT(dmax, chn)                REG64((dmax) + (0x100ULL * (chn)) + 0x068ULL)
#define AXI_DMA_CHX_SSTATAR(dmax, chn)              REG64((dmax) + (0x100ULL * (chn)) + 0x070ULL)
#define AXI_DMA_CHX_DSTATAR(dmax, chn)              REG64((dmax) + (0x100ULL * (chn)) + 0x078ULL)
#define AXI_DMA_CHX_INTSTATUS_ENABLE(dmax, chn)     REG64((dmax) + (0x100ULL * (chn)) + 0x080ULL)
#define AXI_DMA_CHX_INTSTATUSREG(dmax, chn)         REG64((dmax) + (0x100ULL * (chn)) + 0x088ULL)
#define AXI_DMA_CHX_INTSIGNAL_ENABLE(dmax, chn)     REG64((dmax) + (0x100ULL * (chn)) + 0x090ULL)
#define AXI_DMA_CHX_INTCLEAR(dmax, chn)             REG64((dmax) + (0x100ULL * (chn)) + 0x098ULL)

#define AXI_DMA_ID_MASK                             BITS_64(0, 63)

#define AXI_DMA_COMPVER_MASK                        BITS_64(0, 31)

#define AXI_DMA_CFG_INT_EN                          BIT_64(1)
#define AXI_DMA_CFG_EN                              BIT_64(0)

#define AXI_DMA_CHEN_CH_EN_WE                       BITS_64(8, 15)
#define AXI_DMA_CHEN_CH_EN                          BITS_64(0, 7)

#define AXI_DMA_CHX_BLOCK_TS_MASK                   BITS_64(0, 21)

#define AXI_DMA_CHX_CTL_LLI_VAID                    BIT_64(63)
#define AXI_DMA_CHX_CTL_LLI_LAST                    BIT_64(62)
#define AXI_DMA_CHX_CTL_DST_STAT_EN                 BIT_64(57)
#define AXI_DMA_CHX_CTL_SRC_STAT_EN                 BIT_64(56)
#define AXI_DMA_CHX_CTL_AWLEN                       BITS_64(48, 55)
#define AXI_DMA_CHX_CTL_AWLEN_EN                    BIT_64(47)
#define AXI_DMA_CHX_CTL_ARLEN                       BITS_64(39, 46)
#define AXI_DMA_CHX_CTL_ARLEN_EN                    BIT_64(38)
#define AXI_DMA_CHX_CTL_AW_CACHE                    BITS_64(26, 29)
#define AXI_DMA_CHX_CTL_AR_CACHE                    BITS_64(22, 25)
#define AXI_DMA_CHX_CTL_DST_MSIZE                   BITS_64(18, 21)
#define AXI_DMA_CHX_CTL_SRC_MSIZE                   BITS_64(14, 17)
#define AXI_DMA_CHX_CTL_DST_TR_WIDTH                BITS_64(11, 13)
#define AXI_DMA_CHX_CTL_SRC_TR_WIDTH                BITS_64(8, 10)

#define AXI_DMA_CHX_CFG_CH_PRIOR                    BITS_64(49, 51)
#define AXI_DMA_CHX_CFG_HS_SEL_DST                  BIT_64(36)
#define AXI_DMA_CHX_CFG_HS_SEL_SRC                  BIT_64(35)
#define AXI_DMA_CHX_CFG_TT_FC                       BITS_64(32, 34)
#define AXI_DMA_CHX_CFG_DST_MULTBLK_TYPE            BITS_64(2, 3)
#define AXI_DMA_CHX_CFG_SRC_MULTBLK_TYPE            BITS_64(0, 1)

#define AXI_DMA_CHX_CFG_TT_FC_M2M_DMA               (0ULL)
#define AXI_DMA_CHX_CFG_TT_FC_M2P_DMA               (1ULL)
#define AXI_DMA_CHX_CFG_TT_FC_P2M_DMA               (2ULL)
#define AXI_DMA_CHX_CFG_TT_FC_P2P_DMA               (3ULL)
#define AXI_DMA_CHX_CFG_TT_FC_P2M_SRC               (4ULL)
#define AXI_DMA_CHX_CFG_TT_FC_P2P_SRC               (5ULL)
#define AXI_DMA_CHX_CFG_TT_FC_M2P_DST               (6ULL)
#define AXI_DMA_CHX_CFG_TT_FC_P2P_DST               (7ULL)


#define AXI_DMA_CHX_INTSTATUS_DMA_TRF_DONE          BIT_64(1)
#define AXI_DMA_CHX_INTSTATUS_BLOCK_TRF_DONE        BIT_64(0)

struct axi_dma_lli
{
    /* data */
    uint64_t sar;
    uint64_t dar;
    uint32_t block_ts;
    uint32_t reserved0;
    uint64_t llp;
    uint64_t ctl;
    uint32_t sstat;
    uint32_t dstat;
    uint64_t llp_status;
    uint64_t reserved1;
};

int axi_dma_enable(uint64_t dmax);
int axi_dma_init(uint64_t dmax, uint64_t chx, size_t data_size, size_t src_tr_width, size_t dst_tr_width);
int axi_dma_interrupt_enable(uint64_t dmax, uint64_t chx);
int axi_dma_interrupt_disable(uint64_t dmax, uint64_t chx);
int axi_dma_start(uint64_t dmax, uint64_t chx, uint64_t src_addr, uint64_t dst_addr);

#endif // !_AXI_DMA_H_
