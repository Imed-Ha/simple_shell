#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Reads the command entered by the user
 * @buffer: Buffer to store the command
 * Return: Number of characters read
 */
ssize_t read_command(char *buffer)
{
	ssize_t read_chars;

	read_chars = read(0, buffer, BUFFER_SIZE); /* Read command from stdin */

	if (read_chars == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	if (read_chars == 0) /* Check for end of file (Ctrl+D) */
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	buffer[read_chars - 1] = '\0'; /* Remove newline character */

	return (read_chars);
}

/**
 * execute_command - Executes the command
 * @command: Command to execute
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	char **argv = malloc(sizeof(char *) * 2); /* Allocate memory for argv */
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	argv[0] = command;
	argv[1] = NULL;

	child_pid = fork(); /* Create child process */

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) /* Child process */
	{
		if (execve(command, argv, NULL) == -1) /* Execute the command */
		{
			perror("execve"); /* execve should not return */
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for the child process to complete */
		free(argv); /* Free dynamically allocated memory */
	}
}

/**
 * main - Simple shell program
 * Return: Always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t read_chars __attribute__((unused));

	while (1)
	{
		display_prompt();

		read_chars = read_command(buffer);

		execute_command(buffer);
	}

	return (0);
}