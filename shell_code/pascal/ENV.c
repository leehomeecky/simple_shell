#include "shellt.h"

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



/* *
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
//	printf("%s \n",  envdata->envVar[j]);
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
		/*get error;*/
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
	/*	get error*/
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
	envdata->envVar = _environ;
	environ = _environ;
	return (1);
}




int main(void)
{
while(1){

env_t e;
env_t *ev;
int len; /*i*/
   char *command = NULL;
char *args[50];
size_t  bufsize;
   loadenv(&e);
   int numArgs=0, maxArgs = 4;
   char *token;
   ev = &e;
	 _putchar('$');
	 _putchar(' ');

	len = getline(&command, &bufsize, stdin);
if (len == -1)
	return (-1);
	/*Remove the newline character if present*/
if (command[len - 1] == '\n')
	command[len - 1] = '\0';


/*Tokenize the command and store arguments in the array*/
    token = _strtok3((char*)command, " ");
    while (token != NULL && numArgs < maxArgs) {
        args[numArgs] = _strdup(token);
        numArgs++;
        token = _strtok3(NULL, " ");
    }
    if (_strcmp(args[0], "setenv") == 0 && numArgs == 3)
	    _setenv(args[1], args[2], ev);
    
/*	   perror("setenv: too many arguments");*/
    else if(_strcmp(args[0], "unsetenv") == 0 && numArgs == 2)
	    _unset(args[1], ev);
    else
	    _writef("Not a valid command\n");
	  /* return (1); error must be here*/


/*for (i = 0; ev->envVar[i]; i++) */             /*             printf("%s \n",  ev->envVar[i]);*/
/*for (i = 0; environ[i]; i++)*/
/*	printf("%s \n",  environ[i]);*/


free(command);
    }



return (0);
}
