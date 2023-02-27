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
​ ​*​ ​@file​_name    test_lllifo.c
​ ​*​ ​@introduction This file is used to test different linked list based LIFO functions
​ ​*​               File maintains the different algorithm requred for LIFO
​ ​* 
​ ​*​ ​@author​ ​Kiran Jojare
​ ​*​ ​@date​ ​Feb 57 2023 
​ ​*​ ​@version​ ​4.2 
​ ​* 
 * @referense - None
 * 
​ ​*/

#ifndef _TEST_LLLIFO_C_
#define _TEST_LLLIFO_C_

/* Include Files */
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<assert.h>

#include"lllifo.h"              
#include "test_lllifo.h"   

#define MAX_INT_VALUE 0xFFFFFFF 
#define MAX_INT_VALUE_PLUS_1 0x80000000

// function to test linked list LIFO
int test_lllifo()
{
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("::::::::  Testing Linked List LIFO   ::::::::::::: \n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");
    /* ------------------------ Test Case 1 ---------------------------------------------*/
    // This test case creates LIFO with 3 elelmenets and verifies
    // verifies multiple push and pop and checks parallely if length and capacity parameters
    // are verified using assertion statements at proper places
    printf("Test 1 : Create 3 Instances of Capacity into Stack\n");
    lllifo_t *mylifo1 = lllifo_create(3);
    assert(lllifo_capacity(mylifo1)==3);
    assert(lllifo_length(mylifo1)==0); 
    printf("\t\tTest Created 3 empty elements\n"); 

    lllifo_push(mylifo1, "one");
    assert(lllifo_capacity(mylifo1)==3);
    assert(lllifo_length(mylifo1)==1);  
    printf("\t\tTested pushing first element and verified if length is 1 and capacity is 3\n"); 

    lllifo_push(mylifo1, "two");
    assert(lllifo_capacity(mylifo1)==3);
    assert(lllifo_length(mylifo1)==2); 
    printf("\t\tTested pushing second element and verified if length is 2 and capacity is 3\n"); 

    lllifo_push(mylifo1, "three");
    assert(lllifo_capacity(mylifo1)==3);
    assert(lllifo_length(mylifo1)==3); 
    printf("\t\tTested pushing third element and verified if length is 3 and capacity is 3\n"); 

    lllifo_push(mylifo1, "four");
    assert(lllifo_capacity(mylifo1)==4);
    assert(lllifo_length(mylifo1)==4); 
    printf("\t\tTested pushing fourth element and verify if length is 4 and also checked if capacity is increased to 4\n"); 

    lllifo_pop(mylifo1);
    assert(lllifo_capacity(mylifo1)==4);
    assert(lllifo_length(mylifo1)==3); 
    printf("\t\tTested poppping one element and varified if length is 3 and capacity is 4\n"); 
    lllifo_destroy(mylifo1);
    printf("\t\tTested if the lifo is destroyed\n"); 
    printf("\tTest 1 : Test Passed\n");


    /* ------------------------ Test Case 2 ---------------------------------------------*/
    // This test case creates LIFO with 0 elelmenets and verifies
    // if only the template of the lifo is returned and nothing else
    printf("\n\nTest 2 : Create 0 Instances of Capacity into Stack\n");

    lllifo_t *mylifo2 = lllifo_create(0);    
    assert(lllifo_capacity(mylifo2)==0);
    assert(lllifo_length(mylifo2)==0);
    printf("\t\tTested if the lifo is created with one element and verified if length is 0 and capacity is 0\n"); 

    
    lllifo_destroy(mylifo2);
    printf("\t\tTested if the lifo is destroyed\n"); 
    printf("\tTest 2 : Test Passed\n");

    /* ------------------------ Test Case 3 ---------------------------------------------*/
    // This test case creates LIFO with 10 elelmenets and verifies
    // verifies multiple push and pop and checks parallely if length and capacity parameters
    // are verified using assertion statements at proper places
    printf("\n\nTest 2 : Create 10 Instances of Capacity into Stack\n");

    lllifo_t *mylifo3 = lllifo_create(10);    
    assert(lllifo_capacity(mylifo3)==10);
    assert(lllifo_length(mylifo3)==0);   
    printf("\t\tTested if the lifo is created with 10 elements\n"); 
    for(int i=1;i<=5;i++)
    {
        lllifo_push(mylifo3, "Test 3");
        assert(lllifo_capacity(mylifo3)==10);
        assert(lllifo_length(mylifo3)==i);
    }
    assert(lllifo_length(mylifo3)==5);
    printf("\t\tTested pushing 5 elemenets back to back into stack\n"); 

    int count = 5;
    for(int i=0;i<5;i++)
    {
        lllifo_pop(mylifo3);                                // check what value is exactly popped 
        assert(lllifo_capacity(mylifo3)==10);
        assert(lllifo_length(mylifo3)== (--count));
    }
    assert(lllifo_length(mylifo3)==0);
    printf("\t\tTested popping 5 elemenets back to back into stack\n"); 
    
    lllifo_pop(mylifo3);
    assert(lllifo_length(mylifo3)==0);
    assert(lllifo_capacity(mylifo3)==10);
    printf("\t\tTested popping elemenets from empty buffer and verified the length is 0 and capacity is 10\n"); 

    for(int i=1;i<=10;i++)
    {
        lllifo_push(mylifo3, "Test 3");
        assert(lllifo_capacity(mylifo3)==10);
        assert(lllifo_length(mylifo3)==i);
    }
    assert(lllifo_length(mylifo3)==10);
    printf("\t\tTested pushing 10 elemenets back to back into stack\n"); 

    lllifo_push(mylifo3, "Test 3");
    assert(lllifo_capacity(mylifo3)==11);
    assert(lllifo_length(mylifo3)==11);
    printf("\t\tTested pushing 11th elemenet and verified if the length is 11 and capacity is 11\n"); 

    lllifo_destroy(mylifo3);
    printf("\t\tTested if the lifo is destroyed\n"); 
    printf("\tTest 3 : Test Passed\n");


    /* ------------------------ Test Case 4 ---------------------------------------------*/
    // This test case creates LIFO with 20 elelmenets and verifies
    // verifies multiple push and pop and checks parallely if length and capacity parameters
    // are verified using assertion statements at proper places

    printf("\n\nTest 4 : Create 20 Instances of Capacity into Stack\n");
    lllifo_t *mylifo4 = lllifo_create(20);
    assert(lllifo_capacity(mylifo4)==20);
    assert(lllifo_length(mylifo4)==0);   
    //lllifo_push(mylifo4, "Test 4");
    printf("\t\tTested if the lifo is created with 20 elements\n"); 

    for(int i=1;i<=10;i++)
    {
        lllifo_push(mylifo4, "Test 4");
        assert(lllifo_capacity(mylifo4)==20);
        assert(lllifo_length(mylifo4)==i);
    }
    assert(lllifo_length(mylifo4)==10);
    printf("\t\tTested pushing 10 elemenets back to back into stack\n"); 

    int count1 = 10;
    for(int i=0;i<5;i++)
    {
        lllifo_pop(mylifo4);                 
        assert(lllifo_capacity(mylifo4)==20);
        assert(lllifo_length(mylifo4)== (--count1));
    }
    assert(lllifo_length(mylifo4)==5);
    printf("\t\tTested popping 5 elemenets back to back into stack\n"); 

    count1 = 5;
    for(int i=1;i<=15;i++)
    {
        lllifo_push(mylifo4, "Test 4");
        assert(lllifo_capacity(mylifo4)==20);
        assert(lllifo_length(mylifo4)==(++count1));
    }
    assert(lllifo_length(mylifo4)==20);
    printf("\t\tTested pushing 15 elemenets back to back into stack\n"); 


    lllifo_push(mylifo4, "four");
    assert(lllifo_capacity(mylifo4)==21);
    assert(lllifo_length(mylifo4)==21); 
    printf("\t\tPushed 21st element and veryfied if length is 21 and also checked if capacity is increased to 21\n"); 

    lllifo_destroy(mylifo4);
    printf("\t\tTested if the lifo is destroyed\n"); 
    printf("\tTest 4 : Test Passed\n");

   /* ------------------------ Test Case 5 ---------------------------------------------*/
    // This test case verifies if the value inside stack is correctly popped or pushed
    // created lifo of 3 elements. Pusshed strings "first" "Second" and "Third". Popped and 
    // verified if it actually returned the same string values

    printf("\n\nTest 5 : Verify Stack Data using Strings\n");

    lllifo_t *mylifo5 = lllifo_create(3);
    assert(lllifo_capacity(mylifo5)==3);
    assert(lllifo_length(mylifo5)==0); 
    printf("\t\tTested if the lifo is created with 3 elements\n"); 

    // Store "one" "two" and "three" into stack
    lllifo_push(mylifo5, "One");
    assert(lllifo_capacity(mylifo5)==3);
    assert(lllifo_length(mylifo5)==1); 
    printf("\t\tTested pushing \"One \" in stack \n"); 

    lllifo_push(mylifo5, "Two");
    assert(lllifo_capacity(mylifo5)==3);
    assert(lllifo_length(mylifo5)==2); 
    printf("\t\tTested pushing \"Two \" in stack \n"); 

    lllifo_push(mylifo5, "Three");
    assert(lllifo_capacity(mylifo5)==3);
    assert(lllifo_length(mylifo5)==3); 
    printf("\t\tTested pushing \"Three \" in stack \n"); 

    // check if string "three" "two" "one" is actually popped in LIFOs
    char * popped_string = lllifo_pop(mylifo5);
    assert(  (strcmp(popped_string,"three"))  );
    printf("\t\tTested if \"Three \" is popped from stack \n"); 

    popped_string = lllifo_pop(mylifo5);
    assert(  (strcmp(popped_string,"two"))  );
    printf("\t\tTested if \"Two \" is popped from stack \n"); 

    popped_string = lllifo_pop(mylifo5);
    assert(  (strcmp(popped_string,"three"))  );
    printf("\t\tTested if \"one \" is popped from stack \n"); 

    lllifo_destroy(mylifo5);
    printf("\t\tTested if the lifo is destroyed\n"); 
    printf("\tTest 5 : Test Passed\n");

   /* ------------------------ Test Case 6 ---------------------------------------------*/
    // This test case check if the code can implement fifo with MAX_INTEGER capacity
    // i.e 2,147,483,647 instances of emeets will be created
    printf("\nTest 3 : Create 2,147,483,647 (MAX SIGNED INT) instances \n");
    lllifo_t *mylifo6 = lllifo_create(MAX_INT_VALUE);
    assert(lllifo_capacity(mylifo6)==MAX_INT_VALUE);
    assert(lllifo_length(mylifo6)==0); 
    printf("\t\tTested if LIFO is created for 2,147,483,647 elements\n"); 
    lllifo_destroy(mylifo6);
    printf("\t\tTested if the lifo is destroyed\n"); 

    // This test case checks if NULL is returned if tried creating
    // more than 2,147,483,647 cpapacity number of elements
    lllifo_t *mylifo7 =(lllifo_t *)lllifo_create(MAX_INT_VALUE_PLUS_1);
    assert(mylifo7==NULL);
    printf("\t\tTested if LIFO is NULL for creating more than 2,147,483,647 elements\n"); 
    printf("\tTest 5 : Passed\n");
    lllifo_destroy(mylifo7);
    // return 1 if all test are passed
    return 1;

    
}

#endif //_TEST_LLLIFO_C_