#include "shell.h"
void alias_func(char **cmdarr, const char *prgname);
void handlemultiReg(char **command, const char *prgname);
void process_command(const char *command);
int convertStringToArray(char *inputString, char ***commandArray);
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
	_writef("%s: Error opening file %s\n", p, filename);
		return;
	}

	write(newAliasFile, "alias ", 6);
	write(newAliasFile, aN, _strlen(aN));
	write(newAliasFile, "='", 2);
	write(newAliasFile, nV, _strlen(nV));
	write(newAliasFile, "'\n", 2);

	close(newAliasFile);
}


/**
 * process_command - =======
 * @command: =========
 * Return: =======
 */
void process_command(const char *command)
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
			retrieve_alias(args[i]);
		}
	}

	/*Free the dynamically allocated argument pointers*/
	for (i = 0; i < numArgs; i++)
	{
		free(args[i]);
	}
}
/**
 * convertStringToArray - ======
 * @inputString: =========
 * @commandArray: ==========
 * Return: ============
 */
int convertStringToArray(char *inputString
		, char ***commandArray)
{
	const char *delimiter = " \t\n";
	int count = 0;
	int length;
	char *keyword = "alias";
	char *token = _strtok3(inputString, delimiter);

	if (_strncmp(token, keyword, _strlen(keyword)) != 0)
	{
		return (0);
		/*Input string does not start with the keyword "alias"*/
	}

	while ((token = _strtok3(NULL, delimiter)) != NULL)
	{
		if (token[0] == '\'')
			continue;

		length = _strlen(keyword) +  _strlen(token) + 1;
		(*commandArray)[count] = malloc(length + 1);
		_strcpy((*commandArray)[count], keyword);
		_strcat((*commandArray)[count], " ");
		_strcat((*commandArray)[count], token);
		_strcat((*commandArray)[count], "\0");
		count++;
	}
	return (count);
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
				&& _strlen(*command) > 6 && equals == 0)
		{
			process_command(*command);
		}
		else if (_strncmp(*command, "alias ", 6) == 0
				&& _strlen(*command) > 7 && equals >= 1)
		{
			callupdatealias(*command, prgname);
		}
		else
		{
			_writef("Unknown command: %s\n", *command);
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
	if (_strcmp(cmd, "alias") == 0)
	{
		load_aliases();
		return (0);
	}
	else if ((_strncmp(cmd, "alias ", 6) == 0)
			&&  _strlen(cmd) > 6 && equals == 0)
	{
		process_command(cmd);
		return (0);
	}
	else if (_strncmp(cmd, "alias ", 6) == 0 && _strlen(cmd) > 7 && equals >= 1)
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
		j = j + _strlen(cmdarr[i]) + 1;

	cmd  = malloc(sizeof(char) * (j + 1));
	_strcpy(cmd, cmdarr[0]);
	for (i = 1; cmdarr[i]; i++)
	{
		_strcat(cmd, " ");
		_strcat(cmd, cmdarr[i]);
	}
	_strcat(cmd, "\0");
	cmdArray = malloc(sizeof(char *) * _strlen(cmd));
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
			_writef("%s: Unknown command: %s\n", prgname, cmd);
	}
	free(cmd);
}
