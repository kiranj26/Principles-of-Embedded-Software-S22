/***************************************************************************** 
​ ​*​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ ​* 
​ ​*​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary 
​ ​*​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are  
​ ​*​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded 
​ ​*​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for  
​ ​*​ ​any​ ​misuse​ ​of​ ​this​ ​material.  
​ ​* 
*****************************************************************************/ 

/** 
​ ​*​ ​@file_name​    cbfifo.c
​ ​*​ ​@introduction​ This file is used to implement different Circular Buffer based FIFO functions
​ ​*​               File maintains the different algorithm requred for FIFO
​ ​* 
​ ​*​ ​@author​ ​Kiran Jojare
​ ​*​ ​@date​ ​Feb 7 2023 
​ ​*​ ​@version​ ​5.0 
​ ​* 
 * @referense 
 *   1) https://medium.com/@charlesdobson/how-to-implement-a-simple-circular-buffer-in-c-34b7e945d30e
 *   2) https://embedjournal.com/implementing-circular-buffer-embedded-c/
 *   3) Modern Embedded System book by White
 * 
 *  I would like to thank the SA's of the course Daanish, Hari and Ritika for their 
 *  support to debug the Linkedlist FIFO Implementation for test coverage. 
 * 
​ ​*/

#ifndef _CBFIFO_C_
#define _CBFIFO_C_

/* Include Files */
#include "cbfifo.h"             // header file for circular buffer FIFO
#include <stddef.h>             // for size_t data type
#include <string.h>             // for memcpy function
#include <assert.h>             // for assert function


#define CBFIFO_SIZE 256         // size of the buffer
#define ZERO 0                  // return 0

// struct to define the circular buffer FIFO
typedef struct {
    size_t length;              // length of the data stored in the buffer
    size_t capacity;            // capacity of the buffer
    size_t head;                // head of the buffer
    size_t tail;                // tail of the buffer
    char buffer[CBFIFO_SIZE];   // buffer to store the data
} CircularBufferFifo;

// global variable to store the buffer information
static CircularBufferFifo cbfifo = { .capacity = CBFIFO_SIZE };

/**
 * @brief 
 * Data is enqueued onto the FIFO up to the FIFO's maximum capacity.
 * @param
 * buf: pointer to the buffer to enqueue
 * nbyte: number of bytes to enqueue
 * @returns:
 * size_t: number of bytes enqueued into the circular buffer FIFO
 * 
 * Data is added into the circular buffer FIFO using this function. 
 * It determines whether there is room in the buffer and updates the head, tail, and length as necessary. 
 * It gives back 0 if the buffer is full.
 */

size_t cbfifo_enqueue(void *buf, size_t nbyte) {
    if (buf == NULL) {
        return ZERO;                    // return 0 if buffer is NULL
    }                                  
    if (nbyte <= 0 || cbfifo.length == cbfifo.capacity)  {
        return ZERO;                    // return 0 if nbyte is 0 or greater than CBFIFO_SIZE or buffer is full
    }                                 

    size_t available_space = cbfifo.capacity - cbfifo.length;   // available space in the buffer

    if (nbyte > available_space) {
        nbyte = available_space;                                // update nbyte if it is greater than the available space
    }

    size_t end_space = CBFIFO_SIZE - cbfifo.tail;               // space available at the end of the buffer
    if (nbyte > end_space) {
        memcpy(cbfifo.buffer + cbfifo.tail, buf, end_space);    // copy the data to the end of the buffer
        memcpy(cbfifo.buffer, (char *)buf + end_space, nbyte - end_space); // copy the remaining data to the beginning of the buffer
    } else {
        memcpy(cbfifo.buffer + cbfifo.tail, buf, nbyte);        // copy the data to the buffer
    }

    cbfifo.tail = (cbfifo.tail + nbyte) % CBFIFO_SIZE;          // update the tail of the buffer
    cbfifo.length += nbyte;                                     // update the length of the data stored in the buffer

    return nbyte;                                               // return the number of bytes enqueued
}


/**
 * @brief 
 * Function tries to "dequeue" (or remove from the FIFO) up to nbytes of data. The buffer that buf points 
 * to will receive copied data that has been removed.
 * @param 
 * buf: pointer to the buffer to store the dequeued data nbyte: number of bytes to dequeue
 * @return: 
 * On succeess, the number of bytes dequeued
 * 
 * This function removes a certain amount of data from the circular buffer. In the event that either 
 * buf or nbyte are NULL or less, the function returns 0. If the circular buffer is empty, the function 
 * returns 0. If nbyte is greater than the size of the buffer, nbyte is set to the size of the buffer. 
 * The dequeue's data is stored in buf. The head and length of the buffer are updated to reflect the change.
 * 
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte) {
    if (buf == NULL || nbyte <= 0) {
        return ZERO;                                        // Check if buf is NULL or nbyte is 0 or less
    }
    if (cbfifo.length == 0){ 
        return ZERO;                                        // Check if the circular buffer is empty
    }
    if (nbyte > cbfifo.length) nbyte = cbfifo.length;       // If nbyte is greater than the length of the buffer, set nbyte to the length of the buffer

    size_t end_space = CBFIFO_SIZE - cbfifo.head;           // Calculate the end space of the buffer

    // If nbyte is greater than end_space, split the dequeue operation into two memcpy
    if (nbyte > end_space) {
        memcpy(buf, cbfifo.buffer + cbfifo.head, end_space);
        memcpy((char *)buf + end_space, cbfifo.buffer, nbyte - end_space);
    } else {
        memcpy(buf, cbfifo.buffer + cbfifo.head, nbyte);    // If nbyte is less or equal to end_space, use a single memcpy
    }

    cbfifo.head = (cbfifo.head + nbyte) % CBFIFO_SIZE;      // Update the head and length of the buffer
    cbfifo.length -= nbyte;                                 // Return the number of bytes dequeued
    return nbyte;
}

/**
 * @brief 
 * Returns the number of bytes currently on the FIFO.
 * @return: 
 * On success, returns the length of the buffer
 * 
 * The circular buffer's length is returned by this function.
 * 
 */
size_t cbfifo_length() {
    return cbfifo.length;
}

/**
 * @brief 
 * Get the capacity of the circular buffer
 * @return: 
 * On success, returns the capacity of the buffer
 * 
 * The circular buffer's capacity is returned by this function.
 *
 */
size_t cbfifo_capacity() {
    return cbfifo.capacity;
}

#endif