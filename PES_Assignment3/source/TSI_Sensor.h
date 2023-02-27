/*****************************************************************************
​ ​*​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ ​*
​ ​*​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ ​*​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ ​*​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ ​*​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ ​*​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ ​*
*****************************************************************************/
/**
​ ​*​ ​@file​_name    TSI_Sensor.h
​ ​*​ ​@intorduction This is the header file for TSI_Sensor.c
 * It includes necessary libraries and defines macros for TSI sensing operation.
 * Macros are defined for touch offset, touch count, and TSI data.
 * Macros are also defined for slider touch detection, with left and right slider touched values, and slider not touched value.
 * The functions declared in this header file are:
 *     init_TSI(): initializes the TSI module for sensing operation.
 *     load_val_TSI(): loads TSI data value for touch sensing operation.
 *     TSI_Polling(): performs TSI sensing operation and returns the slider touch detection value.
​ ​*​
 * ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
​ ​*
​ ​*/

#ifndef _TSI_SENSOR_H_
#define _TSI_SENSOR_H_

// Header Files
#include "MKL25Z4.h"
#include <stdint.h>
#include "log.h"

// Define macros for touch sensing
#define TOUCH_OFFSET 650  // offset value to be subtracted
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register

// Define macros for touch positions
#define LEFT_SLIDER_TOUCHED 1
#define RIGHT_SLIDER_TOUCHED 2
#define SLIDER_NOT_TOUCHED 3

// Thresholds for Calibrating Touch Sensor
#define UPPER_THD 600
#define LOWER_THD 25

// Function declarations
void init_TSI(void);				// Function to initialize TSI sensor
int load_val_TSI(void);				// Function to load TSI sensor value
uint16_t TSI_Polling(int32_t);	    // Function for TSI polling


#endif
