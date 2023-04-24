#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int main(void)
{
    char *line;
    int status;

    do {
        printf("#cisfun$ ");
        line = read_line();
        status = execute_line(line);
        free(line);
    } while (status);

    return EXIT_SUCCESS;
}

