#ifndef __UI_H
#define __UI_H

//1��ͷ�ļ�
/**********************************************************************************************************************/
#include "stdio.h"
#include "string.h"


//2���궨��
/**********************************************************************************************************************/
#define KEY_SUM 7       //�豸������--7

#define PROCESS_KEY_FUNCTION_SUM   KEY_SUM

#define PAGE_SUM 2     //�豸������--2

#define LONG_PRESS_TICK                 500000      //������������ systick
#define LONG_PRESS_MASK                 0x10
#define SHORT_PRESS_MASK                0x20
#define LONG_PRESS_RELEASE_MESSAGE      0X00

#define UILINE2LCDPAGE(x)             ((x) * 2 + 1)

/* ������ʼλ��λ */
#define INITPAGE_LINE0_STARTCOLUMN         9
#define INITPAGE_LINE1_STARTCOLUMN         33
#define INITPAGE_CURACT_STARTCOLUMN        (INITPAGE_LINE1_STARTCOLUMN + 16 + 16 + 8)
#define INITPAGE_LINE2_STARTCOLUMN         57
#define INITPAGE_LINE3_STARTCOLUMN         33
#define INITPAGE_CURSOR_STARTCOLUMN        9

#define CONFIRMPAGE_LINE0_STARTCOLUMN      33
#define CONFIRMPAGE_LINE1_STARTCOLUMN      65
#define CONFIRMPAGE_LINE2_STARTCOLUMN      65
#define CONFIRMPAGE_CURSOR_STARTCOLUMN     41

//3�����Ͷ���
/**********************************************************************************************************************/
typedef enum
{
    KEY_STATE_INIT,
    KEY_STATE_WOBBLE,
    KEY_STATE_PRESS,
    KEY_STATE_LONG,

    KEY_STATE_INVALID
}KEY_STATE_E;

typedef struct
{
    KEY_STATE_E state;
    AbstractKey_Typedef CurrentKey;          //��ǰADC�����İ���
    unsigned int PressTick;                  //���°���ʱʱ�ӽ��ģ� osKernelSysTick ��ȡ��ǰʱ�ӽ���
}KEY_FSM_T;

typedef enum
{
    LINE0 = 0,
    LINE1 = 1,
    LINE2 = 2,
    LINE3 = 3,

    LINE_INVALID
}CurrentLineTypedef;

typedef enum
{
    Page_Init,
    Page_Confirm,

    Page_Invalid
}CurrentPageTypedef;

//4����������
/**********************************************************************************************************************/

//5����������
/**********************************************************************************************************************/

void LcdUpdateMain(void);
void KeyScanMain(void);
void SHOW_Page_Startup(void);
void SHOW_Page_Init(void);


#endif

