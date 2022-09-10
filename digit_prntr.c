#include "main.h"
/**
 * numprnt -Print Unsigned Int Putchar
 * @n: Unisigned Integer
 * Return: Void
 */
void numprnt(unsigned int n)
{
	unsigned int x = n;

	if ((x / 10) > 0)
		numprnt(x / 10);

	_putchar(x % 10 + '0');
}
/**
 * intiPrint -Print Number Putchar
 * @n:Integer
 * Return: void
 */
void intiPrint(int n)
{
	unsigned int x = n;

	if (n < 0)
	{
		_putchar('-');
		x = -x;
	}
	if ((x / 10) > 0)
		numprnt(x / 10);

	_putchar(x % 10 + '0');
}
