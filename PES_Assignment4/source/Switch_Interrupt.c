/*****************************************************************************
 * @file    Switch_Interrupt.c
 * @brief   C file for switch interrupt functions on PORTA
 *
 * This file provides functions to initialize switch interrupt on PORTA and handle
 * the interrupt. It also defines the GPIO pin and interrupt configuration for
 * the switch. The interrupt flag is set in the interrupt handler, which can be
 * used by the application to identify if the switch was pressed.
 *
 * @author  Kiran
 * @date    Feb 19 2023
 * @version 1.0
 *
 * @referense
 * 1) GPIO Interrupt on KL25Z
 *    https://gab.wallawalla.edu/~larry.aamodt/engr355/lect_interrupts.pdf
 *
 *****************************************************************************/

#ifndef _SWITCH_INTERRUPT_C_
#define _SWITCH_INTERRUPT_C_

#include "MKL25Z4.h"  					// Micro-controller specific header file
#include "fsl_debug_console.h"  		// Free-scale debug console library
#include "Switch_Interrupt.h"  			// Header file for Switch interrupt functions
#include "Timing.h"
#include "log.h"


#define GPIO_SWITCH    	(4) 			// GPIO pin number for switch
#define GPIO_SWITCH_MUX (1) 			// GPIO pin mux value for switch
#define GPIO_SWITCH_IRQ (10) 			// GPIO IRQ number for switch

#define SWITCH_INRPT_PRIORITY (2) 		// Switch interrupt priority of 2

#define FALSE 			(0);			// Value False
#define TRUE 			(1);    		// Value True

volatile bool switch_pressed = FALSE; 	//flag to identify if button is pressed

/**
 * @brief Initializes the switch interrupt on PORTA with a falling edge trigger.
 *
 * This function initializes the switch interrupt on PORTA with a falling edge trigger.
 * It also enables the clock to PORTA, configures the GPIO pin for the switch, and
 * configures the NVIC for PORTA IRQ. The switch pin is set as input.
 *
 * @return None
 */
void InitInterrupt(void)
{
    // enable clock to PORT A
    SIM->SCGC5 |=SIM_SCGC5_PORTA_MASK;

    //configure GPIO switch
    PORTA->PCR[GPIO_SWITCH] = PORT_PCR_MUX(GPIO_SWITCH_MUX);
    // configure pull up / pull down configuration
    PORTA->PCR[GPIO_SWITCH] |= PORT_PCR_PS_MASK;
    PORTA->PCR[GPIO_SWITCH] |= PORT_PCR_PE_MASK;
    // configuring falling edge interrupt
    PORTA->PCR[GPIO_SWITCH] |= PORT_PCR_IRQC(GPIO_SWITCH_IRQ);

    //configuring NVIC
    NVIC_SetPriority(PORTA_IRQn, SWITCH_INRPT_PRIORITY);
    NVIC_ClearPendingIRQ(PORTA_IRQn);
    NVIC_EnableIRQ(PORTA_IRQn);
}

/**
 * @brief Interrupt handler for PORTA.
 *
 * This function is the interrupt handler for PORTA. It sets the interrupt flag
 * to identify if the switch was pressed and clears the interrupt flag.
 *
 * @return None
 */
void PORTA_IRQHandler(void)
{
    //Clearing pending IRQ
    NVIC_ClearPendingIRQ(PORTA_IRQn);
    //Setting switch_pressed
    switch_pressed = TRUE;
    //Clear Int flag
    PORTA->ISFR |= (1 << GPIO_SWITCH);
}

/**
 * @brief Returns the state of the switch interrupt flag.
 *
 * This function returns the state of the switch interrupt flag, which is set
 * to 1 when the switch is pressed and the interrupt is triggered. This function
 * can be used to poll the state of the switch interrupt flag without using an
 * interrupt handler.
 *
 * @return True if the switch interrupt flag is set, false otherwise.
 */
bool Switch_Detected(void)
{
	// return interrupt flag status
    return switch_pressed;
}

/**
 * @brief Resets the flag that indicates if the switch has been pressed.
 *
 * This function resets the flag that indicates if the switch has been pressed
 * by setting it to FALSE.
 *
 * @return None
 */
void Switch_Flag_Reset(void)
{
    switch_pressed = FALSE;
}
#endif // _SWITCH_INTERRUPT_C_

