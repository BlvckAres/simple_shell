#include "main.h"

/**
 * handle_builtin - Handle Builtin cmmd
 * @cmd: parsed cmmd
 * @er:state of last execute
 * Return: -1 Fail 0 Succes (Return :execute Builtin)
 */

int handle_builtin(char **cmd, int er)
{
	 cmmd_lst bil[] = {
		{"cd", CD_cmmd},
		{"env", env_cmd},
		{"help", show_help},
		{"echo", echo_cmmd},
		{"history", showhist},
		{NULL, NULL}
	};
	int i = 0;

	while ((bil + i)->cmmd)
	{
		if (_strcmp(cmd[0], (bil + i)->cmmd) == 0)
		{
			return ((bil + i)->fun(cmd, er));
		}
		i++;
	}
	return (-1);
}
/**
 * check_cmd - execute Simple Shell cmmd (Fork,Wait,execute)
 *
 * @cmd:parsed cmmd
 * @input: User Input
 * @c:Shell Excution Time Case of cmmd Not Found
 * @argv:Program Name
 * Return: 1 Case cmmd Null -1 Wrong cmmd 0 cmmd executed
 */
int check_cmd(char **cmd, char *input, int c, char **argv)
{
	int status;
	pid_t pid;

	if (*cmd == NULL)
	{
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0)
	{
		if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
		{
			path_cmmd(cmd);
		}

		if (execve(*cmd, cmd, environ) == -1)
		{
			printError(cmd[0], c, argv);
			free(input);
			free(cmd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
	return (0);
}
/**
 * signal_to_handel - Handle ^C
 * @sig:Captured Signal
 * Return: Void
 */
void signal_to_handel(int sig)
{
	if (sig == SIGINT)
	{
		PRINTER("\n$ ");
	}
}
