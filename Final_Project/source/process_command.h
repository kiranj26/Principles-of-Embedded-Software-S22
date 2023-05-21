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
 * @file process_command.h
 * @brief Header file for processing user commands
 *
 * This header file contains declarations for functions that process user commands.
 *
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#ifndef __PROCESS_COMMAND_H__
#define __PROCESS_COMMAND_H__

#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.H>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sysclock.h"
#include "uart.h"
#include "test_cbfifo.h"
#include "i2c.h"
#include "sht21.h"
#include "pwm.h"
#include "rgb_led.h"
#include "timer.h"

/**
 * @brief Processes the user command
 *
 * This function processes the user command and performs the corresponding action.
 *
 * @param input User command input
 */
void process_command(char *input);

/**
 * @brief Delays execution for 100ms
 *
 * This function adds a delay of 100ms to the execution.
 */
void delay_100ms(void);

#endif // __PROCESS_COMMAND_H__
