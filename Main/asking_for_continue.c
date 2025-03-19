/*
 * File Name: asking_for_continue.c
 * Authors: Arpit Patel, Dharm Kapatel
 * Date: 2025-03-19
 * Description: This file contains the implementation of a function that prompts the user to decide whether to continue or not.i
 */


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/*
 * Function: _continue
 * ----------------------------
 * Prompts the user to decide whether to continue or not.
 *
 * @return true if the user chooses 'Y', false if the user chooses 'n'.
 *
 * Description:
 *   This function repeatedly asks the user if they want to continue until a valid response ('Y' or 'n') is received.
 *   It handles invalid inputs by displaying an error message and re-prompting the user. The function returns true
 *   if the user chooses 'Y' and false if the user chooses 'n'.
 */
_Bool _continue(){

	char choice;

        do {
        	printf("\n\nDo you want to continue? [Y/n] ");

                // Clear the buffer
                do {
                	clearerr(stdin);
                        choice = getchar();
                } while(choice == EOF || choice == '\n');

                switch (tolower(choice)){

                	case 'y':
                        case 'n':
                        	break;
                        default:
                                choice = 'c';
                                printf("Invalid Choice 6 la bhaila\nDekh rahe ho la parvahi ka natija!!\n Savdhan rahie Satark rahie\n");
				break;
                
		}

	} while(choice == 'c');

        if (choice == 'n') return 0;

	return 1;

}
