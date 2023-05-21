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
 * @file  i2c.h
 * @brief Header file for I2C communication with SHT21
 *
 * This file defines the I2C interface functions for the MKL25Z128 microcontroller.
 * The I2C interface is used to communicate with temperature and humidity sensor called
 * SHT21
 *
 * @author Kiran
 * @date May 04 2023
 * @version 1.0
 * @referenses
 * 1) https://github.com/alexander-g-dean/ESF/blob/master/ST/Code/ch7/SysTick/main.c
 * 2) Alexander G Dean's github repository for I2C Read and Write
 *    https://github.com/alexander-g-dean/ESF/tree/master
 *
 */
#ifndef __I2C_H__
#define __I2C_H__

#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"


/**
 * @brief Generate a START condition on I2C1 bus
 *
 * This macro generates a START condition on I2C1 bus.
 */
#define I2C1_M_START (I2C1->C1 |= I2C_C1_MST_MASK)

/**
 * @brief Generate a STOP condition on I2C1 bus
 *
 * This macro generates a STOP condition on I2C1 bus.
 */
#define I2C1_M_STOP 	(I2C1->C1 &= ~I2C_C1_MST_MASK)

/**
 * @brief Generate a repeated START condition on I2C1 bus
 *
 * This macro generates a repeated START condition on I2C1 bus.
 */
#define I2C1_M_RSTART 	(I2C1->C1 |= I2C_C1_RSTA_MASK)

/**
 * @brief Set I2C1 to transmit mode
 *
 * This macro sets I2C1 to transmit mode.
 */
#define I2C1_TRAN 		(I2C1->C1 |= I2C_C1_TX_MASK)

/**
 * @brief Set I2C1 to receive mode
 *
 * This macro sets I2C1 to receive mode.
 */
#define I2C1_REC 		(I2C1->C1 &= ~I2C_C1_TX_MASK)

/**
 * @brief Wait until interrupt flag is set
 *
 * This macro waits until interrupt flag is set.
 */
#define I2C1_WAIT 		while((I2C1->S & I2C_S_IICIF_MASK)==0); I2C1->S |= I2C_S_IICIF_MASK;

/**
 * @brief Set I2C1 to send NACK
 *
 * This macro sets I2C1 to send NACK.
 */
#define I2C1_NACK 		 (I2C1->C1 |= I2C_C1_TXAK_MASK)

/**
 * @brief Set I2C1 to send ACK
 *
 * This macro sets I2C1 to send ACK.
 */
#define I2C1_ACK 		 (I2C1->C1 &= ~I2C_C1_TXAK_MASK)

/**
 * @brief Wait until transfer is complete
 *
 * This macro waits until transfer is complete.
 */
#define TRANS_COM 		 while((I2C1->S & I2C_S_TCF_MASK)==0);


/**
 * @brief Initialize I2C1
 *
 * This function initializes I2C1.
 */
void init_I2C1(void);

/**
 * @brief Set flags for I2C1
 *
 * This function sets flags for I2C1.
 */
void I2C1_Set_Flags(void);

/**
 * @brief Read data from I2C1
 *
 * This function reads data from I2C1.
 *
 * @param device_address I2C device address
 * @param register_address Register address
 *
 * @return Data read from I2C1
 */
uint16_t I2C1_read(uint8_t device_address,uint8_t register_address);

#endif //__I2C_H__

