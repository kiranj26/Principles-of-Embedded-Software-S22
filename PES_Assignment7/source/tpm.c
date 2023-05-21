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
 * @file tpm.c
 * @brief This file contains functions for initializing and starting TPM0 and TPM1 timers
 *
 * This implementation initializes TPM0 and TPM1 timers and starts them with the provided parameters.
 * TPM0 is initialized with the given period in microseconds and TPM1 is initialized with a default
 * period defined by the clock speed and a defined overflow value.
 *
 * @author  Kiran Jojare
 * @date    April 22, 2023
 * @version 1.0
 *
 * @reference
 *
 * 1) Alexander G Dean's github repository and Book
 * https://github.com/alexander-g-dean/ESF/tree/master/
 *
 * I would like to thank the SAs of the course Daanish, Hari, and Ritika for their support
 * in understanding and explaining the details of the requirements.
 */

#include "MKL25Z4.h"
#include "tpm.h"

/**
 * @brief Initialize TPM0 with the given period
 *
 * This function initializes TPM0 timer with the given period in microseconds by configuring its
 * clock source and prescaler, as well as its modulo value for the given period. TPM0 is then
 * ready to be started by calling Start_TPM0().
 *
 * @param[in] period_us the period for the TPM0 timer in microseconds
 */
void timer_init_TMP0(uint32_t period_us) {
    // Enable the TPM0 clock
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

    // Select the MCGFLLCLK clock (48 MHz) as the clock source for TPM0
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

    // Disable the TPM0 counter while initializing
    TPM0->SC = 0;

    // Set the modulo value to the appropriate value for the given period
    TPM0->MOD = TPM_MOD_MOD(period_us);

    // Set the prescaler to divide the clock by 2^1 = 2 (i.e., TPM_CLK = 24 MHz)
    TPM0->SC = (TPM_SC_DMA_MASK | TPM_SC_PS(1));
}

/**
 * @brief Start TPM0 timer
 *
 * This function starts TPM0 timer after it has been initialized by calling Init_TPM0().
 * The TPM0 timer will continue to run until stopped by disabling its counter.
 */
void timer_start_TMP0(void) {
    // Enable the TPM0 counter
    TPM0->SC |= TPM_SC_CMOD(1);
}

void timer_init_TMP1() {
    // Enable clock to TPM1 module
    SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

    // Set TPM1 clock source to the system clock and divide by 1
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;

    // Disable TPM1 while configuring
    TPM1->SC = 0;

    // Set TPM1 modulo register to get desired frequency
    TPM1->MOD = (CLOCK/TPM_OVERFLOW)-1;

    // Set TPM1 prescaler to divide by 1
    TPM1->SC |= TPM_SC_PS(0);
}

void timer_start_TMP1(void) {
    // Enable TPM1 by setting counter mode to up counting
    TPM1->SC |= TPM_SC_CMOD(1);
}

