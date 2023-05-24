#include "shell.h"
int  isValidVariableName(char *name);
void setunset_func(char **cmdArray, const char *prgname);
/**
 * isValidVariableName - =====
 * @name: =======
 * Return: =====
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
	env_t *ev;
	int i;

	ev = &ess;
	if (_strchr(cmdArray[0], 'u') != NULL)
		_strcpy(cmdArray[0], "unsetenv");
	else
		_strcpy(cmdArray[0], "setenv");

	_strcat(cmdArray[0], "\0");
	for (i = 0; cmdArray[i]; )
		i++;

	if (i < 2 || i > 3)
	{
		perror(prgname);
		return;
	}
	if (cmdArray[1])
	{
		if (isValidVariableName(cmdArray[1]) == -1)
		{
			_puts(prgname);
			_puts(": ");
			_puts(cmdArray[0]);
			_puts(": '");
			_puts(cmdArray[1]);
			_puts("': not a valid identifier\n");
			/*	_freeEnv(&e);*/
			return;
		}
	}
	if ((i ==  3 && _strcmp(cmdArray[0], "setenv") == 0))
	{
		if (_strcmp(cmdArray[0], "setenv") == 0)
		{
			loadenv(&ess);
		/*	setload = &ess;*/
			_setenv(cmdArray[1], cmdArray[2], ev);
		}
	}
	else if ((i  ==  2 && _strcmp(cmdArray[0], "unsetenv") == 0))
	{
		if (_strcmp(cmdArray[0], "unsetenv") == 0)
		{
			loadenv(&ess);
		/*	setload = &ess;*/
			_unset(cmdArray[1], ev);
		}
	}

}
