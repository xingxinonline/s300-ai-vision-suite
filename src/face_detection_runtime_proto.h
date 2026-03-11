#ifndef FACE_DETECTION_RUNTIME_PROTO_H
#define FACE_DETECTION_RUNTIME_PROTO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Demo 私有运行时通知：DSP 不直接写 MM/LCD 寄存器，
 * 而是通过 mailbox 请求 CM4 触发对应硬件同步。
 */
#define FD_RT_MSG_TYPE_MM_SYNC_REQ      0x40000000u

#define FD_RT_SYNC_REQ_CORE_REG_UPDATE  0x00000001u
#define FD_RT_SYNC_REQ_SPI_REG_UPDATE   0x00000002u

#define FD_RT_MSG_TYPE_MASK             0xF0000000u
#define FD_RT_MSG_PAYLOAD_MASK          0x0FFFFFFFu

#define FD_RT_MAKE_MM_SYNC_REQ(req) \
    (FD_RT_MSG_TYPE_MM_SYNC_REQ | ((uint32_t)(req) & FD_RT_MSG_PAYLOAD_MASK))

static inline int fd_runtime_msg_is_mm_sync_req(uint32_t msg)
{
    return (msg & FD_RT_MSG_TYPE_MASK) == FD_RT_MSG_TYPE_MM_SYNC_REQ;
}

static inline uint32_t fd_runtime_msg_get_mm_sync_req(uint32_t msg)
{
    return msg & FD_RT_MSG_PAYLOAD_MASK;
}

#ifdef __cplusplus
}
#endif

#endif