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
 * _atoi - a function that convert strings to number
 *
 * @str: string to be converted to number
 *
 * Return: the number
 */

int _atoi(char *str)
{
	int sign = 1, result = 0, i = 0;

	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	result *= sign;
	return (result);
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
	char *line = NULL, *dlim = ";\n", **cmd_arr, **logic;
	size_t line_len = 0;
	ssize_t num_read;
	int i, exit_val;

	if (argc > 0)
	_prompt();
	while ((num_read = get_line(&line, &line_len, stdin)) > 0)
	{
		cmd_arr = str_to_arr(line, dlim);
		for (i = 0; cmd_arr[i]; i++)
		{
			comment(cmd_arr[i]);
			logic = shell_logic(argv, cmd_arr[i]);
			if (logic)
			{
				if (logic[1])
				exit_val = _atoi(logic[1]);
				else
				exit_val = 0;
				free(logic[0]);
				free(logic);
				free(cmd_arr);
				free(line);
				exit(exit_val);
			}
		}
		free(cmd_arr);
		_prompt();
	}
	free(line);
	_freeEnv(evload);
	_freeEnv(setload);
	return (0);
}
