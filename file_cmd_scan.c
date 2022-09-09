#include "shell.h"

int cant_open(char *file_path);
int proc_file_cmds(char *file_path, int *exec_retn);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _int_to_str(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_cmds - Takes a file and attmpts to run the cmds stored
 * within.
 * @file_path: Path to the file.
 * @exec_retn: Return value of the last executed cmd.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last cmd ran.
 */
int proc_file_cmds(char *file_path, int *exec_retn)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int prev_size = 120;
	char *line, **args, **frnt;
	char buf[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exec_retn = cant_open(file_path);
		return (*exec_retn);
	}
	line = malloc(sizeof(char) * prev_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buf, 119);
		if (b_read == 0 && line_size == 0)
			return (*exec_retn);
		buf[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, prev_size, line_size);
		_strcat(line, buf);
		prev_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exec_retn);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exec_retn = 2;
		free_args(args, args);
		return (*exec_retn);
	}
	frnt = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, frnt, exec_retn);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, frnt, exec_retn);

	free(frnt);
	return (ret);
}

