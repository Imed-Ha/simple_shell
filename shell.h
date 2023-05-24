#ifndef SHELL_H
#define SHELL_H
#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
int main(void)
void execute_command(char **args);
void handle_error(const char *message);
void execute_command(char **args);
void handle_error(const char *message);
char *buffer;
char *token;
char **args;
ssize_t read_bytes;
size_t buffer_size = BUFFER_SIZE;
#endif
