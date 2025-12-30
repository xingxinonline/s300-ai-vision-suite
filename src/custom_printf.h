/*
 * custom_printf.h
 *
 *  Created on: 2024年11月29日
 *      Author: xinhao
 */

#ifndef CUSTOM_PRINTF_H_
#define CUSTOM_PRINTF_H_

#include <stdio.h>

void rt_hw_console_output(const char *str);
void rt_kputs(const char *str);
void rt_kprintf(const char *fmt, ...);
void float_to_string(float value, char *buffer, size_t size, int precision);
char *float_to_string_simple(float value);

// ==================== 输出方式选择 ====================
// 设置 DSP_LOG_USE_RT_HW_CONSOLE 为 1 使用 rt_hw_console_output
// 设置 DSP_LOG_USE_RT_HW_CONSOLE 为 0 使用 printf (默认)
#define DSP_LOG_USE_RT_HW_CONSOLE 1

// 统一的DSP调试输出：根据配置选择输出方式
#ifndef DSP_LOG
#define DSP_LOG(fmt, ...) do { \
        char _dsp_log_buf[192]; \
        int _len = snprintf(_dsp_log_buf, sizeof(_dsp_log_buf), "[DSP] " fmt, ##__VA_ARGS__); \
        if (_len < 0) { \
            /* snprintf 出错，仍尝试输出固定标记 */ \
            if (DSP_LOG_USE_RT_HW_CONSOLE) { \
                rt_hw_console_output("[DSP_LOG snprintf error]\n"); \
            } else { \
                printf("[DSP_LOG snprintf error]\n"); \
            } \
        } else { \
            /* 若内容被截断，添加省略标记 */ \
            if (_len >= (int)sizeof(_dsp_log_buf)) { \
                _dsp_log_buf[sizeof(_dsp_log_buf)-5] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-4] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-3] = '.'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-2] = '\n'; \
                _dsp_log_buf[sizeof(_dsp_log_buf)-1] = '\0'; \
            } \
            if (DSP_LOG_USE_RT_HW_CONSOLE) { \
                rt_hw_console_output(_dsp_log_buf); \
            } else { \
                printf(_dsp_log_buf); \
            } \
        } \
    } while(0)
#endif

#endif /* CUSTOM_PRINTF_H_ */
