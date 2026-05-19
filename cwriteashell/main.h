#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>



/*---MACROS----*/
#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/*---END MACROS----*/



/*---DECLARATIONS---*/
/**
   @brief Builtin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char ** args);

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char ** args);

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */

int lsh_exit(char ** args);

char * builtin_str[] ={
   "cd",
   "help",
   "exit"
};

int (* builtin_funcs)(char **)={
   &lsh_cd,
   &lsh_help,
   &lsh_exit
};
/*---END DECLARATIONS---*/



/*---PROTOTYPES---*/
/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int lsh_launch(char ** args);

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char ** args);

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char * lsh_read_line(void);

/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char ** lsh_split_line(char * line);

/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void);
/*---END PROTOTYPES---*/

#endif /*MAIN_H*/