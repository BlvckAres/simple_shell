#include "main.h"
/**
 * check_delim - checks If A char Match Any Char *
 * @c: char To Check
 * @str: strng To Check
 * Return: 1 Succes, 0 Failed
 */
unsigned int check_delim(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - token A strng into token_str (strtrok)
 * @str: strng
 * @delim: Delimiter
 * Return: Pointer To The Next Token Or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *tkns;
	static char *xj;
	unsigned int i;

	if (str != NULL)
		xj = str;
	tkns = xj;
	if (tkns == NULL)
		return (NULL);
	for (i = 0; tkns[i] != '\0'; i++)
	{
		if (check_delim(tkns[i], delim) == 0)
			break;
	}
	if (xj[i] == '\0' || xj[i] == '#')
	{
		xj = NULL;
		return (NULL);
	}
	tkns = xj + i;
	xj = tkns;
	for (i = 0; xj[i] != '\0'; i++)
	{
		if (check_delim(xj[i], delim) == 1)
			break;
	}
	if (xj[i] == '\0')
		xj = NULL;
	else
	{
		xj[i] = '\0';
		xj = xj + i + 1;
		if (*xj == '\0')
			xj = NULL;
	}
	return (tkns);
}
