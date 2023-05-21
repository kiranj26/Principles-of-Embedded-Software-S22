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
​ ​*​ ​@file​_name     Accumulate_Line.c
​ ​*​ ​@introduction  This file contains the implementation of a function that processes input command from user
 *                The input_process_command() function reads input from user and processes the command as per user input.
​ ​*​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
*/

#include"Accumulate_Line.h"

#define Carriage_Return 	(0X0D)		//Hex ASCII value for the Enter key
#define Backspace      		(0X08)		//Hex ASCII value for the Backspace key
#define buffer_size     	(2000)		//Defines the size of the buffer used for input data


void read_and_process_command()
{
    char buffer[buffer_size];			//Declare input buffer
    char character;						//Declare variable for received character
    int i = 0;							//Initialize index for input buffer

    while (1)							//Run loop until break
    {
        while ((cbfifo_length(receiver) == 0))	//Wait until a character is received
        {
            ;
        }
        cbfifo_dequeue(&character, 1, receiver);	//Read the received character
        putchar(character);						//Echo the received character back to the terminal

        if (character == Carriage_Return)		//Check if the user has pressed Enter
        {
            buffer[i] = '\0';					//If Enter is pressed, terminate the string
            break;								//Exit the loop
        }
        else if (character == Backspace)		//Check if the user has pressed Backspace
        {
            //If Backspace is pressed, delete the last character from the terminal and input buffer
            i--;
            printf(" \b");						//Print a blank space and move the cursor back one position
        }
        else
        {
            buffer[i] = character;				//Store the received data in the input buffer
            i++;								//Increment the buffer index to store the next character
        }
    }

    printf("\n\r");								//Print a new line and return to the head of the terminal
    process_command(buffer);					//Call the function to process the user's input
}
