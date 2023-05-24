#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @information: struct address
 *
 * Return: (1) perfect, (0) otherwise
 */
int interactive(information_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

/**
 * is_D - checks if character is a delimeter
 * @x: the char to check
 * @D: the delimeter string
 * Return: (1) perfect, (0) if false
 */
int is_D(char x, char *D)
{
	while (*D)
		if (*D++ == x)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @x: The character to input
 * Return: (1) if x is alphabetic, (0) otherwise
 */

int _isalpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @st: the string to be converted
 * Return: (0) if no numbers in string, converted number otherwise
 */

int _atoi(char *st)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; st[i] != '\0' && flag != 2; i++)
	{
		if (st[i] == '-')
			sign *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (st[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

