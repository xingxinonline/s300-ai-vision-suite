/*
 * reg.h
 *
 *  Created on: 2023楠烇拷11閺堬拷22閺冿拷
 *      Author: xinhao
 */

#ifndef REG_H_
#define REG_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* bit operations */
#define REG64(addr)         (*(volatile uint64_t *)(uint64_t)(addr))
#define REG32(addr)         (*(volatile uint32_t *)(uint64_t)(addr))
#define REG16(addr)         (*(volatile uint16_t *)(uint64_t)(addr))
#define REG8(addr)          (*(volatile uint8_t  *)(uint64_t)(addr))

#define BIT(x)                          ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)                ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end)    (((regval) & BITS((start),(end))) >> (start))

#define BIT_64(x)          ((uint64_t)((uint64_t)0x01ULL << (x)))
#define BITS_64(start, end) ((0xFFFFFFFFFFFFFFFFULL << (start)) & (0xFFFFFFFFFFFFFFFFULL >> (63ULL - (uint64_t)(end))))
#define GET_BITS_64(regval, start, end) (((regval)&BITS((start), (end))) >> (start))

/* m4 addr*/
#define ARM_ROM_BASE	    0x00000000UL  // 0x0000_0000 ~ 0x0000_27FF
#define FLASH_BASE		    0x08000000UL  // 0x0800_0000 ~ 0x09FF_FFFF
#define ARM_RAM0_BASE	    0x10000000UL  // 0x1000_0000 ~ 0x1000_1FFF
#define ARM_RAM1_BASE	    0x20000000UL  // 0x2000_0000 ~ 0x2005_FFFF

/* APB0 addr 0x4000_0000~0x4000_FFFF*/
#define TIMER0_BASE         0x40000000UL  // 0x4000_0000 ~ 0x4000_0FFF
#define TIMER1_BASE         0x40001000UL  // 0x4000_1000 ~ 0x4000_1FFF
#define TIMER2_BASE         0x40002000UL  // 0x4000_2000 ~ 0x4000_2FFF
#define WDT0_BASE           0x40003000UL  // 0x4000_3000 ~ 0x4000_3FFF
#define WDT1_BASE           0x40004000UL  // 0x4000_4000 ~ 0x4000_4FFF
#define WDT2_BASE           0x40005000UL  // 0x4000_5000 ~ 0x4000_5FFF
#define WDT3_BASE           0x40006000UL  // 0x4000_6000 ~ 0x4000_6FFF
#define INT_CTRL_BASE       0x40007000UL  // 0x4000_7000 ~ 0x4000_7FFF
#define IO_MATRIX_BASE      0x40008000UL  // 0x4000_8000 ~ 0x4000_8FFF
#define IO_MUX_BASE         0x40009000UL  // 0x4000_9000 ~ 0x4000_9FFF
#define RCC_BASE            0x4000A000UL  // 0x4000_A000 ~ 0x4000_AFFF
#define SEC_BASE            0x4000B000UL  // 0x4000_B000 ~ 0x4000_BFFF
#define SCTRL_BASE          0x4000C000UL  // 0x4000_C000 ~ 0x4000_CFFF
#define QSPI_CFG_BASE       0x4000D000UL  // 0x4000_D000 ~ 0x4000_DFFF
#define SECOTP1_BASE        0x4000E000UL  // 0x4000_E000 ~ 0x4000_EFFF
#define SECOTP2_BASE        0x4000F000UL  // 0x4000_F000 ~ 0x4000_FFFF

/* APB1 addr 0x4001_0000~0x4001_FFFF*/
#define UART0_BASE	        0x40010000UL  // 0x4001_0000 ~ 0x4001_FFFF
#define UART1_BASE	        0x40011000UL  // 0x4001_1000 ~ 0x4001_1FFF
#define UART2_BASE	        0x40012000UL  // 0x4001_2000 ~ 0x4001_2FFF
#define UART3_BASE	        0x40013000UL  // 0x4001_3000 ~ 0x4001_3FFF
#define I2C0_BASE	        0x40014000UL  // 0x4001_4000 ~ 0x4001_4FFF
#define I2C1_BASE	        0x40015000UL  // 0x4001_5000 ~ 0x4001_5FFF
#define I2C2_BASE	        0x40016000UL  // 0x4001_6000 ~ 0x4001_6FFF
#define I2C3_BASE	        0x40017000UL  // 0x4001_7000 ~ 0x4001_7FFF
#define GPIO_BASE	        0x40018000UL  // 0x4001_8000 ~ 0x4001_8FFF
#define MAILBOX_BASE	    0x40019000UL  // 0x4001_9000 ~ 0x4001_9FFF
#define I2S0_BASE	        0x4001B000UL  // 0x4001_B000 ~ 0x4001_BFFF
#define I2S1_BASE	        0x4001C000UL  // 0x4001_C000 ~ 0x4001_CFFF
#define PWM_BASE	        0x4001D000UL  // 0x4001_D000 ~ 0x4001_DFFF
#define ETH_BASE	        0x4001E000UL  // 0x4001_E000 ~ 0x4001_EFFF

/* AHB addr 0x4100_0000~0x41FF_FFFF */
#define AHB_DMA0_BASE	    0x41000000UL  // 0x4100_0000 ~ 0x410F_FFFF
#define AHB_DMA1_BASE       0x41100000UL  // 0x4110_0000 ~ 0x411F_FFFF
#define AHB_SPI0_BASE       0x41800000UL  // 0x4180_0000 ~ 0x418F_FFFF
#define AHB_SPI1_BASE       0x41900000UL  // 0x4190_0000 ~ 0x419F_FFFF
#define AHB_SDIO0_BASE      0x41C00000UL  // 0x41C0_0000 ~ 0x41CF_FFFF
#define AHB_SDIO1_BASE      0x41D00000UL  // 0x41D0_0000 ~ 0x41DF_FFFF

/* AON addr 0x4300_0000~0x4302_FFFF */
#define AON_DMA_BASE	    0x43000000UL // 0x4300_0000 ~ 0x4300_3FFF
#define AON_VPROC_BASE	    0x43004000UL // 0x4300_4000 ~ 0x4300_7FFF
#define AON_APROC_BASE	    0x43008000UL // 0x4300_8000 ~ 0x4300_8FFF
#define AON_I2S0_BASE	    0x43010000UL // 0x4301_0000 ~ 0x4301_0FFF
#define AON_I2S1_BASE	    0x43011000UL // 0x4301_1000 ~ 0x4301_1FFF
#define AON_SPI0_BASE	    0x43012000UL // 0x4301_2000 ~ 0x4301_2FFF
#define AON_SPI1_BASE	    0x43013000UL // 0x4301_3000 ~ 0x4301_3FFF
#define AON_GPIO_BASE	    0x43014000UL // 0x4301_4000 ~ 0x4301_4FFF
#define AON_WDOG_BASE	    0x43015000UL // 0x4301_5000 ~ 0x4301_5FFF
#define AON_TIMER_BASE	    0x43016000UL // 0x4301_6000 ~ 0x4301_6FFF
#define AON_RTC_BASE	    0x43017000UL // 0x4301_7000 ~ 0x4301_7FFF
#define AON_CFG_BASE	    0x43018000UL // 0x4301_8000 ~ 0x4301_8FFF
#define AON_SRAM1_BASE      0x43020000UL // 0x4302_0000 ~ 0x4302_3FFF
#define AON_SRAM0_BASE      0x43024000UL // 0x4302_4000 ~ 0x4302_4FFF

/* DSP addr */
#define DSP_RAM0_BASE       0x44000000UL // 0x4400_0000 ~ 0x4403_FFFF
#define DSP_RAM1_BASE       0x44040000UL // 0x4404_0000 ~ 0x4407_FFFF
#define DSP_RCC_BASE        0x44080000UL // 0x4408_0000 ~ 0x4408_03FF
#define DSP_MAILBOX_BASE    0x44080400UL // 0x4408_0400 ~ 0x4408_07FF
#define DSP_SYSCTL_BASE     0x44080800UL // 0x4408_0800 ~ 0x4408_0BFF
#define DSP_H264_BASE       0x44080C00UL // 0x4408_0C00 ~ 0x4408_0FFF
#define DSP_EDAP_BASE       0x44084000UL // 0x4408_4000 ~ 0x4408_7FFF
#define DSP_AXI_DMA_BASE    0x44088000UL // 0x4408_8000 ~ 0x4408_9FFF
#define DSP_PIM_BASE        0x4408A000UL // 0x4408_A000 ~ 0x4408_BFFF

#define DSP_RAM_LEN		    0x40000UL 	// 256KB

/* PSRAM addr */
#define PSRAM_BASE	        0x80000000UL // 0x8000_0000 ~ 0x81FF_FFFF

#endif /* REG_H_ */
