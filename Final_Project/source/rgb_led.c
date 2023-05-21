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
 * @file rgb_led.c
 *
 * @brief C file for RGB LED control functions along with test RGB functions
 *
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 *
 */

// Include header file for RGB Led
#include "rgb_led.h"

// Define maximum PWM value for RGB Led
#define MAX_PWM (255)

// Define constant value to generate 1ms delay
#define ONE_MS_CONS (534)

// Define breathing time in milliseconds
#define BREATHING_TIME (3000)

// Delay function to generate loop as per the input time.
void Delay(volatile int time)
{
    // Multiply time with an approximated value to get desired delay.
    time = time * ONE_MS_CONS;

    // Decrement the counter to get the desired delay.
    while(time--)
    {
        __asm volatile("NOP"); // A no-operation assembly instruction used for delay
    }
}

// Assigns input values to respective CnV for RGB led
void rgb_led(unsigned int red, unsigned int green, unsigned int blue)
{
    TPM0->CONTROLS[1].CnV = blue;   // Set value of blue channel PWM
    TPM2->CONTROLS[1].CnV = green;  // Set value of green channel PWM
    TPM2->CONTROLS[0].CnV = red;    // Set value of red channel PWM
}

void breathing_effect_blue(void)
{
    int i = 0;
    // Low level shade of blue
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(0, 0, i);  // Increase blue component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of blue
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(0, 0, i);  // Increase blue component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of blue
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(0, 0, i);  // Increase blue component
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

void breathing_effect_red(void)
{
    int i = 0;
    // Low level shade of red
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(i, 0, 0);  // Increase red component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of red
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(i, 0, 0);  // Increase red component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of red
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(i, 0, 0);  // Increase red component
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

void breathing_effect_green(void)
{
    int i = 0;
    // Low level shade of green
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(0, i, 0);  // Increase green component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of green
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(0, i, 0);  // Increase green component
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of green
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(0, i, 0);  // Increase green component
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

void breathing_effect_cyan(void)
{
    int i = 0;
    // Low level shade of cyan
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(0, i, i);  // Increase blue and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of cyan
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(0, i, i);  // Increase blue and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of cyan
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(0, i, i);  // Increase blue and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

void breathing_effect_white(void)
{
    int i = 0;
    // Low level shade of white
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(i, i, i);  // Increase all components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of white
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(i, i, i);  // Increase all components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of white
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(i, i, i);  // Increase all components
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

void breathing_effect_gray(void)
{
    int i = 0;
    // Low level shade of gray
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(i, i, i);  // Increase all RGB components equally
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of gray
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(i, i, i);  // Increase all RGB components equally
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of gray
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(i, i, i);  // Increase all RGB components equally
        Delay(BREATHING_TIME / MAX_PWM);
    }
}
void breathing_effect_yellow(void)
{
    int i = 0;
    // Low level shade of yellow
    for (i = 0; i <= MAX_PWM/3; i++) {
        rgb_led(i, i, 0);  // Increase red and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // Medium level shade of yellow
    for (i = MAX_PWM/3; i <= 2*MAX_PWM/3; i++) {
        rgb_led(i, i, 0);  // Increase red and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
    // High level shade of yellow
    for (i = 2*MAX_PWM/3; i <= MAX_PWM; i++) {
        rgb_led(i, i, 0);  // Increase red and green components
        Delay(BREATHING_TIME / MAX_PWM);
    }
}

// Function to test different PWM effects on RGB LED
void test_pwm(void)
{
	breathing_effect_blue(); 	// Call the function to show breathing effect with blue color
	breathing_effect_red(); 	// Call the function to show breathing effect with red color
	breathing_effect_green(); 	// Call the function to show breathing effect with green color
	breathing_effect_cyan(); 	// Call the function to show breathing effect with cyan color
	breathing_effect_white(); 	// Call the function to show breathing effect with white color
	breathing_effect_gray(); 	// Call the function to show breathing effect with gray color
	breathing_effect_yellow(); 	// Call the function to show breathing effect with yellow color
}





