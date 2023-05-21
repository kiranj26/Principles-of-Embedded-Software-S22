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
 * @file pwm.c
 * @brief C file for PWM control of RGB LEDs on KL25Z board
 *
 * This C file contains the function prototypes and definitions for PWM
 * control of the Red, Green, and Blue LEDs on the KL25Z board.
 *
 *  *​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#include "pwm.h"

// Initializes the blue LED PWM with the given period
void Init_Blue_LED_PWM(uint16_t period)
{
    // Enable clock gate for Port D
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;;

    // Clear the MUX bits for the Blue LED position and set them to 4 to enable TPM0_CH1
    PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);

    // Enable clock gate for TPM0 and set the clock source and PLLFLLSEL bits
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    // Set the modulo value for the TPM0 counter to the given period minus 1
    TPM0->MOD = period - 1;

    // Set the prescaler to 1, effectively setting the clock to half the bus clock frequency
    TPM0->SC =  TPM_SC_PS(1);

    // Set the debug mode to '10' (Logic high on TRIGGER input will freeze the counter and TPM counter will resume when the TRIGGER input transitions to low)
    TPM0->CONF |= TPM_CONF_DBGMODE(3);

    // Configure TPM0_CH1 as a PWM output with high true pulses
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

    // Set the initial value for TPM0_CH1 to 40 (20% duty cycle)
    TPM0->CONTROLS[1].CnV = 40;

    // Start the TPM0 counter
    TPM0->SC |= TPM_SC_CMOD(1);
}

void Init_Red_LED_PWM(uint16_t period)
{
    // Enable clock to Port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

    // Configure the red LED pin multiplexer to use TPM2_CH0
    PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK; // Clear the MUX bits
    PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);    // Set MUX bits to 3 (TPM2_CH0)

    // Enable clock to TPM2
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

    // Select the PLL/FLL clock as the TPM2 clock source
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    // Set the TPM2 MOD register to the period-1 value
    TPM2->MOD = period-1;

    // Set the TPM2 prescaler to divide by 2
    TPM2->SC =  TPM_SC_PS(1);

    // Set the TPM2 debug mode to "free-running"
    TPM2->CONF |= TPM_CONF_DBGMODE(3);

    // Configure TPM2 channel 0 for PWM operation
    TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // Set channel mode to edge-aligned PWM with high-true pulses
    TPM2->CONTROLS[0].CnV = 0; // Set the channel value to 0

    // Start the TPM2 counter in up-counting mode
    TPM2->SC |= TPM_SC_CMOD(1);
}

void Init_Green_LED_PWM(uint16_t period)
{
    // Enable the clock for Port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

    // Configure the MUX register for the green LED pin
    PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);

    // Enable the clock for Timer 2
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

    // Set the source for Timer 2 to be the bus clock (48 MHz)
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    // Set the period of the PWM signal
    TPM2->MOD = period-1;

    // Set the prescaler to divide by 2
    TPM2->SC =  TPM_SC_PS(1);

    // Set the debug mode to be enabled when the debugger is attached
    TPM2->CONF |= TPM_CONF_DBGMODE(3);

    // Configure the PWM channel to use the high-true pulse mode
    // (MSB=1, ELSA=1)
    TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

    // Set the initial duty cycle to 0
    TPM2->CONTROLS[1].CnV = 0;

    // Start the timer counting in up-counting mode
    TPM2->SC |= TPM_SC_CMOD(1);
}



