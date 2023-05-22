#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - Execute a single command.
 *	@command: The command to execute.
 *
 * Return: (void)
 */
void	execute_command(const char *command)
{
	/* Implement the logic to execute a single command here */
	/* You can use system(), execvp(),*/
	/* or any other method to execute the command */
	/* This function should handle executing the command,*/
	/*  and any related error handling */
	(void)command;	/* To suppress the unused parameter warning */
}

/**
 * execute_commands - Execute a series of commands separated by semicolons.
 *	@input: The input string containing commands.
 *
 * Return: (void)
 */
void	execute_commands(const char *input)
{
	char	*commands[MAX_COMMANDS];
	int	num_commands = 0;
	int	i;	/* Move the declaration outside the loop for C89 compatibility */

	/* Tokenize the input based on the semicolon separator */
	char	*token = strtok((char *)input, ";");

	while (token != NULL && num_commands < MAX_COMMANDS)
	{
		commands[num_commands] = token;
		num_commands++;
		token = strtok(NULL, ";");
	}

	/* Execute each command in the order they appear */
	for (i = 0; i < num_commands; i++)
	{
		execute_command(commands[i]);
	}
}

/**
 * main - Entry point of the program.
 *
 * Return: (0) Always.
 */
int	main(void)
{
	char	input[MAX_COMMAND_LENGTH];

	printf("Shell 1.0\n");

	while (1)
	{
		printf("Enter commands: ");
		fgets(input, sizeof(input), stdin);

		/* Remove newline character from the input */
		input[strcspn(input, "\n")] = '\0';

		execute_commands(input);
	}

	return (0);
}

