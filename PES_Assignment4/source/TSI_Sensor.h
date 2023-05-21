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
​ ​*​ ​@introduction This is the header file for TSI_Sensor.c. This is same file from Assignment 3.
 *
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

// Function declarations

/**
 * @brief Initializes the TSI sensor module
 *
 * This function initializes the TSI sensor module by configuring its registers
 * with appropriate values for the desired operation.
 *
 * @return void
 */

void init_TSI(void);

/**
 * @brief Loads the current touch sensor value from TSI_DATA register
 *
 * This function triggers a scan of the touch sensor and waits until the scan is complete.
 * It then returns the current touch sensor value by subtracting the TOUCH_OFFSET from
 * the TOUCH_COUNT register value.
 *
 * @return uint32_t The current touch sensor value
 */
int load_val_TSI(void);

/**
 * @brief Detects touch using the Touch Sense Interface (TSI) module
 *
 * This function reads the current touch sensor value using the load_val_TSI() function,
 * which triggers a scan of the touch sensor and waits until the scan is complete.
 * It then compares the touch sensor value to a predefined threshold value, TOUCH_DETECT_THD.
 * If the touch sensor value is greater than or equal to the threshold, the function returns
 * TOUCH_DETECTED, which is a pre-defined constant. Otherwise, it returns TOUCH_NOT_DETECTED,
 * which is another pre-defined constant. The function is of type uint16_t.
 *
 * @return uint16_t A value indicating whether touch is detected or not.
 *                  Possible return values are TOUCH_DETECTED or TOUCH_NOT_DETECTED,
 *                  which are also pre-defined constants.
 */
uint16_t TSI_Touch_Detected(void);


#endif //_TSI_SENSOR_H_
