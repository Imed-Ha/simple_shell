#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"

void execute_command(char **args);
void handle_error(const char *message);

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *buffer;
	char *token;
	char **args;
	ssize_t read_bytes;
	size_t buffer_size = BUFFER_SIZE;
	int i = 0;

	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
	{
		handle_error("malloc error");
	}

	while (1)
	{
		printf("#cisfun$ ");
		read_bytes = getline(&buffer, &buffer_size, stdin);

		if (read_bytes == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				handle_error("getline error");
			}
		}
		else
		{
			buffer[read_bytes - 1] = '\0'; /* Remove the trailing newline character */

			args = malloc(buffer_size * sizeof(char *));
			if (args == NULL)
			{
				handle_error("malloc error");
			}

			token = strtok(buffer, TOKEN_DELIMITERS);
			i = 0;
			while (token != NULL)
			{
				args[i] = token;
				token = strtok(NULL, TOKEN_DELIMITERS);
				i++;
			}
			args[i] = NULL;

			execute_command(args);

			free(args);
		}
	}

	free(buffer);
	return (0);
}

/**
 * execute_command - Executes a command using fork and execvp
 * @args: The arguments for the command
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		handle_error("fork error");
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * handle_error - Prints an error message and exits with failure status
 * @message: The error message to display
 */
void handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

