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
 * @file  waveform_processing.c
 * @brief Implementation of waveform_processing function
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

#include "tpm.h"
#include "test_sine.h"
#include "fp_trig.h"
#include "systick.h"
#include "audio_output.h"
#include "audio_input.h"
#include "hardware_init.h"
#include "waveform_processing.h"

// Define constant value for one second
#define ONE_SECOND 	(825)

/**
 * @brief Perform waveform processing on audio signals.
 *
 * This function checks if one second has elapsed using the timer and calls audio_analysis
 * and audio_output functions if true. It also calls audio_input function to get audio input.
 *
 * @return void
 */
void waveform_processing()
{
	// Initialize elapsed time
	uint32_t time_elapsed = get_timer();

	// Check if one second has elapsed
	if(time_elapsed >= ONE_SECOND) {

		// Call audio analysis function
		audio_analysis();
		// Call audio output function
		audio_output();
	}

	// Call audio input function
	audio_input();
}
