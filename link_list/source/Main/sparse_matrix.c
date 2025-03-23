/*
 * File Name: sparse_matrix.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file provides the main interface for interacting with the S_Matrix structure.
 *              It provides a menu-driven interface for creating, manipulating, and displaying sparse matrices.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/S_Matrix.h"

/*
 * Function: _sparse_matrix
 * ----------------------------
 * Provides a menu-driven interface for interacting with sparse matrices.
 * 
 * Allows users to:
 * - Create a new sparse matrix
 * - Insert values into the matrix
 * - Check for duplicate values
 * - Resize the matrix
 * - Transpose the matrix
 * - Quit and free all allocated memory
 */
void _sparse_matrix() {
       
	system("clear");

       	matrix* M = NULL;
        
        bool flag_create = false;
        
        while (1) {
                displayMatrix(M);
                char choice;
                printf("\nC)reate, I)nsert, D)uplicate, R)esize, T)ranspose, Q)uit? ");
                
                // Clear buffer
                do {
                        clearerr(stdin);
                        choice = getchar();
                } while (choice == EOF || choice == '\n');
                
                switch (tolower(choice)) {
                        case 'c':
                                {
                                        if (!flag_create) {
                                                uint32_t rows;
                                                uint32_t cols;
                                                bool input_valid = false;
                                                while (!input_valid) {
                                                        printf("No of Rows? ");
                                                        if (scanf("%u", &rows)) {
                                                                input_valid = true;
                                                        }
                                                        else {
                                                                printf("Enter valid integer type Number!!\n");
                                                                do {
                                                                        clearerr(stdin);
                                                                } while (getchar() != '\n');
                                                        }
                                                }
                                                input_valid = false;
                                                while (!input_valid) {
                                                        printf("No of Columns? ");
                                                        if (scanf("%u", &cols)) {
                                                                input_valid = true;
                                                        }
                                                        else {
                                                                printf("Enter valid integer type Number!!\n");
                                                                do {
                                                                        clearerr(stdin);
                                                                } while (getchar() != '\n');
                                                        }
                                                }
                                                M = create_S_Matrix(rows, cols);
                                                flag_create = true;
                                                printf("\n\n");
                                        }
                                        else {
                                                printf("Matrix is already created\n");
                                        }
                                }
                                break;
                        case 'i':
                                {
                                        uint32_t row;
                                        uint32_t col;
                                        double value;
                                        bool input_valid = false;
                                        while (!input_valid) {
                                                printf("Position of Row? ");
                                                if (scanf("%u", &row)) {
                                                        input_valid = true;
                                                }
                                                else {
                                                        printf("Enter valid integer type Number!!\n");
                                                        do {
                                                                clearerr(stdin);
                                                        } while (getchar() != '\n');
                                                }
                                        }
                                        input_valid = false;
                                        while (!input_valid) {
                                                printf("Position of Column? ");
                                                if (scanf("%u", &col)) {
                                                        input_valid = true;
                                                }
                                                else {
                                                        printf("Enter valid integer type Number!!\n");
                                                        do {
                                                                clearerr(stdin);
                                                        } while (getchar() != '\n');
                                                }
                                        }
                                        input_valid = false;
                                        while (!input_valid) {
                                                printf("value? ");
                                                if (scanf("%lf", &value)) {
                                                        input_valid = true;
                                                }
                                                else {
                                                        printf("Enter valid double type Number!!\n");
                                                        do {
                                                                clearerr(stdin);
                                                        } while (getchar() != '\n');
                                                }
                                        }
                                        insert_data(M, row, col, value);
                                        printf("\n\n");
                                }
                                break;
                        case 'd':
                                {
                                        double value;
                                        bool input_valid = false;
                                        while (!input_valid) {
                                                printf("value? ");
                                                if (scanf("%lf", &value)) {
                                                        input_valid = true;
                                                }
                                                else {
                                                        printf("Enter valid double type Number!!\n");
                                                        do {
                                                                clearerr(stdin);
                                                        } while (getchar() != '\n');
                                                }
                                        }
                                        (duplicatevalue(M, value)) ? printf("Value %.1lf present in Sparse Matrix\n\n", value) : printf("Value %.1lf not present in Sparse Matrix\n\n", value);
                                }
                                break;
                        case 'r':
                                {
                                        (resize(M)) ? printf("Matrix is resized\n\n") : printf("Matrix is not resized\n\n");
                                }
                                break;
                        case 't':
                                {
                                        (transpose(M)) ? printf("Matrix converted to transposed version\n\n"): printf("Matrix not converted to trasposed version\n\n");
                                }
                                break;
                        case 'q':
                                {
                                        free_S_Matrix(M);
                                        printf("\nExiting\n");
                                        return;
                                }
                                break;
                        default:
                                printf("Invalid choice\n\n");
                                break;
                }
        }
}
