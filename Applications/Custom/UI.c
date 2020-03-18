//*********************************************************************
//
//           ��Ȩ���� (C), 2008-2028, �޲���ʵ����
//             -----------------------------------------------
//
//  �ļ�����:   liupengcheng
//  ��������:
//  ��������:
//  �޸���ʷ:
//  (1) �޸�����:
//      �޸�����:Liu-PC
//      �޸�����:
//
//*********************************************************************
#include "Global.h"
#include "UI.h"
#include "datastruct.h"
#include "LCD12864.h"

/* ������Ҫ����ͷ�ļ� */
#include "SDCard.h"

/*********************************************/
//��ǰ����
CurrentPageTypedef   e_Current_Page = Page_Init;
/**********************************************/


/**********************************************/
//��ǰ����
AbstractKey_Typedef   e_Trigger_Key = KEY_NONE_Enum;
/*********************************************/


/**********************************************/
//��ǰ����
CurrentLineTypedef  e_InitPage_Current_Line    = LINE1;
CurrentLineTypedef  e_ConfirmPage_Current_Line = LINE1;
/**********************************************/

uint8_t g_ActionSum     = 5;
uint8_t g_CurrentAction = 2;

/**********************************************************************
**��������        ��SwitchPage
**������          ��
**��������        ��
**�����޸���      ��
**����޸�����    ��
**��������        ����̨��ת�� nPage
**��ڲ���        ��ö�����ͣ� PageType
**���ز���        ��none
**��ע/ע��       ��
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

/******************************������ʾ����****************************************/

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
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void SHOW_Page_Init(void)
{
    uint16_t column = 0;

    DEV_Ioctl(DEVICE_ZERO, CMD_CLEAR_SCREEN);

    /* ����̧ͷ */
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

    /* ��һ�� */
    column = INITPAGE_LINE1_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_dong);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_zuo);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_8x16, UILINE2LCDPAGE(LINE1),  column, ascii_table_8x16[':' - ' ']);
    column += 8;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_numbers[g_CurrentAction - 1]);
    column += 16;

    /* �ڶ��� */
    column = INITPAGE_LINE2_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_zhi_2);
    column += 16;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_xing);
    column += 16;

    /* ������ */
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

    /* ��� */
    e_InitPage_Current_Line = LINE1;
    column = INITPAGE_CURSOR_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
                    ----�Ƿ�ִ��:---
                          ->��
                          ->��
                    ----------------
                    ----------------
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void SHOW_Page_Confirm(void)
{
    uint16_t column = 0;

    DEV_Ioctl(DEVICE_ZERO, CMD_CLEAR_SCREEN);

    /* ����̧ͷ */
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

    /* ��һ�� */
    column = CONFIRMPAGE_LINE1_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE1), column, hz16x16_shi_2);
    column += 16;

    /* �ڶ��� */
    column = CONFIRMPAGE_LINE2_STARTCOLUMN;
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(LINE2), column, hz16x16_fou);
    column += 16;

    /* ��� */
    column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
    e_ConfirmPage_Current_Line = LINE1;             //ÿ�ι�����õ���һ��
    DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    column += 16;
}

///////////////////////////////����ˢ�º���*************************************************/
typedef void(*LCDUpdateTypedef)(void);            //ָ�뺯��--ָ����������ʾ����
/*
* ���������ʾ����
*/
static LCDUpdateTypedef p_LCDUpdateFunction[] =
{
	SHOW_Page_Init,
	SHOW_Page_Confirm,
};
/*****************************//////////////////////////////////////////////////

/******************************����������****************************************/
/**********************************************************************
**�������� ��Ӧ������ ��Ӧ�̰�������ָ�뺯�� ��ʵ��
**********************************************************************/
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_UpKey_Of_Page_Init(void)
{
    uint16_t column;

    if (LINE1 < e_InitPage_Current_Line)
    {
        //����ԭ���Ĺ��
        column = INITPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, null_16x16);
        e_InitPage_Current_Line--;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_LeftKey_Of_Page_Init(void)
{
    uint16_t column;

	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* ѡ���� */
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
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_OkKey_Of_Page_Init(void)
{
	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* ѡ���� */

            /* SDIO���� */
            Sdcard_Test();

            break;
        }
        case LINE2:
        {
            /* ѡ��ִ�У�����ȷ�Ͻ��� */
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
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_RightKey_Of_Page_Init(void)
{
    uint16_t column;

	switch (e_InitPage_Current_Line)
	{
        case LINE1:
        {
            /* ѡ���� */
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
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_HomeKey_Of_Page_Init(void)
{

}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_DownKey_Of_Page_Init(void)
{
    uint16_t column;

    //e_InitPage_Current_Line += 1��ˢ�¹��
    if (LINE3 > e_InitPage_Current_Line)
    {
        //����ԭ���Ĺ��
        column = INITPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, null_16x16);
        e_InitPage_Current_Line++;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_InitPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_ESCKey_Of_Page_Init(void)
{

}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_UpKey_Of_Page_Confirm(void)
{
    uint16_t column;

    if (LINE1 < e_ConfirmPage_Current_Line)
    {
        //����ԭ���Ĺ��
        column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, null_16x16);
        e_ConfirmPage_Current_Line--;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_LeftKey_Of_Page_Confirm(void)
{

}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_OkKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

	switch (e_ConfirmPage_Current_Line)
	{
        case LINE1:
        {
            /* ѡ���ǡ� */
            p_LCDUpdateFunction[e_Current_Page]();

            break;
        }
        case LINE2:
        {
            /* ѡ�񡰷� */
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
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_RightKey_Of_Page_Confirm(void)
{

}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_HomeKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

    p_LCDUpdateFunction[e_Current_Page]();
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_DownKey_Of_Page_Confirm(void)
{
    uint16_t column;

    //e_InitPage_Current_Line += 1��ˢ�¹��
    if (LINE2 > e_ConfirmPage_Current_Line)
    {
        //����ԭ���Ĺ��
        column = CONFIRMPAGE_CURSOR_STARTCOLUMN;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, null_16x16);
        e_ConfirmPage_Current_Line++;
        DEV_Ioctl(DEVICE_ZERO, CMD_DISPLAY_ICON_16x16, UILINE2LCDPAGE(e_ConfirmPage_Current_Line), column, icon16x16_cursor);
    }
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_ShortPush_ESCKey_Of_Page_Confirm(void)
{
    e_Current_Page = Page_Init;

    p_LCDUpdateFunction[e_Current_Page]();
}

///////////////////////////////����������**********************************************/
typedef void(*KeyProcessTypedef)(void);           //ָ�뺯��--ָ�򰴼�������
/*
* �̰���������
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
****�������� ��Ӧ������ ��Ӧ����������ָ�뺯�� ��ʵ��
**********************************************************************/
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Init(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Init(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Init(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}


/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Body_Fat_Rate(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Body_Fat_Rate(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Body_Fat_Rate(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Height(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Height(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Height(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Age(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Age(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Age(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}


/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Sex(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Sex(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Sex(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Weight(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Weight(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Weight(void)
{
	//UG_PutString(0, 0, "ShortClrKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_UpKey_Of_Page_Body_Resistance(void)
{
	//UG_PutString(0, 0, "ShortSetKey");
}

/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_OkKey_Of_Page_Body_Resistance(void)
{

}
/**********************************************************************
** ��������         :
** ������           :liupengcheng
** ��������         :
** �����޸���       :liupengcheng
** ����޸�����     :
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void PROCESS_LongPush_DownKey_Of_Page_Body_Resistance(void)
{

}


/*
* ������������
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
** ��������         : BoxConfig
** ������           : liupengcheng
** ��������         : 2017/9/7 15:40
** �����޸���       : liupengcheng
** ����޸�����      : 2017/9/7 15:40
** ��������         : ��������ڵ���������
** ��ڲ���         : none
** ���ز���         : none
** ��ע/ע��        :
** QQ              : 1240612852
***********************************************************************/
void BoxConfig(void)
{
	memset(KeyValueBox_Struct, 2, 10 * sizeof(KeyValueBox_Struct));
}
/**********************************************************************
** ��������         :SendKeyValToBox
** ������           :liupengcheng
** ��������         :2017/9/7 15:40
** �����޸���       :liupengcheng
** ����޸�����      :2017/9/7 15:40
** ��������         :������������һ���ʼ���ǰ����ʼ����λ��
** ��ڲ���         :
					--sendDate:�ʼ����������
** ���ز���         :none
** ��ע/ע��        :
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
** ��������         :
** ������           :liupengcheng
** ��������         :2017/9/7 15:40
** �����޸���       :liupengcheng
** ����޸�����      :2017/9/7 15:40
** ��������         :
** ��ڲ���         :
** ���ز���         :
** ��ע/ע��        :
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
			/************������ʼ�ɾ���󣬽����ݷ���********/
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
**��������        ��KeyScanMain
**������          ��liupengcheng
**��������        ��2017-9-7
**�����޸���      ��liupengcheng
**����޸�����    ��2017-9-7
**��������        ����ѯɨ�赱ǰ����������ɨ��ļ�ֵ�ŵ�Box��������ȥ
**��ڲ���        ��none
**���ز���        ��none
**��ע/ע��       ������ɨ�����������10ms��ѯһ�Σ�longPressSignalΪ��������ʱ��ɨ�赽�Ĵ���
**QQ             ��1240612852
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
                //����press��Ϣ
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
//������    ��OLED_Update_Task
//�޸���    ��liupengcheng
//�޸�ʱ��  ��2017-8-28
**��������  ����ѯBox���������ֵ�������ֵ�û�ȡ�����������ݼ�ֵ���½���
//��ڲ���  ��none
//����ֵ    ��none
//��ע     ������ӿ�--�������
//��ϵ��ʽ   ��1240612852
**********************************************/
void LcdUpdateMain()
{


	e_Trigger_Key = KEY_NONE_Enum;				   //û�м�ֵ��ʱ�򣬵�ǰ����ΪKey_None
	e_Trigger_Key = GetKeyValFromBox();        //��������ȡ��һ����ֵ



	//�ް�������Ӧ
	if (e_Trigger_Key == KEY_NONE_Enum)
	{

	}
	//�̰�����Ӧ��Ӧ
	else if (0x00 == (e_Trigger_Key & 0x80))
	{
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_ShortKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1]();  //�������Ӧ�̰���������ִ��
			}
	}
	//����������ʱ�̶�Ӧ��Ӧ
	else if(0xc0 == (e_Trigger_Key & 0xc0))
	{

			e_Trigger_Key &= 0x3f;                 //��ȥ���������±�־
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_LongKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1](); //�������Ӧ������������ִ��
			}
	}
	//�������ɿ�ʱ�̶�Ӧ��Ӧ
	else if (0x80 == (e_Trigger_Key & 0x80))
	{
			//TRACE("e_Trigger_Key:0x%02bx\r\n",e_Trigger_Key);
			e_Trigger_Key &= 0x7f;                 //��ȥ�������ɿ���־
			if (e_Trigger_Key >= (char)KEY_UP_Enum && e_Trigger_Key <= (char)KEY_DOWN_Enum)
			{
				p_LongKeyProcessFunction[e_Current_Page][e_Trigger_Key - 1](); //�������Ӧ������������ִ��
			}
	}

	p_LCDUpdateFunction[e_Current_Page]();



	//UG_FillScreen(C_WHITE);        //����
}
#endif





