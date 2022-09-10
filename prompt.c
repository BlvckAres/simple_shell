#include "main.h"

/**
 * showShellTerminal - show Shell Prompt
 */
void showShellTerminal(void)
{
	PRINTER("$ ");
}
/**
 * printError - show Error Based on cmmd and How Many Time Shell Looped
 * @input:User Input
 * @countr:Simple Shell Count Loop
 * @argv:Program Name
 * Return: Void
 */
void printError(char *input, int countr, char **argv)
{
	char *er;

	PRINTER(argv[0]);
	PRINTER(": ");
	er = _int2str(countr);
	PRINTER(er);
	free(er);
	PRINTER(": ");
	PRINTER(input);
	PRINTER(": not found\n");
}
