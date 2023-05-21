/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file timing.h
 * @brief Header file for timing functions
 *
 * This header file defines the function prototypes and typedef for timing functions.
 *
 * @author Kiran
 * @date Feb 19 2023
 * @version 1.0
 *
 * @reference Function definitions are used from the assignment document.
 */

#ifndef _TIMING_H_
#define _TIMING_H_

/* Global Define used in other files too */
#define MS62_5 	(62.5L)
#define MS		(100L)

/* time since boot, in sixteenths of a second */
typedef uint32_t ticktime_t;

/**
 * @brief Initializes the timing system
 *
 * This function initializes the timing system, specifically the SysTick timer,
 * to generate interrupts every 62.5 milliseconds.
 *
 * @return none
 */
void init_systick();

/**
 * @brief Returns the time since startup in sixteenths of a second
 *
 * This function returns the time since system startup in sixteenths of a second.
 * The time is calculated by incrementing a counter in the SysTick interrupt handler.
 *
 * @return ticktime_t The time since startup in sixteenths of a second
 */
ticktime_t now();

/**
 * @brief Resets the timer to 0
 *
 * This function resets the timer to 0. The time returned by `now()` is not affected.
 *
 * @return none
 */
void reset_timer();

/**
 * @brief Returns the time elapsed since the last timer reset in sixteenths of a second
 *
 * This function returns the time elapsed since the last timer reset in sixteenths of a second.
 *
 * @return ticktime_t The time elapsed since the last timer reset in sixteenths of a second
 */
ticktime_t get_timer();

/**
 * @brief Handler for the SysTick interrupt
 *
 * This function is the handler for the SysTick interrupt. It increments a counter
 * used by the `now()` function to calculate the time since startup.
 *
 * @return none
 */
void SysTick_Handler();

/**
 * @brief Returns the time elapsed since the last crosswalk reset in sixteenths of a second
 *
 * This function returns the time elapsed since the last crosswalk reset in sixteenths of a second.
 *
 * @return ticktime_t The time elapsed since the last crosswalk reset in sixteenths of a second
 */
ticktime_t get_crosswalk_timer();

/**
 * @brief Resets the crosswalk timer to 0
 *
 * This function resets the crosswalk timer to 0. The time returned by `get_crosswalk_timer()` is not affected.
 *
 */
void reset_crosswalk_timer();

ticktime_t now_tick();

#endif //_TIMING_H_
