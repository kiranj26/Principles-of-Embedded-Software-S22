/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Kiran Jojare and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/

/**
* @file   timing.c
* @brief  Main timer functions file
*
* This file contains the implementation of timer functions used for tracking time
* in the system.
*
* @author Kiran
* @date   Feb 19 2023
* @version 1.0
*
* @reference
* 1) https://github.com/alexander-g-dean/ESF/blob/master/ST/Code/ch7/SysTick/main.c
* 2) Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
*    https://github.com/alexander-g-dean/ESF/tree/master
*
*    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support in understanding and explaining
*    details of requirements
*/

#ifndef _TIMING_C_
#define _TIMING_C_

/* Required Headers */
#include "fsl_debug_console.h"
#include "core_cm0plus.h"
#include "Timing.h"

/* Required macro defination
 * this are local to this files so they are included in .c file */

#define F_SYS_CLK           	(3000000L)					// Clock divided by 16
#define DIVIDEBY_16         	(16)						// Divide by 16
#define SYSTICK_INRPT_PRIORITY 	(3)							// Sys-tick Interrupt Priority of 3
#define ZERO					(0)							// Value 0
#define ONE						(1)							// Value 1

/* Global data for timings */
static volatile ticktime_t Time_SinceBoot 			= 0;        // Time since system boot
static volatile ticktime_t Time_SinceLastReset 		= 0;   		// Time since last timer reset
static volatile ticktime_t Time_CrossWalkTime 		= 0;    	// Time since last cross-walk button press

/**
 * @brief Initializes the SysTick timer
 *
 * This function initializes the SysTick timer to generate 62.5ms interrupts, sets the
 * interrupt priority, and enables the timer and interrupt.
 *
 * @return none
 */
void init_systick()
{
    // Set the reload value for the SysTick timer to generate 62.5ms interrupts
    SysTick->LOAD = (F_SYS_CLK / DIVIDEBY_16) - ONE;

    // Set the interrupt priority for the SysTick interrupt
    NVIC_SetPriority(SysTick_IRQn, SYSTICK_INRPT_PRIORITY);

    // Force a reload of the SysTick timer reload value
    SysTick->VAL = ZERO;

    // Enable the SysTick interrupt, enable the SysTick timer, and use the system clock as the timer source
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief SysTick interrupt handler
 *
 * This function is the interrupt handler for the SysTick timer interrupt. It updates the
 * time since boot, time since the last reset, and time since the last crosswalk button press.
 *
 * @return none
 */
void SysTick_Handler()
{
    Time_SinceBoot 		+= 1;	// Increment by 1
    Time_SinceLastReset += 1;	// Increment by 1
    Time_CrossWalkTime 	+= 1;	// Increment by 1
}

/**
 * @brief Returns the current system time in milliseconds
 *
 * This function returns the current system time in milliseconds by accessing a global variable
 * that tracks the time since system boot.
 *
 * @return ticktime_t The current system time in milliseconds
 */
ticktime_t now() {
    return (Time_SinceBoot * MS62_5);
}

ticktime_t now_tick() {
    return (Time_SinceBoot);
}

/**
 * @brief Resets the timer to 0
 *
 * This function resets the timer to 0 by setting a global variable that tracks the time since the
 * last timer reset to 0.
 *
 * @return none
 */
void reset_timer() {
    Time_SinceLastReset = ZERO;
}

/**
 * @brief Returns the time elapsed since the last timer reset in milliseconds
 *
 * This function returns the time elapsed since the last timer reset in milliseconds by calculating
 * the difference between the current system time and the time of the last reset.
 *
 * @return ticktime_t The time elapsed since the last timer reset in milliseconds
 */
ticktime_t get_timer() {
	return (Time_SinceLastReset);
}

/**
 * @brief Resets the crosswalk timer to 0
 *
 * This function resets the crosswalk timer to 0 by setting a global variable that tracks the time
 * since the last reset to 0.
 *
 * @return none
 */
void reset_crosswalk_timer() {
    Time_CrossWalkTime = ZERO;
}

/**
 * @brief Returns the time elapsed since the last crosswalk timer reset in milliseconds
 *
 * This function returns the time elapsed since the last crosswalk timer reset in milliseconds
 * by calculating the difference between the current system time and the time of the last reset.
 *
 * @return ticktime_t The time elapsed since the last crosswalk timer reset in milliseconds
 */
ticktime_t get_crosswalk_timer() {
	return Time_CrossWalkTime;
}

#endif //_TIMING_C_
