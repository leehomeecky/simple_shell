#include "shell.h"

/**
 * str_tok - a function that tokenizes strings
 *
 * @str: string to be tokenized
 * @delim: delimeter to use
 *
 * Return: tokens || NULL
 */

char *str_tok(char *str, const char *delim)
{
	static char *last_token;
	char *token_start, *token_end;

	if (str != NULL)
		last_token = str;
	if (last_token == NULL)
		return (NULL);
	token_start = last_token;
	while (*token_start && str_chr(delim, *token_start) != NULL)
		token_start++;
	if (*token_start == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	token_end = token_start + 1;
	while (*token_end && str_chr(delim, *token_end) == NULL)
		token_end++;
	if (*token_end)
	{
		*token_end = '\0';
		last_token = token_end + 1;
	}
	else
	last_token = NULL;
	return (token_start);
}
