//*********************************************************************
//
//           版权所有 (C), 2008-2028, 罗卜干实验室
//             -----------------------------------------------
//
//  文件作者:
//  生成日期:
//  功能描述:
//  修改历史:
//  (1) 修改日期:2019年3月1日
//      修改作者:Liu-PC
//      修改内容:
//
//*********************************************************************

#include "algorithm.h"
#include "Global.h"






/**********************************************************************
** 函数名称         :CHANGE_Coordinate_2_RS485_ID
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :根据输入电机驱动器在结构上位置的x坐标和y坐标，查表得出从设备对应的RS485_ID号
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
uint8_t CHANGE_Coordinate_2_RS485_ID(uint8_t x,uint8_t y)
{
    uint8_t i=0,j=0;

    for(i=0; i<TOTAL_NUM_OF_ROW ; i++)
    {
            for(j=0; j<TOTAL_NUM_OF_COLUMN; j++)
            {
                if((x == Coordinate_and_ID_Struct[i][j].X)&&(y == Coordinate_and_ID_Struct[i][j].Y))
                {
                        return Coordinate_and_ID_Struct[i][j].RS485_ID;
                }
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
                                                --downlink_message_struct : 下行报文的结构体
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
uint16_t CALCULATE_Total_length_Of_Downlink_Message(DownLink_Struct_Typedef downlink_message_struct)
{
    uint8_t i,j;
    uint16_t total_length_of_downlink_message = 0;
    char buffer_for_fprintf[10];

    //step1、计算rs485 ID的的字符长度 eg:485_ID是16,则total_length_of_downlink_message +=2;
    total_length_of_downlink_message += sprintf(buffer_for_fprintf,"%d",downlink_message_struct.RS485_ID);

    total_length_of_downlink_message += 1;  //下行报文中的485地址后面一个空格的地址

    //step2、计算指令cmd的字符长度，  eg：cmd是cfg，则total_length_of_downlink_message += 3
    for(i = 0; i<TOTAL_NUM_OF_CMD; i++)
    {
            if(downlink_message_struct.Cmd_Enum != Cmd_form_struct[i].e_Cmd)
            {
                continue;
            }
            else
            {
                total_length_of_downlink_message += strlen(Cmd_form_struct[i].s_Cmd);
                break;
            }
    }

    total_length_of_downlink_message +=1;  //下行报文中的cmd后面一个空格字符

    for(j = 0; j<downlink_message_struct.Total_num_of_Para; j++)
    {
            //step3、计算’参数类型‘的字符长度，例如 para_type是brd，则total_length_of_downlink_message += 3
            if( \
                (downlink_message_struct.Cmd_Enum == Cmd_cfg)&&  \
                (downlink_message_struct.Cmd_Enum == Cmd_zero)&& \
                (downlink_message_struct.Cmd_Enum == Cmd_demo)  \
              )
            {
                for(i = 0; i<TOTAL_NUM_OF_PARA_TYPE; i++)
                {
                        if(downlink_message_struct.Para_Struct[0]->e_Para_Type != Para_Type_form_Strcut[i].e_Para_Type)
                        {
                            continue;
                        }
                        else
                        {
                            total_length_of_downlink_message += (sizeof(Cmd_form_struct[j].s_Cmd)-1);
                        }
                }
                total_length_of_downlink_message += 1; //下行报文中的Cmd后面一个等号字符
            }

            //step4、计算‘参数值’的字符长度，例如 para_value是115200，则 total_length_of_downlink_message += 6

            total_length_of_downlink_message += sprintf(buffer_for_fprintf,"%d",downlink_message_struct.Para_Struct[0]->Para_Union.u_Para_Value);

            total_length_of_downlink_message += 2;     //下行报文中的para_value后面'\r\n'两个字符

    }

    return total_length_of_downlink_message;
}

/**********************************************************************
** 函数名称         :CONVERT_Cmd_Enum_Into_String
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :将“指令”的枚举类型转换为字符串类型
** 入口参数         :
												--Para_type_typedef  ：下行报文中“指令”的枚举变量
                                                --r_buffer ：           第一个形参，枚举变量对应的字符串 如Cmd_dev 对应 “dev”
** 返回参数         :
                                                --uint8_t :返回枚举变量对应的字符串字节长度
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
uint8_t CONVERT_Cmd_Enum_Into_String(Cmd_Typedef e_cmd,char * r_buffer)
{
    uint8_t i;
    uint8_t string_length_of_cmd;

    for(i=0; i<TOTAL_NUM_OF_CMD; i++)
    {
            if(e_cmd != Cmd_form_struct[i].e_Cmd)
            {
                continue;
            }
            else
            {
                string_length_of_cmd = strlen(Cmd_form_struct[i].s_Cmd);
                memcpy (r_buffer,Cmd_form_struct[i].s_Cmd,string_length_of_cmd);
                return string_length_of_cmd;
            }
    }
    return 0;
}



/**********************************************************************
** 函数名称         :CONVERT_Para_Type_Enum_Into_String
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :将”参数类型“的枚举类型转换为字符串类型
** 入口参数         :
												--Para_type_typedef  ：下行报文中“参数类型”的枚举变量
                                                --r_buffer ：           第一个形参，枚举变量对应的字符串 如Para_bdr 对应 “brd”
** 返回参数         :
                                                --uint8_t :返回枚举变量对应的字符串字节长度
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
uint8_t CONVERT_Para_Type_Enum_Into_String(Para_type_typedef e_para_type,char* r_buffer)
{
    uint8_t i;
    uint8_t string_length_of_para_type;

    for(i=0; i<TOTAL_NUM_OF_PARA_TYPE; i++)
    {
            if(e_para_type != Para_Type_form_Strcut[i].e_Para_Type)
            {
                continue;
            }
            else
            {
                string_length_of_para_type = strlen(Para_Type_form_Strcut[i].s_Para_Type);
                memcpy (r_buffer,Para_Type_form_Strcut[i].s_Para_Type,string_length_of_para_type);
                return string_length_of_para_type;
            }
    }

    return 0;
}



#if 0

//****************************************************
//UTC日期与当地日期转换
//****************************************************
void UTCDate2LocalDate(void)
{
	Day = (Day_High - 0x30) * 10 + (Day_Low-0x30) + 1;		//日  加一
	Month = (Month_High - 0x30) * 10 + (Month_Low - 0x30);
	Year = 2000 + (Year_High - 0x30) * 10 + (Year_Low - 0x30);

	MaxDay = GetMaxDay(Month,Year);				//获取当月 天数 最大值
	if(Day > MaxDay)		//溢出
	{
		Day = 1;
		Month += 1;
		if(Month > 12)
		{
			Year+=1;
		}
	}

	Day_High = Day/10 + 0x30;				//转换日期值为ASCII
	Day_Low = Day%10 + 0x30;

	Month_High = Month/10 + 0x30;			//转换月份值为ASCII
	Month_Low = Month%10 + 0x30;

	Year_High = Year%100/10 + 0x30;			//转换年份值为ASCII
	Year_Low = Year%10 + 0x30;
}

//****************************************************
//获取当月日期最大值
//****************************************************
unsigned char GetMaxDay(unsigned char Month_Value,unsigned int Year_Value)
{
	unsigned char iDays;
	switch(Month_Value)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			{
				iDays = 31;
			}
			break;
		case 2:
			{
				//2月份比较特殊，需要根据是不是闰年来判断当月是28天还29天
				iDays = IsLeapYear(Year_Value)?29:28;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			{
				iDays = 30;
			}
			break;
		default : break;
	}
	return(iDays);
}

//****************************************************
//闰年检测
//****************************************************
bit IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}

#endif


/**********************************************************************
** 函数名称         :CONVERT_Num_2_String
** 创建人           :
** 创建日期         :2019年3月3日16:20:43
** 最新修改人       :
** 最近修改日期     :2019年3月3日16:20:47
** 功能描述         :获取数字中的“十分位，百分位，个位，十位，百位，千万位，”并且以“字符”的形式输出
** 入口参数         :

												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** QQ               :
***********************************************************************/
char PICK_Char_From_Num(float num, Num_Position_Typedef position)
{
		char   char_temp= '0';
		uint16_t temp_value;
		switch(position)
		{
			case PRECENTILE_Enum:
			{
				num *= 100;
				num *= 10;
				temp_value = (uint16_t)num;
				temp_value %= 10000;
				temp_value %= 1000;
				temp_value %= 100;
				temp_value %= 10;
				char_temp =temp_value+0x30;  //

			};break;
			case TENTHS_DIGIT_POSITION_Enum:
			{
				num *= 10;
				temp_value = (uint16_t)num;
				temp_value %= 1000;
				temp_value %= 100;
				temp_value %= 10;
				char_temp =temp_value+0x30;  //
			};break;

			case UNIT_POSITION:
			{
				 temp_value = (uint16_t)num;
				 temp_value %= 100;
				 temp_value %= 10;
				 char_temp =temp_value+0x30;  //
			};break;
			case DECADE_POSITION:
			{
				  temp_value = (uint16_t)num;
				  temp_value %= 100;
				  temp_value /= 10;
				  char_temp =temp_value+0x30;  //
			};break;
			case HUNDERD_POSITOIN:
			{
					temp_value = (uint16_t)num;
					temp_value /= 100;
					char_temp =temp_value+0x30;  //
			};break;
			default:break;

		}
		return char_temp;
}

/**********************************************************************
** 函数名称         :bcc_checksum
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :BCC异或校验算法
** 入口参数         :uint8_t* data      被校验数据起始地址
                 uint8_t seed       校验码
                 int size           被校验数据长度


** 返回参数         :sum        校验结果

** 备注/注意        :
** QQ               :
***********************************************************************/
uint8_t BCC_Checksum(uint8_t* data, uint8_t seed, int size)
{
	uint8_t sum = seed;
	int index = 0;

	for (index = 0; index < size; index++)
	{
		sum ^= data[index];
	}
	return sum;
}


/**********************************************************************
** 函数名称         :Convert_Uplink_Frame_value_info
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :把5字节数据流转换成4字节数据
** 入口参数         :read uint8_t* data                 数据流
                 Uplink_Frame_value_info* info      数据


** 返回参数         :

** 备注/注意        :
** QQ               :
***********************************************************************/
void Convert_Uplink_Frame_value_info(uint8_t* data, Uplink_Frame_value_info* info)
{
	info->udata = data[0];

	info->udata <<= 7;
	info->udata |= data[1];
	info->udata <<= 7;
	info->udata |= data[2];
	info->udata <<= 7;
	info->udata |= data[3];
	info->udata <<= 7;
	info->udata |= data[4];
}

/**********************************************************************
** 函数名称         :MessageQ_info_Malloc
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :为消息队列通用数据结构申请内存空间
** 入口参数         :size_t data_length                 数据段长度


** 返回参数         :

** 备注/注意        :
** QQ               :
***********************************************************************/
MessageQ_info *MessageQ_info_Malloc(size_t data_length)
{
    MessageQ_info *ret = NULL;

    ret = pvPortMalloc(sizeof(MessageQ_info));
    if (NULL != ret)
    {
        ret->data = (uint8_t *)pvPortMalloc(data_length);
        if (NULL != ret->data)
        {
            ret->length = data_length;
        }
        else
        {
            vPortFree(ret);
            ret = NULL;
        }
    }

    return ret;
}

/**********************************************************************
** 函数名称         :MessageQ_info_Malloc
** 创建人           :
** 创建日期         :
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :释放通用数据结构的内存空间
** 入口参数         :size_t data_length                 数据段长度


** 返回参数         :

** 备注/注意        :
** QQ               :
***********************************************************************/
void MessageQ_info_Free(MessageQ_info **p)
{
    vPortFree((*p)->data);
    (*p)->data = NULL;

    vPortFree(*p);
    (*p) = NULL;
}

void Debug_Printf(const char *format, ...)
{
    MessageQ_info *msg_buf = NULL;
    size_t len = 0;
    va_list args;
    char str_buf[100];

	va_start(args,format);
    len = vsprintf(str_buf, format, args);
    va_end(args);

    msg_buf = MessageQ_info_Malloc(len);

    if (NULL != msg_buf)
    {
        memcpy(msg_buf->data, str_buf, len + 1);
        msg_buf->length = len + 1;

        osMessagePut(Debug_Message_Handle, (uint32_t)msg_buf, 10);
    }
    else
    {
        while(1);
    }
}
