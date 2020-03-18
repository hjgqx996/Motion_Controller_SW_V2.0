/******************************************************************************
* @File 	  : ringbuffer.c
* @Author   : cqx
* @Version  : V0.0.1
* @Date 	  : 29-november-2016
* @Brief	  : This file provides all the fifo functions.
******************************************************************************
* @Attention:
*
*
******************************************************************************/
/* Includes -----------------------------------------------------------------*/
#include "fifo.h"
#include "stdlib.h"
#include "string.h"


/* Variables -----------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :internal helper to calculate the unused elements in a fifo
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
static __inline unsigned int fifo_unused(struct fifo *fifo)
{
  return (fifo->mask + 1) - (fifo->in - fifo->out);
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
unsigned int Fifo_Used(struct fifo *fifo)
{
  return (fifo->in - fifo->out);
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
signed int Fifo_Alloc(struct fifo *fifo, unsigned int size)
{
/*
	 * round down to the next power of 2, since our 'let the indices
	 * wrap' technique works only in this case.
	 */
	if (!is_power_of_2(size))
		return -1;

	fifo->in = 1;
	fifo->out = 1;

	if (size < 2)
    {
		fifo->data = NULL;
		fifo->mask = 0;
		return -1;
	}
	fifo->data = malloc(size);

	if (!fifo->data)
    {
		fifo->mask = 0;
		return -1;
	}
	fifo->mask = size - 1;

  return 0;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
void Fifo_Free(struct fifo *fifo)
{
	free(fifo->data);
	fifo->in = 0;
	fifo->out = 0;
	fifo->data = NULL;
	fifo->mask = 0;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
int Fifo_Init(struct fifo *fifo, unsigned char *buffer, unsigned int size)
{
	if (!is_power_of_2(size))
	{
		return -1;
	}

	fifo->in = 0;
	fifo->out = 0;
	fifo->data = buffer;

	if (size < 2)
    {
		fifo->mask = 0;
		return -1;
	}
	fifo->mask = size - 1;

	return 0;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
static void fifo_copy_in(struct fifo *fifo, unsigned char *src, unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int l;

    /*
     * ȡģ�õ�����ͷ��fifo->data�е�ƫ�Ƶ�ַ
     */
	off &= fifo->mask;

	l = MIN(len, size - off);

	memcpy(fifo->data + off, src, l);
	memcpy(fifo->data, src + l, len - l);
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
unsigned int Fifo_In(struct fifo *fifo, unsigned char *buf, unsigned int len)
{
	unsigned int l;

	l = fifo_unused(fifo);

    /*
     * ���len����ʣ����������ֻ��Դbuf��copy l���ȵ����ݡ�
     */
	if (len > l)
	{
		len = l;
	}

	fifo_copy_in(fifo, buf, len, fifo->in);
	fifo->in += len;

	return len;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
uint8_t *Fifo_Get_Inhandle(struct fifo *fifo)
{
    return fifo->data + (fifo->in & fifo->mask);
}

/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         : ��ȡ���½���ܵ���1�ֽ����� 
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��             :
***********************************************************************/
uint8_t Fifo_Get_Last_In_Data(struct fifo *fifo)
{
    uint8_t *pret;
    uint8_t ret;
    unsigned int off = fifo->in - 1;
    off &= fifo->mask;

    pret = fifo->data + off;
    ret = *(pret);

    return ret;
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
static void fifo_copy_out(struct fifo *fifo, unsigned char *dst, unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int l;

	off &= fifo->mask;
	l = MIN(len, size - off);

	memcpy(dst, fifo->data + off, l);
	memcpy(dst + l, fifo->data, len - l);
}


/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
unsigned int fifo_out_peek(struct fifo *fifo, unsigned char *buf, unsigned int len)
{
	unsigned int l;

	l = fifo->in - fifo->out;
	if (len > l)
	{
		len = l;
	}

	fifo_copy_out(fifo, buf, len, fifo->out);
	return len;
}



/**********************************************************************
** ��������         :
** ������           :
** ��������         :
** �����޸���       :
** ����޸�����     :
** ��������         :
** ��ڲ���         :
												--NONE
** ���ز���         :
												--NONE
** ��ע/ע��        :
** ΢��              :
***********************************************************************/
unsigned int Fifo_Out(struct fifo *fifo, unsigned char *buf, unsigned int len)
{
	len = fifo_out_peek(fifo, buf, len);
	fifo->out += len;
	return len;
}

