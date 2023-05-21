#include <stdio.h>
#include <stdlib.h>

/**
 * main - Simple shell program to handle built-in exit command
 *
 * Return: Always 0
 */
int main(void)
{
	int status;
	char *input = NULL;
	size_t bufsize = 0;

	while (1)
	{
		printf("$ ");
		getline(&input, &bufsize, stdin);

		if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't')
		{
			status = atoi(input + 5);
			free(input);
			exit(status);
		}

		/* Other command handling goes here */
	}

	free(input);
	return (0);
}
