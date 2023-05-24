#include "shell.h"
/**
 * loadcdenv - Initialize enviromental variables
 * @envdata: data struct
 * Return: void
 */
void loadcdenv(env_t *envdata)
{
	unsigned int j;

	if (envdata->envVar == NULL)
	{

	for (j = 0; environ[j]; )
		j++;

	envdata->envVar = malloc(sizeof(char *) * (j + 1));
	for (j = 0; environ[j]; j++)
	{
		envdata->envVar[j] = str_dup(environ[j]);
		/*	printf("%s \n",  envdata->envVar[j]);*/
	}
	envdata->envVar[j] = NULL;
	}
}

