#include "shell.h"

/**
 * isValidVariableName - =====
 * @name: =======
 * Return: ======
 */
int  isValidVariableName(char *name)
{
	int i = 0;

	/*Check if the first character is a letter or underscore*/
	if (!_isalpha(name[0]) && name[0] != '_')
		return (-1);

	/*Check the rest of the characters*/
	for (i = 1; name[i] != '\0'; i++)
	{
		/* Check if the character is alphanumeric or underscore*/
		if (!_isalnum(name[i]) && name[i] != '_')
			return (-1);
	}

	return (0);
}


/*int main(void)*/
/**
 * setunset_func - =========
 * @cmdArray: =========
 * @prgname: ============
 * Return: ===========
 */
void setunset_func(char **cmdArray, const char *prgname)
{
	env_t e;
	env_t *ev;
	int i, j;

	loadenv(&e);
	ev = &e;
	setload = &e;

	if (_strchr(cmdArray[0], 'u') != NULL)
		_strcpy(cmdArray[0], "unsetenv");
	else
		_strcpy(cmdArray[0], "setenv");


	for (i = 0; cmdArray[i]; i++)
		j = j + _strlen(cmdArray[i]) + 1;

	if (i  >  3)
	{
		_writef("%s: Not a valid command\n", prgname);
		return;
	}

	else if (isValidVariableName(cmdArray[1]) == -1)
	{
		_writef("hsh: %s: %s: Not a valid identifier\n", cmdArray[0], cmdArray[1]);
	}
	else if (_strcmp(cmdArray[0], "setenv") == 0)
		_setenv(cmdArray[1], cmdArray[2], ev);

	/*	   perror("setenv: too many arguments");*/
	else if (_strcmp(cmdArray[0], "unsetenv") == 0 && i == 2)
		_unset(cmdArray[1], ev);
	else
		_writef("Not a valid command\n");
}
