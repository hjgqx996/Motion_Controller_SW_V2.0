//*********************************************************************
//
//           ��Ȩ���� (C), 2008-2028, ���ﻥ���Ļ��������޹�˾
//             -----------------------------------------------
//
//  �ļ�����:   liu-PC
//  ��������:   
//  ��������:   ���ļ���Ҫ�洢Ӳ��������ӿڵĲ��Դ���
//  �޸���ʷ:  
//  (1)   �޸�����:2020��1��11��11:13:45
//  (2)   �޸�����:Liu-PC
//  (3)   �޸�����:
//  [4]   ΢��:lpc17707020887    LiuPC
//*********************************************************************

#include "drive_port_test.h"




/**********************************************************************
** ��������         :Fill_Buffer
** ������           :LiuPC
** ��������         :2020��1��11��11:17:17
** �����޸���       :LiuPC
** ����޸�����     :2020��1��11��11:17:24
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :Print_Buffer
** ������           :LiuPC
** ��������         :2020��1��11��11:17:17
** �����޸���       :LiuPC
** ����޸�����     :2020��1��11��11:17:24
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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
** ��������         :Sdcard_Test
** ������           :LiuPC
** ��������         :2020��1��11��11:17:17
** �����޸���       :LiuPC
** ����޸�����     :2020��1��11��11:17:24
** ��������         :����SD���������ӿ�
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :lpc17707020887    LiuPC
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

    /* ��һ�ζ� */
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
    /* �������� */
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

    /* �������ȡ��ӡ */
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

    /* д�� */
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

    /* д����ȡ */
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

