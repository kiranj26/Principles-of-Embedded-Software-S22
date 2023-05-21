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
​ ​*​ ​@file​_name     StateMachine.c
​ ​*​ ​@introduction  C file for State Machine Functionality
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
 *
 * @referense
 * 1) State Machine Framework in C
 *    https://www.codeproject.com/Articles/5273346/State-machine-framework-in-C#:~:text=State%20Machine%20Framework%20in%20C%201%20UML%20State,5%20Configuration%20...%206%20State%20machine%20logging%20
 */
#ifndef _STATE_MACHINE_C_
#define _STATE_MACHINE_C_

/* Header File*/
#include <stdbool.h>

#include "PWM_LED_Func.h"
#include "Timing.h"
#include "TSI_Sensor.h"
#include "Switch_Interrupt.h"
#include "StateMachine.h"
#include "log.h"


/* Global values for start and end of R G and B LED's */
int red_start_val;
int red_end_val;
int green_start_val;
int green_end_val;
int blue_start_val;
int blue_end_val;

/* Global Value for Time to check touch sensed every 62.5 ms */
int Time_TouchSenseStart = 0 ;

// Enumerated list of possible states for the State Machine
typedef enum
{
    STOP,                           	// Stop state
    GO,                             	// Go state

    TRANSITION,                     	// Transition state
	TRANSITION_WITHIN_TRANSITION,       // Transition within Transition State

    WARNING,                        	// Normal Warning state without switch and slider detected

    SLIDER_SWITCH_WARNING,              // Warning state with switch or slider detected
    SLIDER_SWITCH_WARNING_TRANSITION,   // TRasition state from Any color to Warning

    CROSSWALK,                      	// Crosswalk state
    CROSSWALK_TRANSITION,           	// Crosswalk transition state
    CROSSWALK_GO_TRANSITION,        	// Crosswalk to go transition state

}state_t;

/* Global state with STOP state as initial state*/
volatile state_t state = STOP;

/* Assigning current state to STOP state initially */
volatile state_t cur_state = STOP;

/* Constants for LED colors in different states */
#define RED_IN_STOP_STATE 			(0xFF)    // Red LED value in stop state
#define GREEN_IN_STOP_STATE 		(0x00)    // Green LED value in stop state
#define BLUE_IN_STOP_STATE 			(0x00)    // Blue LED value in stop state

#define RED_IN_GO_STATE				(0x00)    // Red LED value in go state
#define GREEN_IN_GO_STATE 			(0xFF)    // Green LED value in go state
#define BLUE_IN_GO_STATE 			(0x00)    // Blue LED value in go state

#define RED_IN_WARNING_STATE 		(0xFF)    // Red LED value in warning state
#define GREEN_IN_WARNING_STATE 		(0xFF)    // Green LED value in warning state
#define BLUE_IN_WARNING_STATE 		(0x00)    // Blue LED value in warning state

#define RED_IN_CROSSWALK_STATE 		(0x00)    // Red LED value in crosswalk state
#define GREEN_IN_CROSSWALK_STATE	(0x10)    // Green LED value in crosswalk state
#define BLUE_IN_CROSSWALK_STATE 	(0x30)    // Blue LED value in crosswalk state

#define LED_ON_DELAY_CROSSWALK 		(16)      // 750 ms ON LED on delay during crosswalk state
#define LED_OFF_DELAY_CROSSWALK 	(4)       // 250 ms OFF LED off delay during crosswalk state

#ifdef DEBUG
	#define DELAY_FOR_STOP_GO_STATES 	(80)     // 5 sec Delay between stop and go states in DEBUG mode
	#define DELAY_FOR_WARNING_STATE 	(48)     // 3 sec Delay for warning state
#else
	#define DELAY_FOR_STOP_GO_STATES 	(320)    // 20 sec Delay between stop and go states in PRODUCTION mode
	#define DELAY_FOR_WARNING_STATE 	(80)     // 5 sec Delay for warning state in PRODUCTION mode
#endif

#define DELAY_FOR_TRANSITION  		(16)     	// 1 sec Delay for transition state in both DEBUG and PRODUCTION
#define DELAY_FOR_CROSSWALK 	  	(80)     	// 5 secDelay for crosswalk state in both DEBUG and PRODUCTION

#define NO_COLOR 		(0)
#define CROSSWALK_SEC 	(5)
#define ZERO 			(0)

// Variables to track touch and switch detection
bool touch_detected = false; 						// Indicates whether a touch has been detected
bool switch_detected = false; 						// Indicates whether a switch has been detected

// Variable to track touch detection during a color transition
bool touch_detected_in_transition = false; 			// Indicates whether a touch has been detected during a color transition


/**
 * @brief Set the start values for the RGB LED when in STOP state
 */
void RGB_STOP_State_StartValue(void)
{
	red_start_val 	= RED_IN_STOP_STATE; 	// Set the start value for red channel
	green_start_val = GREEN_IN_STOP_STATE; 	// Set the start value for green channel
	blue_start_val 	= BLUE_IN_STOP_STATE; 	// Set the start value for blue channel
}

/**
 * @brief Set the end values for the RGB LED when in STOP state
 */
void RGB_STOP_State_EndValue(void)
{
	red_end_val 	= RED_IN_STOP_STATE; 	// Set the end value for red channel
	green_end_val 	= GREEN_IN_STOP_STATE; 	// Set the end value for green channel
	blue_end_val 	= BLUE_IN_STOP_STATE; 	// Set the end value for blue channel
}

/**
 * @brief Set the start values for the RGB LED when in GO state
 */
void RGB_GO_State_StartValue(void)
{
	red_start_val 	= RED_IN_GO_STATE; 		// Set the start value for red channel
	green_start_val = GREEN_IN_GO_STATE; 	// Set the start value for green channel
	blue_start_val 	= BLUE_IN_GO_STATE; 	// Set the start value for blue channel
}

/**
 * @brief Set the end values for the RGB LED when in GO state
 */
void RGB_GO_State_EndValue(void)
{
	red_end_val 	= RED_IN_GO_STATE; 		// Set the end value for red channel
	green_end_val 	= GREEN_IN_GO_STATE; 	// Set the end value for green channel
	blue_end_val 	= BLUE_IN_GO_STATE; 	// Set the end value for blue channel
}

/**
 * @brief Set the start values for the RGB LED when in WARNING state
 */
void RGB_WARNING_State_StartValue(void)
{
	red_start_val 	= RED_IN_WARNING_STATE; 	// Set the start value for red channel
	green_start_val = GREEN_IN_WARNING_STATE; 	// Set the start value for green channel
	blue_start_val 	= BLUE_IN_WARNING_STATE; 	// Set the start value for blue channel
}

/**
 * @brief Set the end values for the RGB LED when in WARNING state
 */
void RGB_WARNING_State_EndValue(void)
{
	red_end_val 	= RED_IN_WARNING_STATE; 	// Set the end value for red channel
	green_end_val 	= GREEN_IN_WARNING_STATE; 	// Set the end value for green channel
	blue_end_val 	= BLUE_IN_WARNING_STATE; 	// Set the end value for blue channel
}

/**
 * @brief Set the start values for the RGB LED when in CROSSWALK state
 */
void RGB_CROSSWALK_State_StartValue(void)
{
	red_start_val 	= RED_IN_CROSSWALK_STATE; 	// Set the start value for red channel
	green_start_val = GREEN_IN_CROSSWALK_STATE; // Set the start value for green channel
	blue_start_val 	= BLUE_IN_CROSSWALK_STATE; 	// Set the start value for blue channel
}

/**
 * @brief Set the end values for the RGB LED when in CROSSWALK state
 */
void RGB_CROSSWALK_State_EndValue(void)
{
	red_end_val   	= RED_IN_CROSSWALK_STATE; 	// Set the end value for red channel
	green_end_val 	= GREEN_IN_CROSSWALK_STATE; // Set the end value for green channel
	blue_end_val  	= BLUE_IN_CROSSWALK_STATE; 	// Set the end value for blue channel
}

/**
 * @brief This function turns off touch/switch detection, gets the starting
 *        leftover value of RGB, sets the end value to warning, resets the timer
 *        for 1 sec delay and transitions to the next state within the transition.
 *
 * @return None
 */

void Transition_Within_Transition_Processing(void)
{
    touch_detected_in_transition = true;  			// Turn off touch/switch detection since delay is not over
    get_RGB_within_transition();       			// Get the starting left over value of RGB
    RGB_WARNING_State_EndValue();      			// Get end value as WARNING
    reset_timer();                     			// Reset timer and start transition again for 1 sec delay
    cur_state = TRANSITION_WITHIN_TRANSITION; 	// Make next state as WARNING State
    state     = TRANSITION;
}

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

void TouchSensor_Switch_Detection(void)
{
	// Poll switch and slider at every 125 ms
	if((now_tick() >= Time_TouchSenseStart + 1)){

		// If touch has been detected in transition earlier
		// don't fetch the latest values till transition delay is over
		if((touch_detected_in_transition != true)){
			// Check if touch or switch is detected
			touch_detected 	= TSI_Touch_Detected();
			switch_detected = Switch_Detected();
		}

		// Check if switch or slider is detected and make sure current state is not CROSSWALK or COSSWALK Transition
		if( ( ( touch_detected == 1) && (cur_state != CROSSWALK) && (cur_state != CROSSWALK_TRANSITION)) ||
				( (switch_detected == 1) && (cur_state != CROSSWALK) && (cur_state != CROSSWALK_TRANSITION)) )
		{
			LOG("\n\r*** Button Press / Slider Touch Detected at %d ms ***\n\r\n\r",now() );

			// If switch or slider is detected, set current state to SLIDER_SWITCH_WARNING and transition state to SLIDER_SWITCH_WARNING_TRANSITION
			cur_state = SLIDER_SWITCH_WARNING;
			state = SLIDER_SWITCH_WARNING_TRANSITION;

			// Change RGB led end value with R,G and B of Warning State
			// Since the state is being changed to WARNING
			RGB_WARNING_State_EndValue();

			// Reset the global flag for switch interrupt
			Switch_Flag_Reset();

			// reset the timer
			reset_timer();
			LOG("Transition From Current State to WARNING started after ext interrupt at %d ms\n\r", now() );

		}

		// Update the time for touch sense start
		Time_TouchSenseStart = now_tick();
	}
}

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

void State_Machine(void)
{

		/******************************************
		 ******* Slider/ Switch  Polling **********
		 ******************************************/
		 TouchSensor_Switch_Detection();


		/******************************************
		 ********** Main State Machine ************
		 ******************************************/
		switch(state)
		{
		// Stop State
	    case STOP:
				if(get_timer() >= DELAY_FOR_STOP_GO_STATES)
				{
					cur_state 	= STOP;
					state 		= TRANSITION;

					// Perform necessary state transition operations
					RGB_STOP_State_StartValue();
					RGB_GO_State_EndValue();

					// Reset the timer for the next state
					reset_timer();
					LOG("Transition From STOP to GO started at %d ms\n\r", now());
					break;
				}
				else
				{
					RGB_STOP_State_StartValue(); // Set the RGB LED to its initial value
					// Set the color of the RGB LED for the STOP state
					set_color(RED_IN_STOP_STATE, GREEN_IN_STOP_STATE, BLUE_IN_STOP_STATE);

					break;
				}
		// GO State
	    case GO:
	            if(get_timer() >= DELAY_FOR_STOP_GO_STATES)
	            {
	                cur_state 	= GO;
	                state 		= TRANSITION;

	                // Perform necessary state transition operations
	                RGB_GO_State_StartValue();
	                RGB_WARNING_State_EndValue();

	                reset_timer(); // Reset the timer for the next state
					LOG("Transition From GO to WARNING started at %d ms\n\r", now());
	                break;
	            }
	            else
	            {
	                RGB_GO_State_StartValue(); // Set the RGB LED to its initial value

	                // Set the color of the RGB LED for the GO state
	                set_color(RED_IN_GO_STATE, GREEN_IN_GO_STATE, BLUE_IN_GO_STATE);

	                break;
	            }
	        // State Warning
	    case WARNING:
	        	if(get_timer() >= DELAY_FOR_WARNING_STATE)
	            {
	                cur_state 	= WARNING;
	                state 		= TRANSITION;

	                // Perform necessary state transition operations
	                RGB_WARNING_State_StartValue();
	                RGB_STOP_State_EndValue();

	                reset_timer(); // Reset the timer for the next state
	                if(cur_state == WARNING)
	                {
	                	LOG("Transition From WARNING to STOP started at %d ms\n\r", now() );
	                }
	                break;

	            }
	            else
	            {
	                RGB_WARNING_State_StartValue(); // Set the RGB LED to its initial value
	                // Set the color of the RGB LED for the WARNING state
	                set_color(RED_IN_WARNING_STATE, GREEN_IN_WARNING_STATE, BLUE_IN_WARNING_STATE);

	                break;
	            }
	    // State Transition
	    case TRANSITION:
	    	// If the current state is STOP, check the timer to see if enough time has passed to transition to the GO state
	    	if (cur_state == STOP) {
	    		if (get_timer() >= DELAY_FOR_TRANSITION) {
	    			state = GO;
	    			reset_timer();
					LOG("Transition From STOP to GO completed at %d ms\n\r", now());

	    		}
	    		// Execute a color transition effect if switch detected within the existing transition
				if ((TSI_Touch_Detected() == 1) || (Switch_Detected() == 1) )
				{
					//Transition_Within_Transition_Processing();
					Transition_Within_Transition_Processing();

				}else
				{
	    			color_transition();
				}

	    	}
	    	// If the current state is GO, check the timer to see if enough time has passed to transition to the WARNING state
	    	else if (cur_state == GO) {
	    		if (get_timer() >= DELAY_FOR_TRANSITION) {
	    			state = WARNING;
	    			reset_timer();
					LOG("Transition From GO to WARNING ended at %d ms\n\r", now());

	    		}
	    		// Execute a color transition effect if switch detected within the existing transition
				if ((TSI_Touch_Detected() == 1) || (Switch_Detected() == 1) )
				{
					Transition_Within_Transition_Processing();
				}else
				{
					color_transition();
				}

	    	}
	    	// If the current state is WARNING, check the timer to see if enough time has passed to transition to the STOP state
	    	else if (cur_state == WARNING) {
	    		if (get_timer() >= DELAY_FOR_TRANSITION) {
	    			state = STOP;
	    			reset_timer();
	    			LOG("Transition From WARNING to STOP ended at %d ms\n\r", now() );

	    		}else
	    		{
	    		color_transition();
	    		}
	    	}

	    	else if (cur_state == TRANSITION_WITHIN_TRANSITION)
	    	{
	    		if (get_timer() >= DELAY_FOR_TRANSITION )
	    		{
	    			touch_detected_in_transition = false;
	    			state = SLIDER_SWITCH_WARNING;
	    			cur_state = SLIDER_SWITCH_WARNING;
	    			reset_timer();
	    		}else{
				// Get the start value as current R G and B values from existing transition
	    		color_transition_within_transition();
	    		}
	    	}
	    	// Exit the switch statement
	    	break;

	    	// This case handles the transition from the SLIDER_SWITCH_WARNING_TRANSITION state to the SLIDER_SWITCH_WARNING state
	    	case SLIDER_SWITCH_WARNING_TRANSITION:

	    		// Check if enough time has passed to transition to the SLIDER_SWITCH_WARNING state
	    		if (get_timer() >= DELAY_FOR_TRANSITION) {

	    			// Set the current state to SLIDER_SWITCH_WARNING and reset the timer
	    			state = SLIDER_SWITCH_WARNING;
	    			reset_timer();
	    			LOG("Transition From Current State to WARNING ended after ext interrupt at %d ms\n\r", now() );
	    			break;
	    		}

	    		// If not enough time has passed, execute a color transition effect
	    		color_transition();
	    		break;

	    	// State for Slider Switch Warning
	    	case SLIDER_SWITCH_WARNING:

	    		// Check if enough time has passed to transition to the CROSSWALK_TRANSITION state
	    		if(get_timer() >= DELAY_FOR_WARNING_STATE) {

	    			// Set the current state to SLIDER_SWITCH_WARNING, and the state to CROSSWALK_TRANSITION
	    			cur_state = SLIDER_SWITCH_WARNING;
	    			state = CROSSWALK_TRANSITION;
    		        RGB_WARNING_State_StartValue();
    		        RGB_CROSSWALK_State_EndValue();

	    			reset_timer();
	    			LOG("Transition WARNING to CROSSWALK started after ext interrupt at %d ms\n\r", now() );
	    			break;

	    		} else {

	    			// If not enough time has passed, execute a warning color effect
	    			RGB_WARNING_State_StartValue();
	    			set_color(RED_IN_WARNING_STATE, GREEN_IN_WARNING_STATE, BLUE_IN_WARNING_STATE);
	    			break;
	    		}

	    		// This case handles the transition from the CROSSWALK_TRANSITION state to the CROSSWALK state
	    		// State Crosswalk Transition
	    		case CROSSWALK_TRANSITION:

	    		    // Check if enough time has passed to transition to the CROSSWALK state
	    		    if (get_timer() >= DELAY_FOR_TRANSITION) {

	    		        // Set the current state to CROSSWALK_TRANSITION and the state to CROSSWALK
	    		        cur_state = CROSSWALK_TRANSITION;
	    		        state = CROSSWALK;
	    		        reset_timer();
		    			LOG("Transition WARNING to CROSSWALK ended after ext interrupt at %d ms\n\r", now() );
	    		        break;
	    		    } else{

	    		        // If not enough time has passed, execute a color transition effect
	    		        color_transition();
	    		    }
	    		break;

	    		// State Crosswalk
	    		case CROSSWALK:
	    		    set_color(NO_COLOR, NO_COLOR, NO_COLOR);
	    		    for (uint32_t i = ZERO; i < CROSSWALK_SEC; i++) {

	    		        // Wait for the specified time before turning off the lights
	    		        while (get_timer() < LED_OFF_DELAY_CROSSWALK) {
	    		            set_color(NO_COLOR, NO_COLOR, NO_COLOR);
	    		        }

	    		        // Wait for the specified time before turning on the crosswalk lights
	    		        while (get_timer() < LED_ON_DELAY_CROSSWALK) {
	    		            set_color(RED_IN_CROSSWALK_STATE, GREEN_IN_CROSSWALK_STATE, BLUE_IN_CROSSWALK_STATE);
	    		        }

	    		        // Transition to the next state
	    		        state = CROSSWALK_GO_TRANSITION;
	    		        // Execute a color transition effect
	    		    	RGB_CROSSWALK_State_StartValue();
	    		    	RGB_GO_State_EndValue();
	    		        reset_timer();
	    		    }
    				LOG("Transition From CROSSWALK to GO started at %d ms\n\r", now());
	    		    // Reset the switch flag
	    		    Switch_Flag_Reset();
	    		break;

	    		// State for Cross-walk to Go Transition
	    		case CROSSWALK_GO_TRANSITION:
	    		    if (get_timer() >= DELAY_FOR_TRANSITION) {
	    		        // Transition to the GO state
	    		        cur_state = CROSSWALK_GO_TRANSITION;
	    		        state = GO;
	    		        reset_crosswalk_timer();
	    		        reset_timer();
	    				LOG("Transition From CROSSALK to GO ended at %d ms\n\r", now());

	    		        break;

	    		    }
	    		    // Execute a color transition effect if switch detected within the existing transition
					if ((TSI_Touch_Detected() == 1) || (Switch_Detected() == 1) )
					{
						Transition_Within_Transition_Processing();

					}else
					{
		    		color_transition();
					}
	    		    break;

	    		// Default case
	    		default:
	    		    break;
		}
}

#endif //_STATE_MACHINE_C_
