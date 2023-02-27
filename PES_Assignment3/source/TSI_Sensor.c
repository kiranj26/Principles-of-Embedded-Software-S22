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
​ ​*​ ​@file​_name    TSI_Sensor.c
​ ​*​ ​@intorduction This code defines functions to interface with a touch sensor
 * module using the TSI (Touch Sense Input) module in a microcontroller. The
 * init_TSI function initializes the TSI module with appropriate configuration values,
 * load_val_TSI function triggers a scan of the touch sensor and returns the current
 * touch sensor value, and TSI_Polling function polls the TSI sensor and determines the
 * position of the slider based on the current touch sensor value. The code also includes
 * comments documenting the purpose of each function and the values of the different registers
 * being used.
 *
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 19​ 2023
​ ​*​ ​@version​ 1.0
​ ​* @@referense
​ ​*              1) https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 * 				2) https://os.mbed.com/teams/Freescale/wiki/frdm-kl25z-pinnames
 * 				3) Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
 * 				   https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Senses
 *
​ *              I would like to thank the SA's of the course Daanish, Hari and Ritika for their support in understanding and explaining
 *              details of requirements
​ ​*/



#ifndef _TSI_SENSOR_C_
#define _TSI_SENSOR_C_

#include"TSI_Sensor.h"
int old_touched = 0;

/**
 * @brief Initializes the TSI sensor module
 *
 * This function initializes the TSI sensor module by configuring its registers
 * with appropriate values for the desired operation.
 *
 * @return void
 */

void init_TSI(void)
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; 					// enabling the clock
	TSI0->GENCS = TSI_GENCS_MODE(0u) | 					//operating in non-noise mode
								TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
								TSI_GENCS_DVOLT(0u) | 	//oscillator voltage rails set to default
								TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
								TSI_GENCS_PS(0u) |  	// frequency clcok divided by one
								TSI_GENCS_NSCN(31u) | 	//scanning the electrode 32 times
								TSI_GENCS_TSIEN_MASK | 	//enabling the TSI module
								TSI_GENCS_EOSF_MASK; 	// writing one to clear the end of scan flag
}
/**
 * @brief Loads the current touch sensor value from TSI_DATA register
 *
 * This function triggers a scan of the touch sensor and waits until the scan is complete.
 * It then returns the current touch sensor value by subtracting the TOUCH_OFFSET from
 * the TOUCH_COUNT register value.
 *
 * @return uint32_t The current touch sensor value
 */

int load_val_TSI(void)
{
	int scan = 0;
	TSI0->DATA = 	TSI_DATA_TSICH(10u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; 				//software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) 	// waiting for the scan to complete 32 times
	;
	scan = TOUCH_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; 			//writing one to clear the end of scan flag
	return scan- TOUCH_OFFSET;
}
/**
 *
 * @brief Polls the TSI sensor and returns the current touch status of a two-point slider
 *
 * This function reads the current value of the TSI sensor and compares it to predefined upper
 * and lower threshold values. It uses the input previous_touch_status to determine the current
 * touch status of the slider. The possible touch statuses are: SLIDER_NOT_TOUCHED if the TSI value
 * is less than 25 or if the previous_touch_status was SLIDER_NOT_TOUCHED. LEFT_SLIDER_TOUCHED if
 * the TSI value is between 25 and 600 and the previous_touch_status was LEFT_SLIDER_TOUCHED or the
 * TSI value is greater than or equal to 650 or the previous_touch_status was RIGHT_SLIDER_TOUCHED.
 * RIGHT_SLIDER_TOUCHED if the TSI value is greater than or equal to 600 and the previous_touch_status
 * was RIGHT_SLIDER_TOUCHED or the TSI value is between 25 and 600 and the previous_touch_status was
 * LEFT_SLIDER_TOUCHED.
 *
 * @param previous_touch_status The previous touch status of the slider: SLIDER_NOT_TOUCHED, LEFT_SLIDER_TOUCHED,
 * or RIGHT_SLIDER_TOUCHED.
 *
 * @return uint16_t The current touch status of the slider: SLIDER_NOT_TOUCHED, LEFT_SLIDER_TOUCHED,
 * or RIGHT_SLIDER_TOUCHED.
*/
uint16_t TSI_Polling(int32_t previous_touch_status)
{
	// get the current value from TSI
	int current_val = load_val_TSI();

	// if the value is greater than or equal to 650 or if the previous touch status was RIGHT_SLIDER_TOUCHED
	if((current_val >= UPPER_THD)  || (previous_touch_status == RIGHT_SLIDER_TOUCHED))
	{
		// if the current value is between 25 and 600
		if((current_val >= LOWER_THD) && (current_val <UPPER_THD))
		{
			// return that the left slider was touched
			return LEFT_SLIDER_TOUCHED;
		}
		// return that the right slider was touched
		return RIGHT_SLIDER_TOUCHED;
	}

	// if the current value is between 25 and 600 or if the previous touch status was LEFT_SLIDER_TOUCHED
	if (((current_val >= LOWER_THD) && (current_val <UPPER_THD)) || (previous_touch_status == LEFT_SLIDER_TOUCHED) )
	{
		// if the current value is greater than or equal to 600
		if((current_val >= UPPER_THD))
		{
			// return that the right slider was touched
			return RIGHT_SLIDER_TOUCHED;
		}
		// return that the left slider was touched
		return LEFT_SLIDER_TOUCHED;
	}

	// if the current value is less than 25 or if the previous touch status was SLIDER_NOT_TOUCHED
	if ((current_val < LOWER_THD) || (previous_touch_status == SLIDER_NOT_TOUCHED))
	{
		// return that the slider was not touched
		return SLIDER_NOT_TOUCHED;
	}

	// this line should never be reached, but if it is, return that the slider was not touched
	return SLIDER_NOT_TOUCHED;
}

#endif
