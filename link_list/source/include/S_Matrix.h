/*
 * File Name: S_Matrix.h
 * Authors: Arpit Patel, Dharma KaPatel
 * Date: 2025-03-19
 * Description: This file defines the basic structure and functionalities of the S_Matrix data structure.
 */


#ifndef S_MATRIX_H
#define S_MATRIX_H


// Include necessary headers
#include <stdint.h>
#include <stdlib.h>


/*
 * Struct: m_node
 * ----------------------------
 * Represents a single element in the sparse matrix.
 *
 * row: The row index of the element.
 * column: The column index of the element.
 * value: The value of the element.
 * row_ptr: Pointer to the next element in the same row.
 * col_ptr: Pointer to the next element in the same column.
 */
typedef struct m_node {
        uint32_t row;
        uint32_t column;
        double value;
        struct m_node* row_ptr;
        struct m_node* col_ptr;
} m_node;


/*
 * Struct: l_node
 * ----------------------------
 * Represents a node in a doubly linked list.
 *
 * matrix_node: Pointer to a matrix node.
 * next: Pointer to the next node in the list.
 * prev: Pointer to the previous node in the list.
 */
typedef struct l_node {
        m_node* matrix_node;
        struct l_node* next;
        struct l_node* prev;
} l_node;


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
        l_node** rowList;
        l_node** columnList;
        uint32_t row;
        uint32_t col;
} matrix;


/*
 * Function: create_list_node
 * ----------------------------
 * Creates and initializes a list node.
 *
 * @return Pointer to the list node, or NULL if allocation fails.
 *
 * Description:
 *   Allocates memory for the list node and initializes its next and prev pointers to NULL.
 */
l_node* create_list_node();


/*
 * Function: create_mat_node
 * ----------------------------
 * Creates and initializes a matrix node with the given row, column, and value.
 *
 * @param row - Row index of the node.
 * @param col - Column index of the node.
 * @param value - Value to be stored in the node.
 *
 * @return Pointer to the matrix node, or NULL if allocation fails.
 *
 * Description:
 *   Allocates memory for the matrix node and initializes its row, column, and value.
 *   Sets row_ptr and col_ptr to NULL.
 */
m_node* create_mat_node(uint32_t row, uint32_t col, double value);


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


/*
 * Function: insert_data
 * ----------------------------
 * Inserts a value at the specified row and column in the matrix.
 *
 * @param M - Pointer to the matrix.
 * @param row - Row index.
 * @param column - Column index.
 * @param value - Value to be inserted.
 *
 * Description:
 *   Inserts the value at the specified position in the sparse matrix.
 */
void insert_data(matrix* M, uint32_t row, uint32_t column, double value);





#endif // S_MATRIX_H
