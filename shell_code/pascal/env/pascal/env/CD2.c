#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shellt.h"
#define MAX_COMMAND_LENGTH 1024


void change_directory(char *path) {
    char new_dir[502];
    char current_dir[500];
env_t e;
env_t *ev;
char resolved_dir[MAX_COMMAND_LENGTH];

loadenv(&e);
ev = &e;

    if (path[0] == '/') {
        /* Absolute path*/
        _strncpy(new_dir, path, sizeof(new_dir));
    } else {
        /* Relative path*/
        if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
            perror("getcwd");
            return;
        }
/*        snprintf(new_dir, sizeof(new_dir), "%s/%s", current_dir, path);*/

_strcpy(new_dir, current_dir);
_strcat(new_dir, "/");
_strcat(new_dir, path);
_strcat(new_dir, "\0");
    }

    if (chdir(new_dir) == -1) 
    {
        perror("chdir");
        return;
    }
    if (realpath(new_dir, resolved_dir) == NULL)
    {
        perror("realpath");
        return;
    }

    /*Update PWD and OLDPWD environment variables*/
    _setenv("OLDPWD", getenv("PWD"), ev);
    _setenv("PWD", resolved_dir, ev);
    printf("Changed directory to: %s\n", resolved_dir);
}


int execute_command(char *command) {
    char *args[MAX_COMMAND_LENGTH];
    char *token;
    int i = 0;

    token = _strtok3(command, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = _strtok3(NULL, " \t\n");
    }
    args[i] = NULL;

    if (_strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            change_directory(getenv("HOME"));
        } else if (_strcmp(args[1], "-") == 0) {
            change_directory(getenv("OLDPWD"));
        } else {
            change_directory(args[1]);
        }
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 1;
}

int main() {

    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");
        fgets(command, sizeof(command), stdin);

        if (_strcmp(command, "exit\n") == 0) {
            break;
        }

        if (execute_command(command) == 0) {
            printf("Invalid command\n");
        }
    }

    return 0;
}

