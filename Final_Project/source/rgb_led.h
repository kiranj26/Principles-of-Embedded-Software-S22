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
 * @file rgb_led.h
 *
 * @brief Header file for RGB LED control functions
 *
 * ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 *
 */

#ifndef __RGB_LED_H__
#define __RGB_LED_H__

#include "MKL25Z4.h"

#include "pwm.h"

#define RED_LED_POS 	(18)    // Red LED position on port B
#define GREEN_LED_POS 	(19)  	// Green LED position on port B
#define BLUE_LED_POS 	(1)    	// Blue LED position on port D

/**
 * @brief Set the RGB LED to a specific color
 *
 * @param red The brightness of the red LED (0-255)
 * @param green The brightness of the green LED (0-255)
 * @param blue The brightness of the blue LED (0-255)
 */
void rgb_led(unsigned int red, unsigned int green, unsigned int blue);

/**
 * @brief Test the PWM functionality of the RGB LED
 */
void test_pwm(void);

/**
 * @brief Delay for a given number of cycles
 *
 * @param time The number of cycles to delay
 */
void Delay(volatile int time);

/**
 * @brief Perform a breathing effect on the blue LED
 */
void breathing_effect_blue(void);

/**
 * @brief Perform a breathing effect on the red LED
 */
void breathing_effect_red(void);

/**
 * @brief Perform a breathing effect on the green LED
 */
void breathing_effect_green(void);

/**
 * @brief Perform a breathing effect on the cyan LED
 */
void breathing_effect_cyan(void);

/**
 * @brief Perform a breathing effect on the white LED
 */
void breathing_effect_white(void);

/**
 * @brief Perform a breathing effect on the gray LED
 */
void breathing_effect_gray(void);

/**
 * @brief Perform a breathing effect on the yellow LED
 */
void breathing_effect_yellow(void);

#endif // __RGB_LED_H__
