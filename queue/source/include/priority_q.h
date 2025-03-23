/*
 * File Name: priority_q.h
 * Authors: Arpit Patel, Dharm KaPatel
 * Date: 2025-03-19
 * Description: This file defines the basic structure and functionalities of the priority queue data structure.
 */



#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <stdint.h>
#include <stdbool.h>



/*
 * Struct: q_node
 * ----------------------------
 * Represents a single node in the priority queue.
 *
 * patient_name: Name of the patient.
 * priority: Priority of the patient.
 * next: Pointer to the next node in the queue.
 */
typedef struct q_node {

        char* patient_name;
        uint16_t priority;
        struct q_node* next;

} q_node;



/*
 * Struct: P_Queue
 * ----------------------------
 * Represents the priority queue.
 *
 * front: Pointer to the front node of the queue.
 * rear: Pointer to the rear node of the queue.
 * last_priority: Priority of the last node in the queue.
 */
typedef struct P_Queue {

        q_node* front;
        q_node* rear;
        uint16_t last_priority;

} P_Queue;



/*
 * Function: create_q_node
 * ----------------------------
 * Creates a new node for the priority queue.
 *
 * @param patient_name - Name of the patient.
 * @param priority - Priority of the patient.
 *
 * @return Pointer to the newly created node.
 */
q_node* create_q_node(char* patient_name, uint16_t priority);



/*
 * Function: PQ
 * ----------------------------
 * Creates a new priority queue.
 *
 * @return Pointer to the newly created priority queue.
 */
P_Queue* PQ();



/*
 * Function: FreePQ
 * ----------------------------
 * Frees the memory allocated for the priority queue.
 *
 * @param p_queue - Pointer to the priority queue to be freed.
 */
void FreePQ(P_Queue* p_queue);



/*
 * Function: pq_newPT
 * ----------------------------
 * Adds a new patient to the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param pt_name - Name of the patient.
 * @param priority - Priority of the patient.
 */
void pq_newPT(P_Queue* p_queue, char* pt_name, uint16_t priority);



/*
 * Function: pq_processPT
 * ----------------------------
 * Processes the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Name of the processed patient.
 */
char* pq_processPT(P_Queue* p_queue);



/*
 * Function: pq_frontName
 * ----------------------------
 * Gets the name of the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Name of the patient at the front of the queue.
 */
char* pq_frontName(P_Queue* p_queue);



/*
 * Function: pq_frontPriority
 * ----------------------------
 * Gets the priority of the patient at the front of the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return Priority of the patient at the front of the queue.
 */
uint16_t pq_frontPriority(P_Queue* p_queue);



/*
 * Function: pq_upgradePT
 * ----------------------------
 * Upgrades the priority of a patient in the queue.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param patient_name - Name of the patient.
 * @param new_priority - New priority of the patient.
 */
void pq_upgradePT(P_Queue* p_queue, char* patient_name, uint16_t new_priority);


/*
 * Function: heapify
 * ----------------------------
 * Reorganizes the queue to maintain the priority order after adding a new node.
 *
 * @param p_queue - Pointer to the priority queue.
 * @param pos - Pointer to the node to be inserted in the proper position.
 */
void heapify(P_Queue* p_queue, q_node* pos);


/*
 * Function: pq_isEmpty
 * ----------------------------
 * Checks if the priority queue is empty.
 *
 * @param p_queue - Pointer to the priority queue.
 *
 * @return True if the queue is empty, false otherwise.
 */
_Bool pq_isEmpty(P_Queue* p_queue);



/*
 * Function: pq_clear
 * ----------------------------
 * Clears the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 */
void pq_clear(P_Queue* p_queue);



/*
 * Function: toString
 * ----------------------------
 * Prints the current state of the priority queue.
 *
 * @param p_queue - Pointer to the priority queue.
 */
void toString(P_Queue* p_queue);



#endif // PRIORITY_Q_H
