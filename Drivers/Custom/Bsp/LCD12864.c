//*********************************************************************
//
//           版权所有 (C), 2008-2028, 萝卜科技工作室
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


#include "LCD12864.h"
#include <stdbool.h>
#include "spi.h"

DEVICE_DEFINE(LCD12864_0,DEVICE_ZERO)

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
DEVICE_FUNC_DEFINE_OPEN(LCD12864_0)
{
	//	first_enter_sign==1：表示第一次进该函数
	//  first_enter_sign==0：表示不是第一次进该函数
	static uint8_t first_enter_sign = 1;

	if(1 == first_enter_sign)
	{
			LCD12864_BL_ON();
			LCD12864_CS_OFF();
			LCD12864_RST_STOP();

			LCD_Init();
			first_enter_sign=0;
	}

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
DEVICE_FUNC_DEFINE_CLOSE(LCD12864_0)
{
	LCD12864_BL_OFF();

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
DEVICE_FUNC_DEFINE_READ(LCD12864_0)
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
DEVICE_FUNC_DEFINE_WRITE(LCD12864_0)
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
DEVICE_FUNC_DEFINE_LSEEK(LCD12864_0)
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
DEVICE_FUNC_DEFINE_IOCTL(LCD12864_0)
{
	switch((Lcd_Ctl_Cmd_Typedef)cmd)
	{
			case CMD_CLEAR_SCREEN:    	 //具体调用举例：DEV_Ioctl(DEVICE_ZERO,CMD_CLEAR_SCREEN);
			{
				CLEAR_Screen();
			};break;
			case CMD_DISPLAY_FULL_IMAGE:  //具体调用举例：DEV_Ioctl(DEVICE_ZERO,CMD_DISPLAY_FULL_IMAGE);
			{
				uint8_t* dot_array_ptr_2;
				dot_array_ptr_2 = va_arg(*args_temp, uint8_t *);

				DISPLAY_Full_Image(dot_array_ptr_2);
			};break;
			case CMD_DISPLAY_ICON_32x32:   //具体调用举例：DEV_Ioctl(DEVICE_ZERO,CMD_DISPLAY_ICON_32x32,1,1,hz0);
			{
				uint8_t column_2,page_2;
				uint8_t* dot_array_ptr_2;

				page_2          = va_arg(*args_temp, int);
				column_2        = va_arg(*args_temp, int);
				dot_array_ptr_2 = va_arg(*args_temp, uint8_t *);

				DISPLAY_Icon_32x32(page_2,column_2,dot_array_ptr_2);
				//DISPLAY_Icon_32x32();
			};break;
			case CMD_DISPLAY_ICON_16x16:
			{
				uint8_t column_2, page_2;
				uint8_t *dot_array_ptr_2;

				page_2          = va_arg(*args_temp, int);
				column_2        = va_arg(*args_temp, int);
				dot_array_ptr_2 = va_arg(*args_temp, uint8_t *);

				DISPLAY_Icon_16x16(page_2, column_2, dot_array_ptr_2);      //具体调用举例：DEV_Ioctl(DEVICE_ZERO,);
			};break;
			case CMD_DISPLAY_ICON_8x16:
			{
				uint8_t column_2, page_2;
				uint8_t *dot_array_ptr_2;

				page_2          = va_arg(*args_temp, int);
				column_2        = va_arg(*args_temp, int);
				dot_array_ptr_2 = va_arg(*args_temp, uint8_t *);

				DISPLAY_Icon_8x16(page_2, column_2, dot_array_ptr_2);       //具体调用举例：DEV_Ioctl(DEVICE_ZERO,);
			};break;
			case CMD_DISPLAY_STRING_8x16:
			{
				//DISPLAY_String_8x16()
				//具体调用举例：DEV_Ioctl(DEVICE_ZERO,);
			};break;
			case CMD_DISPALY_STRING_5x7:
			{
				//DISPALY_String_5x7()
				//具体调用举例：DEV_Ioctl(DEVICE_ZERO,);
			};break;
			default:
			{

			};break;
	}
	//va_end(args);
	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :写指令到LCD 模块
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void SPI_Send_Cmd(uint8_t data_0)
{
	LCD12864_CS_ON();
	LCD12864_RS_COMMOND();

	HAL_SPI_Transmit(&hspi1,&data_0,1,10);        //8bit传输时间：640ns

	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :写数据到LCD 模块
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void SPI_Send_Data(uint8_t data_0)
{
	LCD12864_CS_ON();
	LCD12864_RS_DATA();

	HAL_SPI_Transmit(&hspi1,&data_0,1,10);

	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :延时
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void delay(int i)
{
	int j,k;
	for(j=0;j<i;j++)
	{
			for(k=0;k<110;k++);
	}
}


/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :LCD 模块初始化
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void LCD_Init()
{
	LCD12864_CS_ON();

	LCD12864_RST_START(); 	/*低电平复位*/
//	delay(100);
    delay(200);

	LCD12864_RST_STOP(); 	/*复位完毕*/
	delay(450);
	SPI_Send_Cmd(0xe2); /*软复位*/
	delay(10);
	SPI_Send_Cmd(0x2c); /*升压步聚1*/
	delay(10);
	SPI_Send_Cmd(0x2e); /*升压步聚2*/
	delay(10);
	SPI_Send_Cmd(0x2f); /*升压步聚3*/
	delay(10);
	SPI_Send_Cmd(0x23); /*粗调对比度，可设置范围0x20～0x27*/
	SPI_Send_Cmd(0x81); /*微调对比度*/
	SPI_Send_Cmd(0x28); /*0x1a,微调对比度的值，可设置范围0x00～0x3f*/
	SPI_Send_Cmd(0xa2); /*1/9 偏压比（bias）*/
	SPI_Send_Cmd(0xc8); /*行扫描顺序：从上到下*/
	SPI_Send_Cmd(0xa0); /*列扫描顺序：从左到右*/
	SPI_Send_Cmd(0x40); /*起始行：第一行开始*/
	SPI_Send_Cmd(0xaf); /*开显示*/

	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :SET_Lcd_Cursor_Address
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :设置LCD光标地址
** 入口参数         :
							uint8_t page:页地址 1页~8页
							uint8_t column：列地址：1列~128列
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void SET_Lcd_Cursor_Address(uint8_t page,uint8_t column)
{
	LCD12864_CS_ON();
	column=column-1; //我们平常所说的第1 列，在LCD 驱动IC 里是第0 列。所以在这里减去1.
	page=page-1;
	//设置页地址。每页是8 行。一个画面的64 行被分成8个页。
	//我们平常所说的第1 页，在LCD 驱动IC 里是第0 页，所以在这里减去1
	SPI_Send_Cmd(0xb0+page);

	SPI_Send_Cmd(((column>>4)&0x0f)+0x10); //设置列地址的高4 位
	SPI_Send_Cmd(column&0x0f); //设置列地址的低4 位
}


/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :全屏清屏
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void CLEAR_Screen()
{
	unsigned char i, j;
	LCD12864_CS_ON();
	for(i = 0; i < 9; i++)
	{
		SET_Lcd_Cursor_Address(1 + i, 1);
		for(j = 0;j < 132; j++)
		{
			SPI_Send_Data(0x00);
		}
	}
	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :display a piture of 128*64 dots
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void DISPLAY_Full_Image(uint8_t *dp)
{
	int i, j;
    LCD12864_CS_ON();
	for(i = 0; i < 8; i++)
	{
		SET_Lcd_Cursor_Address(i + 1, 0);
		for(j = 0; j < 128; j++)
		{
			SPI_Send_Data(*dp);
            dp++;
		}
	}
	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :DISPLAY_String_32x32
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :显示32x32点阵图标 、汉字、生僻字或32x32 点阵的其他图标
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void DISPLAY_Icon_32x32(uint8_t page, uint8_t column, uint8_t *dp)
{
	uint8_t i, j;
	LCD12864_CS_ON();

	for(j = 0; j < 4; j++)
	{
		SET_Lcd_Cursor_Address(page + j, column);
		for (i = 0; i < 32; i++)
		{
			SPI_Send_Data(*dp); /*写数据到LCD,每写完一个8 位的数据后列地址自动加1*/
			dp++;
		}
	}

	LCD12864_CS_OFF();
}
/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :显示16x16 点阵图像、汉字、生僻字或16x16 点阵的其他图标
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void DISPLAY_Icon_16x16(uint8_t page, uint8_t column, uint8_t *dp)
{
	uint8_t i, j;
	LCD12864_CS_ON();
	for(j = 0; j < 2; j++)
	{
		SET_Lcd_Cursor_Address(page + j, column);
		for(i = 0; i < 16; i++)
		{
            /*写数据到LCD,每写完一个8 位的数据后列地址自动加1*/
			SPI_Send_Data(*dp);
			dp++;
		}
	}
	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :显示8x16 点阵图像、ASCII, 或8x16 点阵的自造字符、其他图标
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void DISPLAY_Icon_8x16(uint8_t page, uint8_t column, uint8_t *dp)
{
	uint8_t i, j;
	LCD12864_CS_ON();
	for (j = 0; j < 2; j++)
	{
		SET_Lcd_Cursor_Address(page + j, column);
		for (i = 0; i < 8; i++)
		{
			SPI_Send_Data(*dp); /*写数据到LCD,每写完一个8 位的数据后列地址自动加1*/
			dp++;
		}
	}
	LCD12864_CS_OFF();
}

/**********************************************************************
** 函数名称         :DISPLAY_String_8x16
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :显示8*16的英文字符
** 入口参数         :
								uint8_t page（页数）：1页~8页
								uint8_t column（列数）：1列~128列
								uint8_t *text（英文字符）：例如  'A' 'B'
--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
								eg:DISPLAY_String_8x16(3,20,'APPLE');
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void DISPLAY_String_8x16(uint8_t page,uint8_t column,uint8_t *text)
{
	uint8_t i=0,j,k,n;
	LCD12864_CS_ON();
	while(text[i]>0x00)
	{
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			for(n=0;n<2;n++)
			{
				SET_Lcd_Cursor_Address(page+n,column);
				for(k=0;k<8;k++)
				{
    				/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
    				SPI_Send_Data(ascii_table_8x16[j][k+8*n]);
				}
			}
			i++;
			column+=8;
		}
		else
		{
			i++;
		}
	}
}

/**********************************************************************
** 函数名称         :DISPALY_String_5x7
** 创建人           :LiuPC
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
								uint8_t page（页数）：1页~8页
								uint8_t column（列数）：1列~128列
								uint8_t *text（英文字符）：例如  'A' 'B'
** 返回参数         :
												--NONE
** 备注/注意        :eg:DISPLAY_String_5x7(3,20,'APPLE');
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
//void DISPALY_String_5x7(uint8_t page,uint8_t column,uint8_t *text)
//{
//	uint8_t i=0,j,k;
//	LCD12864_CS_ON();
//	while(text[i]>0x00)
//	{
//			if((text[i]>=0x20)&&(text[i]<0x7e))
//			{
//				j = text[i]-0x20;
//				SET_Lcd_Cursor_Address(page,column);
//				for(k=0;k<5;k++)
//				{
//						/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
//						//SPI_Send_Data(ascii_table_5x7[j][k]);
//				}
//				i++;
//				column+=6;
//			}
//			else
//			{
//				i++;
//			}
//	}
//}
















