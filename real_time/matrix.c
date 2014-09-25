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
#include <stddef.h>
#include <stdint.h>
#include "matrix.h"

pthread_mutex_t mutex;
/*TODO: Change the maximum array size*/
pthread_t threads[MATRIX_ROWS];


//Local functions
/**
 * @brief Verifies tha the function can be  implemented. If not, go to an error state and exit the applciation.
 * 
 * @param col1 Number of columns for matrix 1
 * @param row2 Number of row for matrix 2
 * 
 * @return SUCCESS - (TRUE)if the multiplication can be implemented
 * 		   FAILURE - (FALSE)if multiplication cannot be implemented
 */
static uint8_t CheckMatrixSizes(uint32_t col1, uint32_t row2){
	return col1 == row2;
}

// Main function
int main(void) {
	uint32_t i;
	/*For initial tests matrixes have standard size and values. 
	TODO: implement a method that allows the user to create a matrix in whatever way 
	he/se deems fit for the problem*/
	uint32_t matA[MATRIX_ROWS][MATRIX_ROWS] = {10, 10, 10; 10, 10, 10; 10, 10, 10}
	uint32_t matB[MATRIX_ROWS][MATRIX_ROWS] = {11, 12, 13; 14, 15, 16; 17, 18, 19}

	matrix_t matrix = 
	{
		.matrix1 = matA,
		.matrix2 = matB,
		.mutex = &mutex,
		.rowXline = 0 
	}
	/*Since the most inner numbers that describe the matrix's size must be equal, the
	constant MATRIX_LINES is used. This is possible momentarilly because the initial tests
	are being done on sqaure matrixes.*/
	uint32_t numOfThreads = MATRIX_LINES;

	if(CheckMatrixSizes(MATRIX_LINES, MATRIX_ROWS) == FALSE){
		goto error;
	}


	for(i = 0; i < numOfThreads; i++){
		pthread_create(&threads[i], NULL, matrix_MultRowCol, NULL, (void *)matrix);
		pthread_join(threads[i], NULL);
		matrix.rowXline++;
	}

error:
	printf("Function may not be implemented due to errors in the desired matrix\n")

end:
	printf("Exiting the function\n");
	return 0;
}

/**
 * @fn matrix_MultRowCol
 * @brief Multiplies matrix A's row with Matrix B's columns.
 * 
 * @param arg Void pointer to arg is required for compatibility with pthread.
 * @return NULL if operation was successful. 
 */
void *matrix_MultRowCol(void *arg){
	uint32_t i, j;
	uint32_t temp = 0;
	matrix_t *matrix = (matrix_t *)arg;
	/*Separates the contents of arg into manageable parts*/
	uint32_t row = matrix->rowXline;
	uint32_t matrixA[MATRIX_ROWS][MATRIX_LINES] = matrix->matrix1;
	uint32_t matrixB[MATRIX_ROWS][MATRIX_LINES] = matrix->matrix2;

	pthread_mutex_lock(matrix->mutex);
	for(i = 0; i < row; i++) {
		for(j = 0; j < row; j++) {
			temp = matrixA[i][j] * matrixB[j][i];
		}
	}
	matrix->result[row][row] = temp
	pthread_mutex_unlock(matrix-?>mutex);
}
