#ifndef _SHELLT_H
#define _SHELLT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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

/**
 * struct env_t - env variables
 * @environ: pointer
 */
typedef struct env_t
{
	char **envVar;
} env_t;


/*prototype for the custom getline function*/
char *_getenv(char *name);
char *_strdup(char *str);
void loadenv(env_t *envdata);
int _unset(char *name, env_t *envdata);
void _setenv(char *name, char *value, env_t *envdata);
char **addenvMem(char **envptr, unsigned int sizeOld, unsigned int sizeNew);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _snprintf(char* buffer, size_t size, const char* format, ...);
int _rename(const char *oldname, const char *newname);
char *_strrchr(char *str, int character);
char *_strstr(char *haystack, char *needle);
char *_strncpy(char *dest, char *src, int n);
int _strncmp(char *s1, char *s2, size_t n);
char *_strdup(char *str);
char *_strstr(char *haystack, char *needle);
int is_delim(char c, char *delim);
char *_strchr(char *str, char ch);
char *_strtok(char *str, char *delimiters);
int cmp_chars(char str[], const char *delim);
char *_strtok3(char str[], const char *delim);
char **_strtow(char *str, char *d);
void _writef(const char *format, ...);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif
