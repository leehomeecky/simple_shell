#include "shell.h"
void removeExtraSpaces(char *str);
void load_aliases(void);
void save_alias(char *name, char *value);
void retrieve_alias(char *name);
/**
 * removeExtraSpaces - =========
 * @str: =====
 * Return: ==========
 */
void removeExtraSpaces(char *str)
{
	int i, j;
	int len = _strlen(str);

	/*Remove leading spaces*/
	while (len > 0 && str[0] == ' ')
	{
	for (i = 0; i < len; i++)
	{
	str[i] = str[i + 1];
	}
	len--;
	}

	/*Remove extra spaces*/
	for (i = 0; i < len - 1; i++)
	{
	if (str[i] == ' ' && str[i + 1] == ' ')
	{
	for (j = i; j < len; j++)
	{
	str[j] = str[j + 1];
	}
	len--;
	i--;
	}
	}

	/*Remove trailing spaces */
	while (len > 0 && str[len - 1] == ' ')
	{
	str[len - 1] = '\0';
	len--;
	}
}


/*Function to load aliases from file*/
/**
 *load_aliases - =======
 *Return: void
 */
void load_aliases(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	char line[BUFFER_SIZE];
	int i, fileDescriptor, lineLength = 0;

	/*    fileDescriptor = open(ALIAS_FILE, O_RDONLY);*/

	fileDescriptor = open(ALIAS_FILE, O_CREAT | O_RDWR, 0666);
	if (fileDescriptor == -1)
	{
	perror("Error opening aliases file");
	return;
	}

	while ((bytesRead = read(fileDescriptor, buffer, BUFFER_SIZE)) > 0)
	{
	for (i = 0; i < bytesRead; i++)
	{
	if (buffer[i] == '\n')
	{
	line[lineLength] = '\0';

	/* Null-terminate the line*/
	_writef("%s\n", line);
	lineLength = 0;
	}
	else
	{
	line[lineLength] = buffer[i];
	lineLength++;
	}
	}
	}
	close(fileDescriptor);
}

/**
 * save_alias - ========
 * @name: ========
 * @value: ==========
 * Return: ============
 */
/*Function to save an alias to file*/
void save_alias(char *name, char *value)
{
	int fileDescriptor;
	char *filename = ALIAS_FILE;

	/*Open the file in append mode*/
	fileDescriptor = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fileDescriptor < 0)
	{
	_writef("Error opening the file.\n");
	return;
	}

	/*Write the formatted string to the file*/
	write(fileDescriptor, "alias ", 6);
	write(fileDescriptor, name, _strlen(name));
	write(fileDescriptor, "='", 2);
	write(fileDescriptor, value, _strlen(value));
	write(fileDescriptor, "'\n", 2);

	/*Close the file*/
	close(fileDescriptor);

}




/*Function to retrieve and display an alias*/
/**
 * retrieve_alias - ==========
 * @name: =============
 * Return: void
 */
void retrieve_alias(char *name)
{
	char alias_name[MAX_ALIAS_NAME];
	char alias_value[MAX_ALIAS_VALUE];
	char *equalsSign, *quoteEnd, *quoteStart, *alias;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	char line[BUFFER_SIZE];
	int seen, i, fileDescriptor, lineLength = 0;
	/*	fileDescriptor = open(ALIAS_FILE,O_CREAT | O_RDONLY, 0666);*/
	fileDescriptor = open(ALIAS_FILE, O_CREAT | O_RDWR, 0666);
	if (fileDescriptor == -1)
	{
	perror("Error opening aliases file");
	return;
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
								/* formatted output with puts*/
	alias = malloc(sizeof(char)
			* (_strlen(alias_name) +  4 + _strlen(alias_value)));
	_strcat(alias, alias_name);
	_strcat(alias, "=");
	_strcat(alias, "'");
	_strcat(alias, alias_value);
	_strcat(alias, "'");
	_strcat(alias, "\0");
	puts(alias);
	free(alias);
	seen = 1;
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
	if (seen != 1)
	{
		_writef("bash: alias: %s: not foubd\n", name);
	}
	/*============================*/
	close(fileDescriptor);
}
