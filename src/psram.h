/*
 * ospi.h
 *
 *  Created on: 2023楠烇拷11閺堬拷22閺冿拷
 *      Author: xinhao
 */

#ifndef PSRAM_H_
#define PSRAM_H_

#include "reg.h"

#define SSIC_VERSION_ID             0x3130332A

#define READ_REGISTER0      (0xC00800)
#define READ_REGISTER1      (0xC00801)
#define WRITE_REGISTER0     (0x600800)
#define WRITE_REGISTER1     (0x600801)

#define PSRAM_SSIC_NUM_SLAVES       (1)
#define PSRAM_SSIC_RX_FIFO_DEPTH    (64)
#define PSRAM_SSIC_TX_FIFO_DEPTH    (64)
#define PSRAM_SSIC_RAM_DEPTH        (32)

#define RX_ABW                      (PSRAM_SSIC_RX_FIFO_DEPTH / 8)
#define TX_ABW                      (PSRAM_SSIC_TX_FIFO_DEPTH / 8)
#define SSIC_RAM_AW                 PSRAM_SSIC_RAM_DEPTH
#define TXFTHR_W                    TX_ABW

#define OSPI0                           PSRAM_BASE
#define OSPI_CLOCK_RATE                 200000000U

#define OSPI_CTRLR0(spix)               REG32((spix) + 0x0000U + 0x00U)
#define OSPI_CTRLR1(spix)               REG32((spix) + 0x0004U + 0x00U)
#define OSPI_SSIENR(spix)               REG32((spix) + 0x0008U + 0x00U)
#define OSPI_MWCR(spix)                 REG32((spix) + 0x000CU + 0x00U)
#define OSPI_SER(spix)                  REG32((spix) + 0x0010U + 0x00U)
#define OSPI_BAUDR(spix)                REG32((spix) + 0x0014U + 0x00U)
#define OSPI_TXFTLR(spix)               REG32((spix) + 0x0018U + 0x00U)
#define OSPI_RXFTLR(spix)               REG32((spix) + 0x001CU + 0x00U)
#define OSPI_TXFLR(spix)                REG32((spix) + 0x0020U + 0x00U)
#define OSPI_RXFLR(spix)                REG32((spix) + 0x0024U + 0x00U)
#define OSPI_SR(spix)                   REG32((spix) + 0x0028U + 0x00U)
#define OSPI_IMR(spix)                  REG32((spix) + 0x002CU + 0x00U)
#define OSPI_ISR(spix)                  REG32((spix) + 0x0030U + 0x00U)
#define OSPI_RISR(spix)                 REG32((spix) + 0x0034U + 0x00U)
#define OSPI_TXEICR(spix)               REG32((spix) + 0x0038U + 0x00U)
#define OSPI_RXOICR(spix)               REG32((spix) + 0x003cU + 0x00U)
#define OSPI_RXUICR(spix)               REG32((spix) + 0x0040U + 0x00U)
#define OSPI_MSTICR(spix)               REG32((spix) + 0x0044U + 0x00U)
#define OSPI_ICR(spix)                  REG32((spix) + 0x0048U + 0x00U)
#define OSPI_DMACR(spix)                REG32((spix) + 0x004cU + 0x00U)
#define OSPI_DMATDLR(spix)              REG32((spix) + 0x0050U + 0x00U)
#define OSPI_AXIAWLEN(spix)             REG32((spix) + 0x0050U + 0x00U)
#define OSPI_DMARDLR(spix)              REG32((spix) + 0x0054U + 0x00U)
#define OSPI_AXIARLEN(spix)             REG32((spix) + 0x0054U + 0x00U)
#define OSPI_IDR(spix)                  REG32((spix) + 0x0058U + 0x00U)
#define OSPI_SSIC_VERSION_ID(spix)      REG32((spix) + 0x005cU + 0x00U)
#define OSPI_DR(spix,x)                 REG32((spix) + 0x0060U + 0x04U * (x))
#define OSPI_RX_SAMPLE_DELAY(spix)      REG32((spix) + 0x00f0U + 0x00U)
#define OSPI_SPI_CTRLR0(spix)           REG32((spix) + 0x00f4U + 0x00U)
#define OSPI_DDR_DRIVE_EDGE(spix)       REG32((spix) + 0x00f8U + 0x00U)
#define OSPI_XIP_MODE_BITS(spix)        REG32((spix) + 0x00fcU + 0x00U)

#define OSPI_XIP_INCR_INST(spix)        REG32((spix) + 0x0100U + 0x00U)
#define OSPI_XIP_WRAP_INST(spix)        REG32((spix) + 0x0104U + 0x00U)
#define OSPI_XIP_CTRL(spix)             REG32((spix) + 0x0108U + 0x00U)
#define OSPI_XIP_SER(spix)              REG32((spix) + 0x010cU + 0x00U)
#define OSPI_XRXOICR(spix)              REG32((spix) + 0x0110U + 0x00U)
#define OSPI_XIP_CNT_TIME_OUT(spix)     REG32((spix) + 0x0114U + 0x00U)
#define OSPI_SPI_CTRLR1(spix)           REG32((spix) + 0x0118U + 0x00U)
#define OSPI_SPITECR(spix)              REG32((spix) + 0x011cU + 0x00U)
#define OSPI_SPIDR(spix)                REG32((spix) + 0x0120U + 0x00U)
#define OSPI_SPIAR(spix)                REG32((spix) + 0x0124U + 0x00U)
#define OSPI_AXIAR0(spix)               REG32((spix) + 0x0128U + 0x00U)
#define OSPI_AXIAR1(spix)               REG32((spix) + 0x012cU + 0x00U)
#define OSPI_AXIECR(spix)               REG32((spix) + 0x0130U + 0x00U)
#define OSPI_DONECR(spix)               REG32((spix) + 0x0134U + 0x00U)
#define OSPI_XIP_WRITE_INCR_INST(spix)  REG32((spix) + 0x0140U + 0x00U)
#define OSPI_XIP_WRITE_WRAP_INST(spix)  REG32((spix) + 0x0144U + 0x00U)
#define OSPI_XIP_WRITE_CTRL(spix)       REG32((spix) + 0x0148U + 0x00U)

/* bits definitions */
/* OSPI_CTRLR0 */
#define OSPI_CTRLR0_IS_MST              BIT(31) //DWC_SSI is Master(0x1) or Slave(0x0)
#define OSPI_CTRLR0_DWS_EN              BIT(25) //Enable Dynamic wait states when CTRLR0.FRF = 0
#define OSPI_CTRLR0_HYPERBUS_EN         BIT(24)
#define OSPI_CTRLR0_SPI_FRF             BITS(22, 23)
#define OSPI_CTRLR0_CFS                 BITS(16, 19)
#define OSPI_CTRLR0_SSTE                BIT(14)
#define OSPI_CTRLR0_SRL                 BIT(13)
#define OSPI_CTRLR0_SLV_OE              BIT(12)
#define OSPI_CTRLR0_TMOD                BITS(10, 11)
#define OSPI_CTRLR0_SCPOL               BIT(9)
#define OSPI_CTRLR0_SCPH                BIT(8)
#define OSPI_CTRLR0_FRF                 BITS(6, 7)
#define OSPI_CTRLR0_DFS                 BITS(0, 4)

/* OSPI_CTRLR1 */
#define OSPI_CTRLR1_NDF                 BITS(0, 15)

/* OSPI_SSINER */
#define OSPI_SSINER_SSI_EN              BIT(0)

/* OSPI_MWCR */
#define OSPI_MWCR_MHS                   BIT(2)
#define OSPI_MWCR_MDD                   BIT(1)
#define OSPI_MWCR_MWMOD                 BIT(0)

/* OSPI_SER */
#if PSRAM_SSIC_NUM_SLAVES > 1
    #define OSPI_SER_SLAVE_ENABLE           BITS(0, PSRAM_SSIC_NUM_SLAVES - 1)
#else
    #define OSPI_SER_SLAVE_ENABLE           BIT(0)
#endif

#define OSPI_SER_SLAVE_DISABLE          BITS(0, PSRAM_SSIC_NUM_SLAVES - 1)
/* OSPI_BAUDR */
#define OSPI_BAUDR_SCKDV                BITS(1, 15)

/* OSPI_TXFTLR */
#define OSPI_TXFTLR_TXFTHR              BITS(16, TXFTHR_W + 15)
#define OSPI_TXFTLR_TFT                 BITS(0, TX_ABW - 1)

/* OSPI_RXFTLR */
#define OSPI_RXFTLR_RFT                 BITS(0, RX_ABW - 1)

/* OSPI_TXFLR */
#define OSPI_TXFLR_TXTFL                BITS(0, TX_ABW)

/* OSPI_RXFLR */
#define OSPI_RXFLR_RXTFL                BITS(0, RX_ABW)

/* OSPI_SR */
#define OSPI_SR_CMPLTD_DF               BITS(15, 31)
#define OSPI_SR_DCOL                    BIT(6)
#define OSPI_SR_TXE                     BIT(5)
#define OSPI_SR_RFF                     BIT(4)
#define OSPI_SR_RFNE                    BIT(3)
#define OSPI_SR_TFE                     BIT(2)
#define OSPI_SR_TFNF                    BIT(1)
#define OSPI_SR_BUSY                    BIT(0)

/* OSPI_IMR */
#define OSPI_IMR_DONEM                  BIT(11) //DW
#define OSPI_IMR_SPITEM                 BIT(10) //En
#define OSPI_IMR_AXIEM                  BIT(8)
#define OSPI_IMR_TXUIM                  BIT(7)
#define OSPI_IMR_XRXOIM                 BIT(6)
#define OSPI_IMR_MSTIM                  BIT(5)
#define OSPI_IMR_RXFIM                  BIT(4)
#define OSPI_IMR_RXOIM                  BIT(3)
#define OSPI_IMR_RXUIM                  BIT(2)
#define OSPI_IMR_TXOIM                  BIT(1)
#define OSPI_IMR_TXEIM                  BIT(0)

/* OSPI_ISR */
#define OSPI_ISR_DONES                  BIT(11) //DW
#define OSPI_ISR_SPITES                 BIT(10) //En
#define OSPI_ISR_AXIES                  BIT(8)
#define OSPI_ISR_TXUIS                  BIT(7)
#define OSPI_ISR_XRXOIS                 BIT(6)
#define OSPI_ISR_MSTIS                  BIT(5)
#define OSPI_ISR_RXFIS                  BIT(4)
#define OSPI_ISR_RXOIS                  BIT(3)
#define OSPI_ISR_RXUIS                  BIT(2)
#define OSPI_ISR_TXOIS                  BIT(1)
#define OSPI_ISR_TXEIS                  BIT(0)

/* OSPI_RISR */
#define OSPI_RISR_DONER                 BIT(11) //DW
#define OSPI_RISR_SPITER                BIT(10) //En
#define OSPI_RISR_AXIER                 BIT(8)
#define OSPI_RISR_TXUIR                 BIT(7)
#define OSPI_RISR_XRXOIR                BIT(6)
#define OSPI_RISR_MSTIR                 BIT(5)
#define OSPI_RISR_RXFIR                 BIT(4)
#define OSPI_RISR_RXOIR                 BIT(3)
#define OSPI_RISR_RXUIR                 BIT(2)
#define OSPI_RISR_TXOIR                 BIT(1)
#define OSPI_RISR_TXEIR                 BIT(0)

/* OSPI_TXEICR */
#define OSPI_TXEICR_CLEAR               BIT(0)

/* OSPI_RXOICR */
#define OSPI_RXOICR_CLEAR               BIT(0)

/* OSPI_RXUICR */
#define OSPI_RXUICR_CLEAR               BIT(0)

/* OSPI_MSTICR */
#define OSPI_MSTICR_CLEAR               BIT(0)

/* OSPI_ICR */
#define OSPI_ICR_CLEAR                  BIT(0)

/* OSPI_DMACR */
// #define OSPI_DMACR_AID                  BITS(15, SSIC_AXI_IDW + 14)
#define OSPI_DMACR_APROT                BITS(12, 14)
#define OSPI_DMACR_ACACHE               BITS(8, 11)
#define OSPI_DMACR_AINC                 BIT(6)
#define OSPI_DMACR_ATW                  BITS(3, 4)
#define OSPI_DMACR_IDMAE                BIT(2)
#define OSPI_DMACR_TDMAE                BIT(1)
#define OSPI_DMACR_RDMAE                BIT(0)

/* OSPI_DMATDLR */
#define OSPI_DMATDL                     BITS(0, TX_ABW - 1)

/* OSPI_AXIAWLEN */
// #define OSPI_AWLEN                      BITS(8, SSIC_AXI_BLW)

/* OSPI_DMARDLR */
#define OSPI_DMARDL                     BITS(0, RX_ABW)

/* OSPI_AXIARLEN */
// #define OSPI_ARLEN                      BITS(8, SSIC_AXI_BLW + 7)

/* OSPI_IDR */
#define OSPI_IDR_IDCODE                 BITS(0, 31)

/* OSPI_SSIC_VERSION_ID */
#define OSPI_VERSION_ID                 BITS(0, 31)

/* OSPI_DRx */
#define OSPI_DR_DATA                    BITS(0, 31)

/* OSPI_RX_SAMPLE_DELAY */
#define OSPI_RX_SAMPLE_DELAY_SE         BIT(16)
#define OSPI_RX_SAMPLE_DELAY_RSD        BITS(0, 7)

/* OSPI_SPI_CTRLR0 */
#define OSPI_SPI_CTRLR0_CLK_STRETCH_EN  BIT(30)
#define OSPI_SPI_CTRLR0_XIP_PREFETCH_EN BIT(29)
#define OSPI_SPI_CTRLR0_XIP_MBL         BITS(26, 27)
#define OSPI_SPI_CTRLR0_SPI_DWS_EN      BIT(25)
#define OSPI_SPI_CTRLR0_SPI_DM_EN       BIT(24)
#define OSPI_SPI_CTRLR0_XIP_CONT_EN     BIT(21)
#define OSPI_SPI_CTRLR0_XIP_INST_EN     BIT(20)
#define OSPI_SPI_CTRLR0_XIP_DFS_HC      BIT(19)
#define OSPI_SPI_CTRLR0_SPI_RXDS_EN     BIT(18)
#define OSPI_SPI_CTRLR0_INST_DDR_EN     BIT(17)
#define OSPI_SPI_CTRLR0_SPI_DDR_EN      BIT(16)
#define OSPI_SPI_CTRLR0_WAIT_CYCLES     BITS(11, 15)
#define OSPI_SPI_CTRLR0_INST_L          BITS(8, 9)
#define OSPI_SPI_CTRLR0_XIP_MD_BIT_EN   BIT(7)
#define OSPI_SPI_CTRLR0_ADDR_L          BITS(2, 5)
#define OSPI_SPI_CTRLR0_TRANS_TYPE      BITS(0, 1)

/* OSPI_DDR_DRIVE_EDGE */
#define  OSPI_DDR_DRIVE_EDGE_TDE        BITS(0, 7)

/* OSPI_XIP_MODE_BITS */
#define OSPI_XIP_MID_BITS               BITS(0, 15)

/* SPI mode definitions */


#define OSPI_MASTER                     (OSPI_CTRLR0_IS_MST)      /*!< SPI as master */
#define OSPI_SLAVE                      (~OSPI_CTRLR0_IS_MST)

#define OSPI_HYPERBUS_ENABLE            (OSPI_CTRLR0_HYPERBUS_EN)
#define OSPI_HYPERBUS_DISABLE           (~OSPI_CTRLR0_HYPERBUS_EN)

#define OSPI_FRF_STANDARD               (OSPI_CTRLR0_SPI_FRF & (0x0U << 22))
#define OSPI_FRF_DUAL                   (OSPI_CTRLR0_SPI_FRF & (0x1U << 22))
#define OSPI_FRF_QUAD                   (OSPI_CTRLR0_SPI_FRF & (0x2U << 22))
#define OSPI_FRF_OCTAL                  (OSPI_CTRLR0_SPI_FRF & (0x3U << 22))

#define OSPI_SLAVE_TOGGLE_ENABLE        (OSPI_CTRLR0_SSTE)
#define OSPI_SLAVE_TOGGLE_DISABLE       (~OSPI_CTRLR0_SSTE)

#define OSPI_TRANSFER_TX_RX             (OSPI_CTRLR0_TMOD & (0x0U << 10))
#define OSPI_TRANSFER_TX_ONLY           (OSPI_CTRLR0_TMOD & (0x1U << 10))
#define OSPI_TRANSFER_RX_ONLY           (OSPI_CTRLR0_TMOD & (0x2U << 10))
#define OSPI_TRANSFER_EEPROM            (OSPI_CTRLR0_TMOD & (0x3U << 10))

#define OSPI_CLOCK_POLARITY_HIGH        (~OSPI_CTRLR0_SCPOL)
#define OSPI_CLOCK_POLARITY_LOW         (OSPI_CTRLR0_SCPOL)

#define OSPI_CLOCK_PHASE_1EDGE          (OSPI_CTRLR0_SCPH)
#define OSPI_CLOCK_PHASE_2EDGE          (~OSPI_CTRLR0_SCPH)

#define OSPI_FRAME_SPI                  (OSPI_CTRLR0_FRF & (0x0U << 6))
#define OSPI_FRAME_SSP                  (OSPI_CTRLR0_FRF & (0x1U << 6))
#define OSPI_FRAME_MICROWARE            (OSPI_CTRLR0_FRF & (0x2U << 6))
#define OSPI_FRAME_RSVD                 (OSPI_CTRLR0_FRF & (0x3U << 6))

#define OSPI_DATA_SIZE_1BIT             (OSPI_CTRLR0_DFS & (0x00U << 0))
#define OSPI_DATA_SIZE_2BIT             (OSPI_CTRLR0_DFS & (0x01U << 0))
#define OSPI_DATA_SIZE_3BIT             (OSPI_CTRLR0_DFS & (0x02U << 0))
#define OSPI_DATA_SIZE_4BIT             (OSPI_CTRLR0_DFS & (0x03U << 0))
#define OSPI_DATA_SIZE_5BIT             (OSPI_CTRLR0_DFS & (0x04U << 0))
#define OSPI_DATA_SIZE_6BIT             (OSPI_CTRLR0_DFS & (0x05U << 0))
#define OSPI_DATA_SIZE_7BIT             (OSPI_CTRLR0_DFS & (0x06U << 0))
#define OSPI_DATA_SIZE_8BIT             (OSPI_CTRLR0_DFS & (0x07U << 0))
#define OSPI_DATA_SIZE_9BIT             (OSPI_CTRLR0_DFS & (0x08U << 0))
#define OSPI_DATA_SIZE_10BIT            (OSPI_CTRLR0_DFS & (0x09U << 0))
#define OSPI_DATA_SIZE_11BIT            (OSPI_CTRLR0_DFS & (0x0AU << 0))
#define OSPI_DATA_SIZE_12BIT            (OSPI_CTRLR0_DFS & (0x0BU << 0))
#define OSPI_DATA_SIZE_13BIT            (OSPI_CTRLR0_DFS & (0x0CU << 0))
#define OSPI_DATA_SIZE_14BIT            (OSPI_CTRLR0_DFS & (0x0DU << 0))
#define OSPI_DATA_SIZE_15BIT            (OSPI_CTRLR0_DFS & (0x0EU << 0))
#define OSPI_DATA_SIZE_16BIT            (OSPI_CTRLR0_DFS & (0x0FU << 0))
#define OSPI_DATA_SIZE_17BIT            (OSPI_CTRLR0_DFS & (0x10U << 0))
#define OSPI_DATA_SIZE_18BIT            (OSPI_CTRLR0_DFS & (0x11U << 0))
#define OSPI_DATA_SIZE_19BIT            (OSPI_CTRLR0_DFS & (0x12U << 0))
#define OSPI_DATA_SIZE_20BIT            (OSPI_CTRLR0_DFS & (0x13U << 0))
#define OSPI_DATA_SIZE_21BIT            (OSPI_CTRLR0_DFS & (0x14U << 0))
#define OSPI_DATA_SIZE_22BIT            (OSPI_CTRLR0_DFS & (0x15U << 0))
#define OSPI_DATA_SIZE_23BIT            (OSPI_CTRLR0_DFS & (0x16U << 0))
#define OSPI_DATA_SIZE_24BIT            (OSPI_CTRLR0_DFS & (0x17U << 0))
#define OSPI_DATA_SIZE_25BIT            (OSPI_CTRLR0_DFS & (0x18U << 0))
#define OSPI_DATA_SIZE_26BIT            (OSPI_CTRLR0_DFS & (0x19U << 0))
#define OSPI_DATA_SIZE_27BIT            (OSPI_CTRLR0_DFS & (0x1AU << 0))
#define OSPI_DATA_SIZE_28BIT            (OSPI_CTRLR0_DFS & (0x1BU << 0))
#define OSPI_DATA_SIZE_29BIT            (OSPI_CTRLR0_DFS & (0x1CU << 0))
#define OSPI_DATA_SIZE_30BIT            (OSPI_CTRLR0_DFS & (0x1DU << 0))
#define OSPI_DATA_SIZE_31BIT            (OSPI_CTRLR0_DFS & (0x1EU << 0))
#define OSPI_DATA_SIZE_32BIT            (OSPI_CTRLR0_DFS & (0x1FU << 0))

#define OSPI_SELECT_ENABLE(x)           (OSPI_SER_SLAVE_ENABLE & (0x1U << (x)))
#define OSPI_SELECT_DISABLE(x)          (OSPI_SER_SLAVE_ENABLE & ~(0x1U << (x)))

#define OSPI_CLOCK_STRETCH_ENABLE       (OSPI_SPI_CTRLR0_CLK_STRETCH_EN)
#define OSPI_CLOCK_STRETCH_DISABLE      (~OSPI_SPI_CTRLR0_CLK_STRETCH_EN)

#define OSPI_RXDS_ENABLE                (OSPI_SPI_CTRLR0_SPI_RXDS_EN)
#define OSPI_RXDS_DISABLE               (~OSPI_SPI_CTRLR0_SPI_RXDS_EN)

#define OSPI_DDR_ENABLE                 (OSPI_SPI_CTRLR0_SPI_DDR_EN)
#define OSPI_DDR_DISABLE                (~OSPI_SPI_CTRLR0_SPI_DDR_EN)

#define OSPI_WAIT_CYCLES(x)             (OSPI_SPI_CTRLR0_WAIT_CYCLES & ((x) << 11))

#define OSPI_ISTRUCTION_LEN0            (OSPI_SPI_CTRLR0_INST_L & (0x0U << 8))
#define OSPI_ISTRUCTION_LEN4            (OSPI_SPI_CTRLR0_INST_L & (0x1U << 8))
#define OSPI_ISTRUCTION_LEN8            (OSPI_SPI_CTRLR0_INST_L & (0x2U << 8))
#define OSPI_ISTRUCTION_LEN16           (OSPI_SPI_CTRLR0_INST_L & (0x3U << 8))

#define OSPI_ADDRESS_LEN0               (OSPI_SPI_CTRLR0_ADDR_L & (0x0U << 2))
#define OSPI_ADDRESS_LEN4               (OSPI_SPI_CTRLR0_ADDR_L & (0x1U << 2))
#define OSPI_ADDRESS_LEN8               (OSPI_SPI_CTRLR0_ADDR_L & (0x2U << 2))
#define OSPI_ADDRESS_LEN12              (OSPI_SPI_CTRLR0_ADDR_L & (0x3U << 2))
#define OSPI_ADDRESS_LEN16              (OSPI_SPI_CTRLR0_ADDR_L & (0x4U << 2))
#define OSPI_ADDRESS_LEN20              (OSPI_SPI_CTRLR0_ADDR_L & (0x5U << 2))
#define OSPI_ADDRESS_LEN24              (OSPI_SPI_CTRLR0_ADDR_L & (0x6U << 2))
#define OSPI_ADDRESS_LEN28              (OSPI_SPI_CTRLR0_ADDR_L & (0x7U << 2))
#define OSPI_ADDRESS_LEN32              (OSPI_SPI_CTRLR0_ADDR_L & (0x8U << 2))
#define OSPI_ADDRESS_LEN36              (OSPI_SPI_CTRLR0_ADDR_L & (0x9U << 2))
#define OSPI_ADDRESS_LEN40              (OSPI_SPI_CTRLR0_ADDR_L & (0xAU << 2))
#define OSPI_ADDRESS_LEN44              (OSPI_SPI_CTRLR0_ADDR_L & (0xBU << 2))
#define OSPI_ADDRESS_LEN48              (OSPI_SPI_CTRLR0_ADDR_L & (0xCU << 2))
#define OSPI_ADDRESS_LEN52              (OSPI_SPI_CTRLR0_ADDR_L & (0xDU << 2))
#define OSPI_ADDRESS_LEN56              (OSPI_SPI_CTRLR0_ADDR_L & (0xEU << 2))
#define OSPI_ADDRESS_LEN60              (OSPI_SPI_CTRLR0_ADDR_L & (0xFU << 2))

#define OSPI_TRANS_TYPE0                (OSPI_SPI_CTRLR0_TRANS_TYPE & (0x0U << 0))
#define OSPI_TRANS_TYPE1                (OSPI_SPI_CTRLR0_TRANS_TYPE & (0x1U << 0))
#define OSPI_TRANS_TYPE2                (OSPI_SPI_CTRLR0_TRANS_TYPE & (0x2U << 0))
#define OSPI_TRANS_TYPE3                (OSPI_SPI_CTRLR0_TRANS_TYPE & (0x3U << 0))

typedef enum {
    PSRAM_STD = 0,
    PSRAM_DUAL,
    PSRAM_QUAD,
    PSRAM_OCTAL
}emPSRAMMODE;

typedef enum {
    PSRAM_WR = 0x0000,
    PSRAM_WO = 0x0400,
    PSRAM_RO = 0x0800,
    PSRAM_ER = 0x0C00,
}emPSRAMRW;

typedef enum {
    PSRAM_SPI_MODE0= 0x0000,
    PSRAM_SPI_MODE1= 0x0100,
    PSRAM_SPI_MODE2= 0x0200,
    PSRAM_SPI_MODE3= 0x0300,
}emPSRAMSPIMODE;

typedef enum {
    PSRAM_ADDR_NONE = 0x00,
    PSRAM_ADDR_4BIT = 0x04,
    PSRAM_ADDR_8BIT = 0x08,
    PSRAM_ADDR_12BIT = 0x0C,
    PSRAM_ADDR_16BIT = 0x10,
    PSRAM_ADDR_20BIT = 0x14,
    PSRAM_ADDR_24BIT = 0x18,
    PSRAM_ADDR_28BIT = 0x1C,
    PSRAM_ADDR_32BIT = 0x20,
    PSRAM_ADDR_36BIT = 0x24,
    PSRAM_ADDR_40BIT = 0x28,
    PSRAM_ADDR_44BIT = 0x2C,
    PSRAM_ADDR_48BIT = 0x30,
    PSRAM_ADDR_52BIT = 0x34,
    PSRAM_ADDR_56BIT = 0x38,
    PSRAM_ADDR_60BIT = 0x3C,
}emPSRAMADDR;

typedef enum {
    PSRAM_BYTE = 7,
    PSRAM_SHORT = 15,
    PSRAM_WORD = 31,
}emPDT;

int ospi_init_xip(uint32_t spix, uint32_t clock, uint32_t ospi_clock);
void clear_ospi_state(uint32_t spix);
int ospi_config(uint32_t spix, uint32_t tx_fifo, uint32_t rx_fifo, uint32_t ndf, emPSRAMRW rw, emPSRAMSPIMODE spi_mode, uint8_t waitcycle, emPSRAMADDR addr, uint8_t dsize);
int debug_test_psram(void);

#endif /* PSRAM_H_ */
