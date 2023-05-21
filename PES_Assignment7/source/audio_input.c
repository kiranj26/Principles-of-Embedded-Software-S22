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
 * @file 	audio_input.c
 * @brief	C file for initializes the ADC0 module and sets conversion parameters to
 * read analog input from a specific pin. It performs calibration to get accurate readings
 * and then sets the trigger configuration for the ADC. It also contains a function to perform
 * a delay using nops.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @@referense
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *
 * 	 2) ADC calibration routine specified in the KL25Z Reference Manual, §28.4.6.
 *
​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements. Thanks to Daniel and Saurav for re-iterating
 *    the concepts
 */
#include "MKL25Z4.h"                      		// Include the MKL25Z4 header file.
#include "fsl_debug_console.h"             		// Include the debug console header file.

#include "autocorrelate.h"                 		// Include the autocorrelate header file.
#include "tpm.h"                           		// Include the tpm header file.

#include <audio_input.h>                   		// Include the audio input header file.

#define GLOBAL_ADC_POS                  (20UL)    // Define the global ADC position as 20.
#define GLOBAL_ADC_INPUT_CHANNEL        (23UL)    // Define the global ADC input channel as 23.
#define GLOBAL_INPUT_BUFFER_SIZE        (1024UL)  // Define the global input buffer size as 1024.

#define CAL_UNSUCCESSFUL                (0x0040)  // Define CAL_UNSUCCESSFUL as 0x0040.
#define CAL_SHIFT                       (1)       // Define CAL_SHIFT as 1.
#define CAL_OFFSET                      (0x8000)  // Define CAL_OFFSET as 0x8000.
#define CAL_DIVIDEBY2                   (2)       // Define CAL_DIVIDEBY2 as 2.

#define DELAY_CYCLES                    (2)       // Define DELAY_CYCLES as 2.
#define DELAY_TIME                      (3)       // Define DELAY_TIME as 3.

uint16_t global_input_buffer[GLOBAL_INPUT_BUFFER_SIZE];  // Define the global input buffer.

/**
 * @brief Initializes ADC0 module and sets the conversion parameters
 */
void ADC_initialise(void) {
    // Enable clock for ADC0 module
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    // Set the PORT configuration for the ADC input pin
    PORTE->PCR[GLOBAL_ADC_POS] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[GLOBAL_ADC_POS] |= PORT_PCR_MUX(0);

    // Set the ADC configuration register
    ADC0->CFG1 = ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(2);

    // Select the input channel for the ADC
    ADC0->SC1[0] |= ADC_SC1_ADCH(GLOBAL_ADC_INPUT_CHANNEL);

    // Perform calibration of the ADC module
    ADC_Calibration();

    // Set the trigger configuration for ADC
    SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9) | SIM_SOPT7_ADC0PRETRGSEL(0);
}


/*
 * Performs calibration of the ADC to get accurate readings
 */
void ADC_Calibration(void) {
    uint16_t calibration_value = 0;

    // Start calibration by setting the CAL bit in the SC3 register
    ADC0->SC3 |= ADC_SC3_CAL_MASK;

    // Check if calibration was successful
    if (ADC0->SC3 & CAL_UNSUCCESSFUL) {
        // Print an error message if calibration was unsuccessful
        PRINTF("ADC Calibration failed !!\n\r");
    }
    else {
        // Calculate the calibration value for the plus-side gain (PG)
        calibration_value = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS;
        calibration_value /= CAL_DIVIDEBY2;
        calibration_value += CAL_OFFSET;

        // Write the calibration value to the PG register
        ADC0->PG = calibration_value;

        // Calculate the calibration value for the minus-side gain (MG)
        calibration_value = 0;
        calibration_value = ADC0->CLM0 + ADC0->CLM1 + ADC0->CLM2 + ADC0->CLM3 + ADC0->CLM4 + ADC0->CLMS;
        calibration_value = (calibration_value >> CAL_SHIFT);
        calibration_value += CAL_OFFSET;

        // Write the calibration value to the MG register
        ADC0->MG = calibration_value;
    }
}

/**
 * @brief Performs a delay using nops.
 *
 * @param n The number of times to execute the loop.
 */
void global_delay(int n) {
    int i, k;
    for (i = 0; i < n; i++) {
        __asm("nop"); // Execute no-operation instruction once.
        for (k = 0; k <= DELAY_CYCLES; k++) {
             __asm("nop"); // Execute no-operation instruction DELAY_CYCLES number of times.
        }
    }
}

/**
 * This function reads audio input samples from an ADC and stores them in a global buffer.
 * It uses a delay to ensure proper sampling and conversion of the ADC input.
 */
void audio_input(void) {
    for(int index = 0; index < GLOBAL_INPUT_BUFFER_SIZE; index++) {
        // Start ADC conversion
        ADC0->SC1[0] = GLOBAL_ADC_INPUT_CHANNEL;

        // Wait for ADC conversion to complete
        while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)) {
            // wait
        }

        // Delay to allow for proper sampling and conversion of ADC input
        global_delay(DELAY_TIME);

        // Store ADC input sample in global buffer
        global_input_buffer[index] = ADC0->R[0];
    }
}


/*
 * Performs analysis on the digital signal and outputs the result
 */

void audio_analysis(void) {
    int sum = 0; // initialize a variable to store the sum of all the values in the global input buffer
    int min_val = global_input_buffer[0]; // initialize the minimum value to the first value in the global input buffer
    int max_val = global_input_buffer[0]; // initialize the maximum value to the first value in the global input buffer
    int i;

    // loop through all the values in the global input buffer
    for(i = 0; i < GLOBAL_INPUT_BUFFER_SIZE; i++) {
        // check if the current value is less than the current minimum value
        if(min_val > global_input_buffer[i]) {
            min_val = global_input_buffer[i]; // if so, update the minimum value to the current value
        }
        // check if the current value is greater than the current maximum value
        if(max_val < global_input_buffer[i]) {
            max_val = global_input_buffer[i]; // if so, update the maximum value to the current value
        }
        sum += global_input_buffer[i]; // add the current value to the sum
    }

    // calculate the average value by dividing the sum by the number of values in the global input buffer
    int avg_val = sum / i;

    // detect the period of the audio signal using autocorrelation
    int period = autocorrelate_detect_period(global_input_buffer, GLOBAL_INPUT_BUFFER_SIZE, kAC_16bps_unsigned);

    // print the minimum value, maximum value, average value, period, and sample frequency of the audio signal
    PRINTF("min=%d max=%d avg=%d period=%d samples frequency=%d Hz\n\r",
        min_val, max_val, avg_val, period, (TPM_OVERFLOW / period));
}





