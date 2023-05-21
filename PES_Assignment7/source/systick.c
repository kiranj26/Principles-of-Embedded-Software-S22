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
 * @file systick.c
 * @brief File containing the implementation of the system timer (SysTick) module
 *
 * This file contains the implementation of the functions declared in the systick.h header
 * file. The SysTick module provides functionality for getting and resetting a timer
 * based on the system clock.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @references
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
 *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements.
 */

#include "MKL25Z4.h"
#include "systick.h"

// define the system clock frequency
#define SYSTEM_CLOCK (48000000UL)
// define the number of ticks per second for the timer
#define TICKS_PER_SECOND (100)
// define the number of ticks per time value (1 ms)
#define TICKS_PER_TIME (48000)

// calculate the timer load value
#define SYSTICK_LOAD_VALUE ((SYSTEM_CLOCK/TICKS_PER_SECOND) - 1)
// calculate the time value of each timer tick
#define SYSTICK_TIME_VALUE ((SYSTEM_CLOCK/TICKS_PER_SECOND) / TICKS_PER_TIME)

// variable to store the time value of each timer tick
ticktime_t systick_time = 0;
// variable to store the current timer value
ticktime_t get_time = 0;

/**
 * @brief Initializes the system timer (SysTick) module
 *
 * This function initializes the SysTick module by configuring the timer load value,
 * setting the timer value to 0, setting the interrupt priority, and enabling the timer.
 *
 * @return None
 */
void init_systick() {
    SysTick->LOAD = SYSTICK_LOAD_VALUE;    // set the timer load value
    SysTick->VAL = 0;                      // set the timer value to 0
    systick_time = SYSTICK_TIME_VALUE;     // set the time value of each timer tick
    NVIC_SetPriority(SysTick_IRQn, 3);     // set the interrupt priority
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;    // enable the timer
}

/**
 * @brief SysTick interrupt handler
 *
 * This function is called whenever the SysTick timer overflows. It updates the
 * current timer value by adding the time value of each timer tick to the current value.
 *
 * @return None
 */
void SysTick_Handler() {
	// update the current timer value
    get_time += systick_time;
}


/**
 * @brief Returns the current timer value.
 *
 * This function returns the current timer value stored in the global variable
 * get_time. The timer value is incremented by the SYSTICK_TIME_VALUE in the
 * SysTick_Handler() function which is called every SYSTICK_TIME_VALUE seconds.
 *
 * @return Current timer value in milliseconds.
 */
ticktime_t get_timer() {
    return get_time;
}

/**
 * @brief Resets the timer value to 0.
 *
 * This function sets the global variable get_time to 0, which is used to store
 * the current time of the system. This effectively resets the timer value to 0.
 *
 * @return None
 */
void reset_timer() {
    get_time = 0;
}
