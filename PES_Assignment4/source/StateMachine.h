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
​ ​*​ ​@file​_name     StateMachine.h
​ ​*​ ​@introduction  Headers for State Machine Functions
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
 *
 * @referense
 * 1) State Machine Framework in C
 *    https://www.codeproject.com/Articles/5273346/State-machine-framework-in-C#:~:text=State%20Machine%20Framework%20in%20C%201%20UML%20State,5%20Configuration%20...%206%20State%20machine%20logging%20
 */

#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_


/**
 * @brief Set the start values for the RGB LED when in STOP state
 */
void RGB_STOP_State_StartValue(void);

/**
 * @brief Set the end values for the RGB LED when in STOP state
 */
void RGB_STOP_State_EndValue(void);


/**
 * @brief Set the start values for the RGB LED when in GO state
 */
void RGB_GO_State_StartValue(void);

/**
 * @brief Set the end values for the RGB LED when in GO state
 */
void RGB_GO_State_EndValue(void);


/**
 * @brief Set the start values for the RGB LED when in WARNING state
 */
void RGB_WARNING_State_StartValue(void);


/**
 * @brief Set the end values for the RGB LED when in WARNING state
 */
void RGB_WARNING_State_EndValue(void);

/**
 * @brief Set the start values for the RGB LED when in CROSSWALK state
 */
void RGB_CROSSWALK_State_StartValue(void);


/**
 * @brief Set the end values for the RGB LED when in CROSSWALK state
 */
void RGB_CROSSWALK_State_EndValue(void);

/**
 * @brief This function represents the overall state machine, which controls the
 *        behavior of the traffic light system based on the current state.
 *
 * The state machine controls the transition between different states, and the
 * behavior of the LEDs based on the current state. The function loops infinitely,
 * transitioning between different states based on timing and user input.
 *
 * @return None
 */

void TouchSensor_Switch_Detection(void);

/**
 * @brief This function turns off touch/switch detection, gets the starting
 *        leftover value of RGB, sets the end value to warning, resets the timer
 *        for 1 sec delay and transitions to the next state within the transition.
 *
 * @return None
 */
void Transition_Within_Transition_Processing(void);

/**
 * @brief This function represents the overall state machine, which controls the
 *        behavior of the traffic light system based on the current state.
 *
 * The state machine controls the transition between different states, and the
 * behavior of the LEDs based on the current state. The function loops infinitely,
 * transitioning between different states based on timing and user input.
 *
 * @return None
 */
void State_Machine(void);




#endif //_STATE_MACHINE_H_
