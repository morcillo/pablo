/**
 * @file matrix.h
 * @brief Types and macros for matrix
 * @author Pablo Cottens (pablo.cottens.87@gmail.cop)
 * @version 1.0
 */

#include <stdint.h>

/**
 * @def MATRIX_LINES
 * @details For the first version of this file it was decided that 
 * the maximum matrix size would be fixed to 3x3. Later versions might include 
 * variable definition of said matrix. 
 */
#define MATRIX_LINES 3
#define MATRIX_ROWS  3

typedef struct {
	uint32_t matrix1[MATRIX_ROWS][MATRIX_LINES];
	uint32_t matrix2[MATRIX_ROWS][MATRIX_LINES];
	uint32_t result[MATRIX_ROWS][MATRIX_LINES];
} matrix_t;
