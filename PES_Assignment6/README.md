[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-8d59dc4de5201274e310e4c54b9627a8934c3b88527886e3b421487c677d23eb.svg)](https://classroom.github.com/a/SozRB9AY)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10708550&assignment_repo_type=AssignmentRepo)
# PES Assignment 6 : Breeakfast Serial
Student name : Kiran Jojare. 

# Introduction
This assignment works on providing UARt based serial command intepreter running over UART0. Serial intepretor is implemented to help QA team to fully excersise new board. A linkedlist queue has been developed and tested throughly. UART0 has been configured for Trasmittion and Reception over UART.   

**Note : Testing of this assignment is done using tera Term Serial termianl**   

Additionally Both extra credit is completed  
* Command loop extended correctly to handle backspace and delete function.
* Command processing extended to handle two extra coands `info` and `Help`.

# Background
The BreakfastSerial project involves setting up an initial command processor over the serial line to allow the development and QA teams to 
fully exercise a new board under development. The project is named after the manager's love for sugar in the morning and will be the first thing done on the board.

To develop the project, the following tasks must be completed:

* Create two linked list queues, one each for the transmit and receive directions. These will be dynamically allocated at initialization time and should have an initial capacity of 256 bytes. The linked lists should be implemented as queues instead of stacks and should store data of type uint8_t. The push and pop functions should be renamed to enqueue and dequeue.
* Develop test code to exercise the linked list queue. The code should run at startup if the DEBUG define is set in the code to ensure the queue buffers are solid.
Configure UART0 and implement interrupt-based code to send and receive data over it. The UART solution should be built on top of the queue implementation.
* Create glue code that ties the UART communication code into the standard C library functions. Once this code is working, calls to printf() or putchar() on the device should result in characters being sent over UART0 to the PC, and calls to getchar() should result in reading a character that the user typed on the PC.
* Develop a command processor that can accept simple interactive commands and take action on the device.  

# Command Line Format and Setting

Command line UART setting is as follows which matches with the requirements.    
Additionally, kindly note that to **test it using Tera Term** with settings defined at follows.  

![image](https://user-images.githubusercontent.com/111842372/230810645-7b32bceb-0f57-4ec6-8d85-a867ce5836a7.png)

Command line inteprets following functions formats:
| Command | Description                                               |
|---------|-----------------------------------------------------------|
| author  | Print the author name                                     |
| SP      | Current Stack Pointer                                     |
| dump `<Start> <Len>`   |  Output a hex dump starting at starting loc |
|         | Start. Always specify Start in hex, specify Len in hex(0xNN) or dec(NN) |
| info    | Print various build info                                  |
| help    | Print help message                                        |    

**Note: New commands can be easily added into the code. Use new command handler add it in comman table mentioned in file `command_processsing.h`** 

# Command Line Output
Each command from command line format has been tested and results of the same is as follows.  
The default output after testing testing is a follows which shows all commands.  
Kindly note that to **test it using Tera Term** with settings defined at follows.

![image](https://user-images.githubusercontent.com/111842372/230812339-dd48beb4-2a32-4409-938d-3e028fae9240.png)

# MACRO Definations
The UART settings can be modified using below parameters mentioned in file `uart.c`
```
// For 8 bit mode of UART
#define UART_EIGHT_DATA_BIT  	(1)
// For Even Parity, make it 1
#define UART_PARITY_ENABLE 		(1)
// For one stop bit, change to 0
#define UART_TWO_STOP_BIT   	(0)				
```

The ASCII representation for accumation of command line is done using following macro definations mentioned in file `command_processing.c`
```
// Define constants for various key codes and characters
#define BACKSPACE_KEY    8
#define DELETE_KEY       127
#define NULL_CHAR        255
#define MAX_INDEX        255
#define WHITESPACE_CHAR  32

// Define a constant for the command index
#define CMD_INDEX        10

// Define a constant for the maximum length of a dump
#define MAX_DUMP_LEN     640

// Define a constant for the base of the hexadecimal number system
#define HEX_BASE         16

// Define ENTER constant as the ASCII character for carriage return
#define ENTER 			'\r'

// Define BACKSPACE constant as the string containing a space and the ASCII character for backspace
#define BACKSPACE 		" \b"

// Define DELETE constant
#define DELETE	 		"\b \b"
```

Feel free to modify the macro definations.  

# Code Organisation


| File Name             | Description                                                           |
|-----------------------|-----------------------------------------------------------------------|
| `llfifo.c`                | Dynamic linked list implementation for a byte queue                   |
| `llfifo.h`                | Header file for `llfifo.c`                                            |
| `command_processing.c`    | Implementation of a command processor for interactive commands        |
| `command_processing.h`    | Header file for `command_processing.c`                                 |
| `hexdump.c`               | Implementation of a function for printing hexadecimal dump of memory  |
| `hexdump.h`               | Header file for `hexdump.c`                                            |
| `test_llfifo.c`           | Automated test code for `llfifo.c`                                     |
| `test_llfifo.h`           | Header file for `test_llfifo.c`                                        |
| `uart.c`                  | UART configuration and implementation of interrupt-based transmit and receive functionality |
| `uart.h`                  | Header file for `uart.c`                                               |
| `main.c`                  | Main function that ties everything together and implements the command processor 

# Extra Credit
## Extra Credit 1 : BACKSPACE and DELETE 
Backspace and Delete has been incorporated in line accumulation. Functionality has been verified and tested.

## Extra Credit 2 : Help and Info
The additional `help` and `info` command has been implemented vaified and tested. See th command line output section above.
The `makefile.def` is added in the repo and appropriate flags are set in the project to print `info` command. Following flags are added to 
miscellenious C/C++ settings of the project.  
```
-c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections $(BUILD_GIT_COMMIT_DEF) $(BUILD_TIMESTAMP_DEF) $(BUILD_GIT_TAG_DEF) $(BUILD_MACHINE_DEF)
```

# Extent Bugs
No extent bugs found in code file. The code is performing as expected from assignment requirements. Only bug found    
is when same code is executed in MCU Expresso serial termianal since the ASCII sequense of characters are different on this terminal.

