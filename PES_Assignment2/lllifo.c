/***************************************************************************** 
​ ​*​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ ​* 
​ ​*​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary 
​ ​*​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are  
​ ​*​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded 
​ ​*​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado Boulder​ ​are​ ​not​ ​liable​ ​for  
​ ​*​ ​any​ ​misuse​ ​of​ ​this​ ​material.  
​ ​* 
*****************************************************************************/ 

/** 
​ ​*​ ​@file​_name   llifo.c
​ ​*​ ​@information Linked list-based LIFO functions are implemented in this file. 
 *              The various algorithms required for LIFO are tracked in a file.
​ ​* 
​ ​*​ ​@author​ ​Kiran Jojare 
​ ​*​ ​@date​ ​Feb 7 2023 
​ ​*​ ​@version​ ​4.1 
​ ​* 
 * @referense 
 *   1) https://en.wikipedia.org/wiki/Circular_buffer
 *   2) https://medium.com/@charlesdobson/how-to-implement-a-simple-circular-buffer-in-c-34b7e945d30e
 *   3) https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 *   4) Modern Embedded System Books by White
 * 
 *   I would like to thank the SA's of the course Daanish, Hari and Ritika for their 
 *   support to debug the Linkedlist FIFO Implementation for test coverage. 
​ ​*/


/* Include Files */
#ifndef _LLIIFO_C_
#define _LLIIFO_C_

/* Include files */
#include"lllifo.h"

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#define ERROR_CODE -1   // return -1 if error found
#define MAX_INT_VALUE 0x7FFFFFFF 

struct node {
  void *data;           // pointer to the data stored in this node
  struct node *next;    // pointer to the next node in the linked list
};

struct lllifo_s {
  int capacity;         // maximum number of nodes in the linked list
  int length;           // current number of nodes in the linked list
  struct node *head;    // pointer to the head node of the linked list
};

/**
 * @brief 
 * creates a linked list LIFO data structure with specified capacity
 * @param 
 * capacity: the maximum number of elements that can be stored in the linked list
 * @returns 
 * On success, this function returns a pointer to the newly created linked list LIFO data structure, and on failure, 
 * it returns NULL (for instance, if the capacity is negative or memory allocation fails).
 * 
 * With the help of this function, you can build a linked list LIFO (last-in, first-out) structure with a certain amount of space.
 * It receives a pointer to the lllifo t structure in exchange for an integer argument capacity.
 * It returns NULL if the specified capacity is negative or exceeds the upper limit. The lllifo t structure also returns NULL 
 * if memory allocation fails. When the capacity is zero, the created structure is returned without any new nodes being added.
 * The required number of nodes are created, linked together, and the linked list's * head pointer is set to the first node 
 * if the capacity is greater than zero. The function returns the lllifo t pointer for the linked list structure that was created.
 */

lllifo_t *lllifo_create(int capacity) {
    int i;
    struct node *current = NULL;
    if (capacity > MAX_INT_VALUE) {                 // return NULL is the capacity is above maximum possible range of signed integer
        return NULL;
    }
    if (capacity < 0){ 
        return NULL;                                // return error if capacity is negative
    }
    lllifo_t *lifo = malloc(sizeof(lllifo_t));      // allocate memory for the containing structure
    if (lifo == 0) {
        return NULL;                                // return error if memory allocation fails
    }
    lifo->length   = 0;                             // initially, the linked list is empty
    lifo->capacity = capacity;
    lifo->head     = NULL;                          // head pointer is set to NULL

    if (capacity == 0) {                            // return the containing structure if capacity is 0
        return lifo;
    }
    
    // create the required number of nodes and link them
    for (i = 0; i < capacity; i++) {
        struct node *new_node = malloc(sizeof(struct node));
        if (!new_node) {
            // return NULL;                         // return error if memory allocation fails
            lllifo_destroy(lifo);                   // clear partially created NODES is malloc on elements fails
        }
        new_node->data = NULL;                      // initially, the data in each node is set to NULL
        new_node->next = NULL;                      // each node's next pointer is set to NULL

        if (i == 0) {                               // set the head pointer to the first node
            lifo->head = new_node;
            current = new_node;
        } else {                                    // link the current node to the previous node
            current->next = new_node;
            current = new_node;
        }
    }
    return lifo;                                    // return the containing structure
}

/** 
 * @brief 
 * Pushes an element onto the LIFO (Last In First Out) linked list.
 * @param 
 * lifo    - Pointer to the LIFO linked list structure
 * element - Pointer to the element to be pushed onto the LIFO linked list
 * @return 
 * On success, the new length of the LIFO linked list, and -1 on failure.
 * 
 * By making a new node, adding an element to it, linking the new node to the existing head node, 
 * and setting the head node to the new node, this function pushes an element onto the LIFO linked list.
 * The capacity is increased by one if the length of the linked list is equal to the capacity.
 * The function returns -1 if memory allocation is unsuccessful.
*/
int lllifo_push(lllifo_t *lifo, void *element) {
    
    if (lifo->capacity > MAX_INT_VALUE) {
        return ERROR_CODE;                          // Check if the capacity exceeds the limit
    }
    if (lifo->length >= lifo->capacity) {
        lifo->capacity++;                           // Increase the capacity if the length is equal to the capacity
    }
    // Allocate memory for a new node
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == 0) {
        return ERROR_CODE;                          // Return -1 if memory allocation fails
    }

    new_node->data = element;                       // Assign the element to the new node
    new_node->next = lifo->head;                    // Set the next node to the current head node

    lifo->head = new_node;                          // Set the head node to the new node
    lifo->length++;                                 // Increase the length of the lifo
    
    return lifo->length;                            // Return the new length of the lifo
}

/**
 * @brief
 * Remove and return the element at the head of a linked list lifo
 * @param
 * lifo: the linked list lifo to pop the element from
 * @returns:
 * On success, returns the popped element, or NULL if the lifo is NULL or the head node is NULL
 * 
 * 
 * This function removes the first element of the linked list and returns it. 
 * If either the lifo or the head node is NULL, the function returns NULL.
 *
 */
void *lllifo_pop(lllifo_t *lifo) {
    if (lifo == 0) {
        return NULL;
    }                                               // Check if the lifo is NULL
    if (lifo->head == 0) {
        return NULL;
    }                                               // Check if the head node is NULL
    if(lifo->length == 0) {
        return NULL;
    }                                               // check if the pop is recieved for empty stack
    struct node *to_pop = lifo->head;               // Get the node to pop
    lifo->head = to_pop->next;                      // Set the head node to the next node
    lifo->length--;                                 // Decrease the length of the lifo
    void *element = to_pop->data;                   // Get the element from the node
    free(to_pop);                                   // Free the node memor
    return element;                                 // Return the popped element
}

/**
 * @brief 
 * function gives the linked list's LIFO (last-in, first-out) stack's length.
 * @param 
 * lifo - is a pointer to the linked list LIFO (last-in-first-out) stack's lllifo t structure.
 * @return 
 * On success, returns int - The length of the LIFO (last-in-first-out) stack for linked lists. The function returns -1 if the stack pointer that was passed in is NULL.
*/
int lllifo_length(lllifo_t *lifo) {
    if (lifo == 0) {
        return ERROR_CODE;                          // If the passed in stack pointer is NULL, return -1
    }
    return lifo->length;                            // Return the length of the linked list stack
}

/**
 * @brief 
 * lllifo_capacity function takes in a pointer to a lllifo_t structure and returns the capacity of the linked list LIFO (last-in-first-out) stack.
 * @param 
 * lifo - pointer to lllifo_t structure representing the linked list LIFO (last-in-first-out) stack
 * @return 
 * int - capacity of the linked list LIFO (last-in-first-out) stack. If the passed in stack pointer is NULL, the function returns -1.
*/
int lllifo_capacity(lllifo_t *lifo) {
    if (lifo == 0) {
        return ERROR_CODE;                           // If the passed in stack pointer is NULL, return -1
    }
    return lifo->capacity;                           // Return the capacity of the linked list stack
}

/**
 * @brief 
 * function releases the linked list LIFO (last-in-first-out) stack's memory.
 * @param 
 * lifo - a pointer to the linked list stack structure
 * @returns 
 * None
 * 
 * The function releases the memory used by the stack and accepts an argument that points to the linked list stack structure. 
 * The function returns immediately with no action taken if the passed-in stack pointer is NULL.
 * By moving the head pointer to the following node and releasing the current node, the function iterates through the linked list 
 * stack and releases the memory associated with each node. The function releases all of the nodes before releasing the linked list 
 * stack's memory and setting the freed stack pointer to NULL.
 */
void lllifo_destroy(lllifo_t *lifo) {
    if (lifo == 0) {
        return;                                     // If the passed in stack pointer is NULL, return
    }

    while (lifo->head) {                            // Traverse the linked list stack and free up each node's memory
        struct node *to_free = lifo->head;
        lifo->head = to_free->next;
        free(to_free);
        to_free = NULL;                             // Set the freed node pointer to NULL
    }
    free(lifo);                                     // Free up the memory occupied by the linked list stack
    lifo = NULL;                                    // Set the freed stack pointer to NULL
}

#endif //_LLIIFO_C_

