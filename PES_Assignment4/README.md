[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10332917&assignment_repo_type=AssignmentRepo)
# PES Assignment4 : Traffic Lights:
Student name : Kiran Jojare

# Description: 
For this assignment we will are creating a traffic light simulation using LED's connected on KL25Z.
The code apprroach is via state machine usng CASE statement. The states are as follows:

We have been hired to develop a new traffic light for export to the little-known mountain town of Boulder. 
Their traffic lights have the following behavior:
* When the traffic light is in the STOP state, Boulder residents use the color #FF00001.
* When the traffic light is in the GO state, Boulder residents use the color #00FF00
* When the traffic light is in the WARNING state, Boulder residents use the color #FFFF00
* When someone presses the button to cross the street (CROSSWALK state), the traffic light is 
blinking with the color #001030. In the CROSSWALK state, the light blinks 250 msec off, 750 msec on. In all other states, the light is solid (not blinking).

Except for the blinking in CROSSWALK mode, all other changes in traffic light color must transition gradually and linearly over a one-second period. 

Timing Calculations for Both Debug and Production for each state is as follows:
| **State**    | **Debug Time** | **Production Time** |
| :------: | :-------: | :-------------: |
|  STOP    |  5 sec    |      20 sec     |
|          |           |                 |
|  GO      |  5 sec    |      20 sec     |
|          |           |                 |
| WARNING  |  3 sec    |       5 sec     |
|          |           |                 |
| CROSSWALK  |  5 sec    |       5 sec     |
|          |           |                 |
| TRANSITION  |  1 sec    |       1 sec     |
|          |           |                 |

The software also take care of functionality when a slider or switch is detected when its already in transition state. On such occation, transition time will be incremeneted by 1 sec from current and the color change is still found to be gradual by software.  

Note the slider is not driven by interrupt. Its polling at every 125 ms time. However switch is driven by interrupt. For the swicth section please see please see the [EXTRA CREDIT](#extra-credit) section below.

# Code Organisation
The project code is organized as follows:
| File Name         | Description                                                                                               |
| -----------------| --------------------------------------------------------------------------------------------------------- |
| `main.c`          | Main file which is an entry point function for the code. This function does all the initialisation and calls the state machine. |
| `TSI_Sensor.c`    | This file defines a set of functions for controlling LEDs on the MKL25Z4 microcontroller. It contains pin definitions for the red, green, and blue LEDs, as well as functions for initializing the LEDs, turning them on and off, and toggling them in specific patterns. The file also includes a `delay_ms()` function that provides a delay in milliseconds, using the microcontroller's system clock. |
| `TSI_Sensor.h`    | Header file for `TSI_Sensor.c`. It includes necessary libraries and defines macros for TSI sensing operation. Macros are defined for touch offset, touch count, and TSI data. Macros are also defined for slider touch detection, with left and right slider touched values, and slider not touched value. |
| `Timing.c`        | This file contains the implementation of timer functions used for tracking time in the system. Functions such as `sytick_init()`, `systic_handler()`, etc. are available here. |
| `Timing.h`        | Header file for all the timing calculation including function declaration, typedefs, and global data. |
| `Switch_Interrupt.c` | This file contains all the switch functionality including switch interrupt initialisation and interrupt handler. |
| `Switch_Interrupt.h` | Header file for switch interrupt functionality. |
| `StateMachine.c`  | The file contains the main logic for state function. It implements all the state functions and state transitions as described in the state diagram. |
| `StateMachine.h`  | Header file for the state machine function including all the necessary function declarations and global and local data. |
| `PWM_LED_Func.c`  | This file defines all the PWM based and LED based functionality. |
| `PWM_LED_Func.h`  | Header file for all the PWM based and LED based functionality. |
| `log.h`           | This file is for logging the output on UART console.                                                       |

# Calibration Data

Following touch sensor calibrations are added in file `TSI_Sensor.c`. feel free to change it accordingly if required. 

```
#define TOUCH_OFFSET 		(600)  					// offset value to be subtracted
#define TOUCH_DATA 			(TSI0->DATA & 0xFFFF)	//macro for extracting the count from data register

// Macros for touch sense detection
#define TOUCH_DETECT_THD   	(300) 					// The threshold value for touch detection.
                                					// If the touch sensor value is greater than or equal to this value,
                                					// touch is considered to be detected.
#define TOUCH_DETECTED     	(1)  					// The return value when touch is detected by the TSI_touch_detected() function.
#define TOUCH_NOT_DETECTED 	(0)   					// The return value when touch is not detected by the T
```

# State Diagram
![StateDiagramPA4 drawio](https://user-images.githubusercontent.com/111842372/224186936-7b374003-0e7f-41ff-88f8-2f7c023b30e3.png)

# Harware Demonstration

Please find the following demo video for requirements. ![Uploading StateDiagramPA4.drawio.png…]()

* **Slider Working** :  
This demo video shows the execution of LED working in respective mode withe slider touch detected.   
Note execution illustrates DEBUG mode.

    https://user-images.githubusercontent.com/111842372/223984542-4fc6eeae-97c5-46de-b552-4b8272484783.mp4

* **Switch Working** :  
This demo video shows the execution of LED working in respective mode with switch press detected.   
Note execution illustrates DEBUG mode.

    https://user-images.githubusercontent.com/111842372/223984591-3b11923a-cec6-4fb1-bed8-740d332533fd.mp4
# UART Debug Output
Please find the following debug console output for verifying timing accuracy.  

From main loop starting to the first button pressed, indidcates the normal state transition without touch or switch detected.  
From first switch/slider detected to second, indicates state transition when a slider is touched when in STOP state.  
From second switch/slider detected to end, indicates state transition when a switch is pressed when in GO state.

```
Main Loop Starting
Transition From STOP to GO started at 5000 ms
Transition From STOP to GO completed at 6000 ms
Transition From GO to WARNING started at 11000 ms
Transition From GO to WARNING ended at 12000 ms
Transition From WARNING to STOP started at 15000 ms
Transition From WARNING to STOP ended at 16000 ms

*** Button Press / Slider Touch Detected at 17312 ms ***

Transition From Current State to WARNING started after ext interrupt at 17312 ms
Transition From Current State to WARNING ended after ext interrupt at 18312 ms
Transition WARNING to CROSSWALK started after ext interrupt at 21312 ms
Transition WARNING to CROSSWALK ended after ext interrupt at 22312 ms
Transition From CROSSWALK to GO started at 27312 ms
Transition From CROSSALK to GO ended at 28312 ms

*** Button Press / Slider Touch Detected at 30875 ms ***

Transition From Current State to WARNING started after ext interrupt at 30875 ms
Transition From Current State to WARNING ended after ext interrupt at 31875 ms
Transition WARNING to CROSSWALK started after ext interrupt at 34875 ms
Transition WARNING to CROSSWALK ended after ext interrupt at 35875 ms
Transition From CROSSWALK to GO started at 40875 ms
Transition From CROSSALK to GO ended at 41875 ms



```
# Extra Credit
The extra credit 1 and 2 has been fullfilled in this assignment.
## Extra Credit 1  : Peer Review
Peer review is scheduled to be done on date March 9 2022 by Vishweshwaran Bhaskaran. Please see the section [REVIEW DATE](#review-date) and [REVIEW Coments](#review-comments) for review information

## Extra Credit 2  : GPIO Button and Interrupt 
The switch interrupt based state change mechanism has beeen implemented.  
Pleasse note the PIN used is PTA4 and it has been tested using a jumper connected from PTB8 to GND. Pin is initialised to be Pulled High initially. To generate an interrupt please connect header from PTA4 to GND. Please see the video of switch working in the section [HARDWARE DEMO](#harware-demonstration) attached above.

# Author

Kiran Jojare.   

MS- ELectrical Engineering (Computer Engineering).   

University of Colorado Boulder. 

# Reviewer:

Vishweshwaran.    

MS- ELectrical Engineering (Embedded System Engineering).   

University of Colorado Boulder.   


## Review Date:
March 9 2023

## Review Comments:

1. Some function descriptions are missing
    - Added missing function description
2. Log messages on UART does not follow requirements:
    - Correct the UART prints by adding more trasitions to the code. Aslo added /r/n wherever required:
3. Use greater than equal instead of greater than to avoid extra Tick:
    - Corrected the if conditions in state machine to avoid one extra tick by replacing < with <=:
4. Define enum in .c instead of .h:
    - Corrected. Added enum defination which is local to the file to the .c file and not .h:
5. Use of extern could be modified:
    - Could not work on it due to limited time.
6. Remove unnecessary header files like stdio.h, stdint.h :
    - Done. Removed one stdio.h and stdlib.h from the main.c file
7. While (1) in state machine to be removed and should be called in main's while(1)
    - Done, Removed while(1) from state_function().
8. Missing reset_timer() from GO to CROSSWALK transition
    - Done, corrected the logic accordingly.

# Extent Bugs

The code works fine as per requirements. Please not the extra credit part of the code is not tested actually with a button. It has been tested by connecting a jumper from PTA4 pin to a GND when interrupt is requested. The jumper if floating if the interrupt is not requested. 
