/*
 * File Name: patient_management_system.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file contains the implementation of the patient management system using a priority queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../include/priority_q.h"

/*
 * Function: _manage_patient
 * ----------------------------
 * Manages the patient queue by providing options to add, view, upgrade, process, bulk process, clear, and quit.
 *
 * Description:
 *   This function provides a menu-driven interface for managing patients in a priority queue.
 *   It allows the user to perform various operations such as adding a new patient, viewing the front patient,
 *   upgrading a patient's priority, processing the front patient, bulk processing, clearing the queue, and quitting the system.
 */
void _manage_patient() {
        system("clear");

        P_Queue* p_queue = PQ();

        while(1) {
                toString(p_queue);
                char choice;
                printf("N)ew, F)ront, U)pgrade, P)rocess, B)ulk, C)lear, Q)uit? ");

                // Clearing buffer
                do {
                        clearerr(stdin);
                        choice = getchar();
                } while (choice == EOF || choice == '\n');

                switch (tolower(choice)) {
                        case 'n': {
                                char c;
                                char* patient_name = (char*)malloc(20*sizeof(char));
                                uint16_t priority;
                                printf("Name? ");
                                do {
                                        clearerr(stdin);
                                        c = getchar();
                                } while (c == EOF);
                                fgets(patient_name, 20, stdin);
                                patient_name[strcspn(patient_name,"\n")] = '\0';
                                bool input_valid = false;
                                while (!input_valid) {
                                        printf("Priority? ");
                                        if (scanf("%hu", &priority) == 1 && (priority > 0 && priority < 4)) {
                                                input_valid = true;
                                        }
                                        else {
						printf("Enter valid priority!!\n");
                                                do {
                                                        clearerr(stdin);
                                                } while (getchar() != '\n');
                                        }
                                }
                                pq_newPT(p_queue, patient_name, priority);
                                printf("\n\n");
                                break;
                        }
                        case 'f': {
                                if (!pq_isEmpty(p_queue)) {
                                        printf("Name: %s\n", pq_frontName(p_queue));
                                        printf("Priority: %hu\n\n", pq_frontPriority(p_queue));
                                } else {
                                        printf("No patients in the queue\n\n");
                                }
                                break;
                        }
                        case 'u': {
                                char emergency;
                                char* patient_name = (char*)malloc(20*sizeof(char));
                                uint16_t priority;
                                printf("Name? ");

                                do {
                                        clearerr(stdin);
                                } while (getchar() == EOF);

                                fgets(patient_name, 20, stdin);
                                patient_name[strcspn(patient_name,"\n")] = '\0';
                                printf("It's Emergency? [Y/n] ");

                                do {
                                        clearerr(stdin);
                                } while ((emergency = getchar()) == EOF);

                                do {
                                        switch (tolower(emergency)){
                                                case 'y':
                                                case 'n':
                                                        break;
                                                default:
                                                        emergency = 'c';
                                                        printf("Invalid choice\n");
                                                        break;
                                        }
                                } while (emergency == 'c' && (printf("It's Emergency? [Y/n] "), (emergency = getchar()) == EOF));

                                if (emergency == 'y'){
                                        priority = 0;
                                }
                                else {
                                        bool input_valid = false;

                                        while (!input_valid) {
                                                printf("Priority? ");
                                                if (scanf("%hu", &priority) == 1) {
                                                        input_valid = true;
                                                }
                                                else {
                                                        printf("Enter valid integer Number!!\n");
                                                        do {
                                                                clearerr(stdin);
                                                        } while (getchar() != '\n');
                                                }
                                        }
                                }
                                pq_upgradePT(p_queue, patient_name, priority);
                                printf("\n\n");
                                break;
                        }
                        case 'p': {
                                if (!pq_isEmpty(p_queue)) {
                                        printf("Processing patient: %s\n\n", pq_processPT(p_queue));
                                } else {
                                        printf("No patients to process\n\n");
                                }
                                break;
                        }
                        case 'b': {
                                printf("I don't know what to do here\n\n");
                                break;
                        }
                        case 'c': {
                                pq_clear(p_queue);
                                printf("Queue is cleared\n\n");
                                break;
                        }
                        case 'q': {
                                FreePQ(p_queue);
                                printf("\nExiting\n");
                                return;
                        }
                        default: {
                                printf("Invalid choice\n\n");
                                break;
                        }
                }
        }
}
