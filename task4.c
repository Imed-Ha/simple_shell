#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void exit_shell();

int main()
{
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("Shell > ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        /* Remove the newline character at the end of the input */
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            exit_shell();
            break;
        }

        /* Handle other commands */
        /* ... */
    }

    return (0);
}

void exit_shell()
{
    printf("Exiting the shell.\n");
    exit(0);
}

