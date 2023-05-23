#include "shell.h"

/**
 * is_delim - =======
 * @c: =====
 * @delim: ======
 * Return: ========
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _strchr - ============
 * @s: ========
 * @c: ==============
 * Return: =============
 */

char *_strchr(char *s, char c)
{
	int index;

	if (s == NULL)
		return (NULL);

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

