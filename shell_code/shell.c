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
	char *line = NULL, *token, *dlim = " \n", *cp_line, **cmd_arr;
	size_t line_len = 0;
	ssize_t num_read;
	int i;
	pid_t pid;

	while ((num_read = get_line(&line, &line_len, stdin)) > 0)
	{
		cmd_arr = cmd_to_arr(line);
		for (i = 0; cmd_arr[i]; i++)
		printf("commad %d : %s\n", i, cmd_arr[i]);
	}
	free(line);
	return (0);
}
