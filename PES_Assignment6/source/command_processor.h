
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
 * @file 		command_processor.h
 * @brief 		Header file for command processing
 *
 * This header file contains function declarations for command processing.
 *
 * @author 		Kiran Jojare
 * @date 		April 9 2022
 * @version 	1.0
 * @reference
 * none
*/

#ifndef _COMMAND_PROCESSOR_H_
#define _COMMAND_PROCESSOR_H_


/**
 * @brief Accumulates the user input until a newline character is received.
 *
 * This function reads characters from the UART input buffer and accumulates them in a buffer
 * until a newline character is received. The accumulated string is then returned.
 *
 * @return The accumulated string
 */
char* accumulate_cmd();

/**
 * @brief Processes a command string.
 *
 * This function parses a command string and calls the appropriate command handler function
 * based on the command entered.
 *
 * @param input The command string to be processed
 *
 * @return none
 */
void process_cmd(char *input);

/**
 * @brief Handles the "author" command.
 *
 * This function prints the name of the author of the command processor.
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 *
 * @return none
 */
void handle_author(int argc, char *argv[]);

/**
 * @brief Handles the "dump" command.
 *
 * This function performs a hexadecimal dump of a given memory region.
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 *
 * @return none
 */
void handle_dump(int argc, char *argv[]);

/**
 * @brief Handles the "info" command.
 *
 * This function prints information about the command processor.
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 *
 * @return none
 */
void handle_info(int argc, char *argv[]);

/**
 * @brief Handles the "help" command.
 *
 * This function prints the list of available commands and their descriptions.
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 *
 * @return none
 */
void handle_help(int argc, char *argv[]);

/**
 * @brief Handles unknown commands.
 *
 * This function is called when an unknown command is entered.
 *
 * @return none
 */
void handle_unknown();

/**
 * @brief Handles the "SP" command.
 *
 * This function performs a stack pointer dump.
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 *
 * @return none
 */
void handle_SP(int argc, char *argv[]);

#endif /* _COMMAND_PROCESSOR_H_ */
