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
 * next: Pointer to the next node in the queue.
 */
typedef struct q_node {
        char* patient_name;
        struct q_node* next;
} q_node;

/*
 * Struct: P_Queue
 * ----------------------------
 * Represents the priority queue.
 *
 * front: Pointer to the front node of the queue.
 * rear: Pointer to the rear node of the queue.
 * max_patient: Maximum number of patients allowed in this priority level.
 * current_patient: Current number of patients in this priority level.
 */
typedef struct P_Queue {
        q_node* front;
        q_node* rear;
        uint8_t max_patient;
        uint8_t current_patient;
} P_Queue;

/*
 * Function: create_q_node
 * ----------------------------
 * Creates a new node for the priority queue.
 *
 * @param patient_name - Name of the patient.
 *
 * @return Pointer to the newly created node.
 */
q_node* create_q_node(char* patient_name);

/*
 * Function: PQ
 * ----------------------------
 * Creates a new priority queue array with 4 priority levels.
 *
 * @return Pointer to the newly created priority queue array.
 */
P_Queue* PQ();

/*
 * Function: FreePQ
 * ----------------------------
 * Frees the memory allocated for the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array to be freed.
 */
void FreePQ(P_Queue* p_arr);

/*
 * Function: pq_newPT
 * ----------------------------
 * Adds a new patient to the priority queue at specified priority.
 *
 * @param p_arr - Array of priority queues.
 * @param pt_name - Name of the patient.
 * @param priority - Priority of the patient.
 */
void pq_newPT(P_Queue* p_arr, char* pt_name, uint16_t priority);

/*
 * Function: pq_processPT
 * ----------------------------
 * Processes the patient at the front of the highest priority queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Name of the processed patient.
 */
char* pq_processPT(P_Queue* p_arr);

/*
 * Function: pq_frontName
 * ----------------------------
 * Gets the name of the patient at the front of the highest priority queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Name of the patient at the front of the queue.
 */
char* pq_frontName(P_Queue* p_arr);

/*
 * Function: pq_frontPriority
 * ----------------------------
 * Gets the priority of the patient at the front of the queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return Priority of the patient at the front of the queue.
 */
uint16_t pq_frontPriority(P_Queue* p_arr);

/*
 * Function: pq_upgradePT
 * ----------------------------
 * Upgrades the priority of a patient in the queue.
 *
 * @param p_arr - Pointer to the priority queue array.
 * @param patient_name - Name of the patient.
 * @param new_priority - New priority of the patient.
 */
void pq_upgradePT(P_Queue* p_arr, char* patient_name, uint16_t new_priority);

/*
 * Function: pq_isEmpty
 * ----------------------------
 * Checks if the priority queue array is empty.
 *
 * @param p_arr - Pointer to the priority queue array.
 *
 * @return True if the queue is empty, false otherwise.
 */
bool pq_isEmpty(P_Queue* p_arr);

/*
 * Function: pq_clear
 * ----------------------------
 * Clears all priority queues in the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array.
 */
void pq_clear(P_Queue* p_arr);

/*
 * Function: toString
 * ----------------------------
 * Prints the current state of the priority queue array.
 *
 * @param p_arr - Pointer to the priority queue array.
 */
void toString(P_Queue* p_arr);

#endif // PRIORITY_Q_H
