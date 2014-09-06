/**
 * @file matrix.c
 * @author Pablo Cottens (pablo.cottens.87@gmail.com)
 * @version 1.0
 * 
 * @brief Resolution of exercise 1
 * @details In this file lies the resolution of exercise 1. 
 * 
 * The exercise requires that a matrix multiplier be implemented in C, making use
 * of threads (pthread library). For this, it was decided that each row of the matrix
 * would require one hread for the multiplication.
 * 
 * In the end the result will be written in another matrix by another thread. 
 * 
 * Implementation description:
 * 		- Create structures for the matrixes;
 * 		- The matrix size will be fixed initially to a 3x3 matrix;
 * 		- Create a thread for each numbe of rows in the left most matrix;
 * 		- Create thread for writing the result to another matrix;
 * 		- Implement the multiplication algorithm ;
 * 		- Implement last algorithm for thread;
 * 		- Print the result;
 * 		- Bob's your uncle;
 */

// Include files sector
#include <pthread>
#include <stddef.h>
#include <stdint.h>
#include "matrix.h"

// Global variables
matrix_t matrix;
pthread_mutex_t mutex;
// Function prototypes
void *MultRowCol(void *arg);

// Main function
int main() {

	return 0;
}

// Implementation of above prototypes


