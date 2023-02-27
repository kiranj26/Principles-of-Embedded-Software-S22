# PES_Assignment_2

*Student Name*		: Kiran Narendra Jojare  
*Section*			    : Graduate Student in ECEN 

Code for Assignment 2 for PES ECEN 5813 Spring 2023.   
This assignment revolves around creating LIFO and FIFO based solution using C programming

# Introduction
The second assignment focuses on different ways to implement FIFO and LIFO. For this assignment, I have implemented two objects named. 
  
a) `lllifo`: A linked-list implementation of a LIFO.  
b) `cbfifo`: A circular-buffer implementation of a FIFO.   

Repository contains an optamised version of different enqueue, dequeue and push , pop function for FIFO and LIFO respectievly. Both LIFO and FIFO are implemented using C structures.    

Different test files are created to test robustness of the LIFO and FIFO logic in respective test files as mentioned in `Code Organisation` section. 

Each files are tested with multiple input and results are showned in `Testing Results` section.   

## Usage    
Compile using below command and use executable `assgn2` to run the code
```
$ ./make clean
$ ./make all
$ ./assgn2
``` 
The compilation output looks like as below were everything is compiled with `-Wall -Werror` flags
```
gcc -o main.o -c main.c -Wall -Werror 
gcc -o cbfifo.o -c cbfifo.c -Wall -Werror 
gcc -o test_cbfifo.o -c test_cbfifo.c -Wall -Werror 
gcc -o lllifo.o -c lllifo.c -Wall -Werror 
gcc -o test_lllifo.o -c test_lllifo.c -Wall -Werror 
gcc -o assgn2 main.o cbfifo.o test_cbfifo.o lllifo.o test_lllifo.o 
```

# Code Organisation   

The following code organisation explains the folder structure and file formats used in the project    
The main function calls testing functions which tests the robustness of the functions for FIFO anf LIFO from the respective C files.    

* `main.c`- Main file for PES Assignment 2 which calls testing function.  
* `makefile`        - Make file of final executable.   
* `cbfifo.h`		- FIFO's circular-buffer implementation's header file       
* `cbfifo.c`		- FIFO's circular-buffer implementation's C file containing function logic
* `test_cbfifo.h`	- Header file for testing a FIFO's circular buffer implementation       
* `test_cbfifo.c`	- C file for testing a FIFO's circular buffer implementation 
* `lllifo.h`		- Linked-list implementation of a LIFO header file        
* `lllifo.c`		- Linked-list implementation of a LIFO C file containing function logic     
* `test_lllifo.h`	- Test header file for a LIFO's linked-list implementation       
* `test_lllifo.c`	- Testing the FIFO implementation on a linked list     

# Testing Result
Each files are tested with multiple input and results are showned in this section. All possible happy cases, worst corner cases and improper input handling cases are covered and results are as follows.  

## Autograder Results
The autograder for both CB FIFO and LL LIFO is 100% working as expected without any extent bugs found.


![Screenshot 2023-02-07 at 11 47 21 AM](https://user-images.githubusercontent.com/111842372/217338589-2e74148f-1317-4187-b253-46c65cc9881d.png)

## Own Test Case result
### Result For Testing CBFIFO
![Screenshot 2023-02-07 at 11 40 24 PM](https://user-images.githubusercontent.com/111842372/217454204-069f41c1-6130-40dd-9574-d323eb4dfda6.png)


#### Result For Testing LLLIFO
![Screenshot 2023-02-07 at 11 41 17 PM](https://user-images.githubusercontent.com/111842372/217454161-432a0192-4374-477b-93f1-e1de7398bb02.png)


## Any extent Bugs 

No extent bug to be reported. Code works fine for all the test cases given as per assignment requirements. All the requirements are achieved as seen from autograder test cases and my own tests executed on `asgn2` executable.  

