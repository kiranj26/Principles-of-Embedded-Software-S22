/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Kiran Jojare
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Kiran Jojare​ ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file 	command_processor.c
 * @brief 	Header file for command processing
 * This C file contains function definatons for command processing.
 *
 * @author Kiran Jojare
 * @date April 9 2022
 * @version 1.0
 * @reference
 * Using Custom Build Steps with Eclipse Auto-generated Makefiles
 * https://embeddedartistry.com/blog/2019/02/18/using-custom-build-steps-with-eclipse-auto-generated-makefiles/
 * Note  : Lots of functions are taken directly from professor's lecture slides and modified accordngly
 * Additionally thanks to Daniel Mendez for explainning the concepts of preprosessor macro's used
 * to print info command
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "MKL25Z4.h"

#include "uart.h"
#include "hexdump.h"
#include "command_processor.h"

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

// LLLIFO size of 256 elements
#define SIZE			256

// preprocessor Macros for the command info
#ifndef VERSION_GIT_COMMIT_HASH
#define VERSION_GIT_COMMIT_HASH 	"VERSION_GIT_COMMIT_HASH FLAG NOT SET"
#endif

#ifndef VERSION_GIT_TAG
#define VERSION_GIT_TAG				"VERSION_GIT_TAG FLAG FLAG NOT SET"
#endif

#ifndef VERSION_BUILD_MACHINE
#define VERSION_BUILD_MACHINE		"VERSION_BUILD_MACHINE FLAG NOT SET"
#endif

#ifndef VERSION_BUILD_TIMESTAMP
#define VERSION_BUILD_TIMESTAMP		"VERSION_BUILD_TIMESTAMP FLAG NOT SET"
#endif

// Enumeration of the command argument indexes
enum {
    CMD_NAME,
    ADDRESS,
    LENGTH,
};

// Typedef for command handler function
typedef void (*cmd_handler_t)(int, char *argv[]);

// Structure for command table
typedef struct {
    const char      *cmd_name;    	// Name of the command
    cmd_handler_t   cmd_handler; 	// Function pointer to the command handler
    const char      *help_text;   	// Help text for the command
} cmd_table_t;

// Array of command structures
static const cmd_table_t cmd_table[] = {
    {"author",  handle_author,  "\n\t\tPrint the author name\n\r"},
    {"SP",      handle_SP,      "\n\t\t\tCurrent Stack Pointer\n\r"},
    {"dump",    handle_dump,    "<Start> <Len>\n\tOutput a hex dump starting at starting loc Start.\n\r\t"
                                "\t\t\tAlways specify Start in hex, specify Len in hex(0xNN) or dec(NN)\n\r"},
    {"info",    handle_info,    "\n\t\t\tPrint various build info\n\r"},
    {"help",    handle_help,    "\n\t\t\tPrint help message\n\r"},
};

// Formulae to calculate no of commands
static const int num_cmds = sizeof(cmd_table) / sizeof(cmd_table_t);

// Array to store command string after acummulating command line string
char cmd_str[SIZE];

char * accumulate_cmd() {
    // a static char array to store the accumulated input
    static char cmd_str[SIZE];
    // set all elements of cmd_str to 0
    memset(cmd_str, 0, sizeof(cmd_str));

    // keep track of how many characters are in the input
    int count = 0;
    // read the first character from input
    char c = getchar();

    // keep reading input until the user hits enter
    while (c != ENTER)
    {
        // if user enters backspace
        if ( (c == BACKSPACE_KEY) && (count > 0) )
        {
            // move the cursor back one position
            printf(BACKSPACE);
            count--;
            // set the deleted character to null character
            cmd_str[count] = 0;
        }
        // if user enters delete
        else if ( (c == DELETE_KEY) && (count > 0) )
            {
                // move the cursor back one position
                printf(DELETE);
                count--;
                // set the deleted character to null character
                cmd_str[count] = 0;
            }
        // if user enters a valid character
        else if (c != NULL_CHAR && c != BACKSPACE_KEY && c != DELETE_KEY && count < MAX_INDEX)
        {
            // add the character to the input string and increment count
            cmd_str[count++] = c;
        }

        // read the next character from input
        c = getchar();
    }

    // add null character at the end of the input string
    cmd_str[count] = '\0';
    // return a pointer to the accumulated input string
    return cmd_str;
}


void process_cmd(char *input)
{
    // Initialize variables
	char *args[CMD_INDEX] = { 0 };
	int argc = 0;

    // Tokenize input string and store tokens in args array
	char *token = strtok(input, " ");
	while (token != NULL && argc < CMD_INDEX) {
		args[argc++] = token;
		token = strtok(NULL, " ");
	}

    // If no tokens were found, return without further processing
	if (argc == 0) {
		return;
	}

    // Search for command in cmd_table and call the corresponding command handler function
	for (int i = 0; i < num_cmds; i++) {
		if (strcasecmp(args[CMD_NAME], cmd_table[i].cmd_name) == 0) {
			cmd_table[i].cmd_handler(argc, args);
			return;
		}
	}

    // If command was not recognized, call function to handle unknown commands
	handle_unknown(argc, args);
}

void handle_author(int argc, char *argv[])
{
	// Prints the name of the author
    printf("\n\rWritten by: \033[1mKiran Jojare\033[0m\n\r");
}

void handle_dump(int argc, char *argv[])
{
    // Extracts the starting address from the command line argument
    char *start_address = (char *)strtol(argv[ADDRESS], 0, HEX_BASE);
    int len = 0;

    // Extracts the length of the dump from the command line argument
    if ((*(argv[LENGTH] + 1) == 'x') || (*(argv[LENGTH] + 1) == 'X'))
        len = strtol(argv[LENGTH], 0, HEX_BASE);
    else
        len = atoi(argv[LENGTH]);

    // Validates the length of the dump
    if (len < 0 || len > MAX_DUMP_LEN)
        printf("\n\rInvalid Length. Maximum allowed length is 640\n\r");
    else
        // Dumps the memory
        hexdump(start_address, len);
}

void handle_help(int argc, char *argv[])
{
	// Print header for help menu
	printf("\n\t\t\t\033[1mBreakfast Serial Command Processor\033[0m\n\r\n\r");

	// Loop through the command table and print each command's name and help text
	for (int i = 0; i < num_cmds; i++) {
		printf(" \t %s  %s", cmd_table[i].cmd_name, cmd_table[i].help_text);
	}

	// Print newline to separate the help menu from the next command prompt
	printf("\n\r");
}

void handle_info(int argc, char *argv[])
{
	#ifdef DEBUG
		printf("\n\r\t\033[1mBuild Information\033[0m\n\r");

		printf("Version %s built on %s at %s\n\rCommit %s\n\r",
				VERSION_GIT_TAG,VERSION_BUILD_MACHINE, VERSION_BUILD_TIMESTAMP, VERSION_GIT_COMMIT_HASH);
	#endif
}

void handle_unknown(int argc, char *argv[])
{
    // Print error message when command is unknown
    printf("\n\rUnknown Command: ");
    for(int i = 0; argv[CMD_NAME][i] != '\0'; i++)
    {
        printf("%c", argv[CMD_NAME][i]);
    }
    printf("\n\r");
}

// Credit : GCC ARM: get actual value from SP register
// https://stackoverflow.com/questions/45658372/gcc-arm-get-actual-value-from-sp-register
//
void handle_SP(int argc, char *argv[])
{
    // Get the current stack pointer and print it in hexadecimal format
    uint32_t sp = __get_MSP();
    // Printing in requested format as per assignment
    printf("\n\r0x%08X\n\r", sp);
}
