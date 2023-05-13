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

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int str_len(char *str);
char *str_dup(char *str);
int str_cmp(char *str1, char *str2);
void mem_cpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t size);

#endif
