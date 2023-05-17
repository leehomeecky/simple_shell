#include "shell.h"

/**
 * _prompt - a fuction to prompt users to give input to the shell
 */

void _prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("($) ");
}

/**
 * main - entry point
 *
 * @argc: numbers of argument passed
 * @argv: pointer to array of argument
 *
 * Return: 0
 */

int main(int argc, const char **argv)
{
	char *line = NULL, *token, *dlim = " \n", *cp_line, **cmd_arr;
	size_t line_len = 0;
	ssize_t num_read;
	int i;
	pid_t pid;

	_prompt();
	while ((num_read = get_line(&line, &line_len, stdin)) > 0)
	{
		cmd_arr = str_to_arr(line, ";\n");
		for (i = 0; cmd_arr[i]; i++)
		{
			if (shell_logic(argv, cmd_arr[i]))
				_puts("exit");
		}
		free(cmd_arr);
		_prompt();
	}
	free(line);
	return (0);
}
