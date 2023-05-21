#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * _strlen - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len])
		len++;

	return (len);
}

/**
 * _strcmp - Compare two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if strings are equal, negative value if s1 < s2,
 *         positive value if s1 > s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _getline - Read a line of input from the user.
 * @buffer: Pointer to a buffer to store the line.
 * @size:   Pointer to the size of the buffer.
 *
 * Return: Number of characters read (including newline), or -1 on failure.
 */
ssize_t _getline(char **buffer, size_t *size)
{
	ssize_t read_chars = getline(buffer, size, stdin);

	if (read_chars == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (read_chars);
}

/**
 * execute_command - Execute a command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		char **argv = malloc(sizeof(char *) * 2);
        
		if (argv == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Simple Shell entry point.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	while (1)
	{
		printf("$ ");
		_getline(&input, &bufsize);

		if (input[0] == '\n')
			continue;

		input[_strlen(input) - 1] = '\0';

		if (_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		execute_command(input);
	}

	free(input);
	return (0);
}
