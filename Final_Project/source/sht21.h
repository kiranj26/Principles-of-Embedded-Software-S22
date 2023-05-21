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
 * @file sht21.h
 * @brief Header file for the SHT21 temperature and humidity sensor
 *
 * This header file contains the functions and variables declarations for using the SHT21 temperature
 * and humidity sensor.
 *
 * @author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */

#ifndef __SHT21_H__
#define __SHT21_H__

#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "i2c.h"

/**
 * @brief Reads the temperature from the SHT21 sensor
 *
 * This function reads the temperature from the SHT21 sensor and returns it as a float value.
 *
 * @return Temperature value in degrees Celsius
 */
float read_temperature(void);

/**
 * @brief Reads the humidity from the SHT21 sensor
 *
 * This function reads the humidity from the SHT21 sensor and returns it as a float value.
 *
 * @return Humidity value as a percentage
 */
float read_humidity(void);

#endif // __SHT21_H__
