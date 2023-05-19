#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

char *get_command_path(char *command, char **path_directories);

int main()
{
    char *command = "ls";
    char *path_directories[] = {"/usr/bin", "/bin", NULL};

    char *command_path;
    pid_t pid;

    command_path = get_command_path(command, path_directories);

    if (command_path == NULL) {
        printf("Command not found\n");
        return (1);
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        char **args = (char **)malloc(sizeof(char *) * 2);
        args[0] = command;
        args[1] = NULL;
        execv(command_path, args);
        printf("Execution failed\n");
        exit(1);
    } else if (pid > 0) {
        /* Parent process */
        wait(NULL);
        printf("Child process complete\n");
    } else {
        /* Fork failed */
        printf("Fork failed\n");
        return (1);
    }

    free(command_path);

    return (0);
}

char *get_command_path(char *command, char **path_directories)
{
    int i = 0;
    char *command_path = malloc(MAX_COMMAND_LENGTH);

    while (path_directories[i] != NULL) {
        snprintf(command_path, MAX_COMMAND_LENGTH, "%s/%s",
                 path_directories[i], command);

        if (access(command_path, X_OK) == 0)
            return (command_path);

        i++;
    }

    free(command_path);
    return (NULL);
}

