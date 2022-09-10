#ifndef MAIN_H
#define MAIN_H

/**###### environ var ######*/

extern char **environ;

/**##### MACROS ######*/

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"
#define PRINTER(c) (write(STDOUT_FILENO, c, _strlen(c)))

/**###### LIBS USED ######*/

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/**###### strng FUNCTION ######*/

char *_strtok(char *str, const char *tok);
unsigned int check_delim(char c, const char *str);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
int _putchar(char c);
int _atoi(char *s);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
int _isalpha(int c);
void array_rev(char *arr, int len);
int intlen(int num);
char *_int2str(unsigned int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(char *str);

/**###### MEMORIE  MANGMENT ####*/

void free_env(char **env);
void *fill_an_array(void *a, int el, unsigned int len);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_calloc(unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **input, char *line);

/**###### INPUT Function ######*/

void showShellTerminal(void);
void signal_to_handel(int sig);
char *_getline(void);

/** ###### cmmd parser and extractor ###*/

int path_cmmd(char **line);
char *_getenv(char *name);
char **parseInput(char *input);
int handle_builtin(char **cmd, int er);
void read_file(char *filename, char **argv);
char *bild(char *token, char *value);
int check_builtin(char **cmd);
void creareEnviromentVariabel(char **envi);
int check_cmd(char **tkens, char *line, int count, char **argv);
void treat_file(char *line, int countr, FILE *fd, char **argv);
void exit_cmmd_for_file(char **cmd, char *line, FILE *fd);

/** ####BUL FUNC #####*/

void remveCmmnts(char *_buffer);
int history(char *input);
int showhist(char **cmd, int er);
int env_cmd(char **cmd, int er);
int CD_cmmd(char **cmd, int er);
int show_help(char **cmd, int er);
int echo_cmmd(char **cmd, int er);
void  exit_cmmd(char **cmd, char *input, char **argv, int c);
int prnt_echo(char **cmd);

/** ####error handle and Printer ####*/
void numprnt(unsigned int n);
void intiPrint(int n);
void printError(char *line, int c, char **argv);
void _prerror(char **argv, int c, char **cmd);


/**
 * struct bulltin - contain bultin to handle and function to execute
 * @cmmd:pointer to char
 * @fun:fun to execute when bultin true
 */

typedef struct  bulltin
{
	char *cmmd;
	int (*fun)(char **line, int er);
} cmmd_lst;

#endif
