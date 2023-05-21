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
 * @file    Assignment-7-Waveforms.c
 * @brief	Initializes the board hardware and calls waveform_processing function
 * indefinitely in an infinite while loop.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @@referense
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements.
 */


#include <audio_input.h>               	// include header file for audio input
#include <audio_output.h>              	// include header file for audio output
#include <stdio.h>                     	// include standard input/output library
#include "board.h"                     	// include board header file
#include "peripherals.h"               	// include peripheral header file
#include "pin_mux.h"                   	// include pin multiplexing header file
#include "clock_config.h"              	// include clock configuration header file
#include "MKL25Z4.h"                   	// include processor header file
#include "fsl_debug_console.h"         	// include FSL debug console header file

#include "test_sine.h"                 	// include header file for testing sine wave
#include "fp_trig.h"                   	// include header file for fixed-point trigonometry functions
#include "tpm.h"                       	// include header file for timer peripheral module
#include "systick.h"                   	// include header file for system tick
#include "audio_output.h"              	// include header file for audio output
#include "audio_input.h"               	// include header file for audio input
#include "hardware_init.h"             	// include header file for initializing hardware
#include "waveform_processing.h"       	// include header file for processing waveforms

#define FREQUENCY_CNTRL 500            	// define frequency control macro as 500


/*
 * @brief   Application entry point.
 *
 * Initializes the board hardware and calls waveform_processing function
 * indefinitely in an infinite while loop.
 *
 * @return  0
 */

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();					// Initialize pins
    BOARD_InitBootClocks();					// Initialize clocks
    BOARD_InitBootPeripherals();			// Initialize peripherals
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();				// Initialize debug console
#endif

    PRINTF("Assignment 7.... Getting in waveforms !!!\n\r");  // Print message

    test_sin();         					// Generate a sine wave for testing purposes

    hardware_init();    					// Initialize hardware for audio processing

    audio_output();     					// Initialize audio output

    while(1) {
    	waveform_processing();  			// Process waveforms in an infinite loop
        __asm volatile ("nop");
    }

    return 0;
}
