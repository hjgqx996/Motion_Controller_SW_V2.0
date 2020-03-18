//*********************************************************************
//
//           ��Ȩ���� (C), 2008-2028, �޲���ʵ����
//             -----------------------------------------------
//
//  �ļ�����:
//  ��������:
//  ��������:
//  �޸���ʷ:
//  (1) �޸�����:2019��3��1��
//      �޸�����:Liu-PC
//      �޸�����:
//
//*********************************************************************

#include "algorithm.h"
#include "Global.h"






/**********************************************************************
** ��������         :CHANGE_Coordinate_2_RS485_ID
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :�����������������ڽṹ��λ�õ�x�����y���꣬���ó����豸��Ӧ��RS485_ID��
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
                                                --downlink_message_struct : ���б��ĵĽṹ��
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
***********************************************************************/
uint16_t CALCULATE_Total_length_Of_Downlink_Message(DownLink_Struct_Typedef downlink_message_struct)
{
    uint8_t i,j;
    uint16_t total_length_of_downlink_message = 0;
    char buffer_for_fprintf[10];

    //step1������rs485 ID�ĵ��ַ����� eg:485_ID��16,��total_length_of_downlink_message +=2;
    total_length_of_downlink_message += sprintf(buffer_for_fprintf,"%d",downlink_message_struct.RS485_ID);

    total_length_of_downlink_message += 1;  //���б����е�485��ַ����һ���ո�ĵ�ַ

    //step2������ָ��cmd���ַ����ȣ�  eg��cmd��cfg����total_length_of_downlink_message += 3
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

    total_length_of_downlink_message +=1;  //���б����е�cmd����һ���ո��ַ�

    for(j = 0; j<downlink_message_struct.Total_num_of_Para; j++)
    {
            //step3�����㡯�������͡����ַ����ȣ����� para_type��brd����total_length_of_downlink_message += 3
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
                total_length_of_downlink_message += 1; //���б����е�Cmd����һ���Ⱥ��ַ�
            }

            //step4�����㡮����ֵ�����ַ����ȣ����� para_value��115200���� total_length_of_downlink_message += 6

            total_length_of_downlink_message += sprintf(buffer_for_fprintf,"%d",downlink_message_struct.Para_Struct[0]->Para_Union.u_Para_Value);

            total_length_of_downlink_message += 2;     //���б����е�para_value����'\r\n'�����ַ�

    }

    return total_length_of_downlink_message;
}

/**********************************************************************
** ��������         :CONVERT_Cmd_Enum_Into_String
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :����ָ���ö������ת��Ϊ�ַ�������
** ��ڲ���         :
												--Para_type_typedef  �����б����С�ָ���ö�ٱ���
                                                --r_buffer ��           ��һ���βΣ�ö�ٱ�����Ӧ���ַ��� ��Cmd_dev ��Ӧ ��dev��
** ���ز���         :
                                                --uint8_t :����ö�ٱ�����Ӧ���ַ����ֽڳ���
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :CONVERT_Para_Type_Enum_Into_String
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :�����������͡���ö������ת��Ϊ�ַ�������
** ��ڲ���         :
												--Para_type_typedef  �����б����С��������͡���ö�ٱ���
                                                --r_buffer ��           ��һ���βΣ�ö�ٱ�����Ӧ���ַ��� ��Para_bdr ��Ӧ ��brd��
** ���ز���         :
                                                --uint8_t :����ö�ٱ�����Ӧ���ַ����ֽڳ���
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
//UTC�����뵱������ת��
//****************************************************
void UTCDate2LocalDate(void)
{
	Day = (Day_High - 0x30) * 10 + (Day_Low-0x30) + 1;		//��  ��һ
	Month = (Month_High - 0x30) * 10 + (Month_Low - 0x30);
	Year = 2000 + (Year_High - 0x30) * 10 + (Year_Low - 0x30);

	MaxDay = GetMaxDay(Month,Year);				//��ȡ���� ���� ���ֵ
	if(Day > MaxDay)		//���
	{
		Day = 1;
		Month += 1;
		if(Month > 12)
		{
			Year+=1;
		}
	}

	Day_High = Day/10 + 0x30;				//ת������ֵΪASCII
	Day_Low = Day%10 + 0x30;

	Month_High = Month/10 + 0x30;			//ת���·�ֵΪASCII
	Month_Low = Month%10 + 0x30;

	Year_High = Year%100/10 + 0x30;			//ת�����ֵΪASCII
	Year_Low = Year%10 + 0x30;
}

//****************************************************
//��ȡ�����������ֵ
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
				//2�·ݱȽ����⣬��Ҫ�����ǲ����������жϵ�����28�컹29��
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
//������
//****************************************************
bit IsLeapYear(unsigned int uiYear)
{
	return (((uiYear%4)==0)&&((uiYear%100)!=0))||((uiYear%400)==0);
}

#endif


/**********************************************************************
** ��������         :CONVERT_Num_2_String
** ������           :
** ��������         :2019��3��3��16:20:43
** �����޸���       :
** ����޸�����     :2019��3��3��16:20:47
** ��������         :��ȡ�����еġ�ʮ��λ���ٷ�λ����λ��ʮλ����λ��ǧ��λ���������ԡ��ַ�������ʽ���
** ��ڲ���         :

												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
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
** ��������         :bcc_checksum
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :BCC���У���㷨
** ��ڲ���         :uint8_t* data      ��У��������ʼ��ַ
                 uint8_t seed       У����
                 int size           ��У�����ݳ���


** ���ز���         :sum        У����

** ��ע/ע��        :
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
** ��������         :Convert_Uplink_Frame_value_info
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :��5�ֽ�������ת����4�ֽ�����
** ��ڲ���         :read uint8_t* data                 ������
                 Uplink_Frame_value_info* info      ����


** ���ز���         :

** ��ע/ע��        :
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
** ��������         :MessageQ_info_Malloc
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :Ϊ��Ϣ����ͨ�����ݽṹ�����ڴ�ռ�
** ��ڲ���         :size_t data_length                 ���ݶγ���


** ���ز���         :

** ��ע/ע��        :
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
** ��������         :MessageQ_info_Malloc
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :�ͷ�ͨ�����ݽṹ���ڴ�ռ�
** ��ڲ���         :size_t data_length                 ���ݶγ���


** ���ز���         :

** ��ע/ע��        :
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
