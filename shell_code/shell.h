#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>
#define MAX_COMMAND_LENGTH 1024
#define MAX_ALIAS_NAME 50
#define BUFFER_SIZE 1024
#define MAX_ALIAS_VALUE 100
#define ALIAS_FILE "aliases.txt"
#define MAX_NUM_ARGS 100

extern char **environ;

/*#define BUFFER_SIZE 100*/


/**
 * struct select_function - structure to filter
 * which command function to select
 * @cmd: command to check
 * @cmdFunc: function to run the command
 */

typedef struct select_function
{
	char *cmd;
	void (*cmdFunc)(char **cmd_arr, const char *prog_name);
} sltFunc;

/**
 * struct array_quote - a structure to store the quote found, and amount found
 *
 * @quote: quote found
 * @len: number of quote found
 */

typedef struct array_quote
{
	char quote;
	int len;
} arrQut;

/**
 * struct env_t - env variables
 * @envVar: pointer
 */

typedef struct env_t
{
	char **envVar;
} env_t;

env_t *evload;

void _freeEnv(env_t *e);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int str_len(char *str);
char *str_dup(char *str);
int str_cmp(char *str1, char *str2);
void mem_cpy(void *dest, const void *src, ssize_t n);
void *_realloc(void *ptr, size_t size);
char *str_chr(const char *s, char c);
char *str_tok(char *str, const char *delim);
char **str_to_arr(char *cmd, const char *delim);
int _puts(const char *str);
void _prompt(void);
char *full_cmd(char *cmd);
char **shell_logic(const char **argv, char *cmd);
char *str_cat(char *str1, char *str2);
void execve_func(char **cmd_arr, const char *prog_name);
void alias_func(char **cmdarr, const char *prgname);
void cd_func(char **cmdarr, const char *prgname);
void remove_quotes(char *str, char quote);
int count_quotes_int(char *str, char quote);
arrQut *count_quotes_arr(char **cmd_arr);
void echo_func(char **cmd_arr, const char *prog_name);
void (*cmd_func(char *cmd))(char **cmd_arr, const char *prog_name);
void comment(char *str);
void removeExtraSpaces(char *str);
void load_aliases(void);
void save_alias(char *name, char *value);
void retrieve_alias(char *name);
void retrieve_alias(char *name);
void removeExtraSpaces(char *str);
void load_aliases(void);
int _isalpha(int c);
int _isalnun(int c);
int _putchar(char c);
char *_strncat(char *dest, char *src, int n);
char *_getenv(char *name);
void handlemultiReg(char **command, const char *prgname);
void callupdatealias(char *command, const char *prgname);
void update_alias(char *aliasName, char *filename,
		char *newValue, const char *prgname);
char *_strdup(char *str);
void loadenv(env_t *envdata);
int _unset(char *name, env_t *envdata);
void _setenv(char *name, char *value, env_t *envdata);
char **addenvMem(char **envptr, unsigned int sizeOld, unsigned int sizeNew);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _snprintf(char *buffer, size_t size, const char *format, ...);
int _rename(const char *oldname, const char *newname);
char *_strrchr(char *str, int character);
char *_strstr(char *haystack, char *needle);
char *_strncpy(char *dest, char *src, int n);
int _strncmp(char *s1, char *s2, size_t n);
char *_strdup(char *str);
char *_strstr(char *haystack, char *needle);
char *_strncpy(char *dest, char *src, int n);
int _strncmp(char *s1, char *s2, size_t n);
char *_strdup(char *str);
char *_strstr(char *haystack, char *needle);
int is_delim(char c, char *delim);
char *_strchr(char *str, char ch);
char *_strtok(char *str, char *delimiters);
int strcmp_chars(char str[], const char *delim);
char *_strtok3(char str[], const char *delim);
void _writef(const char *format, ...);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);

#endif
