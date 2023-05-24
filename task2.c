#include "shell.h"

/**
 * _myexit - exits the shell
 * @information: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if information.argv[0] != "exit"
 */
int _myexit(information_t *information)
{
	int exitcheck;

	if (information->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(information->argv[1]);
		if (exitcheck == -1)
		{
			information->status = 2;
			print_error(information, "Illegal number: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(information_t *information)
{
	char *st, *z, buffer[1024];
	int chdir_ret;

	st = getcwd(buffer, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		z = _getenv(information, "HOME=");
		if (!z)
			chdir_ret = /* TODO: what should this be? */
				chdir((z = _getenv(information, "PWD=")) ? z : "/");
		else
			chdir_ret = chdir(z);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((z = _getenv(information, "OLDPWD=")) ? z : "/");
	}
	else
		chdir_ret = chdir(information->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(information_t *information)
{
	char **arg_array;

	arg_array = information->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

