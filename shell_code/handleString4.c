#include "shell.h"
/**
 * _isalpha - =======
 * @c: ========
 * Return: ========
 */
int _isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/**
 * _isalnum - =======
 * @c: =====
 * Return: -===
 */
int _isalnum(int c)
{
	return (_isalpha(c) || (c >= '0' && c <= '9'));
}

/**
 * _strncat - ========
 * @dest: ===========
 * @src: ========
 * @n: ===========
 * Return: =========
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * strcmp_chars - =========
 * @str: ===========
 * @delim: ===========]]]]
 *
 * Return: 1 if are equals, 0 if not.
 */
int strcmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}





/**
 * _strtok3 - ===============
 * @str: ====
 * @delim: ====+
 * Return: ======
 */
char *_strtok3(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (strcmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		i = str_len(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}
