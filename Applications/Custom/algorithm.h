#ifndef __ALGORITHM_H
#define __ALGORITHM_H

//1��ͷ�ļ�
/********************************************************************************************************************************************************************/
#include "stm32f1xx_hal.h"
#include "datastruct.h"
#include "string.h"
#include "stdio.h"
#include "Global.h"

//2���궨��
/********************************************************************************************************************************************************************/


//3�����Ͷ���
/********************************************************************************************************************************************************************/
typedef enum
{
	 PRECENTILE_Enum = 0,	            //�ٷ�λ
	 TENTHS_DIGIT_POSITION_Enum,        //ʮ��λ
	 UNIT_POSITION,                     //��λ
	 DECADE_POSITION,                   //ʮλ
	 HUNDERD_POSITOIN,                  //��λ
}Num_Position_Typedef;




//4����������
/********************************************************************************************************************************************************************/


//5����������
/********************************************************************************************************************************************************************/
char PICK_Char_From_Num(float num, Num_Position_Typedef position);
uint8_t BCC_Checksum(uint8_t* data, uint8_t seed, int size);
uint8_t  CHANGE_Coordinate_2_RS485_ID(uint8_t x, uint8_t y);
uint16_t  CALCULATE_Total_length_Of_Downlink_Message (DownLink_Struct_Typedef  downlink_message_struct);
void Convert_Uplink_Frame_value_info(uint8_t* data, Uplink_Frame_value_info* info);

uint8_t CONVERT_Cmd_Enum_Into_String(Cmd_Typedef e_cmd,char * r_buffer);
uint8_t CONVERT_Para_Type_Enum_Into_String(Para_type_typedef e_para_type,char* r_buffer);

MessageQ_info *MessageQ_info_Malloc(size_t data_length);
void MessageQ_info_Free(MessageQ_info **p);
void Debug_Printf(const char *format, ...);

#endif




