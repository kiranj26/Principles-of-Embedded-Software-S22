@ Author Kiran Jojare
@ Date Mar 22 2019
@ Assembly file for ISHAProcessMessageBlock function used inside isha.c

.cpu cortex-m0
.syntax unified

.text
.globl ISHAProcessMessageBlock
.type ISHAProcessMessageBlock, %function

@ static void ISHAProcessMessageBlock(ISHAContext *ctx)
ISHAProcessMessageBlock:
	// Push the contents of r4, r5, r6, r7 and lr to the stack
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
