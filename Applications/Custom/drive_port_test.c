//*********************************************************************
//
//           版权所有 (C), 2008-2028, 格物互动文化传播有限公司
//             -----------------------------------------------
//
//  文件作者:   liu-PC
//  生成日期:   
//  功能描述:   本文件主要存储硬件驱动层接口的测试代码
//  修改历史:  
//  (1)   修改日期:2020年1月11日11:13:45
//  (2)   修改作者:Liu-PC
//  (3)   修改内容:
//  [4]   微信:lpc17707020887    LiuPC
//*********************************************************************

#include "drive_port_test.h"




/**********************************************************************
** 函数名称         :Fill_Buffer
** 创建人           :LiuPC
** 创建日期         :2020年1月11日11:17:17
** 最新修改人       :LiuPC
** 最近修改日期     :2020年1月11日11:17:24
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void Fill_Buffer(char *pBuffer, uint32_t BufferLength, uint8_t dat)
{
  uint32_t index = 0;

  for (index = 0; index < BufferLength; index++ )
  {
    pBuffer[index] = dat++;
  }
}


/**********************************************************************
** 函数名称         :Print_Buffer
** 创建人           :LiuPC
** 创建日期         :2020年1月11日11:17:17
** 最新修改人       :LiuPC
** 最近修改日期     :2020年1月11日11:17:24
** 功能描述         :
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void Print_Buffer(char *pBuffer, uint32_t BufferLength)
{
    uint32_t i, j = 0;
    for (i = 0; i < BufferLength; i++)
    {
        if (16 == j)
        {
            TRACE("\r\n");
            j = 0;
        }
        TRACE("%08X   ", pBuffer[i]);
        j++;
    }
    TRACE("\r\n");
}


/**********************************************************************
** 函数名称         :Sdcard_Test
** 创建人           :LiuPC
** 创建日期         :2020年1月11日11:17:17
** 最新修改人       :LiuPC
** 最近修改日期     :2020年1月11日11:17:24
** 功能描述         :测试SD卡的驱动接口
** 入口参数         :
												--NONE
** 返回参数         :
												--NONE
** 备注/注意        :
** 微信              :lpc17707020887    LiuPC
***********************************************************************/
void Sdcard_Test(void)
{
    Dev_Run_Resul_Enum ret = DEV_FAIL;
    HAL_SD_CardInfoTypeDef CardInfo;

    
    DEV_Ioctl(DEVICE_FOUR,CMD_GET_SDCARD_INFO,&hsd,&CardInfo);
    
    TRACE("card Type                        :%d\r\n", CardInfo.CardType);
    TRACE("card version                     :%d\r\n", CardInfo.CardVersion);
    TRACE("card class                       :%d\r\n", CardInfo.Class);
    TRACE("Relative Card Address            :%d\r\n", CardInfo.RelCardAdd);
    TRACE("Card Capacity in blocks          :%d\r\n", CardInfo.BlockNbr);
    TRACE("one block size in bytes          :%d\r\n", CardInfo.BlockSize);
    TRACE("Card logical Capacity in blocks  :%d\r\n", CardInfo.LogBlockNbr);
    TRACE("logical block size in bytes      :%d\r\n", CardInfo.LogBlockSize);

    /* 第一次读 */
    ret = DEV_Read(DEVICE_FOUR, buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE, WRITE_READ_ADDRESS);
    HAL_Delay(500);
    
    if (DEV_FAIL == ret)
    {
        TRACE("SDCare read failed.\r\n");
    }
    else
    {
        TRACE("SDCare read success.\r\n");
        Print_Buffer(buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE);
    }
#if 1
    /* 擦出数据 */
    ret = DEV_Ioctl(DEVICE_FOUR, CMD_ERASE_SECTOR, &hsd, WRITE_READ_ADDRESS, WRITE_READ_ADDRESS + BLOCK_SIZE * 4);
    HAL_Delay(500);
    
    if (DEV_FAIL == ret)
    {
        TRACE("SDCare erase failed.\r\n");
    }
    else
    {
        TRACE("SDCare erase success.\r\n");
    }

    /* 擦除后读取打印 */
    ret = DEV_Read(DEVICE_FOUR, buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE, WRITE_READ_ADDRESS);
    HAL_Delay(500);
    
    if (DEV_FAIL == ret)
    {
        TRACE("SDCare read failed.\r\n");
    }
    else
    {
        TRACE("SDCare read success.\r\n");
        Print_Buffer(buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE);
    }

    /* 写入 */
    Fill_Buffer(buf_write, NUMBER_OF_BLOCKS * BLOCK_SIZE, 0);
    ret = DEV_Write(DEVICE_FOUR, buf_write, NUMBER_OF_BLOCKS * BLOCK_SIZE, WRITE_READ_ADDRESS);
    HAL_Delay(500);
    
    if (DEV_FAIL == ret)
    {
        TRACE("SDCare write failed.\r\n");
    }
    else
    {
        TRACE("SDCare write success.\r\n");
    }

    /* 写入后读取 */
    ret = DEV_Read(DEVICE_FOUR, buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE, WRITE_READ_ADDRESS);
    HAL_Delay(500);
    
    if (DEV_FAIL == ret)
    {
        TRACE("SDCare read failed.\r\n");
    }
    else
    {
        TRACE("SDCare read success.\r\n");
        Print_Buffer(buf_read, NUMBER_OF_BLOCKS * BLOCK_SIZE);
    }
#endif
}

