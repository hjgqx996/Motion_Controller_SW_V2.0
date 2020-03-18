#ifndef _PIN_REMAP_H
#define _PIN_REMAP_H

//1��ͷ�ļ�
/********************************************************************************************************************************************************************/
#include "stm32f1xx_hal.h"

//2���궨��
/********************************************************************************************************************************************************************/
//1�����÷�Χ��key.c
////////*********************************************************/
//������ԭ����ADC����������ʹ��������ADC���������룬
//ÿ��ADC�����������8��������һ��16������
//һ����PC5 ,һ����PB0
#define ADC_KEY_PORT1		 GPIOC          //��δƥ��
#define ADC_KEY_PORT1_Pin1   GPIO_PIN_5     //��δƥ��
/*******************************************************//////////

//2�����÷�Χ:LCD12864.c
////////////*******************************************************/
// 0�������⣬1���ر���
#define LCD_BL_PORT		GPIOC 	             //��δƥ��
#define LCD_BL_PIN		GPIO_PIN_13          //��δƥ��
// 1�����ݣ�0������
#define LCD_RS_PORT		GPIOA 	             //��δƥ��
#define LCD_RS_PIN		GPIO_PIN_6           //��δƥ��
// LCD����ѡ�񣬵͵�ƽʹ��
#define LCD_CS_PORT		GPIOC                //��δƥ��
#define LCD_CS_PIN      GPIO_PIN_4           //��δƥ��
// LCD��λ�� �͵�ƽ��λ
#define LCD_RST_PORT	GPIOA                //��δƥ��
#define LCD_RST_PIN    GPIO_PIN_4           //��δƥ��
/*********************************************************///////////

//3�����÷�Χ��Flash.c
////////////*******************************************************/
#define  EXFLASH_MOSI_PORT  GPIOD            //��δƥ��
#define  EXFLASH_MOSI_PIN   GPIO_PIN_3       //��δƥ��

#define EXFLASH_MISO_PORT   GPIOD            //��δƥ��
#define EXFLASH_MISO_PIN    GPIO_PIN_4       //��δƥ��

#define EXFLASH_CLK_PORT   GPIOD             //��δƥ��
#define EXFLASH_CLK_PIN    GPIO_PIN_5        //��δƥ��

#define EXFLASH_CS1_PORT   GPIOD             //��δƥ��
#define EXFLASH_CS1_PIN    GPIO_PIN_6        //��δƥ��

#define EXFLASH_CS2_PORT   GPIOD             //��δƥ��
#define EXFLASH_CS2_PIN    GPIO_PIN_7        //��δƥ��
/*********************************************************///////////

//4�����÷�Χ��EEprom.c
////////////*******************************************************/

/*********************************************************///////////

//4�����÷�Χ��Ex_adc.c
////////////*******************************************************/


//5�����÷�Χ DigitalCollect.c
/*********************************************************///////////


//5�����÷�Χ power.c
/*********************************************************///////////



//6.���÷�Χ RS485_Module.c
#define SW_Of_T_R_GPIO_Port     GPIOE
#define SW_Of_T_R_Pin           GPIO_PIN_15
//7.���÷�Χ sensor_port_bsp.h




//3�����Ͷ���
/********************************************************************************************************************************************************************/


//4����������
/********************************************************************************************************************************************************************/


//5����������
/********************************************************************************************************************************************************************/







#endif




