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
 * @file pwm.h
 * @brief Header file for PWM control of RGB LEDs on KL25Z board
 *
 * This header file contains the function prototypes and definitions for PWM
 * control of the Red, Green, and Blue LEDs on the KL25Z board.
 *
 * ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#ifndef __PWM_H__
#define __PWM_H__


#include "timer.h"
#include "rgb_led.h"
#include <MKL25Z4.h>


#define RED_LED_POS 	(18)		// on port B
#define GREEN_LED_POS 	(19)		// on port B
#define BLUE_LED_POS 	(1)			// on port D

/**
 * @brief Initializes Blue LED PWM on the specified period
 *
 * This function initializes Blue LED PWM on the specified period
 *
 * @param period PWM period
 */
void Init_Blue_LED_PWM(uint16_t period);

/**
 * @brief Initializes Green LED PWM on the specified period
 *
 * This function initializes Green LED PWM on the specified period
 *
 * @param period PWM period
 */
void Init_Green_LED_PWM(uint16_t period);

/**
 * @brief Initializes Red LED PWM on the specified period
 *
 * This function initializes Red LED PWM on the specified period
 *
 * @param period PWM period
 */
void Init_Red_LED_PWM(uint16_t period);


#endif // __PWM_H__
