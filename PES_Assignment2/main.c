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
​ ​*​ ​@file​_name    main.c
​ ​*​ ​@intorduction main file for PES Assignment 2 - LL Lifo and Ciruclar Buffer FIFO
​ ​* This file invokes the testing function for Linked List based LIFO and
​ ​*​ Curcular Buffer based FIFO functions named test_lllifo() and test_cbfifo
​ ​*​ 
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 7​ 2023 
​ ​*​ ​@version​ 4.2 
​ ​* 
​ ​*/

/* Include Files */
#include<stdio.h>                   // include the standard input/output library
#include<stdlib.h>                  // include the standard library
#include<string.h>                  // include the string handling library

#include "test_cbfifo.h"            // include the header file for circular buffer FIFO test
#include "test_lllifo.h"            // include the header file for linked list FIFO test

int main(int argc, char * argv[])   // main function
{
    /* Test linked list FIFO */
    if(test_lllifo() == 1)          
    {   
        printf("\n\n");  
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");      
        printf("::::::::::  LL LIFO All Tests Passed   :::::::::::\n");      
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");  
    }else{
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");      
        printf("::::::::::        Test Failed          :::::::::::\n");       
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");  
    }
    /* Test circular buffer FIFO */
    if(test_cbfifo() == 1)          
    {   
        printf("\n\n");
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");      
        printf("::::::::::  CB FIFO All Tests Passed   :::::::::::\n");      
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");  
    }else{
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");      
        printf("::::::::::       Test Failed           :::::::::::\n");       
        printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");  
    }
// return 0 to indicate the program has executed successfully  
return 0;                       
}