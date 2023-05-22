#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int change_directory(const char *path)
{
    int status = chdir(path);

    if (status == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

char *get_current_directory()
{
    char *cwd = malloc(BUFSIZE);

    if (cwd == NULL)
    {
        perror("malloc");
        return (NULL);
    }
    if (getcwd(cwd, BUFSIZE) == NULL)
    {
        perror("getcwd");
        free(cwd);
        return (NULL);
    }
    return (cwd);
}

int cd_command(const char *directory)
{
    char *path;
    char *cwd;
    
    if (directory == NULL)
    {
        path = getenv("HOME");
        if (path == NULL)
        {
            fprintf(stderr, "cd: No home directory\n");
            return (1);
        }
    }
    else if (strcmp(directory, "-") == 0)
    {
        path = getenv("OLDPWD");

        if (path == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return (1);
        }
        printf("%s\n", path);
    }
    else
    {
        path = (char *)directory;
    }

    cwd = get_current_directory();

    if (cwd == NULL)
    {
        return (1);
    }

    if (change_directory(path) == 0)
    {
        setenv("OLDPWD", cwd, 1);
        free(cwd);
        cwd = get_current_directory();

        if (cwd == NULL)
        {
            return (1);
        }

        setenv("PWD", cwd, 1);
        free(cwd);

        return (0);
    }
    else
    {
        free(cwd);
        return (1);
    }
}

int main(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t read_chars;

    while (1)
    {
        printf("$ ");
        read_chars = getline(&line, &bufsize, stdin);
        
        if (read_chars == -1)
        {
            break;
        }

        if (line[read_chars - 1] == '\n')
        {
            line[read_chars - 1] = '\0';
        }

        if (strcmp(line, "exit") == 0)
        {
            break;
        }
        else if (strncmp(line, "cd ", 3) == 0)
        {
            return (cd_command(line + 3));
        }
        else
        {
            printf("Command not found: %s\n", line);
        }
    }

    free(line);
    return (0);
}
