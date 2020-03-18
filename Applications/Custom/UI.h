#ifndef __UI_H
#define __UI_H

//1、头文件
/**********************************************************************************************************************/
#include "stdio.h"
#include "string.h"


//2、宏定义
/**********************************************************************************************************************/
#define KEY_SUM 7       //设备按键数--7

#define PROCESS_KEY_FUNCTION_SUM   KEY_SUM

#define PAGE_SUM 2     //设备界面数--2

#define LONG_PRESS_TICK                 500000      //长按键持续的 systick
#define LONG_PRESS_MASK                 0x10
#define SHORT_PRESS_MASK                0x20
#define LONG_PRESS_RELEASE_MESSAGE      0X00

#define UILINE2LCDPAGE(x)             ((x) * 2 + 1)

/* 界面起始位定位 */
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

//3、类型定义
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
    AbstractKey_Typedef CurrentKey;          //当前ADC读到的按键
    unsigned int PressTick;                  //按下按键时时钟节拍， osKernelSysTick 获取当前时钟节拍
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

//4、变量声明
/**********************************************************************************************************************/

//5、函数声明
/**********************************************************************************************************************/

void LcdUpdateMain(void);
void KeyScanMain(void);
void SHOW_Page_Startup(void);
void SHOW_Page_Init(void);


#endif

