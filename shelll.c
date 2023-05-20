#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * read_command - Read a command from the user.
 *
 * Returns:
 *   (char *) The command entered by the user.
 */
char *read_command(void)
{
        char *buffer = NULL;
        size_t bufsize = 0;

        printf("$ "); /* Display the prompt */

        if (getline(&buffer, &bufsize, stdin) == -1)
        {
                if (feof(stdin))
                {
                        printf("\n");
                        exit(EXIT_SUCCESS); /* Handle end of file (Ctrl+D) */
                }
                else
                {
                        perror("Error reading command");
                        exit(EXIT_FAILURE);
                }
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove the newline character */
        return buffer;
}

/**
 * execute_command - Execute a command.
 * @command: The command to execute.
 *
 * Returns:
 *   (void) None.
 */
void execute_command(char *command)
{
        if (execve(command, NULL, NULL) == -1)
        {
                perror("Command execution error");
                exit(EXIT_FAILURE);
        }
}

/**
 * main - Entry point of the program.
 *
 * Returns:
 *   (int) 0 on success.
 */
int main(void)
{
        char *command;

        while (1)
        {
                command = read_command();
                execute_command(command);
                free(command);
        }

        return (0);
}

