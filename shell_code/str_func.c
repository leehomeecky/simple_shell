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
 * putchar_int - a function that prints out integer value
 *
 * @val: integer value to be printed
 */

void putchar_int(int val)
{
	do {
		_putchar((val % 10) + '0');
		val /= 10;
	} while (val > 0);
}
