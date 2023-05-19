/*for write */
#include "shell.h"
/**
 * _writef - ========
 * @format: ===========
 * Return: ===========
 */
void _writef(const char *format, ...)
{
	/*Set up the argument list*/
	va_list args;
	char *str;
	size_t len;

	va_start(args, format);

	/*Iterate over the format string*/
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
		if (*format == 's')
		{
				/*Fetch the next argument as a string*/
		str = va_arg(args, char *);

				/*Get the length of the string*/
				len = _strlen(str);

				/*Write the string to the standard output*/
				write(STDOUT_FILENO, str, len);
			}
		}
		else
		{
			/*Write regular characters to the standard output*/
			write(STDOUT_FILENO, format, 1);
		}
		format++;
	}

	/*Clean up the argument list*/
	va_end(args);
}

