#include "shell.h"
int convertStringToArray(char *command, char ***commandArray);
void update_alias(char *aN, char *fn, char *nV, const char *p);
/**
 * update_alias - =============
 * @aN: ======
 * @fn: =======
 * @nV: =======
 * @p: ======
 * Return: ===========
 */
void update_alias(char *aN, char *fn, char *nV, const char *p)
{
	char line[1024];
	size_t lineLength;
	char *aliasStart,  *lineBreak, *linePtr, *lineEnd, *equalsSign;
	char  alias[500];
	size_t aliasLength;
	int tempFile, file,  aliasExists = 0;
	ssize_t bytesRead;

	file = open(fn, O_CREAT | O_RDWR, 0666);
	if (file == -1)
	{
		perror(p);
		return;
	}
	tempFile = open("/root/temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tempFile == -1)
	{
		perror(p);
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
					_strncpy(alias, aliasStart, aliasLength);
					alias[aliasLength] = '\0';
					if (_strcmp(alias, aN) == 0)
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
	alchecks(aliasExists, fn, aN, nV, p);
}





/**
 * convertStringToArray - =======
 * @command: =========
 * @commandArray: ==========
 * Return: count
 */
int convertStringToArray(char *command, char ***commandArray)
{
	char alias_name[1024];
	char alias_value[1024];
	char *equalsSign, *quoteEnd, *quoteStart = NULL;
	int length;
	int i = 0, qc = 0, count = 0;
	int ok;

	command = command + 5;
	while (*command != '\0')
	{
		if (*command == '=' && quoteStart == NULL)
		{
			_strncpy(alias_name, command - i, i);
			alias_name[i] = 0;
			equalsSign = command;
			removeExtraSpaces(alias_name);
		}
		if (*command == '\'')
		{
			qc++;
			if (qc == 1)
			{
				quoteStart = command;
			}
			if (qc == 2)
			{
				quoteEnd = command;
				command++;
				i = 0;
			}
		}
		ok = quoteStart - equalsSign;
		if (equalsSign != NULL)
		{
			if (quoteStart != NULL && quoteEnd != NULL
				&& quoteEnd > quoteStart && ok == 1)
			{


				_strncpy(alias_value, quoteStart + 1, quoteEnd - quoteStart - 1);
				alias_value[quoteEnd - quoteStart - 1] = '\0';

				length = _strlen(alias_name) +  _strlen(alias_value) + 10;
				(*commandArray)[count] = malloc(length + 1);
				_strcpy((*commandArray)[count], "alias ");
				_strcat((*commandArray)[count], alias_name);
				_strcat((*commandArray)[count], "=");
				_strcat((*commandArray)[count], "'");
				_strcat((*commandArray)[count], alias_value);
				_strcat((*commandArray)[count], "'");
				_strcat((*commandArray)[count], "\0");

				quoteEnd = NULL;
				quoteStart = NULL;
				equalsSign = NULL;
				qc = 0;
				i = 0;
				count++;
				/*	printf("%s \n", alias_value);*/
			}
			else
			{					/*_writef("Wrong Format\n");*/
			}
		}
		if (*command == '\0')
			return (count);
		i++;
		command++;
	}
	return (count);
}
