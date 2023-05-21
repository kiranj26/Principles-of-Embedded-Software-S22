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
​ ​*​ ​@file​_name     main.c
​ ​*​ ​@introduction  The main.c file is a source code file for a microcontroller-based
 * embedded system. The code initializes the system clock, UART, I2C, PWM, TSI, and
 * other peripherals, performs hardware and software testing, and sets up a watchdog
 * timer for system safety. The file includes several header files, such as board.h,
 * peripherals.h, and pin_mux.h, that define the pins, clocks, and peripherals used
 * in the system. The code is written in C programming language and is intended to
 * be compiled and executed on a Freescale Kinetis KL25Z microcontroller board.
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#include <stdio.h>                       // Include standard input/output header file
#include "board.h"                       // Include board header file
#include "peripherals.h"                 // Include peripheral header file
#include "pin_mux.h"                     // Include pin_mux header file
#include "clock_config.h"                // Include clock_config header file
#include "MKL25Z4.h"                     // Include MKL25Z4 header file
#include "fsl_debug_console.h"           // Include FSL debug console header file
#include "i2c.h"                         // Include I2C header file
#include "sht21.h"                       // Include SHT21 header file
#include "sysclock.h"                    // Include system clock header file
#include "uart.h"                        // Include UART header file
#include "pwm.h"                         // Include PWM header file
#include "rgb_led.h"                     // Include RGB LED header file
#include "timer.h"                       // Include timer header file
#include "test_cbfifo.h"                 // Include CBFIFO test header file
#include "Accumulate_Line.h"             // Include Accumulate_Line header file
#include "timer.h"                       // Include timer header file
#include "test_sht21.h"                  // Include SHT21 test header file
#include "state_machine.h"               // Include state machine header file
#include "TSI.h"                         // Include TSI header file
#include "wdt.h"                         // Include watchdog timer header file


#define BAUD_RATE 		(38400)          // Set baud rate to 38400
#define WDT_TIMEOUT 	COP_CYCLES_03    // Define watchdog timer timeout value
										 // (COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles)
#define WDT_CLK_SRC 	BUS_CLOCK        // Set watchdog timer clock source to bus clock
#define WDT_WIN_MODE 	NORMAL_MODE      // Set watchdog timer window mode to normal mode


// Main function
int main(void)
{

	BOARD_InitBootPins();                // Initialize board pins
	BOARD_InitBootClocks();              // Initialize board clocks
	BOARD_InitBootPeripherals();         // Initialize board peripherals
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	BOARD_InitDebugConsole();            // Initialize FSL debug console
#endif

	Init_UART0(BAUD_RATE);               // Initialize UART0

	// Initialization of LEDs
	Init_Red_LED_PWM(PWM_PERIOD);        // Initialize red LED with PWM period
	Init_Green_LED_PWM(PWM_PERIOD);      // Initialize green LED with PWM period
	Init_Blue_LED_PWM(PWM_PERIOD);       // Initialize blue LED with PWM period

	PRINTF("\n\r+---------------------------------------+\n\r");  		// Print message
	PRINTF("\n\r|         Enabling Watchdog Timer       |\n\r");       	// Print message
	PRINTF("\n\r+---------------------------------------+\n\r");  		// Print message

	COPC_config_t wdt_config = {         	// Initialize watchdog timer configuration struct
			.timeout = WDT_TIMEOUT,      	// Set timeout value
			.clock_select = WDT_CLK_SRC, 	// Set clock source
			.windowsed_mode = WDT_WIN_MODE 	// Set window mode
	};

	Init_wdt(&wdt_config);               	// Initialize watchdog timer with configuration struct

	delay_100ms();
	PRINTF("\n\r+---------------------------------------+\n\r");  		// Print message
	PRINTF("\n\r|       Hardware & Software Testing     |\n\r");       	// Print message
	delay_100ms();
	PRINTF("\n\r+---------------------------------------+\n\r");  		// Print message


#ifdef DEBUG 							// Enable PWM automated testing only in debug mode
	printf("Testing PWM with different values : \n\r"); // Print message to console
	test_pwm(); 										// Call test_pwm() function to test PWM
	printf("PWM Tested Successfully! \n\r\n\r"); 		// Print success message to console
#endif

	sysclock_init(); 					// Initialize the system clock
	init_I2C1(); 						// Initialize I2C1
	init_systick(); 					// Initialize Systick timer
	init_TSI(); 						// Initialize TSI

#ifdef DEBUG 							// Enable CBFIFO automated testing only in debug mode
	printf("Testing CBFIFO with different values : \n\r"); 	// Print message to console
	test_cbfifo(); 											// Call test_cbfifo() function to test CBFIFO (commented out)
	printf("CBFIFO Tested Successfully! \n\r\n\r"); 		// Print success message to console
#endif

#ifdef DEBUG 							// Enable SHT21 automated testing only in debug mode
	printf("Testing SHT21 to read value 10 times : \n\r"); 	// Print message to console
	test_sht21(); 											// Call test_sht21() function to test SHT21
	printf("SHT21 Sensor Tested Successfully! \n\r\n\r"); 	// Print success message to console
#endif

	print_UI(); 						// Print the User Interface to console
	PRINTF("? "); 						// Prompt user for input

	// Enter an infinite loop
	while(1)
	{
	    read_and_process_command(); 	// Call read_and_process_command() function to process user input
	}
	return 0 ; 							// End of main function, return 0 to indicate successful execution
}
