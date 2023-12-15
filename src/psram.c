/*
 * @Author       : panxinhao
 * @Date         : 2023-11-22 16:31:18
 * @LastEditors  : panxinhao
 * @LastEditTime : 2023-11-22 18:27:02
 * @FilePath     : \\ceva_no_ecc_test_ext_4m\\test_data_ext_mem\\src\\ospi.c
 * @Description  :
 *
 * Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved.
 */

/*
 * ospi.c
 *
 *  Created on: 2023楠烇拷11閺堬拷22閺冿拷
 *      Author: xinhao
 */

#include "psram.h"
#include "axi_dma.h"
#include "debug.h"

int ospi_init(uint32_t spix, uint32_t clock, uint32_t ospi_clock)
{
    uint32_t temp;
    OSPI_SSIENR(spix) = 0;
    OSPI_SER(spix) = 0;
    OSPI_IMR(spix) = 0;
    OSPI_CTRLR1(spix) = 0;
    OSPI_TXFTLR(spix) = 0;
    OSPI_RXFTLR(spix) = 0;
    clear_ospi_state(spix);
    temp = 0;
    temp |= 0
            | 1 << 31
            | 1 << 25
            | 1 << 24
            | 3 << 22
            | 0 << 14
            | 0 << 10
            | 0 << 9
            | 0 << 8
            | 0 << 6
            | 0x7;
    OSPI_CTRLR0(spix) = temp;
    temp = 0;
    temp |= 0
            | 1 << 30
            | 0 << 29
            | 0 << 26
            | 1 << 25
            | 1 << 24
            | 0 << 21
            | 0 << 20
            | 0 << 19
            | 1 << 18
            | 1 << 17
            | 1 << 16
            | 0 << 11
            | 0 << 8
            | 0 << 7
            | 0xc << 2
            | 0x2;
    OSPI_SPI_CTRLR0(spix) = temp;
    if (OSPI_CTRLR0(spix) & 0x2000000)
    {
        /* code */
        temp = 0;
        temp |= 0
                | 15 << 8
                | 0;
        OSPI_SPI_CTRLR1(spix) =  temp;
    }
    OSPI_BAUDR(spix) = clock / ospi_clock;
    OSPI_DDR_DRIVE_EDGE(spix) =  clock / (ospi_clock * 2) - 1;
    OSPI_TXFTLR(spix) = 0;
    OSPI_RXFTLR(spix) = 0;
    OSPI_IMR(spix) = 0;
    OSPI_SER(spix) |= 1;
    OSPI_SSIENR(spix) |= 1;
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    return 0;
}

int ospi_init_xip(uint32_t spix, uint32_t clock, uint32_t ospi_clock)
{
    uint32_t temp;
    OSPI_SSIENR(spix) = 0;
    OSPI_SER(spix) = 0;
    OSPI_IMR(spix) = 0;
    OSPI_CTRLR1(spix) = 0;
    OSPI_TXFTLR(spix) = 0;
    OSPI_RXFTLR(spix) = 0;
    clear_ospi_state(spix);
    temp = 0;
    temp |= 0
            | 1 << 31
            | 1 << 25
            | 1 << 24
            | 3 << 22
            | 0 << 14
            | 0 << 10
            | 0 << 9
            | 0 << 8
            | 0 << 6
            | 0x7;
    OSPI_CTRLR0(spix) = temp;
    temp = 0;
    temp |= 0
            | 1 << 30
            | 0 << 29
            | 0 << 26
            | 1 << 25
            | 1 << 24
            | 0 << 21
            | 1 << 20
            | 0 << 19
            | 1 << 18
            | 1 << 17
            | 1 << 16
            | 7 << 11
            | 0 << 8
            | 0 << 7
            | 0xc << 2
            | 0x2;
    OSPI_SPI_CTRLR0(spix) = temp;
    // if (OSPI_CTRLR0(spix) & 0x2000000)
    // {
    //     /* code */
    //     temp = 0;
    //     temp |= 0
    //             | 15 << 8
    //             | 0;
    //     OSPI_SPI_CTRLR1(spix) =  temp;
    // }
    OSPI_BAUDR(spix) = clock / ospi_clock;
    OSPI_RX_SAMPLE_DELAY(spix) = 1 << 16 | 10;
    OSPI_DDR_DRIVE_EDGE(spix) =  1;
    OSPI_TXFTLR(spix) = 0;
    OSPI_RXFTLR(spix) = 0;
    OSPI_IMR(spix) = 0;
    temp = 0;
    temp &= ~(1 << 29 | 3 << 26 | 7 << 22 | 7 << 18 | 0 << 13 | 3 << 9 | 0xf << 4 | 3 << 2 | 3);
    temp |= 0
            | 0 << 29
            | 2 << 26
            | 1 << 25
            | 1 << 24
            | 0 << 23
            | 1 << 22
            | 1 << 21
            | 1 << 20
            | 1 << 19
            | 0 << 18
            | 7 << 13
            | 0 << 12
            | 0 << 9
            | 0xc << 4
            | 2 << 2
            | 3;
    OSPI_XIP_CTRL(spix) = temp;
    temp = OSPI_XRXOICR(spix);
    if (OSPI_CTRLR0(spix) & 0x2000000)
    {
        /* code */
        temp = OSPI_SPI_CTRLR1(spix);
        temp &= ~(0xf << 8 | 0x7);
        temp |= 0
                | 0 << 8
                | 0;
        OSPI_SPI_CTRLR1(spix) =  temp;
        temp = OSPI_SPITECR(spix);
    }
    OSPI_XIP_WRITE_INCR_INST(spix) = 0x2;
    OSPI_XIP_WRITE_WRAP_INST(spix) = 0x0;
    OSPI_XIP_INCR_INST(spix) = 0xa;
    OSPI_XIP_WRAP_INST(spix) = 0x8;
    temp = 0;
    temp &= ~(0x1f << 16 | 7 << 10 | 3 << 8 | 0xff);
    temp |= 0
            | 7 << 16
            | 1 << 13
            | 1 << 12
            | 1 << 11
            | 1 << 10
            | 0 << 8
            | 0xc << 4
            | 2 << 2
            | 3;
    OSPI_XIP_WRITE_CTRL(spix) = temp;
    OSPI_XIP_MODE_BITS(spix) = 0;
    OSPI_XIP_SER(spix) |= 1;
    OSPI_SER(spix) |= 1;
    OSPI_SSIENR(spix) |= 1;
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    REG32(SCTRL_BASE + 0x0c) |= 1; //enable psram xip
    return 0;
}

int ospi_config(uint32_t spix, uint32_t tx_fifo, uint32_t rx_fifo, uint32_t ndf, emPSRAMRW rw, emPSRAMSPIMODE spi_mode, uint8_t waitcycle, emPSRAMADDR addr, uint8_t dsize)
{
    uint32_t temp, temp1;
    OSPI_SSIENR(spix) &= ~1;
    temp = OSPI_CTRLR0(spix);
    temp &= ~(0xf << 8 | 0x1F);
    dsize &= 0x1f;
    temp |= rw | spi_mode | dsize;
    temp1 = OSPI_SPI_CTRLR0(spix);
    temp1 &= ~(0x1f << 11 | 0xf << 2);
    temp1 |= addr | ((waitcycle & 0x1f) << 11);
    OSPI_CTRLR0(spix) = temp;
    OSPI_SPI_CTRLR0(spix) = temp1;
    if (OSPI_CTRLR0(spix) & 0x2000000)
    {
        /* code */
        temp = OSPI_SPI_CTRLR1(spix);
        temp &= ~(0xf << 8 | 0x1f);
        temp |= 0 << 8
                | 0;
        OSPI_SPI_CTRLR1(spix) = temp;
    }
    OSPI_TXFTLR(spix) = tx_fifo;
    OSPI_RXFTLR(spix) = rx_fifo;
    OSPI_CTRLR1(spix) = ndf - 1;
    OSPI_IMR(spix) = 0;
    OSPI_SER(spix) |= 1;
    OSPI_SSIENR(spix) |= 1;
    return 0;
}

void clear_ospi_state(uint32_t spix)
{
    uint32_t temp;
    temp = OSPI_TXEICR(spix);
    temp = OSPI_RXOICR(spix);
    temp = OSPI_RXUICR(spix);
    temp = OSPI_MSTICR(spix);
    temp = OSPI_ICR(spix);
    temp = OSPI_SR(spix);
    (void)temp;
}

int ca(char isread, char isregister, char islinearburst, uint32_t addr, uint32_t *out)
{
    uint32_t temp;
    temp = 0;
    if (isread) temp |= 0x80000000;
    if (isregister) temp |= 0x40000000;
    if (islinearburst) temp |= 0x20000000;
    temp |= (addr >> 3) & 0x1fffffff;
    out[0] = temp;
    temp = (addr & 7);
    out[1] = temp;
    return 0;
}

void clear_spi_fifo(uint32_t spix)
{
    uint32_t temp;
    while (OSPI_SR(spix) & OSPI_SR_RFNE)
    {
        /* code */
        temp = OSPI_DR(spix, 0);
    }
    (void)temp;
}

int read_psram_id(uint32_t spix, uint32_t *id)
{
    uint32_t temp;
    uint32_t waitcycle;
    uint8_t ndf;
    uint32_t tx_fifo, rx_fifo;
    uint32_t cmd[2];
    ndf = 1;
    tx_fifo = 0x10000;
    rx_fifo = 0x0000;
    waitcycle = 7;
    ospi_config(OSPI0, tx_fifo, rx_fifo, ndf, PSRAM_RO, PSRAM_SPI_MODE0, waitcycle, PSRAM_ADDR_48BIT, PSRAM_SHORT);
    while ((OSPI_SR(spix) & (OSPI_SR_TFE | OSPI_SR_BUSY)) != OSPI_SR_TFE);
    while ((OSPI_SR(spix) & OSPI_SR_TFNF) == 0);
    ca(1, 1, 0, 0, cmd);
    OSPI_DR(spix, 0) = cmd[0];
    OSPI_DR(spix, 0) = cmd[1];
    while ((OSPI_SR(spix) & OSPI_SR_TFE) == 0);
    while ((OSPI_SR(spix) & OSPI_SR_RFNE) == 0);
    temp = OSPI_DR(spix, 0);
    id[0] = (temp & 0xffff) << 16;
    ca(1, 1, 0, 1, cmd);
    OSPI_DR(spix, 0) = cmd[0];
    OSPI_DR(spix, 0) = cmd[1];
    while ((OSPI_SR(spix) & OSPI_SR_TFE) == 0);
    while ((OSPI_SR(spix) & OSPI_SR_RFNE) == 0);
    temp = OSPI_DR(spix, 0);
    id[0] |= (temp & 0xffff);
    clear_spi_fifo(spix);
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    clear_ospi_state(spix);
    (void)temp;
    return 0;
}

uint32_t read_write_psram_status(uint32_t spix, uint32_t cmd, uint16_t val)
{
    uint32_t temp, waitcycles, tx_fifo, rx_fifo, cmd_out[2];
    uint8_t ndf;
    if ((cmd & READ_REGISTER0) == READ_REGISTER0)
    {
        /* code */
        ndf = 1;
        tx_fifo = 0x10000;
        rx_fifo = 0;
        waitcycles = 7;
        ospi_config(OSPI0, tx_fifo, rx_fifo, ndf, PSRAM_RO, PSRAM_SPI_MODE0, waitcycles, PSRAM_ADDR_48BIT, PSRAM_SHORT);
        ca(1, 1, 0, cmd & 0xfff, cmd_out);
        temp = 0;
    }
    else
    {
        ndf = 1;
        tx_fifo = 0x20000;
        rx_fifo = 0;
        waitcycles = 0;
        ospi_config(OSPI0, tx_fifo, rx_fifo, ndf, PSRAM_WO, PSRAM_SPI_MODE0, waitcycles, PSRAM_ADDR_48BIT, PSRAM_SHORT);
        ca(0, 1, 0, cmd & 0xfff, cmd_out);
    }
    while ((OSPI_SR(spix) & (OSPI_SR_TFE | OSPI_SR_BUSY)) != OSPI_SR_TFE);
    while ((OSPI_SR(spix) & OSPI_SR_TFNF) == 0);
    OSPI_DR(spix, 0) = cmd_out[0];
    OSPI_DR(spix, 0) = cmd_out[1];
    if ((cmd & WRITE_REGISTER0) == WRITE_REGISTER0)
    {
        /* code */
        OSPI_DR(spix, 0) = val;
    }
    while ((OSPI_SR(spix) & OSPI_SR_TFE) == 0);
    if ((cmd & READ_REGISTER0) == READ_REGISTER0)
    {
        /* code */
        while ((OSPI_SR(spix) & OSPI_SR_RFNE) == 0);
        temp = OSPI_DR(spix, 0);
        temp &= 0xffff;
    }
    clear_spi_fifo(spix);
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    clear_ospi_state(spix);
    return temp;
}

int write_psram_unit(uint32_t spix, uint32_t addr, void *data, uint32_t len, emPDT type, char islinearburst)
{
    uint32_t waitcycles, tx_fifo, rx_fifo, cmd[2];
    uint8_t ndf;
    uint8_t *pthis = (uint8_t *)data;
    uint16_t *pthis16 = (uint16_t *)data;
    uint32_t *pthis32 = (uint32_t *)data;
    switch (type)
    {
    case PSRAM_BYTE:
        /* code */
        break;
    case PSRAM_SHORT:
        /* code */
        len  >>= 1;
        break;
    case PSRAM_WORD:
        /* code */
        len >>= 2;
        break;
    default:
        break;
    }
    ndf = len;
    tx_fifo = (len - 1) << 16;
    rx_fifo = 0;
    waitcycles = 7;
    ospi_config(spix, tx_fifo, rx_fifo, ndf, PSRAM_WO, PSRAM_SPI_MODE0, waitcycles, PSRAM_ADDR_48BIT, type);
    ca(0, 0, islinearburst, addr, cmd);
    while ((OSPI_SR(spix) & (OSPI_SR_TFE | OSPI_SR_BUSY)) != OSPI_SR_TFE);
    while ((OSPI_SR(spix) & OSPI_SR_TFNF) == 0);
    OSPI_DR(spix, 0) = cmd[0];
    OSPI_DR(spix, 0) = cmd[1];
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        while ((OSPI_SR(spix) & OSPI_SR_TFNF) == 0);
        switch (type)
        {
        default:
        case PSRAM_BYTE:
            /* code */
            OSPI_DR(spix, 0) = pthis[i];
            break;
        case PSRAM_SHORT:
            /* code */
            OSPI_DR(spix, 0) = pthis16[i];
            break;
        case PSRAM_WORD:
            /* code */
            OSPI_DR(spix, 0) = pthis32[i];
            break;
        }
    }
    while ((OSPI_SR(spix) & OSPI_SR_TFE) == 0);
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    clear_ospi_state(spix);
    return 0;
}

int read_psram_unit(uint32_t spix, uint32_t addr, void *data, uint32_t len, emPDT type, char islinearburst)
{
    uint32_t waitcycles, tx_fifo, rx_fifo, cmd[2];
    uint8_t ndf;
    uint8_t *pthis = (uint8_t *)data;
    uint16_t *pthis16 = (uint16_t *)data;
    uint32_t *pthis32 = (uint32_t *)data;
    switch (type)
    {
    case PSRAM_BYTE:
        /* code */
        break;
    case PSRAM_SHORT:
        /* code */
        len  >>= 1;
        break;
    case PSRAM_WORD:
        /* code */
        len >>= 2;
        break;
    default:
        break;
    }
    ndf = len;
    tx_fifo = 0x10000;
    rx_fifo = len - 1;
    waitcycles = 7;
    ospi_config(spix, tx_fifo, rx_fifo, ndf, PSRAM_RO, PSRAM_SPI_MODE0, waitcycles, PSRAM_ADDR_48BIT, type);
    ca(1, 0, islinearburst, addr, cmd);
    while ((OSPI_SR(spix) & (OSPI_SR_TFE | OSPI_SR_BUSY)) != OSPI_SR_TFE);
    while ((OSPI_SR(spix) & OSPI_SR_TFNF) == 0);
    OSPI_DR(spix, 0) = cmd[0];
    OSPI_DR(spix, 0) = cmd[1];
    while ((OSPI_SR(spix) & OSPI_SR_TFE) == 0);
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        while ((OSPI_SR(spix) & OSPI_SR_RFNE) == 0);
        switch (type)
        {
        default:
        case PSRAM_BYTE:
            /* code */
            pthis[i] = OSPI_DR(spix, 0);
            break;
        case PSRAM_SHORT:
            /* code */
            pthis16[i] = OSPI_DR(spix, 0);
            break;
        case PSRAM_WORD:
            /* code */
            pthis32[i] = OSPI_DR(spix, 0);
            break;
        }
    }
    clear_spi_fifo(spix);
    while (OSPI_SR(spix) & OSPI_SR_BUSY);
    clear_ospi_state(spix);
    return 0;
}

uint16_t data16[] = {0x1234, 0x5678, 0x9abc, 0xdef0, 0x1111, 0x2222, 0x3333, 0x4444,
                     0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0xaaaa, 0xbbbb, 0xcccc,
                    };
uint32_t data32[] = {0x12345678, 0x9abcdef0, 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666,
                     0x77777777, 0x88888888, 0x99999999, 0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee
                    };
uint16_t rdata16[16];
uint32_t rdata32[16];
int debug_test_psram(void)
{
    uint32_t id;
    uint32_t sys_clock = 50000000;
    uint32_t psram_clock = 10000000;
    REG32(SCTRL_BASE + 0x0c) &= ~1; //disable psram xip
    // for (int i = 0; i < 1000; i++)
    // {
    //     // REG32(0x4407FFF0) = i;
    // }
    /* Test start */
    debug_init(TEST_CODE_PSRAM);
    ospi_init(OSPI0, sys_clock, psram_clock);
    /* Test 1: read id*/
    {
        debug_new_case();
        read_psram_id(OSPI0, &id);
        if (id != 0x0f860001)
        {
            /* code */
            debug_case_set_failed(id);
        }
        case_finish();
    }
    /* Test 2: read register0*/
    uint32_t temp;
    {
        debug_new_case();
        temp = 0;
        temp = read_write_psram_status(OSPI0, READ_REGISTER0, temp);
        if (temp != 0x8f2f)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 3: read register1*/
    {
        debug_new_case();
        temp = 0;
        temp = read_write_psram_status(OSPI0, READ_REGISTER1, temp);
        if (temp != 0xffc1)
        {
            /* code */
            debug_case_set_failed(temp);
        }
        case_finish();
    }
    /* Test 4: write&read uint16*/
    {
        debug_new_case();
        write_psram_unit(OSPI0, 0x0000, data16, sizeof(data16), PSRAM_SHORT, 0);
        memset(rdata16, 0, sizeof(rdata16));
        read_psram_unit(OSPI0, 0x0000, rdata16, sizeof(rdata16), PSRAM_SHORT, 0);
        for (size_t i = 0; i < sizeof(rdata16) / sizeof(uint16_t); i++)
        {
            /* code */
            if (rdata16[i] != data16[i])
            {
                /* code */
                debug_case_set_failed(rdata16[i]);
            }
        }
        case_finish();
    }
    /* Test 5: write&read uint32*/
    {
        debug_new_case();
        write_psram_unit(OSPI0, 0x0000, data32, sizeof(data32), PSRAM_WORD, 1);
        memset(rdata32, 0, sizeof(rdata32));
        read_psram_unit(OSPI0, 0x0000, rdata32, sizeof(rdata32), PSRAM_WORD, 1);
        for (size_t i = 0; i < sizeof(rdata32) / sizeof(uint32_t); i++)
        {
            /* code */
            if (rdata32[i] != data32[i])
            {
                /* code */
                debug_case_set_failed(rdata32[i]);
            }
        }
        case_finish();
    }
    ospi_init_xip(OSPI0, sys_clock, psram_clock);
    REG32(SCTRL_BASE + 0x0c) |= 1; //enable psram xip
    /* Test 6: write&read xip uint16*/
    {
        debug_new_case();
        uint16_t *data16_xip = (uint16_t *)PSRAM_BASE;
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            data16_xip[i] = i;
        }
        for (size_t i = 0; i < 16; i++)
        {
            /* code */
            if (data16_xip[i] != i)
            {
                /* code */
                debug_case_set_failed(data16_xip[i]);
            }
        }
        case_finish();
    }
    /* Test 7: write&read xip uint32*/
    {
        debug_new_case();
        uint32_t *data32_xip = (uint32_t *)PSRAM_BASE;
        for (size_t i = 0; i < 0x40; i++)
        {
            /* code */
            data32_xip[i] = i;
        }
        for (size_t i = 0; i < 0x40; i++)
        {
            /* code */
            if (data32_xip[i] != i)
            {
                /* code */
                debug_case_set_failed(data32_xip[i]);
            }
        }
        case_finish();
    }
    axi_dma_enable(DSP_DMA);
    /* Test 8: dma psram sram0 */
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            /* code */
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint32_t *data32_sram0 = (uint32_t *)(DSP_RAM0_BASE + 0x30000);
            axi_dma_start(DSP_DMA, chx, PSRAM_BASE, DSP_RAM0_BASE + 0x30000);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x20; i++)
            {
                /* code */
                if (data32_sram0[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data32_sram0[i]);
                }
            }
        }
        case_finish();
    }
    /* Test 9: dma psram sram1 */
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint32_t *data32_sram1 = (uint32_t *)DSP_RAM1_BASE;
            axi_dma_start(DSP_DMA, chx, PSRAM_BASE, DSP_RAM1_BASE);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x20; i++)
            {
                /* code */
                if (data32_sram1[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data32_sram1[i]);
                }
            }
        }
        case_finish();
    }
    /* Test 12: dma ch1 psram psram */
    {
        debug_new_case();
        for (size_t chx = 1; chx <= 8; chx++)
        {
            axi_dma_init(DSP_DMA, chx, 0x80, 16, 16);
            uint32_t *data32_psram2 = (uint32_t *)(PSRAM_BASE + 0x0FFFF00);
            axi_dma_start(DSP_DMA, chx, PSRAM_BASE, PSRAM_BASE + 0x0FFFF00);
            while (AXI_DMA_CHEN(DSP_DMA) & (AXI_DMA_CHEN_CH_EN & (0x01ULL << (chx - 1))));
            for (size_t i = 0; i < 0x20; i++)
            {
                /* code */
                if (data32_psram2[i] != i)
                {
                    /* code */
                    debug_case_set_failed(data32_psram2[i]);
                }
            }
        }
        case_finish();
    }
    /* Test finished */
    debug_finish();
    return 0;
}

