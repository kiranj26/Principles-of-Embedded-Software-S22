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
 * @file wdt.h
 *
 * @brief Header file for Watchdog Timer functions implementation
 */

#ifndef __WDOG_H__
#define __WDOG_H__

#include <stdint.h>
#include <MKL25Z4.H>

// COP Watchdog Timeout
// These write-once bits select the timeout period of the COP.
// The COPT field along with the COPCLKS bit define the COP timeout period.
#define COP_DISABLED    0   //00 COP disabled
#define COP_CYCLES_01   1   //01 COP timeout after 2^5 LPO cycles or 2^13 bus clock cycles
#define COP_CYCLES_02   2   //10 COP timeout after 2^8 LPO cycles or 2^16 bus clock cycles
#define COP_CYCLES_03   3   //11 COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles

//COP Clock Select
//This write-once bit selects the clock source of the COP watchdog.
#define INTERNAL_1KHz   0   //00 Internal 1 kHz clock is source to COP
#define BUS_CLOCK       1   //01 Bus clock is source to COP

// Windowed mode is only supported when COP is running from the bus clock.
// The COP window is opened three quarters through the timeout period.
#define NORMAL_MODE     0   //00 Normal mode
#define WINDOWED_MODE   1   //01 Windowed mode

typedef struct
{
    uint8_t timeout;
    uint8_t clock_select;
    uint8_t windowsed_mode;
} COPC_config_t;

/**
 * @brief Initializes the watchdog timer (WDT) with the given configuration
 *
 * This function initializes the watchdog timer (WDT) with the given configuration.
 *
 * @param[in] config Pointer to the configuration structure for the WDT
 */
void Init_wdt(COPC_config_t *config);

/**
 * @brief Deinitializes the watchdog timer (WDT)
 *
 * This function deinitializes the watchdog timer (WDT).
 */
void Deinit_wdt(void);

/**
 * @brief Refreshes the watchdog timer (WDT)
 *
 * This function refreshes the watchdog timer (WDT) by writing to the refresh register.
 */
void Refresh_wdt(void);


#endif // __WDOG_H__
