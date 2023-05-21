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
 * @file 	fp_trip.c
 * @brief	Implementation of trigonometric functions using fixed point arithmetic
 *
 * This file contains the implementation of lookup_fp_sin and fp_triangle functions that use
 * fixed point arithmetic to perform trigonometric calculations. The lookup_fp_sin function
 * generates a sine value based on a lookup table and uses interpolation to calculate the value
 * for other angles. The fp_triangle function generates a triangle wave using a scaling factor.
 *
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
 *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements.
 */

#include <stdbool.h>
#include "fsl_debug_console.h"

#include "fp_trig.h"

#define TRIANGLE_SCALE_FACTOR 	(163UL) // Define the triangle wave scaling factor

int32_t fp_triangle(int32_t x) // Define the function for generating a triangle wave
{
    int sign = 1; // Initialize the sign of the triangle wave to positive

    while (x < -PI) { // If the angle is less than -pi
        x += TWO_PI; // Add 2*pi to it until it's between -pi and pi
    }

    while (x > PI) { // If the angle is greater than pi
        x -= TWO_PI; // Subtract 2*pi from it until it's between -pi and pi
    }

    if (x < 0) { // If the angle is negative
        x = -x; // Take the absolute value
        sign = -1; // And set the sign of the triangle wave to negative
    }

    if (x > HALF_PI) { // If the angle is greater than pi/2
        x = PI - x; // Subtract the angle from pi
    }

    int32_t result = x * TRIANGLE_SCALE_FACTOR; // Multiply the angle by the scaling factor
    result >>= 8; // Shift the result right by 8 bits to divide by 256

    return sign * result; // Return the result with the appropriate sign
}
