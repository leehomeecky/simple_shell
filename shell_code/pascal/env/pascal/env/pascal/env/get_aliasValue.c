#include "shell.h"
char *get_aliasValue(char *name);
/*Function to retrieve and display an alias*/
/**
 * get_aliasValue - ==========
 * @name: =============
 * Return: void
 */
char *get_aliasValue(char *name)
{
	char alias_name[MAX_ALIAS_NAME];
	char alias_value[MAX_ALIAS_VALUE];
	char *equalsSign, *quoteEnd, *quoteStart, *alias;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	char line[BUFFER_SIZE];
	int i, fileDescriptor, lineLength = 0;

	fileDescriptor = open(ALIAS_FILE, O_CREAT | O_RDWR, 0666);
	if (fileDescriptor == -1)
	{
		perror("Error opening aliases file");
		return (NULL);
	}

	while ((bytesRead = read(fileDescriptor, buffer, BUFFER_SIZE)) > 0)
	{
	for (i = 0; i < bytesRead; i++)
	{
	if (buffer[i] == '\n')
	{
	line[lineLength] = '\0';
	/* Null-terminate the line*/
	if (_strstr(line, "alias") != NULL)
	{
	equalsSign = _strchr(line, '=');
	if (equalsSign != NULL)
	{
	quoteStart = _strchr(line, '\'');
	quoteEnd = _strrchr(line, '\'');
	if (quoteStart != NULL && quoteEnd != NULL && quoteEnd > quoteStart)
	{
	_strncpy(alias_name, line + 6, equalsSign - (line + 6));
	alias_name[equalsSign - (line + 6)] = '\0';
	_strncpy(alias_value, quoteStart + 1, quoteEnd - quoteStart - 1);
	alias_value[quoteEnd - quoteStart - 1] = '\0';
	/* Perform the comparison and write to stdout*/
	if (_strcmp(alias_name, name) == 0)
	{
	alias = alias_value;
	return (alias);
	}
	}
	}
	}
	lineLength = 0;
	}
	else
	{
	line[lineLength] = buffer[i];
	lineLength++;
			}
		}
	}
	/*============================*/
	close(fileDescriptor);
	return (NULL);
}
