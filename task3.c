#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

extern char **environ;

/**
 * get_full_path - Get the full path of a command by searching the directories in PATH
 * @command: The command to search for
 *
 * Return: (char *) The full path of the command if found, NULL otherwise
 */
char *get_full_path(char *command) {
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	
	while (token != NULL) {
		char *full_path = malloc(strlen(token) + strlen(command) + 2);
		
		sprintf(full_path, "%s/%s", token, command);
		
		if (access(full_path, X_OK) == 0) {
			free(path_copy);
			return (full_path);
		}
		
		free(full_path);
		token = strtok(NULL, ":");
	}
	
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Execute a command with the given arguments
 * @command: The command to execute
 * @arguments: An array of arguments for the command
 *
 * Return: (int) The exit status of the command, or -1 on failure
 */
int execute_command(char *command, char **arguments) {
	pid_t pid = fork();
	
	if (pid == -1) {
		perror("fork");
		return (-1);
	}
	
	if (pid == 0) {
		// Child process
	char *full_path = get_full_path(command);
	
	if (full_path == NULL) {
		fprintf(stderr, "Command not found: %s\n", command);
		exit(127);
	}
	
	execve(full_path, arguments, environ);
	perror("execve");
	exit(EXIT_FAILURE);
	} else {
		// Parent process
	int status;
	
	waitpid(pid, &status, 0);
	
	if (WIFEXITED(status)) {
		return (WEXITSTATUS(status));
	}
	
	return (-1);
	}
}

/**
 * main - Entry point of the program
 *
 * Return: (int) Always 0
 */
int main(void) {
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	
	while (1) {
		printf("$ ");
		
		if (fgets(command, sizeof(command), stdin) == NULL) {
			printf("\n");
			break;
		}
		
		// Remove trailing newline character
	command[strcspn(command, "\n")] = '\0';
	
	if (strcmp(command, "exit") == 0) {
		break;
	}
	
	char *token = strtok(command, " ");
	int arg_count = 0;
	
	while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
		arguments[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	
	arguments[arg_count] = NULL;
	
	if (arg_count > 0) {
		int status = execute_command(arguments[0], arguments);
		
		if (status == -1) {
			printf("Failed to execute command.\n");
		}
	}
	}
	
	return (0);
}

