#include "shell.h"
/**
 * parse_line - Tokenizes a command line into separate arguments
 * @line: The command line to be tokenized
 *
 * Return: A struct containing the command and its arguments
 */
command_t parse_line(char *line)
{
    char *token;
    int i = 0;
    command_t cmd;

    cmd.args = malloc(MAX_ARGS * sizeof(char *));
    if (!cmd.args)
    {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \n");
    while (token)
    {
        if (i == 0)
            cmd.cmd = token;
        cmd.args[i++] = token;
        token = strtok(NULL, " \n");
    }
    cmd.args[i] = NULL;

    return (cmd);
}

