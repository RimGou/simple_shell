#include "shell.h"
/**
 * ext - execute an external command
 * @args: array of arguments including command to be executed
 * @env: array of environment variables
 * Return: 1 on success, 0 on failure
 */
int ext(char **args, char **env)
{
	pid_t child_pid;
	int status;
	char *path = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (0);
	}
	else if (child_pid == 0)
	{
		path = find_path(args[0], env);
		if (path == NULL)
		{
			print_error(args[0], "not found");
			free(args);
			exit(127);
		}
		if (execve(path, args, env) == -1)
		{
			perror("Error");
			free(path);
			free(args);
			exit(126);
		}
		free(path);
		free(args);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

