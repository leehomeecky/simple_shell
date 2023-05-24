#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_TOKENS 256

int execute_command(char *command, const char *p);
void change_directory(char *path, const char *p);
char *_realpath(char *path, char *resolved_path, const char *p);
/**
 * _realpath - =====
 * @path: ========
 * @resolved_path: ======
 * @p: ========
 * Return: =====
 */
char *_realpath(char *path, char *resolved_path, const char *p)
{
	char temp[PATH_MAX];
	/* char* token;*/
	char *delimiter = "/";
	char *result, *last_slash;

	if (path == NULL || resolved_path == NULL)
	{
		return (NULL);
	}

	/* Handle absolute paths*/
	if (path[0] == '/')
	{
		_strncpy(temp, path, sizeof(temp));
	} else
	{
		/* Handle relative paths*/
		if (getcwd(temp, sizeof(temp)) == NULL)
		{
			perror(p);
			return (NULL);
		}
		_strncat(temp, "/", sizeof(temp) - str_len(temp));
		_strncat(temp, path, sizeof(temp) - str_len(temp));
	}

	resolved_path[0] = '\0';  /* Initialize resolved_path as an empty string*/

	result = _strtok3(temp, delimiter);
	while (result != NULL)
	{
		/* Handle "."*/
		if (str_cmp(result, ".") == 0)
		{
			result = _strtok3(NULL, delimiter);
			continue;
		}

		/*( Handle ".."*/
		if (str_cmp(result, "..") == 0)
		{
			last_slash = _strrchr(resolved_path, '/');
			if (last_slash != NULL)
			{
				*last_slash = '\0';
			}
			result = _strtok3(NULL, delimiter);
			continue;
		}

		/* Append the directory or filename to the resolved path*/
		_strncat(resolved_path, "/", PATH_MAX - str_len(resolved_path));
		_strncat(resolved_path, result, PATH_MAX - str_len(resolved_path));
		result = _strtok3(NULL, delimiter);
	}
	return (resolved_path);
}

/**
 * change_directory - ======
 * @path: =========
 * @p: ===========
 * Return: =====
 */
void change_directory(char *path, const char *p)
{
	char new_dir[502];
	char current_dir[500];
	env_t *ev;
/*	env_t e;*/
	char resolved_dir[MAX_COMMAND_LENGTH];

	loadenv(&cdss);
	ev = &cdss;
/*	evload = &e;*/

	if (path[0] == '/')
	{
		/* Absolute path*/
		_strncpy(new_dir, path, sizeof(new_dir));
	} else
	{
		/* Relative path*/
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
			perror(p);
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
		perror(p);
		return;
	}
	if (_realpath(new_dir, resolved_dir, p) == NULL)
	{
		perror(p);
		return;
	}

	/*Update PWD and OLDPWD environment variables*/
	_setenv("OLDPWD", _getenv("PWD"), ev);
	_setenv("PWD", resolved_dir, ev);
}

/**
 * execute_command - =====
 * @command: ======
 * @p: =====
 * Return: ====
 */
int execute_command(char *command, const char *p)
{
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	int i = 0;

	token = _strtok3(command, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok3(NULL, " \t\n");
	}
	args[i] = NULL;

	if (str_cmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			change_directory(_getenv("HOME"), p);
		} else if (str_cmp(args[1], "-") == 0)
		{
			change_directory(_getenv("OLDPWD"), p);
		}
		else if (str_cmp(args[1], "~") == 0)
		{
			change_directory(_getenv("HOME"), p);
		}
		else
		{
			change_directory(args[1], p);
		}
		return (1);
	}

	return (1);
}
/**
 * cd_func -  ====
 * @cmdarr: =======
 * @prgname: ========
 * Return: =====
 */
void cd_func(char **cmdarr, const char *prgname)
{
		char *command = NULL;
		int i = 0;
		int j = 0;
	_strcpy(cmdarr[0], "cd");
	for (i = 0; cmdarr[i]; i++)
		j = j + str_len(cmdarr[i]) + 1;
	command  = malloc(sizeof(char) * (j + 1));
	_strcpy(command, cmdarr[0]);
	for (i = 1; cmdarr[i]; i++)
	{
	_strcat(command, " ");
	_strcat(command, cmdarr[i]);
	_strcat(command, "\0");
	}
	if (_strcmp(command, "\0") == 0)
		{
	/*exit*/
		}

		if (execute_command(command, prgname) == 0)
		{
		_puts(prgname);
		_puts(": Invalid command\n");
		}

		free(command);
	/*	free(cmdarr);*/
}

