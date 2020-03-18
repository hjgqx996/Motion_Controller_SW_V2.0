//*********************************************************************
//
//           版权所有 (C), 2008-2028, 格物互动文化传播有限公司
//             -----------------------------------------------
//
//  文件作者:   liu-PC
//  生成日期:
//  功能描述:
//  修改历史:
//  (1)   修改日期:
//  (2)   修改作者:Liu-PC
//  (3)   修改内容:
//  [4]   微信:lpc17707020887    LiuPC
//*********************************************************************
#include "printf.h"





DEVICE_DEFINE(DEBUG_0,DEVICE_ONE)

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_OPEN(DEBUG_0)
{


	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_CLOSE(DEBUG_0)
{


	return DEV_OK;
}



/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_READ(DEBUG_0)
{


	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_WRITE(DEBUG_0)
{


	return DEV_OK;
}
/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_LSEEK(DEBUG_0)
{


	return DEV_OK;
}


/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_IOCTL(DEBUG_0)
{

#if 1
	switch((Debug_Ctl_Cmd_Typedef)cmd)
	{
			case CMD_CODE_DAT_2_BUF:    	 //具体调用举例：DEV_Ioctl(DEVICE_ONE,CMD_CODE_DAT_2_BUF,(char*)destination_buf_addr,buf_lengt,"hello world %d !!!",temp);
			{
                //destination_buf_addr 指针是TRACE()函数的第一个参数，
                //这个指针指向“debug消息”,
                //debug消息：传递调试信息（已经完成编码）的一条消息。
                char* destination_buf_addr = 0;
                //debug消息的总预留大小
                uint8_t buf_lengt = 0;

                //该指针是Trace函数第三个参数的首地址，
                //第三个形参是一串字符串
                char* source_dat_addr =NULL;


                destination_buf_addr = va_arg(*args_temp,char*);
                buf_lengt = va_arg(*args_temp,uint8_t);
                source_dat_addr =  va_arg(*args_temp,char*);

                vsprintf(destination_buf_addr,source_dat_addr,*args_temp);



			};break;
			case CMD_SEND_DAT_TO_PORT:  //具体调用举例： DEV_Ioctl(DEVICE_ONE,CMD_SEND_DAT_TO_PORT,(uint8_t *)buf_ptr,uint8_t buf_length);
			{
                uint8_t* buf_ptr = NULL;

                //step1、获取首指针，实时打印
                buf_ptr = va_arg(*args_temp,uint8_t*);
                while(*buf_ptr != '\0')
                {
                    outc(*buf_ptr++);
                }


				//DISPLAY_Full_Image();
			};break;
			default:
			{

			};break;
	}

#endif
	//va_end(args);
	return DEV_OK;

}











unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
                         '8','9','a','b','c','d','e','f'};
/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
static int outc(int c)
{
    __out_putchar(c);
    return 0;
}


/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
static int outs (const char *s)
{
    while (*s != '\0')
    {
            __out_putchar(*s++);
    }
    return 0;
}









/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
--n:变量
                                                --base:进制
                                                --lead:

												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
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
    }
    while ((m /= base) != 0);

    if( maxwidth && count < maxwidth)
    {
            for (i=maxwidth - count; i; i--)
            {
                *--s = lead;
            }
    }

    if (n < 0)
    {
            *--s = '-';
    }
    return outs(s);
}



const double eps = 1e-11;


/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
static void float_to_str(char *str,double num)
{
    int high;            //float_整数部分
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


/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
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
                case 'd':       //十进制有符号整数
                {
                        out_num(va_arg(ap, int), 10, lead, maxwidth);
                        break;
                }
                case 'o':      //八进制有符号整形
                {
                        out_num(va_arg(ap, unsigned int), 8, lead, maxwidth);
                        break;
                }
                case 'u':     //十进制无符号整数
                {
                        out_num(va_arg(ap, unsigned int), 10, lead, maxwidth);
                        break;
                }
                case 'x':     //十六进制无符号整数
                {
                        out_num(va_arg(ap, unsigned int), 16, lead, maxwidth);
                        break;
                }
                case 'c':    //
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


/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
int usart_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    my_vprintf(fmt, ap);
    va_end(ap);
    return 0;
}


