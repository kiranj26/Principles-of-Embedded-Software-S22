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
​ ​*​ ​@file​ test_cbfifo.c
​ ​*​ ​@brief​ Main file for implementing functions ot test various implementation and
​ ​*        different courner cases for logic implemented in cbfifo.c file
 *
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 4​ 2023 
​ ​*​ ​@version​ ​1.0 
​ ​* 
​ ​*/

#ifndef _TEST_CBFIFO_C_
#define _TEST_CBFIFO_C_

/* Include Files */
#include<stdio.h>
#include<assert.h>
#include<string.h>

#include "cbfifo.h"
#include "test_cbfifo.h"

// main function for testing the circular buffer FIFO
int test_cbfifo()
{
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("::::::::  Testing Circular Buffer FIFO   :::::::::\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n");

    printf("\nTest 1 : Multiple Enqueue and Dequeue on Queue\t\n");
    /* ------------------------ Test Case 1 ---------------------------------------------*/
    // Test 1 : Multiple Enqueue and Dequeue
    // Test check sthe initial length of the buffer. Then enqueues 128 bytes from an array of char into the buffer.
    // Test dequeues 64 bytes followed by enqueue of 256 and expects at the end if 192 bytes are avaialble in the buffer
    int i;  
    char data1[256];
    char data_out1[256];
    printf("\t\tTest case checked initial length and capacity as 0 and 256.\n");
    // Check if the initial length of the FIFO is 0 and its capacity is 256
    assert(cbfifo_length() == 0);
    assert(cbfifo_capacity() == 256);

    printf("\t\tTested if it enqueued 128 bytes and expects function to return the same.\n");
    // Enqueue 128 bytes into the FIFO
    for (i = 0; i < 128; i++) {
        data1[i] = (char) i;
    }
    assert(cbfifo_enqueue(data1, 128) == 128);
    assert(cbfifo_length() == 128);

    printf("\t\tTested if dequeud 64 bytes and expectes function to return the same.\n");
    // Dequeue 64 bytes from the FIFO
    assert(cbfifo_dequeue(data_out1, 64) == 64);
    assert(cbfifo_length() == 64);

    printf("\t\tTested again if enqueued 128 bytes and expectes function to return the same with length set t 192.\n");
    // Enqueue 128 more bytes into the FIFO
    for (i = 0; i < 128; i++) {
        data1[i] = (char) i;
    }
    assert(cbfifo_enqueue(data1, 128) == 128);
    assert(cbfifo_length() == 192);

    printf("\t\tTested after dequed return remainning bytes (128 + 64 = 192 Bytes).\n");
    // Dequeue all bytes from the FIFO
    assert(cbfifo_dequeue(data_out1, 192) == 192);
    assert(cbfifo_length() == 0);
    printf("\t\tTest returns 192 Bytes");

    printf("\n\tTest 1 : Test Passed\n");

    /* ------------------------ Test Case 2 ---------------------------------------------*/
    // Test 1 : Circular Buffer Overflow 1
    // Test check sthe initial length of the buffer. Then enqueues 256 bytes from an array of char into the buffer.
    // Test dequeues 128 bytes followed by enqueue of 256 and expects at the end if 256 - 128= 128 bytes are avaialble 
    // in the buffer. In short this test case checks overflow and checks if only available bytes are retrieved or not

    printf("\nTest 2 : Circular Buffer Overflow 1 \t\n");
    int i2;
    char data2[256];
    char data_out2[256];

    printf("\t\tTest case check initial length and capacity as 0 and 256.\n");
    assert(cbfifo_length() == 0);
    assert(cbfifo_capacity() == 256);

    printf("\t\tTested enqueueing 256 bytes and expectes function to return the same.\n");
    // Enqueue 256 bytes into the FIFO
    for (i2 = 0; i2 < 256; i2++) {
        data2[i2] = (char) i2;
    }
    assert(cbfifo_enqueue(data2, 256) == 256);
    assert(cbfifo_length() == 256);

    printf("\t\tTested dequeueing 128 bytes and expectes function to return the same.\n");
    // Dequeue 128 bytes from the FIFO
    assert(cbfifo_dequeue(data_out2, 128) == 128);
    assert(cbfifo_length() == 128);

    printf("\t\tTested enqueueing 256 bytes and but expect function to enqueue only (256-128 = 128 Bytes).\n");
    // Enqueue 256 more bytes into the FIFO
    for (i2 = 0; i2 < 256; i2++) {
        data2[i2] = (char) i2;
    }
    assert(cbfifo_enqueue(data2, 256) == 128);
    assert(cbfifo_length() == 256);

    printf("\t\tTested dequeueing all 256 bytes and expectes function to return the same.\n");
    // Dequeue 256 bytes from the FIFO
    assert(cbfifo_dequeue(data_out2, 256) == 256);
    assert(cbfifo_length() == 0);

    printf("\tTest 2 : Test Passed\n");
    /* ------------------------ Test Case 3 ---------------------------------------------*/
    // Test 3 : Enqueue & Dequeue on NULL
    // This test checks if enqueue and dequeue returns0 if passed NULL
    printf("\nTest 3 : Passing NULL Buffer \t\t");
    assert(cbfifo_enqueue(NULL, 100) == 0);
    assert(cbfifo_dequeue(NULL, 100) == 0);  
    printf("\n\t\tTested dequeue and dequeue on NULL returns 0.\n");

    printf("\tTest 3 : Test Passed\n");

    /* ------------------------ Test Case 4 ---------------------------------------------*/
    // Test 4 : Circular Buffer Overflow 2
    // This test checks lenitial length and capacity. Test enqueues 128 bytes first.
    // Then test try dequeueing 200 bytes but it shoud return only available bytes(128 Bytes) 
    // not 200 bytes.  
    printf("\nTest 4 : Circular Buffer Overflow 2\t\n");

    printf("\t\tTest case check initial length and capacity as 0 and 256.\n");
    assert(cbfifo_length() == 0);
    assert(cbfifo_capacity() == 256);

    printf("\t\tTested enqueueing 128 bytes initially.\n");
    int i4;
    char data4[256];
    char data_out4[256];
    // Enqueue 128 bytes into the FIFO
    for (i4 = 0; i4 < 128; i4++) {
        data4[i4] = (char) i4;
    }
    assert(cbfifo_enqueue(data4, 128) == 128);
    assert(cbfifo_length() == 128);

    // Dequeue 200 bytes from the FIFO
    assert(cbfifo_dequeue(data_out4, 200) == 128);
    assert(cbfifo_length() == 0);
    printf("\t\tTested dequeuing 200 bytes. \n\t\tReturned whatever available i.e 128 Bytes and not 200 Bytes.\n");
    printf("\tTest 4 : Test Passed\n");

    /* ------------------------ Test Case 5 ---------------------------------------------*/
    printf("\nTest 5 : Test for Enqueue on Full Buffer also Dequeue on Empty Buffer\t");
    // Test 5 : Enqueue on Full Buffer also Dequeue on Empty Buffer
    // Test checks initial length and capacity. Test fills 256 Bytes into buffer.
    // Test then enqueues 10 indicating enqueue on full buffer so test returns 0
    // Test then empties buffer and checks if 0 is returned on dequeueing empty
    // buffer
    int i5;
    char data5[256];
    char data_out5[256];
    for (i5 = 0; i5 < 256; i5++) {
        data5[i5] = (char) i5;
    }
    assert(cbfifo_length() == 0);
    assert(cbfifo_capacity() == 256);

    printf("\n\t\tTest case Fills buffer first upto 256 Bytes.\n");
    assert(cbfifo_enqueue(data5, 256) == 256);
    assert(cbfifo_length() == 256);
    // Again enqueue on the full buffer
    assert(cbfifo_enqueue(data5, 10) == 0);
    assert(cbfifo_length() == 256);

    printf("\t\tTest case check 0 bytes returned if enqueued 10 bytes on full buffer.\n");
    // Dequeue 256 bytes from the FIFO
    printf("\n\t\tTest case empties buffers.\n");
    assert(cbfifo_dequeue(data_out5,256) == 256);
    assert(cbfifo_length() == 0);
    // Dequeueing on empty buffer
    assert(cbfifo_dequeue(data_out5,300) == 0);
    assert(cbfifo_length() == 0);
    printf("\t\tTest case check 0 bytes returned if dequeued 300 bytes on empty buffer.\n");

    printf("\tTest 5 : Test Passed\n");

// return 1 if all test are passed
return 1;
 
}

#endif // _TEST_CBFIFO_C_




