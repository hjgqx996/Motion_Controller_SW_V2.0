#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

//1��ͷ�ļ�
/********************************************************************************************************************************************************************/
#include "stdio.h"
#include "string.h"

//#include "ugui.h"
#include "stm32f1xx_hal.h"

//2���궨��
/********************************************************************************************************************************************************************/
#define TOTAL_NUM_OF_COLUMN  4    //��е��̬�����������
#define TOTAL_NUM_OF_ROW  3       //��е��̬�����������

#define TOTAL_NUM_OF_CMD  12            //���б��� ָ�����͵�����
#define TOTAL_NUM_OF_PARA_TYPE    29    //���б��� �������͵�����

#define UPLINK_FRAME_HEADER                     (0xff)      //���б�����ʼ��־
#define UPLINK_FRAME_TAIL                       (0xfe)      //���б��Ľ�����־
#define UART3_FIFOBUF_LENGTH                    (64)        //ѭ��buffer�ռ��С
#define DEVIDE_FRAME_TASK_FSM_BUF_LENGTH        (64)        //��֡�߳�״̬�����ݻ���



//���ǹ�drive_port_test.c�ļ�ʹ�õĺ�
#define BLOCK_SIZE      512         //SD�����С
#define WRITE_READ_ADDRESS    0x00000000
#define NUMBER_OF_BLOCKS 1


//3�����Ͷ���
/********************************************************************************************************************************************************************/
/**************************************************���Ͷ��壺���б���������ݽṹ����*****************************************/
#pragma pack(push)
#pragma pack(1)


//���б��ġ��������͡�ö��
typedef enum
{
    Para_bdr      = 0,  //���ò����ʣ�������Ч
    Para_cid,     //�����豸ID��������Ч
    Para_mcs,        //����΢��ϸ��
    Para_spd,        //�����ٶ�
    Para_acc,        //���ü��ٶ�
    Para_dec,        //���ü��ٶ�
    Para_cra,        //���ü���ʱ����
    Para_crn,        //��������ʱ����
    Para_crh,        //���ñ���ʱ����
    Para_s1f,        //����S1�½��ش����¼�
    Para_s1r,        //����S1�����ش����¼�
    Para_s2f,        //����S2�½��ش����¼�
    Para_s2r,        //����S2�����ش����¼�
    Para_s3f,        //����S3�½��ش����¼�
    Para_s3r,        //����S3�����ش����¼�
    Para_zmd,        //���ù��㹦�ܣ�ON/OFF��
    Para_snr,        //���ù����ô�����
    Para_osv,        //���ù��㴫����OPENʱ��ƽ
    Para_zsd,        //���ù����ٶȣ�����������
    Para_zsp,        //���ù����İ�ȫλ��
    Para_dmd,        //������������ģʽ
    Para_dar,        //��������������ʱ��
    Para_pas,        //S3ģʽ����
    Para_res,        //����λ����С��ŷķ��
    Para_value,      //�ƶ���ָ��λ��
    Para_start,      //ִ�й���  eg: zero start\n   or   ������������ eg: demo start\n
    Para_stop,       //ֹͣ����  eg: zero stop\n    or   ֹͣ�������� eg: demo stop\n
    Para_add,        //��ӽڵ�
    Para_clear,      //������нڵ�
}Para_type_typedef;


//��CALCULATE_Total_Length_Of_Downlink_Message�������棬
//��Ҫʵ�֡��������͡���ö�ٺ��ַ���֮���ת����
//�������Ƕ���һ���ṹ�����ͣ���������ö�ٺ��ַ������ձ�
typedef struct
{
    Para_type_typedef e_Para_Type;       //���������͡���ö����ʽ
    char s_Para_Type[5];                //���������͡� ���ַ�����ʽ
}Para_Type_form_typedef;

//���б���ָ��ö��
typedef enum
{
    Cmd_dev=0,       //���֣���ȡ������������ͺźͰ汾��
    Cmd_sts,         //��ȡ����״̬���ٶȡ�λ�á�״̬��
    Cmd_cfg,         //��ȡ����ֵ
    Cmd_ena,         //���ʹ��
    Cmd_off,         //����ѻ�
    Cmd_mov,         //��ָ���ٶ�������ת
    Cmd_pos,         //�ƶ���ָ��λ��
    Cmd_org,         //ָ����ǰλ��Ϊԭ��
    Cmd_stp,         //ֹͣ
    Cmd_zero,        //ִ�й���
    Cmd_sav,         //�������浽FLASH
    Cmd_demo,        //��ȡ�������нڵ�

}Cmd_Typedef;

//��CALCULATE_Total_Length_Of_Downlink_Message�������棬
//��Ҫʵ�֡�ָ���ö�ٺ��ַ���֮���ת����
//�������Ƕ���һ���ṹ�����ͣ���������ö�ٺ��ַ������ձ�
typedef struct
{
    Cmd_Typedef e_Cmd;
    char s_Cmd[5];
}Cmd_form_typedef;



//���б��Ĳ����ṹ��
typedef struct
{
    Para_type_typedef e_Para_Type;      // �������� eg:bdr/cid/mcs/spd/...
    union
    {
        int32_t u_Para_Value;             // ����ֵ���޷������Σ�
        float f_Para_Value;                // ����ֵ�������ȸ��������Σ�
    }Para_Union;
}Para_Struct_Typedef;


//���б��Ľṹ��
typedef struct
{
    uint8_t               RS485_ID;                       //�����������485_ID��
    Cmd_Typedef           Cmd_Enum;                       //ָ��
    uint8_t               Total_num_of_Para;              //���б����в����ĸ���
    Para_Struct_Typedef*  Para_Struct[24];                //�������ͼ�����ֵ
}DownLink_Struct_Typedef;

//���б���֡�ṹ��
typedef struct
{
    char * head_ptr;        //���б���֡ͷ
    uint8_t total_length;   //���б���֡����
}Downlink_Frame_typedef;

/*******************************************Triggle_Send_Task ��״̬����״̬***************************************************/
typedef enum
{
    Preparing_Animation_Data_Status,            //׼����������״̬
    Waiting_Count_Down_Status,                  //�ȵ���ʱ״̬
    Waiting_Ack_Status,                         //�Ȼظ�״̬
    Timeout_Resend_Status,                      //��ʱ�ش�״̬
}Status_Of_Triggle_Send_Task_Typedef;                 //Triggle_Send_Task ��״̬����״̬

/**********************************************�����е�������X��Y��Z����******************************************************************/
typedef struct
{
    uint16_t X;        //�����е���������X����
    uint16_t Y;        //�����е���������Y����
    int32_t Z;         //�����е������������е���Z����
}Motor_Coordinate_typedef;
/**********************************************����������ڽṹ��λ�õ������485ID�ŵĶ�Ӧ��ϵ�ṹ��************************************************************/

typedef struct
{
    uint16_t X;
    uint16_t Y;
    uint8_t RS485_ID;
}Coordinate_and_ID_Typedef;
/********************************************************************************************************************************************************************/

/* ���б������ݶ���Ϣ */
typedef union
{
	float fdata;
	int32_t idata;
	uint32_t udata;
}Uplink_Frame_value_info;

/* ���б��� */
typedef struct
{
    uint8_t cid;
    uint8_t fbid;
    uint8_t *data;
}Uplink_Frame_Typedef;

/*�������״̬��Ϣ�ṹ�� */
typedef struct
{
    uint8_t cid;        //�豸��
    //������
    //����
    //����������
	float spd;          //�ٶ�
	int32_t pos;        //λ��
	uint32_t status;    //״̬
}device_info;

/* ��֡�߳�״̬ */
typedef enum
{
    WAITING_STATE = 0,       //
    RECEIVE_STATE,       //
    SEND_STATE,          //   
    DROP_STATE,          //�Ƿ����ĵĴ���״̬

    INVALID_STATE
}Devide_Frame_Task_FSM_Status_Typedef;

/* ��֡�߳�״̬���ṹ */
typedef struct
{
    Devide_Frame_Task_FSM_Status_Typedef status;    //״̬��״̬
    uint32_t length;                                //
    uint8_t  sum;                                   //У���,��ֵΪ0
    uint8_t  *data;                                 //
}Devide_Frame_Task_FSM_Typedef;

/* ��֡�߳�->�����߳���Ϣ������Ϣ�ṹ */
typedef struct
{
    uint32_t len;
    uint8_t *data;
}Devide_Frame_MessageQ_info;

/* ͨ����Ϣ���нṹ */
typedef struct
{
    uint32_t length;
    uint8_t *data;
}MessageQ_info;

#pragma pack(pop)


//4����������
/********************************************************************************************************************************************************************/
extern Status_Of_Triggle_Send_Task_Typedef Status_Of_Triggle_Send_Task;
extern Motor_Coordinate_typedef Motor_Coordinate_Array[2][12];
extern Coordinate_and_ID_Typedef Coordinate_and_ID_Struct[3][4];
extern Para_Type_form_typedef Para_Type_form_Strcut[];
extern Cmd_form_typedef Cmd_form_struct[];

extern uint8_t g_Uart3_DevideFrame_Fifo_Buffer[UART3_FIFOBUF_LENGTH];      //ѭ������ ������λ���������������б���
extern struct fifo g_Uart3_DevideFrame_Fifo;

extern uint8_t g_Devide_Frame_Task_FSM_Buf[DEVIDE_FRAME_TASK_FSM_BUF_LENGTH];

extern Devide_Frame_Task_FSM_Typedef g_Devide_Frame_Task_FSM;

//���ǹ�drive_port_test.c�ļ�ʹ�õ�ȫ�ֱ���
extern char buf_read[NUMBER_OF_BLOCKS * BLOCK_SIZE];
extern char buf_write[NUMBER_OF_BLOCKS * BLOCK_SIZE];

//5����������
/********************************************************************************************************************************************************************/


#endif


















