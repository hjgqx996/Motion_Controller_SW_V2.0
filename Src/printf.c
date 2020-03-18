
#include <stdint.h>
#include <math.h>
#include <stdarg.h>
#include "printf.h"
#include "usart.h"

#if 0
typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap, v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_arg(ap, t)    ( *(t *)( ap = ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )
#endif

unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
                         '8','9','a','b','c','d','e','f'};

static int outc(int c)
{
    __out_putchar(c);
    return 0;
}

static int outs (const char *s)
{
    while (*s != '\0')
        __out_putchar(*s++);
    return 0;
}

static int out_num(long n, int base, char lead, int maxwidth)
{
    unsigned long m = 0;
    char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
    int count = 0;
    int i = 0;

    *--s = '\0';

    if (n < 0)
    {
        m = -n;
    }
    else
    {
        m = n;
    }

    do
    {
        *--s = hex_tab[m%base];
        count++;
    }while ((m /= base) != 0);

    if( maxwidth && count < maxwidth)
    {
        for (i=maxwidth - count; i; i--)
        {
            *--s = lead;
        }
    }

    if (n < 0)
        *--s = '-';

    return outs(s);
}

const double eps = 1e-11;

static void float_to_str(char *str,double num)
{
    int high;           //float_整数部分
    double low;          //float_小数部分
    char *start = str;
    int n = 0;
    char ch[20];
    int i;
    high = (int)num;
    low = num - high;

    while(high > 0)
    {
        ch[n++] = '0' + high%10;
        high = high/10;
    }

    for(i = n - 1; i >= 0; i--)
    {
        *str++ = ch[i];
    }

    num -= (int)num;
    double tp = 0.1;
    *str++ = '.';

    while(num > eps)    //精度限制
    {
        num -= tp * (int)(low * 10);
        tp /= 10;
        *str++ = '0' + (int)(low*10);
        low = low*10.0 - (int)(low*10);
    }
    *str='\0';
    str=start;
}

/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap)
{
    char lead=' ';
    int  maxwidth = 0;
    char str[20];
    double get_double;

     for (; *fmt != '\0'; fmt++)
     {
        if (*fmt != '%')
        {
            outc(*fmt);
            continue;
        }

        //format : %08d, %8d,%d,%u,%x,%f,%c,%s
        fmt++;
        if (*fmt == '0')
        {
            lead = '0';
            fmt++;
        }

        while (*fmt >= '0' && *fmt <= '9')
        {
            maxwidth *= 10;
            maxwidth += (*fmt - '0');
            fmt++;
        }

        switch (*fmt)
        {
            case 'd':
            {
                out_num(va_arg(ap, int), 10, lead, maxwidth);
                break;
            }
            case 'o':
            {
                out_num(va_arg(ap, unsigned int), 8, lead, maxwidth);
                break;
            }
            case 'u':
            {
                out_num(va_arg(ap, unsigned int), 10, lead, maxwidth);
                break;
            }
            case 'x':
            {
                out_num(va_arg(ap, unsigned int), 16, lead, maxwidth);
                break;
            }
            case 'c':
            {
                outc(va_arg(ap, int));
                break;
            }
            case 's':
            {
                outs(va_arg(ap, char *));
                break;
            }
            case 'f':
            {
                get_double = va_arg(ap, double);
                float_to_str(str, get_double);
                outs(str);
                break;
            }

            default:
                outc(*fmt);
                break;
        }
    }
    return 0;
}

int usart_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    my_vprintf(fmt, ap);
    va_end(ap);
    return 0;
}


