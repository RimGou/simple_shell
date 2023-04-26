#include "shell.h"
/**
 * execute_command - Executes the command passed as argument
 * @cmd: A struct containing the command and its arguments
 * @env: The environment variables
 *
 * Return: The status code of the command execution
 */
int execute_command(command_t cmd, char **env)
{
    if (is_builtin(cmd.cmd))
        return (execute_builtin(cmd, env));
    else
        return (ext(cmd, env));
}

