#ifndef __printf_H
#define __printf_H


//1、头文件
/********************************************************************************************************************************************************************/
#include "stm32f1xx_hal.h"
#include "coupling_between_app_and_bsp.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include "usart.h"

//2、宏定义
/********************************************************************************************************************************************************************/
#define  __out_putchar  USART1_Putchar
#define  MAX_NUMBER_BYTES  64

 

      
#if 0
    typedef char *  va_list;
    #define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

    #define va_start(ap, v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
    //#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
    #define va_arg(ap, t)    ( *(t *)( ap = ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
    #define va_end(ap)      ( ap = (va_list)0 )
#endif




//3、类型定义
/********************************************************************************************************************************************************************/



//4、变量声明
/********************************************************************************************************************************************************************/




//5、函数声明
/********************************************************************************************************************************************************************/
static void float_to_str(char *str,double num);
static int out_num(long n, int base, char lead, int maxwidth);
int usart_printf(const char *fmt, ...);
static int outc(int c);
static int outs (const char *s);


#endif





