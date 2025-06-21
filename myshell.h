#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h> 
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_BUFFER 1024  // max line buffer
#define MAX_ARGS 64  // max # args
#define SEPARATORS " \t\n"  // token separators
#define NUM 10        // the command number
#define MAX_OPEN 10  // max open files for stdin/stdout redirection
#define MAX_PATH 100 // max length of file or folder path

/***********************************************************************
announce certain data types
***********************************************************************/
typedef struct // redirection data structure
{ 
	char *filename;   // redirection file name
	char opentype[3]; // open mode of redirection file: "a" (append), "r" (read), "w" (write)
	char open[3];     // redirection type: ">>" (append), "<" (input), ">" (output)
} Redirect;          //

extern int errno;        // system error number
extern char **environ;   // environment variables array

/***********************************************************************
announce the functions
***********************************************************************/

// Executes the given command line stored in 'buffer'.
int Execute(char *buffer);
//stocks*************
void Command_shell_interactive(void);
//**void Command_shell(FILE *in, void *arg1, void *arg2);
// Executes a command with possible input/output redirection and state tracking.
int Command_exec(char **args, const Redirect *Inputs, const Redirect *Outputs, int *states);

// Prints an error message related to command execution.
int Error(int errortype, char **args, const Redirect *IOputs, const int *states, char *msg);

// Parses the command line into tokens, identifies redirection and command states.
int Command_strtok(char *buf, char **args, int *states, Redirect *InPuts, Redirect *OutPuts);

// Changes the current working directory according to the 'cd' command.
int Command_cd(char **args, const Redirect *Inputs, int *states);

// Clears the terminal screen (executes the 'clear' command).
void Command_clear(void);

// Lists files and directories in the specified directory (executes the 'dir' command).
int Command_dir(char **args, const Redirect *Inputs, int *states);

// Prints the provided arguments to the terminal (executes the 'echo' command).
int Command_echo(char **args, const Redirect *Inputs, int *states);

// Lists all environment variables (executes the 'environ' command).
int list_environ(void);

// Shows the current working directory path (executes the 'pwd' command).
int show_pwd(void);

//*****
// Reads lines from the input file or stdin and calls Execute() to run commands.
int Command_shell(FILE *inputfile, const Redirect *Outputs, const int *states);

// Introduces a delay of 'n' units to control process execution order.
void Command_delay(int n);

// Converts a relative file or directory path to its absolute full path.
void get_fullpath(char *fullpath, const char *shortpath);

// Displays the user manual by reading the "readme" file, optionally filtering by keywords.
int Command_help(char **args, const Redirect *Outputs, int *states);

// Executes batch files by running myshell with the specified batch file.
int Command_bat(char **args, const Redirect *Inputs, const Redirect *Outputs, int *states);
