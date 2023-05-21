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
 * @file hardware_init.c
 * @brief Hardware initialization functions for the test_sine application.
 *
 * This file contains the functions necessary to initialize the hardware for
 * the test_sine application. It initializes the DAC, generates a sine wave,
 * sets up two timers to control the frequency of the sine wave, and initializes
 * the SysTick timer for timing purposes.
 *
 * This file also contains acknowledgments for external resources used in the
 * development of this application.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @reference
 *
 *   1) Alexander G Dean's github repository and Book
 *      https://github.com/alexander-g-dean/ESF/tree/master/
 *
 *   I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *   in understanding and explaining details of requirements.
 */

#include "test_sine.h"
#include "fp_trig.h"
#include "tpm.h"
#include "systick.h"
#include "audio_output.h"
#include "audio_input.h"
#include "hardware_init.h"

#define FREQUENCY_CONTROL 500 /**< Frequency control value for timer 0. */

/**
 * @brief Initializes the hardware for the test_sine application.
 *
 * This function initializes the DAC, generates a sine wave, and sets up two timers
 * to control the frequency of the sine wave. It also initializes the SysTick timer
 * for timing purposes.
 */
void hardware_init(void)
{
	    DAC_initialise();               // initialize DAC
	    tone_to_samples();              // generate sine wave
	    timer_init_TMP0(FREQUENCY_CONTROL);  // initialize timer 0 for frequency control
	    timer_start_TMP0();             // start timer 0
	    init_systick();                 // initialize SysTick timer
	    ADC_initialise();               // initialize DAC again
	    timer_init_TMP1();              // initialize timer 1 for timing purposes
	    timer_start_TMP1();             // start timer 1
}
