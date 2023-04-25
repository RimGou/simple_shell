#include <shell.h>
#define MAX_INPUT_LENGTH 256

int main() 
{
    char *input = malloc(MAX_INPUT_LENGTH);
    char *path = "/bin/";
    int status;

    while (1) {
        printf("#cisfun$ ");
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                exit(0);
            }
            else {
                perror("fgets");
                exit(1);
            }
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "exit") == 0) {
            exit(0);
        }
        char *command = malloc(strlen(path) + strlen(input) + 1);
        strcpy(command, path);
        strcat(command, input);
        if (access(command, X_OK) == -1) {
            printf("./shell: %s: No such file or directory\n", input);
        }
        else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(1);
            }
            else if (pid == 0) {
                char *args[] = {command, NULL};
                char *env[] = {NULL};
                execve(command, args, env);
                perror("execve");
                exit(1);
            }
            else {
                wait(&status);
            }
        }
        free(command);
    }
    free(input);
    return 0;
}
