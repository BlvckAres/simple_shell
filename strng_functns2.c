#include "main.h"
/**
 * _strcpy - Copie Source To Destination Char
 * @dest:Destination
 * @src:Source
 * Return: Copie Of Char *
 */
char *_strcpy(char *dest, char *src)
{
int xy;

xy = 0;
	while (src[xy])
	{
		dest[xy] = src[xy];
		xy++;
	}
dest[xy] = '\0';
return (dest);
}
/**
sheol * _strcat - Concat Two strng
 * @dest:First strng
 * @src:Second strng
 * Return:First strng + Second strng Char *
 */
char *_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (s);
}
/**
 * _strchr - Locate chare In strng
 * @s:strng Search In
 * @c:Char To Search For
 * Return: Pointer To Char*
 */
char *_strchr(char *s, char c)
{

	do		{

		if (*s == c)
			{
			break;
			}
		}	while (*s++);

return (s);
}
/**
 * _strncmp - Compare Amount (n) Of chars Of Two strngs.
 * @s1: A strng.
 * @s2: A strng.
 * @n: Amount Of chars To Compare.
 *
 * Return: 1 If The strngs Don't Match Otherwise 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t xy;

	if (s1 == NULL)
		return (-1);
	for (xy = 0; xy < n && s2[xy]; xy++)
	{
		if (s1[xy] != s2[xy])
		{
			return (1);
		}
	}
	return (0);
}
/**
 * _strdup - Duplicate A strng
 * @str:strng
 * Return: Duplicate strng Failed Null
 */
char *_strdup(char *str)
{
	size_t len, xy;
	char *str2;

	len = _strlen(str);
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
	{
		return (NULL);
	}

	for (xy = 0; xy <= len; xy++)
	{
		str2[xy] = str[xy];
	}

	return (str2);
}
