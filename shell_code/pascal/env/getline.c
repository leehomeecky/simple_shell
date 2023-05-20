#include "shell.h"

/**
 * get_line - a function that get input from standard input, or file
 *
 * @lineptr: buffer to write to
 * @n: number of bytes allocated to @lineptr
 * @stream: input to read from
 *
 * Return: numbers of bytes wretten to @lineptr if success |
 * 0 if input is empty | -1 if error occured
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	char buffer[BUFFER_SIZE];
	ssize_t num_read, pos = 0;
	size_t i = 0;
	char c;

	if (!*lineptr)
	{
	*lineptr = malloc(BUFFER_SIZE);
	if (!*lineptr)
	return (-1);
	*n = BUFFER_SIZE;
	}
	while (1)
	{
	if (pos == 0)
	{
	fflush(stream);
	num_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	if (num_read == -1)
		return (-1);
	else if (num_read == 0)
		return (i);
	buffer[num_read] = '\0';
	}
	c = buffer[pos++];
	if (c == '\0')
	{
	(*lineptr)[i] = '\0';
	return (i);
	}
	else
	(*lineptr)[i++] = c;
	if (i == *n)
	{
	*lineptr = _realloc(*lineptr, *n += BUFFER_SIZE);
	if (!*lineptr)
		return (-1);
	}
	}
}
