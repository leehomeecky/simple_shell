#include "shell.h"
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
		_writef("Error opening file %s\n", fn);
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
