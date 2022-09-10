#include "main.h"

/**
 * parseInput - parse Line Of Input
 * @input:User Input To parse
 * Return: Array Of Char (parsed):Simple Shell
 */
char **parseInput(char *input)
{
	char **tkens;
	char *token;
	int i, buffsize = BUFSIZE;

	if (input == NULL)
		return (NULL);
	tkens = malloc(sizeof(char *) * buffsize);
	if (!tkens)
	{
		perror("sh");
		return (NULL);
	}

	token = _strtok(input, "\n ");
	for (i = 0; token; i++)
	{
		tkens[i] = token;
		token = _strtok(NULL, "\n ");
	}
	tkens[i] = NULL;

	return (tkens);
}
