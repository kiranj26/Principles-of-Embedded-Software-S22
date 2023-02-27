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
​ ​*​ ​@file​_name    LED_Func.c
​ ​*​ ​@intorduction
 * This is a C file containing functions for controlling LEDs on a development board. Here are the functions in this file:
 * delay_ms(uint32_t ms): This function introduces a delay for a specified number of milliseconds using a busy-wait approach. It has one parameter ms that specifies the number of milliseconds to delay.
 * init_leds(): This function configures the GPIO pins used to drive the Red, Green, and Blue LEDs on the development board. It sets the pin muxing to GPIO mode, sets the pins to output mode, and turns off all the LEDs.
 * turn_on_red_led(): This function turns off the green and blue LEDs (if they are on), and then turns on the red LED.
 * turn_off_red_led(): This function turns off the red LED.
 * turn_on_green_led(): This function turns off the red and blue LEDs (if they are on), and then turns on the green LED.
 * turn_off_green_led(): This function turns off the green LED.
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
​ ​* @@referense
​ ​*              1) https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 * 				2) https://os.mbed.com/teams/Freescale/wiki/frdm-kl25z-pinnames
 * 				3) Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
 * 				   https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *
​ *              I would like to thank the SA's of the course Daanish, Hari and Ritika for their support in understanding and explaining
 *              details of requirements
​ ​*/


#ifndef _LED_FUNC_C_
#define _LED_FUNC_C_

#include"LED_Func.h"
#include"TSI_sensor.h"

/* Global Variable */
static int32_t  previous_touch = SLIDER_NOT_TOUCHED;

/**
 * @brief Delay function
 *
 * This function introduces a delay for a specified number of milliseconds using
 * a busy-wait approach. The delay is achieved by executing nested for-loops,
 * where the outer loop counts the number of milliseconds to delay and the inner
 * loop counts a fixed number of iterations to achieve approximately 1 millisecond
 * of delay.
 *
 * @param ms The number of milliseconds to delay
 *
 * @return void
 */
void delay_ms(uint32_t ms) {
    uint32_t i, j;
    // The outer loop counts the number of milliseconds to delay
    for (i = 0; i < ms; i++) {
        // The inner loop counts a fixed number of iterations to achieve
        // approximately 1 millisecond of delay
        for (j = 0; j < DELAY_CONSTANT; j++) {
        }
    }
}

/**
 * @brief Initializes the LED pins for use as outputs
 *
 * This function configures the GPIO pins used to drive the Red, Green, and Blue LEDs
 * on the development board. It sets the pin muxing to GPIO mode, sets the pins to output
 * mode, and turns off all the LEDs.
 *
 * @return void
 */
void init_leds() {
    // Enable clock to port B and D
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

    // Set pin muxing to GPIO
    PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
    PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
    PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

    // Set pins to output mode
    PTB->PDDR |= (1UL << RED_LED_PIN);
    PTB->PDDR |= (1UL << GREEN_LED_PIN);
    PTD->PDDR |= (1UL << BLUE_LED_PIN);

    // Turn off all LEDs
    PTB->PSOR |= (1UL << RED_LED_PIN);
    PTB->PSOR |= (1UL << GREEN_LED_PIN);
    PTD->PSOR |= (1UL << BLUE_LED_PIN);
}

/**
 * @brief Turns on the red LED
 * This function turns off the green and blue LEDs (if they are on), and then turns on the
 * red LED by setting the appropriate bit in the GPIO register.
 * @return void
*/

void turn_on_red_led() {
	GPIOB->PSOR |= (1UL<<GREEN_LED_PIN);  //turning green led off
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);	  //turning blue led off
	GPIOB->PCOR |= (1UL<<RED_LED_PIN);	  //turning red led on
}
/**
 *
 * @brief Turns off the red LED
 * This function turns off the red LED by setting the appropriate bit in the GPIO register.
 * @return void
*/
void turn_off_red_led() {
	GPIOB->PSOR |= (1UL<<RED_LED_PIN) | (1UL<<GREEN_LED_PIN);
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);
}

/**
 *
 * @brief Turns on the green LED
 * This function turns off the red and blue LEDs (if they are on), and then turns on the
 * green LED by setting the appropriate bit in the GPIO register.
 * @return void
*/
void turn_on_green_led() {
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);		//turning blue led off
	GPIOB->PSOR |= (1UL<<RED_LED_PIN);		//turning red led off
	GPIOB->PCOR |= (1UL<<GREEN_LED_PIN);	//turning green led on
}


/**
 * @brief Turns off the green LED
 * This function turns off the green LED by setting the appropriate bit in the GPIO register.
 * @return void
*/
void turn_off_green_led() {
	GPIOB->PSOR |= (1UL<<RED_LED_PIN) | (1UL<<GREEN_LED_PIN);
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);
}

/**
 * @brief Turns on the blue LED
 * This function turns off the red and green LEDs (if they are on), and then turns on the
 * blue LED by setting the appropriate bit in the GPIO register.
 * @return void
*/
void turn_on_blue_led() {
	GPIOB->PSOR |= (1UL<<GREEN_LED_PIN);	//turning green led off
	GPIOB->PSOR |= (1UL<<RED_LED_PIN);		//turning red led off
	GPIOD->PCOR |= (1UL<<BLUE_LED_PIN);		//turning blue led on
}
/**
 * @brief Turns off the blue LED
 * his function turns off the blue LED by setting the appropriate bit in the GPIO register.
 * @return void
 */
void turn_off_blue_led() {
	GPIOB->PSOR |= (1UL<<RED_LED_PIN) | (1UL<<GREEN_LED_PIN);
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);
}
/**
 * @brief Turns on all the RGB LEDs to white color
 * This function turns on all the RGB LEDs to white color by setting the appropriate bits in the GPIO register.
 * @return void
*/
void turn_on_white_led()
{
	GPIOB->PCOR |= (1UL<<GREEN_LED_PIN);	//turning green led on
	GPIOB->PCOR |= (1UL<<RED_LED_PIN);		//turning red led on
	GPIOD->PCOR |= (1UL<<BLUE_LED_PIN);		//turning blue led on
}
/**
 * @brief Turns off all the RGB LEDs
 * This function turns off all the RGB LEDs by setting the appropriate bits in the GPIO register.
 * @return void
*/
void turn_off_white_led()
{
	GPIOB->PSOR |= (1UL<<GREEN_LED_PIN);	//turning green led off
	GPIOB->PSOR |= (1UL<<RED_LED_PIN);		//turning red led off
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);		//turning blue led on
}
/**
 * @brief Turns off all LEDs
 * This function turns off the green and red LEDs and turns on the blue LED.
 * It achieves this by setting the corresponding bits in the GPIO port output data
*/
void turn_off_all_leds()
{
	GPIOB->PSOR |= (1UL<<GREEN_LED_PIN);	//turning green led off
	GPIOB->PSOR |= (1UL<<RED_LED_PIN);		//turning red led off
	GPIOD->PSOR |= (1UL<<BLUE_LED_PIN);		//turning blue led on
}
/**
 * @brief Tests the LED blinking pattern
 * This function tests the LED blinking pattern by turning the white LED on and off, followed by
 * turning the blue LED on and off. This is repeated twice. The function uses the turn_on_white_led(),
 * turn_off_white_led(), turn_on_blue_led(), and turn_off_blue_led() functions to control the LEDs.
 * It also uses delay_ms() function to introduce delays in between LED state changes.
 *
 * * @return void
*/
void test_led_blinking_pattern() {
	/* Turn White LED ON*/
	turn_on_white_led();
	LOG("WHITE LED ON!!\n");
	LOG("STARTING 500 ms Timer!!\n");
    delay_ms(DELAY_500);
    /* Turn White LED Off*/
    turn_off_white_led();
	LOG("WHITE LED OFF!!\n");
	LOG("STARTING 100 ms Timer!!\n");
    delay_ms(DELAY_100);
    /* Turn Blue LED On*/
    turn_on_blue_led();
	LOG("BLUE LED ON!!\n");
	LOG("STARTING 500 ms Timer!!\n");
    delay_ms(DELAY_500);
    /* Turn Blue LED Off*/
    turn_off_blue_led();
	LOG("BLUE LED OFF!!\n");
	LOG("STARTING 100 ms Timer!!\n");
    delay_ms(DELAY_100);

	/* Turn White LED ON*/
	turn_on_white_led();
	LOG("WHITE LED ON!!\n");
	LOG("STARTING 500 ms Timer!!\n");
    delay_ms(DELAY_500);
    /* Turn White LED Off*/
    turn_off_white_led();
	LOG("WHITE LED OFF!!\n");
	LOG("STARTING 100 ms Timer!!\n");
    delay_ms(DELAY_100);
    /* Turn Blue LED On*/
    turn_on_blue_led();
	LOG("BLUE LED ON!!\n");
	LOG("STARTING 500 ms Timer!!\n");
    delay_ms(DELAY_500);
    /* Turn Blue LED Off*/
    turn_off_blue_led();
	LOG("BLUE LED OFF!!\n");
	LOG("STARTING 100 ms Timer!!\n");
    delay_ms(DELAY_100);
}

void infinite_loop(void)
{

	/* ************************************** */
	/* ************************************** */
	/* RED ON for 500 msec, OFF for 500 msec, */
	/* ************************************** */
	/* ************************************** */

	/* Total delay of 500ms          */
	/* Include Poll for every 100 ms */
	LOG("Red LED ON!!\n");
	for (int i=0;i<=4;i++){
		previous_touch = TSI_Polling(previous_touch);
		// if left slider touched
		if((previous_touch == LEFT_SLIDER_TOUCHED) || ((previous_touch == SLIDER_NOT_TOUCHED )))
		{
			// if left slider pressed during delay
			// change it to red
			turn_on_red_led();
		}
		// if right slider touched
		else if ((previous_touch == RIGHT_SLIDER_TOUCHED))
		{
			// if left slider pressed during delay
			// change it to green
			turn_on_green_led();
			LOG("SEQUENSE CHANGED FROM RED TO GREEN!!\n");
			LOG("SEQUENSE CHANGED WITH SLIDER VALUE %d\n",load_val_TSI());
		}
		LOG("STARTING 100 ms Timer!!\n");
		delay_ms(DELAY_100);
	}

    /* Turn RED LED Off*/
    turn_off_red_led();
	LOG("Red LED OFF!!\n");
    //delay_ms(500);
	for (int i=0;i<=4;i++){
		previous_touch = TSI_Polling(previous_touch);
		LOG("STARTING 100 ms Timer!!\n");
        delay_ms(DELAY_100);
    }
	/* **************************************** */
	/* **************************************** */


	/* **************************************** */
	/* **************************************** */
	/* GREEN ON for 1000 msec, OFF for 500 msec */
	/* **************************************** */
	/* **************************************** */
	LOG("GREEN LED ON!!\n");
	for (int i=0;i<=9;i++){
		previous_touch = TSI_Polling(previous_touch);
		if((previous_touch == LEFT_SLIDER_TOUCHED))
		{
			// if left slider pressed during delay
			// change it to red
			turn_on_red_led();
			LOG("SEQUENSE CHANGED FROM GREEN TO RED!!\n");
			LOG("SEQUENSE CHANGED WITH SLIDER VALUE %d\n",load_val_TSI());

		}
		// if right slider touched
		else if ((previous_touch == RIGHT_SLIDER_TOUCHED) || (previous_touch == SLIDER_NOT_TOUCHED ))
		{
			// if left slider pressed during delay
			// change it to green
			turn_on_green_led();
		}
		LOG("STARTING 100 ms Timer!!\n");
		delay_ms(DELAY_100);
	}

    /* Turn RED LED Off*/
    turn_off_green_led();
	LOG("GREEN LED OFF!!\n");
    //delay_ms(500);
	for (int i=0;i<=4;i++){
		previous_touch = TSI_Polling(previous_touch);
		LOG("STARTING 100 ms Timer!!\n");
        delay_ms(DELAY_100);
    }
	/* **************************************** */
	/* **************************************** */


	/* **************************************** */
	/* **************************************** */
	/* RED ON for 2000 msec, OFF for 500 msec,  */
	/* **************************************** */
	/* **************************************** */
	LOG("Red LED ON!!\n");
	for (int i=0;i<=19;i++){
		previous_touch = TSI_Polling(previous_touch);
		if((previous_touch == LEFT_SLIDER_TOUCHED) || (previous_touch == SLIDER_NOT_TOUCHED ))
		{
			// if left slider pressed during delay
			// change it to red
			turn_on_red_led();
		}
		// if right slider touched
		else if ((previous_touch == RIGHT_SLIDER_TOUCHED))
		{
			// if left slider pressed during delay
			// change it to green
			turn_on_green_led();
			LOG("SEQUENSE CHANGED FROM GREEN TO RED!!\n");
			LOG("SEQUENSE CHANGED WITH SLIDER VALUE %d\n",load_val_TSI());

		}
		LOG("STARTING 100 ms Timer!!\n");
	    delay_ms(DELAY_100);

	}

	/* Turn LED OFF */
	turn_off_red_led();
	LOG("Red LED OFF!!\n");
	for (int i=0;i<=4;i++){
		previous_touch = TSI_Polling(previous_touch);
		LOG("STARTING 100 ms Timer!!\n");
        delay_ms(DELAY_100);
    }
	/* **************************************** */
	/* **************************************** */


	/* **************************************** */
	/* **************************************** */
	/* GREEN ON for 3000 msec, OFF for 500 msec */
	/* **************************************** */
	/* **************************************** */
	/* Turn ON GREEN LED*/
	LOG("GREEN LED ON!!\n");
	for (int i=0;i<=29;i++){
		previous_touch = TSI_Polling(previous_touch);
		if((previous_touch == LEFT_SLIDER_TOUCHED))
		{
			// if left slider pressed during delay
			// change it to red
			turn_on_red_led();
			LOG("SEQUENSE CHANGED FROM RED TO GREEN!!\n");
			LOG("SEQUENSE CHANGED WITH SLIDER VALUE %d\n",load_val_TSI());
		}
		// if right slider touched
		else if ((previous_touch == RIGHT_SLIDER_TOUCHED) || (previous_touch == SLIDER_NOT_TOUCHED ))
		{
			// if left slider pressed during delay
			// change it to green
			turn_on_green_led();
		}
		LOG("STARTING 100 ms Timer!!\n");
	    delay_ms(DELAY_100);
	}

    /* Turn RED LED Off*/
    turn_off_green_led();
	LOG("GREEN LED ON!!\n");
	for (int i=0;i<=4;i++){
		previous_touch = TSI_Polling(previous_touch);
		LOG("STARTING 100 ms Timer!!\n");
        delay_ms(100);
    }
}

#endif
