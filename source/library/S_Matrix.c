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

	M->row = rows;
	M->col = columns;

	

	return M;

}


node* create_node(uint32_t row, uint32_t col, double value){

	node* m_node = (node*)malloc(sizeof(node*));

	m_node->value = value;
	m_node->row = row;
	m_node->column = column;
	m_node->row_ptr = NULL;
	m_node->col_ptr = NULL;

	return m_node;

}


void insert_data(matrix* M, uint32_t row, uint32_t col, double value){

	node* new_node = create_node(row, col, data);



}
