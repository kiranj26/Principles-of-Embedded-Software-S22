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
 * @file uart.h
 * @brief This header file contains functions to initialize UART0 and print user interface via UART.
 *
 */

#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.H>
#include "fsl_debug_console.h"
#include "process_command.h"
#include "cbfifo.h"

/**
 * @brief Initializes UART0 with the given baud rate
 *
 * This function initializes UART0 with the given baud rate.
 *
 * @param[in] baud_rate The desired baud rate for UART0
 */
void Init_UART0(uint32_t baud_rate);

/**
 * @brief Prints the User Interface menu
 *
 * This function prints the User Interface menu to the console.
 */
void print_UI(void);


#endif // __UART_H__
