#include "shell.h"
void alias_func(char **cmdarr, const char *prgname);
void handlemultiReg(char **command, const char *prgname);
void process_command(const char *command, const char *p);
int checks(char *cmd, int equals, const char *prgname);
/**
 * alchecks - ================
 * @aliasExists: ========
 * @filename: =========
 * @aN: ========
 * @nV: ======
 * @p: ==========
 * Return: ==========
 */
void alchecks(int aliasExists,
		char *filename, char *aN, char *nV, const char *p)
{
	int newAliasFile;

	if (aliasExists)
	{
		/*remove(filename);*/
		_rename(filename, "/root/_temp");
		/* Remove the original file*/
	_rename("/root/temp.txt", "/root/aliases.txt");
/* Rename the temporary file to the original filename*/
	}
	else
	{
		/* remove("temp.txt"); Remove the temporary file since no alias was removed*/
	}

	/*Add the new alias entry*/
	newAliasFile = open(filename, O_WRONLY | O_APPEND);
	if (newAliasFile == -1)
	{
	perror(p);
		return;
	}

	write(newAliasFile, "alias ", 6);
	write(newAliasFile, aN, str_len(aN));
	write(newAliasFile, "='", 2);
	write(newAliasFile, nV, str_len(nV));
	write(newAliasFile, "'\n", 2);

	close(newAliasFile);
}


/**
 * process_command - =======
 * @command: =========
 * @p: =====
 * Return: =======
 */
void process_command(const char *command, const char *p)
{
	const int maxArgs = 50;  /*Maximum number of arguments*/
	char *args[100];     /*Array to store argument pointers*/
	int numArgs = 0;         /*Number of arguments*/
	char *token;
	int i;

	/*Tokenize the command and store arguments in the array*/
	token = _strtok3((char *)command, " ");
	while (token != NULL && numArgs < maxArgs)
	{
		args[numArgs] = _strdup(token);
		numArgs++;
		token = _strtok3(NULL, " ");
	}

	/*Check if the command starts with "alias" and has at least one argument*/
	if (numArgs >= 2 && _strcmp(args[0], "alias") == 0)
	{
		/*Pass the arguments one by one to the retrieve_alias() function*/
		for (i = 1; i < numArgs; i++)
		{
			retrieve_alias(args[i], p);
		}
	}

	/*Free the dynamically allocated argument pointers*/
	for (i = 0; i < numArgs; i++)
	{
		if (args[i] != NULL)
			free(args[i]);
	}
}
/**
 * handlemultiReg - ==========
 * @command: ===========
 * @prgname: ======
 * Return: =========
 */
void handlemultiReg(char **command, const char *prgname)
{
	int equals = 1;

	while (*command)
	{
		if (_strncmp(*command, "alias ", 6) == 0
				&& str_len(*command) > 6 && equals == 0)
		{
			process_command(*command, prgname);
		}
		else if (_strncmp(*command, "alias ", 6) == 0
				&& str_len(*command) > 7 && equals >= 1)
		{
			callupdatealias(*command, prgname);
		}
		else
		{
			perror(prgname);
		}
		command++;
	}
}
/**
 * checks - ==========
 * @cmd: =======
 * @equals: =========
 * @prgname: ========
 * Return: int
 */
int checks(char *cmd, int equals, const char *prgname)
{
	if (!cmd)
		return (-1);
	if (_strcmp(cmd, "alias") == 0)
	{
		load_aliases();
		return (0);
	}
	else if ((_strncmp(cmd, "alias ", 6) == 0)
			&&  str_len(cmd) > 6 && equals == 0)
	{
		process_command(cmd, prgname);
		return (0);
	}
	else if (_strncmp(cmd, "alias ", 6) == 0 && str_len(cmd) > 7 && equals >= 1)
	{
		callupdatealias(cmd, prgname);
		return (0);
	}
	return (-1);
}
/**
 * alias_func - =====
 * @cmdarr: ======
 * @prgname: ========
 * Return: ========
 */
void alias_func(char **cmdarr, const char *prgname)
{
	char *cmd = NULL;
	int i = 0, j = 0, equals = 0;
	char **cmdArray;

	_strcpy(cmdarr[0], "alias");
	for (i = 0; cmdarr[i]; i++)
		j = j + str_len(cmdarr[i]) + 1;
	cmd  = malloc(sizeof(char) * (j + 1));
	_strcpy(cmd, cmdarr[0]);
	for (i = 1; cmdarr[i]; i++)
	{
		_strcat(cmd, " ");
		_strcat(cmd, cmdarr[i]);
	}
	_strcat(cmd, "\0");
	cmdArray = malloc(sizeof(char *) * str_len(cmd));
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			equals = equals +  1;
		i++;
	}
	if (equals >= 2)
	{
		convertStringToArray(cmd, &cmdArray);
	handlemultiReg(cmdArray, prgname);
	}
	else
	{
		removeExtraSpaces(cmd);
		if (checks(cmd, equals, prgname) != 0)
		{
		_puts(prgname);
		}
	}
/*	free(*cmdArray);*/
	free(cmd);
}
