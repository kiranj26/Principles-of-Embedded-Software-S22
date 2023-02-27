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
​ ​*​ ​@file​ main.c
​ ​*​ ​@brief​ Main file for PES Assignment 1 - Logical Bit Operation and Manupulation
​ ​* 
​ ​*​  
​ ​*​  
​ ​* 
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Jan ​9​ 2023 
​ ​*​ ​@version​ ​2.0 
​ ​* 
​ ​*/

#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

/* 
 * Private header files
 */
#include"main.h"
#include"test.h"

int main()
{
    printf("::::  Testing Binary to Uint Function  ::::\n");
    int result7= test_binstr_to_uint();
    if (result7 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");

    printf("::::  Testing int to binary Function    ::::\n");
    int result5= test_int_to_binstr();
    if (result5 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");

    printf("\n::::    Testing Hex to Binary         ::::\n");
    int result6 = test_hexstr_to_uint();
    if (result6 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");
    
    printf("\n::::   Testing Twiggle Except Bit     ::::\n");
    int result4 = test_twiggle_except_bit();
    if (result4 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");
    
    printf("\n::::      Testing Grab Four Biits     ::::\n");
    int result1 = test_grab_four_bits();
    if (result1 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");

    printf("\n::::          Testing Hex Dump        ::::\n");
    int result2 = test_hexdump();
    if (result2 == 0) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");

    printf("\n::::  Testing Rotate Left Function    ::::\n");
    //test_rotate_right();
    int result3 = test_rotate_right();
    if (result3 == 1) printf("\tAll test cases passed!\n");
    else printf("Test case failed!\n");
}