#include "shell.h"

/**
 * check_for_builtins - checks if the command is a built-in and executes it
 * @args: double pointer to an array of arguments passed to the shell
 * @env: pointer to the environment variables
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int check_for_builtins(char **args, char **env)
{
    if (_strcmp(args[0], "exit") == 0)
    {
        free_args(args);
        free_env(env);
        exit(EXIT_SUCCESS);
    }
    else if (_strcmp(args[0], "env") == 0)
    {
        print_env(env);
        return (1);
    }
    return (0);
}

