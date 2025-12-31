#include "dsp_mailbox.h"
#include "custom_printf.h"
// #include <math.h>

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

// Simple square root approximation (Newton's method)
static float dsp_sqrtf(float number) {
    if (number <= 0.0f) return 0.0f;
    float x = number;
    float y = 1.0f;
    float e = 0.00001f; // Precision
    while (x - y > e) {
        x = (x + y) / 2.0f;
        y = number / x;
    }
    return x;
}

// =============================================================================
// Protocol Implementation
// =============================================================================

static dsp_msg_t g_dsp_evt_msg;
// Static buffer for feature vector (128 bytes)
static int8_t g_feature_vector[128];

// External function for face recognition
// Note: We might need to modify fr_run to output int8 directly or we convert float
extern int fr_run(int8_t* result, uint8_t *rgb_data);

void dsp_mailbox_send_evt(uint32_t evt_id, uint32_t arg0, uint32_t arg1, uint32_t arg2) {
    g_dsp_evt_msg.type = evt_id;
    g_dsp_evt_msg.args[0] = arg0;
    g_dsp_evt_msg.args[1] = arg1;
    g_dsp_evt_msg.args[2] = arg2;
    
    // Send the address of the message structure
    // Ensure data is written to memory before sending address (memory barrier might be needed depending on architecture)
    mailbox_write_data((uint32_t)&g_dsp_evt_msg);
}

void dsp_mailbox_process_command(void) {
    if (mailbox_is_empty()) {
        return;
    }

    uint32_t msg_addr = mailbox_read_data();
    // Assuming the address is in a shared memory region accessible by DSP
    volatile dsp_msg_t *msg = (volatile dsp_msg_t *)msg_addr;

    if (msg == NULL) {
        return;
    }

    switch (msg->type) {
        case CMD_PING:
            DSP_LOG("Received CMD_PING\n");
            dsp_mailbox_send_evt(EVT_PONG, 0, 0, 0);
            break;

        case CMD_SET_MODEL:
            // msg->args[0] = Addr, msg->args[1] = Size
            // TODO: Store model address and size for future use
            DSP_LOG("Received CMD_SET_MODEL\n");
            dsp_mailbox_send_evt(EVT_ACK, CMD_SET_MODEL, 0, 0);
            break;

        case CMD_EXTRACT_FEATURE:
        {
            uint32_t image_addr = msg->args[0];
            DSP_LOG("Received CMD_EXTRACT_FEATURE, Image Addr: 0x%x\n", image_addr);
            
            // Acknowledge command reception
            dsp_mailbox_send_evt(EVT_ACK, CMD_EXTRACT_FEATURE, 0, 0);

            // Run Face Recognition
            // fr_run writes to g_feature_vector (which are already normalized and quantized int8)
             DSP_LOG("CMD_EXTRACT_FEATURE fr_run start\n");
            // uint32_t start_cycles = get_cycles_start();
            fr_run(g_feature_vector, (uint8_t*)image_addr); 
            // uint32_t end_cycles = get_cycles_end();
            // DSP_LOG("Face Recognition cycles: %u\n", end_cycles - start_cycles);
             DSP_LOG("CMD_EXTRACT_FEATURE fr_run finish\n");

            dsp_mailbox_send_evt(EVT_FEATURE_READY, (uint32_t)g_feature_vector, 0, 0);
            // DSP_LOG("Received CMD_EXTRACT_FEATURE, Image Addr: 0x%x\n", image_addr);
            break;
        }

        default:
            DSP_LOG("Received Unknown Command: %d\n", msg->type);
            dsp_mailbox_send_evt(EVT_NACK, msg->type, 0, 0);
            break;
    }
}
