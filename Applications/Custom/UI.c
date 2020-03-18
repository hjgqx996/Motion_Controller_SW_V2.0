//*********************************************************************
//
//           版权所有 (C), 2008-2028, 罗卜干实验室
//             -----------------------------------------------
//
//  文件作者:   liupengcheng
//  生成日期:
//  功能描述:
//  修改历史:
//  (1) 修改日期:
//      修改作者:Liu-PC
//      修改内容:
//
//*********************************************************************
#include "Global.h"
#include "UI.h"
#include "datastruct.h"
#include "LCD12864.h"

/* 测试需要包含头文件 */
#include "SDCard.h"

/*********************************************/
//当前界面
CurrentPageTypedef   e_Current_Page = Page_Init;
/**********************************************/


/**********************************************/
//当前按键
AbstractKey_Typedef   e_Trigger_Key = KEY_NONE_Enum;
/*********************************************/


/**********************************************/
//当前行数
CurrentLineTypedef  e_InitPage_Current_Line    = LINE1;
CurrentLineTypedef  e_ConfirmPage_Current_Line = LINE1;
/**********************************************/

uint8_t g_ActionSum     = 5;
uint8_t g_CurrentAction = 2;

/**********************************************************************
**函数名称        ：SwitchPage
**创建人          ：
**创建日期        ：
**最新修改人      ：
**最近修改日期    ：
**功能描述        ：后台跳转到 nPage
**入口参数        ：枚举类型： PageType
**返回参数        ：none
**备注/注意       ：
**********************************************************************/
void SWITCH_Page(CurrentPageTypedef page_Enum)
{
	if ((int8_t)page_Enum >= (int8_t)Page_Invalid || (int8_t)page_Enum < (int8_t)Page_Init)
	{
		return;
	}
	else
	{
		e_Current_Page = page_Enum;
	}
}

/******************************界面显示函数****************************************/

void SHOW_Page_Startup(void)
{
    uint16_t column = 25;

    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_32x32, UILINE2LCDPAGE(LINE0), 1, hz32x32_ge);
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_32x32, UILINE2LCDPAGE(LINE0), 33, hz32x32_wu);
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_32x32, UILINE2LCDPAGE(LINE0), 65, hz32x32_hu);
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_32x32, UILINE2LCDPAGE(LINE0), 97, hz32x32_dong);

    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, 6, column, hz16x16_yun);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, 6, column, hz16x16_dong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, 6, column, hz16x16_kong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, 6, column, hz16x16_zhi);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, 6, column, hz16x16_qi);
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void SHOW_Page_Init(void)
{
    uint16_t column = 0;

    DEV_Ioctl(DEVICE_ZERO, CMD_CLEAR_SCREEN);

    /* 界面抬头 */
    column = INITPAGE_LINE0_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_yun);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_dong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_kong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_zhi);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_qi);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16['(' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16['0' + g_CurrentAction - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16['/' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16['0' + g_ActionSum - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16[')' - ' ']);
    column += 8;

    /* 第一行 */
    column = INITPAGE_LINE1_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_dong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_zuo);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE1),  column, ascii_table_8x16[':' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_numbers[g_CurrentAction - 1]);
    column += 16;

    /* 第二行 */
    column = INITPAGE_LINE2_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_zhi_2);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_xing);
    column += 16;

    /* 第三行 */
    column = INITPAGE_LINE3_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE3), column, hz16x16_shi);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE3), column, hz16x16_yan);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16[':' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['3' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['.' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['3' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['3' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['m' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE3), column, ascii_table_8x16['s' - ' ']);
    column += 8;

    /* 光标 */
    e_InitPage_Current_Line = LINE1;
    column = INITPAGE_CURSOR_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
                    ----是否执行:---
                          ->是
                          ->否
                    ----------------
                    ----------------
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void SHOW_Page_Confirm(void)
{
    uint16_t column = 0;

    DEV_Ioctl(DEVICE_ZERO, CMD_CLEAR_SCREEN);

    /* 界面抬头 */
    column = CONFIRMPAGE_LINE0_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_shi_2);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_fou);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_zhi_2);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE0), column, hz16x16_xing);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE0), column, ascii_table_8x16[':' - ' ']);
    column += 8;

    /* 第一行 */
    column = CONFIRMPAGE_LINE1_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_shi_2);
    column += 16;

    /* 第二行 */
    column = CONFIRMPAGE_LINE2_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_fou);
    column += 16;

    /* 光标 */
    column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
    e_ConfirmPage_Current_Line = LINE1;             //每次光标重置到第一行
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    column += 16;
}

///////////////////////////////界面刷新函数*************************************************/
typedef void(*LCDUpdateTypedef)(void);            //指针函数--指向界面更新显示函数
/*
* 界面更新显示函数
*/
static LCDUpdateTypedef p_LCDUpdateFunction[] =
{
	SHOW_Page_Init,
	SHOW_Page_Confirm,
};
/*****************************//////////////////////////////////////////////////

/******************************按键处理函数****************************************/
/**********************************************************************
**下面是在 相应界面下 对应短按键处理指针函数 的实现
**********************************************************************/
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_UpKey_Of_Page_Init(void)
{
    uint16_t column;

    if (LINE1 < e_InitPage_Current_Line)
    {
        //擦除原来的光标
        column = INITPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, null_16x16);
        e_InitPage_Current_Line--;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_LeftKey_Of_Page_Init(void)
{
    uint16_t column;

	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* 选择动作 */
            g_CurrentAction--;
            if (0 == g_CurrentAction)
            {
                g_CurrentAction += g_ActionSum;
            }
            column = INITPAGE_CURACT_STARTCOLUMN;
            DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_numbers[g_CurrentAction - 1]);

            break;
        }
        case LINE2:
        {
            break;
        }
        default:
        {
            break;
        }
	}
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_OkKey_Of_Page_Init(void)
{
	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* 选择动作 */

            /* SDIO测试 */
            Sdcard_Test();

            break;
        }
        case LINE2:
        {
            /* 选择执行，跳到确认界面 */
            e_Current_Page = Page_Confirm;
            p_LCDUpdateFunction[e_Current_Page]();

            /*
            SWITCH_Page(Page_Confirm);
            */

            break;
        }
        default:
        {
            break;
        }
	}
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_RightKey_Of_Page_Init(void)
{
    uint16_t column;

	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* 选择动作 */
            g_CurrentAction++;
            if (g_ActionSum < g_CurrentAction)
            {
                g_CurrentAction -= g_ActionSum;
            }
            column = INITPAGE_CURACT_STARTCOLUMN;
            DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_numbers[g_CurrentAction - 1]);

            break;
        }
        case LINE2:
        {
            break;
        }
        default:
        {
            break;
        }
	}
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_HomeKey_Of_Page_Init(void)
{

}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_DownKey_Of_Page_Init(void)
{
    uint16_t column;

    //e_InitPage_Current_Line += 1，刷新光标
    if (LINE3 > e_InitPage_Current_Line)
    {
        //擦除原来的光标
        column = INITPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, null_16x16);
        e_InitPage_Current_Line++;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_ESCKey_Of_Page_Init(void)
{

}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_UpKey_Of_Page_Confirm(void)
{
    uint16_t column;

    if (LINE1 < e_ConfirmPage_Current_Line)
    {
        //擦除原来的光标
        column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, null_16x16);
        e_ConfirmPage_Current_Line--;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_LeftKey_Of_Page_Confirm(void)
{

}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_OkKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

	switch (e_ConfirmPage_Current_Line)
	{
        case LINE1:
        {
            /* 选择“是” */
            p_LCDUpdateFunction[e_Current_Page]();

            break;
        }
        case LINE2:
        {
            /* 选择“否” */
            p_LCDUpdateFunction[e_Current_Page]();

            break;
        }
        default:
        {
            break;
        }
	}
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_RightKey_Of_Page_Confirm(void)
{

}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_HomeKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

    p_LCDUpdateFunction[e_Current_Page]();
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_DownKey_Of_Page_Confirm(void)
{
    uint16_t column;

    //e_InitPage_Current_Line += 1，刷新光标
    if (LINE2 > e_ConfirmPage_Current_Line)
    {
        //擦除原来的光标
        column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, null_16x16);
        e_ConfirmPage_Current_Line++;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_ESCKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

    p_LCDUpdateFunction[e_Current_Page]();
}

///////////////////////////////按键处理函数**********************************************/
typedef void(*KeyProcessTypedef)(void);           //指针函数--指向按键处理函数
/*
* 短按键处理函数
    KEY_NONE_Enum  = 0,
    KEY_UP_Enum    = 1,
    KEY_LEFT_Enum  = 2,
    KEY_OK_Enum    = 3,
    KEY_RIGHT_Enum = 4,
    KEY_HOME_Enum  = 5,
    KEY_DOWN_Enum  = 6,
    KEY_ESC_Enum   = 7,
*/
static KeyProcessTypedef p_ShortKeyProcessFunction[PAGE_SUM][PROCESS_KEY_FUNCTION_SUM] =
{
	{
        PROCESS_ShortPush_UpKey_Of_Page_Init,
        PROCESS_ShortPush_LeftKey_Of_Page_Init,
        PROCESS_ShortPush_OkKey_Of_Page_Init,
        PROCESS_ShortPush_RightKey_Of_Page_Init,
        PROCESS_ShortPush_HomeKey_Of_Page_Init,
        PROCESS_ShortPush_DownKey_Of_Page_Init,
        PROCESS_ShortPush_ESCKey_Of_Page_Init,
    },

	{
        PROCESS_ShortPush_UpKey_Of_Page_Confirm,
        PROCESS_ShortPush_LeftKey_Of_Page_Confirm,
        PROCESS_ShortPush_OkKey_Of_Page_Confirm,
        PROCESS_ShortPush_RightKey_Of_Page_Confirm,
        PROCESS_ShortPush_HomeKey_Of_Page_Confirm,
        PROCESS_ShortPush_DownKey_Of_Page_Confirm,
        PROCESS_ShortPush_ESCKey_Of_Page_Confirm,
    },
};

#if 0

/**********************************************************************
****下面是在 相应界面下 对应长按键处理指针函数 的实现
**********************************************************************/
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Init(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Init(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Init(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Body_Fat_Rate(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Body_Fat_Rate(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Body_Fat_Rate(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Height(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Height(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Height(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Age(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Age(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Age(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}


/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Sex(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Sex(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Sex(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Weight(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Weight(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Weight(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Body_Resistance(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Body_Resistance(void)
{

}
/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :
** 最新修改人       :liupengcheng
** 最近修改日期     :
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Body_Resistance(void)
{

}


/*
* 长按键处理函数
*/
static  KeyProcessTypedef p_LongKeyProcessFunction[PAGE_SUM][PROCESS_KEY_FUNCTION_SUM] =
{
	{PROCESS_LongPush_UpKey_Of_Page_Init,            PROCESS_LongPush_OkKey_Of_Page_Init,            PROCESS_LongPush_DownKey_Of_Page_Init,           },
	{PROCESS_LongPush_UpKey_Of_Page_Body_Fat_Rate,   PROCESS_LongPush_OkKey_Of_Page_Body_Fat_Rate,   PROCESS_LongPush_DownKey_Of_Page_Body_Fat_Rate,  },
	{PROCESS_LongPush_UpKey_Of_Page_Height,          PROCESS_LongPush_OkKey_Of_Page_Height,          PROCESS_LongPush_DownKey_Of_Page_Height,         },
	{PROCESS_LongPush_UpKey_Of_Page_Age,             PROCESS_LongPush_OkKey_Of_Page_Age,             PROCESS_LongPush_DownKey_Of_Page_Age,            },
	{PROCESS_LongPush_UpKey_Of_Page_Sex,             PROCESS_LongPush_OkKey_Of_Page_Sex,             PROCESS_LongPush_DownKey_Of_Page_Sex,            },
	{PROCESS_LongPush_UpKey_Of_Page_Weight,          PROCESS_LongPush_OkKey_Of_Page_Weight,          PROCESS_LongPush_DownKey_Of_Page_Weight,         },
	{PROCESS_LongPush_UpKey_Of_Page_Body_Resistance, PROCESS_LongPush_OkKey_Of_Page_Body_Resistance, PROCESS_LongPush_DownKey_Of_Page_Body_Resistance,},
};
/*****************************//////////////////////////////////////////////////


KeyValueBox_Typedef KeyValueBox_Struct[10];
/**********************************************************************
** 函数名称         : BoxConfig
** 创建人           : liupengcheng
** 创建日期         : 2017/9/7 15:40
** 最新修改人       : liupengcheng
** 最近修改日期      : 2017/9/7 15:40
** 功能描述         : 清空邮箱内的所有内容
** 入口参数         : none
** 返回参数         : none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void BoxConfig(void)
{
	memset(KeyValueBox_Struct, 2, 10 * sizeof(KeyValueBox_Struct));
}
/**********************************************************************
** 函数名称         :SendKeyValToBox
** 创建人           :liupengcheng
** 创建日期         :2017/9/7 15:40
** 最新修改人       :liupengcheng
** 最近修改日期      :2017/9/7 15:40
** 功能描述         :向邮箱里面扔一个邮件，前面的邮件向后位移
** 入口参数         :
					--sendDate:邮件里面的数据
** 返回参数         :none
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
void SendKeyValToBox(AbstractKey_Typedef SendDate)
{
	uint8_t i = 0;
	for (i = 9; i > 0; i--)
	{
		KeyValueBox_Struct[i].data = KeyValueBox_Struct[i - 1].data;
		KeyValueBox_Struct[i].RecieverID = KeyValueBox_Struct[i - 1].RecieverID;
		KeyValueBox_Struct[i].SenderID = KeyValueBox_Struct[i - 1].SenderID;
	}
	KeyValueBox_Struct[0].SenderID = KeyScanMain_ID;
	KeyValueBox_Struct[0].RecieverID = LcdUpdateMain_ID;
	KeyValueBox_Struct[0].data = SendDate;
}

/**********************************************************************
** 函数名称         :
** 创建人           :liupengcheng
** 创建日期         :2017/9/7 15:40
** 最新修改人       :liupengcheng
** 最近修改日期      :2017/9/7 15:40
** 功能描述         :
** 入口参数         :
** 返回参数         :
** 备注/注意        :
** QQ              : 1240612852
***********************************************************************/
AbstractKey_Typedef GetKeyValFromBox(void)
{
	int8_t i = 0;
	AbstractKey_Typedef date_temp = KEY_NONE_Enum;
	for (i = 9; i >= 0; i--)
	{
		if (KeyValueBox_Struct[i].RecieverID == LcdUpdateMain_ID)
		{
			date_temp = KeyValueBox_Struct[i].data;
			/************将这封邮件删除后，将数据返回********/
			KeyValueBox_Struct[i].data = KEY_NONE_Enum;
			KeyValueBox_Struct[i].RecieverID = 0;
			KeyValueBox_Struct[i].SenderID = 0;
			/**********************************************/
			return date_temp;
		}
	}
	return KEY_NONE_Enum;
}

#endif

/**********************************************************************
**函数名称        ：KeyScanMain
**创建人          ：liupengcheng
**创建日期        ：2017-9-7
**最新修改人      ：liupengcheng
**最近修改日期    ：2017-9-7
**功能描述        ：轮询扫描当前按键，并将扫描的键值放到Box队列里面去
**入口参数        ：none
**返回参数        ：none
**备注/注意       ：按键扫描放在任务中10ms轮询一次，longPressSignal为按键按下时，扫描到的次数
**QQ             ：1240612852
**********************************************************************/
void KeyScanMain()
{
	AbstractKey_Typedef CurrentKey;
    static KEY_FSM_T key_fsm;
    uint32_t releasetick;

	DEV_Read(DEVICE_THREE, (char *)&CurrentKey, sizeof(char), 0x0);

    switch (key_fsm.state)
    {
        case KEY_STATE_INIT:
        {
            if (KEY_NONE_Enum != CurrentKey)
            {
                key_fsm.CurrentKey = CurrentKey;
                key_fsm.state      = KEY_STATE_WOBBLE;
            }

            break;
        }
        case KEY_STATE_WOBBLE:
        {
            if (CurrentKey == key_fsm.CurrentKey)
            {
                key_fsm.PressTick  = osKernelSysTick();
                key_fsm.state      = KEY_STATE_PRESS;
            }
            else
            {
                key_fsm.CurrentKey = KEY_NONE_Enum;
                key_fsm.state      = KEY_STATE_INIT;
            }

            break;
        }
        case KEY_STATE_PRESS:
        {
            if (CurrentKey == key_fsm.CurrentKey)
            {
                if (osKernelSysTick() - key_fsm.PressTick > osKernelSysTickMicroSec(LONG_PRESS_TICK))
                {
                    osMessagePut(Key_Message_Handle, key_fsm.CurrentKey | LONG_PRESS_MASK, 10);
                    key_fsm.state = KEY_STATE_LONG;
                }
            }
            else if (KEY_NONE_Enum == CurrentKey)
            {
                //发送press消息
                osMessagePut(Key_Message_Handle, key_fsm.CurrentKey | SHORT_PRESS_MASK, 10);
                key_fsm.CurrentKey = KEY_NONE_Enum;
                key_fsm.state      = KEY_STATE_INIT;
            }

            break;
        }
        case KEY_STATE_LONG:
        {
            if (KEY_NONE_Enum == CurrentKey)
            {
                osMessagePut(Key_Message_Handle, LONG_PRESS_RELEASE_MESSAGE, 10);
                key_fsm.CurrentKey = KEY_NONE_Enum;
                key_fsm.state      = KEY_STATE_INIT;
            }

            break;
        }
        default:
        {
            break;
        }
    }
}

void LcdUpdateMain()
{
    osEvent event;
    uint16_t keyValue;
    uint16_t isLongPress = 0;

    event = osMessageGet(Key_Message_Handle, 0);
    if (osOK == event.status)
    {

    }
    else if (osEventMessage == event.status)
    {
        keyValue = event.value.v;
        isLongPress = keyValue & LONG_PRESS_MASK;
        if (SHORT_PRESS_MASK == (keyValue & SHORT_PRESS_MASK))
        {
            e_Trigger_Key = keyValue^SHORT_PRESS_MASK;

            TRACE("Short press key: %d.\r\n", keyValue^SHORT_PRESS_MASK);
            p_ShortKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1]();
        }
        else if (LONG_PRESS_MASK == (keyValue & LONG_PRESS_MASK))
        {
            TRACE("Long press key: %d.\r\n", keyValue^LONG_PRESS_MASK);
        }
        else if (LONG_PRESS_RELEASE_MESSAGE == keyValue)
        {
            TRACE("Long press key released.\r\n");
        }
    }

//	p_LCDUpdateFunction[e_Current_Page]();
}

#if 0

/*********************************************
//函数名    ：OLED_Update_Task
//修改人    ：liupengcheng
//修改时间  ：2017-8-28
**功能描述  ：轮询Box队列里面的值，如果有值得话取出来，并根据键值更新界面
//入口参数  ：none
//返回值    ：none
//备注     ：对外接口--界面更新
//联系方式   ：1240612852
**********************************************/
void LcdUpdateMain()
{


	e_Trigger_Key = KEY_NONE_Enum;				   //没有键值的时候，当前按键为Key_None
	e_Trigger_Key = GetKeyValFromBox();        //从邮箱中取出一个键值



	//无按键不响应
	if (e_Trigger_Key == KEY_NONE_Enum)
	{

	}
	//短按键对应响应
	else if (0x00 == (e_Trigger_Key & 0x80))
	{
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_ShortKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1]();  //跳到相对应短按键处理函数执行
			}
	}
	//长按键按下时刻对应响应
	else if(0xc0 == (e_Trigger_Key & 0xc0))
	{

			e_Trigger_Key &= 0x3f;                 //除去长按键按下标志
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_LongKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1](); //跳到相对应长按键处理函数执行
			}
	}
	//长按键松开时刻对应响应
	else if (0x80 == (e_Trigger_Key & 0x80))
	{
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			e_Trigger_Key &= 0x7f;                 //除去长按键松开标志
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_LongKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1](); //跳到相对应长按键处理函数执行
			}
	}

	p_LCDUpdateFunction[e_Current_Page]();



	//UG_FillScreen(C_WHITE);        //清屏
}
#endif





