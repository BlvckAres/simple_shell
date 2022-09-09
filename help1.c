#include "shell.h"

void free_args(char **args, char **frnt);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exec_retn);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing cmds/arguments.
 * @frnt: A double pointer to the beginning of args.
 */
void free_args(char **args, char **frnt)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(frnt);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buf and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buf;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(file);
		return (NULL);
	}
	read(file, buf, 120);
	while (buf[i] != ' ')
		i++;
	buf[i] = '\0';

	close(file);
	return (buf);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		tmp = *var_addr;
		while (*tmp != '=')
			tmp++;
		tmp++;
		replacement = malloc(_strlen(tmp) + 1);
		if (replacement)
			_strcpy(replacement, tmp);
	}

	return (replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the cmd and arguments.
 * @exec_retn: A pointer to the return value of the last executed cmd.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exec_retn)
{
	int j, k = 0, len;
	char *replacement = NULL, *prev_line = NULL, *new_line;

	prev_line = *line;
	for (j = 0; prev_line[j]; j++)
	{
		if (prev_line[j] == '$' && prev_line[j + 1] &&
				prev_line[j + 1] != ' ')
		{
			if (prev_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (prev_line[j + 1] == '?')
			{
				replacement = _int_to_str(*exec_retn);
				k = j + 2;
			}
			else if (prev_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; prev_line[k] &&
						prev_line[k] != '$' &&
						prev_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&prev_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&prev_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, prev_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &prev_line[k]);
			free(prev_line);
			*line = new_line;
			prev_line = new_line;
			j = -1;
		}
	}
}

