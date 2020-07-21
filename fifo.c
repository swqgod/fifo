/**
  ******************************************************************************
  * @file    fifo.c
  * @author  swq
  * @version 20200428
  * @brief   缓存队列
  * @history
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fifo.h"

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  初始化FIFO
  * @param  fifo-FIFO对象
  */
void fifo_init(FIFO *fifo)
{
	fifo->m_head = 0;
	fifo->m_tail = 0;
	fifo->m_empty = TRUE;
	fifo->m_full = FALSE;
}

/**
  * @brief  获取FIFO中数据长度
  * @param  fifo-FIFO对象
  */
uint32_t fifo_size(FIFO *fifo)
{
	if (fifo->m_full) {
		return FIFO_LEN;
	}
	return (fifo->m_head >= fifo->m_tail) ? (fifo->m_head - fifo->m_tail) : (FIFO_LEN - fifo->m_head + fifo->m_tail);
}

/**
  * @brief  读取FIFO
  * @param  fifo-FIFO对象
  * @param  buffer-缓冲区用于存储读出的数据
  * @param  btr-要读取的字节数
  * @retval 返回读取字节数
  */
uint32_t fifo_read(FIFO *fifo, void *buff, uint32_t btr)
{
	if (fifo->m_empty == 1) {
		return 0;
	}
	if (btr > 0) {
		fifo->m_full = 0;
	}
	for (uint32_t i = 0; i < btr; i++) {
		((uint8_t *)buff)[i] = fifo->m_buffer[fifo->m_tail++];
		if (fifo->m_tail == FIFO_LEN) {
			fifo->m_tail = 0;
		}
		if (fifo->m_tail == fifo->m_head) {
			fifo->m_empty = 1;
			return i + 1;
		}
	}
	return btr;
}

/**
  * @brief  读取FIFO
  * @param  fifo-FIFO对象
  * @param  buffer-指向要写入数据的指针
  * @param  btw-要写入的字节数
  * @retval 返回写入字节数
  */
uint32_t fifo_write(FIFO *fifo, void *buff, uint32_t btw)
{
	if (fifo->m_full == TRUE) {
		return 0;
	}
	if (btw > 0) {
		fifo->m_empty = FALSE;
	}
	for (uint32_t i = 0; i < btw; i++) {
		fifo->m_buffer[fifo->m_head++] = ((uint8_t *)buff)[i];
		if (fifo->m_head == FIFO_LEN) {
			fifo->m_head = 0;
		}
		if (fifo->m_head == fifo->m_tail) {
			fifo->m_full = TRUE;
			return i + 1;
		}
	}
	return btw;
}

/************************ (C) COPYRIGHT  ***********************END OF FILE****/
