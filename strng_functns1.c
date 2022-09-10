#include "main.h"

/**
 * _strcmp - Compares Two strngs
 * @s1:strng 1
 * @s2:strng 2
 * Return: 0 If Identical result if diffrent
 */
int _strcmp(char *s1, char *s2)
{
int cmp = 0, xy, len1, len2;
len1 = _strlen(s1);
len2 = _strlen(s2);

	if (s1 == NULL || s2 == NULL)
		return (1);
	if (len1 != len2)
		return (1);
	for (xy = 0; s1[xy]; xy++)
	{
		if (s1[xy] != s2[xy])
		{
			cmp = s1[xy] - s2[xy];
			break;
		}
		else
			continue;
	}
	return (cmp);
}
/**
 * _isalpha - Check if Alphabtic
 *@c: char
 * Return: 1 If True 0 If Not
 */
int _isalpha(int c)
{
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * _int2str - Convert Integer To Char
 * @n: Int To Convert
 * Return: Char Pointer
 */
char *_int2str(unsigned int n)
{
	int len = 0, xy = 0;
	char *s;

	len = intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (n / 10)
	{
		s[xy] = (n % 10) + '0';
		n /= 10;
		xy++;
	}
	s[xy] = (n % 10) + '0';
	array_rev(s, len);
	s[xy + 1] = '\0';
	return (s);
}
/**
 *  array_rev - Reverse Array
 * @arr:Array To Reverse
 * @len:Length Of Array
 * Return: Void(Reverse Array)
 */
void array_rev(char *arr, int len)
{
	int xy;
	char tmp;

	for (xy = 0; xy < (len / 2); xy++)
	{
		tmp = arr[xy];
		arr[xy] = arr[(len - 1) - xy];
		arr[(len - 1) - xy] = tmp;
	}
}
/**
 * intlen - Determine Length Of Int
 * @num: Given Int
 * Return: Length Of Int
 */
int intlen(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}
