#include <stdarg.h>
#include <stddef.h>
#include "shellt.h"
int _snprintf(char* buffer, size_t size, const char* format, ...)
{
	const char *str, *fmt;
	int written = 0; // Number of characters written to the buffer
    size_t remaining = size; // Remaining space in the buffer
    char* dest = buffer; // Destination pointer for writing characters

    va_list args;
    va_start(args, format);

    // Iterate through the format string
    for (fmt = format; *fmt != '\0'; ++fmt)
    {
        if (*fmt != '%')
        {
            if (remaining > 1)
            {
                *dest++ = *fmt;
                --remaining;
            }
            ++written;
        }
        else if (*(fmt + 1) == '%')
        {
            if (remaining > 1)
            {
                *dest++ = '%';
                --remaining;
            }
            ++fmt; // Skip the second '%'
            ++written;
        }
        else if (*(fmt + 1) == 's')
        {
            // Handle the %s placeholder
           str = va_arg(args, const char*);
            while (*str != '\0' && remaining > 1)
            {
                *dest++ = *str++;
                --remaining;
                ++written;
            }
            ++fmt; // Skip the 's'
        }
        else
        {
            // Invalid format specifier, ignore it
            ++written;
        }

        if (remaining == 1)
            break; // Buffer full, stop processing
    }

    va_end(args);

    if (remaining > 0)
        *dest = '\0'; // Null-terminate the string if space allows

    return (written);
}

