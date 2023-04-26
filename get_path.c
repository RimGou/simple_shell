#include "shell.h"

/**
 * get_path - get the directories listed in the PATH environment variable
 *
 * Return: pointer to an array of strings containing the directories listed in PATH
 */
char **get_path(void)
{
        char *path_env = getenv("PATH");
        char **path_list;
        char *dir;
        int i, num_dirs;

        if (path_env == NULL)
                return (NULL);

        num_dirs = count_delimiters(path_env, ':') + 1;
        path_list = malloc(sizeof(char *) * (num_dirs + 1));
        if (path_list == NULL)
                return (NULL);

        dir = strtok(path_env, ":");
        for (i = 0; i < num_dirs && dir != NULL; i++)
        {
                path_list[i] = dir;
                dir = strtok(NULL, ":");
        }
        path_list[i] = NULL;

        return (path_list);
}
