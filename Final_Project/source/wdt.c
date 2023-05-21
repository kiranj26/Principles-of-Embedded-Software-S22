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
 * @file wdt.c
 *
 * @brief Watchdog Timer functions implementation
 */

#include "wdt.h"

/**
 * @brief Initializes the watchdog timer
 *
 * This function initializes the watchdog timer with the configuration values specified in the COPC_config_t
 *
 * @param[in] config Configuration values for watchdog timer
 */
void Init_wdt(COPC_config_t *config)
{
    SIM->COPC = (SIM_COPC_COPW(config->windowsed_mode)) |
                (SIM_COPC_COPCLKS(config->clock_select)) |
                (SIM_COPC_COPT(config->timeout));
}

/**
 * @brief Deinitializes the watchdog timer
 *
 * This function disables the watchdog timer.
 */
void Deinit_wdt(void)
{
    SIM->COPC &= ~SIM_COPC_COPW_MASK;
}

/**
 * @brief Refreshes the watchdog timer
 *
 * This function refreshes the watchdog timer by writing a specific sequence of values to the SRVCOP register.
 */
void Refresh_wdt(void)
{
    SIM->SRVCOP = 0x55;
    SIM->SRVCOP = 0xAA;
}
