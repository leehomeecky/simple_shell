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
 * var_handler - a function that handles variable replacement
*
* @str: array of string to check
*
* Return: handled string
*/

char *var_handler(char *str)
{
	int i, j = 0, s_q = 0, d_q = 0, *p;
	char *space;

	space = (char *)malloc(BUFFER_SIZE);
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\'')
			p = &s_q;
		else if (str[i] == '"')
			p = &d_q;
		if (str[i] == '\'' || str[i] == '"')
			if (i > 0)
			{
			if (str[(i - 1)] != '\\')
				(*p)++;
			}
			else
				(*p)++;
		if (str[i] == '$' && s_q % 2 == 0 &&  d_q % 2 == 0)
		{
			if (str[(i + 1)] == '$')
			{
			j += write_int(&(space[j]), getpid());
			i++;
			continue;
			}
			else if (str[(i + 1)] == '?')
			{
			j += write_int(&(space[j]), 0);
			i++;
			continue;
			}
			else if ((str[(i + 1)] >= 'a' && str[(i + 1)] <= 'z') ||
			(str[(i + 1)] >= 'A' && str[(i + 1)] <= 'Z') || str[(i + 1)] >= '_')
			{
				j += write_str(&(space[j]), _getenv(&(str[(i + 1)])));
				return (space);
			}
		}
		space[j++] = str[i];
	}
	space[j] = '\0';
	return (space);
}


/**
 * echo_func - function to handle echo command
 *
 * @cmd_arr: array of command and string to echo
 * @prog_name: program name
 */

void echo_func(char **cmd_arr, const char *prog_name)
{
	int i;
	char var;
	pid_t pid = getpid();

	arrQut *arr_qut;

	arr_qut = count_quotes_arr(cmd_arr);
	for (i = 1; cmd_arr[i]; i++)
	cmd_arr[i] = var_handler(cmd_arr[i]);
	for (i = 0; cmd_arr[i]; i++)
		remove_quotes(cmd_arr[i], arr_qut->quote);
	if (arr_qut)
	free(arr_qut);
	execve_func(cmd_arr, prog_name);
	for (i = 1; cmd_arr[i]; i++)
		free (cmd_arr[i]);

}
