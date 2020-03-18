#include "datastruct.h"
#include "fifo.h"

//全局参数
//UG_GUI g_gui_config_structure;

uint8_t g_Uart3_DevideFrame_Fifo_Buffer[UART3_FIFOBUF_LENGTH];      //循环缓存 接收上位机发送下来的下行报文
struct fifo g_Uart3_DevideFrame_Fifo;

uint8_t g_Devide_Frame_Task_FSM_Buf[DEVIDE_FRAME_TASK_FSM_BUF_LENGTH];                   //方便调试从512设置成64
Devide_Frame_Task_FSM_Typedef g_Devide_Frame_Task_FSM;      //分帧线程状态机  Finite status machine
Status_Of_Triggle_Send_Task_Typedef  Status_Of_Triggle_Send_Task  =  Preparing_Animation_Data_Status;

//这是供drive_port_test.c文件使用的全局变量
__align(4) char buf_read[NUMBER_OF_BLOCKS * BLOCK_SIZE] = {0};
__align(4) char buf_write[NUMBER_OF_BLOCKS * BLOCK_SIZE] = {0};




Motor_Coordinate_typedef  Motor_Coordinate_Array[2][12] =  \
{    \
   {{0,0,-100},{0,1,-100},{0,2,-100},{1,0,-100},{1,1,-100},{1,2,-100},{2,0,-100},{2,1,-100},{2,2,-100},{3,0,-100},{3,1,-100},{3,2,-100}},   \
   {{0,0,-90000},{0,1,-90000},{0,2,-90000},{1,0,-90000},{1,1,-90000},{1,2,-90000},{2,0,-90000},{2,1,-90000},{2,2,-90000},{3,0,-90000},{3,1,-90000},{3,2,-90000}},   \

};


Coordinate_and_ID_Typedef Coordinate_and_ID_Struct[3][4] =   \
{   \
   {{0,0,1},{1,0,4},{2,0,7},{3,0,10}},  \
   {{0,1,2},{1,1,5},{2,1,8},{3,1,11}},  \
   {{0,2,3},{1,2,6},{2,2,9},{3,2,12}},  \
};

//”指令“在枚举和字符串之间的转换表
Cmd_form_typedef Cmd_form_struct[] =
{
    {Cmd_dev,   "dev"},
    {Cmd_sts,   "sts"},
    {Cmd_cfg,   "cfg"},
    {Cmd_ena,   "ena"},
    {Cmd_off,   "off"},
    {Cmd_mov,   "mov"},
    {Cmd_pos,   "pos"},
    {Cmd_org,   "org"},
    {Cmd_stp,   "stp"},
    {Cmd_zero,  "zero"},
    {Cmd_sav,   "sav"},
    {Cmd_demo,  "demo"},
};


//‘参数类型’在枚举和字符串之间的转换表
Para_Type_form_typedef Para_Type_form_Strcut[]=
{
    {Para_bdr,     "bdr"    },
    {Para_cid,     "cid"    },
    {Para_mcs,     "mcs"    },
    {Para_spd,     "spd"    },
    {Para_acc,     "acc"    },
    {Para_dec,     "dec"    },
    {Para_cra,     "cra"    },
    {Para_crn,     "crn"    },
    {Para_crh,     "crh"    },
    {Para_s1f,     "s1f"    },
    {Para_s1r,     "s1r"    },
    {Para_s2f,     "s2f"    },
    {Para_s2r,     "s2r"    },
    {Para_s3f,     "s3f"    },
    {Para_s3r,     "s3r"    },
    {Para_zmd,     "zmd"    },
    {Para_snr,     "snr"    },
    {Para_osv,     "osv"    },
    {Para_zsd,     "zsd"    },
    {Para_zsp,     "zsp"    },
    {Para_dmd,     "dmd"    },
    {Para_dar,     "dar"    },
    {Para_pas,     "pas"    },
    {Para_res,     "res"    },
    {Para_value,   ""       },
    {Para_start,   "start"  },
    {Para_stop,    "start"  },
    {Para_add,     "add"    },
    {Para_clear,   "clear"  },
};







