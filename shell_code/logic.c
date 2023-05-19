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
 * @name: name of the program
 */

void execve_func(char **cmd_arr, conat char *prog_name)
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

void (*cmd_func(char *cmd))(char **cmd_arr)
{
	int i, len = 1;

	sltFunc slt_func[] = {
				{"/bin/echo", echo_func},
			};

	if (access(cmd, X_OK) == 0)
	{
		if (str_cmp(cmd, "/bin/echo") == 0)
			return (echo_func);
		else
			return (execve_func);
	}
	for (i = 0; i < len; i++)
	if (str_cmp(cmd, (slt_func + i)->cmd) == 0)
	return ((slt_func + i)->cmdFunc);

	return (NULL);
}

/**
 * shell_logic - a finction that handles all the shell logics
 *
 * @argv: pointer to argument array
 * @cmd: comand to run
 * @cmd_no: command number
 *
 * Return: NULL || pointer to an array
 */

char **shell_logic(const char **argv, char *cmd)
{
	char **cmd_arr, *delim = " \n", *cp_cmd, *alias_cmd = NULL;
	void (*cmdFunc)(char **cmd_arr);

	cp_cmd = str_dup(cmd);
	cmd_arr = str_to_arr(cp_cmd, delim);
	if (str_cmp(cmd_arr[0], "exit") == 0)
	{
		free(cp_cmd);
		return(cmd_arr);
	}
	/*alias_cmd = alias_functio(cmd_arr[0]);*/
	if (alias_cmd != NULL)
	{
	cmd_arr[0] = full_cmd(alias_cmd);
	free(alias_cmd);
	}
	else
	cmd_arr[0] = full_cmd(cmd_arr[0], );
	cmdFunc = cmd_func(cmd_arr[0]);
	if (cmdFunc == NULL)
	perror(argv[0]);
	else
	cmdFunc(cmd_arr, argv[0]);
	if (cp_cmd)
	free(cp_cmd);
	if (cmd_arr[0])
	free(cmd_arr[0]);
	if(cmd_arr)
	free(cmd_arr);
	return (NULL);

}
