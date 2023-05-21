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
​ ​*​ ​@file​ test_sht21.c
​ ​*​ ​@brief​ C file to test successfull and valid readings from sht21 sensor for temperture and humidity
​ ​*        Added a assert function to always check if my sensor reading are as per data sheet range
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 4​ 2023
​ ​*​ ​@version​ ​1.0
​ ​*
​ ​*/

#include "test_sht21.h"
#include "i2c.h"
#include "sht21.h"
#include <assert.h>
void test_sht21(void)
{
    int i;
    for (i = 0; i < 10; i++) {
        // Set I2C1 flags for communication with SHT21 sensor
        I2C1_Set_Flags();

        // Read temperature value from SHT21 sensor and store it in a float variable
        float temp = read_temperature();

        // Added a assert function to always check if temperature sensor reading are as per data sheet range
        assert(temp >= 0.0f && temp <= 120.0f);

        // Set I2C1 flags for communication with SHT21 sensor
        I2C1_Set_Flags();

        // Read humidity value from SHT21 sensor and store it in a float variable
        float hum = read_humidity();

        // Added a assert function to always check if humidity sensor reading are as per data sheet range

        assert(hum >= 0.0f && hum <= 100.0f);

        // Print the current temperature and humidity values
        printf("Temperature: %.2f C\n\r", temp);
        printf("Humidity: %.2f %%\n\r", hum);
    }
}
