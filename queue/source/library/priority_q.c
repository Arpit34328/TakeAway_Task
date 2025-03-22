/*
 * File Name: priority_q.c
 * Authors: Arpit Patel, Dharma KaPatel
 * Date: 2025-03-19
 * Description: This file implements the functions and operations of the priority queue data structure.
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/priority_q.h"

/*
 * Function: create_q_node
 * ----------------------------
 * Creates a new node for the priority queue.
 *
 * @param pt_name - Name of the patient.
 * @param priority - Priority of the patient.
 *
 * @return Pointer to the newly created node.
 */
q_node* create_q_node(char* pt_name, uint16_t priority){

        q_node* new_q_node = (q_node*)malloc(sizeof(q_node));

        if (!new_q_node){
                printf("Failed to allocate memory for new node\n");
                return NULL;
        }
        
        new_q_node->patient_name = pt_name;
        new_q_node->priority = priority;
        new_q_node->next = NULL;

        return new_q_node;

}

/*
 * Function: PQ
 * ----------------------------
 * Creates a new priority queue.
 *
 * @return Pointer to the newly created priority queue.
 */
P_Queue* PQ(){

        P_Queue* new_p_queue = (P_Queue*)malloc(sizeof(P_Queue));

        if (!new_p_queue){
                printf("Failed to allocate memory for new queue\n");
                return NULL;
        }
        
        new_p_queue->front = NULL;
        new_p_queue->rear = NULL;
        new_p_queue->last_priority = 0;

        return new_p_queue;

}

/*
 * Function: FreePQ
 * ----------------------------
 * Frees the memory allocated for the priority queue.
 *
 * @param p_queue - Pointer to the priority queue to be freed.
 */
void FreePQ(P_Queue* p_queue){

        if (!pq_isEmpty(p_queue)){

		q_node* temp = p_queue->front;

        	while (temp->next){
                	q_node* cur = temp;
                	temp = temp->next;
                	free(cur);
        	}
        	free(temp);

	}
        
	free(p_queue);

}

/*
 * Function: pq_newPT
 * ----------------------------
 * Adds a new patient to the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param pt_name - Name of the patient.
 * @param priority - Priority of the patient.
 */
void pq_newPT(P_Queue* p_queue, char* pt_name, uint16_t priority){

        q_node* new_node = create_q_node(pt_name, priority);

        if (pq_isEmpty(p_queue)){
                p_queue->front = new_node;
                p_queue->rear = new_node;
                p_queue->last_priority = p_queue->front->priority;
        }
        else {
                if (new_node->priority < p_queue->front->priority) {
                        new_node->next = p_queue->front;
                        p_queue->front = new_node;
                }
                else if (new_node->priority >= p_queue->last_priority) {
                        p_queue->rear->next = new_node;
                        p_queue->rear = new_node;
                        p_queue->last_priority = p_queue->rear->priority;
                }
                else {
                        heapify(p_queue, new_node);

                        if (p_queue->rear->next) {
                                p_queue->rear = p_queue->rear->next;
                                p_queue->last_priority = p_queue->rear->priority;
                        }
                }
        }
}

/*
 * Function: pq_processPT
 * ----------------------------
 * Processes the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Name of the processed patient.
 */
char* pq_processPT(P_Queue* p_queue){

        char* patient_name;
        if (pq_isEmpty(p_queue))
                return "Sorry, There is no Patient\n";
        else{
                q_node* temp = p_queue->front;
                if (!temp->next){
                        p_queue->front = NULL;
                        p_queue->rear = NULL;
                        p_queue->last_priority = 0;
                }
		else
			p_queue->front = temp->next;

                patient_name = temp->patient_name;
                free(temp);
        }

        return patient_name;

}
 
/* Function: pq_frontName
 * ----------------------------
 * Gets the name of the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Name of the patient at the front of the queue.
 */
char* pq_frontName(P_Queue* p_queue){

        if (pq_isEmpty(p_queue))
                return "Sorry, There is no patient\n";

        return p_queue->front->patient_name;

}

/*
 * Function: pq_frontPriority
 * ----------------------------
 * Gets the priority of the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Priority of the patient at the front of the queue.
 */
uint16_t pq_frontPriority(P_Queue* p_queue){

        if (pq_isEmpty(p_queue))
                return 0;
        return p_queue->front->priority;

}

/*
 * Function: pq_upgradePT
 * ----------------------------
 * Upgrades the priority of a patient in the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param patient_name - Name of the patient.
 * @param new_priority - New priority of the patient.
 */
void pq_upgradePT(P_Queue* p_queue, char* patient_name, uint16_t new_priority){

        if (pq_isEmpty(p_queue))
                printf("Sorry! There is no patient\n");
        else{
                q_node* temp = p_queue->front;
                q_node* back_node = NULL;

                while (temp){
                        if (!strcmp(temp->patient_name, patient_name)){
                                if (new_priority > temp->priority)
                                        printf("You can not down grade the priority\n");
                                else if(temp != p_queue->front){
                                       
				       	q_node* original_next = temp->next;
                                        
                                        back_node->next = temp->next;
                                        temp->next = NULL;
                                        
                                        temp->priority = new_priority;
                                        
                                        heapify(p_queue, temp);
                                        
                                        if (p_queue->rear == temp && original_next == NULL) {
                                                q_node* curr = p_queue->front;
                                                while (curr->next) {
                                                        curr = curr->next;
                                                }
                                                p_queue->rear = curr;
                                                p_queue->last_priority = curr->priority;
                                        }
                                } 
				else 
                                        temp->priority = new_priority;        
                                
                                break;
                        }
                        back_node = temp;
                        temp = temp->next;
                }
        }
}

/*
 * Function: heapify
 * ----------------------------
 * Reorganizes the queue to maintain the priority order after adding a new node.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param pos - Pointer to the node to be inserted in the proper position.
 */
void heapify(P_Queue* p_queue, q_node* pos){

        q_node* temp = p_queue->front;

        if (temp->priority > pos->priority){
                pos->next = temp;
                p_queue->front = pos;
        }
        else{
                while (temp->next && temp->next->priority <= pos->priority)
                        temp = temp->next;
                pos->next = temp->next;
                temp->next = pos;
        }

}

/*
 * Function: pq_isEmpty
 * ----------------------------
 * Checks if the priority queue is empty.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return True if the queue is empty, false otherwise.
 */
_Bool pq_isEmpty(P_Queue* p_queue){

        return (!p_queue->front) ? 1 : 0;

}

/*
 * Function: pq_clear
 * ----------------------------
 * Clears the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 */
void pq_clear(P_Queue* p_queue){

        if (pq_isEmpty(p_queue))
                printf("Queue is already clean\n");
        else{
                q_node* temp = p_queue->front;

                while (temp->next){
                        q_node* cur = temp;
                        temp = temp->next;
                        free(cur);
                }

                free(temp);
        }

        p_queue->front = NULL;
        p_queue->rear = NULL;
        p_queue->last_priority = 0;

}

/*
 * Function: toString
 * ----------------------------
 * Prints the current state of the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 */
void toString(P_Queue* p_queue){

        printf("Current patient queue:\n");
        if (pq_isEmpty(p_queue))
                printf("{} (empty)\n");
        else{
                q_node* temp = p_queue->front;

                printf("{");
                while (temp->next){
                        printf("%hu:%s, ", temp->priority, temp->patient_name);
                        temp = temp->next;
                }
                printf("%hu:%s} (not empty)\n", temp->priority, temp->patient_name);
        }

}
