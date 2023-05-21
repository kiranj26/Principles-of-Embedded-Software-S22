/*****************************************************************************
 * Copyright (C) 2023 by Kiran Jojare
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of embedded
 * software. Kiran Jojare and the University of Colorado are not liable for
 * any misuse of this material.
 *
 *****************************************************************************/

/**
 * @file   TSI_Sensor.h
 * @brief  Header file for PWM LED functions on ARM Cortex-M0+ micro-controller
 *
 * This file contains the declarations for the PWM LED functions that can be
 * used to control an RGB LED using pulse width modulation on an ARM Cortex-M0+
 * microcontroller.
 *
 * @author Kiran
 * @date   Feb 19 2023
 * @version 1.0
 *
 * @references
 */

#ifndef _PWM_LED_FUNC_H_
#define _PWM_LED_FUNC_H_

/* This macro is also used by the function main.c
 * hence its in header file and not .c file */
#include <stdint.h>

#define CLK_PERIOD      (255)  // The maximum value for the clock period, used in the PWM signal generation.

/**
 * @brief Initializes the PWM module on the microcontroller with a specified period.
 *
 * This function initializes the PWM module on the microcontroller with the specified
 * period. The period is specified as a parameter of the function.
 *
 * @param period The period of the PWM module in clock cycles.
 *
 * @return None
 */
void init_PWM_LED(uint32_t period);

/**
 * @brief Sets the color of the RGB LED by specifying the intensity of the red, green, and blue components.
 *
 * This function sets the color of the RGB LED by specifying the intensity of the red,
 * green, and blue components. The function takes three integer parameters for the
 * intensity of each color component.
 *
 * @param r The intensity of the red component, ranging from 0 to 255.
 * @param g The intensity of the green component, ranging from 0 to 255.
 * @param b The intensity of the blue component, ranging from 0 to 255.
 *
 * @return None
 */
void set_color(int r, int g, int b);

/**
 * @brief Transitions smoothly between different colors of the RGB LED.
 *
 * This function transitions smoothly between different colors of the RGB LED by
 * gradually increasing or decreasing the intensity of the red, green, and blue
 * components.
 *
 * @return None
 */
void color_transition(void);

/**
 * @brief Sets the starting values of the current color transition to the current color values (r, g, b).
 *
 * This function sets the starting values (red_start_val, green_start_val, and blue_start_val) of the current color transition to the current color values (r, g, b).
 *
 * @return void
 */

void get_RGB_within_transition(void);

/**
 * @brief Performs a color transition within an existing color transition.
 *
 * This function performs a color transition within an existing color transition by first calling get_RGB_within_transition to get the current color values,
 * and then performing the color transition using the same formula as color_transition. The new color gradients are set using the set_color function.
 *
 * @return void
 */
void color_transition_within_transition(void);


#endif // _PWM_LED_FUNC_H_
