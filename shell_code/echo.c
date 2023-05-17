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

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '"' && (i == 0 || str[i-1] != '\\'))
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
		if (cmd_arr[i] == quote && cmd_arr[(i - 1)] != '\\')
			count++;
	return (count);
}
