#include "shell.h"

int (*get_builtin(char *cmd))(char **args, char **frnt);
int shell_exit(char **args, char **frnt);
int shell_cd(char **args, char __attribute__((__unused__)) **frnt);
int shell_help(char **args, char __attribute__((__unused__)) **frnt);

/**
 * get_builtin - matches a cmd with a corresponding
 *               shell builtin function.
 * @cmd: The cmd to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *cmd))(char **args, char **frnt)
{
	builtin_t func[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; func[i].name; i++)
	{
		if (_strcmp(func[i].name, cmd) == 0)
			break;
	}
	return (func[i].f);
}

/**
 * shell_exit - Causes normal process termination
 *                for the shell.
 * @args: An array of arguments containing the exit value.
 * @frnt: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shell_exit(char **args, char **frnt)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, frnt);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * shell_cd - Changes the current directory of the shell process.
 * @args: An array of arguments.
 * @frnt: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **frnt)
{
	char **dir_info, *new_line = "\n";
	char *prevpwd = NULL, *pwd = NULL;
	struct stat dir;

	prevpwd = getcwd(prevpwd, 0);
	if (!prevpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("PREVPWD") != NULL)
					(chdir(*_getenv("PREVPWD") + 7));
			}
			else
			{
				free(prevpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(prevpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "PREVPWD";
	dir_info[1] = prevpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(prevpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shell_help - display information about shell builtin cmds.
 * @args: An array of arguments.
 * @frnt: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **frnt)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

