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
 * @file hardware_init.h
 * @brief Header file for hardware initialization functions for the test_sine application.
 *
 * This header file contains the function prototype for the `hardware_init()` function,
 * which initializes the hardware for the test_sine application.
 *
 * This header file also contains acknowledgments for external resources used in the
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



#ifndef _HARDWARE_INIT_H_
#define _HARDWARE_INIT_H_

/**
 * @brief Initializes the hardware for the test_sine application.
 *
 * This function initializes the DAC, generates a sine wave, and sets up two timers
 * to control the frequency of the sine wave. It also initializes the SysTick timer
 * for timing purposes.
 */
void hardware_init(void);

#endif // _HARDWARE_INIT_H_
