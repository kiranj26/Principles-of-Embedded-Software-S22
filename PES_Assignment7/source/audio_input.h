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
 * @file	audio_input.h
 * @brief 	Header file for ADC functionality
 *
 * This header file contains the function prototypes for initializing, calibrating and performing
 * analysis on the analog signal from the audio input.
 *
 * The functions included are:
 *      ADC_initialise - Initializes the ADC for reading the analog signal
 *      ADC_Calibration - Performs calibration of the ADC to get accurate readings
 *      audio_input - Reads the analog signal and converts it to digital value
 *      audio_analysis - Performs analysis on the digital signal and outputs the result
 *      delay - Delays execution for a specified number of milliseconds
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

#ifndef _AUDIO_INPUT_H_
#define _AUDIO_INPUT_H_


/*
 * Initializes the ADC for reading the analog signal
 *
 * Parameters:
 *    None
 *
 * Returns:
 *    None
 */
void ADC_initialise(void);

/*
 * Performs calibration of the ADC to get accurate readings
 *
 * Parameters:
 *    None
 *
 * Returns:
 *    None
 */
void ADC_Calibration(void);

/*
 * Reads the analog signal and converts it to digital value
 *
 * Parameters:
 *    None
 *
 * Returns:
 *    None
 */
void audio_input(void);

/*
 * Performs analysis on the digital signal and outputs the result
 *
 * Parameters:
 *    None
 *
 * Returns:
 *    None
 */
void audio_analysis(void);

/*
 * Delays execution for a specified number of milliseconds
 *
 * Parameters:
 *    n  Number of milliseconds to delay execution
 *
 * Returns:
 *    None
 */
void delay(int n);


#endif // _AUDIO_INPUT_H_
