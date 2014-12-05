/**
 * @file main.c
 * @author Pablo Cottens (pablo.cottens.87@gmail.com)
 * @version 1.0
 * 
 * @brief Resolution of exercise 2
 * @details In this file lies the resolution of exercise 2. 
 * 
 * The exercise requires that 10 random variables to be simulated and monitored every 5 seconds. 
 * After that it is required that there is a method to calculate its minimum, average and maximum, also to maintain a
 * story of the last 100 values.
 * 
 * The exercise requires that the supervisory be implemented in C, making use
 * of threads (pthread library).  
 * 
 * Which means:
 *     - One thread per variable update = 10 threads;
 * 	- One thread per variable per mathrmatical operation (minimum, average, maximum) = 30 threads;
 * 	- One thread to read all the data and display it for the user (supervisory) = 1 thread
 */

#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <stddef.h> 
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

#define NUM_OF_VARIABLES 10
#define NUM_OF_THREADS 	(NUM_OF_VARIABLES+NUM_OF_VARIABLES*3+1)
#define NUM_OF_DATAS   	NUM_OF_THREADS

typedef struct {
	uint32_t min;
	uint32_t avg;
	uint32_t max;
} varData_t;

uint32_t variable0;
uint32_t variable1;
uint32_t variable2;
uint32_t variable3;
uint32_t variable4;
uint32_t variable5;
uint32_t variable6;
uint32_t variable7;
uint32_t variable8;
uint32_t variable9;

uint32_t storevar0[100];
uint32_t storevar1[100];
uint32_t storevar2[100];
uint32_t storevar3[100];
uint32_t storevar4[100];
uint32_t storevar5[100];
uint32_t storevar6[100];
uint32_t storevar7[100];
uint32_t storevar8[100];
uint32_t storevar9[100];

pthread_mutex_t mutexvar0;
pthread_mutex_t mutexvar1;
pthread_mutex_t mutexvar2;
pthread_mutex_t mutexvar3;
pthread_mutex_t mutexvar4;
pthread_mutex_t mutexvar5;
pthread_mutex_t mutexvar6;
pthread_mutex_t mutexvar7;
pthread_mutex_t mutexvar8;
pthread_mutex_t mutexvar9;

pthread_t threads[NUM_OF_THREADS];

varData_t dataVar0 = {0, 0, 0};
varData_t dataVar1 = {0, 0, 0};
varData_t dataVar2 = {0, 0, 0};
varData_t dataVar3 = {0, 0, 0};
varData_t dataVar4 = {0, 0, 0};
varData_t dataVar5 = {0, 0, 0};
varData_t dataVar6 = {0, 0, 0};
varData_t dataVar7 = {0, 0, 0};
varData_t dataVar8 = {0, 0, 0};
varData_t dataVar9 = {0, 0, 0};

#define REGISTER_STRUCT(index)  {&mutexvar##index, &variable##index, &storevar##index, &dataVar##index, -1, "var" #index "\0"}				

typedef struct {
	pthread_mutex_t *mutex;
	uint32_t *variable;
	uint32_t *store;
	varData_t *data;
	int32_t index;
	char name[4];
} system_t;

/**
 * @brief Registers all structures to be passed via parameter to the threads. 
 */
system_t sys[NUM_OF_THREADS] = 
{
	REGISTER_STRUCT(0),
	REGISTER_STRUCT(1),
	REGISTER_STRUCT(2),
	REGISTER_STRUCT(3),
	REGISTER_STRUCT(4),
	REGISTER_STRUCT(5),
	REGISTER_STRUCT(6),
	REGISTER_STRUCT(7),
	REGISTER_STRUCT(8),
	REGISTER_STRUCT(9), 
	{NULL, NULL, NULL, NULL, -1, "NULL\0"}
};

static void UpdateVar(void *var) {
	system_t *sys = (system_t *)var;
	sys->index = 0;
	while(1){
		sleep(1);
		pthread_mutex_lock(sys->mutex);
		sys->variable = rand();
		sys->store[sys->index++] = sys->variable;
		if(sys->index > 99) sys->index = 0;
		pthread_mutex_unlock(sys->mutex);
	}
}

static void Minimum(void *var){
	system_t *sys = (system_t *)var;
	uint32_t i;
	uint32_t min = 0;
	bool firstTime = true;
	uint32_t index = sys->index;
	while(1) {
		if(sys->index != index && sys->index != -1) {
			pthread_mutex_lock(sys->mutex);
			index = sys->index;
			for(i = 0; i < index; i++) {
				if(firstTime) {
					min = sys->store[i];
					firstTime = false;
				} else {
					if(min > sys->store[i]) {
						min = sys->store[i];
						sys->data->min = min;
					}
				}
			}
			pthread_mutex_unlock(sys->mutex);
		}
	}
}

static void Maximum(void *var){
	system_t *sys = (system_t *)var;
	uint32_t i;
	uint32_t max;
	bool firstTime = true;
	uint32_t index = sys->index;
	while(1) {
		if(sys->index != index && sys->index != -1) {
			pthread_mutex_lock(sys->mutex);
			index = sys->index;
			for(i = 0; i < index; i++) {
				if(firstTime) {
					max = sys->store[i];
					firstTime = false;
				} else {
					if(sys->store[i] > max) {
						max = sys->store[i];
						sys->data->max = max;
					}
				}
			}
			pthread_mutex_unlock(sys->mutex);
		}
	}
}

static void Average(void *var){
	system_t *sys = (system_t *)var;
	uint32_t i;
	int32_t index = sys->index;
	uint32_t sum;
	uint32_t avg;
	while(1){
		if(sys->index != index && sys->index != -1) {
			pthread_mutex_lock(sys->mutex);
			index = sys->index;
			for(i = 0; i < index; i++) {
				sum += sys->store[i];
			}
			avg = sum/(index+1);
			sys->data->avg = avg;

			pthread_mutex_unlock(sys->mutex);
		}		
	}
}

#define PRINT_SUPERVISORY(var)	printw("Variable: %s \t Min: %d \t Avg: %d \t Max: %d \n", var.name, var.data->min, var.data->avg, var.data->max)

static void Supervisory(void *var) {
	system_t *sys = (system_t *)var;
	uint8_t i, j;
	initscr();
	while(1){
		sleep(2);
		for(i = 0; i < NUM_OF_VARIABLES; i++) {
			pthread_mutex_lock(sys[i].mutex);	
		}
		clear();
		printw("Supervisory\n");
		for(i = 0; i < NUM_OF_VARIABLES; i ++) {
				printw("Variable %c", &sys[i].name);
				printw(", min %d,  avg %d, max %d\n", sys[i].data->min, sys[i].data->avg, sys[i].data->max);
		}
		printw("\n");
		for (i = 0 ; i < 0; i++) {
			for (j = 0; j < 100; j++){
				printw("store %d   %d \n", j, sys[i].store[j]);
			}
		}
		refresh();
		for(i = 0; i < NUM_OF_VARIABLES; i++) {
			pthread_mutex_unlock(sys[i].mutex);	
		}
	}
}

int main(void) {
	uint32_t i;

	for(i = 0; i < NUM_OF_VARIABLES; i++) {
		pthread_create(&threads[4*i], NULL, UpdateVar, (void *)&sys[i]);
		pthread_create(&threads[i*4+1], NULL, Minimum, (void *)&sys[i]);
		pthread_create(&threads[i*4+2], NULL, Maximum, (void *)&sys[i]);
		pthread_create(&threads[i*4+3], NULL, Average, (void *)&sys[i]);
	}

	pthread_create(&threads[NUM_OF_THREADS-1], NULL, Supervisory, (void *)&sys);

	pthread_join(threads[i+1], NULL);
	pthread_join(threads[4*i], NULL);
	pthread_join(threads[i+2], NULL);
    pthread_join(threads[NUM_OF_THREADS-1], NULL);
	pthread_join(threads[i+3], NULL);

    return 0;

}
