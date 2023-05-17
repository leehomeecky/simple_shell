#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#define BUFFER_SIZE 100

/**
 * struct select_function - structure to filter which command function to select
 *
 * @cmd: command to check
 * @cmdFunc: function to run the command
 */

typedef struct select_function
{
	char *cmd;
	void (*cmdFunc)(char **cmd_arr);
}

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int str_len(char *str);
char *str_dup(char *str);
int str_cmp(char *str1, char *str2);
void mem_cpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t size);
char *str_chr(const char *s, char c);
char *str_tok(char *str, const char *delim);
char **str_to_arr(char *cmd, const char *delim);
int _puts(const char *str);
void _prompt(void);
char *full_cmd(char *cmd);
char **shell_logic(const char **argv, char *cmd);
char *str_cat(char *str1, char *str2);
void execve_func(char **cmd_arr);

#endif
