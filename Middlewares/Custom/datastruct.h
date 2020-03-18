#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

//1、头文件
/********************************************************************************************************************************************************************/
#include "stdio.h"
#include "string.h"

//#include "ugui.h"
#include "stm32f1xx_hal.h"

//2、宏定义
/********************************************************************************************************************************************************************/
#define TOTAL_NUM_OF_COLUMN  4    //机械动态矩阵的总列数
#define TOTAL_NUM_OF_ROW  3       //机械动态矩阵的总行数

#define TOTAL_NUM_OF_CMD  12            //下行报文 指令类型的总数
#define TOTAL_NUM_OF_PARA_TYPE    29    //下行报文 参数类型的总数

#define UPLINK_FRAME_HEADER                     (0xff)      //上行报文起始标志
#define UPLINK_FRAME_TAIL                       (0xfe)      //上行报文结束标志
#define UART3_FIFOBUF_LENGTH                    (64)        //循环buffer空间大小
#define DEVIDE_FRAME_TASK_FSM_BUF_LENGTH        (64)        //分帧线程状态机数据缓存



//这是供drive_port_test.c文件使用的宏
#define BLOCK_SIZE      512         //SD卡块大小
#define WRITE_READ_ADDRESS    0x00000000
#define NUMBER_OF_BLOCKS 1


//3、类型定义
/********************************************************************************************************************************************************************/
/**************************************************类型定义：下行报文相关数据结构定义*****************************************/
#pragma pack(push)
#pragma pack(1)


//下行报文’参数类型‘枚举
typedef enum
{
    Para_bdr      = 0,  //设置波特率，重启生效
    Para_cid,     //设置设备ID，重启生效
    Para_mcs,        //设置微步细分
    Para_spd,        //设置速度
    Para_acc,        //设置加速度
    Para_dec,        //设置减速度
    Para_cra,        //设置加速时电流
    Para_crn,        //设置运行时电流
    Para_crh,        //设置保持时电流
    Para_s1f,        //设置S1下降沿触发事件
    Para_s1r,        //设置S1上升沿触发事件
    Para_s2f,        //设置S2下降沿触发事件
    Para_s2r,        //设置S2上升沿触发事件
    Para_s3f,        //设置S3下降沿触发事件
    Para_s3r,        //设置S3上升沿触发事件
    Para_zmd,        //设置归零功能（ON/OFF）
    Para_snr,        //设置归零用传感器
    Para_osv,        //设置归零传感器OPEN时电平
    Para_zsd,        //设置归零速度（正负代表方向）
    Para_zsp,        //设置归零后的安全位置
    Para_dmd,        //设置离线运行模式
    Para_dar,        //设置无握手启动时间
    Para_pas,        //S3模式设置
    Para_res,        //外界电位器大小（欧姆）
    Para_value,      //移动到指定位置
    Para_start,      //执行归零  eg: zero start\n   or   启动离线运行 eg: demo start\n
    Para_stop,       //停止归零  eg: zero stop\n    or   停止离线运行 eg: demo stop\n
    Para_add,        //添加节点
    Para_clear,      //清除所有节点
}Para_type_typedef;


//在CALCULATE_Total_Length_Of_Downlink_Message函数里面，
//需要实现‘参数类型’在枚举和字符串之间的转换，
//所以我们定义一个结构体类型，用来定义枚举和字符串对照表
typedef struct
{
    Para_type_typedef e_Para_Type;       //“参数类型”的枚举形式
    char s_Para_Type[5];                //”参数类型“ 的字符串形式
}Para_Type_form_typedef;

//下行报文指令枚举
typedef enum
{
    Cmd_dev=0,       //握手，获取电机驱动器的型号和版本号
    Cmd_sts,         //获取运行状态（速度、位置、状态）
    Cmd_cfg,         //获取参数值
    Cmd_ena,         //电机使能
    Cmd_off,         //电机脱机
    Cmd_mov,         //以指定速度连续运转
    Cmd_pos,         //移动到指定位置
    Cmd_org,         //指定当前位置为原点
    Cmd_stp,         //停止
    Cmd_zero,        //执行归零
    Cmd_sav,         //参数保存到FLASH
    Cmd_demo,        //获取离线运行节点

}Cmd_Typedef;

//在CALCULATE_Total_Length_Of_Downlink_Message函数里面，
//需要实现‘指令’在枚举和字符串之间的转换，
//所以我们定义一个结构体类型，用来定义枚举和字符串对照表
typedef struct
{
    Cmd_Typedef e_Cmd;
    char s_Cmd[5];
}Cmd_form_typedef;



//下行报文参数结构体
typedef struct
{
    Para_type_typedef e_Para_Type;      // 参数类型 eg:bdr/cid/mcs/spd/...
    union
    {
        int32_t u_Para_Value;             // 参数值（无符号整形）
        float f_Para_Value;                // 参数值（单精度浮点型整形）
    }Para_Union;
}Para_Struct_Typedef;


//下行报文结构体
typedef struct
{
    uint8_t               RS485_ID;                       //电机驱动器的485_ID号
    Cmd_Typedef           Cmd_Enum;                       //指令
    uint8_t               Total_num_of_Para;              //下行报文中参数的个数
    Para_Struct_Typedef*  Para_Struct[24];                //参数类型及参数值
}DownLink_Struct_Typedef;

//下行报文帧结构体
typedef struct
{
    char * head_ptr;        //下行报文帧头
    uint8_t total_length;   //下行报文帧长度
}Downlink_Frame_typedef;

/*******************************************Triggle_Send_Task 的状态机各状态***************************************************/
typedef enum
{
    Preparing_Animation_Data_Status,            //准备动画数据状态
    Waiting_Count_Down_Status,                  //等倒计时状态
    Waiting_Ack_Status,                         //等回复状态
    Timeout_Resend_Status,                      //超时重传状态
}Status_Of_Triggle_Send_Task_Typedef;                 //Triggle_Send_Task 的状态机各状态

/**********************************************矩阵中单点电机的X、Y、Z坐标******************************************************************/
typedef struct
{
    uint16_t X;        //矩阵中单点电机所处X坐标
    uint16_t Y;        //矩阵中单点电机所处Y坐标
    int32_t Z;         //矩阵中单点电机即将运行到的Z坐标
}Motor_Coordinate_typedef;
/**********************************************电机驱动器在结构中位置的坐标和485ID号的对应关系结构体************************************************************/

typedef struct
{
    uint16_t X;
    uint16_t Y;
    uint8_t RS485_ID;
}Coordinate_and_ID_Typedef;
/********************************************************************************************************************************************************************/

/* 上行报文数据段信息 */
typedef union
{
	float fdata;
	int32_t idata;
	uint32_t udata;
}Uplink_Frame_value_info;

/* 上行报文 */
typedef struct
{
    uint8_t cid;
    uint8_t fbid;
    uint8_t *data;
}Uplink_Frame_Typedef;

/*步进电机状态信息结构体 */
typedef struct
{
    uint8_t cid;        //设备号
    //反馈号
    //长度
    //数据联合体
	float spd;          //速度
	int32_t pos;        //位置
	uint32_t status;    //状态
}device_info;

/* 分帧线程状态 */
typedef enum
{
    WAITING_STATE = 0,       //
    RECEIVE_STATE,       //
    SEND_STATE,          //   
    DROP_STATE,          //非法报文的处理状态

    INVALID_STATE
}Devide_Frame_Task_FSM_Status_Typedef;

/* 分帧线程状态机结构 */
typedef struct
{
    Devide_Frame_Task_FSM_Status_Typedef status;    //状态机状态
    uint32_t length;                                //
    uint8_t  sum;                                   //校验和,初值为0
    uint8_t  *data;                                 //
}Devide_Frame_Task_FSM_Typedef;

/* 分帧线程->解码线程消息队列消息结构 */
typedef struct
{
    uint32_t len;
    uint8_t *data;
}Devide_Frame_MessageQ_info;

/* 通用消息队列结构 */
typedef struct
{
    uint32_t length;
    uint8_t *data;
}MessageQ_info;

#pragma pack(pop)


//4、变量声明
/********************************************************************************************************************************************************************/
extern Status_Of_Triggle_Send_Task_Typedef Status_Of_Triggle_Send_Task;
extern Motor_Coordinate_typedef Motor_Coordinate_Array[2][12];
extern Coordinate_and_ID_Typedef Coordinate_and_ID_Struct[3][4];
extern Para_Type_form_typedef Para_Type_form_Strcut[];
extern Cmd_form_typedef Cmd_form_struct[];

extern uint8_t g_Uart3_DevideFrame_Fifo_Buffer[UART3_FIFOBUF_LENGTH];      //循环缓存 接收上位机发送下来的下行报文
extern struct fifo g_Uart3_DevideFrame_Fifo;

extern uint8_t g_Devide_Frame_Task_FSM_Buf[DEVIDE_FRAME_TASK_FSM_BUF_LENGTH];

extern Devide_Frame_Task_FSM_Typedef g_Devide_Frame_Task_FSM;

//这是供drive_port_test.c文件使用的全局变量
extern char buf_read[NUMBER_OF_BLOCKS * BLOCK_SIZE];
extern char buf_write[NUMBER_OF_BLOCKS * BLOCK_SIZE];

//5、函数声明
/********************************************************************************************************************************************************************/


#endif


















