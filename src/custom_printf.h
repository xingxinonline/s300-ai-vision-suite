/*
 * custom_printf.h
 *
 *  Created on: 2024年11月29日
 *      Author: xinhao
 */

#ifndef CUSTOM_PRINTF_H_
#define CUSTOM_PRINTF_H_
void rt_hw_console_output(const char *str);
void rt_kputs(const char *str);
void rt_kprintf(const char *fmt, ...);
void float_to_string(float value, char *buffer, size_t size, int precision);
char *float_to_string_simple(float value);
#endif /* CUSTOM_PRINTF_H_ */
