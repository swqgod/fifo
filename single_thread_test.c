/**
  ******************************************************************************
  * @file    single_thread_test.c
  * @author  swq
  * @version 20200617
  * @brief   single-thread function test for this fifo
  * @history
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "fifo.h"

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  main
  */
int main()
{
	//single thread test
	FIFO fifo;
	unsigned short input_data = 0;
	unsigned short output_data = 0;
	unsigned short last_data = 0;

	fifo_init(&fifo);
	for (int i = 0; i < 10000; i++) {
		if (!fifo_full(&fifo)) {
			fifo_write(&fifo, (char *)&input_data, sizeof(input_data));
			input_data++;
		}
		if (!fifo_full(&fifo)) {
			fifo_write(&fifo, (char *)&input_data, sizeof(input_data));
			input_data++;
		}
		fifo_read(&fifo, (char *)&output_data, sizeof(input_data));
		if (output_data != last_data)
			printf("error. index: %d, data: %d, last: %d.\n", i, output_data, last_data);
		last_data = output_data + 1;
	}
}

/************************ (C) COPYRIGHT  ***********************END OF FILE****/
