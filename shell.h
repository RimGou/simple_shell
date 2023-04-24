#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Function prototypes */
void display_prompt(void);
char *read_command(void);
char **parse_command(char *command);
int execute_command(char **args);
void free_memory(char *command, char **args);

/* Constants */
#define PROMPT "> "

/* Main function */
int main(void)
{
    char *command;
    char **args;
    int status;

    while (1) {
        display_prompt();
        command = read_command();
        args = parse_command(command);
        status = execute_command(args);
        free_memory(command, args);
        if (status == -1) {
            break;
        }
    }

    return 0;
}

/* Function to display prompt */
void display_prompt(void)
{
    printf(PROMPT);
}

/* Function to read command */
char *read_command(void)
{
    char *command = NULL;
    size_t size = 0;
    getline(&command, &size, stdin);
    return command;
}

/* Function to parse command */
char **parse_command(char *command)
{
    char **args = malloc(2 * sizeof(char *));
    args[0] = command;
    args[1] = NULL;
    return args;
}

/* Function to execute command */
int execute_command(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, NULL) == -1) {
            perror("execve");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking */
        perror("fork");
    } else {
        /* Parent process */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/* Function to free memory */
void free_memory(char *command, char **args)
{
    free(command);
    free(args);
}

#endif /* SHELL_H */
