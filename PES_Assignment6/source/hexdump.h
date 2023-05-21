/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file hexdump.h
 * @brief Header file for hexdump function
 *
 * This header file defines the function prototype for hexdump function.
 *
 * @author Kiran Jojare
 * @date   April 9 2022
 * @version 1.0
 *
 * @reference
 * none
 */

#ifndef _HEXDUMP_H_
#define _HEXDUMP_H_

/**
 * @brief Prints hexadecimal dump of memory region
 *
 * This function prints the hexadecimal dump of a memory region starting from a given start address
 * and for a given length. The dump is printed in rows of 8 bytes, with each byte separated by a space.
 * Each row starts with the address of the first byte in the row.
 *
 * @param startAddress Pointer to the start of the memory region to dump
 * @param length Length of the memory region to dump
 *
 * @return none
 */
void hexdump(char *startAddress, int length);

#endif /* _HEXDUMP_H_ */
