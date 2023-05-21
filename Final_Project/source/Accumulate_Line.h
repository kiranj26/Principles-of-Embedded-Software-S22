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
​ ​*​ ​@file​_name     Accumulate_Line.h
​ ​*​ ​@introduction  This header file declares the function "read_and_process_command" which reads
 * input commands from the user via UART, accumulates the input into a circular buffer,
 * and processes the accumulated command using the "process_command" function.
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
*/

#ifndef __ACCUMULATE_LINE_H__
#define __ACCUMULATE_LINE_H__

#include <stdio.h>
#include <string.h>

#include "uart.h"
#include "cbfifo.h"
#include "process_command.h"

/**
 * @brief Reads input commands from the user via UART, accumulates the input into a circular buffer,
 * and processes the accumulated command using the "process_command" function.
 *
 */
void read_and_process_command();

#endif // __ACCUMULATE_LINE_H__
