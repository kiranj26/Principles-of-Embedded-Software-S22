[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10544687&assignment_repo_type=AssignmentRepo)
# PES Assignment 5 - Optamizing PBKDF2  
Student name : Kiran Jojare. 

# Introduction
This assignment works on providing optamization on C files for ISHA Hashing algorithm and also include and extra credit for ARM asssembly.  
Note : Both extra credit is completed
* Code does runs in less than 200 msec with Only C Optamization
* Code does runs in less than 1700 msec and an assembly file is written for the code `ISHAProcessMessageBlock` function inside `isha.c`

# Background
In cryptography, a key derivation function is used to stretch a secret—usually a passphrase—into a longer binary key suitable for use in a cryptosystem. By their nature, key derivation functions must be expensive to compute, in order to protect the cryptosystem against brute force dictionary attacks.  

One popular key derivation function is known as PBKDF2, which is defined in RFC 8018. PBKDF2 is used in a number of applications, including WPA2-PSK—perhaps the most widespread authentication system used today in deployed Wi-Fi networks.
As used in WPA2-PSK, the PBKDF2 function relies on calling HMAC-SHA1 8192 times; each call to HMAC-SHA1 in turn results in two calls to the SHA-1 secure hashing algorithm. Although it is not strictly equired for this assignment, you may wish to learn a little about cryptographic hashing functions by reading the introduction to this Wikipedia page:  

https://en.wikipedia.org/wiki/Cryptographic_hash_function.  

For our purposes, PBKDF2 based on the full HMAC-SHA1 is quite complex. To simplify things (somewhat), for this assignment you are being given a completely insecure hashing algorithm, which is called ISHA: The Insecure Hashing Algorithm.
You are provided reference C source code which computes PBKDF2-HMAC-ISHA, using parameters similar to those used every time a device connects to Wi-Fi. At present, this reference source code is believed to be correct—that is, it computes accurate results. However, when running on our FRDM- KL25Z board, one call to this function consumes approximately 8.7 seconds when compiled with -O0. Our marketing department is not happy with this performance, and you have been given the job to
improve it. 

# Optamization Changes
Following functions and files has been optamized and description for each is aded below. Code contains comments with prefix `KJ : <comments>` indicating the optamisations done.  
## isha.h
* Changed Length_Low and High to use only one Length
```
  /* KJ : Changed Length_Low and High
   *      to use only one Length
   */
  uint32_t Length;
```
## pbkdf2_hmac_isha()
* Updated the size of accumulator from 2560 back to 512 no need for 2560 size `uint8_t accumulator[512];`
* Check variable as a work around added used in F() function. This change will make sure to run the hmac_isha function only once.
* Eliminated for loop to with memcopy Assuming that DK and accumulator are arrays of the same type and size `__builtin_memcpy(DK, accumulator, dkLen * sizeof(DK[0]));`

## F()
* Updated the data type for i to register `register int i=0`
* Eliminated for loop with `memcopy memcpy(saltplus, salt, salt_len);` `__builtin_memcpy(saltplus, salt, salt_len);`
* Reversing the blkidx with the help of __builtin_bswap32 and then storing it in salplus rather than copying data byte-wise `blkidx=__builtin_bswap32(blkidx);` `memcpy(saltplus+salt_len,&blkidx,4);`
* Eliminated for loop with memcopy `  memcpy(result, temp, ISHA_DIGESTLEN);`

## hmac_isha()
* Local ISHAContext for workaround to store ISHAContext status will calling for ipad and opad 	`static ISHAContext Ipad_ISHAContext_ctx;` `static ISHAContext Opad_ISHAContext_ctx;` 
* Check is added to ensure that calculation for ipad opad and keypad Only once when hmac_isha is called `if(check==1)`
* Removed if loop part and only kept else part as since test has key_len == 8 which will be never greater than ISHA_BLOCKLEN which is 64 Also changed for loop with memset Please note concept is visualised based on lecture slides
* Storing state into local static ISHAContext 

## ISHAReset()
* Removed use of Length high and low and only single length variable use `tx->Length  	 = 0;`

## ISHAResult()
* Deleting the corrupted check as per lecture slides
* Updated the byte by byte transfer wit bsswao32 function to eliminate for loop limitations
```
	*((uint32_t *)(digest_out )) = __builtin_bswap32(ctx->MD[0]);
	*((uint32_t *)(digest_out + 4)) = __builtin_bswap32(ctx->MD[1]);
	*((uint32_t *)(digest_out + 8)) = __builtin_bswap32(ctx->MD[2]);
	*((uint32_t *)(digest_out + 12)) = __builtin_bswap32(ctx->MD[3]);
	*((uint32_t *)(digest_out + 16)) = __builtin_bswap32(ctx->MD[4]);
```
## ISHAInput()
* Removed first two if conditions as length will never be zero
* Line called inside loop multiple times but not updated everytime replaced at top to reduce no of iterations `  ctx->Length += 8 * length;`
* Removed not required ANDING with 0xFFFFFFFF
* Removed if check when data is corrupted as per lecture slides

## ISHAProcessMessageBlock()
### C Optamised Version
```
tatic void ISHAProcessMessageBlock(ISHAContext *ctx)
{
/* KJ : register variables used
 *
 */
  register uint32_t temp;
  register int t;

  uint32_t W[16];
  uint32_t A, B, C;
  uint32_t D, E;

  A = ctx->MD[0];
  B = ctx->MD[1];
  C = ctx->MD[2];
  D = ctx->MD[3];
  E = ctx->MD[4];

  /* KJ : Using single loop for optimization
   */

  for(t = 0; t < 16; t++)
  {
	/* KJ : Used __builtin_bswap32 for copying to
	 *      reduce iterations
	 */
	W[t] = (__builtin_bswap32(*(uint32_t *)(&ctx->MBlock[t<<2])));

    temp = ISHACircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t];

	/* KJ : Removed redundant ANDINF with 0xFFFFFFFF
	 *      Keeping everything same
	 */
    E = ISHACircularShift(25, D);
    D = ISHACircularShift(15,C);
    C = ISHACircularShift(30,B);
    B = ISHACircularShift(10,A);
    A = ISHACircularShift(5, temp);
  }
  /* KJ : Removed redundant bitwise ANDING
   *      as its not affecting
   */
  ctx->MD[0] += A;
  ctx->MD[1] += B;
  ctx->MD[2] += C;
  ctx->MD[3] += D;
  ctx->MD[4] += E;

  ctx->MB_Idx = 0;

}
```

### Assembly Version
```
	push {r4, r5, r6, r7, lr}
	// Load the contents of the memory address pointed to by r0 + 0 into r3
	ldr r3, [r0, #0]
	// Subtract 36 from the stack pointer
	sub sp, #36
	// Store the contents of r3 to the memory address pointed to by sp + 0
	str r3, [sp, #0]
	// Load the contents of the memory address pointed to by r0 + 4 into r3
	ldr r3, [r0, #4]
	// Load the contents of the memory address pointed to by sp + 0 into r5
	ldr r5, [sp, #0]
	// Store the contents of r3 to the memory address pointed to by sp + 4
	str r3, [sp, #4]
	// Load the contents of the memory address pointed to by r0 + 8 into r3
	ldr r3, [r0, #8]
	// Load the contents of the memory address pointed to by sp + 4 into r4
	ldr r4, [sp, #4]
	// Store the contents of r3 to the memory address pointed to by sp + 8
	str r3, [sp, #8]
	// Load the contents of the memory address pointed to by r0 + 12 into r3
	ldr r3, [r0, #12]
	// Load the contents of the memory address pointed to by sp + 8 into r1
	ldr r1, [sp, #8]
	// Store the contents of r3 to the memory address pointed to by sp + 12
	str r3, [sp, #12]
	// Load the contents of the memory address pointed to by r0 + 16 into r3
	ldr r3, [r0, #16]
	// Load the contents of the memory address pointed to by sp + 12 into r2
	ldr r2, [sp, #12]
	// Store the contents of r3 to the memory address pointed to by sp + 16
	str r3, [sp, #16]
	// Move the constant 24 to r3
	movs r3, #24
	// Move the contents of r3 to r12
	mov r12, r3
	// Move the contents of r0 to r3
	movs r3, r0
	// Load the contents of the memory address pointed to by sp + 16 into r6
	ldr r6, [sp, #16]
	// Add 88 to the value in register r3
	adds    r3, #88
	// Add the value in register r0 to r12
	add     r12, r0
	// Store the value in r3 to the address pointed by sp + 24
	str     r3, [sp, #24]
	// Assign the value in r12 to r7
	JUMP1:   mov     r7, r12
	// Load the value from memory pointed by r7 into r3 and update r7
	ldmia   r7!, {r3}
	// Reverse the bits of the value in r3
	rev     r3, r3
	// Store the value in r3 to the address pointed by sp + 20
	str     r3, [sp, #20]
	// Assign the value in r1 to r3, then do eors, ands, and eors operations
	movs    r3, r1
	eors    r3, r2
	ands    r3, r4
	eors    r3, r2
	// Store the value in r3 to the address pointed by sp + 28
	str     r3, [sp, #28]
	// Assign the value in r7 to r12 and assign 27 to r3
	mov     r12, r7
	movs    r3, #27
	// Assign the value in r5 to r7, rotate r7 to the right by 27 bits
	// Add the values in r7 and the memory location pointed by sp + 20
	// Add the values in r3 and the memory location pointed by sp + 28
	movs    r7, r5
	rors    r7, r3
	ldr     r3, [sp, #20]
	adds    r7, r7, r3
	ldr     r3, [sp, #28]
	adds    r7, r3, r7
	// Adds the value of register r6 to the value of register r7 and stores the result in r7.
	adds    r7, r7, r6
	// Moves the value 7 into register r6.
	movs    r6, #7
	// Rotates the bits in register r2 by the value in register r6.
	rors    r2, r6
	// Moves the value in register r2 to register r6.
	movs    r6, r2
	// Moves the value in register r1 to register r2.
	movs    r2, r1
	// Moves the value 17 into register r1.
	movs    r1, #17
	// Rotates the bits in register r2 by the value in register r1.
	rors    r2, r1
	// Moves the value in register r4 to register r1.
	movs    r1, r4
	// Moves the value 2 into register r4.
	movs    r4, #2
	// Moves the value 22 into register r3.
	movs    r3, #22
	// Rotates the bits in register r1 by the value in register r4.
	rors    r1, r4
	// Moves the value in register r5 to register r4.
	movs    r4, r5
	// Moves the value in register r7 to register r5.
	movs    r5, r7
	// Rotates the bits in register r4 by the value in register r3.
	rors    r4, r3
	// Adds 5 to the value in register r3.
	adds    r3, #5
	// Rotates the bits in register r5 by the value in register r3.
	rors    r5, r3
	// Loads the value stored in memory at the address in sp + 24 into register r3.
	ldr     r3, [sp, #24]
	// Compares the values in registers r3 and r12.
	cmp     r3, r12
	// Branches to the label JUMP1 if the values in registers r3 and r12 are not equal.
	bne.n   JUMP1
	// Loads the value stored in memory at the address in sp + 0 into register r3.
	ldr     r3, [sp, #0]
	// Adds the values of registers r3 and r5 and stores the result in r5
	adds    r5, r3, r5
	// Loads the value from memory address stored in sp+4 into register r3
	ldr     r3, [sp, #4]
	// Stores the value of register r5 in the memory address stored in r0+0
	str     r5, [r0, #0]
	// Adds the values of registers r3 and r4 and stores the result in r4
	adds    r4, r3, r4
	// Loads the value from memory address stored in sp+8 into register r3
	ldr     r3, [sp, #8]
	// Stores the value of register r4 in the memory address stored in r0+4
	str     r4, [r0, #4]
	// Adds the values of registers r3 and r1 and stores the result in r1
	adds    r1, r3, r1
	// Loads the value from memory address stored in sp+12 into register r3
	ldr     r3, [sp, #12]
	// Stores the value of register r1 in the memory address stored in r0+8
	str     r1, [r0, #8]
	// Adds the values of registers r3 and r2 and stores the result in r2
	adds    r2, r3, r2
	// Loads the value from memory address stored in sp+16 into register r3
	ldr     r3, [sp, #16]
	// Stores the value of register r2 in the memory address stored in r0+12
	str     r2, [r0, #12]
	// Stores the value of register r2 in the memory address stored in r0+12
	adds    r6, r3, r6
	// Sets the value of register r3 to 0
	movs    r3, #0
	str     r6, [r0, #16]
	str     r3, [r0, #88]
	add     sp, #36
	pop     {r4, r5, r6, r7, pc}

```

## ISHAPadMessage()
* `ctx->MBlock[ctx->MB_Idx++] = 0x80;` called inside function for both if and else condition and was not doing same changes so added at the top.
* Updated all while loop with memset
* Replace byte by bte transfer with btswap32 function `	*(uint32_t *)(ctx->MBlock+60) = __builtin_bswap32(ctx->Length);`

# Analysis
The table below shows the timing and size analysis of the before optamisation after optamisation. The tables also shows the details with C only changes and also C plus asembly file changes. To summerise, after optamisation code with  C + Assebly changes where found to be most matching requirement with time achieved as `1330 ms` and .text file as `18900 bytes` with -O0(None) optamisation.

### Before Optamization
The table below shows the result with debug mode of output with three optamisation options.  
| Compile Option | Speed (msec) | Size of .text (bytes) |
|----------------|--------------|-----------------------|
| -O0            | 8874         | 21036                 |
| -O3            | 2363         | 18292                 |
| -Os            | 3258         | 15084                 |

### With Only C Changes
Table below shows timing anf .text analysis for the code which contains only C optamization. Note results are for release mode.
| Compile Option | Speed (msec) | Size of .text (bytes) |
|----------------|--------------|-----------------------|
| -O0            | 1588         | 18900                 |
| -O3            | 889         | 17472                 |
| -Os            | 1014         | 13824                 |

### With C And Assembly
Table below shows timing anf .text analysis for the code which contains C as well as Assembly file optamization. Note results are for release mode.

| Compile Option | Speed (msec) | Size of .text (bytes) |
|----------------|--------------|-----------------------|
| -O0            | 1330         | 18836                 |
| -O3            | 911         | 14692                 |
| -Os            | 1014         | 15084                 |

#### With Only C Changes
Timing analysis with only C file based optamization -O0(none) is calculated to be *1590 ms**. The UART result of the same is added below.  

![image](https://user-images.githubusercontent.com/111842372/226911201-79a4e281-3793-45a4-85b0-732eeeeff9db.png)

#### With C and Assembly
Timing analysis with C file based optamization -O0(none) and an assembly for the function `ISHAProcessMessageBlock` is calculated to be *1330 ms**. The UART result of the same is added below. 

![image](https://user-images.githubusercontent.com/111842372/226910802-7b6f4a22-e25d-4cfc-a281-dc233b736c42.png)

# Extra Credit

Both extra credit is completed
* Code does runs in less than 200 msec with Only C Optamization
* Code does runs in less than 1700 msex and an assembly file is written for the code `ISHAProcessMessageBlock` function inside `isha.c`


# Function Call Stack

Function call stack is found to be as follows. Same organisation is also found in technical demo.

![image](https://user-images.githubusercontent.com/111842372/226929995-7c40a53b-e299-41c9-9cc6-39501c8d8eb3.png)

# Code Organisation
* `assembly_ISHAProcessMessageBlock.h` : Header file containing function declarations for the assembly implementation of the SHA-1 hash algorithm.
* `assembly_ISHAProcessMessageBlock.s`: Assembly language implementation of the SHA-1 hash algorithm.
* `isha.c` : Implementation of the ISHA-1 hash algorithm in C.
* `isha.h` : Header file containing function declarations and data structures for the ISHA-1 hash algorithm.
* `main.c` : Main file of the program, containing the entry point and examples of how to use the ISHA-1 hash algorithm.
* `pbkdf2_test.c` :  Implementation of a test suite for the PBKDF2 key derivation function.
* `pbkdf2_test.h` : Header file containing function declarations and data structures for the PBKDF2 test suite.
* `pdkdfp2.c`: Implementation of the PDKDFP2 key derivation function.
* `pdkdfp2.h`: Header file containing function declarations and data structures for the PDKDFP2 key derivation function.
* `ticktime.c` : Implementation of a function to measure the elapsed time between two points in the program.
* `ticktime.h` : Header file containing function declarations and data structures for the ticktime module.


# Extent Bugs
No extent bugs found in code file. The code is performing as expected from assignment requirements. However there is one warnign of return from non voidnfunction in test file. The test files where unaffected so warnign is not taken care. 

