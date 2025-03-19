/* 
 * File Name: S_Matrix.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file implements the functions and operations for the S_Matrix data structure.
 */


// Include necessary headers
#include <stdint.h>
#include <stdlib.h>

#include "../include/S_Matrix.h"


/*
 * Function: create_S_Matrix
 * ----------------------------
 * Creates and initializes an S_Matrix with the given rows and columns.
 *
 * @param rows - Number of rows.
 * @param columns - Number of columns.
 *
 * @return Pointer to the matrix, or NULL if allocation fails.
 *
 * Description:
 *   Allocates memory for the matrix and its row and column lists, initializing all pointers to NULL.
 *   Frees allocated memory if any allocation fails.
 */
matrix* create_S_Matrix(uint32_t rows, uint32_t columns){
		
	matrix* M = (matrix*)malloc(sizeof(matrix));

	if (M == NULL) return NULL;

	M->rows = rows;
	M->columns = columns;

	// Allocate rowlist
	M->rowList = (node**)malloc(rows * sizeof(node*));
	if (M->rowList == NULL) {
		free(M);
		return NULL;
	}

	// Allocate columnlist
	M->columnList = (node**)malloc(columns * sizeof(node*));
	if (M->columnList == NULL) {
		free(M->rowList);
		free(M);
		return NULL;
	}

	for (uint32_t row_ind = 0; row_ind < rows; row_ind++) {
		M->rowList[row_ind] = NULL;
	}

	for (uint32_t col_ind = 0; col_ind < columns; col_ind++) {
		M->columnList[col_ind] = NULL;
	}

	return M;

}
