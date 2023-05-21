#include "shell.h"

/**
 * str_cat - function to concatinate strings
 *
 * @str1: string 1 to concatinate
 * @str2: string 2 to concatinate with @str1
 *
 * Return: concatinated string
 */

char *str_cat(char *str1, char *str2)
{
	int len1, len2, i = 0;
	char *str;

	len1 = str_len(str1);
	len2 = str_len(str2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	while (str1[i])
	{
	str[i] = str1[i];
	i++;
	}

	while (*str2)
	{
	str[i] = *str2;
	i++;
	str2++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * write_int - a function that writes integer value to space
 *
 * @space: space to write to
 * @val: integer value to be writen
 *
 * Return: number of value writen
 */

int write_int(char *space, int val)
{
	int i = 0, j, k = 0;
	char str;

	do {
		*(space + i) = (val % 10) + '0';
		val /= 10;
		i++;
	} while (val > 0);
	for (j = (i - 1); k < j; j--)
	{
	str = *(space + k);
	*(space + k) = *(space + j);
	*(space + j) = str;
	k++;
	}
	return (i);
}


/**
 * write_str - a function that writes string to space
 *
 * @space: space to write to
 * @str: string to be writen
 *
 * Return: number of value writen
 */

int write_str(char *space, char *str)
{
	int i = 0;

	if (str != NULL)
	{
		while (str[i])
		{
		*(space + i) = str[i];
		i++;
		}
	}
	*(space + i) = '\0';
	return (i);
}
