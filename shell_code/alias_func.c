#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
void handlemultiReg(char **command);
void update_alias(char *aliasName, char *filename, char *newValue);
void process_command(const char *command);
int convertStringToArray(char *inputString, char ***commandArray);
/**
 * update_alias - =============
 * @aliasName: ======
 * @filename: =======
 * @newValue: =======
 * Return: ===========
 */
void update_alias(char *aliasName, char *filename, char *newValue)
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

		while (linePtr < lineEnd) {
			lineBreak = _strchr(linePtr, '\n');
			if (lineBreak == NULL) {
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
		_rename("temp.txt","aliases.txt"); /* Rename the temporary file to the original filename*/
	}
	else
	{
		/* remove("temp.txt"); Remove the temporary file since no alias was removed*/
	}

	/*Add the new alias entry*/
	newAliasFile = open(filename, O_WRONLY | O_APPEND);
	if (newAliasFile == -1)
	{
		printf("Error opening file %s\n", filename);
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
void process_command(const char* command) {
	const int maxArgs = 50;  /*Maximum number of arguments*/
	char *args[100];     /*Array to store argument pointers*/
	int numArgs = 0;         /*Number of arguments*/
	char *token;
	int i;

	/*Tokenize the command and store arguments in the array*/
	token = _strtok3((char*)command, " ");
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
	const char* delimiter = " \t\n";
	int count = 0;
	int length;
	char *keyword = "alias";
	char *token = _strtok3(inputString, delimiter);
	if (_strncmp(token, keyword, _strlen(keyword)) != 0)
	{
		return 0;
		/*Input string does not start with the keyword "alias"*/
	}

	while ((token = _strtok3(NULL, delimiter)) != NULL)
	{
		length = _strlen(keyword) +  _strlen(token) + 1;
		(*commandArray)[count] = malloc(length + 1);  /* Allocate memory for the command*/
		/*_snprintf((*commandArray)[count], length + 1, "%s %s", keyword, token);*/
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
 * Return: =========
 */
void handlemultiReg(char **command)
{
	int equals = 1;
	char alias_name[1024];
	char alias_value[1024];
	char *equalsSign, *quoteEnd, *quoteStart;
	
	while(*command)
	{
	if (_strncmp(*command, "alias ", 6) == 0 && _strlen(*command) > 6 && equals == 0)
	{
	process_command(*command);
	}
	else if (_strncmp(*command, "alias ", 6) == 0 && _strlen(*command) > 7)
	{
	if (_strstr(*command, "alias") != NULL)
	{
equalsSign = _strchr(*command, '=');
	if (equalsSign != NULL)
	{
quoteStart = _strchr(*command, '\'');
quoteEnd = _strrchr(*command, '\'');
	if (quoteStart != NULL && quoteEnd != NULL && quoteEnd > quoteStart)
	{
	_strncpy(alias_name, *command + 6, equalsSign - (*command + 6));
	alias_name[equalsSign - (*command + 6)] = '\0';
	_strncpy(alias_value, quoteStart + 1, quoteEnd - quoteStart - 1);
	alias_value[quoteEnd - quoteStart - 1] = '\0';
	update_alias(alias_name, ALIAS_FILE, alias_value); /*Update the alias*/
	}
	else
	{					/*_writef("Wrong Format\n");*/
	}
	}
	}
	else
	{
	perror("Invalid alias format. Use: alias name='value'\n");
	}
	}
else if (_strcmp(*command, "exit") == 0)
	{
	break;
	}
	else
	{
_writef("Unknown command: %s\n", *command);
	}
	command++;
	}
}

/**
 * aliad_func - =====
 * @cmdarr: ======
 * @prgname: ========
 * Return: ========
 */
void alias_func(char **cmdarr, const char *prgname)
{
		char *command = NULL;
		/*char *command = *cmd;*/
		size_t bufsize = 0;
		ssize_t len;
		int i = 0, j = 0;
		/*    int size; */
		int equals = 0;
		char **commandArray;
		char alias_name[1024];
		char alias_value[1024];
		char *equalsSign, *quoteEnd, *quoteStart;

	_strcpy(cmdarr[0], "alias");

	for (i = 0; cmdarr[i]; i++)
		j = j + _strlen(cmdarr[i]) + 1;

	command  = malloc(sizeof(char) * (j + 1));
		_strcpy(command, cmdarr[0]);
		for (i = 1; cmdarr[i]; i++)
		{
		_strcat(command, " ");
		_strcat(command, cmdarr[i]);
		}
	
		_strcat(command, "\0");

		commandArray = malloc(sizeof(char*) * _strlen(command));
		i = 0;
		while (command[i]) {
			if (command[i] == '=')
			{
				equals = equals +  1;
			}
			i++;
		}
		/*handle multi registrstion of alias*/
		if (equals >= 2)
		{
			/*removeExtraSpaces(command);*/
			convertStringToArray(command, &commandArray);
			handlemultiReg(commandArray);
		}
		else
		{
			removeExtraSpaces(command);

			if (_strcmp(command, "alias") == 0) {
				load_aliases();
			}
			else if (_strncmp(command, "alias ", 6) == 0 &&  _strlen(command) > 6 && equals == 0)
			{
				process_command(command);
			} else if (_strncmp(command, "alias ", 6) == 0 && _strlen(command) > 7)
			{
				if (_strstr(command, "alias") != NULL)
				{
					equalsSign = _strchr(command, '=');
					if (equalsSign != NULL)
					{
						quoteStart = _strchr(command, '\'');
						quoteEnd = _strrchr(command, '\'');
						if (quoteStart != NULL && quoteEnd != NULL && quoteEnd > quoteStart)
						{
							_strncpy(alias_name, command + 6, equalsSign - (command + 6));
							alias_name[equalsSign - (command + 6)] = '\0';
							_strncpy(alias_value, quoteStart + 1, quoteEnd - quoteStart - 1);
							alias_value[quoteEnd - quoteStart - 1] = '\0';
							update_alias(alias_name, ALIAS_FILE, alias_value); /* Update the alias*/
						}
						else
						{
							/*	_writef("wrong format\n");*/
						}
					}
				} else {
					_writef("Invalid alias format. Use: alias name='value'\n");
				}
			} else if (_strcmp(command, "exit") == 0) {
	/*			break;*/
			} else {
	/*			_writef("Unknown command: %s\n", command);*/
	perror(prgname);
			}
		}
		free(commandArray);
		free(command);
}
