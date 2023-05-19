#include "shell.h"

/**
 * str_len - function to count numbers of string
 *
 * @str: pointer to null terminated string to be counted
 *
 * Return: numbers of characters counted
 */

int str_len(char *str)
{
	if (*str == '\0' || str == NULL)
		return (0);
	return (1 + str_len(++str));
}

/**
 * str_dup - a function that duplicate a string
 *
 * @str: pointer to string to be duplicated
 *
 * Return: pointer to duplicated string
 */

char *str_dup(char *str)
{
	int len, i;
	char *dup_str;

	if (str == NULL || *str == '\0')
		return (NULL);
	len = str_len(str);
	dup_str = (char *)malloc(sizeof(char) * len + 1);
	for (i = 0; str[i]; i++)
	dup_str[i] = str[i];
	dup_str[i] = '\0';
	return (dup_str);
}

/**
 * str_cmp - function to compare strings
 *
 * @str1: string to compare
 * @str2: string to be compared to
 *
 * Return: 0 if te same else -1
 */

int str_cmp(char *str1, char *str2)
{
	int len1, len2, i;

	len1 = str_len(str1);
	len2 = str_len(str2);

	if (len1 != len2)
		return (-1);
	for (i = 0; str1[i]; i++)
	if (str1[i] != str2[i])
		return (-1);
	return (0);
}

/**
 * mem_cpy - a function that copies data from a memory locatin to another
 *
 * @src: pointer to the source memory
 * @dest: pointer to the destination memory
 * @n: number of element to be copied from @src to @dest
 */

void mem_cpy(void *dest, const void *src, ssize_t n)
{
	char *d;
	const char *s = src;

	for (d = dest; n >= 0; n--)
	*d++ = *s++;
}

/**
 * str_chr - a function to check for a character in a string
 *
 * @str: string to search through
 * @c: character to find match
 *
 * Return: pointer to match | null
 */

char *str_chr(const char *str, char c)
{
	char ch = c;

	while (*str != '\0')
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}
