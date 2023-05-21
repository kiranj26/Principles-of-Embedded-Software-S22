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
​ ​*​ ​@file​_name     cbfifo.c
​ ​*​ ​@introduction  C file containing the functions for CBFIFO implementation
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
*/

#include"cbfifo.h"

#define CB_size (256)   //Define maximum CBFIFO byte size

typedef struct circular_buffer
{
    uint8_t buffer[CB_size];
    int write;
    int read;
    int buffer_length;
} cbfifo;

cbfifo CB_fifo_type[2];

size_t cbfifo_enqueue(void *buf, size_t nbyte, uint32_t command_type)
{
    size_t length_e = 0;                                   	// declaring variable
    uint32_t primask;
    if (buf == NULL)                     					//Checking whether buf is equal to NULL
    {
        return -1;                                         	// Return Value
    }
    else if (nbyte == 0)               						// Checking whether nbyte is equal to 0
    {
        return 0;                                          	// Return Value
    }
    //Checking whether buffer length is more than or equal to maximum size
    else if (CB_fifo_type[command_type].buffer_length >= CB_size)
    {
        return 0;                                          // Return Value
    }
    // If nbyte is more than difference of maximum size and length of buffer
    else if (nbyte > (CB_size - CB_fifo_type[command_type].buffer_length))
    {
        nbyte = CB_size - CB_fifo_type[command_type].buffer_length; 	// Assigning value of nbyte
    }
    {
        primask = __get_PRIMASK();

        __disable_irq();

        for (int i = 0; i < nbyte; i++)                   	// For loop to enqueue
        {
            //filling data into the buffer
            CB_fifo_type[command_type].buffer[CB_fifo_type[command_type].write] = *(uint8_t*) (buf + i);
            length_e++;                  					//Incrementing length of bytes enqueued
            CB_fifo_type[command_type].buffer_length++; 	//Incrementing the length of buffer
            CB_fifo_type[command_type].write++; 			//Incrementing the write pointer
            if (CB_fifo_type[command_type].write == CB_size)//If write pointer reaches maximum size
            {
                CB_fifo_type[command_type].write = 0; 		//Write pointer points to beginning i.e. 0
            }

        }

        __set_PRIMASK(primask);
        return length_e;                 					//Returning the total elements enqueued
    }
}


size_t cbfifo_dequeue(void *buf, size_t nbyte, uint32_t command_type)
{

    size_t length_d = 0;                                   	// declaring variable
    uint32_t primask;

    if (buf == NULL)                     					//Checking whether buf is equal to NULL
    {
        return -1;                                          // Return Value
    }
    else if (CB_fifo_type[command_type].buffer_length == 0)   //Checking whether buffer length is equal to 0
    {
        return 0;                                          // Return Value
    }
    else if (nbyte == 0)               				     // Checking whether nbyte is equal to 0
    {
        return 0;                                          // Return Value
    }
    else if (nbyte > CB_fifo_type[command_type].buffer_length)   // If nbyte is more than length of buffer
    {
        nbyte = CB_fifo_type[command_type].buffer_length;  // Assign length of buffer to nbyte
    }
    else
    {
        nbyte = nbyte;                					   //else let nbyte value remain unchanged
    }

    primask = __get_PRIMASK();

    __disable_irq();

    for (int i = 0; i < nbyte; i++)                 		// For loop to dequeue bytes
    {
        // dequeuing bytes to location pointed by buff
        *(uint8_t*) buf = CB_fifo_type[command_type].buffer[CB_fifo_type[command_type].read];
        length_d++;                     					// Incrementing length of bytes dequeued
        CB_fifo_type[command_type].buffer_length--; 		// Decrementing buffer length
        buf = (uint8_t*) buf + 1;                         	// Incrementing buffer
        CB_fifo_type[command_type].read++;          		// Incrementing read pointer
        if (CB_fifo_type[command_type].read == CB_size) 	// If read pointer reaches maximum size
        {
            CB_fifo_type[command_type].read = 0; 			// Read pointer points to beginning i.e. 0
        }

        __set_PRIMASK(primask);
    }
    return length_d;                    					// Returning the total elements dequeued
}


size_t cbfifo_length(uint32_t command_type)
{
    return CB_fifo_type[command_type].buffer_length; 		//Returning length of buffer
}


size_t cbfifo_capacity(uint32_t command_type)
{
    return CB_size;                   						//Returning the maximum capacity of CBFIFO
}

void cbfifo_reset(uint32_t command_type)
{
    CB_fifo_type[command_type].buffer_length = 0;
    CB_fifo_type[command_type].read = 0;
    CB_fifo_type[command_type].write = 0;
}
