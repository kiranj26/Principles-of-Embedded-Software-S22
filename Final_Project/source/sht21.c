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
 * @file sht21.c
 *
 * @brief C file for SHT21 temperature and humidity sensor functions
 *  The file contains functions & varibled declared to read values from sensor.
 *
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 *
 */

#include "sht21.h"    				// Include header file for SHT21 sensor

#define TEMPERATURE 	(0xE3)     	// Assign master register address for temperature as 0xE3
#define HUMIDITY 		(0xE5)    	// Assign master register address for humidity as 0xE5
#define SHT21_ADDRESS 	(0x40)   	// Assign device address for SHT21 as 0x40

// Define function to read temperature
float read_temperature(void)
{
	// Read raw data from sensor using device address and master
	// register address for temperature and save in raw_data
    uint16_t raw_data = I2C1_read(SHT21_ADDRESS,TEMPERATURE);

    // Clear the last 2 bits in raw data

    raw_data &= ~0x003;
    // Convert raw data into Celsius using formula provided
    // in the datasheet and return the temperature value
    return (-46.85 + 175.72/65536 * (float)raw_data);
}

// Define function to read humidity
float read_humidity(void)
{
	// Read raw data from sensor using device address and
	// master register address for humidity and save in raw_data
    uint16_t raw_data = I2C1_read(SHT21_ADDRESS,HUMIDITY);

    // Clear the last 2 bits in raw data
    raw_data &= ~0x003;

    // Convert raw data into relative humidity (%) using formula
    // provided in the datasheet and return the humidity value
    return (-6.0 + 125.0/65536 * (float)raw_data);
}
