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
​ ​*​ ​@file​_name     TSI_Sensor.c
​ ​*​ ​@introduction  C file for TSI sensor functionality. This is same file from Assignment 3.
 *
 * This code defines functions to interface with a touch sensor
 * module using the TSI (Touch Sense Input) module in a micro-controller. The
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

/* required Header File */
#include "MKL25Z4.h"
#include "TSI_Sensor.h"

// Define macros for touch sensing
#define TOUCH_OFFSET 		(600)  					// offset value to be subtracted
#define TOUCH_DATA 			(TSI0->DATA & 0xFFFF)	//macro for extracting the count from data register

// Macros for touch sense detection
#define TOUCH_DETECT_THD   	(300) 					// The threshold value for touch detection.
                                					// If the touch sensor value is greater than or equal to this value,
                                					// touch is considered to be detected.
#define TOUCH_DETECTED     	(1)  					// The return value when touch is detected by the TSI_touch_detected() function.
#define TOUCH_NOT_DETECTED 	(0)   					// The return value when touch is not detected by the T

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
 * @brief Detects touch using the Touch Sense Interface (TSI) module
 *
 * This function reads the current touch sensor value using the load_val_TSI() function,
 * which triggers a scan of the touch sensor and waits until the scan is complete.
 * It then compares the touch sensor value to a predefined threshold value, TOUCH_DETECT_THD.
 * If the touch sensor value is greater than or equal to the threshold, the function returns
 * TOUCH_DETECTED, which is a pre-defined constant. Otherwise, it returns TOUCH_NOT_DETECTED,
 * which is another pre-defined constant. The function is of type uint16_t.
 *
 * @return uint16_t A value indicating whether touch is detected or not.
 *                  Possible return values are TOUCH_DETECTED or TOUCH_NOT_DETECTED,
 *                  which are also pre-defined constants.
 */

uint16_t TSI_Touch_Detected(void)
{
	// get the current value from TSI
    int current_val = load_val_TSI();

    if (current_val >= TOUCH_DETECT_THD) {
        return TOUCH_DETECTED;
    } else {
        return TOUCH_NOT_DETECTED;
    }

}


#endif
