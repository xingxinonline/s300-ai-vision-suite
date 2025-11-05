/*
 * custom_printf.c
 *
 *  Created on: 2024年11月29日
 *      Author: xinhao
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "uart.h"

#define DSP_DBG_UART UART3

void rt_kprintf(const char *fmt, ...);

/* RT-Thread version information */
#define RT_VERSION                      3L              /**< major version number */
#define RT_SUBVERSION                   1L              /**< minor version number */
#define RT_REVISION                     5L              /**< revise version number */

/* RT-Thread version */
#define RTTHREAD_VERSION                ((RT_VERSION * 10000) + \
                                         (RT_SUBVERSION * 100) + RT_REVISION)


/* use precision */
#define RT_USING_CONSOLE
#define RT_PRINTF_PRECISION
#define RT_PRINTF_LONGLONG
#define RT_PRINTF_SPECIAL
#define RT_CONSOLEBUF_SIZE          128
/* private function */
#define _ISDIGIT(c)  ((unsigned)((c) - '0') < 10)

#ifdef RT_PRINTF_LONGLONG
static __inline int divide(long long *n, int base)
{
    int res;
    /* optimized for processor which does not support divide instructions. */
    if (base == 10)
    {
        res = (int)(((unsigned long long) * n) % 10U);
        *n = (long long)(((unsigned long long) * n) / 10U);
    }
    else
    {
        res = (int)(((unsigned long long) * n) % 16U);
        *n = (long long)(((unsigned long long) * n) / 16U);
    }
    return res;
}
#else
static __inline int divide(long *n, int base)
{
    int res;
    /* optimized for processor which does not support divide instructions. */
    if (base == 10)
    {
        res = (int)(((unsigned long) * n) % 10U);
        *n = (long)(((unsigned long) * n) / 10U);
    }
    else
    {
        res = (int)(((unsigned long) * n) % 16U);
        *n = (long)(((unsigned long) * n) / 16U);
    }
    return res;
}
#endif

static __inline int skip_atoi(const char **s)
{
    register int i = 0;
    while (_ISDIGIT(**s))
        i = i * 10 + *((*s)++) - '0';
    return i;
}

#define ZEROPAD     (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed long */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* use 'ABCDEF' instead of 'abcdef' */

#ifdef RT_PRINTF_PRECISION
__attribute__((optnone, noinline))
static char *print_number(char *buf,
                          char *end,
#ifdef RT_PRINTF_LONGLONG
    long long  num,
#else
    long  num,
#endif
                          int   base,
                          int   s,
                          int   precision,
                          int   type)
#else
static char *print_number(char *buf,
                          char *end,
#ifdef RT_PRINTF_LONGLONG
    long long  num,
#else
    long  num,
#endif
                          int   base,
                          int   s,
                          int   type)
#endif
{
    char c, sign;
#ifdef RT_PRINTF_LONGLONG
    char tmp[32];
#else
    char tmp[16];
#endif
    int precision_bak = precision;
    const char *digits;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    register int i;
    register int size;
    size = s;
    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;
    c = (type & ZEROPAD) ? '0' : ' ';
    /* get sign */
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
        }
        else if (type & PLUS)
            sign = '+';
        else if (type & SPACE)
            sign = ' ';
    }
#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
#endif
    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
    {
        while (num != 0)
            tmp[i++] = digits[divide(&num, base)];
    }
#ifdef RT_PRINTF_PRECISION
    if (i > precision)
        precision = i;
    size -= precision;
#else
    size -= i;
#endif
    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
            size--;
        while (size-- > 0)
        {
            if (buf < end)
                *buf = ' ';
            ++ buf;
        }
    }
    if (sign)
    {
        if (buf < end)
        {
            *buf = sign;
        }
        -- size;
        ++ buf;
    }
#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
        }
        else if (base == 16)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
            if (buf < end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++ buf;
        }
    }
#endif
    /* no align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            if (buf < end)
                *buf = c;
            ++ buf;
        }
    }
#ifdef RT_PRINTF_PRECISION
    while (i < precision--)
    {
        if (buf < end)
            *buf = '0';
        ++ buf;
    }
#endif
    /* put number in the temporary buffer */
    while (i-- > 0 && (precision_bak != 0))
    {
        if (buf < end)
            *buf = tmp[i];
        ++ buf;
    }
    while (size-- > 0)
    {
        if (buf < end)
            *buf = ' ';
        ++ buf;
    }
    return buf;
}

__attribute__((optnone, noinline))
int32_t rt_vsnprintf(char       *buf,
                     size_t   size,
                     const char *fmt,
                     va_list     args)
{
#ifdef RT_PRINTF_LONGLONG
    unsigned long long num;
#else
    uint32_t num;
#endif
    int i, len;
    char *str, *end, c;
    const char *s;
    uint8_t base;            /* the base of number */
    uint8_t flags;           /* flags to print number */
    uint8_t qualifier;       /* 'h', 'l', or 'L' for integer fields */
    int32_t field_width;     /* width of output field */
#ifdef RT_PRINTF_PRECISION
    int precision;      /* min. # of digits for integers and max for a string */
#endif
    str = buf;
    end = buf + size;
    /* Make sure end is always >= buf */
    if (end < buf)
    {
        end  = ((char *) - 1);
        size = end - buf;
    }
    for (; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            if (str < end)
                *str = *fmt;
            ++ str;
            continue;
        }
        /* process flags */
        flags = 0;
        while (1)
        {
            /* skips the first '%' also */
            ++ fmt;
            if (*fmt == '-') flags |= LEFT;
            else if (*fmt == '+') flags |= PLUS;
            else if (*fmt == ' ') flags |= SPACE;
            else if (*fmt == '#') flags |= SPECIAL;
            else if (*fmt == '0') flags |= ZEROPAD;
            else break;
        }
        /* get field width */
        field_width = -1;
        if (_ISDIGIT(*fmt)) field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++ fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }
#ifdef RT_PRINTF_PRECISION
        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++ fmt;
            if (_ISDIGIT(*fmt)) precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++ fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0) precision = 0;
        }
#endif
        /* get the conversion qualifier */
        qualifier = 0;
#ifdef RT_PRINTF_LONGLONG
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
#else
        if (*fmt == 'h' || *fmt == 'l')
#endif
        {
            qualifier = *fmt;
            ++ fmt;
#ifdef RT_PRINTF_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++ fmt;
            }
#endif
        }
        /* the default base */
        base = 10;
        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
            }
            /* get character */
            c = (uint8_t)va_arg(args, int);
            if (str < end) *str = c;
            ++ str;
            /* put width */
            while (--field_width > 0)
            {
                if (str < end) *str = ' ';
                ++ str;
            }
            continue;
        case 's':
            s = va_arg(args, char *);
            if (!s) s = "(NULL)";
            for (len = 0; (len != field_width) && (s[len] != '\0'); len++);
#ifdef RT_PRINTF_PRECISION
            if (precision > 0 && len > precision) len = precision;
#endif
            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
            }
            for (i = 0; i < len; ++i)
            {
                if (str < end) *str = *s;
                ++ str;
                ++ s;
            }
            while (len < field_width--)
            {
                if (str < end) *str = ' ';
                ++ str;
            }
            continue;
        case 'p':
            if (field_width == -1)
            {
                field_width = sizeof(void *) << 1;
                flags |= ZEROPAD;
            }
#ifdef RT_PRINTF_PRECISION
            str = print_number(str, end,
                               (long)va_arg(args, void *),
                               16, field_width, precision, flags);
#else
            str = print_number(str, end,
                               (long)va_arg(args, void *),
                               16, field_width, flags);
#endif
            continue;
        case '%':
            if (str < end) *str = '%';
            ++ str;
            continue;
        /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;
        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;
        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;
        default:
            if (str < end) *str = '%';
            ++ str;
            if (*fmt)
            {
                if (str < end) *str = *fmt;
                ++ str;
            }
            else
            {
                -- fmt;
            }
            continue;
        }
#ifdef RT_PRINTF_LONGLONG
        if (qualifier == 'L') num = va_arg(args, long long);
        else if (qualifier == 'l')
#else
        if (qualifier == 'l')
#endif
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
        else if (qualifier == 'h')
        {
            num = (uint16_t)va_arg(args, int32_t);
            if (flags & SIGN) num = (int16_t)num;
        }
        else
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
#ifdef RT_PRINTF_PRECISION
        str = print_number(str, end, num, base, field_width, precision, flags);
#else
        str = print_number(str, end, num, base, field_width, flags);
#endif
    }
    if (size > 0)
    {
        if (str < end) *str = '\0';
        else
        {
            end[-1] = '\0';
        }
    }
    /* the trailing null byte doesn't count towards the total
    * ++str;
    */
    return str - buf;
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param size the size of buffer
 * @param fmt the format
 */
__attribute__((optnone, noinline))
int32_t rt_snprintf(char *buf, size_t size, const char *fmt, ...)
{
    int32_t n;
    va_list args;
    va_start(args, fmt);
    n = rt_vsnprintf(buf, size, fmt, args);
    va_end(args);
    return n;
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param arg_ptr the arg_ptr
 * @param format the format
 */
__attribute__((optnone, noinline))
int32_t rt_vsprintf(char *buf, const char *format, va_list arg_ptr)
{
    return rt_vsnprintf(buf, (size_t) - 1, format, arg_ptr);
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param format the format
 */
__attribute__((optnone, noinline))
int32_t rt_sprintf(char *buf, const char *format, ...)
{
    int32_t n;
    va_list arg_ptr;
    va_start(arg_ptr, format);
    n = rt_vsprintf(buf, format, arg_ptr);
    va_end(arg_ptr);
    return n;
}

#ifdef RT_USING_CONSOLE

void rt_hw_console_output(const char *str)
{
	size_t i = 0, size = 0;
	char a = '\r';
	size = strlen(str);
	for (i = 0; i < size; i++)
	{
		if (*(str + i) == '\n')
		{
			while ((UART_LSR(DSP_DBG_UART) & UART_LSR_THRE) == 0);
			// usart_data_transmit(UART1, (uint32_t )a);
			UART_THR(DSP_DBG_UART) = (uint8_t)a;
		}
		while ((UART_LSR(DSP_DBG_UART) & UART_LSR_THRE) == 0);
		// usart_data_transmit(UART0, (uint32_t)*(str + i));
		UART_THR(DSP_DBG_UART) = (uint8_t) * (str + i);
	}
}

/**
 * This function will print a formatted string on system console
 *
 * @param fmt the format
 */
void rt_kprintf(const char *fmt, ...)
{
    va_list args;
    size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];
    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;
     rt_hw_console_output(rt_log_buf);
    va_end(args);
}
#endif

// 实现支持 float 类型的 powf 函数
static float powf_manual(float base, int exp) {
    float result = 1.0f;

    // 处理负指数
    int is_negative = (exp < 0);
    if (is_negative) {
        exp = -exp; // 转为正指数
    }

    // 快速幂算法（适用于整数指数）
    while (exp > 0) {
        if (exp % 2 == 1) { // 如果指数是奇数
            result *= base;
        }
        base *= base; // 基数平方
        exp /= 2;     // 指数减半
    }

    // 如果原指数是负数，取倒数
    if (is_negative) {
        result = 1.0f / result;
    }

    return result;
}

// 将浮点数转换为字符串
void float_to_string(float value, char *buffer, size_t size, int precision) {
    int int_part = (int)value;                     // 整数部分
    float frac = value - int_part;                // 小数部分
    if (frac < 0) frac = -frac;                   // 确保小数部分为正
    int frac_part = (int)(frac * powf_manual(10, precision)); // 获取小数部分

    // 使用 snprintf 避免 buffer 溢出
    snprintf(buffer, size, "%d.%0*d", int_part, precision, frac_part);
}

// 将浮点数转换为字符串
char *float_to_string_simple(float value) {
	static char buffer[32];
    int int_part = (int)value;                     // 整数部分
    float frac = value - int_part;                // 小数部分
    if (frac < 0) frac = -frac;                   // 确保小数部分为正
    int frac_part = (int)(frac * powf_manual(10, 6)); // 获取小数部分

    // 使用 snprintf 避免 buffer 溢出
    snprintf(buffer, 32, "%d.%0*d", int_part, 6, frac_part);

    return buffer;
}

