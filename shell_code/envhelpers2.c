#include "shell.h"
/**
 * free_env - =======
 * @e: =========
 * Return: no return
 */
void _freeEnv(env_t *e)
{
	unsigned int i;

	for (i = 0; e->envVar[i]; i++)
	{
		free(e->envVar[i]);
	}

	free(e->envVar);
}
