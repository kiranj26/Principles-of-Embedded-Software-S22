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
 * @file  waveform_generation.h
 * @brief Header file for waveform generation function
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


#ifndef _WAVEFORM_PROC_H_
#define _WAVEFORM_PROC_H_

/**
 * @brief   Generates waveform for given frequency and amplitude
 *
 * @param   amplitude: Amplitude of the waveform to be generated
 * @param   frequency: Frequency of the waveform to be generated
 *
 * @return  None
 */
void waveform_processing(void);

#endif // _WAVEFORM_PROC_H_
