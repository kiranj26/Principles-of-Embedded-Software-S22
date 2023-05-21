/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ ​2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file LLFIFO.h
 * @brief Header file for a Linked List FIFO (First In First Out) implementation
 *
 * This header file defines the structure and function prototypes for a Linked List FIFO
 * implementation. It provides functions to create, enqueue, dequeue, check for full/empty,
 * and destroy the FIFO.
 *
 * @author Kiran Jojare
 * @date April 9 2023
 * @version 1.0
 * @reference
 * None
*/

#include<stdint.h>

#ifndef _LLFIFO_H_
#define _LLFIFO_H_

/**
 * @brief Structure representing the linked list FIFO queue
 */
struct llfifo_s {
    int capacity;       /* Maximum capacity of the queue */
    int length;         /* Current length of the queue */
    struct node *start; /* Start of the queue */

    struct node *head;  /* Head of the queue */
    struct node *tail;  /* Tail of the queue */
};

typedef struct llfifo_s llfifo_t;

/**
 * @brief Creates a new linked list FIFO queue
 *
 * This function creates a new linked list FIFO queue of the given capacity.
 *
 * @param capacity Maximum capacity of the queue
 *
 * @return Pointer to the created queue
 */
llfifo_t *llfifo_create(int capacity);

/**
 * @brief Enqueues an element in the linked list FIFO queue
 *
 * This function enqueues the given data in the linked list FIFO queue.
 *
 * @param fifo Pointer to the queue to enqueue to
 * @param data Data to enqueue
 *
 * @return 0 on success, -1 on failure (queue is full)
 */
int llfifo_enqueue(llfifo_t *fifo, uint8_t data);

/**
 * @brief Dequeues an element from the linked list FIFO queue
 *
 * This function dequeues an element from the linked list FIFO queue and returns it.
 *
 * @param fifo Pointer to the queue to dequeue from
 *
 * @return Dequeued element
 */
uint8_t llfifo_dequeue(llfifo_t *fifo);

/**
 * @brief Returns the length of the linked list FIFO queue
 *
 * This function returns the current length of the linked list FIFO queue.
 *
 * @param fifo Pointer to the queue to get the length of
 *
 * @return Current length of the queue
 */
int llfifo_length(llfifo_t *fifo);

/**
 * @brief Returns the maximum capacity of the linked list FIFO queue
 *
 * This function returns the maximum capacity of the linked list FIFO queue.
 *
 * @param fifo Pointer to the queue to get the capacity of
 *
 * @return Maximum capacity of the queue
 */
int llfifo_capacity(llfifo_t *fifo);

/**
 * @brief Returns whether the linked list FIFO queue is full
 *
 * This function returns whether the linked list FIFO queue is full or not.
 *
 * @param fifo Pointer to the queue to check
 *
 * @return 1 if the queue is full, 0 otherwise
 */
int llfifo_is_full(llfifo_t *fifo);

/**
 * @brief Returns whether the linked list FIFO queue is empty
 *
 * This function returns whether the linked list FIFO queue is empty or not.
 *
 * @param fifo Pointer to the queue to check
 *
 * @return 1 if the queue is empty, 0 otherwise
 */
int llfifo_is_empty(llfifo_t *fifo);

#endif // _LLFIFO_H_
