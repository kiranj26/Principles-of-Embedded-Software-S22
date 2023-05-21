/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file uart.h
 * @brief Header file for SERIAL UART function
 *
 * This header file contains function declarations for initializing UART and performing read and write operations.
 *
 * @author Kiran Jojare
 * @date   April 9 2022
 * @version 1.0
 *
 * @reference
 * The code in the files "UART.c" and "UART.h" that contains the functions "UART_init" and "UART_IRQ handler" has been sourced
 * from Alexander Dean's Github repository. You can find the link to this repository below..
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c.
 * Code has been twicked little to incorporated use of LLFIFO and issues observed with queue
 */

#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>

/**
 * @brief Initializes the SERIAL UART with the given BAUD RATE.
 *
 * @param baud_rate Desired baud rate.
 *
 * @return None.
 */
void Init_UART0(uint32_t baud_rate);

/**
 * @brief Writes data to the UART.
 *
 * @param handle The handle to the output device.
 * @param buf Pointer to the buffer containing the data to write.
 * @param size The number of bytes to write.
 *
 * @return The number of bytes written.
 */
int __sys_write(int handle, char *buf, int size);

/**
 * @brief Reads a single character from the UART.
 *
 * @param None.
 *
 * @return The character read from the UART.
 */
int __sys_readc(void);

#endif // _UART_H_
