/**
 * @file variables.h
 * @author Pablo Cottens (pablo.cottens.87@gmail.com)
 * @brief Functions related to the creation of the variables is here. 
 */

#include <stdint.h>

#ifndef VARIABLES_H
#define VARIABLES_H
 
extern double var[10];

typedef enum {
	variable1 = 0,
	variable2,
	variable3,
	variable4,
	variable5,
	variable6,
	variable7,
	variable8,
	variable9,
	variable10,
} variables_t;

void Variables_Update(void *var);


 
#endif
