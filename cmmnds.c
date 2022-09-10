#include "main.h"
/**
 * exit_cmmd - Exit state Shell
 * @cmd: parsed cmmd
 * @input: User Input
 * @argv:Program Name
 * @c:execute Count
 * Return: Void (Exit state)
 */
void  exit_cmmd(char **cmd, char *input, char **argv, int c)
{
	int state, i = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}
		else
		{
			state = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(state);
		}
	}
}


/**
 * CD_cmmd - Change Directory
 * @cmd: parsed cmmd
 * @er: state Last cmmd executed
 * Return: 0 Succes 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 */
int CD_cmmd(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(_getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(_getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * env_cmd - show Enviroment Variable
 * @cmd:parsed cmmd
 * @er:state of Last cmmd executed
 * Return:Always 0
 */
int env_cmd(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * show_help - showing Help For Builtin
 * @cmd:parsed cmmd
 * @er: state Of Last cmmd executed
 * Return: 0 Succes -1 Fail
 */
int show_help(char **cmd, __attribute__((unused))int er)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}
/**
 * echo_cmmd - execute echo Cases
 * @st:state Of Last cmmd executed
 * @cmd: parsed cmmd
 * Return: Always 0 Or execute Normal echo
 */
int echo_cmmd(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		intiPrint(st);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		numprnt(pid);
		PRINTER("\n");

	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);

	}
	else
		return (prnt_echo(cmd));

	return (1);
}
