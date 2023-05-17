#include "shell.h"

/**
 * full_cmd - a function that checks if the command is a full command
 * if not convert it to a full command
 *
 * @cmd: is the command
 *
 * Return: the full commad
 */

char *full_cmd(char *cmd)
{
	char *path = "/bin/";
	int i;

	for (i = 0; path[i]; i++)
	{
		if (cmd[i] != path[i])
		{
		return (str_cat(path, cmd));
		}
	}
	return (str_dup(cmd));
}

/**
 * execve_func - a function that runs the execve function
 *
 * @cmd_arr: array of command to run
 */

void execve_func(char **cmd_arr)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	execve(cmd_arr[0], cmd_arr, NULL);
	else
	wait(NULL);
}

/**
 * cmd_func - a function that checks the command
 *
 * @cmd: the commande to be checked
 *
 * Return: the function to run the command if success else NULL
 */



/**
 * shell_logic - a finction that handles all the shell logics
 *
 * @argv: pointer to argument array
 * @cmd: comand to run
 *
 * Return: NULL || pointer to an array
 */

char **shell_logic(const char **argv, char *cmd)
{
	char **cmd_arr, *delim = " \n", *cp_cmd, *alias_cmd = NULL;

	cp_cmd = str_dup(cmd);
	cmd_arr = str_to_arr(cp_cmd, delim);
	/*alias_cmd = alias_functio(cmd_arr[0]);*/
	if (alias_cmd != NULL)
	{
	cmd_arr[0] = full_cmd(alias_cmd);
	free(alias_cmd);
	}
	else
	cmd_arr[0] = full_cmd(cmd_arr[0]);
	_puts(cmd_arr[0]);
	_puts("\n");
	free(cp_cmd);
	free(cmd_arr[0]);
	free(cmd_arr);
	return (NULL);

}
