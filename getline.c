#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

/**
 *	custom_getline - The getline function
 *	@lineptr: The input storage
 *	@n: storage allocation
 *	@stream: File
 *
 *	Return: returns num
 */

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[MAX_BUFFER_SIZE];
	static size_t buf_pos;
	static ssize_t bytes_read;
	size_t i = 0;
	int c;

	if (buf_pos == 0)
	{bytes_read = read(fileno(stream), buffer, MAX_BUFFER_SIZE);
		if (bytes_read <= 0)
		{return (-1);
		}
	}
	if (*lineptr == NULL || (ssize_t)(*n) < bytes_read)
	{*n = bytes_read + 1;
		*lineptr = (char *)realloc(*lineptr, *n);
		if (*lineptr == NULL)
		{return (-1);
		}
	}
	while (i < *n - 1)
	{c = buffer[buf_pos++];
		if (c == '\n' || c == EOF)
		{
			(*lineptr)[i] = '\0';
			return (i);
		i
		(*lineptr)[i++] = c;
	}
	(*lineptr)[i] = '\0';
	return (i);
}
