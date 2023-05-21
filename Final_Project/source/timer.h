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
 * @file timer.h
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

#ifndef __TIMER_H__
#define __TIMER_H__

#include <MKL25Z4.h>
#include <stdio.h>
#include <stdlib.h>

#define PWM_PERIOD (255)
#define systick_value (30000)

typedef uint32_t ticktime_t;

/**
 * @brief Initializes the systick timer.
 */
void init_systick();

/**
 * @brief Interrupt handler for the systick timer.
 */
void SysTick_Handler();

/**
 * @brief Gets the current time in milliseconds since startup.
 *
 * @return The current time in milliseconds.
 */
ticktime_t now();

/**
 * @brief Gets the current time in milliseconds since the last call to reset_alert_mode_timer().
 *
 * @return The time since the last call to reset_alert_mode_timer().
 */
ticktime_t now_alert_time();

/**
 * @brief Resets the timer to zero.
 */
void reset_timer();

/**
 * @brief Resets the alert mode timer to zero.
 */
void reset_alert_mode_timer();

/**
 * @brief Gets the current time in milliseconds since the last call to reset_timer().
 *
 * @return The time since the last call to reset_timer().
 */
ticktime_t get_timer();

/**
 * @brief Gets the current time in milliseconds since the last call to reset_alert_mode_timer().
 *
 * @return The time since the last call to reset_alert_mode_timer().
 */
ticktime_t get_alert_time();

#endif // __TIMER_H__
