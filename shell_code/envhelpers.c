#include "shell.h"

char *_getenv(char *name);
char **addenvMem(char **envptr, unsigned int sizeOld, unsigned int sizeNew);
void loadenv(env_t *envdata);
void _setenv(char *name, char *value, env_t *envdata);
int _unset(char *name, env_t *envdata);
/**
 * _getenv - Getenv
 * @name: ===
 * Return: =====
 */
char *_getenv(char *name)
{
	size_t namelen = _strlen(name);
	char **var;

	for (var = environ; *var != NULL; ++var)
	{
		if (strncmp(name, *var, namelen) == 0 && (*var)[namelen] == '=')
		{
			return (*var + namelen + 1);
		}
	}

	return (NULL);
}

/**
 * addenvMem - =====
 * @envptr: ===.
 * @sizeOld: =====
 * @sizeNew: ====
 * Return: ======
 */
char **addenvMem(char **envptr, unsigned int sizeOld, unsigned int sizeNew)
{
	unsigned int i;
	char **_envptr;


	if (envptr == NULL)
		return (malloc(sizeof(char *) * sizeNew));

	if (sizeNew == sizeOld)
		return (envptr);

	_envptr = malloc(sizeof(char *) * sizeNew);
	if (_envptr == NULL)
		return (NULL);

	for (i = 0; i < sizeOld; i++)
		_envptr[i] = envptr[i];

	free(envptr);

	return (_envptr);
}



/**
 * loadenv - Initialize enviromental variables
 * @envdata: data struct
 * Return: void
 */
void loadenv(env_t *envdata)
{
	unsigned int j;

	for (j = 0; environ[j]; )
		j++;

	envdata->envVar = malloc(sizeof(char *) * (j + 1));
	for (j = 0; environ[j]; j++)
	{
		envdata->envVar[j] = _strdup(environ[j]);
		/*	printf("%s \n",  envdata->envVar[j]);*/
	}
	envdata->envVar[j] = NULL;
}


/**
 * _setenv - ==========
 * @name: ===========
 * @value: --=-=
 * @envdata: struct data
 * Return: no return
 */
void _setenv(char *name, char *value, env_t *envdata)
{
	int k, namelen, valuelen, varlen;
	char *dupVar, *var;

	for (k = 0; envdata->envVar[k]; k++)
	{
		dupVar = _strdup(envdata->envVar[k]);
		var = _strtok3(dupVar, "=");
		if (_strcmp(var, name) == 0)
		{
			free(envdata->envVar[k]);
			/*free(environ[k]);*/
			namelen = _strlen(name);
			valuelen = _strlen(value);
			varlen = namelen + valuelen + 2;
			envdata->envVar[k] = malloc(sizeof(char) * (varlen));
			_strcpy(envdata->envVar[k], name);
			_strcat(envdata->envVar[k], "=");
			_strcat(envdata->envVar[k], value);
			_strcat(envdata->envVar[k], "\0");
			/*environ[k] = malloc(sizeof(char) * (varlen));*/
			/*_strcpy(environ[k], name);*/
			/*_strcat(environ[k], "=");*/
			/*_strcat(environ[k], value);*/
			/*_strcat(environ[k], "\0");*/
			environ = envdata->envVar;
			free(dupVar);
			return;
		}
		free(var);
	}

	envdata->envVar = addenvMem(envdata->envVar, k, sizeof(char *) * (k + 2));
	/*	environ = addenvMem(environ, k, sizeof(char *) * (k + 2));*/
	namelen = _strlen(name);
	valuelen = _strlen(value);
	varlen = namelen + valuelen + 2;
	envdata->envVar[k] = malloc(sizeof(char) * (varlen));
	/*	environ[k] = malloc(sizeof(char) * (varlen));*/
	_strcpy(envdata->envVar[k], name);
	_strcat(envdata->envVar[k], "=");
	_strcat(envdata->envVar[k], value);
	_strcat(envdata->envVar[k], "\0");
	envdata->envVar[k + 1] = NULL;
	/*_strcpy(environ[k], name);*/
	/*_strcat(environ[k], "=");*/
	/*_strcat(environ[k], value);*/
	/*_strcat(environ[k], "\0");*/
	/*environ[k + 1] = NULL;*/
	environ = envdata->envVar;
}

/**
 * _unset - =======
 * @envdata: =====
 * @name: ======
 * Return: ========
 */
int _unset(char *name, env_t *envdata)
{
	char **_environ;
	char *dupvar, *nametounset;
	int m, i, j;

	if (name == NULL)
	{
		/*get_error(datash, -1);*/
		return (1);
	}
	m = -1;
	for (i = 0; envdata->envVar[i]; i++)
	{
		dupvar = _strdup(envdata->envVar[i]);
		nametounset = _strtok3(dupvar, "=");
		if (_strcmp(nametounset, name) == 0)
		{
			m = i;
		}
		free(dupvar);
	}
	if (m == -1)
	{
		/*	get_error(datash, -1);*/
		return (1);
	}
	_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; envdata->envVar[i]; i++)
	{
		if (i != m)
		{
			_environ[j] = envdata->envVar[i];
			j++;
		}
	}
	_environ[j] = NULL;
	free(envdata->envVar[m]);
	free(envdata->envVar);
	free(nametounset);
	envdata->envVar = _environ;
	environ = _environ;
	return (1);
}
