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
​ ​*​ ​@file​_name    TSI_Sensor.c
​ ​*​ ​@introduction Main timer functions file
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
 *
 * @referense
 *
 */
#ifndef _PWM_LED_FUNC_C_
#define _PWM_LED_FUNC_C_

// Header files
#include "fsl_debug_console.h"
#include "core_cm0plus.h"

#include "PWM_LED_Func.h"
#include "Timing.h"

#define RED_LED_PIN     (18)   	// The GPIO pin number used to control the red LED.
#define GREEN_LED_PIN   (19)   	// The GPIO pin number used to control the green LED.
#define BLUE_LED_PIN    (1)    	// The GPIO pin number used to control the blue LED.

#define RGB_MAX_VALUE   (255)  	// The maximum value for the RGB color value, which is used to
                               	   // normalize the PWM signal generated for each color channel.

#define COLOR_TRANSITION_CONST (0.0625) // Color transition constant of 0.0625

/**
 * @brief Initializes the LED pins for use as outputs
 *
 * This function configures the GPIO pins used to drive the Red, Green, and Blue LEDs
 * on the development board. It sets the pin muxing to GPIO mode, sets the pins to output
 * mode, and turns off all the LEDs.
 *
 * @return void
 */
void init_PWM_LED(uint32_t period) {

    // Enable clock to Port B and Port D
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    // Enable clock to TPM0 and TPM2
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

    // Configure RED LED pin to be GPIO
    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);

    // Configure GREEN LED pin to be GPIO
    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

    // Configure BLUE LED pin to be GPIO
    PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);

    // Set TPM clock source to 48 MHz and select PLLFLLSEL
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    // Set the period of the TPM0 and TPM2 modules
    TPM0->MOD = period - 1;
    TPM2->MOD = period - 1;

    // Set the prescaler for TPM0 and TPM2
    TPM0->SC = TPM_SC_PS(1);
    TPM2->SC = TPM_SC_PS(1);

    // Set the debug mode to '10' for both TPM0 and TPM2
    TPM0->CONF |= TPM_CONF_DBGMODE(3);
    TPM2->CONF |= TPM_CONF_DBGMODE(3);

    // Configure PWM settings for RED LED on TPM0 Channel 1
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM0->CONTROLS[1].CnV = 0;
    TPM0->SC |= TPM_SC_CMOD(1);

    // Configure PWM settings for BLUE LED on TPM2 Channel 0
    TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM2->CONTROLS[0].CnV = 0;

    // Configure PWM settings for GREEN LED on TPM2 Channel 1
    TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM2->CONTROLS[1].CnV = 0;

    // Enable TPM2 Counter
    TPM2->SC |= TPM_SC_CMOD(1);
}

/**
 * @brief Sets the color of an RGB LED connected to a TPM module.
 *
 * This function takes in three integer values representing the intensity of the red, green, and blue
 * colors (r, g, and b, respectively) and sets the corresponding duty cycle for each color on a TPM module.
 * The clock period and maximum RGB value are used to calculate the duty cycle values.
 *
 * @param r The intensity of the red color (0-255).
 * @param g The intensity of the green color (0-255).
 * @param b The intensity of the blue color (0-255).
 *
 * @return void
 */

void set_color(int r, int g, int b) {

	// Set the duty cycle of each color by updating the corresponding TPM control register
	TPM2->CONTROLS[0].CnV = r;
	TPM2->CONTROLS[1].CnV = g;
	TPM0->CONTROLS[1].CnV = b;
}

extern int red_start_val;    	// The starting value for the red LED in the fade effect.
extern int red_end_val;      	// The ending value for the red LED in the fade effect.
extern int green_start_val;  	// The starting value for the green LED in the fade effect.
extern int green_end_val;    	// The ending value for the green LED in the fade effect.
extern int blue_start_val;   	// The starting value for the blue LED in the fade effect.
extern int blue_end_val;     	// The ending value for the blue LED in the fade effect.

static int r = 0, g = 0, b = 0;  // The current RGB color value for the fade effect.
                                 // Initialized to 0 for all three color channels.

int timer = 0;  // The current time for the fade effect, in milliseconds.
                // Initialized to 0 at the beginning of the fade effect.


/**
 * @brief Transitions the color of an RGB LED from its starting values to its ending values over time.
 *
 * This function smoothly transitions the color of an RGB LED from its starting values (red_start_val, green_start_val, and blue_start_val)
 * to its ending values (red_end_val, green_end_val, and blue_end_val) over a specified period of time. The transition is performed by
 * calling the set_color function with intermediate color values.
 *
 * @return void
 */
void color_transition(void) {

	// Calculate the new value of each color based on the starting and ending values and the current ste
	timer = get_timer();
	r = ((red_end_val - red_start_val) * COLOR_TRANSITION_CONST * timer) + red_start_val;
	g = ((green_end_val - green_start_val) * COLOR_TRANSITION_CONST * timer) + green_start_val;
	b = ((blue_end_val - blue_start_val) * COLOR_TRANSITION_CONST * timer) + blue_start_val;

	// Set the new color gradients
	set_color(r, g, b);
}

/**
 * @brief Sets the starting values of the current color transition to the current color values (r, g, b).
 *
 * This function sets the starting values (red_start_val, green_start_val, and blue_start_val) of the current color transition to the current color values (r, g, b).
 *
 * @return void
 */
void get_RGB_within_transition(void)
{
	red_start_val = r;
	green_start_val = g;
	blue_start_val = b;
}

/**
 * @brief Performs a color transition within an existing color transition.
 *
 * This function performs a color transition within an existing color transition by first calling get_RGB_within_transition to get the current color values,
 * and then performing the color transition using the same formula as color_transition. The new color gradients are set using the set_color function.
 *
 * @return void
 */
void color_transition_within_transition(void)
{
	// get the current R G and B values from existing transition
	// get_RGB_within_transition();

	timer = get_timer();
	r = ((red_end_val - red_start_val) * COLOR_TRANSITION_CONST * timer) + red_start_val;
	g = ((green_end_val - green_start_val) * COLOR_TRANSITION_CONST * timer) + green_start_val;
	b = ((blue_end_val - blue_start_val) * COLOR_TRANSITION_CONST * timer) + blue_start_val;

	// Set the new color gradients
	set_color(r, g, b);
}

#endif // _PWM_LED_FUNC_C_
