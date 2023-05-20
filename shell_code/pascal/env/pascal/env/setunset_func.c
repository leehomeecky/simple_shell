#include "shell.h"

/**
 * isValidVariableName - =====
 * @name: =======
 * Return: ======
 */
int  isValidVariableName(char *name)
{
	int i = 0;

    /*Check if the first character is a letter or underscore*/
    if (!_isalpha(name[0]) && name[0] != '_')
	    return (-1);

    /*Check the rest of the characters*/
    for (i = 1; name[i] != '\0'; i++) {
        /* Check if the character is alphanumeric or underscore*/
        if (!_isalnum(name[i]) && name[i] != '_')
            return (-1);
    }

    return (0);
}


/*int main(void)*/
void setunset_func(char **cmdArray, const char *prgname)
{
env_t e;
env_t *ev;
   char *command = NULL;
char *args[50];
/*size_t  bufsize;*/
   loadenv(&e);
   int numArgs=0, maxArgs = 4, i, j;
   char *token;
   ev = &e;
   setload = &e;
   
   if (_strchr(cmdArray[0], 'u') != NULL)
	   _strcpy(cmdArray[0], "unsetenv");
   else
	   _strcpy(cmdArray[0], "setenv");
   
   for (i = 0; cmdArray[i]; i++)
	   j = j + _strlen(cmdArray[i]) + 1;
   
   command  = malloc(sizeof(char) * (j + 1));
   _strcpy(command, cmdArray[0]);
   _strcat(command, " ");
   _strcat(command, cmdArray[1]);
   _strcat(command, " ");
   _strcat(command, cmdArray[2]);
   _strcat(command, "\0");
   if (sizeof(cmdArray) > 3)
   {
	   perror(prgname);
	   return;
	   /*exit*/
   }


/*Tokenize the command and store arguments in the array*/
    token = _strtok3((char*)command, " ");
    while (token != NULL && numArgs < maxArgs) {
        args[numArgs] = _strdup(token);
        numArgs++;
        token = _strtok3(NULL, " ");
    }

    if (isValidVariableName(args[1]) == -1)
    {
_writef("hsh: %s: %s: Not a valid identifier\n", args[0], args[1]);
    }
    else if (_strcmp(args[0], "setenv") == 0 && numArgs == 3)
	    _setenv(args[1], args[2], ev);
    
/*	   perror("setenv: too many arguments");*/
    else if(_strcmp(args[0], "unsetenv") == 0 && numArgs == 2)
	    _unset(args[1], ev);
    else
	    _writef("Not a valid command\n");

free(command);


}
