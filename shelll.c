#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point of the shell
 *
 * Return: (0) Always
 */
int main(void)
{
	char *command;
	char buffer[BUFFER_SIZE];
	ssize_t read_bytes;

	while (1)
	{
		printf("$ ");
		read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (read_bytes == 0)
		{
			printf("\n");
			break;
		}

		buffer[read_bytes - 1] = '\0'; /* Remove newline character */
		command = buffer;
		if (execve(command, &command, NULL) == -1)
		{
			perror("execve");
			printf("Command not found: %s\n", command);
		}
	}

	return (0);
}

