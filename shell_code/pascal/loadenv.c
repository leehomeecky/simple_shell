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
/*	envdata->envVar[k] = copy_info(name_env, value);*/
	namelen = _strlen(name);
	valuelen = _strlen(value);
	varlen = namelen + valuelen + 2;
	envdata->envVar[k] = malloc(sizeof(char) * (varlen));
	_strcpy(envdata->envVar[k], name);
	_strcat(envdata->envVar[k], "=");
	_strcat(envdata->envVar[k], value);
	_strcat(envdata->envVar[k], "\0");
			free(dupVar);
			return;
		}
		free(var);
	}

	envdata->envVar = addenvMem(envdata->envVar, k, sizeof(char *) * (k + 2));
//	envdata->envVar[k] = copy_info(name, value);
	namelen = _strlen(name);
	valuelen = _strlen(value);
	varlen = namelen + valuelen + 2;
	envdata->envVar[k] = malloc(sizeof(char) * (varlen));
	_strcpy(envdata->envVar[k], name);
	_strcat(envdata->envVar[k], "=");
	_strcat(envdata->envVar[k], value);
	_strcat(envdata->envVar[k], "\0");
	envdata->envVar[k + 1] = NULL;
environ = envdata->envVar;
}






int main(void)
{

//	_setenv("MKEE", "1980", ev);
//	_setenv("PASCAL", "1989", ev);
//	_setenv("SADE", "1980", ev);
 //      	_setenv("UNCLE", "1989", ev);

while(1){

env_t e;
env_t *ev;
int i, j, len;
   char *command = NULL;
char *args[50];
ssize_t  bufsize;
   loadenv(&e);
   int numArgs=0, maxArgs = 4;
   char *token;
   ev = &e;
	 printf("$ ");

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


_setenv(args[1], args[2], ev);

for (i = 0; ev->envVar[i]; i++)                           printf("%s \n",  ev->envVar[i]);
for (i = 0; environ[i]; i++)
	printf("%s \n",  environ[i]);


free(command);
    }



return (0);
}
