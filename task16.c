#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - Execute a single command.
 *	@command: The command to execute.
 *
 * Return: (void)
 */
void execute_command(const char *command)
{
	/* Implement the logic to execute a single command here */
	/* You can use system(), execvp(),*/
	/* or any other method to execute the command */
	/* This function should handle executing the command,*/
	/* and any related error handling */
	system(command);
}

/**
 * execute_commands_from_file - Execute commands from a file.
 *	@filename: The name of the file containing commands.
 *
 * Return: (void)
 */
void execute_commands_from_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	char command[MAX_COMMAND_LENGTH];

	if (file == NULL)
	{
		fprintf(stderr, "Error: Cannot open file %s\n", filename);
		exit(1);
	}

	while (fgets(command, sizeof(command), file) != NULL)
	{
		command[strcspn(command, "\n")] = '\0'; /* Remove newline character */
		execute_command(command);
	}

	fclose(file);
}

/**
 * main - Entry point of the program.
 *	@argc: The number of command-line arguments.
 *	@argv: An array containing the command-line arguments.
 *
 * Return: (int) 0 on success.
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	execute_commands_from_file(argv[1]);

	return (0);
}

