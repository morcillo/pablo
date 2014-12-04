/**
 * @file main.c
 * @author Pablo Cottens (pablo.cottens.87@gmail.com)
 * @brief Main file for task 2
 * 
 * In this task we have to:
 * 	- Create 10 "variables", which will be simulated in software by a random generator;
 * 	- Monitor the variables with another task every 5 seconds;
 * 	- Put those readings in a buffer for each one of them. maximum buffer size = 100;
 * 	- Supervisory. Read the minimum, average and maximum of each variable. Each of these calculation mst be a different task;
 */

#include <stddef.h>
#include <stdint.h>
#include <pthread.h>
#include "variables.h"

#define VARIABLES_AMOUNT 10
#define CALCULATIONS_AMOUNT	VARIABLES_AMOUNT*3
#define SUPERVISORY_THREAD_COUNT 1
#define TOTAL_THREADS (VARIABLES_AMOUNT+CALCULATIONS_AMOUNT+SUPERVISORY_THREAD_COUNT)

typedef struct {
	double variable;
	pthread_mutex_t mutex;
} argument_t;


pthread_mutex_t mutex[10];

pthread_t threads[VARIABLES_AMOUNT + CALCULATIONS_AMOUNT + SUPERVISORY_THREAD_COUNT];

argument_t arg[10];

static void initarg(void) {
	uint32_t i;

	for(i = 0; i < VARIABLES_AMOUNT; i++) {
		arg[i].mutex    = mutex[i];
		arg[i].variable = var[i];
	}

}
int main(void) {
	uint32_t i;

	initarg();

	for(i = 0; i < VARIABLES_AMOUNT; i++) {
		pthread_create(&threads[i], NULL, Variables_Update, (void *)&arg[i]);
		pthread_join(threads[i], NULL);
	}
}