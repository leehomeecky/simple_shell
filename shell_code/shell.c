#include "shell.h"

/**
 * main - entry point
 *
 * @argc: numbers of argument passed
 * @argv: pointer to array of argument
 *
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *line = NULL, *token, *dlim = " \n", *cp_line;
	size_t line_len = 0;
	ssize_t num_read;
	int i;
	pid_t pid;

	while ((num_read = get_line(&line, &line_len, stdin)) > 0)
	{
		cp_line = str_dup(line);
		token = strtok(line, dlim);
		for (i = 0; token; i++)
		{
		printf("Read %ld bytes: %s\n", num_read, token);
		token = strtok(NULL, dlim);
		}
	}
	free(line);
	return (0);
}
