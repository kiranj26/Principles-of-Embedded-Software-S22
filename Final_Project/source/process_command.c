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
 * @file process_command.h
 * @brief C file used for processing user command and reading it from UART
 *
 * This C file contains declarations for functions that process user commands.
 *
 *​ ​@author​ ​Kiran
​ ​*​ ​@date​ ​May 04​ 2023
​ ​*​ ​@version​ 1.0
 */


#include "process_command.h"
#include "state_machine.h"
#include "wdt.h"
#include "test_sht21.h"

#define Hexdump_max_size 	(640)

// Warning temperature and CO values
#define WARNING_TEMP 		(26)
#define WARNING_CO 			(350)

// Danger temperature and CO values
#define DANGER_TEMP 		(30)
#define DANGER_CO 			(800)

// Maximum PWM value
#define MAX_PWM				(255)

// 100ms in units of 10ms
#define HUNDRED_MS			(10)

// Define command handler function pointer
typedef void (*command_handler_t)(int, char *argv[]);

// Define command handler functions
void handle_author(int argc, char *argv[]);
void handle_help(int argc, char *argv[]);
void handle_temp(int argc, char *argv[]);
void handle_hum(int argc, char *argv[]);
void handle_test(int argc, char *argv[]);
void handle_statemachine(int argc, char *argv[]);

// Command Table struct
typedef struct
{
	const char *name;
	command_handler_t handler;
	const char *help_string;
} command_table_t;

// Array of commands
static const command_table_t commands[] =
{
	{ "author"			, 	handle_author		, "author help" 	},
	{ "help"			, 	handle_help			, "command help"	},
	{ "temp"			,	handle_temp			, "temperature help"},
	{ "hum"				,	handle_hum			, "humidity help"	},
	{ "test"			,	handle_test			, "test help"},
	{ "start"			,	handle_statemachine	, "State Machine help"},
};

// Number of commands in the command table
static const int num_commands = sizeof(commands) / sizeof(command_table_t);

// Command handler function to print the name of the author
void handle_author(int argc, char *argv[])
{
	printf("Kiran Narendra Jojare \n\r");
	printf("? ");
}

// Command handler function to run various tests
void handle_test(int argc, char *argv[])
{
	// Test PWM with different values
#ifdef DEBUG
	printf("Testing PWM with different values : \n\r");

	test_pwm();
	printf("PWM Tested Successfully! \n\r\n\r");
#endif

	// Test CBFIFO with different values
#ifdef DEBUG
	printf("Testing CBFIFO with different values : \n\r");
	// test_cbfifo();
	printf("CBFIFO Tested Successfully! \n\r\n\r");
#endif

	// Test SHT21 to read value 10 times
#ifdef DEBUG
	printf("Testing SHT21 to read value 10 times : \n\r");

	test_sht21();
	printf("SHT21 Sensor Tested Successfully! \n\r\n\r");
#endif
	PRINTF("? ");
}

// Command handler function to read and print the humidity
void handle_hum(int argc, char *argv[])
{
	// Set I2C1 flags
	I2C1_Set_Flags();
	// Read humidity value
	float hum= read_humidity();
	// Print humidity value
	printf("Humidity is: %.3f \n\r",hum);
	printf("? ");
}

// Command handler function to read and print the temperature
void handle_temp(int argc, char *argv[])
{
	// Set I2C1 flags
	I2C1_Set_Flags();
	// Read temperature value
	float temp=read_temperature();
	// Print temperature value
	printf("Temperature is: %.3f \n\r",temp);
	printf("? ");
}

//  This function starts the state machine and loops infinitely,
//  refreshing the watchdog timer and running the state machine
//  at each iteration.
void handle_statemachine(int argc, char *argv[])
{
	// Print a message indicating that the state machine has been enabled
	PRINTF("\n\r+---------------------------------------+\n\r");
	PRINTF("\n\r|         State Machine Enabled         |\n\r");
	PRINTF("\n\r+---------------------------------------+\n\r");

	// Run the state machine infinitely, refreshing the watchdog timer at each iteration
	while(1)
	{
		Refresh_wdt();
		state_machine();
	}
}

//  This function creates a 100 ms delay.

void delay_100ms(void)
{
	// Loop for a large number of iterations to create a 100 ms delay
	for(int i=0;i<100000;i++);
}

void handle_help(int argc, char *argv[])
{
	printf("+-----------------------------------------------------------------+\n\r");
	printf("|                          COMMAND LIST                           |\n\r");
	printf("+-----------------------------------------------------------------+\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("+------------+---------------------------------------------------+\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| temp       | Prints Surrounding Temperature                    |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| hum        | Prints Surrounding Humidity                       |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| start      | Starts State Machine                                 |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| test       | Starts hardware and software testing              |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| help       | Shows possible user options                       |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("| author     | Author Name                                       |\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("+------------+---------------------------------------------------+\n\r\n\r");
	delay_100ms();
	delay_100ms();
	delay_100ms();
	printf("? ");
}

void process_command(char *input)
{
    // Find the end of the input string
    char *end;
    for (end = input; *end != '\0'; end++)
    {
        // Do nothing, just loop until we reach the end of the string
    }

    // Initialize variables for parsing the input
    bool in_token = false;
    char *argv[10];
    int argc = 0;
    memset(argv, 0, sizeof(argv));

    // Parse the input into arguments
    char *p;
    for (p = input; p < end; p++)
    {
        switch (in_token)
        {
        case false:
            // We're not currently in a token
            if ((*p != ' ') || (*p != '\t'))
            {
                // This is the start of a new token
                argv[argc] = p;
                argc++;
                in_token = true;
            }
            break;
        case true:
            // We're currently in a token
            if ((*p == ' ') || (*p == '\t'))
            {
                // This is the end of the current token
                *p = '\0';  // Replace the whitespace with a null terminator
                in_token = false;
            }
            break;
        }
    }

    // Add a null terminator to the end of the argument list
    argv[argc] = NULL;

    // If there are no arguments, return
    if (argc == 0)
    {
        return;
    }

    // Check each registered command for a match with the input
    for (int i = 0; i < num_commands; i++)
    {
        if (strcasecmp(argv[0], commands[i].name) == 0)
        {
            // If we find a matching command, call its handler function
            commands[i].handler(argc, argv);
            break;
        }
        if (i == (num_commands - 1))
        {
            // If we've checked all the commands and none match, print an error message
            printf("Unknown Command :");
            for (int j = 0; j < argc; j++)
            {
                printf(" %s", argv[j]);
            }
            printf("\n\r? ");
        }
    }
}
