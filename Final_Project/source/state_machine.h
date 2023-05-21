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
 * @file state_machine.h
 * @brief Header file for the state machine functions
 *
 * This header file contains the function declarations for state transitions of a state machine.
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

/**
 * @brief Delay the execution for 1 second
 *
 * This function delays the execution for 1 second.
 */
void delay_1sec(void);

/**
 * @brief Check the temperature value
 *
 * This function checks the temperature value and returns a boolean indicating whether it's within a certain range or not.
 *
 * @return Boolean value indicating whether temperature is within range or not
 */
uint8_t check_temperature(void);

/**
 * @brief Check the humidity value
 *
 * This function checks the humidity value and returns a boolean indicating whether it's within a certain range or not.
 *
 * @return Boolean value indicating whether humidity is within range or not
 */
uint8_t check_humidity(void);

/**
 * @brief Print the temperature and humidity values
 *
 * This function prints the temperature and humidity values to the console.
 */
void print_temp_humd(void);

/**
 * @brief Check for user input from UART
 *
 * This function checks for user input from UART and handles it accordingly.
 */
void check_uart_input(void);

/**
 * @brief Check for user input from slider
 *
 * This function checks for user input from a slider and handles it accordingly.
 */
void check_slider_input(void);

/**
 * @brief Perform state transitions according to event
 *
 * This function performs state transitions according to the current state and the event that occurs.
 */
void state_machine(void);

/**
 * @brief Sleep state transition function
 *
 * This function performs state transitions for the sleep state.
 *
 * @param[in] event The event that occurred
 *
 * @return The next state of the state machine
 */
enum state sleep_state(enum event event);

/**
 * @brief Temperature alert state transition function
 *
 * This function performs state transitions for the temperature alert state.
 *
 * @param[in] event The event that occurred
 *
 * @return The next state of the state machine
 */
enum state alert_temp_state(enum event event);

/**
 * @brief Humidity alert state transition function
 *
 * This function performs state transitions for the humidity alert state.
 *
 * @param[in] event The event that occurred
 *
 * @return The next state of the state machine
 */
enum state alert_humid_state(enum event event);

#endif // __STATE_MACHINE_H__
