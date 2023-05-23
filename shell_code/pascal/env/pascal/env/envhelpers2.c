#include "shell.h"
/**
 * _freeEnv - =======
 * @e: ========
 * Return: no return
 */
void _freeEnv(env_t *e)
{
	unsigned int i;

	if (!e)
		return;

	for (i = 0; e->envVar[i]; i++)
	{
		free(e->envVar[i]);
	}

	free(e->envVar);
}
