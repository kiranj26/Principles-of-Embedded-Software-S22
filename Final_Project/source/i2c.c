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
​ ​*​ ​@file​_name     main.c
​ ​*​ ​@introduction
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 * @referenses
 * 1) https://github.com/alexander-g-dean/ESF/blob/master/ST/Code/ch7/SysTick/main.c
 * 2) Alexander G Dean's github repository for I2C Read and Write
 *    https://github.com/alexander-g-dean/ESF/tree/master
*/

#include "i2c.h"

#define ONE				(1)		// Integer value 1
#define MSB_SHIFT		(8)		// Shift amount for MSB

// Initialize I2C1 module
void init_I2C1(void)
{
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;			// Enable clock for I2C1 module
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;			// Enable clock for PORTE
}

// Configure I2C1 module
void I2C1_Set_Flags(void)
{
    PORTE->PCR[0] |= PORT_PCR_MUX(6);			// Set pin PTE0 as I2C1_SCL
    PORTE->PCR[1] |= PORT_PCR_MUX(6);			// Set pin PTE1 as I2C1_SDA
    I2C1->C1 = 0;								// Disable I2C1 module
    I2C1->F = I2C_F_ICR(0x11) |					// Set SCL clock frequency to 100 kHz
              I2C_F_MULT(0);					// Set multiplier factor to 1
    I2C1->C1 |= (I2C_C1_IICEN_MASK);			// Enable I2C1 module
    I2C1->C2 |= (I2C_C2_HDRS_MASK);				// Enable automatic generation of STOP condition
}

// Read data from I2C1 slave device
uint16_t I2C1_read(uint8_t device_address,uint8_t register_address)
{
    uint8_t buffer;
    uint8_t buffer1;
    uint16_t result;

    I2C1_TRAN;									// Set I2C1 to transmit mode
    I2C1_M_START;								// Generate START condition
    I2C1->D = device_address << ONE;			// Send device address and write bit
    TRANS_COM									// Wait for transmission to complete
    I2C1_WAIT;

    I2C1->D = register_address;					// Send register address to read from
    TRANS_COM									// Wait for transmission to complete
    I2C1_WAIT;
    I2C1_M_RSTART;								// Generate repeated START condition
    I2C1->D = ((device_address << ONE) | 0x01);	// Send device address and read bit
    TRANS_COM									// Wait for transmission to complete
    I2C1_WAIT;

    I2C1_REC;									// Set I2C1 to receive mode
    I2C1_NACK;									// Send NACK to indicate end of data reception

    buffer = I2C1->D;							// Read first byte of data
    TRANS_COM									// Wait for transmission to complete
    I2C1_WAIT;

    buffer = I2C1->D;							// Read second byte of data
    TRANS_COM									// Wait for transmission to complete
    I2C1_WAIT;
    buffer1 = I2C1->D;							// Read third byte of data

    I2C1_M_STOP;								// Generate STOP condition

    result = (buffer << MSB_SHIFT);				// Shift first byte to MSB
    result += buffer1;							// Add second and third byte

    return result;								// Return result
}
