/**
 * @file variables.c
 * @author Pablo Cottens (pablo.cottens.87@gmail.com)
 * @brief Functions related to the creation of the variables is here. 
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

double var[10];

void Variables_Update(void *structure){
	double *variable = (double *)structure->var;
	while(1) {
		sleep(5);
		pthread_mutex_lock(mutex);
	}
}