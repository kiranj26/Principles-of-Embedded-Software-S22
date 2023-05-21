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
 * @file    audio_output.h
 * @brief   C file  that contains functions to initialize the DAC module on the KL25Z board and generate
 * sine wave tones of different frequencies. It also contains a function to output these tones through
 * the DAC using DMA transfers. The module generates two tones, A4 (440Hz) and D5 (587Hz), using the DAC
 * module on the KL25Z board
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

#ifndef _AUDIO_OUTPUT_H_
#define _AUDIO_OUTPUT_H_

#include <stdint.h>


/**
 * @brief Initializes the DMA module for playback.
 *
 * This function initializes the DMA module on the KL25Z board for playback, with the given source
 * buffer and count of samples to be played.
 *
 * @param audio_buffer Pointer to the source buffer containing the samples to be played.
 * @param byte_count The number of samples to be played.
 */
void init_dma_for_playback(uint16_t *audio_buffer, uint32_t byte_count);


/**
 * @brief DMA0 interrupt handler.
 *
 * This function is the interrupt handler for DMA0 interrupts. It clears the interrupt flag
 * and sets a flag indicating that the DMA transfer is complete.
 */
void DMA0_IRQHandler();

/**
 * @brief Generates a sine wave tone with given frequency and stores in buffer.
 *
 * @param buffer Pointer to the buffer where generated tone will be stored.
 * @param tone_freq Frequency of the sine wave tone to be generated.
 */
void generate_audio(uint16_t *buffer, uint16_t tone_freq);

/**
 * @brief Outputs the generated tones through the DAC using DMA transfers.
 *
 * This function initializes the DMA module on the KL25Z board and starts the DMA transfer of
 * the generated sine wave tones to the DAC output.
 */
void audio_output();

/**
 * @brief Starts the DMA transfer for playback.
 *
 * This function starts the DMA transfer of the samples to be played to the DAC output.
 */
void start_dma_playback();

/**
 * @brief Generates sine wave tones of different frequencies.
 *
 * This function generates sine wave tones of two different frequencies, A4 (440Hz) and D5 (587Hz),
 * and stores them in a buffer. Each tone has a duration of 2 seconds.
 */
void tone_to_samples();

/**
 * @brief Initializes the DAC module on the KL25Z board.
 */
void DAC_initialise();

#endif // _AUDIO_OUTPUT_H_
