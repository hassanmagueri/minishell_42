#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char **get_input(char *input) {
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char *delimiter = " \t\n";
    char *token = strtok(input, delimiter);
    int i = 0;

    while (token != NULL) {
        command[i++] = token;
        token = strtok(NULL, delimiter);
    }
    command[i] = NULL;  // Set the last element to NULL as execvp() expects NULL-terminated array

    return command;
}

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

    while (1) {
        input = readline("unixsh> ");
        if (input == NULL) {
            printf("\n");
            break; // User pressed Ctrl+D, exit the shell
        }
        command = get_input(input);

        child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            perror("execvp failed"); // Print error if execvp fails
            exit(EXIT_FAILURE); // Terminate child process if execvp fails
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }

    return 0;
}
