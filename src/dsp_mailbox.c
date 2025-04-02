#include "dsp_mailbox.h"

// Function to write data to the mailbox
void mailbox_write_data(uint32_t data) {
    // Wait until there is space in the FIFO
    while (STATUS_REG & STATUS_FULL_FLAG) {
        // Busy wait
    }
    WRDATA_REG = data;
}

// Function to read data from the mailbox
uint32_t mailbox_read_data(void) {
    // Wait until there is data available in the FIFO
    while (STATUS_REG & STATUS_EMPTY_FLAG) {
        // Busy wait
    }
    return RDDATA_REG;
}

// Function to check if the mailbox FIFO is full
bool mailbox_is_full(void) {
    return (STATUS_REG & STATUS_FULL_FLAG) != 0;
}

// Function to check if the mailbox FIFO is empty
bool mailbox_is_empty(void) {
    return (STATUS_REG & STATUS_EMPTY_FLAG) != 0;
}

// Function to enable specified interrupts
void mailbox_enable_interrupts(uint32_t interrupt_flags) {
    IE_REG |= interrupt_flags;
}

// Function to disable specified interrupts
void mailbox_disable_interrupts(uint32_t interrupt_flags) {
    IE_REG &= ~interrupt_flags;
}

// Function to clear specified interrupts
void mailbox_clear_interrupts(uint32_t interrupt_flags) {
    IIS_REG |= interrupt_flags;
}

// Function to get the current status of the mailbox
uint32_t mailbox_get_current_status(void) {
    return STATUS_REG;
}

// Function to get the current error status of the mailbox
uint32_t mailbox_get_current_error(void) {
    uint32_t error_status = ERROR_REG;
    // Reading the ERROR_REG clears all error flags
    return error_status;
}

// Function to set the send interrupt threshold
void mailbox_set_send_threshold(uint8_t threshold) {
    SIT_REG = (SIT_REG & 0xFFFFFF00) | (threshold & 0xFF);
}

// Function to set the receive interrupt threshold
void mailbox_set_receive_threshold(uint8_t threshold) {
    RIT_REG = (RIT_REG & 0xFFFFFF00) | (threshold & 0xFF);
}

// Function to clear the receive FIFO
void mailbox_clear_receive_fifo(void) {
    CTRL_REG = CTRL_CRF_FLAG;
}

// Function to clear the send FIFO
void mailbox_clear_send_fifo(void) {
    CTRL_REG = CTRL_CSF_FLAG;
}

// Interrupt Service Routine (ISR) to handle mailbox interrupts
void mailbox_isr_handler(void) {
    uint32_t interrupt_status = IIS_REG;

    // Handle send threshold interrupt
    if (interrupt_status & IIS_SIT_FLAG) {
        // Custom code to handle send threshold interrupt
        mailbox_clear_interrupts(IIS_SIT_FLAG);
    }

    // Handle receive threshold interrupt
    if (interrupt_status & IIS_RIT_FLAG) {
        // Custom code to handle receive threshold interrupt
        mailbox_clear_interrupts(IIS_RIT_FLAG);
    }

    // Handle error interrupt
    if (interrupt_status & IIS_ERR_FLAG) {
        // Custom code to handle error interrupt
        mailbox_clear_interrupts(IIS_ERR_FLAG);
    }
}
