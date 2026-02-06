#ifndef __DSP_MAILBOX_H__
#define __DSP_MAILBOX_H__

#include <stdint.h>
#include <stdbool.h>

#include "reg.h"
#include "detection_protocol.h"

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
bool mailbox_write_data_nb(uint32_t data);  // Non-blocking version
uint32_t mailbox_get_drop_count(void);      // Get dropped message count
uint32_t mailbox_read_data(void);
uint32_t mailbox_read(void);
uint32_t mailbox_get_status(void);
uint32_t mailbox_get_error(void);
void mailbox_clear_receive_fifo(void);
void mailbox_clear_send_fifo(void);
void mailbox_enable_interrupt(uint32_t interrupt_flags);
void mailbox_disable_interrupt(uint32_t interrupt_flags);
void mailbox_clear_interrupt(uint32_t interrupt_flags);
bool mailbox_is_empty(void);
bool mailbox_is_full(void);

/*============================================================================
 * 多目标检测消息发送接口
 *============================================================================*/

/**
 * @brief 发送多目标检测结果消息
 *
 * Payload 发送 DSP 本地地址（即相对于 PTCM 起始的偏移），
 * M4 收到后需要加上 DSP_PTCM_M4_BASE_OFFSET (0x44800000) 才能访问。
 *
 * @param result 检测结果结构体指针（DSP本地地址）
 * @return 发送的消息值（0 表示发送失败/被丢弃）
 */
static inline uint32_t mailbox_send_multi_detection(const DetectionResult_t *result) {
    // Payload = DSP 本地地址（M4 收到后自己加 0x44800000 偏移）
    uint32_t dsp_local_addr = (uint32_t)(uintptr_t)result;
    uint32_t msg;

    if (result->count > 0) {
        // 发送 DSP 本地地址作为 payload
        msg = MAILBOX_MSG_TYPE_MULTI | (dsp_local_addr & MAILBOX_MSG_PAYLOAD_MASK);
    } else {
        msg = MAILBOX_MSG_TYPE_NO_DETECT;
    }

    // 使用非阻塞发送，避免 M4 处理慢导致 DSP 阻塞
    if (!mailbox_write_data_nb(msg)) {
        return 0;  // 发送失败，FIFO 满
    }
    return msg;
}

/**
 * @brief 发送无检测结果消息（非阻塞）
 * @return true 发送成功，false 发送失败（FIFO满）
 */
static inline bool mailbox_send_no_detection(void) {
    return mailbox_write_data_nb(MAILBOX_MSG_TYPE_NO_DETECT);
}

#endif // __DSP_MAILBOX_H__
