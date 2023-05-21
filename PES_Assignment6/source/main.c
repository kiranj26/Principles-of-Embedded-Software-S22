/*****************************************************************************
 * Copyright (C) 2023 by Kiran Jojare
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of
 * embedded software. Kiran Jojare and the University of Colorado are not
 * liable for any misuse of this material.
 *****************************************************************************/

/**
 * @file    main.c
 * @brief   Main file for PES Assignment 6
 *          This assignment works on providing UARt based serial command intepreter
 *          running over UART0. Serial intepretor is implemented to help QA team to
 *          fully excersise new board. A linkedlist queue has been developed and
 *          tested throughly. UART0 has been configured for Trasmittion and
 *          Reception over UART.
 *
 * @author  Kiran Jojare
 * @date    March 3, 2023
 * @version 1.0
 *
 * @@referense
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements. Additionally I want to thank
 *    Daniel Mendez and Saurav negi for helping and explainning the preprosessor macro used for info
 *    command and LLFIFO issues respetively.
 */

// Include standard C headers
#include <string.h>
#include <stdio.h>

// Include headers for the system clock, UART, hexdump, and command processor
#include "sysclock.h"
#include "uart.h"
#include "hexdump.h"
#include "command_processor.h"

// Define the UART baud rate
#define BAUD_RATE (38400)

int main(void)
{
    // Initialize the system clock
    sysclock_init();

    // Initialize UART0 with the specified baud rate
    Init_UART0(BAUD_RATE);

    // Print a welcome message in bold font
    printf("\n\r\033[1mWelcome to BreakfastSerial!\033[0m\n\r");

    // Enter the main loop
    while (1) {
        // Print the command prompt
        printf("$$ ");

        // Process the user command by accumulating it and then processing it
        process_cmd(accumulate_cmd());

        // A no-operation instruction that adds a delay to the loop
        __asm volatile ("nop");
    }

    // The main function should never return, but if it does, return 0
    return 0;
}

