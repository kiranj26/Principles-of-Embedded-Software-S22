/*****************************************************************************
 * Copyright (C) 2023 by Kiran Jojare
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of
 * embedded software. Kiran Jojare and the University of Colorado are not
 * liable for any misuse of this material.
 *****************************************************************************/

/**
 * @file    main.c
 * @brief   Main file for PES Assignment 4
 *          This file initializes the board hardware, initializes
 *          the PWM LED and timing functions, initializes the touch sensor,
 *          runs the state machine, and enters an infinite loop
 * @author  Kiran Jojare
 * @date    March 3, 2023
 * @version 1.0
 *
 * @@referense
 *   1) https://github.com/alexander-g-dean/ESF/blob/master/
 * 	 2) https://os.mbed.com/teams/Freescale/wiki/frdm-kl25z-pinnames
 * 	 3) Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support in understanding and explaining
 *    details of requirements
 */

#ifndef _TRAFFIC_LIGHTS_C_
#define _TRAFFIC_LIGHTS_C_


#include <MKL25Z4.h>            // Processor specific header file
#include "board.h"              // Board specific header file
#include "pin_mux.h"            // Header file for pin multiplexing functions
#include "clock_config.h"       // Header file for clock configuration
#include "peripherals.h"        // Header file for peripheral drivers
#include "fsl_debug_console.h"  // Header file for debug console functions
#include "core_cm0plus.h"       // Cortex-M0+ specific header file

#include "log.h"				// Log file logging functions
#include "PWM_LED_Func.h"       // Header file for PWM LED functions
#include "Timing.h"             // Header file for timing functions
#include "StateMachine.h"       // Header file for state machine functions
#include "TSI_sensor.h"         // Header file for touch sensor functions
#include "Switch_Interrupt.h"	// Header file for switch interrupt functions

/*
 * @brief   Application entry point.
 */

int main(void) {

    /* Init board hardware */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console */
    BOARD_InitDebugConsole();
#endif

    /* Initialize PWM LED */
    init_PWM_LED(CLK_PERIOD);

    /* Initialize touch sensor */
    init_TSI();

    /* Initialize switch interrupt */
    InitInterrupt();

    /* Initialize timing functions */
    init_systick();

    LOG("Main Loop Starting\n\r");

    /* Enter an infinite loop */
    while (1) {
    	 /* Run State Machine in a loop */
    	State_Machine();
        /* Dummy NOP to allow source level single stepping of tight while() loop */
        __asm volatile ("nop");
    }
    return 0;
}

#endif /* _TRAFFIC_LIGHTS_C_ */
