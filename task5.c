#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

/**
 * print_environment - Prints the current environment
 */
void print_environment(void);

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	print_environment();

	return (0);
}

/**
 * print_environment - Prints the current environment
 */
void print_environment(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

