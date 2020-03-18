#ifndef __DEVICE_H
#define __DEVICE_H

//1、头文件
/********************************************************************************************************************************************************************/
#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"





//2、类型定义
/********************************************************************************************************************************************************************/
//设备open/close/read/write/lseek/ioctl 函数运行状态结果枚举
typedef enum
{
    DEV_FAIL = 0,           //运行错误
    DEV_OK ,         		//运行成功
	DEV_SEND_TIMES_OVER,    //发送超时
	DEV_SEND_SUCCESS,		//发送成功

} Dev_Run_Resul_Enum;


#pragma pack(push)
#pragma pack(1)

struct devopt
{
    Dev_Run_Resul_Enum (*open)(void);
    Dev_Run_Resul_Enum (*close)(void);
    Dev_Run_Resul_Enum (*read)(char *buf, int len, uint8_t* destination_add);
    Dev_Run_Resul_Enum (*write)(char *buf, int len, uint8_t* destination_add);
    Dev_Run_Resul_Enum (*lseek)(int ptr, int dir);
    Dev_Run_Resul_Enum (*ioctl)(int cmd, va_list* args_temp);
};

struct device
{
    int id;
    struct devopt opt;
};


#pragma pack(pop)


//*****************0号设备：相关的IO_Ctrl 指令枚举***************/
typedef enum
{
	CMD_CLEAR_SCREEN = 0,          //清屏指令
	CMD_DISPLAY_FULL_IMAGE,    //绘制全屏照片指令
	CMD_DISPLAY_ICON_32x32,    //绘制32*32小图标指令
	CMD_DISPLAY_ICON_16x16,    //绘制16*16小图标指令
	CMD_DISPLAY_ICON_8x16,     //绘制8*16小图标指令
	CMD_DISPLAY_STRING_8x16,   //绘制8*16小图标指令
	CMD_DISPALY_STRING_5x7,    //绘制5*7小图标指令
}Lcd_Ctl_Cmd_Typedef;

//*****************1号设备：相关的IO_Ctrl 指令枚举***************/
typedef enum
{
	CMD_CODE_DAT_2_BUF = 0,          //将当前数据全部输出到buffer里去
    CMD_SEND_DAT_TO_PORT,            //将buffer里面的数据输出到对应端口，如usart
}Debug_Ctl_Cmd_Typedef;


//*****************2号设备：相关的IO_Ctrl 指令枚举***************/
typedef enum
{
    CMD_SEND_Or_RECEIVE = 0,          //控制RS48数据流向的指令
}Rs485_Ctl_Cmd_Typedef;


typedef enum
{
    Direction_Input = 0,     //设置RS485输出状态
    Direction_Output,        //设置RS485输入状态
}Rs485_Flow_Direction_Typedef;
//*****************3号设备：相关的IO_Ctrl 指令枚举***************/

//*****************4号设备：相关的IO_Ctrl 指令枚举***************/
typedef enum
{
    CMD_ERASE_SECTOR,
    CMD_GET_SDCARD_INFO,
    CMD_INVALID
}SDCard_Ctl_Cmd_Typedef;


//3、宏定义
/********************************************************************************************************************************************************************/
#define DEVICE_SUM      5      //这里指可以最多可以注册4个外围设备


#define DEVICE_ZERO     0      //DEVICE_DEFINE(LCD12864_0, DEVICE_ZERO)
#define DEVICE_ONE      1      //DEVICE_DEFINE(DEBUG_0, DEVICE_ONE)
#define DEVICE_TWO      2      //DEVICE_DEFINE(RS485_0, DEVICE_TWO)
#define DEVICE_THREE    3      //DEVICE_DEFINE(KEY, DEVICE_THREE)
#define DEVICE_FOUR     4      //DEVICE_DEFINE(SDCARD, DEVICE_FOUR)



//温馨提示： 选用了不同的芯片，这个地址必需改变哟，预留15（15个板载设备）*28B（每个板载设备占用空间）=0x1A4
//因为stm32f030f4p6的flash顶部地址是0x08004000，所以0x08080000-0x1A4 = 0x807FE5C
#define DEVICE_CTRL_FIRST_ADDRESS 0x08001000

#define DEVICE_DEFINE(DEV, ID)                                                                             				   \
    static Dev_Run_Resul_Enum DEV##_Open(void);                                                                            \
    static Dev_Run_Resul_Enum DEV##_Close(void);                                                                           \
    static Dev_Run_Resul_Enum DEV##_Write(char *buf, int len, uint8_t* destination_add);                                          \
    static Dev_Run_Resul_Enum DEV##_Read(char *buf, int len, uint8_t* destination_add);                                           \
    static Dev_Run_Resul_Enum DEV##_Lseek(int ptr, int dir);                                                              \
    static Dev_Run_Resul_Enum DEV##_Ioctl(int cmd, va_list* args_temp);                                                    	\
    static struct device DEV __attribute__((at(DEVICE_CTRL_FIRST_ADDRESS + ID * sizeof(struct device)))) =						                  	\
    {                                                                                                  						\
            .id = ID,                                                                                      					\
            .opt.open = &DEV##_Open,                                                                        				\
            .opt.close = DEV##_Close,                                                                      					\
            .opt.read = DEV##_Read,                                                                        					\
            .opt.write = DEV##_Write,                                                                      					\
            .opt.lseek = DEV##_Lseek,                                                                      					\
            .opt.ioctl = DEV##_Ioctl,                                                                      					\
    };




#define DEVICE_FUNC_DEFINE_OPEN(DEV) \
static Dev_Run_Resul_Enum DEV##_Open(void)

#define DEVICE_FUNC_DEFINE_CLOSE(DEV) \
static Dev_Run_Resul_Enum DEV##_Close(void)

#define DEVICE_FUNC_DEFINE_WRITE(DEV) \
static Dev_Run_Resul_Enum DEV##_Write(char *buf, int len, uint8_t* destination_add)

#define DEVICE_FUNC_DEFINE_READ(DEV) \
static Dev_Run_Resul_Enum DEV##_Read(char *buf, int len, uint8_t* destination_add)

#define DEVICE_FUNC_DEFINE_LSEEK(DEV) \
static Dev_Run_Resul_Enum DEV##_Lseek(int ptr, int dir)

#define DEVICE_FUNC_DEFINE_IOCTL(DEV) \
static Dev_Run_Resul_Enum DEV##_Ioctl(int cmd, va_list* args_temp)




//4、变量声明
/********************************************************************************************************************************************************************/
extern struct device *device_list[];



//5、函数声明
/********************************************************************************************************************************************************************/
extern Dev_Run_Resul_Enum DEV_Open(int device_num);
extern Dev_Run_Resul_Enum DEV_Close(int device_num);
extern Dev_Run_Resul_Enum DEV_Read(int device_num, char *ptr, int len,uint8_t* destination_add);
extern Dev_Run_Resul_Enum DEV_Write(int device_num, char *ptr, int len,uint8_t* destination_add);
extern Dev_Run_Resul_Enum DEV_Lseek(int device_num, int ptr, int dir);
extern Dev_Run_Resul_Enum DEV_Ioctl(int device_num, int cmd, ...);


#endif

// static int DEV_Open(struct inode *inode, struct file *file)
// static ssize_t DEV_Read(struct file *file, char __user *buf, size_t count, loff_t *pos)
// static ssize_t DEV_Write(struct file *file, char __user *buf, size_t count, loff_t *pos)
// static loff_t DEV_Lseek(struct file *file, loff_t offset, int dir)
// static long DEV_Ioctl(struct file *file, unsigned int cmd, unsigned long *arg)
// static int DEV_Close(struct inode *inode, struct file *file)
