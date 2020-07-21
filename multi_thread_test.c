/**
  ******************************************************************************
  * @file    multi_thread_test.c
  * @author  swq
  * @version 20200617
  * @brief   multi-thread function test for this fifo(using pthread library)
  * @history
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <pthread.h>
#include "fifo.h"

/* Private variables ---------------------------------------------------------*/
FIFO fifo;
pthread_mutex_t mutex = PTHREAD_DEFAULT_MUTEX_INITIALIZER;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  producer thread
  * @param  param-default parameter
  */
void *producer(void *param)
{
	unsigned short input_data = 0;
	while (input_data <= 10000) {
		pthread_mutex_lock(&mutex);
		if (!fifo_full(&fifo)) {
			fifo_write(&fifo, (char *)&input_data, 2);
			input_data++;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

/**
  * @brief  consumer thread
  * @param  param-default parameter
  */
void *consumer(void *param)
{
	unsigned short output_data = 0;
	unsigned short last_data = 0;
	while (output_data < 10000) {
		pthread_mutex_lock(&mutex);
		if (!fifo_empty(&fifo)) {
			fifo_read(&fifo, (char *)&output_data, 2);
			if (output_data != last_data)
				printf("error. data: %d, last: %d.\n", output_data, last_data);
			last_data = output_data + 1;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

/**
  * @brief  main
  */
int main()
{
	//multi-thread test(using pthread library)
	pthread_t producer_thread;
	pthread_t consumer_thread;

	pthread_mutex_init(&mutex, PTHREAD_MUTEX_DEFAULT);
	for (int i = 0; i < 1000; i++) {
		fifo_init(&fifo);
		pthread_create(&producer_thread, NULL, producer, NULL);
		pthread_create(&consumer_thread, NULL, consumer, NULL);
		pthread_join(producer_thread, NULL);
		pthread_join(consumer_thread, NULL);
		printf("%d\n", i);
	}
	pthread_mutex_destroy(&mutex);

	return 0;
}

/************************ (C) COPYRIGHT  ***********************END OF FILE****/
