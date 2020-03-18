
#include "SDCard.h"

DEVICE_DEFINE(SDCARD, DEVICE_FOUR)



/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_OPEN(SDCARD)
{
	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_CLOSE(SDCARD)
{
	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_WRITE(SDCARD)
{
    uint8_t *pData = (uint8_t *)buf;
    uint32_t BlockAdd = (uint32_t)destination_add;
    uint32_t NumberOfBlocks = len/512;
    HAL_StatusTypeDef ret;

    if (len%512 != 0 && BlockAdd%512 != 0)
    {
        return DEV_FAIL;
    }

    /* 设置DMA通道方向 */
    /* SDIO DeInit */
    if (HAL_DMA_DeInit(&hdma_sdio) != HAL_OK)
    {
      Error_Handler();
    }
    /* SDIO Init */
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
    {
      Error_Handler();
    }

    ret = HAL_SD_WriteBlocks_DMA(&hsd, pData, BlockAdd, NumberOfBlocks);
    if (HAL_OK != ret)
    {
        return DEV_FAIL;
    }

	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_READ(SDCARD)
{
    uint8_t *pData = (uint8_t* )buf;
    uint32_t BlockAdd = (uint32_t)destination_add;
    uint32_t NumberOfBlocks = len/512;
    HAL_StatusTypeDef ret;

    if (len%512 != 0 && BlockAdd%512 != 0)
    {
        return DEV_FAIL;
    }

    /* 设置DMA通道方向 */
    /* SDIO DeInit */
    if (HAL_DMA_DeInit(&hdma_sdio) != HAL_OK)
    {
        Error_Handler();
    }
    /* SDIO Init */
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
    {
      Error_Handler();
    }

    ret = HAL_SD_ReadBlocks_DMA(&hsd, pData, BlockAdd, NumberOfBlocks);
    if (HAL_OK != ret)
    {
        return DEV_FAIL;
    }

	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_LSEEK(SDCARD)
{
	return DEV_OK;
}

/**********************************************************************
** 函数名称         :
** 创建人           :lihai
** 创建日期         :2019年12月24日 14:24:29
** 最新修改人       :
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :
***********************************************************************/
DEVICE_FUNC_DEFINE_IOCTL(SDCARD)
{
    Dev_Run_Resul_Enum ret = DEV_FAIL;

    switch ((SDCard_Ctl_Cmd_Typedef)cmd)
    {
            case CMD_ERASE_SECTOR:
            {
                uint32_t BlockStartAdd;
                uint32_t BlockEndAdd;
                HAL_StatusTypeDef stat;
                SD_HandleTypeDef *phsd;

                phsd          = va_arg(*args_temp, SD_HandleTypeDef *);
                BlockStartAdd = va_arg(*args_temp, uint32_t);
                BlockEndAdd   = va_arg(*args_temp, uint32_t);

                stat = HAL_SD_Erase(phsd, BlockStartAdd, BlockEndAdd);
                if (HAL_OK == stat)
                {
                    ret = DEV_OK;
                }

                break;
            }
            case CMD_GET_SDCARD_INFO:       //具体调用举例：DEV_Ioctl(DEVICE_FOUR,CMD_GET_SDCARD_INFO,&hsd,&CardInfo);
            {
                 SD_HandleTypeDef* p_hsd_temp;
                 HAL_SD_CardInfoTypeDef* p_CardInfo_temp;
                
                 p_hsd_temp          = va_arg(*args_temp, SD_HandleTypeDef *);
                 p_CardInfo_temp =va_arg(*args_temp,HAL_SD_CardInfoTypeDef*);   
                
                 HAL_SD_GetCardInfo(p_hsd_temp, p_CardInfo_temp);
                
                 break;
            }
            default:
            {
                
                break;
            }
    }

	return ret;
}
