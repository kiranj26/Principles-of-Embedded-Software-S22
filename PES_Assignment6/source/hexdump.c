/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Kiran Jojare and the University of Colorado are not liable for
* any misuse of this material.
*
*****************************************************************************/

/**
* @file   hexdump.c
* @brief  File conataining the functions required for hexdump
*
* The hexdump function takes a starting address and length as input and prints
* the hex dump of the memory region starting at that address. It prints the memory
* address of each line and the hex values of the bytes in that line.
*
* @author Kiran Jojare
* @date   April 9 2023
* @version 1.0
*
* @reference
* Hexdump using C idea is incorporated from following repo
* https://gist.github.com/domnikl/af00cc154e3da1c5d965
*
* Code has been modified according to our requirements
*
*/

#include <stdio.h>
#include "hexdump.h"

#define BYTES_PER_LINE 	7     				 	// constant for number of bytes to print per line
#define MSB_TWO_BYTE(x) (((x)>>16)&0xFFFF)   	// macro to get most significant two bytes of a 4-byte word
#define LSB_TWO_BYTE(x) ((x)&0xFFFF)         	// macro to get least significant two bytes of a 4-byte word

void hexdump(char *start_add, int length)
{
	// initialize starting address of the memory region being printed and the end address of the memory region being printed
	int start = 0;
	char *end_address = 0;

	printf("\n\r");

	// convert the starting address to an integer and print in hex format
	start = (int)start_add;
	printf("%04X_%04X", MSB_TWO_BYTE(start), LSB_TWO_BYTE(start));

	// loop over each byte in the memory region being printed
	for (int byte = 0; byte < length; byte++)
	{
		// if we've reached the end of a line, print a newline and the starting address of the next line
		if (!(byte & BYTES_PER_LINE) && byte != 0)
		{
			printf("\n\r");
			end_address = start_add + byte;     // calculate the end address of the current line
			start = (int)end_address;           // convert the end address to an integer
			printf("%04X_%04X", MSB_TWO_BYTE(start), LSB_TWO_BYTE(start));  // print the starting address of the next line
		}

		// print the current byte in hex format
		printf(" %02X", *(start_add + byte));
	}

	printf("\n\r");   							// print a newline at the end of the output
}
