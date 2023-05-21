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
​ ​*        different corner cases for logic implemented in cbfifo.c file
 *
 *
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​Feb 4​ 2023
​ ​*​ ​@version​ ​1.0
​ ​*
​ ​*/

#include "test_cbfifo.h"

#define ARRAY_SIZE 	(261)

static void test_cbfifo_transmiter()
{
    // Define a char array with size of 261, and initialize it with characters.
    char str[ARRAY_SIZE] = { 'H', 'e', 'l', 'l', 'o', 'K', 'K', 'i', 'r', 'a', 'n','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B','C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B','C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'H', 'e',
                      'l', 'l', 'o'
                    };

    char dequeque_buf[261];
    int expected_read = 0;
    int expected_write = 0;

    int capacity = cbfifo_capacity(transmitter);

    // Test 1 :Enqueuing NULL value
    assert(cbfifo_enqueue(NULL, 1, transmitter) == -1);

    // Test 2 : Dequeuing NULL value
    assert(cbfifo_dequeue(NULL, 1, transmitter) == -1);

    // Test 3: Verify buffer length when it's empty.
    assert(cbfifo_length(transmitter) == 0);

    // Test 4: Enqueue 60 bytes and check if the operation was successful.
    assert(cbfifo_enqueue(str, 60, transmitter) == 60);

    // Test 5: Dequeue 10 bytes, compare both buffers, and check if the expected length matches.
    assert(cbfifo_dequeue(dequeque_buf, 10, transmitter) == 10);
    assert(strncmp(dequeque_buf, str, 10) == 0);
    assert(cbfifo_length(transmitter) == 50);

    // Test 6: Enqueue 65 bytes and check if it's possible to add data beyond the capacity of the buffer.
    assert(cbfifo_enqueue(str, 65, transmitter) == 65);
    assert(cbfifo_length(transmitter) == 115);

    // Test 7: Dequeue all elements and ensure that all the data has been dequeued successfully.
    assert(cbfifo_dequeue(dequeque_buf, 115, transmitter) == 115);
    assert(cbfifo_length(transmitter) == 0);

    // Test 8: Enqueue the full capacity of the buffer and then try to enqueue one more element.
    // Finally, dequeue all the elements to verify the data consistency.
    assert(cbfifo_enqueue(str, capacity, transmitter) == capacity);
    assert(cbfifo_length(transmitter) == capacity);
    assert(cbfifo_enqueue(str, 1, transmitter) == 0);
    assert(cbfifo_dequeue(dequeque_buf, capacity, transmitter) == capacity);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, capacity) == 0);

    // Test 9   : checks whether the function returns 0 when nbyte is set to 0.
    assert(cbfifo_enqueue(str, 0, transmitter) == 0);

    // Test 10 : checks whether the Dequeue function returns 0 when the buffer length is 0.
    assert(cbfifo_length(transmitter) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 1, transmitter) == 0);

    // Test 11 : aims to test the functionality of read and write pointers in the circular buffer.
    assert(cbfifo_enqueue(str, capacity, transmitter) == capacity);
    expected_write = capacity;
    assert(cbfifo_length(transmitter) == capacity);
    assert(cbfifo_dequeue(dequeque_buf, 100, transmitter) == 100);
    expected_read = 100;
    assert(cbfifo_length(transmitter) == 156);
    assert(strncmp(dequeque_buf, str, 100) == 0);
    assert(cbfifo_enqueue(str + 25, 25, transmitter) == 25);
    expected_read += 25;
    assert(cbfifo_length(transmitter) == 181);
    assert(cbfifo_dequeue(dequeque_buf, 181, transmitter) == 181);
    assert(cbfifo_length(transmitter) == 0);

    //Test 12 : Enqueue 45 bytes, dequeue 40 bytes, then remove all elements and empty the buffer.
    assert(cbfifo_enqueue(str, 45, transmitter) == 45);
    assert(cbfifo_length(transmitter) == 45);
    assert(cbfifo_dequeue(dequeque_buf, 40, transmitter) == 40);
    assert(cbfifo_length(transmitter) == 5);
    assert(strncmp(dequeque_buf, str, 40) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 5, transmitter) == 5);
    assert(cbfifo_length(transmitter) == 0);

    //Test 13 :  Check the positions of the read and write pointers in the cbfifo buffer.
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 100, transmitter) == 100);
    expected_write = 100;
    assert(cbfifo_length(transmitter) == 100);
    assert(cbfifo_dequeue(dequeque_buf, 32, transmitter) == 32);
    expected_read = 32;
    assert(cbfifo_length(transmitter) == 68);
    assert(strncmp(dequeque_buf, str, 32) == 0);
    assert(cbfifo_enqueue(str + expected_write, 12, transmitter) == 12);
    expected_read += 12;
    assert(cbfifo_length(transmitter) == 80);

    //Empty the buffer to prepare for the next test case.
    assert(cbfifo_dequeue(dequeque_buf, 80, transmitter) == 80);
    assert(cbfifo_length(transmitter) == 0);

    //Test 14 : Enqueue a certain number of elements and then dequeue more than that. Check the buffer length and the elements that were dequeued.
    assert(cbfifo_enqueue(str, 32, transmitter) == 32);
    assert(cbfifo_length(transmitter) == 32);
    assert(cbfifo_dequeue(dequeque_buf, 48, transmitter) == 32);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, 32) == 0);

    //Test 15 : Enqueue a certain number of elements and then dequeue more than that in two separate steps. Check the buffer length and the elements that were dequeued.
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 50, transmitter) == 50);
    assert(cbfifo_length(transmitter) == 50);
    expected_write = 50;
    assert(cbfifo_dequeue(dequeque_buf, 25, transmitter) == 25);
    assert(cbfifo_length(transmitter) == 25);
    expected_read = 25;
    assert(cbfifo_dequeue(dequeque_buf + expected_read, 30, transmitter) == 25);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, 50) == 0);

    //Test 16 : Check if the capacity of the buffer is 256.
    assert(capacity == 256);
}

static void test_cbfifo_receiver()
{
    // Define a char array with size of 261, and initialize it with characters.
    char str[ARRAY_SIZE] = { 'H', 'e', 'l', 'l', 'o', 'K', 'i', 'r', 'a', 'n', 'J','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B','C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B','C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b','c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'H', 'e',
                      'l', 'l', 'o'
                    };
    char dequeque_buf[261];
    int expected_read = 0;
    int expected_write = 0;

    int capacity = cbfifo_capacity(receiver);

    //Test 1 : Enqueuing a NULL value should not add any element to the buffer.
    assert(cbfifo_enqueue(NULL, 1, receiver) == -1);

    //Test 2 :  Dequeuing from an empty buffer (NULL value) should not return any element.
    assert(cbfifo_dequeue(NULL, 1, receiver) == -1);

    //Test 3 :  When the buffer is empty, its length should be equal to 0.
    assert(cbfifo_length(receiver) == 0);

    //Test 4 : Enqueue 60 bytes to the buffer and check if the length of the buffer is 60.
    assert(cbfifo_enqueue(str, 60, receiver) == 60);

    //Test 5 :  Dequeue 10 bytes from the buffer, compare the dequeued elements with the expected values, and check the length of the buffer.
    assert(cbfifo_dequeue(dequeque_buf, 10, receiver) == 10);
    assert(strncmp(dequeque_buf, str, 10) == 0);
    assert(cbfifo_length(receiver) == 50);

    //Test 6 :  Enqueue 65 bytes to the buffer and check if the length of the buffer is 125.
    assert(cbfifo_enqueue(str, 65, receiver) == 65);
    assert(cbfifo_length(receiver) == 115);

    //Test 7 :  Dequeue all elements from the buffer and check if the length of the buffer is 0.
    assert(cbfifo_dequeue(dequeque_buf, 115, receiver) == 115);
    assert(cbfifo_length(receiver) == 0);

    //Test 8 : Enqueue elements to fill the buffer to its full capacity, then try to enqueue one more element. Dequeue all elements from the buffer and check if the length of the buffer is 0.

    assert(cbfifo_enqueue(str, capacity, receiver) == capacity);
    assert(cbfifo_length(receiver) == capacity);
    assert(cbfifo_enqueue(str, 1, receiver) == 0);
    assert(cbfifo_dequeue(dequeque_buf, capacity, receiver) == capacity);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, capacity) == 0);

    //Test 9  : When the value of nbyte is equal to 0, the function should return 0.
    assert(cbfifo_enqueue(str, 0, receiver) == 0);

    //Test 10 : When the length of the buffer is 0, dequeuing an element from the buffer should return 0.
    assert(cbfifo_length(receiver) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 1, receiver) == 0);

    //Test 11 :  Check the positions of the read and write pointers in the cbfifo buffer.
    assert(cbfifo_enqueue(str, capacity, receiver) == capacity);
    expected_write = capacity;
    assert(cbfifo_length(receiver) == capacity);
    assert(cbfifo_dequeue(dequeque_buf, 100, receiver) == 100);
    expected_read = 100;
    assert(cbfifo_length(receiver) == 156);
    assert(strncmp(dequeque_buf, str, 100) == 0);
    assert(cbfifo_enqueue(str + 25, 25, receiver) == 25);
    expected_read += 25;
    assert(cbfifo_length(receiver) == 181);
    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 181, receiver) == 181);
    assert(cbfifo_length(receiver) == 0);

    //Test 12 : Add 45 bytes and pull out 40 later remove all and empty
    assert(cbfifo_enqueue(str, 45, receiver) == 45);
    assert(cbfifo_length(receiver) == 45);
    assert(cbfifo_dequeue(dequeque_buf, 40, receiver) == 40);
    assert(cbfifo_length(receiver) == 5);
    assert(strncmp(dequeque_buf, str, 40) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 5, receiver) == 5);
    assert(cbfifo_length(receiver) == 0);

    //Test 13 : Testing read and write pointer in cbfifo
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 100, receiver) == 100);
    expected_write = 100;
    assert(cbfifo_length(receiver) == 100);
    assert(cbfifo_dequeue(dequeque_buf, 32, receiver) == 32);
    expected_read = 32;
    assert(cbfifo_length(receiver) == 68);
    assert(strncmp(dequeque_buf, str, 32) == 0);
    assert(cbfifo_enqueue(str + expected_write, 12, receiver) == 12);
    expected_read += 12;
    assert(cbfifo_length(receiver) == 80);
    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 80, receiver) == 80);
    assert(cbfifo_length(receiver) == 0);

    //Test 14 : Enqueue elements and then dequeue more than that.
    assert(cbfifo_enqueue(str, 32, receiver) == 32);
    assert(cbfifo_length(receiver) == 32);
    assert(cbfifo_dequeue(dequeque_buf, 48, receiver) == 32);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, 32) == 0);

    //Test 15 : Enqueue elements and then dequeue more than that in two steps.
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 50, receiver) == 50);
    assert(cbfifo_length(receiver) == 50);
    expected_write = 50;
    assert(cbfifo_dequeue(dequeque_buf, 25, receiver) == 25);
    assert(cbfifo_length(receiver) == 25);
    expected_read = 25;
    assert(cbfifo_dequeue(dequeque_buf + expected_read, 30, receiver) == 25);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, 50) == 0);

    //Test 16 : Checking if capacity is 256
    assert(capacity == 256);

}

// Main testing function
void test_cbfifo()
{
	// testing cbfifo treception
    test_cbfifo_transmiter();
    // testing cbfifo trasnmittion
    test_cbfifo_receiver();
}
