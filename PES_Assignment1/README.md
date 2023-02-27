# PES_Assignment_1

**Student Name**     : Kiran Narendra Jojare  
**Section**          : Graduate Student in ECEN 

Code for Assignment 1 for PES ECEN 5813 Spring 2023
This assignment is a refresher for C basics specially C bitwise operators and Bitwise Manupulation.

# Introduction
The asignment check the functions related to bitmanipulation and verify them via seperate test functions. The test function returns string to indicate weather they pass or fail.

Usage : 
```
$ ./make clean
$ ./make all
$ ./main

```
Note : The assignment also covers the extra credit function to imlement and test `rotate_right()` function

# Code Organisation
* `main.c` : Main function to call test function and to verify weather test cases are passed or not

* `main.h` : File containing the function definations

* `test.h` : File containing the individual test functions to test functions in main.h


# Function Details

* `nt32_t binstr_to_uint(const char *str)`

This function takes a string of binary digits as input, with the prefix "0b". It converts the binary 
string to an unsigned 32-bit integer and returns the result. If the input string is not a valid binary  string or input is NULL or the string is too long, the function returns an error value of 0xFFFFFFFF 
 ``
 
 * `int int_to_binstr(char *str, size_t size, int32_t num, uint8_t nbits)
`

This function converts the input integer to a binary string with a leading '0b' and a trailing null character.  The caller must ensure that the buffer passed in is large enough to hold the binary string. If the number of bits specified is less than the number of bits required to represent the integer, the most significant bits are truncated. If the number of bits specified is greater than 32, the function returns -1.

* `uint32_t hexstr_to_uint(const char *str) {
`

This function expects the input string to be in the format "0x[0-9A-Fa-f]+" and will only convert the first 8 digits of the string.

* `uint32_t twiggle_except_bit(uint32_t input, int bit, operation_t operation)
`

This function is used to perform operations on a specific bit in a 32-bit unsigned integer.  The function takes three parameters as inputs Based on the value of the 'operation' parameter, 
the function will set, clear, or toggle the specified bit in the 'input' variable. 
The function returns the result of the operation, or 0xFFFFFFFF if an error is detected (bit out of range or invalid operation).

* `uint32_t grab_four_bits(uint32_t input, int start_bit)
`


This function function to extract a 4-bit sequence from a 32-bit unsigned integer.

* `char *hexdump(char *str, size_t size, const void *loc, size_t nbytes) {
`

This function creates a hexdump of a given memory location. It takes in 4 parameters:  a string buffer (str) to store the hexdump, the size of the string buffer, the memory  location to be hex dumped, and the number of bytes to be hex dumped from the memory location.  It returns the hexdump string, or an empty string if an error is detected, such as if the str parameter is NULL or if the nbytes parameter exceeds 65535.

* `uint8_t rotate_right(uint8_t input, uint8_t places)
`

Function to rotate a given 8-bit input right by a specified number of places

# Any extent Bugs

No extent bug to be reported. Code works fine for all the test cases given as per assignment requirements.
