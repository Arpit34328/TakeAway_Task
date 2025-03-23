/*
 * File Name: S_Matrix.h
 * Authors: Arpit Patel, Dharma KaPatel
 * Date: 2025-03-19
 * Description: This file defines the basic structure and functionalities of the S_Matrix data structure.
 *              The S_Matrix is a sparse matrix implementation using linked lists for efficient storage.
 */


#ifndef S_MATRIX_H
#define S_MATRIX_H


// Include necessary headers
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


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
 * Represents a node in a linked list.
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
 * Struct: link_list
 * ----------------------------
 * Represents a linked list to store nodes.
 *
 * head: Pointer to the first node in the list.
 * tail: Pointer to the last node in the list.
 * size: Number of nodes in the list.
 */
typedef struct link_list {
        l_node* head;
        l_node* tail;
        uint32_t size;
} link_list;


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
        link_list* rowList;
        link_list* columnList;
        uint32_t row;
        uint32_t col;
} matrix;


/*
 * Function: create_l_node
 * ----------------------------
 * Creates and initializes a linked list node with the given matrix node data.
 *
 * @param data - Pointer to the matrix node to be stored in the linked list node.
 *
 * @return Pointer to the linked list node, or NULL if allocation fails.
 */
l_node* create_l_node(m_node* data);


/*
 * Function: add_list_node
 * ----------------------------
 * Adds a new node to the end of the linked list.
 *
 * @param ll - Pointer to the linked list.
 * @param data - Pointer to the matrix node to be stored in the new list node.
 */
void add_list_node(link_list* ll, m_node* data);


/*
 * Function: create_link_list
 * ----------------------------
 * Creates and initializes a new linked list.
 *
 * @return Pointer to the linked list, or NULL if allocation fails.
 */
link_list* create_link_list();


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
 *   If the position already contains a value, it updates the existing value.
 */
void insert_data(matrix* M, uint32_t row, uint32_t column, double value);


/*
 * Function: duplicatevalue
 * ----------------------------
 * Checks if a specific value exists in the matrix.
 *
 * @param M - Pointer to the matrix.
 * @param value - Value to search for.
 *
 * @return true if the value exists, false otherwise.
 */
bool duplicatevalue(matrix* M, double value);


/*
 * Function: resize
 * ----------------------------
 * Resizes the matrix by doubling its dimensions.
 *
 * @param M - Pointer to the matrix.
 *
 * @return true if resizing is successful, false otherwise.
 */
bool resize(matrix* M);


/*
 * Function: transpose
 * ----------------------------
 * Transposes the matrix, swapping rows and columns.
 *
 * @param M - Pointer to the matrix.
 *
 * @return true if transposition is successful, false otherwise.
 */
bool transpose(matrix* M);


/*
 * Function: displayMatrix
 * ----------------------------
 * Displays the matrix contents in a formatted manner.
 *
 * @param M - Pointer to the matrix.
 */
void displayMatrix(matrix* M);


/*
 * Function: free_S_Matrix
 * ----------------------------
 * Frees all memory associated with the matrix.
 *
 * @param M - Pointer to the matrix.
 */
void free_S_Matrix(matrix* M);


#endif // S_MATRIX_H
