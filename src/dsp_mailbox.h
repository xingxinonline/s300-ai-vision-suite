#ifndef __DSP_MAILBOX_H__
#define __DSP_MAILBOX_H__

#include <stdint.h>
#include <stdbool.h>

#include "reg.h"
#include "dsp_protocol.h"

// Base address of the Mailbox peripheral (example base address, replace as needed)
#define MAILBOX_BASE_ADDR   DSP_MAILBOX_BASE

// Register Offsets
enum MAILBOX_REG_OFFSETS {
    WRDATA_OFFSET = 0x00,
    RDDATA_OFFSET = 0x08,
    STATUS_OFFSET = 0x10,
    ERROR_OFFSET  = 0x14,
    SIT_OFFSET    = 0x18,
    RIT_OFFSET    = 0x1C,
    IIS_OFFSET    = 0x20,
    IE_OFFSET     = 0x24,
    IPA_OFFSET    = 0x28,
    CTRL_OFFSET   = 0x2C
};

// Register Addresses
#define MAILBOX_REG_ADDR(offset)  (MAILBOX_BASE_ADDR + (offset))

#define WRDATA_REG   (*(volatile uint32_t *)(MAILBOX_REG_ADDR(WRDATA_OFFSET)))
#define RDDATA_REG   (*(volatile uint32_t *)(MAILBOX_REG_ADDR(RDDATA_OFFSET)))
#define STATUS_REG   (*(volatile uint32_t *)(MAILBOX_REG_ADDR(STATUS_OFFSET)))
#define ERROR_REG    (*(volatile uint32_t *)(MAILBOX_REG_ADDR(ERROR_OFFSET)))
#define SIT_REG      (*(volatile uint32_t *)(MAILBOX_REG_ADDR(SIT_OFFSET)))
#define RIT_REG      (*(volatile uint32_t *)(MAILBOX_REG_ADDR(RIT_OFFSET)))
#define IIS_REG      (*(volatile uint32_t *)(MAILBOX_REG_ADDR(IIS_OFFSET)))
#define IE_REG       (*(volatile uint32_t *)(MAILBOX_REG_ADDR(IE_OFFSET)))
#define IPA_REG      (*(volatile uint32_t *)(MAILBOX_REG_ADDR(IPA_OFFSET)))
#define CTRL_REG     (*(volatile uint32_t *)(MAILBOX_REG_ADDR(CTRL_OFFSET)))

// Status Flags
#define STATUS_RTA_FLAG   (1 << 3)
#define STATUS_STA_FLAG   (1 << 2)
#define STATUS_FULL_FLAG  (1 << 1)
#define STATUS_EMPTY_FLAG (1 << 0)

// Interrupt Enable Flags
#define IE_ERR_FLAG   (1 << 2)
#define IE_RIT_FLAG   (1 << 1)
#define IE_SIT_FLAG   (1 << 0)

// Interrupt Status Flags
#define IIS_ERR_FLAG  (1 << 2)
#define IIS_RIT_FLAG  (1 << 1)
#define IIS_SIT_FLAG  (1 << 0)

// Control Flags
#define CTRL_CRF_FLAG (1 << 1) // Clear Receive FIFO
#define CTRL_CSF_FLAG (1 << 0) // Clear Send FIFO

// Function Prototypes
void mailbox_write_data(uint32_t data);
uint32_t mailbox_read_data(void);
uint32_t mailbox_read(void);
uint32_t mailbox_get_status(void);
uint32_t mailbox_get_error(void);
void mailbox_clear_receive_fifo(void);
void mailbox_clear_send_fifo(void);
void mailbox_enable_interrupt(uint32_t interrupt_flags);
void mailbox_disable_interrupt(uint32_t interrupt_flags);
void mailbox_clear_interrupt(uint32_t interrupt_flags);
bool mailbox_is_empty(void) ;

// Protocol functions
void dsp_mailbox_send_evt(uint32_t evt_id, uint32_t arg0, uint32_t arg1, uint32_t arg2);
void dsp_mailbox_process_command(void);

#endif // __DSP_MAILBOX_H__
