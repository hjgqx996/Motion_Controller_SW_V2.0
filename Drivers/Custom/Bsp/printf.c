//*********************************************************************
//
//           ��Ȩ���� (C), 2008-2028, ���ﻥ���Ļ��������޹�˾
//             -----------------------------------------------
//
//  �ļ�����:   liu-PC
//  ��������:
//  ��������:
//  �޸���ʷ:
//  (1)   �޸�����:
//  (2)   �޸�����:Liu-PC
//  (3)   �޸�����:
//  [4]   ΢��:lpc17707020887    LiuPC
//*********************************************************************
#include "printf.h"





DEVICE_DEFINE(DEBUG_0,DEVICE_ONE)

/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_OPEN(DEBUG_0)
{


	return DEV_OK;
}

/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_CLOSE(DEBUG_0)
{


	return DEV_OK;
}



/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_READ(DEBUG_0)
{


	return DEV_OK;
}


/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_WRITE(DEBUG_0)
{


	return DEV_OK;
}
/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_LSEEK(DEBUG_0)
{


	return DEV_OK;
}


/**********************************************************************
** ��������         :
** ������           :LiuPC
** ��������         :2019��5��26��23:44:35
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
DEVICE_FUNC_DEFINE_IOCTL(DEBUG_0)
{

#if 1
	switch((Debug_Ctl_Cmd_Typedef)cmd)
	{
			case CMD_CODE_DAT_2_BUF:    	 //������þ�����DEV_Ioctl(DEVICE_ONE,CMD_CODE_DAT_2_BUF,(char*)destination_buf_addr,buf_lengt,"hello world %d !!!",temp);
			{
                //destination_buf_addr ָ����TRACE()�����ĵ�һ��������
                //���ָ��ָ��debug��Ϣ��,
                //debug��Ϣ�����ݵ�����Ϣ���Ѿ���ɱ��룩��һ����Ϣ��
                char* destination_buf_addr = 0;
                //debug��Ϣ����Ԥ����С
                uint8_t buf_lengt = 0;

                //��ָ����Trace�����������������׵�ַ��
                //�������β���һ���ַ���
                char* source_dat_addr =NULL;


                destination_buf_addr = va_arg(*args_temp,char*);
                buf_lengt = va_arg(*args_temp,uint8_t);
                source_dat_addr =  va_arg(*args_temp,char*);

                vsprintf(destination_buf_addr,source_dat_addr,*args_temp);



			};break;
			case CMD_SEND_DAT_TO_PORT:  //������þ����� DEV_Ioctl(DEVICE_ONE,CMD_SEND_DAT_TO_PORT,(uint8_t *)buf_ptr,uint8_t buf_length);
			{
                uint8_t* buf_ptr = NULL;

                //step1����ȡ��ָ�룬ʵʱ��ӡ
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
static int outc(int c)
{
    __out_putchar(c);
    return 0;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
--n:����
                                                --base:����
                                                --lead:

												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
static void float_to_str(char *str,double num)
{
    int high;            //float_��������
    double low;          //float_С������
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

    while(num > eps)    //��������
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
                case 'd':       //ʮ�����з�������
                {
                        out_num(va_arg(ap, int), 10, lead, maxwidth);
                        break;
                }
                case 'o':      //�˽����з�������
                {
                        out_num(va_arg(ap, unsigned int), 8, lead, maxwidth);
                        break;
                }
                case 'u':     //ʮ�����޷�������
                {
                        out_num(va_arg(ap, unsigned int), 10, lead, maxwidth);
                        break;
                }
                case 'x':     //ʮ�������޷�������
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
int usart_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    my_vprintf(fmt, ap);
    va_end(ap);
    return 0;
}


