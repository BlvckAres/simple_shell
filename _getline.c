#include "main.h"

/**
* _getline - Read The Input By User From Stdin
* Return: Input
*/
char *_getline()
{
int xy, buffsize = BUFSIZE, rd;
char c = 0;
char *_buffer = malloc(buffsize);

	if (_buffer == NULL)
	{
		free(_buffer);
		return (NULL);
	}

	for (xy = 0; c != EOF && c != '\n'; xy++)
	{
		fflush(stdin);
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == 0)
		{
			free(_buffer);
			exit(EXIT_SUCCESS);
		}
		_buffer[xy] = c;
		if (_buffer[0] == '\n')
		{
			free(_buffer);
			return ("\0");
		}
		if (xy >= buffsize)
		{
			_buffer = _realloc(_buffer, buffsize, buffsize + 1);
			if (_buffer == NULL)
			{
				return (NULL);
			}
		}
	}
	_buffer[xy] = '\0';
	remveCmmnts(_buffer);
	return (_buffer);
}

/**
 * remveCmmnts - remove everything after #
 * @_buffer: input;
 * Return:void
 */
void remveCmmnts(char *_buffer)
{
	int xy;

		for (xy = 0; _buffer[xy] != '\0'; xy++)
		{
			if (_buffer[xy] == '#')
			{
			_buffer[xy] = '\0';
			break;
			}
	}
}
