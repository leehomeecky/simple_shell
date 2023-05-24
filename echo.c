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
 * check_quote - function to if its a valid quote
 *
 * @str: caracter to check
 * @quote: type of quote to check
 * @pos: position of quote in string
 *
 * Return: 1 if valid quote || zero if not
 */

int check_quote(char *str, char quote, int pos)
{
	if (str[pos] == quote)
	{
		if (pos > 0)
		{
			if (str[(pos - 1)] == '\\')
				return (0);
		}
		return (1);
	}
	return (0);
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
	int i, j = 0;
	char *space = (char *)malloc(BUFFER_SIZE);

	for (i = 0; str[i] != '\0'; i++)
	{
		s_qu.val += check_quote(str, '\'', i);
		d_qu.val += check_quote(str, '"', i);
		if (str[i] == '$' && s_qu.val % 2 == 0 &&  d_qu.val % 2 == 0)
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
			if (write_str(&(space[j]), _getenv(&(str[(i + 1)]))) >= 0)
				return (space);
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
	int i, j = 0;
	arrQut *arr_qut;
	char **cp_arr;

	s_qu.val = 0;
	d_qu.val = 0;
	arr_qut = count_quotes_arr(cmd_arr);
	for (i = 1; cmd_arr[i]; i++)
		cmd_arr[i] = var_handler(cmd_arr[i]);

	for (i = 0; cmd_arr[i]; i++)
		remove_quotes(cmd_arr[i], arr_qut->quote);

	cp_arr = (char **)malloc((1 + arr_cnt(cmd_arr)) * sizeof(char *));
	if (cp_arr == NULL)
		return;
	for (i = 0; cmd_arr[i]; i++)
		if (cmd_arr[i][0] != '\0')
		cp_arr[j++] = cmd_arr[i];
	/*_puts(cp_arr[2]);*/
	cp_arr[j] = NULL;
	if (arr_qut)
	free(arr_qut);
	execve_func(cp_arr, prog_name);
	for (i = 1; cmd_arr[i]; i++)
		free(cmd_arr[i]);
	free(cp_arr);

}
