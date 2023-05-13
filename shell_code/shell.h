#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024

ssize_t mygetline(char **lineptr, size_t *n, FILE *stream);
int _strlen(char *str);
char *_strdup(char *str);
int _strcmp(char *str1, char *str2);

#endif
