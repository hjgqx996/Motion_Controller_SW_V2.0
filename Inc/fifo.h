/*******************************************************************************
* @File 	  : fifo.h
* @Author   : cqx
* @Version  : V0.0.1
* @Date 	  : 29-november-2016
* @Brief	  : This file provides all the fifo functions.
********************************************************************************
* @Attention:
* Non
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FIFO_H
#define _FIFO_H

//#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))

/* Private typedef -----------------------------------------------------------*/
struct fifo
{
	unsigned int in;        //写入buffer数据总量
	unsigned int out;       //从buffer中取出的数据总量
	unsigned int mask;
	uint8_t  *data;
};

/* Function prototypes -------------------------------------------------------*/
extern unsigned int Fifo_Used(struct fifo *fifo);
extern signed int   Fifo_Alloc(struct fifo *fifo, unsigned int size);
extern void         Fifo_Free(struct fifo *fifo);
extern int          Fifo_Init(struct fifo *fifo, unsigned char *buffer,	unsigned int size);
extern unsigned int Fifo_In(struct fifo *fifo, unsigned char *buf, unsigned int len);
extern unsigned int Fifo_Out(struct fifo *fifo,	unsigned char *buf, unsigned int len);
extern uint8_t *Fifo_Get_Inhandle(struct fifo *fifo);
extern uint8_t      Fifo_Get_Last_In_Data(struct fifo *fifo);

#ifdef __cplusplus
}
#endif

#endif

