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
​ ​*​ ​@file​ main.h
​ ​*​ ​@brief​ Header file for PES Assignment 1 - Logical Bit Operation and Manupulation
​ ​* 
​ ​*​ The header file contains the function definations for the required functions
​ ​* Note - Used some test inputs from Viraj Patel to check robustness
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Jan ​9​ 2023 
​ ​*​ ​@version​ ​1.0 
​ ​* 
​ ​*/

#ifndef MAIN_H
#define MAIN_H

#include<string.h>

/* 
 * Global Data
*/

typedef enum {
    CLEAR,
    SET,
    TOGGLE
} operation_t;

/*
 * Function Delcarations
 */

/*
* binstr_to_uint - function to convert binary string to unsigned integer
* -----------------
* This function takes a string of binary digits as input, with the prefix "0b". It converts the binary 
* string to an unsigned 32-bit integer and returns the result. If the input string is not a valid binary 
* string or input is NULL or the string is too long, the function returns an error value of 0xFFFFFFFF 
* 
* num: an unsigned 32-bit integer representing the number whose number of bits are to be calculated
*
* returns: an integer representing the number of bits in the input number
*/
int32_t binstr_to_uint(const char *str)
{
   // data initialisation
    int32_t error;
    int32_t result = 0;
    /* check if the input string is NULL */
    if (str == NULL)
    {
        return 0xFFFFFFFF;
    }
    /* check if the input string is in the correct format of "0bXXXXXX" */    
    if (!(str[0] == '0' && str[1] =='b'))
    {
        return 0xFFFFFFFF;
    }
    /* eliminating the "0b" prefix to get the actual binary representation */
    str = str + 2;
    /* variable to keep track of the number of characters in the input string */
    int count = 0;
    /* loop through the input string */
    while(*str)
    {
        count ++;
        /* check if the input string is too long */
        if(count > 31)
        {
            return 0xFFFFFFFF;
        }        
        /* check if the current character is a '0' or '1' */
        if(*str == '0' || *str == '1')
        {
            error = 0;
        }else
        {
            error = -1;
            return 0xFFFFFFFF;
        }
        /* if the current character is '1', add 1 to the result */
        if(*str == '1')
        {
            result = (result << 1) | 1;
        }
        /* if the current character is '0', don't add anything to the result */
        if(*str == '0')
        {
            result = result << 1;
        }
        str++;
    } 
    /* check if an error occurred */
    if (error == -1)
    {
        result = 0xFFFFFFFF;
    }
    /* return the result */
    return result;
}


/*
* Function: nb
* -----------------
* This function takes an unsigned 32-bit integer 'num' as input and returns the number of bits it has. 
* inputs  
* num: an unsigned 32-bit integer representing the number whose number of bits are to be calculated
*
* returns: an integer representing the number of bits in the input number
*/
int nb(uint32_t num){
    int pos = 0;
    /* check if the number is greater than or equal to 0 */
    if(num >= 0){
    /* while the number is not equal to 0 */
    while(num != 0){
        pos++;
        num = num >> 1;
    }
    }
    /* return the number of bits */
    return pos;
}

/**
 * int_to_binstr - Convert an integer to a binary string
 * -------------
 * This function converts the input integer to a binary string with a leading '0b' and a trailing null character. 
 * The caller must ensure that the buffer passed in is large enough to hold the binary string.
 * If the number of bits specified is less than the number of bits required to represent the integer, the most significant bits are truncated.
 * If the number of bits specified is greater than 32, the function returns -1.
 * 
 * str: Pointer to the buffer where the binary string will be stored
 * size: Size of the buffer where the binary string will be stored
 * num: Integer to be converted to binary string
 * nbits: Number of bits to represent the integer
 *
 * Returns: the number of characters in the binary string, -1 on failure
 */
int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
{
    /* Check if the string is NULL and throw -1 */
     if(str == NULL){
        return -1;
    }
    /* Check if no is negative*/
    if(num < 0){
        num += (1 << nbits);
    }
    /* Check if the nbits is less that bits required to represent num and check if size is less than (nbits +3)*/
    if((nbits < nb(num))||(size < nbits + 3)){
        *str = '\0';
        return -1;
    }
    /* main logic*/
    if(nbits > 32){
        /*If nbits is greater than 31 throw null string */
        *str = '\0';
        return -1;
    }
    else{
    int i;
    str[0] = '0';
    str[1] = 'b';
    for(i = nbits+1;i >= 2;i--){
       if((num & 1) == 1){
            str[i] = '1';
        }
        else{
            str[i] = '0';
        }
        num = num >> 1;
      }
    str[nbits + 2] = '\0';
    }
    return nbits + 2;
}

/**
 * hexstr_to_uint - converts a hexadecimal string to an unsigned integer
 * ---------------
 * This function expects the input string to be in the format "0x[0-9A-Fa-f]+"
 * and will only convert the first 8 digits of the string.
 * @tr: the string to convert
 * 
 * Returns the converted integer, or -1 if the input is invalid
 * 
 */
uint32_t hexstr_to_uint(const char *str) {
    uint32_t res = 0;
    uint32_t count = 0;
    /* if input string is null, return -1*/ 
    if (str == NULL) {
        return -1;
    }
    /* check if the input string starts with "0x" or "0X" */
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        // move pointer to the first character after "0x"
        str = &str[2];
        // iterate through each character of the string
        while (*str) {
            if (*str == '0') {
                res = (res << 4) | 0b0000; // left shift the result by 4 bits and add 0 in the last 4 bits
            }
            else if (*str == '1') {
                res = (res << 4) | 0b0001; // left shift the result by 4 bits and add 1 in the last 4 bits
            }
            else if (*str == '2') {
                res = (res << 4) | 0b0010; // left shift the result by 4 bits and add 2 in the last 4 bits
            }
            else if (*str == '3') {
                res = (res << 4) | 0b0011; // left shift the result by 4 bits and add 3 in the last 4 bits
            }
            else if (*str == '4') {
                res = (res << 4) | 0b0100; // left shift the result by 4 bits and add 4 in the last 4 bits
            }
            else if (*str == '5') {
                res = (res << 4) | 0b0101; // left shift the result by 4 bits and add 5 in the last 4 bits
            }
            else if (*str == '6') {
                res = (res << 4) | 0b0110; // left shift the result by 4 bits and add 6 in the last 4 bits
            }
            else if (*str == '7') {
                res = (res << 4) | 0b0111; // left shift the result by 4 bits and add 7 in the last 4 bits
            }
            else if (*str == '8') {
                res = (res << 4) | 0b1000; // left shift the result by 4 bits and add 8 in the last 4 bits
            }
            else if (*str == '9') {
                res = (res << 4) | 0b1001; // left shift the result by 4 bits and add 9 in the last 4 bits
            }
            else if (*str == 'a' || *str == 'A') { 
                res = (res << 4) | 0b1010; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else if (*str == 'b' || *str == 'B') {
                res = (res << 4) | 0b1011; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else if (*str == 'c' || *str == 'C') {
                res = (res << 4) | 0b1100; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else if (*str == 'd' || *str == 'D') {
                res = (res << 4) | 0b1101; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else if (*str == 'e' || *str == 'E') {
                res = (res << 4) | 0b1110; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else if (*str == 'f' || *str == 'F') {
                res = (res << 4) | 0b1111; // left shift the result by 4 bits and add 10 in the last 4 bits
            }
            else {
                return -1;
            }

            str++;
            count = -(~count);
            if (count > 8) {
                return -1;
            } 
        }
        return res;
    }
    else {
        return -1;
    }
}

/**
* twiggle_except_bit - function to perform operations on a specific bit in a 32-bit unsigned integer
* ------------------
* This function is used to perform operations on a specific bit in a 32-bit unsigned integer. 
* The function takes three parameters as inputs Based on the value of the 'operation' parameter, 
* the function will set, clear, or toggle the specified bit in the 'input' variable. 
* The function returns the result of the operation, or 0xFFFFFFFF if an error is detected (bit out of 
* range or invalid operation).
* 
* input: 32-bit unsigned integer on which the operation is to be performed
* bit: the specific bit on which the operation is to be performed (0-31)
* operation: the operation to be performed (SET, CLEAR, TOGGLE)
* Returns: the result of the operation, or 0xFFFFFFFF if an error is detected (bit out of range or invalid operation)
*/
uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation)
{
    uint32_t result = 0xFFFFFFFF;
    /* Check if bit is above 31 bit else return -1 */
    if (bit>31 || bit<0)
    {
        return 0xFFFFFFFF;
    }else
    {
        /* If operation is SET */
        if(operation == SET)
        {
            /* Check the value of bit if its 0 or 1*/
            
            if (((input >> bit) & 1) == 1)
            {
                /*If bit is 1 return FFFFFFFF*/
                result = 0xFFFFFFFF;
            }else
            {
                /* if bit is 0, take mask and AND it to the inverted mask */
                result = 0xFFFFFFFF & (~(1 << bit));
            }
        }
        else if(operation == CLEAR)
        {
            /* Clear everythig except bit at bit position */
            result = input & (1 << bit);
        }
        else if(operation == TOGGLE)
        {
            /* Toggle everythig except bit at bit position */
            result = ~(input ^ (1 << bit));
        }
        else{
            /* if no SET,CLEAR or TOGGLE operation return -1*/
            return 0xFFFFFFFF;
        }       
    }
    return result;
}
/**
 * grab_four_bits - function to extract a 4-bit sequence from a 32-bit unsigned integer
 * ---------------
 * input: 32-bit unsigned integer from which the 4-bit sequence is to be extracted
 * start_bit: the starting bit position of the 4-bit sequence (0-28)
 *
 * Returns: the extracted 4-bit sequence as a 32-bit unsigned integer, or 0xFFFFFFFF if an error is detected (start_bit out of range)
 */

uint32_t grab_four_bits(uint32_t input, int start_bit)
{
    if(start_bit > 28 || start_bit < 0)
    {
        return 0xFFFFFFFF;
    }else
    {
        // Shift input right by start_bit
        input = input >> start_bit;
        // Mask input to only keep the last 4 bits
        input = input & 15;
    }
return input;
}
/**
 * hexdump - function to create a hexdump of a given memory location
 * ------------
 * This function creates a hexdump of a given memory location. It takes in 4 parameters: 
 * a string buffer (str) to store the hexdump, the size of the string buffer, the memory 
 * location to be hex dumped, and the number of bytes to be hex dumped from the memory location. 
 * It returns the hexdump string, or an empty string if an error is detected, such as if the str parameter 
 * is NULL or if the nbytes parameter exceeds 65535.
 * 
 * str: string buffer to store the hexdump
 * size: size of the string buffer
 * loc: memory location to be hex dumped
 * nbytes: number of bytes to be hex dumped from the memory location
 *
 * Returns: the hexdump string, or an empty string if an error is detected (str is NULL, nbytes > 65535)
 */
char *hexdump(char *str, size_t size, const void *loc, size_t nbytes) {
    /* if string is NULL return empty string */
    if (str == NULL)
    {
        *str = '\0';
        return str;   
    }
    char *p = str;
    const unsigned char *data = loc;
    char hex[] = "0123456789abcdef";
    /* check for erroors */
    if (nbytes > 65535) {
        *str = '\0';
        return str;
    }
    /* loops through mem location */
    while (nbytes) {
        int i;
        int n = nbytes > 8 ? 8 : nbytes;
        int offset = data - (unsigned char *)loc;
        int upper_offset, lower_offset;

        /* Append the offset to the hexdump string */
        *p++ = '0';
        *p++='x';

        upper_offset = (offset >> 12) & 0xF;
        *p++ = hex[upper_offset];
        upper_offset = (offset >> 8) & 0xF;
        *p++ = hex[upper_offset];
        upper_offset = (offset >> 4) & 0xF;
        *p++ = hex[upper_offset];
        lower_offset = offset & 0xF;
        *p++ = hex[lower_offset];
        /* Add spaces after offset */
        *p++ = ' ';
        *p++ = ' ';
        /* Append the hex values of the data to the string */
        for (i = 0; i < 8; i++) {
            if (i < n) {
                upper_offset = (*data >> 4) & 0xF;
                *p++ = hex[upper_offset];
                lower_offset = *data & 0xF;
                *p++ = hex[lower_offset];
                *p++ = ' ';
                data++;
            } else {
                /* Three space added */
                *p++ = ' ';
                *p++ = ' ';
                *p++ = ' ';
            }
        }
        *p++ = '\n';

        nbytes -= n;
    }

    *p = '\0';
    return str;
}
/**
 * rotate_right - function to rotate a given 8-bit input right by a specified number of places
 * -------------
 * input: 8-bit input to be rotated
 * places: number of places to rotate the input
 *
 * Returns: the rotated input
 */

uint8_t rotate_right(uint8_t input, uint8_t places)
{
    uint8_t cnt = 1;
    /* Loop to rotate the input for the specified number of places */
    while(cnt<=places)
    {
        /* Perform the right rotate operation */
        input = (input >> 1) | ((input & 1) << 7);
        cnt = -(~cnt);
    }
    return input;
}
#endif
