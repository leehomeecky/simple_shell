#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellt.h"

void load_aliases();                      void retrieve_alias(char* name);

void removeExtraSpaces(char *str) 
{
	int i, j;
	int len = _strlen(str);

    /*Remove leading spaces*/
	while (len > 0 && str[0] == ' ')
	{
        for (i = 0; i < len; i++) {
            str[i] = str[i + 1];
        }
        len--;
    }

    /*Remove extra spaces*/
    for (i = 0; i < len - 1; i++) 
    {
        if (str[i] == ' ' && str[i + 1] == ' ') {
            for (j = i; j < len; j++) {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }

    /*Remove trailing spaces */
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
}


/*Function to load aliases from file*/
void load_aliases() 
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

    while ((bytesRead = read(fileDescriptor, buffer, BUFFER_SIZE)) > 0) {
        for (i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                line[lineLength] = '\0'; 
		/* Null-terminate the line*/
                _writef("%s\n", line);
                lineLength = 0;
            } else {
                line[lineLength] = buffer[i];
                lineLength++;
            }
        }
    }
close(fileDescriptor);
}


/*Function to save an alias to file*/
void save_alias(char* name, char* value) 
{
    int fileDescriptor;
    char *filename = ALIAS_FILE;  
    
    /*Open the file in append mode*/
    fileDescriptor = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fileDescriptor < 0) {
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

void update_alias(char* aliasName, char* filename, char* newValue)
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
    if (file == -1) {
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

    while ((bytesRead = read(file, line, sizeof(line))) > 0) {
        linePtr = line;
        lineEnd = line + bytesRead;

        while (linePtr < lineEnd) {
lineBreak = _strchr(linePtr, '\n');
            if (lineBreak == NULL) {
                lineBreak = lineEnd;
            }

	    lineLength = lineBreak - linePtr;
            if (_strncmp(linePtr, "alias ", 6) == 0) {
                aliasStart = linePtr + 6;
                equalsSign = _strstr(aliasStart, "=");
                if (equalsSign != NULL) {
                aliasLength = equalsSign - aliasStart;
             /* char  alias[aliasLength + 1];*/
                    _strncpy(alias, aliasStart, aliasLength);
                    alias[aliasLength] = '\0';

                    if (_strcmp(alias, aliasName) == 0) {
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
    } else {
       /* remove("temp.txt"); Remove the temporary file since no alias was removed*/
    }

    /*Add the new alias entry*/
    newAliasFile = open(filename, O_WRONLY | O_APPEND);
    if (newAliasFile == -1) {
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


/*Function to retrieve and display an alias*/
void retrieve_alias(char *name)
{
	char alias_name[MAX_ALIAS_NAME];
	char alias_value[MAX_ALIAS_VALUE];
	char *equalsSign, *quoteEnd, *quoteStart;
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
	if (buffer[i] == '\n') {
		line[lineLength] = '\0'; 
		/* Null-terminate the line*/ 
		if (_strstr(line, "alias") != NULL) 
		{
        equalsSign = _strchr(line, '=');
            if (equalsSign != NULL) {
	quoteStart = _strchr(line, '\'');
        quoteEnd = _strrchr(line, '\'');

                if (quoteStart != NULL && quoteEnd != NULL && quoteEnd > quoteStart) {

_strncpy(alias_name, line + 6, equalsSign - (line + 6));
	alias_name[equalsSign - (line + 6)] = '\0';
                    _strncpy(alias_value, quoteStart + 1, quoteEnd - quoteStart - 1);
		    alias_value[quoteEnd - quoteStart - 1] = '\0';

        /* Perform the comparison and write to stdout*/
                    if (_strcmp(alias_name, name) == 0) {
                        _writef("%s='%s'\n", alias_name, alias_value);
seen = 1;
                    }

                }
            }
        }
lineLength = 0;
	} else {
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

void process_command(const char* command) {
    const int maxArgs = 50;  /*Maximum number of arguments*/
    char *args[100];     /*Array to store argument pointers*/
    int numArgs = 0;         /*Number of arguments*/
char *token;
int i;

    /*Tokenize the command and store arguments in the array*/
    token = strtok((char*)command, " ");
    while (token != NULL && numArgs < maxArgs) {
        args[numArgs] = _strdup(token);
        numArgs++;
        token = strtok(NULL, " ");
    }

    /*Check if the command starts with "alias" and has at least one argument*/
    if (numArgs >= 2 && _strcmp(args[0], "alias") == 0) {
        /*Pass the arguments one by one to the retrieve_alias() function*/
        for (i = 1; i < numArgs; i++) {
            retrieve_alias(args[i]);
        }
    }

    /*Free the dynamically allocated argument pointers*/
    for (i = 0; i < numArgs; i++) {
        free(args[i]);
    }
}

int convertStringToArray(char* inputString
, char*** commandArray) {
    const char* delimiter = " \t\n";
    int count = 0;
    int length;
    char *keyword = "alias";
char* token = strtok(inputString, delimiter);
if (strncmp(token, keyword, strlen(keyword)) != 0) {
        return 0;
	/*Input string does not start with the keyword "alias"*/
	}

    while ((token = strtok(NULL, delimiter)) != NULL) {                                     length = strlen(keyword) + strlen(token) + 1;
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

void handlemultiReg(char **command)
{
	int equals = 1;
	char alias_name[1024];
	char alias_value[1024];
	char *equalsSign, *quoteEnd, *quoteStart;
	while(*command)
	{
if (strncmp(*command, "alias ", 6) == 0 && _strlen(*command) > 6 && equals == 0) 
{
               process_command(*command);
        } else if (strncmp(*command, "alias ", 6) == 0 && _strlen(*command) > 7) 
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
	{
	/*_writef("Wrong Format\n");*/
	}
	}      
		/*Update the alias*/
	}
    else 
    {
                perror("Invalid alias format. Use: alias name='value'\n");
            }
        } else if (_strcmp(*command, "exit") == 0) {
            break;
        } else {
            _writef("Unknown command: %s\n", *command);
        }

command++;
	}
}

int main() 
{

	while(1){
   char *command = NULL;
    size_t bufsize = 0;
    ssize_t len;
    int i = 0;
    int equals = 0;
    char **commandArray;
    char alias_name[1024]; 
    char alias_value[1024];
    char *equalsSign, *quoteEnd, *quoteStart;
        _writef("$ ");

	len = getline(&command, &bufsize, stdin);
if (len == -1)
	return (-1);
	/*Remove the newline character if present*/
if (command[len - 1] == '\n')
	command[len - 1] = '\0';
commandArray = malloc(sizeof(char*) * _strlen(command));
	
        while (command[i]) {
            if (command[i] == '=') {
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
        } else if (_strncmp(command, "alias ", 6) == 0 && _strlen(command) > 6 && equals == 0) {
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
            break;
        } else {
            _writef("Unknown command: %s\n", command);
        }
}
free(commandArray);
free(command);
    }
    return 0;
}
