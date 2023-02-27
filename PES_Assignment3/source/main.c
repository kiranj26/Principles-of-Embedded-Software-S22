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
​ ​*​ ​@file​_name    main.c
​ ​*​ ​@intorduction main file for PES Assignment 3
 *               Main file that calls main() function which test led pattern and then triggers
 *               calls function infinite loop for LED blinking and also polls the touch sensor
 *               every 100 msec.
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
 *
 * @@referense
​ ​*              1) https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 * 				2) https://os.mbed.com/teams/Freescale/wiki/frdm-kl25z-pinnames
 * 				3) Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
 * 				   https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *
​ *              I would like to thank the SA's of the course Daanish, Hari and Ritika for their support in understanding and explaining
 *              details of requirements
*/

#ifndef _CHRISTMAS_LED_C
#define _CHRISTMAS_LED_C

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "log.h"


/* Include the LED_Func.h and TSI_Sensor.h header files */
#include "LED_Func.h"
#include "TSI_Sensor.h"


/* Main function where the program execution starts */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    	/* Init FSL debug console. */
    	BOARD_InitDebugConsole();
	#endif

	/* Initialize the LEDs */
    init_leds();

    /* Test the LED blinking pattern */
    init_TSI();

    /* This is an infinite loop that keeps the program running */
	LOG("Starting Testing Pattern\n");
    test_led_blinking_pattern();

    /* Enter an infinite loop, just incrementing a counter. */
	LOG("Starting Infinite Loop\n");
    while(1) {
        /* Call the infinite loop function */
    	infinite_loop();

    }
    return 0 ;
}
#endif // _CHRISTMAS_LED_C_
