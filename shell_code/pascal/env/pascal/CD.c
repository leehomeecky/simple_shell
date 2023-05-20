#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shellt.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_TOKENS 256

int execute_command(char *command);
void change_directory(char *path);
char *_realpath(char *path, char *resolved_path);
/**
 * _realpath - ======
 * @path: ========
 * @resolved_path: ======
 * Return: =====
 */
char *_realpath(char *path, char *resolved_path)
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
			perror("getcwd");
			return (NULL);
		}
		_strncat(temp, "/", sizeof(temp) - _strlen(temp));
		_strncat(temp, path, sizeof(temp) - _strlen(temp));
	}

	resolved_path[0] = '\0';  /* Initialize resolved_path as an empty string*/

	result = _strtok3(temp, delimiter);
	while (result != NULL)
	{
		/* Handle "."*/
		if (_strcmp(result, ".") == 0)
		{
			result = _strtok3(NULL, delimiter);
			continue;
		}

		/*( Handle ".."*/
		if (_strcmp(result, "..") == 0)
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
		_strncat(resolved_path, "/", PATH_MAX - _strlen(resolved_path));
		_strncat(resolved_path, result, PATH_MAX - _strlen(resolved_path));
		result = _strtok3(NULL, delimiter);
	}
	return (resolved_path);
}

/**
 * change_directory - ======
 * @path: =========
 * Return: =====
 */
void change_directory(char *path)
{
	char new_dir[502];
	char current_dir[500];
	env_t e;
	env_t *ev;
	char resolved_dir[MAX_COMMAND_LENGTH];

	loadenv(&e);
	ev = &e;

	if (path[0] == '/')
	{
		/* Absolute path*/
		_strncpy(new_dir, path, sizeof(new_dir));
	} else
	{
		/* Relative path*/
		if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		{
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
	if (_realpath(new_dir, resolved_dir) == NULL)
	{
		perror("realpath");
		return;
	}

	/*Update PWD and OLDPWD environment variables*/
	_setenv("OLDPWD", _getenv("PWD"), ev);
	_setenv("PWD", resolved_dir, ev);
	_writef("Changed directory to: %s\n", resolved_dir);
}

/**
 * execute_command - =====
 * @command: ======
 * Return: ====
 */
int execute_command(char *command)
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

	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			change_directory(_getenv("HOME"));
		} else if (_strcmp(args[1], "-") == 0)
		{
			change_directory(_getenv("OLDPWD"));
		}
		else if (_strcmp(args[1], "~") == 0)
		{
			change_directory(_getenv("HOME"));
		}
		else
		{
			change_directory(args[1]);
		}
		return (1);
	}

/*	pid_t pid = fork();*/

/*	if (pid == -1)*/
/*	{*/
	/*	perror("fork");*/
/*		exit(EXIT_FAILURE);*/
/*	} else if (pid == 0)*/
/*	{*/
	/*	execvp(args[0], args);*/
	/*	perror("execvp");*/
	/*	exit(EXIT_FAILURE);*/
/*	}*/
/*	else*/
/*	{*/
	/*	waitpid(pid, NULL, 0);*/
/*	}*/

	return (1);
}
/**
 * main - ====
 * Return: =====
 */
int main(void)
{

	while (1)
	{
		/*  char command[MAX_COMMAND_LENGTH];*/
		size_t  bufsize = 0;
		char *command = NULL;
		ssize_t len;

		_putchar('$');
		_putchar(' ');

		len = getline(&command, &bufsize, stdin);
		if (len == -1)
			return (-1);
		/*Remove the newline character if present*/
		if (command[len - 1] == '\n')
			command[len - 1] = '\0';

		if (_strcmp(command, "\0") == 0)
		{
			break;
		}

		if (execute_command(command) == 0)
		{
			_writef("Invalid command\n");
		}
	}

	return (0);
}

