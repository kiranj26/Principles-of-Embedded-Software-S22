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
 * @file cbfifo.h
 * @brief Header file for circular buffer FIFO implementation
 *
 * This is the header file for the implementation of a circular buffer FIFO. It provides the function declarations for
 * enqueueing, dequeuing, and resetting the FIFO, as well as getting the length and capacity of the buffer.
 *
 * @author Kiran
 * @date May 04 2023
 * @version 1.0
 *
 */

#ifndef __CBFIFO_H__
#define __CBFIFO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <MKL25Z4.H>

typedef enum fifo_buffers {
	transmitter = 0,
	receiver = 1
} fifo_type;

/**
 * @brief Enqueues data into the circular buffer FIFO
 *
 * This function adds data to the end of the specified circular buffer FIFO.
 *
 * @param buf Pointer to the buffer to add data to
 * @param nbyte Number of bytes to add to the buffer
 * @param command_type Type of command to determine which buffer to use (transmitter or receiver)
 *
 * @return The number of bytes actually added to the buffer
 */
size_t cbfifo_enqueue(void *buf, size_t nbyte, uint32_t command_type);

/**
 * @brief Dequeues data from the circular buffer FIFO
 *
 * This function removes data from the front of the specified circular buffer FIFO.
 *
 * @param buf Pointer to the buffer to remove data from
 * @param nbyte Number of bytes to remove from the buffer
 * @param command_type Type of command to determine which buffer to use (transmitter or receiver)
 *
 * @return The number of bytes actually removed from the buffer
 */
size_t cbfifo_dequeue(void *buf, size_t nbyte, uint32_t command_type);

/**
 * @brief Returns the current length of the circular buffer FIFO
 *
 * This function returns the current number of bytes in the specified circular buffer FIFO.
 *
 * @param command_type Type of command to determine which buffer to use (transmitter or receiver)
 *
 * @return The current number of bytes in the buffer
 */
size_t cbfifo_length(uint32_t command_type);

/**
 * @brief Returns the maximum capacity of the circular buffer FIFO
 *
 * This function returns the maximum number of bytes that can be stored in the specified circular buffer FIFO.
 *
 * @param command_type Type of command to determine which buffer to use (transmitter or receiver)
 *
 * @return The maximum capacity of the buffer
 */
size_t cbfifo_capacity(uint32_t command_type);

/**
 * @brief Resets the circular buffer FIFO to an empty state
 *
 * This function resets the specified circular buffer FIFO to an empty state by setting the head and tail pointers to
 * the beginning of the buffer.
 *
 * @param command_type Type of command to determine which buffer to reset (transmitter or receiver)
 */
void cbfifo_reset(uint32_t command_type);

#endif // __CBFIFO_H__
