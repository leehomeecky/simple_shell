#include "shell.h"

/**
 * _strlen - function to count numbers of string
 *
 * @str: pointer to null terminated string to be counted
 *
 * Return: numbers of characters counted
 */

int _strlen(char *str)
{
	if (*str == '\0' || str == NULL)
		return (0);
	return (1 + _strlen(++str));
}

/**
 * _strdup - a function that duplicate a string
 *
 * @str - pointer to string to be duplicated
 *
 * Return: pointer to duplicated string
 */

char *_strdup(char *str)
{
	int len, i;
	char *dup_str;

	if (str == NULL || *str = '\0')
		return (NULL);
	len = _strlen(str);
	dup_str = (char *)malloc(sizeof(char) * len + 1);
	for (i = 0; str[i]; i++)
	dup_str[i] = str[i];
	dup_str[i] = '\0';
	return (dup_str);
}

/**
 * _strcmp - function to compare strings
 *
 * @str1: string to compare
 * @str2: string to be compared to
 *
 * Return: 0 if te same else -1
 */

int _strcmp(char *str1, char *str2)
{
	int len1, len2, i;

	len1 = _strlen(str1);
	len2 = _strlen(str2);

	if (len1 != len2)
		return (-1);
	for (i = 0; len1[i]; i++)
	if (len1[i] != len2[i])
		return (-1);
	return (0);
}
