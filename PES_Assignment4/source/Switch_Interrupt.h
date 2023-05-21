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
​ ​*​ ​@file​_name     Switch_Interrupt.h
​ ​*​ ​@introduction  Header file for Switch interrupt functions
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
 *
 * @referense
 * 1) GPIO Interrupt on KL25Z
 *    https://gab.wallawalla.edu/~larry.aamodt/engr355/lect_interrupts.pdf
 */
#ifndef _SWITCH_INTERRUPT_H_
#define _SWITCH_INTERRUPT_H_

/**
 * @brief Initializes the switch interrupt on PORTA with a falling edge trigger.
 *
 * This function initializes the switch interrupt on PORTA with a falling edge trigger.
 * It also enables the clock to PORTA, configures the GPIO pin for the switch, and
 * configures the NVIC for PORTA IRQ. The switch pin is set as input.
 *
 * @return None
 */
void InitInterrupt(void);

/**
 * @brief Interrupt handler for PORTA.
 *
 * This function is the interrupt handler for PORTA. It sets the interrupt flag
 * to identify if the switch was pressed and clears the interrupt flag.
 *
 * @return None
 */
void PORTB_IRQHandler(void);

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
bool Switch_Detected(void);

/**
 * @brief Resets the flag that indicates if the switch has been pressed.
 *
 * This function resets the flag that indicates if the switch has been pressed
 * by setting it to FALSE.
 *
 * @return None
 */
void Switch_Flag_Reset(void);

#endif // _SWITCH_INTERRUPT_H_
