#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 on success
 */
int main(void)
{
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    char **args = NULL;
    int status;

    /* Install signal handler for SIGINT (Ctrl+C) */
    signal(SIGINT, signal_handler);

    /* Display prompt and wait for user input */
    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#cisfun$ ", 9);
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        /* Remove trailing newline character */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Parse command line and execute command */
        args = parse_line(line);
        status = execute_command(args);

        /* Free memory allocated by parse_line() */
        free(args);

        /* Handle errors */
        if (status == 2)
            perror("Error");

    }

    free(line);
    exit(EXIT_SUCCESS);
}

