/*
 * File Name: priority_q.c
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file implements the functions and operations of the priority queue data structure.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/priority_q.h"

/*
 * Function: create_q_node
 * ----------------------------
 * Creates a new node for the priority queue.
 *
 * @param pt_name - Name of the patient.
 *
 * @return Pointer to the newly created node.
 */
q_node* create_q_node(char* pt_name) {
        q_node* new_q_node = (q_node*)malloc(sizeof(q_node));

        if (!new_q_node) {
                printf("Failed to allocate memory for new node\n");
                return NULL;
        }

        new_q_node->patient_name = pt_name;
        new_q_node->next = NULL;

        return new_q_node;
}

/*
 * Function: PQ
 * ----------------------------
 * Creates a new priority queue array.
 *
 * @return Pointer to the newly created priority queue array.
 */
P_Queue* PQ() {
        P_Queue* priority_arr = (P_Queue*)malloc(4 * sizeof(P_Queue));
        if (!priority_arr) {
                printf("Failed to allocate memory for new queue\n");
                return NULL;
        }

        for (uint8_t priority = 0; priority < 4; priority++) {
                priority_arr[priority].front = NULL;
                priority_arr[priority].rear = NULL;
                priority_arr[priority].current_patient = 0;
        }

        priority_arr[0].max_patient = 3;
        priority_arr[1].max_patient = 10;
        priority_arr[2].max_patient = 15;
        priority_arr[3].max_patient = 50;

        return priority_arr;
}

/*
 * Function: FreePQ
 * ----------------------------
 * Frees the memory allocated for the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array to be freed.
 */
void FreePQ(P_Queue* p_arr) {
        if (!pq_isEmpty(p_arr)) {
                for (uint8_t priority = 0; priority < 4; priority++) {
                        q_node* temp = p_arr[priority].front;
                        while (temp) {
                                q_node* cur = temp;
                                temp = temp->next;
                                free(cur);
                        }
                }
        }
        free(p_arr);
}

/*
 * Function: pq_newPT
 * ----------------------------
 * Adds a new patient to the priority queue.
 *
 * @param p_arr - Array of priority queues.
 * @param pt_name - Name of the patient.
 * @param priority - Priority of the patient.
 */
void pq_newPT(P_Queue* p_arr, char* pt_name, uint16_t priority) {
        q_node* new_node = create_q_node(pt_name);

        if (!p_arr[priority].front) {
                p_arr[priority].front = new_node;
                p_arr[priority].rear = new_node;
                p_arr[priority].current_patient++;
        } else {
                if (p_arr[priority].current_patient == p_arr[priority].max_patient) {
                        if (priority == 3) {
                                printf("You can't adjust more patients\n");
                                return;
                        }

                        printf("You can't add more patients in this priority\n");
                        printf("You can add to next priority\n");
                        printf("Do you want? [Y/n] ");
                        char choice;
                        do {
                                clearerr(stdin);
                                choice = getchar();
                        } while (choice == '\n');

                        if (tolower(choice) == 'y') {
                                pq_newPT(p_arr, pt_name, priority + 1);
                        }

                        return;
                }

                p_arr[priority].rear->next = new_node;
                p_arr[priority].rear = new_node;
                p_arr[priority].current_patient++;
        }
}

/*
 * Function: pq_processPT
 * ----------------------------
 * Processes the patient at the front of the highest priority queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Name of the processed patient.
 */
char* pq_processPT(P_Queue* p_arr) {
        if (pq_isEmpty(p_arr)) {
                return "Sorry, There is no Patient";
        } else {
                uint8_t priority;
                for (priority = 0; priority < 4 && !p_arr[priority].front; priority++);

                q_node* temp = p_arr[priority].front;

                if (!temp->next) {
                        p_arr[priority].front = NULL;
                        p_arr[priority].rear = NULL;
                } else {
                        p_arr[priority].front = temp->next;
                }

                p_arr[priority].current_patient--;
                char* patient_name = temp->patient_name;
                free(temp);

                return patient_name;
        }
}

/*
 * Function: pq_frontName
 * ----------------------------
 * Gets the name of the patient at the front of the highest priority queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Name of the patient at the front of the queue.
 */
char* pq_frontName(P_Queue* p_arr) {
        if (pq_isEmpty(p_arr)) {
                return "Sorry, There is no patient";
        }

        uint8_t priority;
        for (priority = 0; priority < 4 && !p_arr[priority].front; priority++);

        return p_arr[priority].front->patient_name;
}

/*
 * Function: pq_frontPriority
 * ----------------------------
 * Gets the priority of the patient at the front of the queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Priority of the patient at the front of the queue.
 */
uint16_t pq_frontPriority(P_Queue* p_arr) {
        if (pq_isEmpty(p_arr)) {
                return 0;
        }

        uint8_t priority;
        for (priority = 0; priority < 4 && !p_arr[priority].front; priority++);

        return priority;
}

/*
 * Function: pq_upgradePT
 * ----------------------------
 * Upgrades the priority of a patient in the queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 * @param patient_name - Name of the patient.
 * @param new_priority - New priority of the patient.
 */
void pq_upgradePT(P_Queue* p_arr, char* patient_name, uint16_t new_priority) {
        if (pq_isEmpty(p_arr)) {
                printf("Sorry! There is no patient\n");
                return;
        }

        bool found_patient = false;
        
        for (uint8_t priority = 0; priority < 4 && !found_patient; priority++) {
                q_node* temp = p_arr[priority].front;
                q_node* prev = NULL;

                while (temp) {
                        if (strcmp(temp->patient_name, patient_name) == 0) {
                                if (priority <= new_priority) {
                                        printf("You can't downgrade the priority\n");
                                        return;
                                }

                                if (p_arr[new_priority].current_patient == p_arr[new_priority].max_patient) {
                                        printf("Upper priority is already full\n");
                                        return;
                                }

                                if (prev) {
                                        prev->next = temp->next;
                                } else {
                                        p_arr[priority].front = temp->next;
                                }

                                if (temp == p_arr[priority].rear) {
                                        p_arr[priority].rear = prev;
                                }

                                p_arr[priority].current_patient--;

                                if (!p_arr[new_priority].front) {
                                        p_arr[new_priority].front = temp;
                                        p_arr[new_priority].rear = temp;
                                } else {
                                        p_arr[new_priority].rear->next = temp;
                                        p_arr[new_priority].rear = temp;
                                }

                                temp->next = NULL;
                                p_arr[new_priority].current_patient++;

                                found_patient = true;
                                break;
                        }

                        prev = temp;
                        temp = temp->next;
                }
        }

        if (!found_patient) {
                printf("Patient not found\n");
        }
}

/*
 * Function: pq_isEmpty
 * ----------------------------
 * Checks if the priority queue array is empty.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return True if the queue is empty, false otherwise.
 */
bool pq_isEmpty(P_Queue* p_arr) {
        for (uint8_t priority = 0; priority < 4; priority++) {
                if (p_arr[priority].front) {
                        return false;
                }
        }
        return true;
}

/*
 * Function: pq_clear
 * ----------------------------
 * Clears all priority queues in the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array.
 */
void pq_clear(P_Queue* p_arr) {
        if (pq_isEmpty(p_arr)) {
                printf("Queue is already clean\n");
                return;
        }

        for (uint8_t priority = 0; priority < 4; priority++) {
                q_node* temp = p_arr[priority].front;
                while (temp) {
                        q_node* cur = temp;
                        temp = temp->next;
                        free(cur);
                }
                p_arr[priority].front = NULL;
                p_arr[priority].rear = NULL;
                p_arr[priority].current_patient = 0;
        }
}


/*
 * Function: toString
 * ----------------------------
 * Prints the current state of the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array.
 */
void toString(P_Queue* p_arr) {
        printf("Current patient queue:\n");

        if (pq_isEmpty(p_arr)) {
                printf("{} (empty)\n");
                return;
        }

        printf("{");
        bool first_patient = true;
        for (uint8_t priority = 0; priority < 4; priority++) {
                q_node* temp = p_arr[priority].front;
                while (temp) {
                        if (!first_patient) {
                                printf(", ");
                        }
			if (priority == 0){
				printf("Emergency: %s", temp->patient_name);
			}
			else{
                        	printf("%hhu:%s", priority, temp->patient_name);
			}
			temp = temp->next;
                        first_patient = false;
                }
        }
        printf("} (not empty)\n");
}
