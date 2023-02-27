[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10101588&assignment_repo_type=AssignmentRepo)
# PES Assignment 3 : Christmas Lights
Student name : Kiran Jojare
# Description: 
Assignment 3 for implementing "Christmas Lights" program on KL25Z Microcontroller. 
The program test the board LED'S at the startup by blinking test pattern and then inside an infinite loop.   
*Note : Extra credit section is calculated and noted in these readMe at the section `Extra Credit`*

The "ChristmasLights" program will be implemented as follows:
1. When the program first launches, ChristmasLights will "test" the LED by blinking in the manner described below.
White for 500 milliseconds, off for 100 milliseconds, blue for 500 milliseconds, off for 100 milliseconds, white for 500 milliseconds, off for 100 milliseconds.

2. ChristmasLights will then go into an endless loop, flashing the LED in the manner described below:
Red is on for 500 milliseconds and then turns off. Green is on for 1000 milliseconds and then turns off. Red is on for 2000 milliseconds and then turns off.
Return to the top (for example, RED ON for 500 msec...)

3. During the infinite loop, when the LED is RED and GREEN, if the user touches the capacitive touch slider, the color will change as follows:  
    If User Touches - Left Side Of The Slider: Red  
    If User Touches - Right Side Of The Slider: Green  
The blinking timing and sequence will be similar to earlier step 2. except that it will use only one color Red or Green depending on the slider touch.   

The ChristmasLights code polls the touch slider at least once every 100 msec. If the LED is on when a touch is detected, the light color changes immediately. 

## Code Organisation
* `main.c` - Main file that calls main() function which test led pattern and then triggers calls function infinite loop for LED blinking and also polls the touch sensor every 100 msec.

* `LED_Func.c` -  This is a C file containing functions for controlling LEDs on a development board. 

* `LED_Func.h` - This file, LED_Func.h, defines a set of functions for controlling LEDs on the MKL25Z4 microcontroller. It contains pin definitions for the red, green, and blue LEDs, as well as functions for initializing the LEDs, turning them on and off, and toggling them in specific patterns. The file also includes a delay_ms() function that provides a delay in milliseconds, using the microcontroller's system clock.
 
* `TSI_Sensor.c` - This file, LED_Func.h, defines a set of functions for controlling LEDs on the MKL25Z4 microcontroller. It contains pin definitions for the red, green, and blue LEDs, as well as functions for initializing the LEDs, turning them on and off, and toggling them in specific patterns. The file also includes a delay_ms() function that provides a delay in milliseconds, using the microcontroller's system clock.

* `TSI_Sensor.h` - This is the header file for TSI_Sensor.c It includes necessary libraries and defines macros for TSI sensing operation. Macros are defined for touch offset, touch count, and TSI data. Macros are also defined for slider touch detection, with left and right slider touched values, and slider not touched value.

## Calibration Data

#### Delay Calibration

Following delay calibrations are added in file `LED_Func.h`
```
// Timer delay constant
#define DELAY_CONSTANT 3225

// Constants for delay function inputs
#define DELAY_100 100
#define DELAY_500 500
```

#### Touch Sensor Calibrations

Following calibrations are added in file `TSI_Sensor.h`
```
// offset value to be subtracted
#define TOUCH_OFFSET 650  
// Thresholds for Calibrating Touch Sensor
#define UPPER_THD 600 
#define LOWER_THD 25.     
```
The code will consider right side touched if sensor value returned is above UPPER_THD. 
The code will consider left side touched if sensor returns value between 25 and 600
The code will consider slider not touhed if it returns value less than 25


## Extra credit

### Part 1 Address of main() function & Size of delay_ms() function
The starting addresss as per below screenshot is 00000c5cH   

![Screenshot 2023-02-22 at 2 00 17 AM](https://user-images.githubusercontent.com/111842372/220571929-b4878674-1b3c-4277-b663-35555302ea6d.png)



The delay function disassembly is as show below
In this case, the address of the first instruction is 00000506, and the address of the last instruction is 00000542.
Subtracting the address of the first instruction from the address of the last instruction gives us:  


00000542 - 00000504 = 62 Bytes


Therefore, based on this calculation, the size of the code is 62 bytes.
Note that this assumes that each instruction is encoded as a single byte, which is not the case for the ARM Cortex-M0+ architecture. The actual size of the code may be larger than 62 bytes.  

![Screenshot 2023-02-22 at 2 04 13 AM](https://user-images.githubusercontent.com/111842372/220572889-a7e96d49-e4ee-4a4a-be5c-58f1627c9cb3.png)



### Part 2 Disassembly of delay() function.   

This assembly code is implementing a delay function delay_ms that causes a specified number of milliseconds of delay. The function takes one argument ms, which specifies the number of milliseconds to delay, and the actual delay is performed using a loop that repeatedly increments an inner loop counter from 0 to a constant value (DELAY_CONSTANT) and an outer loop counter from 0 to ms-1.

The detailed delay_ms() function disassembly is explained line by line in detail as below:
```
delay_ms:
00000504:   push    {r7, lr}      ; Push the contents of r7 and the link register lr to the stack to save them.
00000506:   sub     sp, #16       ; Allocate 16 bytes of space on the stack for local variables.
00000508:   add     r7, sp, #0    ; Set the frame pointer r7 to point to the beginning of the stack frame.
0000050a:   str     r0, [r7, #4]  ; Store the function argument (ms) in the local variable at r7+4.

; Initialize the loop counter i to 0.
0000050c:   movs    r3, #0
0000050e:   str     r3, [r7, #12]

; Loop over i from 0 to ms-1.
00000510:   b.n     0x52c <delay_ms+40>  ; Jump to the delay_ms+40 label (end of outer loop) if i >= ms.

; Initialize the loop counter j to 0.
00000512:   movs    r3, #0
00000514:   str     r3, [r7, #8]

; Loop over j from 0 to DELAY_CONSTANT-1.
00000516:   b.n     0x51e <delay_ms+26>  ; Jump to the delay_ms+26 label (end of inner loop) if j >= DELAY_CONSTANT.
00000518:   ldr     r3, [r7, #8]  ; Load the value of j into r3.
0000051a:   adds    r3, #1        ; Increment j by 1.
0000051c:   str     r3, [r7, #8]  ; Store the new value of j.
0000051e:   ldr     r3, [r7, #8]  ; Load the value of j into r3.
00000520:   ldr     r2, [pc, #28] ; Load the constant value DELAY_CONSTANT from the program counter + 28 bytes (delay_ms+60 label) into r2.
00000522:   cmp     r3, r2        ; Compare j and DELAY_CONSTANT.
00000524:   bls.n   0x518 <delay_ms+20>  ; Jump to the delay_ms+20 label (inner loop) if j < DELAY_CONSTANT.

; Increment i by 1.
00000526:   ldr     r3, [r7, #12] ; Load the value of i into r3.
00000528:   adds    r3, #1        ; Increment i by 1.
0000052a:   str     r3, [r7, #12] ; Store the new value of i.

; Compare i with ms and loop if i < ms.
0000052c:   ldr     r2, [r7, #12] ; Load the value of i into r2.
0000052e:   ldr     r3, [r7, #4]  ; Load the value of ms into r3.
00000530:   cmp     r2, r3        ; Compare i and ms.
00000532:   bcc.n   0x512 <delay_ms+14>  ; Jump to the delay_ms+14 label (outer loop) if i < ms.

; Return

```

## Author
Kiran Jojare

## Reviewer:
Vishweshwaran. 

## Review Date:
21st Feb

## Review Comments:
1. Should use macros to set left and right threshold for the touch sensor in TSI_sensor.c line 99 to line 109
    - Added MACRO named
        #define UPPER_THD 600
        #define LOWER_THD 25 
        inside `TSI_Sensor.h`
2. Should use macro to define 1 millisecond loop variable value to improve readability in LED_Func.c line 57
    - Added MACRO named 
        #define DELAY_100 100
        #define DELAY_500 500
        inside `LED_Func.h`
3. Can optimize the code in infinite_loop() by trying to combine the four seperate for loops (to poll the touch sensor in increments of 100ms while LED needs to be on for 500,1000,2000 and 3000 ms) by instead fetching the requisite no. of iterations from an integer array.
    - There was no need to actually use Arrays for delay timers but approprotate modifications has been done on improving the infinity_loop by exculding        unneccessary looping
4. In ChristmasLights.c, LEDs blink with proper delay as required only when line 49, BOARD_InitBootClocks() is commented out.
    - Addeed Board initialisations function and verified that system works as expected with board init function
5. Yet to add print statements that will only print in debug mode and not in release mode
    -  Addeed PRNTF using files `log.h` and tested using the same in `debug mode`
6. Has to include instructions in README.md to edit touch sensor calibration macros for ease of implementation on a different FRDMKL25Z dev board.
    - Updated readme to indicate TA's the constants needed to be modified

## Extent Bugs
No bugs found as of now. The code works fine as per requirements
