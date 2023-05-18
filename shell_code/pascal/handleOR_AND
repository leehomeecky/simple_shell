#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute_command(char* command) {
    char* args[64];
    int arg_count = 0;

    // Tokenize the command into arguments
    char* token = strtok(command, " ");
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    // Execute the command
    execvp(args[0], args);
    perror("execvp");
    exit(1);
}

int main() {
    char input[256];
    printf("Enter the command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    pid_t pid;
    int status;

    char* and_token = "&&";
    char* or_token = "||";

    // Create a copy of the input command
    char command_copy[256];
    strcpy(command_copy, input);

    char* token = strtok(command_copy, and_token);
    while (token != NULL) {
        int is_or = 0;
        char* or_command = strstr(token, or_token);
        if (or_command != NULL) {
            // The command contains ||
            is_or = 1;
            *or_command = '\0';
            or_command += strlen(or_token);
        }

        if ((pid = fork()) == 0) {
            // Child process
            execute_command(token);
        }
        waitpid(pid, &status, 0);
        int command_status = WEXITSTATUS(status);
        if (is_or) {
            // Logical OR operator
            if (command_status == 0) {
                // Command succeeded, stop executing further commands
                break;
            } else if (or_command != NULL) {
                // Execute the command after the logical OR operator
                execute_command(or_command);
            }
        } else {
            // Logical AND operator
            if (command_status != 0) {
                // Command failed, stop executing further commands
                break;
            }
        }

        // Check if there are more commands separated by && or ||
        token = strtok(NULL, and_token);
    }

    return 0;
}
