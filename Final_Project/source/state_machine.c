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
 * @file state_machine.c
 * @brief C file for state machine implementation
 *
 * This C file creates a state machine that handles different states like SLEEP , ALERT, WATCHDOG and SLIDER.
 * File declared different sub-functions and variables required for state machine and its state transitions
 *
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

// Define required libraries
#include <stdint.h> 		// integer data types
#include <stdio.h> 			// standard input/output
#include <fsl_debug_console.h>

#include "i2c.h"			// I2C
#include "sht21.h" 			// temperature and humidity sensor
#include "TSI.h" 			// touch slider input
#include "rgb_led.h" 		// RGB LED control
#include "timer.h"			// timer functions
#include "state_machine.h" 	// state machine functionality

#define MAX_PWM 255 // maximum PWM value

static float TEMP_THRESHOLD = 40.00; // temperature threshold
static float HUMD_THRESHOLD = 100.00; // humidity threshold

static volatile ticktime_t time_alert_mode = 0; // alert mode timer
static volatile int32_t previous_touch = SLIDER_NOT_TOUCHED; // previous touch slider value

// Enumeration of possible states
enum state {
	SLEEP, 			// default state
	ALERT_TEMP, 	// temperature alert state
	ALERT_HUMID, 	// humidity alert state
	ALERT, 			// both temperature and humidity alert state
	SLIDER, 		// slider input state
	WATCHDOG 		// watchdog timer state
};

enum state current_state = SLEEP; // initialize state to default

// Delay function for 1 second
void delay_1sec(void)
{
	for (int i = 0; i < 1000000; i++); // delay loop
}

// Check if temperature is above threshold
uint8_t check_temperature(void)
{
	// Setting I2C1 Flags
	I2C1_Set_Flags();
	// Read temperature from sensor
	float temperature = read_temperature();

	if (temperature > TEMP_THRESHOLD && temperature >= 0) {
		return 1;
	} else {
		return 0;
	}
}

// Check if humidity is above threshold
uint8_t check_humidity(void)
{
	// Setting I2C1 Flags
	I2C1_Set_Flags();
	// Read humidity from sensor
	float temperature = read_humidity();

	if (temperature > HUMD_THRESHOLD) {
		return 1;
	} else {
		return 0;
	}
}

// Print current temperature and humidity values
void print_temp_humd()
{
	// Setting I2C1 Flags
	I2C1_Set_Flags();
	// Store temperature value from SHT21 sensor
	float temp = read_temperature();
	// Print current temperature
	printf("Temperature is: %.3f \n\r", temp);

	// Setting I2C1 Flags
	I2C1_Set_Flags();
	// Store humidity value from SHT21 sensor
	float hum = read_humidity();
	// Print current humidity
	printf("Humidity is: %.3f \n\r", hum);
}

// Check if alert mode timer has elapsed
void check_alert_mode_time(void)
{
	if (time_alert_mode >= 1000 && (!(time_alert_mode < 0))) {
		TEMP_THRESHOLD = 40.00;
		HUMD_THRESHOLD = 100.00;
		current_state = WATCHDOG;
	}
}


void check_slider_input(void)
{
	previous_touch = TSI_Polling(previous_touch);

	if((previous_touch == LEFT_SLIDER_TOUCHED))
	{
		// if left slider pressed during delay
		// change the threshold as follows
		// turn_on_red_led();
		TEMP_THRESHOLD = 20.00;
		HUMD_THRESHOLD = 50.00;
		current_state = SLIDER;
	}
	// if right slider touched
	else if ((previous_touch == RIGHT_SLIDER_TOUCHED))
	{
		// if left slider pressed during delay
		// change the threshold as follows
		TEMP_THRESHOLD = 45.00;
		HUMD_THRESHOLD = 150.00;
		current_state = SLIDER;
	}else{
		// keep the value old one
		// current_state = SLEEP;
	}
	previous_touch = SLIDER_NOT_TOUCHED;
}

void state_machine(void)
{
	// Check if it's time to switch to alert mode.
	check_alert_mode_time();

	// Check if the slider input has changed.
	check_slider_input();

	// Handle each state.
	switch(current_state)
	{
	case SLEEP:
		// Print the current state.
		PRINTF("\n\r|             Sleep Mode                |\n\r");

		// Check if the temperature is high.
		if (check_temperature())
		{
			current_state = ALERT_TEMP;
		}

		// Check if the humidity is high.
		if (check_humidity())
		{
			current_state = ALERT_HUMID;
		}

		// Check if both temperature and humidity are high.
		if (check_humidity() && check_temperature())
		{
			current_state = ALERT;
		}

		// Print the current temperature and humidity.
		print_temp_humd();

		// Reset the alert mode timer.
		reset_alert_mode_timer();

		// Blink the blue LED.
		breathing_effect_blue();
		delay_1sec();
		break;

	case ALERT_TEMP:
		// Print the current state.
		PRINTF("\n\r|     Alert Mode (Temperature)          |\n\r");

		// Get the time spent in alert mode and print it.
		time_alert_mode = get_alert_time();
		PRINTF("Time in alert Mode = %d\n\r",time_alert_mode);

		// Set I2C1 flags.
		I2C1_Set_Flags();

		// Get the current temperature from the SHT21 sensor.
		float temp=read_temperature();

		// Print the current temperature.
		printf("Temperature is High: %.3f \n\r",temp);

		// Check if temperature goes back to normal
		if (!check_temperature()) {
			current_state = SLEEP;
		}

		// Blink the red LED.
		breathing_effect_red();
		break;

	case ALERT_HUMID :
		// Print the current state.
		PRINTF("\n\r|     Alert Mode (Humidity)             |\n\r");

		// Get the time spent in alert mode and print it.
		time_alert_mode = get_alert_time();
		PRINTF("Time in alert Mode = %d\n\r",time_alert_mode);

		// Set I2C1 flags.
		I2C1_Set_Flags();

		// Get the current humidity from the SHT21 sensor.
		float hum= read_humidity();

		// Print the current humidity.
		printf("Humidity is High: %.3f \n\r",hum);

		// Check if humidity goes back to normal
		if (!check_humidity()) {
			current_state = SLEEP;
		}

		// Blink the red LED.
		breathing_effect_red();
		break;

	case ALERT:
		// print Alert mode
		PRINTF("\n\r|              Alert Mode                 |\n\r");
		// get time in alert mode
		time_alert_mode = get_alert_time();
		// print time in alert mode
		PRINTF("Time in alert Mode = %d\n\r",time_alert_mode);

		// check if temperature goes back to normal
		if (!check_temperature()) {
			// set current state to SLEEP
			current_state = SLEEP;
		}
		else {
			// set I2C1 flags
			I2C1_Set_Flags();
			// read temperature value from SHT21 sensor and store it
			float temp1 = read_temperature();
			// print current temperature
			printf("Temperature is High: %.3f \n\r", temp1);
		}

		// check if humidity goes back to normal
		if (!check_humidity()) {
			// set current state to SLEEP
			current_state = SLEEP;
		}
		else {
			// set I2C1 flags
			I2C1_Set_Flags();
			// read humidity value from SHT21 sensor and store it
			float hum1 = read_humidity();
			// print current humidity
			printf("Humidity is High: %.3f \n\r", hum1);
		}

		// show breathing effect on red LED
		breathing_effect_red();
		break;

		// if current state is SLIDER
	case SLIDER:
		// print Slider mode
		PRINTF("\n\r|              Slider Mode                |\n\r");
		// print that sensor thresholds have changed
		PRINTF("\n\r|          Sensor Thresholds Changed      |\n\r");
		// print temperature threshold
		PRINTF("\n\r| Temperature Threshold - %.4f |\n\r", TEMP_THRESHOLD);
		// print humidity threshold
		PRINTF("\n\r| Humidity Threshold    - %.4f |\n\r", HUMD_THRESHOLD);
		// set current state to SLEEP
		current_state = SLEEP;
		// delay for 1 second
		delay_1sec();
		// reset alert mode timer
		reset_alert_mode_timer();

		// show breathing effect on white LED
		breathing_effect_white();
		break;

		// if current state is WATCHDOG
	case WATCHDOG:
		// print Watch Dog mode
		PRINTF("\n\r|              Watch Dog Mode             |\n\r");
		// print alert message
		PRINTF("\n\r|               !! ALERT !!               |\n\r");
		// print that sensor readings are high
		PRINTF("\n\r|          SENSOR READING HIGH            |\n\r");
		// print that the system is being reset
		PRINTF("\n\r|          Resetting the system           |\n\r");
		// delay for 1 second
		delay_1sec();

		// set time in alert mode to 0
		time_alert_mode = 0;
		// reset timer
		reset_timer();

		// set current state to SLEEP
		current_state = SLEEP;
		// delay for 1 second
		delay_1sec();
		// reset alert mode timer
		reset_alert_mode_timer();

		// show breathing effect on yellow LED
		breathing_effect_yellow();
		break;

		// default case
	default:
		// reset alert mode timer
		reset_alert_mode_timer();
		break;

	}
}
