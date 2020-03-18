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
** 函数名称         :DEV_Open
** 创建人           :liupengcheng
** 创建日期         :2018-3-22
** 最新修改人       :liupengcheng
** 最近修改日期      :2018-3-22
** 功能描述         :注册设备
** 入口参数         :
                        file：待初始化设备设备号
** 返回参数         :
                        none
** 备注/注意        :
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
** 函数名称         :DEV_Close
** 创建人           :liupengcheng
** 创建日期         :2018-5-11
** 最新修改人       :liupengcheng
** 最近修改日期     :2018-5-11
** 功能描述         :调用该函数可以实现如：
											给板载IC断电，关闭MCU内部对应时钟以及复位外设初始化等复位功能
** 入口参数         :
--device_num:设备号
** 返回参数         :
--函数运行状态
** 备注/注意        :
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
** 函数名称         :DEV_Read
** 创建人           :liupengcheng
** 创建日期         :2018-5-11
** 最新修改人       :liupengcheng
** 最近修改日期     :2018-5-11
** 功能描述         :调用该函数可以对字符型设备进行读操作
** 入口参数         :
					--device_num:设备号
					--ptr：读出数据存储到sram的首地址
					--len：读出数据字节数
					--address:从字符型设备address地址开始读取数据
** 返回参数         :
--函数运行状态
** 备注/注意        :
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
** 函数名称         :DEV_Write
** 创建人           :liupengcheng
** 创建日期         :2018-5-11
** 最新修改人       :liupengcheng
** 最近修改日期     :2018-5-11
** 功能描述         :调用该函数可以对字符型设备进行写操作
** 入口参数         :
					--device_num:设备号
					--ptr：待写数据存储在sram的首地址
					--len：写入数据字节数
					--address:  从字符型设备address地址开始写入数据
** 返回参数         :
** 备注/注意        :
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
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2019年5月26日23:44:35
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
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
** 函数名称         :DEV_Lseek
** 创建人           :liupengcheng
** 创建日期         :2018-5-11
** 最新修改人       :liupengcheng
** 最近修改日期     :2018-5-11
** 功能描述         :移动字符型设备当前光标位置
** 入口参数         :
--device_num:设备号
--ptr:光标移动个数
--dir：光标移动方向
** 返回参数         :
** 备注/注意        :
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
** 函数名称         :DEV_ioctl
** 创建人           :liupengcheng
** 创建日期         :2018-5-11
** 最新修改人       :liupengcheng
** 最近修改日期     :2018-5-11
** 功能描述         :该函数实现了对设备进行的输入输出流的操作
** 入口参数         :
--device_num：操作设备号
--cmd：控制指令
--...多参
** 返回参数         :函数运行装填
** 备注/注意        :
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







