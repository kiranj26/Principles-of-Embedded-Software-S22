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
 * @file    audio_output.c
 * @brief   C file  that contains functions to initialize the DAC module on the KL25Z board and generate
 * sine wave tones of different frequencies. It also contains a function to output these tones through
 * the DAC using DMA transfers. The module generates two tones, A4 (440Hz) and D5 (587Hz), using the DAC
 * module on the KL25Z board
 *
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
​ *    I would like to thank the SA's of the course Daanish, Hari and Ritika for their support
 *    in understanding and explaining details of requirements.
 */

#include "MKL25Z4.h" // include header file for MKL25Z4 microcontroller
#include "fsl_debug_console.h" // include header file for debug console

#include "audio_output.h" // include header file for audio output
#include "fp_trig.h" // include header file for fast math library functions for sine and cosine
#include "systick.h" // include header file for systick timer
#include "audio_input.h" // include header file for audio input

#define DAC_POS_PIN 	(30UL) 	// define the DAC output pin
#define TONE_A4_FREQ 	(440UL) // define frequency of note A4
#define TONE_D5_FREQ 	(589UL) // define frequency of note D5
#define TONE_TRI_FREQ 	(885UL) // define frequency of triangle wave

#define SAMPLING_FREQ 	(48000UL) // define the sampling frequency
#define BUFF_SIZE 		(1024UL) // define the buffer size

#define DMA_CHANNEL 		0 // define the DMA channel
#define DMA_REQUEST_SOURCE 	54 // define the DMA request source
#define DMA_DCR_SETTINGS 	(DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK) // define the DMA control register settings

uint16_t A4[BUFF_SIZE]; // declare an array to store A4 note data
uint16_t D5[BUFF_SIZE]; // declare an array to store D5 note data
uint16_t Sin_Tri[BUFF_SIZE]; // declare an array to store sine and triangle wave data

int tune_no = 0; // initialize tune number as 0

uint16_t * reload_dma_source; // declare a pointer to reload DMA source
uint32_t reload_dma_bytecount; // declare a variable to store the reload DMA byte count


// This function initializes the DAC module
void DAC_initialise() {

    // Enable clock to DAC module
    SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;

    // Enable clock to PORTE module
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Set the multiplexer value of the DAC0_OUT pin
    PORTE->PCR[DAC_POS_PIN] &= ~(PORT_PCR_MUX(7));

    // Disable the DAC0 module
    DAC0->C1 = 0;

    // Disable the buffer and set the reference voltage to VDDA
    DAC0->C2 = 0;

    // Enable the DAC0 module and set the reference voltage to VREFH/VREFL
    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

// This function generates a sine waveform
void generate_sine_waveform(uint16_t *buffer, uint32_t buffer_size, uint32_t frequency) {

    // Calculate the period of the waveform
    uint32_t period = ((SAMPLING_FREQ + (frequency/2)) / frequency) + 1;

    // Calculate the number of cycles that will fit in the buffer
    uint32_t cycles = buffer_size / period;

    // Calculate the number of samples in the buffer
    uint32_t samples = period * cycles;

    // Generate the samples for the waveform
    for(int i = 0; i < samples; i++) {

        // Generate a sine sample using the fixed-point trigonometric functions
        buffer[i] = fp_sin(i*TWO_PI / period) + TRIG_SCALE_FACTOR;
    }
}

// This function generates a triangle waveform
void generate_triangle_waveform(uint16_t *buffer, uint32_t buffer_size, uint32_t frequency) {

    // Calculate the period of the waveform
    uint32_t period = ((SAMPLING_FREQ + (frequency/2)) / frequency) + 1;

    // Calculate the number of cycles that will fit in the buffer
    uint32_t cycles = buffer_size / period;

    // Calculate the number of samples in the buffer
    uint32_t samples = period * cycles;

    // Generate the samples for the waveform
    for(int i = 0; i < samples; i++) {

        // Generate a triangle sample using the fixed-point trigonometric functions
        buffer[i] = fp_triangle(i*TWO_PI / period) + TRIG_SCALE_FACTOR;
    }
}


void tone_to_samples() {

    // Generate the sine waveform for A4 note and store in A4 array
    generate_sine_waveform(A4, BUFF_SIZE, TONE_A4_FREQ);

    // Generate the sine waveform for D5 note and store in D5 array
    generate_sine_waveform(D5, BUFF_SIZE, TONE_D5_FREQ);

    // Generate the triangle waveform for 880Hz and store in Sin_Tri array
    generate_triangle_waveform(Sin_Tri, BUFF_SIZE, TONE_TRI_FREQ);

}


void generate_audio(uint16_t *buffer, uint16_t tone_freq) {
    uint16_t TONE_SIZE;   // Tone size
    int cycles, samples, period;  // Number of cycles, samples and period

    // Compute the period based on the tone frequency
    period = ((SAMPLING_FREQ + (tone_freq/2)) / tone_freq);

    // Compute the number of cycles based on the buffer size and period
    cycles = BUFF_SIZE / period;

    // Compute the number of samples based on the period and cycles
    samples = period * cycles;

    // Set the tone size to the given tone frequency
    TONE_SIZE = tone_freq;

    // Print the number of generated samples, the computed period and the tone frequency
    PRINTF("\n\rGenerated %d samples at %d Hz computed period=%d samples\n\r", samples, TONE_SIZE, period);

    // Reset the timer
    reset_timer();

    // Initialize DMA for playback with the generated samples
    init_dma_for_playback(buffer, samples);

    // Start DMA playback
    start_dma_playback();
}


void audio_output() {
	uint16_t *buffer; // pointer to the buffer holding the audio samples

	// If tune_no is 0, play tone A4
	if (tune_no==0) {
		buffer = A4;
		generate_audio(buffer, TONE_A4_FREQ); // generate audio of A4 frequency
		tune_no++; // increment tune_no to play next tune in the next iteration
	}
	// If tune_no is 1, play tone D5
	else if (tune_no==1) {
		buffer = D5;
		generate_audio(buffer, TONE_D5_FREQ); // generate audio of D5 frequency
		tune_no++; // increment tune_no to play next tune in the next iteration
	}
	// If tune_no is 2, play a triangle waveform
	else if (tune_no==2) {
		buffer = Sin_Tri;
		generate_audio(buffer, TONE_TRI_FREQ); // generate audio of a triangle waveform
		tune_no = 0; // reset tune_no to 0 so that A4 will be played in the next iteration
	}
}

void init_dma_for_playback(uint16_t *audio_buffer, uint32_t byte_count) {

    // Set the reload source and byte count for DMA playback
    reload_dma_source = audio_buffer;
    reload_dma_bytecount = byte_count * 2;

    // Enable the DMA and DMAMUX clocks
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

    // Disable and configure the DMA channel
    DMAMUX0->CHCFG[DMA_CHANNEL] = 0;
    DMA0->DMA[DMA_CHANNEL].DCR = DMA_DCR_SETTINGS;

    // Set the DMA interrupt priority and enable the DMA interrupt
    NVIC_SetPriority(DMA0_IRQn, 2);
    NVIC_ClearPendingIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);

    // Configure the DMAMUX channel source
    DMAMUX0->CHCFG[DMA_CHANNEL] = DMAMUX_CHCFG_SOURCE(DMA_REQUEST_SOURCE);

}

void start_dma_playback() {

    // Configure the DMA source and destination addresses and byte count
    DMA0->DMA[DMA_CHANNEL].SAR = DMA_SAR_SAR((uint32_t) reload_dma_source);
    DMA0->DMA[DMA_CHANNEL].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));
    DMA0->DMA[DMA_CHANNEL].DSR_BCR = DMA_DSR_BCR_BCR(reload_dma_bytecount);

    // Clear the DMA done flag and start DMA playback
    DMA0->DMA[DMA_CHANNEL].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;
    DMAMUX0->CHCFG[DMA_CHANNEL] |= DMAMUX_CHCFG_ENBL_MASK;

}

void DMA0_IRQHandler() {

    // Clear the DMA done flag and restart DMA playback
    DMA0->DMA[DMA_CHANNEL].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
    start_dma_playback();

}
