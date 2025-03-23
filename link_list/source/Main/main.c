/*
 * File Name: main.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description:
 */


#include <stdio.h>
#include <stdbool.h>

#include "../include/S_Matrix.h"

extern _Bool _continue();
extern void _sparse_matrix();

int main(){

	while(1){

		_sparse_matrix();

		if (!_continue()) break;
	
	}

	return 0;
}
