/*
 * File Name: main.c
 * Authors: Arpit Patel, Dharma KaPatel
 * Date: 2025-03-19
 * Description: This file contains the main function for the patient management system.
 *              It continuously manages patients until the user decides to quit.
 */

#include <stdio.h>
#include <stdbool.h>


extern _Bool _continue();
extern void _manage_patient();


int main(){

	while(1){

		_manage_patient();

		if (!_continue()) break;
	
	}
}
