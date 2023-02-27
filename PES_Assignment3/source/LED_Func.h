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
​ ​*​ ​@file​_name    LED_Func.h
​ ​*​ ​@intorduction This file, LED_Func.h, defines a set of functions for controlling LEDs on the MKL25Z4
 * microcontroller. It contains pin definitions for the red, green, and blue LEDs, as well as functions for initializing
 * the LEDs, turning them on and off, and toggling them in specific patterns. The file also includes a delay_ms() function
 * that provides a delay in milliseconds, using the microcontroller's system clock.
 *
​ ​*​
 * ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
​ ​*
​ ​*/

#ifndef _LED_FUNC_H_
#define _LED_FUNC_H_

// Including necessary headers
#include <stdint.h>
#include "MKL25Z4.h"
#include "log.h"

// Pin definitions for LEDs
#define RED_LED_PIN    18
#define GREEN_LED_PIN  19
#define BLUE_LED_PIN   1

// Timer delay constant
#define DELAY_CONSTANT 3225

// Constants for delay function inputs
#define DELAY_100 100
#define DELAY_500 500

// Function prototypes for LED control
void delay_ms(uint32_t ms);
void init_leds(void);
void turn_on_red_led(void);
void turn_off_red_led(void);
void turn_on_green_led(void);
void turn_off_green_led(void);
void turn_on_blue_led(void);
void turn_off_blue_led(void);
void turn_on_white_led(void);
void turn_off_white_led(void);
void turn_off_all_leds(void);

// Function prototypes for LED testing
void test_led_blinking_pattern(void);

// Function prototypes for infinite loop testing
void infinite_loop(void);


// global touched function;
#endif //_LED_FUNC_H_
