/*
 * File Name: S_Matrix.h
 * Authors: Arpit Patel, Dharma KaPatel
 * Date: 2025-03-19
 * Description: This file defines the basic structure and functionalities of the S_Matrix data structure.
 */


#ifndef _S_MATRIX_H
#define _S_MATRIX_H

// Include necessary headers
#include <stdint.h>
#include <stdlib.h>


/*
 * Struct: node
 * ----------------------------
 * Represents a single element in the sparse matrix.
 * 
 * row: The row index of the element.
 * column: The column index of the element.
 * value: The value of the element.
 * row_ptr: Pointer to the next element in the same row.
 * col_ptr: Pointer to the next element in the same column.
 */
typedef struct node {

	uint32_t row;
	uint32_t column;
	double value;
	struct node* row_ptr;
	struct node* col_ptr;

} node;


/*
 * Struct: matrix
 * ----------------------------
 * Represents the sparse matrix structure.
 * 
 * rowList: Array of pointers to the first node in each row.
 * columnList: Array of pointers to the first node in each column.
 * row: The number of rows in the matrix.
 * col: The number of columns in the matrix.
 */
typedef struct matrix {

	node** rowList;
	node** columnList;
	uint32_t row;
	uint32_t col;

} matrix;


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
matrix* create_S_Matrix(uint32_t rows, uint32_t columns);


#endif // _S_MATRIX_H
