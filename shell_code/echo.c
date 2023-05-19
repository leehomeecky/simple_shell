#include "shell.h"

/**
 * remove_quotes - a function to remove quote in the echo string
 *
 * @str: string to remove quote from
 * @quote: the quote type to remove
 */

void remove_quotes(char *str, char quote)
{
	int i, j = 0;

	if (quote == '\0')
		return;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == quote && (i == 0 || str[(i - 1)] != '\\'))
			continue;
		str[j] = str[i];
		j++;
	}
	str[j] = '\0';
}


/**
 * count_quotes_int - function to count quote in string
 *
 * @str: string to check
 * @quote: type of quote to check
 *
 * Return: numbers of quote found
 */

int count_quotes_int(char *str, char quote)
{
	int i, count = 0;

	for (i = 0; str[i]; i++)
		if (str[i] == quote && str[(i - 1)] != '\\')
			count++;
	return (count);
}

/**
 * count_quotes_arr - function to count quotes in an array
 *
 * @cmd_arr: array to count quote from
 *
 * Return: a struct of type arrQut
 */

arrQut *count_quotes_arr(char **cmd_arr)
{
	int i, j;

	arrQut *arr_qut = (arrQut *)malloc(sizeof(arrQut));

	if (arr_qut == NULL)
		return (NULL);
	arr_qut->quote = '\0';
	arr_qut->len = 0;
	for (i = 0; cmd_arr[i]; i++)
	{
		for (j = 0; cmd_arr[i][j]; j++)
		{
			if (arr_qut->quote == '\0' && (cmd_arr[i][j] == '\'' ||
			cmd_arr[i][j] == '"') && cmd_arr[i][(j - 1)] != '\\')
			{
				arr_qut->quote = cmd_arr[i][j];
				arr_qut->len++;
			}
			else if (cmd_arr[i][j] == arr_qut->quote &&
					cmd_arr[i][(j - 1)] != '\\')
				arr_qut->len++;
		}
	}
	return (arr_qut);

}


/**
 * echo_func - function to handle echo command
 *
 * @cmd_arr: array of command and string to echo
 */

void echo_func(char **cmd_arr, const char *prog_name)
{
	char *line = NULL, *cp_line;
	size_t line_len = 0, arr_len = 0, i;
	arrQut *arr_qut;

	for (i = 0; cmd_arr[i]; i++)
		arr_len++;
	arr_qut = count_quotes_arr(cmd_arr);
	/*while (arr_qut->len % 2 == 1)
	{
		_puts("\n> ");
		get_line(&line, &line_len, stdin);
		cp_line = str_dup(line);
		cmd_arr = _realloc(cmd_arr, (arr_len += 1));
		cmd_arr[(arr_len = 1)] = cp_line;
		cmd_arr[arr_len] = NULL;
		arr_qut->len += count_quotes_int(cp_line, arr_qut->quote);
		free(line);
	}*/
	for (i = 0; cmd_arr[i]; i++)
		remove_quotes(cmd_arr[i], arr_qut->quote);
	if (arr_qut)
	free(arr_qut);
	execve_func(cmd_arr, prog_name);

}
