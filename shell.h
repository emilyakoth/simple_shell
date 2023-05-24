#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <sdtlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define MAX_WORD_COUNT 1000
#define BUF_FLUSH -1

#define CMD_NORM  0
#define CMD_OR    1
#define CMD_AND   2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;

/**
 * struct liststr - ...
 * @num: ...
 * @str: ...
 * @next: ...
 */
typedef struct lists
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-args
 * @arg: ...
 * @argv: ...
 * @path: ...
 * @argc: ...
 * @line_count: error count
 * @err_num: error code
 * @linecount_flag: if count
 * @fname: the program
 * @env: linked list
 * @environ: custom
 * @history: history node
 * @alias: the alias node
 * @env_changed: ...
 * @status: ...
 * @cmd_buf: pointer address
 * @cmd_buf: pointer address
 * @readfd: the fd
 * @histcount: history
 */
typedef struct passinfo
{
	char *args;
	char **args;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	int readfd;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int histcount;
} info_t;
#define INFO_INT \
	{NULL, NULL, NULL, 0, 0, 0,0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, '\0', 0, 0}

/**
 * struct builtin - builtin fucntion
 * @type: commmand flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* atoi functions */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/* simple shell function */
int main(int argc, char *argv[], char **env);

/* handle builtin functions */
bool handle_builtin(char **args, size_t no_of_args);
void handle_error(pid_t pid);
int execute(char *arguments, struct stat *statbuf, char **envp);

/* split string functions */
char **split_string(char *str, char *separators, size_t *word_count);
size_t vector_len(char **vector);

/* string concenate functions */
char *str_concat(char *s1, char *s2);
char *strs_concat(int args_no, char *s1, char *s2);

/* word count functions */
bool is_delimiter(char c, char *separators);
unsigned int words_count(char *str, char *separators, unsigned int *word_sizes);

/* string length */
int _strlen(char *s);

/* print environ path */
int main(int argc, char **argv, char **env);

/* set zeros */
void set_zeros(unsigned int *arr, size_t size);

/* handle exit */
void handle_exit(char **exit_args, size_t no_of_args);

/* value of specified env variable */
char *_getenv(char *key);

/* check files */
bool check_file_status(char *pathname, struct stat *statbuf);
char *check_file_in_path(char *filename, struct stat *statbuf);

/* compare strings */
int _strncmp(char *s1, char *s2, size_t n);

/* memory deallocation */
void free_vector(char **vec, int len);

/* handler for env */
void handle_env(char **env_args, size_t no_of_args);
void _printenv(void);

/* my cd */
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* printing functions */
void _eputs(char *str);
int _eputchar(char c);

/* environment variable */
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
 
/* linked nodes */
list_t *add_node_end(list_t **head, const char *str);

#endif	
