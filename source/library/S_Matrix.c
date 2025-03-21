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
 * Function: create_list_node
 * ----------------------------
 * Creates and initializes a list node.
 *
 * @return Pointer to the list node, or NULL if allocation fails.
 *
 * Description:
 *   Allocates memory for the list node and initializes its next and prev pointers to NULL.
 */
l_node* create_list_node() {
        l_node* list_node = (l_node*)malloc(sizeof(l_node)); // Fixed: Correct allocation size
        if (list_node == NULL) return NULL; // Added: NULL check
        list_node->matrix_node = NULL; // Added: Initialize matrix_node pointer
        list_node->next = NULL;
        list_node->prev = NULL;
        return list_node; // Added: Return statement
}
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
m_node* create_mat_node(uint32_t row, uint32_t col, double value){
        m_node* mat_node = (m_node*)malloc(sizeof(m_node)); // Fixed: Correct allocation size
        if (mat_node == NULL) return NULL; // Added: NULL check
        mat_node->value = value;
        mat_node->row = row;
        mat_node->column = col; // Fixed: Use col parameter, not column
        mat_node->row_ptr = NULL;
        mat_node->col_ptr = NULL;
        return mat_node; // Fixed: Return mat_node, not m_node
}
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
        
        // Allocate memory for rowList array (array of pointers to l_node)
        M->rowList = (l_node**)calloc(rows, sizeof(l_node*)); // Fixed: Properly allocate array
        if (M->rowList == NULL) {
                free(M);
                return NULL;
        }
        
        // Allocate memory for columnList array (array of pointers to l_node)
        M->columnList = (l_node**)calloc(columns, sizeof(l_node*)); // Fixed: Properly allocate array
        if (M->columnList == NULL) {
                free(M->rowList);
                free(M);
                return NULL;
        }
        
        return M;
}
/*
 * Function: insert_data
 * ----------------------------
 * Inserts a value at the specified row and column in the matrix.
 *
 * @param M - Pointer to the matrix.
 * @param row - Row index.
 * @param col - Column index.
 * @param value - Value to be inserted.
 */
void insert_data(matrix* M, uint32_t row, uint32_t col, double value){
        if (M == NULL || row >= M->row || col >= M->col) return; // Added: Boundary check
        
        m_node* new_mat_node = create_mat_node(row, col, value); // Fixed: Use create_mat_node instead of create_node
        if (new_mat_node == NULL) return;
        
        // Add code to insert the node into the matrix structure
        // This is a basic implementation - you may need to extend this
        l_node* new_row_node = create_list_node();
        if (new_row_node == NULL) {
                free(new_mat_node);
                return;
        }
        new_row_node->matrix_node = new_mat_node;
        
        // Link into row list
        if (M->rowList[row] == NULL) {
                M->rowList[row] = new_row_node;
        } else {
                // Insert at the beginning of the list for simplicity
                new_row_node->next = M->rowList[row];
                M->rowList[row]->prev = new_row_node;
                M->rowList[row] = new_row_node;
        }
        
        // Create another list node for column list
        l_node* new_col_node = create_list_node();
        if (new_col_node == NULL) {
                // Handle error (in a real implementation, you'd need to clean up previous allocations)
                return;
        }
        new_col_node->matrix_node = new_mat_node;
        
        // Link into column list
        if (M->columnList[col] == NULL) {
                M->columnList[col] = new_col_node;
        } else {
                // Insert at the beginning of the list for simplicity
                new_col_node->next = M->columnList[col];
                M->columnList[col]->prev = new_col_node;
                M->columnList[col] = new_col_node;
        }
}
