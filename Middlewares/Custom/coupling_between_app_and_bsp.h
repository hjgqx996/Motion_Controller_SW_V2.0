#ifndef __DEVICE_H
#define __DEVICE_H

//1��ͷ�ļ�
/********************************************************************************************************************************************************************/
#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"





//2�����Ͷ���
/********************************************************************************************************************************************************************/
//�豸open/close/read/write/lseek/ioctl ��������״̬���ö��
typedef enum
{
    DEV_FAIL = 0,           //���д���
    DEV_OK ,         		//���гɹ�
	DEV_SEND_TIMES_OVER,    //���ͳ�ʱ
	DEV_SEND_SUCCESS,		//���ͳɹ�

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


//*****************0���豸����ص�IO_Ctrl ָ��ö��***************/
typedef enum
{
	CMD_CLEAR_SCREEN = 0,          //����ָ��
	CMD_DISPLAY_FULL_IMAGE,    //����ȫ����Ƭָ��
	CMD_DISPLAY_ICON_32x32,    //����32*32Сͼ��ָ��
	CMD_DISPLAY_ICON_16x16,    //����16*16Сͼ��ָ��
	CMD_DISPLAY_ICON_8x16,     //����8*16Сͼ��ָ��
	CMD_DISPLAY_STRING_8x16,   //����8*16Сͼ��ָ��
	CMD_DISPALY_STRING_5x7,    //����5*7Сͼ��ָ��
}Lcd_Ctl_Cmd_Typedef;

//*****************1���豸����ص�IO_Ctrl ָ��ö��***************/
typedef enum
{
	CMD_CODE_DAT_2_BUF = 0,          //����ǰ����ȫ�������buffer��ȥ
    CMD_SEND_DAT_TO_PORT,            //��buffer����������������Ӧ�˿ڣ���usart
}Debug_Ctl_Cmd_Typedef;


//*****************2���豸����ص�IO_Ctrl ָ��ö��***************/
typedef enum
{
    CMD_SEND_Or_RECEIVE = 0,          //����RS48���������ָ��
}Rs485_Ctl_Cmd_Typedef;


typedef enum
{
    Direction_Input = 0,     //����RS485���״̬
    Direction_Output,        //����RS485����״̬
}Rs485_Flow_Direction_Typedef;
//*****************3���豸����ص�IO_Ctrl ָ��ö��***************/

//*****************4���豸����ص�IO_Ctrl ָ��ö��***************/
typedef enum
{
    CMD_ERASE_SECTOR,
    CMD_GET_SDCARD_INFO,
    CMD_INVALID
}SDCard_Ctl_Cmd_Typedef;


//3���궨��
/********************************************************************************************************************************************************************/
#define DEVICE_SUM      5      //����ָ����������ע��4����Χ�豸


#define DEVICE_ZERO     0      //DEVICE_DEFINE(LCD12864_0, DEVICE_ZERO)
#define DEVICE_ONE      1      //DEVICE_DEFINE(DEBUG_0, DEVICE_ONE)
#define DEVICE_TWO      2      //DEVICE_DEFINE(RS485_0, DEVICE_TWO)
#define DEVICE_THREE    3      //DEVICE_DEFINE(KEY, DEVICE_THREE)
#define DEVICE_FOUR     4      //DEVICE_DEFINE(SDCARD, DEVICE_FOUR)



//��ܰ��ʾ�� ѡ���˲�ͬ��оƬ�������ַ����ı�Ӵ��Ԥ��15��15�������豸��*28B��ÿ�������豸ռ�ÿռ䣩=0x1A4
//��Ϊstm32f030f4p6��flash������ַ��0x08004000������0x08080000-0x1A4 = 0x807FE5C
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




//4����������
/********************************************************************************************************************************************************************/
extern struct device *device_list[];



//5����������
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
