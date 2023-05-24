#include "shell.h"

char *_getenv(char *name);
char **addenvMem(char **envptr, unsigned int sizeOld, unsigned int sizeNew);
void loadenv(env_t *envdata);
void _setenv(char *name, char *value, env_t *envdata);
int _unset(char *name, env_t *envdata);
/**
 * _getenv - Getenv
 * @name: ===
 * Return: ====
 */
char *_getenv(char *name)
{
	size_t namelen = str_len(name);
	char **var;

	for (var = environ; *var != NULL; ++var)
	{
		if (_strncmp(name, *var, namelen) == 0 && (*var)[namelen] == '=')
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
	{
	_envptr[i] = envptr[i];
	}
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

	if (envdata->envVar == NULL)
	{

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
	env_t *ec;

	ec = &ess;
	if (name == NULL || value == NULL || envdata == NULL)
		return;

	for (k = 0; envdata->envVar[k]; k++)
	{
		dupVar = _strdup(envdata->envVar[k]);
		var = _strtok3(dupVar, "=");
		if (str_cmp(var, name) == 0)
		{
			free(envdata->envVar[k]);
			/*free(environ[k]);*/
			namelen = str_len(name);
			valuelen = str_len(value);
			varlen = namelen + valuelen + 2;
			envdata->envVar[k] = malloc(sizeof(char) * (varlen));
			_strcpy(envdata->envVar[k], name);
			_strcat(envdata->envVar[k], "=");
			_strcat(envdata->envVar[k], value);
			_strcat(envdata->envVar[k], "\0");
			environ = envdata->envVar;
			ec->envVar = envdata->envVar;
			free(dupVar);
			return;
		}
		free(var);
	}
	envdata->envVar = addenvMem(envdata->envVar, k, sizeof(char *) * (k + 2));
	/*	environ = addenvMem(environ, k, sizeof(char *) * (k + 2));*/
	namelen = str_len(name);
	valuelen = str_len(value);
	varlen = namelen + valuelen + 2;
	envdata->envVar[k] = malloc(sizeof(char) * (varlen));
	_strcpy(envdata->envVar[k], name);
	_strcat(envdata->envVar[k], "=");
	_strcat(envdata->envVar[k], value);
	_strcat(envdata->envVar[k], "\0");
	envdata->envVar[k + 1] = NULL;
	environ = envdata->envVar;
	ec->envVar = envdata->envVar;
}


/**
 * _unset - =======
 * @envdata: =====
 * @name: ======
 * Return: ========
 */
int _unset(char *name, env_t *envdata)
{
;
	char *dupvar, *nametounset;
	int m, i, j;


	if (name == NULL)
	{
		/*error section*/
		return (1);
	}
	m = -1;
	for (i = 0; envdata->envVar[i]; i++)
	{
		dupvar = _strdup(envdata->envVar[i]);
		nametounset = _strtok3(dupvar, "=");
		if (str_cmp(nametounset, name) == 0)
		{
			m = i;
		}
		free(dupvar);
	}
	if (m == -1)
	{
		/*error*/
		return (1);
	}
	for (i = j = 0; envdata->envVar[i]; i++)
	{
		if (i != m)
		{
			envdata->envVar[j] = envdata->envVar[i];
			j++;
		}
	}
	envdata->envVar[j] = envdata->envVar[i];
	/*free(nametounset);*/
	free(envdata->envVar[m]);
	/*free(envdata->envVar);*/
	envdata->envVar = envdata->envVar;
	environ = envdata->envVar;
	return (1);
}
