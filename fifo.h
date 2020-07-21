/**
  ******************************************************************************
  * @file    fifo.h
  * @author  swq
  * @version 20200428
  * @brief   缓存队列
  * @history
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIFO_H
#define __FIFO_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
#define     FIFO_LEN    131072
#define     TRUE        1
#define     FALSE       0

/* Exported types ------------------------------------------------------------*/
typedef struct FIFO {
	uint32_t m_head;
	uint32_t m_tail;
	uint8_t m_full;
	uint8_t m_empty;
	uint8_t m_buffer[FIFO_LEN];
} FIFO;

/* Exported macro ------------------------------------------------------------*/
#define fifo_empty(fifo) ((fifo)->m_empty)
#define fifo_full(fifo) ((fifo)->m_full)

/* Exported functions --------------------------------------------------------*/
void fifo_init(FIFO *fifo);
uint32_t fifo_size(FIFO *fifo);
uint32_t fifo_read(FIFO *fifo, void *buff, uint32_t btr);
uint32_t fifo_write(FIFO *fifo, void *buff, uint32_t btw);

#endif
/************************ (C) COPYRIGHT ************************END OF FILE****/
