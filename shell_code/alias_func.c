#include "shell.h"

void alias_func(char **cmdarr, const char *prgname);
void handlemultiReg(char **command, const char *prgname);
void update_alias(char *a, char *f, char *new, const char *prgname);
void process_command(const char *command);
int convertStringToArray(char *inputString, char ***commandArray);
int checks(char *cmd, int equals, const char *prgname);
/**
 * update_alias - =============
 * @aliasName: ======
 * @filename: =======
 * @newValue: =======
 * @prgname: ======
 * Return: ===========
 */
void update_alias(char *aliasName, char *filename,
		char *newValue, const char *prgname)
{
	char line[1024];
	size_t lineLength;
	char *aliasStart,  *lineBreak;
	char *linePtr, *lineEnd;
	char *equalsSign;
	char  alias[500];
	/*	char alias[1024];*/
	size_t aliasLength;
	int tempFile,  aliasExists = 0;
	ssize_t bytesRead;
	int file, newAliasFile;
	/*    int file = open(filename, O_RDONLY);*/
	file = open(filename, O_CREAT | O_RDWR, 0666);
	if (file == -1)
	{
		_writef("Error opening file %s\n", filename);
		return;
	}

	tempFile = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tempFile == -1)
	{
		_writef("Error creating temporary file\n");
		close(file);
		return;
	}

	while ((bytesRead = read(file, line, sizeof(line))) > 0)
	{
		linePtr = line;
		lineEnd = line + bytesRead;

		while (linePtr < lineEnd)
		{
			lineBreak = _strchr(linePtr, '\n');
			if (lineBreak == NULL)
			{
				lineBreak = lineEnd;
			}

			lineLength = lineBreak - linePtr;
			if (_strncmp(linePtr, "alias ", 6) == 0)
			{
				aliasStart = linePtr + 6;
				equalsSign = _strstr(aliasStart, "=");
				if (equalsSign != NULL)
				{
					aliasLength = equalsSign - aliasStart;
					/* char  alias[aliasLength + 1];*/
					_strncpy(alias, aliasStart, aliasLength);
					alias[aliasLength] = '\0';

					if (_strcmp(alias, aliasName) == 0)
					{
						aliasExists = 1;
						linePtr = lineBreak + 1;
						continue; /*Skip the existing alias line*/
					}
				}
			}
			write(tempFile, linePtr, lineLength);
			write(tempFile, "\n", 1);

			linePtr = lineBreak + 1;
		}
	}

	close(file);
	close(tempFile);

	if (aliasExists)
	{
		/*remove(filename);*/
		_rename(filename, "_temp");
		/* Remove the original file*/
	_rename("temp.txt", "aliases.txt");
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
		/*	printf("Error opening file %s\n", filename);*/
		perror(prgname);
		return;
	}

	write(newAliasFile, "alias ", 6);
	write(newAliasFile, aliasName, _strlen(aliasName));
	write(newAliasFile, "='", 2);
	write(newAliasFile, newValue, _strlen(newValue));
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
	free(cmdArray);
	free(cmd);
}
