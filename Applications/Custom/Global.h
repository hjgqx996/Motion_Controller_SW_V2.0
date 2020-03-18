#ifndef __GLOBAL_H
#define __GLOBAL_H

//1、头文件
/********************************************************************************************************************************************************************/

//底层驱动接口
#include "stm32f1xx_hal.h"
#include "printf.h"
#include "pin_remap.h"
#include "usart.h"
#include "adc.h"
#include "key.h"

//中间中接口
#include "coupling_between_app_and_bsp.h"
#include "gbk_font_matrix.h"
#include "trcRecorder.h"
#include "factory_setting.h"
#include "cmsis_os.h"
#include "pin_remap.h"
#include "datastruct.h"
#include "fifo.h"
#include "stm32f1xx_it.h"

//应用层接口
#include "string.h"
#include "algorithm.h"
#include "UI.h"




//2、宏定义
/********************************************************************************************************************************************************************/
#define  PRIORITY_ISR_USART3   6        //USART3的抢占中断优先级


//3、类型定义
/********************************************************************************************************************************************************************/





//4、变量声明
/**************Status_Of_Triggle_Send_Task_Typedef Status_Of_Triggle_Send_Task = Preparing_Animation_data_Status;******************************************************************************************************************************************************/
extern osSemaphoreId Uart3_DevideFrame_SemHandle;  //串口中断-->解码线程
extern osMessageQId Debug_Message_Handle;
extern osMessageQId Key_Message_Handle;

//5、函数声明
/********************************************************************************************************************************************************************/
void GLOBAL_Variable_Init(void);


void BSP_Init(void);
void MIDDLEWARE_Init(void);
void APP_Init(void);



void task_devide_frame_init(void);


#endif






























