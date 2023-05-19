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
 * comment - function to handle comment
 *
 * @str: command to check
 */

void comment(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '#')
		{
			if (str[(i - 1)] != '"' && str[(i - 1)] != '\'')
				str[i] = '\0';
		}
	}
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
	char *line = NULL, *dlim = ";\n", **cmd_arr;
	size_t line_len = 0;
	ssize_t num_read;
	int i;

	if (argc > 0)
	_prompt();
	while ((num_read = get_line(&line, &line_len, stdin)) > 0)
	{
		cmd_arr = str_to_arr(line, dlim);
		if (cmd_arr == NULL)
			continue;
		for (i = 0; cmd_arr[i]; i++)
		{
			comment(cmd_arr[i]);
			if (shell_logic(argv, cmd_arr[i]))
				_puts("exit");
		}
		if (cmd_arr)
		free(cmd_arr);
		cmd_arr = NULL;
		_prompt();
	}
	if (line)
	free(line);
	return (0);
}
