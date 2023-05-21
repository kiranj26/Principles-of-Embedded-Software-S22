//
///*****************************************************************************
// * Copyright (C) 2023 by Kiran Jojare
// *
// * Redistribution, modification or use of this software in source or binary
// * forms is permitted as long as the files maintain this copyright. Users
// * are permitted to modify this and use it to learn about the field of
// * embedded software. Kiran Jojare and the University of Colorado are not
// * liable for any misuse of this material.
// *****************************************************************************/
//
///**
// * @file
// * @brief
// *
// *
// * @author  Kiran Jojare
// * @date    April 22, 2023
// * @version 1.0
// *
// * @@referense
// *
// * 	 1) Alexander G Dean's github repository and Book
// * 		 https://github.com/alexander-g-dean/ESF/tree/master/
// *
//​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
// *    in understanding and explaining details of requirements.
// */
//
//#ifndef _SYSTICK_H_
//#define _SYSTICK_H_
//
//typedef uint32_t ticktime_t;
//
//void init_systick();
//
//void SysTick_Handler();
//
//void reset_timer();
//
//ticktime_t get_timer();
//
//#endif

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
 * @file systick.h
 * @brief Header file for the SysTick timer module.
 *
 * This header file contains the function prototypes and type definition for the
 * SysTick timer module.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @referense
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
 *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements.
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

typedef uint32_t ticktime_t;  ///< Type definition for the tick time.

/**
 * @brief Initializes the SysTick timer module.
 *
 * This function initializes the SysTick timer module by setting the interrupt
 * priority, enabling the timer interrupt, and configuring the timer to use the
 * processor clock as the time base.
 *
 * @return None.
 */
void init_systick();

/**
 * @brief Interrupt handler for the SysTick timer module.
 *
 * This function is the interrupt handler for the SysTick timer module. It is
 * called every time the timer interrupt occurs, and it increments the tick time
 * by one.
 *
 * @return None.
 */
void SysTick_Handler();

/**
 * @brief Resets the tick time.
 *
 * This function resets the tick time to zero.
 *
 * @return None.
 */
void reset_timer();

/**
 * @brief Gets the current tick time.
 *
 * This function gets the current tick time.
 *
 * @return The current tick time.
 */
ticktime_t get_timer();

#endif //_SYSTICK_H_

