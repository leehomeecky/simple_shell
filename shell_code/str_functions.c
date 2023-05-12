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
	if (*str == '\0' || *str == NULL)
		return (0);
	return (1 + _strlen(++str));
}
