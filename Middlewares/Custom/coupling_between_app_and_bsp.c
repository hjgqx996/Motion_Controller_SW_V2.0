//*********************************************************************
//
//           ��Ȩ���� (C), 2008-2028, �ܲ��Ƽ�������
//             -----------------------------------------------
//
//  �ļ�����:   liu-PC
//  ��������:
//  ��������:
//  �޸���ʷ:
//  (1)   �޸�����:
//  (2)   �޸�����:Liu-PC
//  (3)   �޸�����:
//  [4]   ΢��:lpc17707020887    LiuPC
//*********************************************************************
#include "coupling_between_app_and_bsp.h"




struct device *device_list[DEVICE_SUM]=
{
	 ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+DEVICE_ZERO  * sizeof(struct device))),
	 ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+DEVICE_ONE   * sizeof(struct device))),
     ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+DEVICE_TWO   * sizeof(struct device))),
     ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+DEVICE_THREE * sizeof(struct device))),
     ((struct device *)(DEVICE_CTRL_FIRST_ADDRESS+DEVICE_FOUR  * sizeof(struct device))),
};



/**********************************************************************
** ��������         :DEV_Open
** ������           :liupengcheng
** ��������         :2018-3-22
** �����޸���       :liupengcheng
** ����޸�����      :2018-3-22
** ��������         :ע���豸
** ��ڲ���         :
                        file������ʼ���豸�豸��
** ���ز���         :
                        none
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Open(int device_num)
{
    if (device_list[device_num]->opt.open == NULL|| \
		device_list[device_num]->id != device_num)
    {
			return DEV_FAIL;
    }
    device_list[device_num]->opt.open();
    return DEV_OK;
}

/**********************************************************************
** ��������         :DEV_Close
** ������           :liupengcheng
** ��������         :2018-5-11
** �����޸���       :liupengcheng
** ����޸�����     :2018-5-11
** ��������         :���øú�������ʵ���磺
											������IC�ϵ磬�ر�MCU�ڲ���Ӧʱ���Լ���λ�����ʼ���ȸ�λ����
** ��ڲ���         :
--device_num:�豸��
** ���ز���         :
--��������״̬
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Close(int device_num)
{
    if (device_list[device_num]->opt.close==NULL||device_list[device_num]->id!=device_num)
    {
			return DEV_FAIL;
    }
    device_list[device_num]->opt.close();
    return DEV_OK;
}

/**********************************************************************
** ��������         :DEV_Read
** ������           :liupengcheng
** ��������         :2018-5-11
** �����޸���       :liupengcheng
** ����޸�����     :2018-5-11
** ��������         :���øú������Զ��ַ����豸���ж�����
** ��ڲ���         :
					--device_num:�豸��
					--ptr���������ݴ洢��sram���׵�ַ
					--len�����������ֽ���
					--address:���ַ����豸address��ַ��ʼ��ȡ����
** ���ز���         :
--��������״̬
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Read(int device_num, char *ptr, int len,uint8_t* destination_add)
{
    Dev_Run_Resul_Enum ret = DEV_FAIL;

    if (device_list[device_num]->opt.read==NULL||device_list[device_num]->id!=device_num)
    {
			return DEV_FAIL;
    }
    ret = device_list[device_num]->opt.read(ptr, len, destination_add);

    return ret;
}


/**********************************************************************
** ��������         :DEV_Write
** ������           :liupengcheng
** ��������         :2018-5-11
** �����޸���       :liupengcheng
** ����޸�����     :2018-5-11
** ��������         :���øú������Զ��ַ����豸����д����
** ��ڲ���         :
					--device_num:�豸��
					--ptr����д���ݴ洢��sram���׵�ַ
					--len��д�������ֽ���
					--address:  ���ַ����豸address��ַ��ʼд������
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Write(int device_num, char *ptr, int len,uint8_t* destination_add)
{
    Dev_Run_Resul_Enum ret = DEV_FAIL;

    if (device_list[device_num]->opt.read==NULL||device_list[device_num]->id!=device_num)
    {
			return DEV_FAIL;
    }
    ret = device_list[device_num]->opt.write(ptr, len,destination_add);

    return ret;
}


#if 0
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :2019��5��26��23:44:35
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
caddr_t _sbrk(int incr)
{
    extern char *end;
    extern char *_Main_Stack_Limit;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == NULL)
        heap_end = end;

    prev_heap_end = heap_end;

    if (heap_end + incr > _Main_Stack_Limit)
    {
			errno = ENOMEM;
			return (caddr_t)-1;
    }

    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

#endif



/**********************************************************************
** ��������         :DEV_Lseek
** ������           :liupengcheng
** ��������         :2018-5-11
** �����޸���       :liupengcheng
** ����޸�����     :2018-5-11
** ��������         :�ƶ��ַ����豸��ǰ���λ��
** ��ڲ���         :
--device_num:�豸��
--ptr:����ƶ�����
--dir������ƶ�����
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Lseek(int device_num, int ptr, int dir)
{
    if (device_list[device_num]->opt.lseek==NULL||device_list[device_num]->id!=device_num)
    {
			return DEV_FAIL;
    }
    device_list[device_num]->opt.lseek(ptr, dir);
    return DEV_OK;
}



/**********************************************************************
** ��������         :DEV_ioctl
** ������           :liupengcheng
** ��������         :2018-5-11
** �����޸���       :liupengcheng
** ����޸�����     :2018-5-11
** ��������         :�ú���ʵ���˶��豸���е�����������Ĳ���
** ��ڲ���         :
--device_num�������豸��
--cmd������ָ��
--...���
** ���ز���         :��������װ��
** ��ע/ע��        :
** QQ               : 1240612852
***********************************************************************/
Dev_Run_Resul_Enum DEV_Ioctl(int device_num, int cmd, ...)
{
    va_list args;

    Dev_Run_Resul_Enum res = DEV_FAIL;

	va_start(args,cmd);

        if (device_num != device_list[device_num]->id||device_list[device_num]->opt.ioctl==NULL)
        {
                return DEV_FAIL;
        }


        res = device_list[device_num]->opt.ioctl(cmd ,&args);

    va_end(args);
    return res;
}


//(void**)(first_para_ptr+4)[-1]







