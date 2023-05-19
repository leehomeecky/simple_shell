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

/**
 * str_to_arr - a function that saves all string to an array of pointers
 *
 * @cmd: commands to be splited
 * @delim: delimiter to use for spliting
 *
 * Return: poimter to array of commands
 */

char **str_to_arr(char *cmd, const char *delim)
{
	char *cpy_cmd, **cmd_arr, *token;
	size_t arr_len, i;

	if (cmd == NULL || *cmd == '\0')
		return (NULL);
	cpy_cmd = str_dup(cmd);
	if (cpy_cmd == NULL)
		return (NULL);
	token = str_tok(cpy_cmd, delim);
	for (arr_len = 0; token; arr_len++)
		token = str_tok(NULL, delim);
	cmd_arr = (char **)malloc(sizeof(char *) * arr_len);
	if (cmd_arr == NULL)
		return (NULL);
	token = str_tok(cmd, delim);
	for (i = 0; token; i++)
	{
		cmd_arr[i] = token;
		token = str_tok(NULL, delim);
	}
	cmd_arr[i] = NULL;
	if (cpy_cmd)
	free(cpy_cmd);
	return (cmd_arr);
}



