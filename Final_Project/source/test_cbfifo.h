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
​ ​*​ ​@file​ test_cbfifo.h
​ ​*​ ​@brief​ Header file for function declarations of different functions used
​ ​*​        test implementation for CBFIFO logic
​ ​*
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 4​ 2023
​ ​*​ ​@version​ ​1.0
​ ​*
​ ​*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbfifo.h"
#include "uart.h"
#include <assert.h>

/**
 * @brief Test the circular buffer functionality
 *
 * This function tests the various functionalities of the circular buffer such as
 * initializing, adding, removing and checking for full and empty buffer.
 *
 * @return 0
 */

void test_cbfifo();
