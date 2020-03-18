/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Global.h"
#include "fifo.h"
#include "algorithm.h"
#include "UI.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern UART_HandleTypeDef huart1;
/* USER CODE END Variables */
osThreadId TASK_1Handle;
osThreadId TASK_2Handle;
osThreadId TASK_3Handle;
osThreadId TASK_4Handle;
osThreadId TASK_5Handle;
osThreadId TASK_6Handle;
osThreadId TASK_7Handle;
osThreadId TASK_8Handle;
osThreadId TASK_9Handle;
osSemaphoreId Uart3_DevideFrame_SemHandle;  //串口中断-->解码线程
osMessageQId Uplink_MessageHandle;          //分帧线程--上行报文-->解码线程
osMessageQId UpLink_StructureHandle;        //解码线程--上行结构体-->执行线程

osMessageQId DownLink_Message_Handle;       //编码线程--下行报文-->发送线程
osMessageQId DownLink_StructureHandle;      //数据采集线程--下行结构体-->编码线程

osMessageQId Send_Ack_Handle;               //执行线程--上行报文设备ID-->触发线程
osMessageQId Debug_Message_Handle;          //所有的线程--调试信息-->调试输出线程
osMessageQId Motor_Coordinate_Handle;       //触发线程--电机坐标-->采集线程
osMessageQId Key_Message_Handle;            //按键消息队列

osPoolId Uplink_Para_Struct_Handle;


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TASK_Trigger_Send(void const * argument);
void TASK_Collect_Data(void const * argument);
void TASK_Code(void const * argument);
void TASK_Send(void const * argument);
void TASK_Devide_Frame(void const * argument);
void TASK_Decode(void const * argument);
void TASK_Execute(void const * argument);
void TASK_Debug_Output(void const * argument);
void TASK_Ui(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */
  osPoolDef(Uplink_Para_Struct,24,Para_Struct_Typedef);
  Uplink_Para_Struct_Handle = osPoolCreate(osPool(Uplink_Para_Struct));
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */

  /* 创建uart3中断和分帧线程通信的信号量 */
  osSemaphoreDef(Uart3_DevideFrame_SemHandle);
  Uart3_DevideFrame_SemHandle = osSemaphoreCreate(osSemaphore(Uart3_DevideFrame_SemHandle), 0);

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of Uplink_Message */
  osMessageQDef(Uplink_Message, 16, uint32_t);
  Uplink_MessageHandle = osMessageCreate(osMessageQ(Uplink_Message), NULL);

  /* definition and creation of UpLink_Structure */
  osMessageQDef(UpLink_Structure, 16, uint32_t);
  UpLink_StructureHandle = osMessageCreate(osMessageQ(UpLink_Structure), NULL);

  osMessageQDef(DownLink_Message, 16, uint32_t);
  DownLink_Message_Handle = osMessageCreate(osMessageQ(DownLink_Message), NULL);

  /* definition and creation of DownLink_Structure */
  osMessageQDef(DownLink_Structure, 16, uint32_t);
  DownLink_StructureHandle = osMessageCreate(osMessageQ(DownLink_Structure), NULL);

  osMessageQDef(Send_Ack, 16, uint32_t);
  Send_Ack_Handle = osMessageCreate(osMessageQ(Send_Ack), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  osMessageQDef(Debug_Message, 64, uint32_t);
  Debug_Message_Handle = osMessageCreate(osMessageQ(Debug_Message),NULL);

  osMessageQDef(Motor_Coordinate,10,uint32_t);
  Motor_Coordinate_Handle = osMessageCreate(osMessageQ(Motor_Coordinate),NULL);

  osMessageQDef(Key_Message, 4, uint16_t);
  Key_Message_Handle = osMessageCreate(osMessageQ(Key_Message),NULL);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of TASK_1 */
  osThreadDef(TASK_Trigger, TASK_Trigger_Send, osPriorityIdle, 0, 128);
  TASK_1Handle = osThreadCreate(osThread(TASK_Trigger), NULL);

  /* definition and creation of TASK_2 */
  osThreadDef(TASK_Collect, TASK_Collect_Data, osPriorityNormal, 0, 128);
  TASK_2Handle = osThreadCreate(osThread(TASK_Collect), NULL);

  /* definition and creation of TASK_3 */
  osThreadDef(TASK_Code, TASK_Code, osPriorityNormal, 0, 128);
  TASK_3Handle = osThreadCreate(osThread(TASK_Code), NULL);

  /* definition and creation of TASK_4 */
  osThreadDef(TASK_Send, TASK_Send, osPriorityLow, 0, 128);
  TASK_4Handle = osThreadCreate(osThread(TASK_Send), NULL);

  /* definition and creation of TASK_5 */
  osThreadDef(TASK_Devide_F, TASK_Devide_Frame, osPriorityIdle, 0, 128);
  TASK_5Handle = osThreadCreate(osThread(TASK_Devide_F), NULL);

  /* definition and creation of TASK_6 */
  osThreadDef(TASK_Decode, TASK_Decode, osPriorityIdle, 0, 128);
  TASK_6Handle = osThreadCreate(osThread(TASK_Decode), NULL);

  /* definition and creation of TASK_7 */
  osThreadDef(TASK_Execute, TASK_Execute, osPriorityIdle, 0, 128);
  TASK_7Handle = osThreadCreate(osThread(TASK_Execute), NULL);

  /* definition and creation of TASK_8 */
  osThreadDef(TASK_Debug, TASK_Debug_Output, osPriorityBelowNormal, 0, 128);
  TASK_8Handle = osThreadCreate(osThread(TASK_Debug), NULL);

  /* definition and creation of TASK_9 */
  osThreadDef(TASK_Ui, TASK_Ui, osPriorityIdle, 0, 128);
  TASK_9Handle = osThreadCreate(osThread(TASK_Ui), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TASK_Trigger_Send */
/**
  * @brief  Function implementing the TASK_1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TASK_Trigger_Send */
void TASK_Trigger_Send(void const * argument)
{

  /* USER CODE BEGIN TASK_Trigger_Send */

    uint8_t resend_time = 0;

  /* Infinite loop */
    for(;;)
    {
        static uint8_t i = 0, j = 0;


        //HAL_StatusTypeDef hal_status;
        switch(Status_Of_Triggle_Send_Task)
        {
            case Preparing_Animation_Data_Status:
            {
                //Part1、闹钟触发进入Waiting_Count_Down_Status状态
                Status_Of_Triggle_Send_Task = Waiting_Count_Down_Status;


                //Part2、广域网的下行报文触发进入Waiting_Count_Down_Status状态


                //Part3、UI交互界面触发进入Waiting_Count_Down_Status状态

                break;
            };
            case Waiting_Count_Down_Status:
            {
                //1.1、倒计时结束时 触发发送一帧 驱动器控制报文 ，然后进入Waiting_Ack_Status 状态
                resend_time = 0;


                if(12 == j)
                {
                    if(0 == i)
                    {
                        i = 1;
                    }
                    else if(1 == i)
                    {
                        i = 0;
                    }
                    j=0;
                    osDelay(8000);
                }

                osMessagePut(Motor_Coordinate_Handle, (uint32_t)&Motor_Coordinate_Array[i][j++], 10);

                Status_Of_Triggle_Send_Task = Waiting_Ack_Status;
                    //1.2、发送完所有的 所以驱动器控制报文，然后进入 Preparing_Animation_data_Status 状态

                break;
            };
            case Waiting_Ack_Status:
            {
                uint8_t cid;
                osEvent event;

                //1、收到电机驱动器的上行报文响应，触发进入 Waiting_Count_Down_Status 状态
                event = osMessageGet(Send_Ack_Handle, 400);
                if (osEventMessage == event.status)
                {
                    /* 之后还需要对cid做校验 */

                    cid = (uint8_t)event.value.v;

                    Status_Of_Triggle_Send_Task = Waiting_Count_Down_Status;
                }
                else if (osEventTimeout == event.status)
                {

                    cid = CHANGE_Coordinate_2_RS485_ID(Motor_Coordinate_Array[i][j-1].X,Motor_Coordinate_Array[i][j-1].Y);

                    Status_Of_Triggle_Send_Task = Timeout_Resend_Status;
                }

                break;
            };
            case Timeout_Resend_Status:
            {
                osMessagePut(Motor_Coordinate_Handle, (uint32_t)&Motor_Coordinate_Array[i][j - 1], 10);
                resend_time++;

                if (3 > resend_time)
                {
                  Status_Of_Triggle_Send_Task = Waiting_Ack_Status;
                }
                else
                {
                  Status_Of_Triggle_Send_Task = Waiting_Count_Down_Status;
                }

                break;
            }
            default:
            {
                break;
            };
        }
        //hal_status= HAL_UART_Transmit(&huart1, (uint8_t *)0x7A, 1, 2);

        osDelay(55);

    }
  /* USER CODE END TASK_Trigger_Send */
}

/* USER CODE BEGIN Header_TASK_Collect_Data */
/**
* @brief Function implementing the TASK_2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Collect_Data */
void TASK_Collect_Data(void const * argument)
{
  /* USER CODE BEGIN TASK_Collect_Data */


  /* Infinite loop */
  for(;;)
  {
        osStatus status;
        osEvent event;
        DownLink_Struct_Typedef  DownLink_Message_Struct;
        Motor_Coordinate_typedef Motor_Coordinate_temp_0;


        event = osMessageGet(Motor_Coordinate_Handle,10);
        if(osEventMessage == event.status)
        {
            memcpy(&Motor_Coordinate_temp_0,    \
                   (Motor_Coordinate_typedef *)event.value.p,     \
                   sizeof(Motor_Coordinate_typedef));

            DownLink_Message_Struct.RS485_ID = CHANGE_Coordinate_2_RS485_ID(Motor_Coordinate_temp_0.X,Motor_Coordinate_temp_0.Y);
            DownLink_Message_Struct.Cmd_Enum = Cmd_pos;

            DownLink_Message_Struct.Total_num_of_Para = 1;

            DownLink_Message_Struct.Para_Struct[0]= (Para_Struct_Typedef*)osPoolAlloc(Uplink_Para_Struct_Handle);
            DownLink_Message_Struct.Para_Struct[0]->e_Para_Type = Para_value;
            DownLink_Message_Struct.Para_Struct[0]->Para_Union.u_Para_Value = Motor_Coordinate_temp_0.Z;

            status = osMessagePut(DownLink_StructureHandle,(uint32_t)&DownLink_Message_Struct,10);
            if(osOK != status)
            {

            }
        }




        osDelay(10);

  }
  /* USER CODE END TASK_Collect_Data */
}

/* USER CODE BEGIN Header_TASK_Code */
/**
* @brief Function implementing the TASK_3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Code */
void TASK_Code(void const * argument)
{
  /* USER CODE BEGIN TASK_Code */
  //char test_string[5]={'a','b','c','d','e'};

  /* Infinite loop */
  for(;;)
  {
          osEvent event_0;
          osStatus status_0;
          DownLink_Struct_Typedef   Downlink_Struct_0;

          Downlink_Frame_typedef downlink_frame_struct_0;
              uint8_t total_length_of_downlink_message = 0;
              char * downlink_message_head_ptr = NULL;      //指向下行报文帧中首地址的指针
              char * downlink_message_movable_ptr;          //下行报文帧中可移动的指针


          char buffer_for_sprintf[5];
          uint8_t string_length;
          uint8_t i;


          event_0 = osMessageGet(DownLink_StructureHandle,10);

          if(osEventMessage == event_0.status)
          {
              memcpy(&Downlink_Struct_0,(DownLink_Struct_Typedef *)event_0.value.p,sizeof(DownLink_Struct_Typedef));

              total_length_of_downlink_message = CALCULATE_Total_length_Of_Downlink_Message(Downlink_Struct_0);

              downlink_message_head_ptr = pvPortMalloc(total_length_of_downlink_message);

              downlink_message_movable_ptr = downlink_message_head_ptr;

              //step1、编码RS485的ID
              string_length = sprintf(buffer_for_sprintf,"%d",Downlink_Struct_0.RS485_ID);
              memcpy(downlink_message_movable_ptr,buffer_for_sprintf,string_length);
              downlink_message_movable_ptr = downlink_message_movable_ptr + string_length;

              //step2、编码RS485的ID号后面的空格
              *downlink_message_movable_ptr =' ';
              downlink_message_movable_ptr += 1;

              //step3、编码指令码
              string_length = CONVERT_Cmd_Enum_Into_String( \
                                                               Downlink_Struct_0.Cmd_Enum,\
                                                               buffer_for_sprintf \
                                                          );
              memcpy( \
                         downlink_message_movable_ptr,\
                         buffer_for_sprintf,\
                         string_length
                    );
              downlink_message_movable_ptr = downlink_message_movable_ptr + string_length;

              //step4、编码指令后面的空格
              *downlink_message_movable_ptr =' ';
              downlink_message_movable_ptr += 1;

              for(i=0; i<Downlink_Struct_0.Total_num_of_Para; i++)
              {
                      if( \
                          (Downlink_Struct_0.Cmd_Enum == Cmd_cfg)&&  \
                          (Downlink_Struct_0.Cmd_Enum == Cmd_zero)&& \
                          (Downlink_Struct_0.Cmd_Enum == Cmd_demo)   \
                        )
                      {
                          //step5、编码参数类型
                          string_length = CONVERT_Para_Type_Enum_Into_String(   \
                                                                                 Downlink_Struct_0.Para_Struct[0]->e_Para_Type,  \
                                                                                 buffer_for_sprintf \
                                                                            );
                          memcpy( \
                                     downlink_message_movable_ptr, \
                                     buffer_for_sprintf, \
                                     string_length \
                                );
                          downlink_message_movable_ptr = downlink_message_movable_ptr + string_length;

                          //step6、编码参数类型后面的等号
                          *downlink_message_movable_ptr ='=';
                          downlink_message_movable_ptr += 1;

                      }
                      //step7、编码参数值
                      string_length = sprintf(   \
                                                   buffer_for_sprintf, \
                                                   "%d",  \
                                                   Downlink_Struct_0.Para_Struct[0]->Para_Union.u_Para_Value \
                                             );
                      memcpy( \
                                 downlink_message_movable_ptr, \
                                 buffer_for_sprintf, \
                                 string_length \
                            );
                      downlink_message_movable_ptr = downlink_message_movable_ptr + string_length;
              }

              //step5、编码换行符
              *downlink_message_movable_ptr ='\r';
              downlink_message_movable_ptr+=1;

              *downlink_message_movable_ptr ='\n';


              downlink_frame_struct_0.head_ptr = downlink_message_head_ptr;
              downlink_frame_struct_0.total_length = total_length_of_downlink_message;

              status_0 = osMessagePut(DownLink_Message_Handle,(uint32_t)&downlink_frame_struct_0,10);
              if(osOK == status_0)
              {
                      for(i=0; i<Downlink_Struct_0.Total_num_of_Para; i++)
                      {
                          osPoolFree(Uplink_Para_Struct_Handle,Downlink_Struct_0.Para_Struct[i]);
                          Downlink_Struct_0.Para_Struct[i] = NULL;
                      }
              }

          }


          osDelay(10);

  }
  /* USER CODE END TASK_Code */
}

/* USER CODE BEGIN Header_TASK_Send */
/**
* @brief Function implementing the TASK_4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Send */
void TASK_Send(void const * argument)
{
    /* USER CODE BEGIN TASK_Send */
    /* Infinite loop */
    for(;;)
    {
        osEvent event_0;
        Downlink_Frame_typedef* downlink_frame_struct_0;

        event_0 = osMessageGet(DownLink_Message_Handle,10);
        if(osEventMessage == event_0.status)
        {
            downlink_frame_struct_0 = (Downlink_Frame_typedef*)event_0.value.p;

            DEV_Write(DEVICE_TWO,downlink_frame_struct_0->head_ptr,downlink_frame_struct_0->total_length,0x00);



            vPortFree(downlink_frame_struct_0->head_ptr);
            downlink_frame_struct_0->head_ptr = NULL;
        }

        //DEV_Ioctl(DEVICE_TWO, CMD_SEND_Or_RECEIVE, Direction_Output);
        osDelay(10);
    }
    /* USER CODE END TASK_Send */
}

/* USER CODE BEGIN Header_TASK_Devide_Frame */
/**
* @brief Function implementing the TASK_5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Devide_Frame */
void TASK_Devide_Frame(void const * argument)
{
  /* USER CODE BEGIN TASK_Devide_Frame */
  /* Infinite loop */
    for(;;)
    {
        uint8_t tmp;
        uint8_t sum;
        uint8_t seed;

        /* 执行状态机 */
        switch (g_Devide_Frame_Task_FSM.status)
        {
            case WAITING_STATE:
            {
                uint8_t rest_num_of_token=0;

                rest_num_of_token = osSemaphoreWait(Uart3_DevideFrame_SemHandle, osWaitForever);
                //TRACE("FUNCTION:%s,LINE:%d-----rest_num_of_token:%d\r\n",__FUNCTION__,__LINE__,rest_num_of_token);
                Fifo_Out(&g_Uart3_DevideFrame_Fifo, &tmp, 1);

                if (UPLINK_FRAME_HEADER == tmp)
                {
                    g_Devide_Frame_Task_FSM.status = RECEIVE_STATE;
                }
                else
                {
                    g_Devide_Frame_Task_FSM.status = DROP_STATE;
                }

                break;
            }
            case RECEIVE_STATE:
            {
                Fifo_Out(&g_Uart3_DevideFrame_Fifo, &tmp, 1);

                if (UPLINK_FRAME_TAIL == tmp)   //如果到帧尾，则上一字节是校验和，进行校验
                {
                    seed = ((g_Devide_Frame_Task_FSM.data)[g_Devide_Frame_Task_FSM.length-2] << 7) +
                          g_Devide_Frame_Task_FSM.data[g_Devide_Frame_Task_FSM.length-1];
                    sum = BCC_Checksum(g_Devide_Frame_Task_FSM.data, seed, g_Devide_Frame_Task_FSM.length - 2);
                    if (0 == sum)
                    {
                        g_Devide_Frame_Task_FSM.status = SEND_STATE;
                    }
                    else
                    {

                        g_Devide_Frame_Task_FSM.sum = 0;
                        g_Devide_Frame_Task_FSM.length = 0;
                        g_Devide_Frame_Task_FSM.status = WAITING_STATE;
                    }
                }
                else
                {
                    g_Devide_Frame_Task_FSM.data[g_Devide_Frame_Task_FSM.length] = tmp;
                    g_Devide_Frame_Task_FSM.length++;
                }

                break;
            }
            case SEND_STATE:
            {
                Devide_Frame_MessageQ_info *MQInfo = NULL;

                MQInfo = (Devide_Frame_MessageQ_info *)pvPortMalloc(sizeof(Devide_Frame_MessageQ_info));

                MQInfo->len = g_Devide_Frame_Task_FSM.length - 2;
                MQInfo->data = (uint8_t *)pvPortMalloc((size_t)MQInfo->len);
                memcpy(MQInfo->data, g_Devide_Frame_Task_FSM.data, MQInfo->len);

                osMessagePut(Uplink_MessageHandle, (uint32_t)MQInfo, osWaitForever);

                g_Devide_Frame_Task_FSM.sum = 0;
                g_Devide_Frame_Task_FSM.length = 0;
                g_Devide_Frame_Task_FSM.status = WAITING_STATE;

                break;
            }
            case DROP_STATE:
            {
                do
                {
                    Fifo_Out(&g_Uart3_DevideFrame_Fifo, &tmp, 1);
                    if(UPLINK_FRAME_HEADER == tmp)  //如果检测到上行帧头
                    {

                        g_Devide_Frame_Task_FSM.status = RECEIVE_STATE;
                        break;
                    }
                    else if(UPLINK_FRAME_TAIL == tmp)
                    {
                        g_Devide_Frame_Task_FSM.sum = 0;
                        g_Devide_Frame_Task_FSM.length = 0;
                        g_Devide_Frame_Task_FSM.status = WAITING_STATE;
                    }

                }
                while(1);
                break;
            }
            default:
            {
                break;
            }
        }

        osDelay(10);

  }
  /* USER CODE END TASK_Devide_Frame */
}

/* USER CODE BEGIN Header_TASK_Decode */
/**
* @brief Function implementing the TASK_6 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Decode */
void TASK_Decode(void const * argument)
{
  /* USER CODE BEGIN TASK_Decode */
  /* Infinite loop */
    for(;;)
    {
        osEvent evt;
        Devide_Frame_MessageQ_info *MQInfo = NULL;
        device_info *p_dev_tmp;

        evt = osMessageGet(Uplink_MessageHandle, osWaitForever);
        MQInfo = (Devide_Frame_MessageQ_info *)evt.value.p;


        switch (MQInfo->data[1])
        {
            /* dev */
            case 1:
            {
                break;
            }
            /* sts */
            case 2:
            {
                Uplink_Frame_value_info info;

                p_dev_tmp = (device_info *)pvPortMalloc(sizeof(device_info));

                p_dev_tmp->cid = MQInfo->data[0];

                Convert_Uplink_Frame_value_info(&MQInfo->data[2], &info);
                p_dev_tmp->spd = info.fdata;

                Convert_Uplink_Frame_value_info(&MQInfo->data[7], &info);
                p_dev_tmp->pos = info.idata;

                Convert_Uplink_Frame_value_info(&MQInfo->data[12], &info);
                p_dev_tmp->status = info.udata;

                /* 发送报文结构体地址到执行线程 */
                osMessagePut(UpLink_StructureHandle, (uint32_t)p_dev_tmp, osWaitForever);

                break;
            }
            default:
            {
                break;
            }
        }

        vPortFree(MQInfo->data);
        MQInfo->data = NULL;

        vPortFree(MQInfo);
        MQInfo = NULL;

        osDelay(1);

  }
  /* USER CODE END TASK_Decode */
}

/* USER CODE BEGIN Header_TASK_Execute */
/**
* @brief Function implementing the TASK_7 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Execute */
void TASK_Execute(void const * argument)
{
  /* USER CODE BEGIN TASK_Execute */
  /* Infinite loop */
    for(;;)
    {
        osEvent evt;
        device_info dev_tmp;
        osStatus ret;

        evt = osMessageGet(UpLink_StructureHandle, osWaitForever);
        dev_tmp = *(device_info *)evt.value.p;

        osMessagePut(Send_Ack_Handle, (uint32_t)dev_tmp.cid, osWaitForever);
        vPortFree(evt.value.p);
        evt.value.p = NULL;

        osDelay(1);

  }
  /* USER CODE END TASK_Execute */
}

/* USER CODE BEGIN Header_TASK_Debug_Output */
/**
* @brief Function implementing the TASK_8 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Debug_Output */
/**********************************************************************
** 函数名称         :TASK_Debug_Output
** 创建人           :Liu-PC
** 创建日期         :2019年11月11日13:44:21
** 最新修改人       :Liu-PC
** 最近修改日期     :2019年11月11日13:44:27
** 功能描述         :接收其他线程发送过来的调试数据，调试数据通过消息队列在各线程之间传输
** 入口参数         :
												--argument：未被使用
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void TASK_Debug_Output(void const * argument)
{
  /* USER CODE BEGIN TASK_Debug_Output */
  osEvent event_0;
  MessageQ_info *msg_buf;


  /* Infinite loop */
  for(;;)
  {
        event_0 = osMessageGet(Debug_Message_Handle, 10);
        if(event_0.status == osEventMessage)
        {
            msg_buf = (MessageQ_info *)event_0.value.p;
            DEV_Ioctl(DEVICE_ONE, CMD_SEND_DAT_TO_PORT, msg_buf->data,msg_buf->length);

            //释放为打印调试信息 申请的buffer
            MessageQ_info_Free(&msg_buf);
        }


        osDelay(10);

  }
  /* USER CODE END TASK_Debug_Output */
}

/* USER CODE BEGIN Header_TASK_Ui */
/**
* @brief Function implementing the TASK_9 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_Ui */
void TASK_Ui(void const * argument)
{
    /* USER CODE BEGIN TASK_Ui */

    /* Infinite loop */
    for(;;)
    {
        KeyScanMain();
        LcdUpdateMain();

        osDelay(10);

    }
    /* USER CODE END TASK_Ui */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
