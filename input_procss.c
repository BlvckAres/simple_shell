#include "shell.h"

char *get_args(char *line, int *exec_retn);
int call_args(char **args, char **frnt, int *exec_retn);
int run_args(char **args, char **frnt, int *exec_retn);
int handle_args(int *exec_retn);
int check_args(char **args);

/**
 * get_args - Gets a cmd from standard input.
 * @line: A buf to store the cmd.
 * @exec_retn: The return value of the last executed cmd.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored cmd.
 */
char *get_args(char *line, int *exec_retn)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exec_retn));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exec_retn);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - Partitions operators from cmds and calls them.
 * @args: An array of arguments.
 * @frnt: A double pointer to the beginning of args.
 * @exec_retn: The return value of the parent process' last executed cmd.
 *
 * Return: The return value of the last executed cmd.
 */
int call_args(char **args, char **frnt, int *exec_retn)
{
	int ret, index;

	if (!args[0])
		return (*exec_retn);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, frnt, exec_retn);
			if (*exec_retn != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, frnt, exec_retn);
			if (*exec_retn == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, frnt, exec_retn);
	return (ret);
}

/**
 * run_args - Calls the execution of a cmd.
 * @args: An array of arguments.
 * @frnt: A double pointer to the beginning of args.
 * @exec_retn: The return value of the parent process' last executed cmd.
 *
 * Return: The return value of the last executed cmd.
 */
int run_args(char **args, char **frnt, int *exec_retn)
{
	int ret, i;
	int (*builtin)(char **args, char **frnt);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, frnt);
		if (ret != EXIT)
			*exec_retn = ret;
	}
	else
	{
		*exec_retn = execute(args, frnt);
		ret = *exec_retn;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a cmd.
 * @exec_retn: The return value of the parent process' last executed cmd.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed cmd.
 */
int handle_args(int *exec_retn)
{
	int ret = 0, index;
	char **args, *line = NULL, **frnt;

	line = get_args(line, exec_retn);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exec_retn = 2;
		free_args(args, args);
		return (*exec_retn);
	}
	frnt = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, frnt, exec_retn);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, frnt, exec_retn);

	free(frnt);
	return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized cmds and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}

