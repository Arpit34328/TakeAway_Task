/*
 * File Name: S_Matrix.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file implements the functions and operations for the S_Matrix data structure.
 *              The S_Matrix is a sparse matrix implementation that efficiently stores only non-zero values.
 */


// Include necessary headers
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


#include "../include/S_Matrix.h"


/*
 * Function: create_l_node
 * ----------------------------
 * Creates and initializes a linked list node with the given matrix node data.
 *
 * @param data - Pointer to the matrix node to be stored in the linked list node.
 *
 * @return Pointer to the linked list node, or NULL if allocation fails.
 */
l_node* create_l_node(m_node* data) {
        l_node* new_l_node = (l_node*)malloc(sizeof(l_node));
        if (!new_l_node) return NULL;

        new_l_node->matrix_node = data;
        new_l_node->next = NULL;
        new_l_node->prev = NULL;  // Initialize prev pointer

        return new_l_node;
}


/*
 * Function: add_list_node
 * ----------------------------
 * Adds a new node to the end of the linked list.
 *
 * @param ll - Pointer to the linked list.
 * @param data - Pointer to the matrix node to be stored in the new list node.
 */
void add_list_node(link_list* ll, m_node* data) {
        if (!ll) {
                printf("Linked list is not created!\n");
                return;
        }

        l_node* new_node = create_l_node(data);
        if (!new_node) {
                printf("Memory allocation failed!\n");
                return;
        }

        if (!ll->head) {
                ll->head = new_node;
                ll->tail = new_node;
                ll->size = 1;
        } else {
                new_node->prev = ll->tail;  // Set prev pointer
                ll->tail->next = new_node;
                ll->tail = new_node;
                ll->size++;
        }
}


/*
 * Function: create_link_list
 * ----------------------------
 * Creates and initializes a new linked list.
 *
 * @return Pointer to the linked list, or NULL if allocation fails.
 */
link_list* create_link_list() {
        link_list* ll = (link_list*)malloc(sizeof(link_list));  // Corrected size

        if (!ll) return NULL;

        ll->head = NULL;
        ll->tail = NULL;
        ll->size = 0;

        return ll;
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
 */
m_node* create_mat_node(uint32_t row, uint32_t col, double value) {
        m_node* new_m_node = (m_node*)malloc(sizeof(m_node));  // Corrected size

        if (!new_m_node) return NULL;  // Corrected variable name

        new_m_node->row = row;
        new_m_node->column = col;
        new_m_node->value = value;
        new_m_node->row_ptr = NULL;  // Initialize pointers
        new_m_node->col_ptr = NULL;

        return new_m_node;
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
 */
matrix* create_S_Matrix(uint32_t rows, uint32_t columns) {
        matrix* M = (matrix*)malloc(sizeof(matrix));
        if (M == NULL) return NULL;

        M->row = rows;
        M->col = columns;

        // Create row and column lists
        M->rowList = create_link_list();
        M->columnList = create_link_list();

        if (!M->rowList || !M->columnList) {
                // Free allocated memory if creation fails
                if (M->rowList) free(M->rowList);
                if (M->columnList) free(M->columnList);
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
 * @param column - Column index.
 * @param value - Value to be inserted.
 */
void insert_data(matrix* M, uint32_t row, uint32_t column, double value) {
        if (!M) {
                printf("Currently Matrix is not created!!\n");
                return;
        }

        if (value == 0) {
                printf("you can not add 0 in the matrix\n");
                return;
        }

        if (row > M->row || row < 1 || column > M->col || column < 1) {
                printf("Row or Col out of bound\n");
                return;
        }

        m_node* matrix_node = create_mat_node(row, column, value);
        if (!matrix_node) {
                printf("Memory allocation failed!\n");
                return;
        }

        link_list* col_ll = M->columnList;
        link_list* row_ll = M->rowList;

        uint32_t cur_col_size = col_ll->size;
        uint32_t cur_row_size = row_ll->size;

        l_node* col_pos = NULL;
        l_node* row_pos = NULL;

        uint32_t col_index = 0;
        uint32_t row_index = 0;

        m_node* cur_col_ptr = NULL;
        m_node* cur_row_ptr = NULL;

        // Find the Col position where matrix node will add
        if (cur_col_size < column) {
                while (cur_col_size < column) {
                        add_list_node(col_ll, NULL);
                        cur_col_size = col_ll->size;
                }
                col_pos = col_ll->tail;
        } else {
                col_pos = col_ll->head;  // Corrected from col_list to col_ll
                col_index = 1;
                while (col_index < column) {
                        col_pos = col_pos->next;
                        col_index++;
                }
        }

        // Find the Row position where matrix node will add
        if (cur_row_size < row) {
                while (cur_row_size < row) {
                        add_list_node(row_ll, NULL);
                        cur_row_size = row_ll->size;
                }
                row_pos = row_ll->tail;
        } else {
                row_pos = row_ll->head;  // Corrected from row_list to row_ll
                row_index = 1;
                while (row_index < row) {
                        row_pos = row_pos->next;
                        row_index++;
                }
        }

        // Case1: row_pos and col_pos not pointing to any matrix node
        if (!row_pos->matrix_node && !col_pos->matrix_node) {
                col_pos->matrix_node = matrix_node;
                row_pos->matrix_node = matrix_node;
                return;  // Added return for clarity
        }

        bool exist_col_m_node = false;  // Changed from _Bool to bool
        bool exist_row_m_node = false;  // Changed from _Bool to bool

        // Case2: col_pos pointing to any node
        if (col_pos->matrix_node) {
                // Row value less than the first m_node in that col
                if (col_pos->matrix_node->row > row) {
                        matrix_node->col_ptr = col_pos->matrix_node;
                        col_pos->matrix_node = matrix_node;
                } else if (col_pos->matrix_node->row == row) {
                        exist_col_m_node = true;
                        // Update value if node exists
                        if (col_pos->matrix_node->column == column) {
                                col_pos->matrix_node->value = value;
                                free(matrix_node);  // Free the newly created node
                                return;
                        }
                } else {
                        // Row value between or highest in that column
                        cur_col_ptr = col_pos->matrix_node;
                }
        }

        // Case3: row_pos pointing to any node
        if (row_pos->matrix_node) {
                // Col value less than the first m_node in that row
                if (row_pos->matrix_node->column > column) {
                        matrix_node->row_ptr = row_pos->matrix_node;
                        row_pos->matrix_node = matrix_node;
                } else if (row_pos->matrix_node->column == column) {
                        exist_row_m_node = true;
                        // Update value if node exists
                        if (row_pos->matrix_node->row == row) {
                                row_pos->matrix_node->value = value;
                                if (!exist_col_m_node) {  // Only free if not already freed
                                        free(matrix_node);
                                }
                                return;
                        }
                } else {
                        // Row value between or highest in that row
                        cur_row_ptr = row_pos->matrix_node;
                }
        }

        // Case4: m_node in col will add after some nodes or at the end of col
        if (cur_col_ptr) {
                while (cur_col_ptr->col_ptr) {
                        if (cur_col_ptr->col_ptr->row > row) {
                                break;
                        } else if (cur_col_ptr->col_ptr->row < row) {
                                cur_col_ptr = cur_col_ptr->col_ptr;
                        } else {
                                exist_col_m_node = true;
                                // Update value if node exists
                                if (cur_col_ptr->col_ptr->column == column) {
                                        cur_col_ptr->col_ptr->value = value;
                                        free(matrix_node);
                                        return;
                                }
                                break;
                        }
                }
        }

        // Case5: m_node in row will add after some nodes or at the end of row
        if (cur_row_ptr) {
                while (cur_row_ptr->row_ptr) {
                        if (cur_row_ptr->row_ptr->column > column) {
                                break;
                        } else if (cur_row_ptr->row_ptr->column < column) {
                                cur_row_ptr = cur_row_ptr->row_ptr;
                        } else {
                                exist_row_m_node = true;
                                // Update value if node exists
                                if (cur_row_ptr->row_ptr->row == row && !exist_col_m_node) {
                                        cur_row_ptr->row_ptr->value = value;
                                        free(matrix_node);
                                        return;
                                }
                                break;
                        }
                }
        }

        if (exist_col_m_node && exist_row_m_node) {
                printf("Node is already exists\n");
                free(matrix_node);  // Free the node if it already exists
        } else {
                if (cur_col_ptr) {
                        matrix_node->col_ptr = cur_col_ptr->col_ptr;
                        cur_col_ptr->col_ptr = matrix_node;
                }
                if (cur_row_ptr) {
                        matrix_node->row_ptr = cur_row_ptr->row_ptr;
                        cur_row_ptr->row_ptr = matrix_node;
                }
        }
}


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
bool duplicatevalue(matrix* M, double value) {  // Changed _Bool to bool
        if (!M) {
                printf("Currently Matrix is not created!!\n");
                return false;
        }

        if (value == 0) {
                printf("Zero can not be there\n");
                return false;
        }

        link_list* row_ll = M->rowList;
        if (!row_ll) {
                return false;
        }

        l_node* temp = row_ll->head;

        while (temp) {
                m_node* temp_row_ptr = temp->matrix_node;

                while (temp_row_ptr) {
                        if (temp_row_ptr->value == value) {
                                return true;
                        }
                        temp_row_ptr = temp_row_ptr->row_ptr;
                }
                temp = temp->next;
        }

        return false;
}


/*
 * Function: resize
 * ----------------------------
 * Resizes the matrix by doubling its dimensions.
 *
 * @param M - Pointer to the matrix.
 *
 * @return true if resizing is successful, false otherwise.
 */
bool resize(matrix* M) {  // Changed _Bool to bool
        if (!M) {
                printf("Currently Matrix is not created!!\n");
                return false;
        }

        // Double the matrix size
        M->row *= 2;
        M->col *= 2;

        return true;
}


/*
 * Function: transpose
 * ----------------------------
 * Transposes the matrix, swapping rows and columns.
 *
 * @param M - Pointer to the matrix.
 *
 * @return true if transposition is successful, false otherwise.
 */
bool transpose(matrix* M) {  // Changed _Bool to bool
        if (!M) {
                printf("Currently Matrix is not created!!\n");
                return false;
        }

        // Swapping the size values
        M->row = M->col + M->row;
        M->col = M->row - M->col;
        M->row = M->row - M->col;

        // Swapping the pointers of list
        link_list* temp = M->rowList;  // Corrected from list_node* to link_list*
        M->rowList = M->columnList;
        M->columnList = temp;

        link_list* row_ll = M->rowList;
        if (!row_ll) {
                return true;  // No nodes to transpose
        }

        l_node* temp_node = row_ll->head;

        while (temp_node) {
                m_node* temp_row_ptr = temp_node->matrix_node;
                while (temp_row_ptr) {
                        // Swap row and column of each node
                        uint32_t temp_val = temp_row_ptr->row;
                        temp_row_ptr->row = temp_row_ptr->column;
                        temp_row_ptr->column = temp_val;
                        
                        // Swap row_ptr and col_ptr of each node
                        m_node* temp_ptr = temp_row_ptr->row_ptr;
                        temp_row_ptr->row_ptr = temp_row_ptr->col_ptr;
                        temp_row_ptr->col_ptr = temp_ptr;
                        
                        temp_row_ptr = temp_row_ptr->row_ptr;
                }
                temp_node = temp_node->next;
        }

        return true;
}


/*
 * Function: displayMatrix
 * ----------------------------
 * Displays the matrix contents in a formatted manner.
 *
 * @param M - Pointer to the matrix.
 */
void displayMatrix(matrix* M) {
        printf("\n--------Current Matrix--------\n");
        if (!M) {
                printf("Not Created\n");
                return;
        }

        link_list* row_ll = M->rowList;
        if (!row_ll) {
                printf("Row list not initialized\n");
                return;
        }

        l_node* temp = row_ll->head;

        uint32_t row_index = 1;

        if (temp) {
                while (temp && row_index <= M->row) {
                        uint32_t col_index = 1;
                        m_node* temp_row_ptr = temp->matrix_node;
                        
                        while (col_index <= M->col) {
                                if (temp_row_ptr && temp_row_ptr->column == col_index) {
                                        printf("%5.1f", temp_row_ptr->value);  // Changed to %5.1f for double values
                                        temp_row_ptr = temp_row_ptr->row_ptr;
                                } else {
                                        printf("%5.1f", 0.0);  // Changed to %5.1f for double values
                                }
                                col_index++;
                        }
                        
                        printf("\n");
                        temp = temp->next;
                        row_index++;
                }
                
                // Print remaining rows if any
                while (row_index <= M->row) {
                        for (uint32_t col_index = 1; col_index <= M->col; col_index++) {
                                printf("%5.1f", 0.0);  // Changed to %5.1f for double values
                        }
                        printf("\n");
                        row_index++;
                }
        } else {
                // Print all zeros if no nodes exist
                for (row_index = 1; row_index <= M->row; row_index++) {
                        for (uint32_t col_index = 1; col_index <= M->col; col_index++) {
                                printf("%5.1f", 0.0);  // Changed to %5.1f for double values
                        }
                        printf("\n");
                }
        }
}


/*
 * Function: free_S_Matrix
 * ----------------------------
 * Frees all memory associated with the matrix.
 *
 * @param M - Pointer to the matrix.
 */
void free_S_Matrix(matrix* M) {
        if (!M) {
                return;
        }

        link_list* row_ll = M->rowList;
        if (!row_ll) {
                free(M->columnList);
                free(M);
                return;
        }

        link_list* col_ll = M->columnList;
        l_node* temp = row_ll->head;
        l_node* back_node = NULL;

        // Free all matrix nodes through row list only
        while (temp) {
                back_node = temp;
                m_node* temp_row_ptr = temp->matrix_node;
                m_node* back_row_ptr = NULL;
                while (temp_row_ptr) {
                        back_row_ptr = temp_row_ptr;
                        temp_row_ptr = temp_row_ptr->row_ptr;
                        free(back_row_ptr);
                }
                temp = temp->next;
                free(back_node);
        }

        // Free linked lists and matrix structure
        free(row_ll);
        
        // Free column list nodes
        if (col_ll) {
                l_node* temp_col = col_ll->head;
                while (temp_col) {
                        l_node* back_col_node = temp_col;
                        temp_col = temp_col->next;
                        free(back_col_node);
                }
                free(col_ll);
        }
        
        free(M);
}
