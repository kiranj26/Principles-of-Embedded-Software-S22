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
 * @file
 * @brief
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


#ifndef _TPM_H_
#define _TPM_H_

#include <stdint.h>

#define CLOCK (48000000UL)
#define TPM_OVERFLOW (96000UL)

void timer_init_TMP0(uint32_t period_us);

void timer_start_TMP0(void);

void timer_init_TMP1();

void timer_start_TMP1(void);

#endif // _TPM_H_
