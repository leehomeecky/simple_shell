#include "shell.h"

/**
 * _error - function to print error to standard error
 *
 * @shell: the name of the shell
 * @cmd: the command
 * @error_no: error number
 * @msg: message to print out
 */

void _error(const char *shell, char *cmd, char error_no, char *msg)
{
	char *cat1, *cat2, *cat3, *cat4, *cat5;

	cat1 = str_cat((char *)shell, ": ");
	cat2 = char_cat(cat1, error_no);
	cat3 = str_cat(cat2, ": ");
	cat4 = str_cat(cat3, cmd);
	cat5 = str_cat(cat4, msg);
	perror(cat5);
	free(cat1);
	free(cat2);
	free(cat3);
	free(cat4);
	free(cat5);
}
