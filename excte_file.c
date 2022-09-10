#include "main.h"
/**
 * read_file - Read cmmd From File
 * @filename:Filename
 * @argv:Program Name
 * Return: -1 or  0
 */

void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int countr = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		countr++;
		treat_file(line, countr, fp, argv);

	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}
/**
 * treat_file - parse Check cmmd Fork Wait execute in Line of File
 * @line: Line From A File
 * @countr:Error countr
 * @fp:File Descriptor
 * @argv:Program Name
 * Return : execute A line void
 */
void treat_file(char *line, int countr, FILE *fp, char **argv)
{
	char **cmd;
	int st = 0;

	cmd = parseInput(line);

		if (_strncmp(cmd[0], "exit", 4) == 0)
		{
			exit_cmmd_for_file(cmd, line, fp);
		}
		else if (check_builtin(cmd) == 0)
		{
			st = handle_builtin(cmd, st);
			free(cmd);
		}
		else
		{
			st = check_cmd(cmd, line, countr, argv);
			free(cmd);
		}
}
/**
 * exit_cmmd_for_file - Exit Shell Case Of File
 * @line: Line From A File
 * @cmd: parsed cmmd
 * @fd:File Descriptor
 * Return : Case Of Exit in A File Line
 */
void exit_cmmd_for_file(char **cmd, char *line, FILE *fd)
{
	int state, i = 0;

	if (cmd[1] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) < 0)
		{
			perror("illegal number");
		}
	}
	state = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(state);



}
