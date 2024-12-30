#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

int main() {
    char input[MAX_INPUT_LENGTH];
    char *arguments[MAX_ARGUMENTS];

    while (1) {
        // Display a prompt and get user input
        printf("Enter a command: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit on EOF
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the user input into command and arguments
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;  // Null-terminate the argument array

        // Check if the user entered "exec" and a command (e.g., "exec ls")
        if (arg_count >= 2 && strcmp(arguments[0], "exec") == 0) {
            // Fork a child process to execute the specified command
            pid_t child_pid = fork();
            if (child_pid == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }

            if (child_pid == 0) {
                // In the child process, execute the specified command
                execvp(arguments[1], &arguments[1]);
                perror("Exec failed");
                exit(EXIT_FAILURE);
            } else {
                // In the parent process, wait for the child to finish
                int status;
                wait(&status);
            }
        } else {
            printf("Invalid command. Please use 'exec <command>'.\n");
        }
    }

    return 0;
}
