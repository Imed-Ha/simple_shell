#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024
void execute_command(char *command);
void handle_error(const char *message);

/**
 * main - Simple UNIX command line interpreter
 *
 * Return: Always 0
 */
int main(void)
{
char *buffer;
ssize_t read_bytes;
size_t buffer_size = BUFFER_SIZE;

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
execute_command(buffer);
}
}

free(buffer);
return (0);
}

/**
 * execute_command - Executes a command using fork and execve
 * @command: The command to execute
 */
void execute_command(char *command)
{
pid_t pid = fork();

if (pid == -1)
{
handle_error("fork error");
}
else if (pid == 0)
{
if (execve(command, (char *const *)NULL, (char *const *)NULL) == -1)
{
perror("execve error");
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

