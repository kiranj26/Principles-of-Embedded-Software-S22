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
* @file   timer.c
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


#include"timer.h"

// global variables to keep track of timer values
volatile ticktime_t timer_value = 0;
volatile ticktime_t timer_reset_value = 0;
volatile ticktime_t time_in_alert_mode = 0;
volatile ticktime_t time_in_reset_alert_mode = 0;

void init_systick()
{
    // set the systick timer value
    SysTick->LOAD = systick_value;
    // set the interrupt priority
    NVIC_SetPriority(SysTick_IRQn, 3);
    // reset the current value
    SysTick->VAL = 0;
    // enable interrupt and the timer
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
    // increment the timer value
    timer_value++;
    time_in_alert_mode++;
}

ticktime_t now()
{
    // returns the current timer value
    return (timer_value);
}

ticktime_t now_alert_time()
{
    // returns the current alert timer value
    return (time_in_alert_mode);
}

void reset_timer()
{
    // reset the timer value
    timer_reset_value = now();
    // reinitialize the systick
    init_systick();
}

void reset_alert_mode_timer()
{
    // reset the alert mode timer value
    time_in_reset_alert_mode = now_alert_time();
    // reinitialize the systick
    init_systick();
}

ticktime_t get_timer()
{
    // returns the elapsed time since the last reset_timer() call
    return (timer_value - timer_reset_value);
}

ticktime_t get_alert_time()
{
    // returns the elapsed time since the last reset_alert_mode_timer() call
    return (time_in_alert_mode - time_in_reset_alert_mode);
}
