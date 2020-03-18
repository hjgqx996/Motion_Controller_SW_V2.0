/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdint.h>
#include "fifo.h"
#include "Global.h"
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
        Error_Handler();
  }

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
        Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
      /* USER CODE BEGIN USART1_MspInit 0 */

      /* USER CODE END USART1_MspInit 0 */
        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = DEBUG_Tx_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(DEBUG_Tx_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = DEBUG_Rx_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(DEBUG_Rx_GPIO_Port, &GPIO_InitStruct);

      /* USER CODE BEGIN USART1_MspInit 1 */

      /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
      /* USER CODE BEGIN USART3_MspInit 0 */

      /* USER CODE END USART3_MspInit 0 */
        /* USART3 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**USART3 GPIO Configuration
        PB10     ------> USART3_TX
        PB11     ------> USART3_RX
        */
        GPIO_InitStruct.Pin = RS485_Tx_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(RS485_Tx_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = RS485_Rx_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(RS485_Rx_GPIO_Port, &GPIO_InitStruct);

      /* USER CODE BEGIN USART3_MspInit 1 */
        HAL_NVIC_SetPriority(USART3_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
      /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, DEBUG_Tx_Pin|DEBUG_Rx_Pin);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, RS485_Tx_Pin|RS485_Rx_Pin);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

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
int USART1_Putchar(uint8_t c)
{
    uint8_t temp[1]={c};

    HAL_UART_Transmit(&huart1,temp,1,2);

    return 0 ;
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
int USART1_Puts(const uint8_t *s)
{
	while (*s)
	{
            USART1_Putchar(*s);
            s++;
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
int USART3_Putchar(uint8_t c)
{
    uint8_t temp[1]={c};

    HAL_UART_Transmit(&huart3, temp, 1, 2);

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
int USART3_Puts(const uint8_t *s)
{
	while (*s)
	{
		USART3_Putchar(*s);
		s++;
	}

    return 0;
}

/**********************************************************************
** 函数名称         :
** 创建人           :
** 创建日期         :
** 最新修改人        :
** 最近修改日期       :
** 功能描述         :开启UART3中断，把接收到的数据放入FIFO，每次接收1字节
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void Open_UART3_Receive_IT(void)
{
    uint8_t *fifoin = NULL;
    fifoin = Fifo_Get_Inhandle(&g_Uart3_DevideFrame_Fifo);
    HAL_UART_Receive_IT(&huart3, fifoin, HAL_UART_RX_SIZE);
}

/**********************************************************************
** 函数名称         :Handle_UART3_IT
** 创建人          :
** 创建日期         :
** 最新修改人        :
** 最近修改日期       :
** 功能描述         :检测到帧尾标志就通知分帧线程。
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void Handle_UART3_IT(void)
{
    uint8_t tmp;

    /* 串口中断中写入了HAL_UART_RX_SIZE大小的数据 */
    g_Uart3_DevideFrame_Fifo.in += HAL_UART_RX_SIZE;

    /* 如果是报文帧尾标志就在发送一个信号量令牌 */
    tmp = Fifo_Get_Last_In_Data(&g_Uart3_DevideFrame_Fifo);
    if (UPLINK_FRAME_TAIL == tmp)
    {
        osSemaphoreRelease(Uart3_DevideFrame_SemHandle);
    }

    Open_UART3_Receive_IT();
}






/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
