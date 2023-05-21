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
 * @file LLFIFO.c
 * @brief C file for a Linked List FIFO (First In First Out) implementation
 *
 * This header file defines the structure and function definations for a Linked List FIFO
 * implementation. It provides functions to create, enqueue, dequeue, check for full/empty,
 * and destroy the FIFO.
 *
 * @author Kiran Jojare
 * @date April 9 2023
 * @version 1.0
 * @reference
 * None
*/

#include "llfifo.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <MKL25Z4.H>

// macro definations
#define ERROR_CODE 		(-1)
#define SUCCESS_CODE 	(1)
#define MAX_INT_VALUE 	0x7FFFFFFF

// Node structure with data and pointer to ne
struct node {
    uint8_t data;
    struct node *next;
};


// Function to create a linked-list based FIFO with the given capacity
llfifo_t *llfifo_create(int capacity) {

    // Declare variables for iteration and linked-list traversal
    int i;
    struct node *current = NULL;
    struct node *temp = NULL;

    // Check if capacity is negative
    if(capacity < 0 )
    {
        return NULL;
    }

    // Check if capacity is greater than the maximum int value
    if (capacity > MAX_INT_VALUE) {
        return NULL;
    }

    // Allocate memory for the FIFO structure
    llfifo_t *fifo = malloc(sizeof(llfifo_t));

    // Check if memory allocation was successful
    if (fifo == NULL) {
        return NULL;
    }

    // Initialize the FIFO structure with given capacity and length 0
    fifo->capacity = capacity;
    fifo->length = 0;

    // Initialize the start, head and tail pointers of the FIFO as NULL
    fifo->start = NULL;
    fifo->head = NULL;
    fifo->tail = NULL;

    // Loop to create a linked-list of nodes with the given capacity
    for (i = 0; i < capacity; i++) {

        // Allocate memory for a new node
        struct node *new_node = malloc(sizeof(struct node));

        // Check if memory allocation was successful
        if (new_node == NULL) {

            // Free all the nodes that were allocated before this failed attempt
            while (fifo->head != NULL) {
                current = fifo->head->next;
                free(fifo->head);
                fifo->head = current;
            }

            // Free the FIFO structure itself
            free(fifo);
            return NULL;
        }

        // Initialize the new node with data 0 and NULL next pointer
        new_node->data = 0;
        new_node->next = NULL;

        // Add the new node to the linked-list
        if (fifo->start == NULL) {
            fifo->start = new_node;
            temp = new_node;
        } else {
            temp->next = new_node;
            temp = new_node;
        }
    }

    // Return the newly created FIFO structure
    return fifo;
}

int llfifo_enqueue(llfifo_t *fifo, uint8_t data) {
	__disable_irq();

    // check if the FIFO is NULL or if it is full
    if (fifo == NULL || fifo->length >= fifo->capacity) {
    	__enable_irq();
        return ERROR_CODE;
    }

    // if this is the first node to be enqueued, set the head and tail to the start node
    if(fifo->head == NULL && fifo->tail == NULL)
    {
    	fifo->head = fifo->start;
    	fifo->tail = fifo->start;

    	fifo->tail->data = data;

    	fifo->length++;
    	__enable_irq();
    	return SUCCESS_CODE;
    }

    // if the tail's next node is NULL, the FIFO is full
    if(fifo->tail->next == NULL)
    {
    	__enable_irq();
    	return ERROR_CODE;
    }

    // enqueue the data and update the tail pointer
    fifo->tail = fifo->tail->next;
    fifo->tail->data = data;

    fifo->length++;

    __enable_irq();
    return SUCCESS_CODE;
}


uint8_t llfifo_dequeue(llfifo_t *fifo) {
	//disable interrupts to make the function atomic
	__disable_irq();

	uint8_t ret;

	if(fifo == NULL) {
		// dequeue failed
		__enable_irq();
		return ERROR_CODE; //return -1 if the given fifo pointer is null
	}

	if(fifo->start == NULL) {
		__enable_irq();
	    return ERROR_CODE; //return -1 if the start pointer is null
	}

	if(fifo->head == NULL) {
		__enable_irq();
		return ERROR_CODE; //return -1 if the head pointer is null
	}

	if(fifo->head == fifo->tail)
	{	//get the data at the head of the fifo
		ret = fifo->head->data;
		//set start pointer to head
		fifo->start = fifo->head;
		//clear head data
		fifo->head->data = 0;
		//clear head pointer
		fifo->head = NULL;
		//clear tail pointer
		fifo->tail = NULL;
		//reset the length of the fifo
		fifo->length = 0;

		__enable_irq();
		return ret; //return the dequeued data
	}
	//get the data at the head of the fifo
	ret = fifo->head->data;
	//clear head data
	fifo->head->data = 0;
	//get the next node after the current head
	struct node *new_head = fifo->head->next;

	struct node *temp = fifo->tail->next;
	//set the next of the new head to the temp
	fifo->head->next = temp;
	//set the next of the tail to the new head
	fifo->tail->next = fifo->head;
	//set the new head
	fifo->head = new_head;
	//set the start to the new head
	fifo->start = fifo->head;
	fifo->length -= 1; //decrement the length of the fifo

	__enable_irq();
	return ret; //return the dequeued data
}

int llfifo_length(llfifo_t *fifo) {
    if (fifo == NULL) {
        return ERROR_CODE;  // if fifo is not created, return error code
    }
    // returns the length of the fifo

    return fifo->length;
}

int llfifo_capacity(llfifo_t *fifo) {
    if (fifo == NULL) {
        return ERROR_CODE;  // if fifo is not created, return error code
    }
    // returns the capacity of the fifo

    return fifo->capacity;
}

int llfifo_is_empty(llfifo_t *fifo) {
    if (fifo->length == 0) {
        return 1;  // if fifo length is zero, it is empty
    } else {
        return 0;  // otherwise, it is not empty
    }
}

int llfifo_is_full(llfifo_t *fifo) {
    if (fifo->length == fifo->capacity) {
        return 1;  // if fifo length is equal to its capacity, it is full
    } else {
        return 0;  // otherwise, it is not full
    }
}
