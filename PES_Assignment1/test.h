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
​ ​*​ ​@file​ test.h
​ ​*​ ​@brief​ Test file for PES Assignment 1 - Logical Bit Operation and Manupulation
​ ​* 
​ ​*​ The file for testing function inside main.h with multiple inputs to test robustness
​ ​* 
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Jan ​9​ 2023 
​ ​*​ ​@version​ ​1.0 
​ ​* 
​ ​*/

#ifndef TEST_H
#define TEST_H

#define SIZE 1024


#include <string.h>

/* test_binstr_to_uint
* ---------------------
* This test function, test_binstr_to_uint(), tests the binstr_to_uint() function by calling it with 
* various inputs and using the assert macro to check if the returned value is as expected. The test 
* cases include valid binary strings, invalid binary strings, strings that are too long, and a NULL input. 
* If all the assert statements pass, the program will print "All test cases passed!" and return 0. 
* If any of the assert statements fail, the program will stop executing and report the failure.
*/

uint32_t test_binstr_to_uint(void)
{
    int passed =1;
    // test Case 1 String is NULL
    char * str = NULL;
    uint32_t result1 = binstr_to_uint(str);
    if (result1 != -1) {
        passed = 0;
    }
    // Test Case 2 
    char * str2 = "0b00";
    uint32_t result2 = binstr_to_uint(str2);
    if (result2 != 0) {
        passed = 0;
    }

    char * str3 = "0b0510";
    uint32_t result3 = binstr_to_uint(str3);
    if (result3 != -1) {
        passed = 0;
    }
    
    char * str4 = "0b1111";
    uint32_t result4 = binstr_to_uint(str4);
    if (result4 != 15) {
        passed = 0;
    }

    char * str8 = "0x010101";
    uint32_t result5 = binstr_to_uint(str8);
    if (result5 != -1) {
        passed = 0;
    }

    char * str5 = "0b1111111111111111";
    uint32_t result6 = binstr_to_uint(str5);
    if (result6 != 65535) {
        passed = 0;
    }

    char * str7 = "0b1111111111111111111111111111111";
    uint32_t result7 = binstr_to_uint(str7);
    if (result7 != 2147483647) {
        passed = 0;
    }

    char * str6 = "0b111111111111111111111111111111111";
    uint32_t result8 = binstr_to_uint(str6);
    if (result8 != -1) {
        passed = 0;
    }
    return passed;
}

/* Function to test int_to_binstr */
int test_int_to_binstr(void)
{
    int passed=1;
    //printf("\n:::: Testing Integer To Binary String Function ::::\n");
    char str[SIZE];
    // Given Test Cases 
    int result = int_to_binstr(str,15,18,8);
    if (result != 10) {
        passed = 0;
    }

    result = int_to_binstr(str,15,-1,4);
    if (result != 6) {
        passed = 0;
    }

    result = int_to_binstr(str,15,-3,8);
    if (result != 10) {
        passed = 0;
    }

    // wrong output
    result = int_to_binstr(str,15,-18,4);
    if (result != -1) {
        passed = 0;
    }

    result = int_to_binstr(str,15,128,8);
    if (result != 10) {
        passed = 0;
    }

    result = int_to_binstr(str,15,-127,8);
    if (result != 10) {
        passed = 0;
    }

    result = int_to_binstr(NULL,22,65400,16);       //case where input is NULL
    if (result != -1) {
        passed = 0;
    }

    result = int_to_binstr(str,3,310,0);            //case where nbits is 0
    if (result != -1) {
        passed = 0;
    }

    result = int_to_binstr(str,40,310,8);           //case where num is greater than 2 power nbits
    if (result != -1) {
        passed = 0;
    }

    result = int_to_binstr(str,40,310,33);          //case where nbits is greater than 33
    if (result != -1) {
        passed = 0;
    }

    result = int_to_binstr(str,259,4,255);          //extreme case for uint8_t input
    if (result != -1) {
        passed = 0;
    }
    return passed;
}
/* Function to test hexstr_to_uint */

int test_hexstr_to_uint(void)
{
    int passed  = 1;
    uint32_t result = hexstr_to_uint("0xSFT1");
    if (result != -1) {
        passed = 0;
    } 

    result = hexstr_to_uint("0X12");
    if (result != 18) {
        passed = 0;
    }
    result = hexstr_to_uint("0x0012");
    if (result != 18) {
        passed = 0;
    }

    result = hexstr_to_uint("0xfF78");
    if (result != 65400) {
        passed = 0;
    }

    result = hexstr_to_uint("0X0136");
    if (result != 310) {
        passed = 0;
    }

    result = hexstr_to_uint("0x00000000");
    if (result != 0) {
        passed = 0;
    }
    result = hexstr_to_uint("0x8FFFFFF");
    if (result != 150994943) {
        passed = 0;
    }
return passed;
}
/* Function to test twiggle_except_bit */

int test_twiggle_except_bit(void)
{
    int passed =1;
    // given test cases
    uint32_t result = twiggle_except_bit(0,0,SET);
    if (result != 0xfffffffe) {
        passed = 0;
    }

    result = twiggle_except_bit(0,3,SET);
    if (result != 0xfffffff7) {
        passed = 0;
    }

    result = twiggle_except_bit(0x7337,5,TOGGLE);
    if (result != 0xffff8ce8) {
        passed = 0;
    }

    // Additional test Cases
    result = twiggle_except_bit(0,31,SET);
    if (result != 0x7fffffff) {
        passed = 0;
    }

    // n = 1 and bit =1 answer shoudl be 4294967292
    result = twiggle_except_bit(1,1,TOGGLE);
    if (result != 0xfffffffc) {
        passed = 0;
    }

    result = twiggle_except_bit(147483647,31,CLEAR);
    if (result != 0x0) {
        passed = 0;
    }

    // The number 4294967295 in 32 bits has all bits set.  When we toggle all bits except last bit, we get 1.
    result = twiggle_except_bit(4294967295,0,TOGGLE);
    if (result != 0x1) {
        passed = 0;
    }

    // The number 4294967295 in 32 bits has all bits set.  When we toggle all bits except last bit, we get 1.
    result = twiggle_except_bit(10,2,SET);
    if (result != 0xfffffffb) {
        passed = 0;
    }
    return passed;
}
/* Function to test grab_four_bits */

int test_grab_four_bits() {
    int passed = 1;
    uint32_t input = 0x12345678;

    // Test 1: Check if function returns -1 for invalid start_bit
    uint32_t result = grab_four_bits(input, 30);
    if (result != -1) {
        passed = 0;
    }

    // Test 2: Check if function returns -1 for negative start_bit
    result = grab_four_bits(input, -1);
    if (result != -1) {
        passed = 0;
    }

    // Test 3: Check if function handles input of 0 correctly
    result = grab_four_bits(0, 0);
    if (result != 0) {
        passed = 0;
    }
    result = grab_four_bits(0x7337,6);
    if (result != 12) {
        passed = 0;
    }
    result = grab_four_bits(0x7337,7);
    if (result != 6) {
        passed = 0;
    }
    // 1111000011110000
    result = grab_four_bits(61680,12);
    if (result != 15) {
        passed = 0;
    }

    // 11110000111100001111000011110000
    result = grab_four_bits(4042322160,28);
    if (result != 15) {
        passed = 0;
    }

    result = grab_four_bits(-1,28);
    if (result != 15) {
        passed = 0;
    }
    return passed;
}

uint32_t test_hexdump(){
char *test1,*test2,*test3,*test4,*test5,*test6;
    char str1[1024];
    char str2[1024];
    char str3[1024];
    char str4[1024];
    char str5[1024];

    const char *buf1= \
        "To achieve great things, two things are needed:\n" \
        "a plan, and not quite enough time.";
    uint8_t buf2[] = {0,1,2,3,4,5,6,7,8,9,10,
                    11,12,13,14,15,16,17,18,19,20,
                    21,22,23,24,25,26,27,28,29,30,
                    31,32,33,34,35,36,37,38,39,40,
                    41,42,43,44,45,46,47,48,49,50,
                    51,52};
    const char *buf3= \
        "To achieve great things, two things are needed:\n" \
        "a plan, and not quite enough tim";

    //Positive cases
    test1 = hexdump(str1,1024,buf1,16);                     //case to print only single line
    //printf("String returned : \n%s\n",test1);
    test2 = hexdump(str2,1024,buf1,17);                     //case to print till 1 byte after 16
    //printf("String returned : \n%s\n",test2);

    test3 = hexdump(str3,1024,buf2,32);                     //case to print exactly 2 lines
    //printf("String returned : \n%s\n",test3);

    test4 = hexdump(str4,1024,buf2,33);                     //case to print one byte after 2 lines
    //printf("String returned : \n%s\n",test4);

    test5 = hexdump(str5,sizeof(str5),buf3,strlen(buf3)+1); //case to print exactly 5 lines when I remove the last 2 characters
    //printf("String returned : \n%s\n",test5);


    //Negative cases
    test6 = hexdump(str1,22,buf1,strlen(buf1)+1);              //case where str size is less
    //printf("String returned : \n%s\n",test6);


    if((test1[0] == '\0')&&(test2[0] != '\0')&&(test3[0] != '\0')&&
       (test4[0] != '\0')&&(test5[0] != '\0')&&(test6[0] == '\0')){
        return 1;
    }
    else{
        return 0;
    }
}

/* This test function test_rotate_right(), tests the rotate_right() function by calling it with various inputs, 
* and comparing the returned value to the expected result. The test cases include rotating by different number of places, 
* rotating by 0 places, and also negative test cases like rotating by more than 8 places. If all the test cases pass, the 
* function will return 0, otherwise it will return 1. In the main function, the result of the test function is checked and 
* a message is displayed to indicate whether the test passed or failed. The return value of the main function is the same 
* as the return value of the test function, so that it can be used to check the success or failure of the test cases.
*/
int test_rotate_right() {
    int success= 1;
    uint8_t result = rotate_right(5, 1);
    if(result != 130) {success =0;}

    result = rotate_right(5, 2);
    if(result != 65) {success =0;}

    result = rotate_right(5, 7);
    if(result != 10) {success =0;}

    result = rotate_right(5, 8);
    if(result != 5) {success =0;}

    result = rotate_right(255, 0);
    if(result != 255) {success =0;}

    result = rotate_right(5, 12);
    if(result != 80) {success =0;}

    return success;
}

#endif