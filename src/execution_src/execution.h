/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:00:13 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 01:22:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1

typedef struct s_input
{
	char			**environ;
	char			**paths;
	char			*cmd_path;
	char			**cmd_args;
	int32_t			exit_for_pipe;
	int32_t			cmd_count;
	int32_t			exit_code;
	int64_t			value;
	t_env			expo_var;
	t_env			old_var;
	t_env			new_var;
	int32_t			temp_fd[2];
	int32_t			fds[2];
	int32_t			readfd;
	int32_t			pipe_fd[2];
}	t_input;

/**
 * @brief Get the PATH variable from environment calling seeking_path,
 * if there, split the path by directory and calling complete_path, it puts / at
 * the end of the path. if no path creates a empty double array
 * @param data struct where it's stored the pointer to the environment and the 
 * pointer to a 2Darray created to get the list of directories in PATH
 */
void		get_path(t_input *data);

/**
 * @brief writes a message to stderr and exits
 * 
 * @param text the message to print
 * @param exit_code the code to exit with
 */
void		error_exit(char *text, int exit_code);

/**
 * @brief writes a message to stderr
 * 
 * @param text the message to print
 */
void		error_print(char *text);

/**
 * @brief writes a message to stderr, incuding the name of comand, and exits
 * 
 * @param data struct where stored the list of comands
 */
void		command_not_found(t_input *data);

/**
 * @brief writes a message to stderr, incuding the name of comand, and exits
 * 
 * @param data struct where stored the list of comands
 */
void		permission_denied(t_input *data);

/**
 * @brief  writes a message to stderr, incuding the name of comand, and exits
 * 
 * @param data struct where stored the list of comands
 */
void		no_such_file(t_input *data);

/**
 * @brief iterate the list of token from parsing in order to record and copy
 * the list of comands from readline and copy the content in a 2d array that 
 * will be stored in the struct data in the var cmd_args; the iteration will 
 * continue until the first pipe
 *   
 * @param tok list of tokens from parsing
 * @param data struct where stored the list of comands
 */
void		get_cmd(t_token *tok, t_input *data);

/**
 * @brief count of comands in the entire token list
 * 
 * @param tok token list
 * @param data struct where stored the number of comands
 */
void		count_cmds(t_token *tok, t_input *data);

/**
 * @brief checks if a command is found by joining it with one of the paths
 * or if it exists in present dir or if accessible with absolute path
 * 
 * @param data struct where stored list of comands and path
 * @return int32_t 0 succes 1 failure
 */
void		access_file(t_input *data);
void		err_is_directory(t_input *data);

int32_t		is_dir(char *path);
/**
 * @brief dup2 of the current file descriptors and close fd
 * 
 * @param fd 
 * @param in_out paramenter passed as indication 0 for std input and 1 is
 * passed as std output
 * @return int32_t -1 in case of failure
 */
int32_t		dup_and_close(int fd, int in_out);

/**
 * @brief in case of redirection as input, opens the files and assigns the 
 * related file descriptor to the reading end of pipe or as standard input;
 * in case of heredoc, it calls st_redirection_heredoc to create a file where 
 * the text from readline will be written and the file will be read and 
 * redirected to the correct reading end. If not existing or if the permissions
 * don't allow the reading of the file, an error will be printed on std error.
 * in case of redirection as output, opens the files and assigns the 
 * related file descriptor to the writing end of pipe or as standard output;
 * in case of heredoc, it calls st_redirection_dgreat to create a file where 
 * the text received  will be appended and the file will be assigned 
 * to the correct writing end. If not existing the file will be created
 * 
 * @param tok ist of tokens from parsing
 * @param data struct where file descriptors are stored before dup2
 */
void		open_in_andoutfiles(t_token *tok, t_input *data);

void		redir_less(t_token *tok, t_input *data);
void		redir_dless(t_token *tok, t_input *data);
void		redir_great(t_token *tok, t_input *data);
void		redir_dgreat(t_token *tok, t_input *data);

int32_t		check_if_redir_built(t_token *tok, t_input *data);
int32_t		built_open_infiles(t_token *tok, t_input *data);
int32_t		built_open_outfiles(t_token *tok, t_input *data);

/**
 * @brief execute cmd when the count from readline is 1;
 * it checkes if the command is listed in the builtins and runs it. 
 * if built in file descriptors will be saved and reset after the execution.
 * Execution will be from main proess, no fork, exit code will be aquired 
 * and returned after execution and fds reset 
 * @param tok token list
 * @param data struct with multiple information
 * @param env_table hash-map with environment information and storage of vars
 * @return int32_t exit code as result of error or builtins execution outcome
 */
int32_t		single_command(t_token *tok, t_input *data, t_table *env_table);

/**
 * @brief execution of multiple commands piped. Exeution loop will go through 
 * the entire lists from readline and it will check for every command 
 * redirections, it will check if the command is a built in and run the related 
 * funtions, in this case the process will be forked and piped
 * 
 * @param tok token list
 * @param data struct with multiple information
 * @param env_table hash-map with environment information and storage of vars
 * @return int32_t g_exit_code with outcome of waiting call every child process
 */
int32_t		multiple_commands(t_token *tok, t_input *data, t_table *env_table);

/**
 * @brief blocks the calling process until one of its child processes exits or
 *  a signal is received. After child process terminates, parent continues its
 *  execution after wait system call instruction. 
 * 
 * @param id last child pid
 * @param max number of commnds, every comand is related to a child process, 
 * all the children will be waited
 * @return int32_t signal status
 */
int32_t		waiting(int id, int max);

/**
 * @brief execution of the multple commands, where the processis forked and
 * the commands piped; interruption of signals, check for
 * redirections and assignement of correct fd (pipe ends and redirections )
 * Arguments : token list, struct with multiple information, number of commands 
 * (max) and hash table
 */
void		child_process(t_token *tok, t_input *data, int max, \
			t_table *env_table);

/**built-ins **/

/**
 * @brief check if built in by comparison of cmd name from tokens
 * 
 * @param cmd string from 2d array containing the cmd and its arguments
 * @return true 
 * @return false 
 */
bool		is_built_in(char *cmd);

/**
 * @brief if built in run execution
 * 
 * @param data struct with list of commands
 * @param env_table hash table
 * @return int32_t exit code
 */
int32_t		run_builtin(t_input *data, t_table *env_table);

/**
 * @brief reproduce the command export, if there are no arguments , it will 
 * print the sorted list including variable not inizialized;
 * If export has arguments it will export those to the env list 
 * 
 * @param data struct containing 2d with command and its arguments
 * @param env_table hash table with environment and variables
 * @return int32_t 0 succes 1 failure
 */
int32_t		ft_export(t_input *data, t_table *env_table);

/**
 * @brief DEPRECATED
 * 
 * @param unexp_value DEPRECATED
 * @param env DEPRECATED
 * @return char* DEPRECATED
 */
char		*ft_export_expand_var(char *unexp_value, t_table *env);

/**
 * @brief sorting in alphabetical order of env + variable list 
 * 
 * @param table hash table
 * @return char** return 2d array sorted
 */
char		**sort_table(t_table *table);

/**
 * @brief checks if the string contains the char '='
 * 
 * @param s string to check
 * @param c char '='
 * @return int32_t 0 success 1 failure
 */
int32_t		mini_ft_strchr(const char *s, int c);

/**
 * @brief insert in hash map new variable as per export cmd, variable passed 
 * with a sign = with or without data assigned
 * 
 * @param data struct with cmd and its arguments (possibility to pass
 * multiple variable)
 * @param env_table hash table 
 * @param pos index of current element in the list of arguments (multiple vars)
 * @return int32_t 0 success 1 failure
 */
int32_t		insert_replace_var(t_input *data, t_table *env_table, int pos);

/**
 * @brief insert in hash map new variable as per export cmd, variable passed 
 * without a sign = hence it will be stored in the has map but not in the
 * environment with the variables which have been initialized with sign =
 * with or without data
 * 
 * @param data struct with cmd and its arguments (possibility to pass
 * multiple variable)
 * @param env_table hash table
 * @param pos index of current element in the list of arguments (multiple vars)
 * @return int32_t 0 success 1 failure
 */
int32_t		ins_replace_var_no_eq(t_input *data, t_table *env_table, int pos);

/**
 * @brief remove variable from hash table and env, possible multiple input 
 * with multiple variables to be removed
 * 
 * @param data struct with cmd and its arguments (possibility to pass
 * multiple variable)
 * @param env_table  hash table
 * @return int32_t 0 success 1 failure
 */
int32_t		ft_unset(t_input *data, t_table *env_table);

/**
 * @brief change directory to commands[1]
 * 
 * @param data struct with 2d array where to find cmd and the directory name
 * @param env_table  hash table
 * @return int32_t 0 success 1 failure
 */
int32_t		ft_cd(t_input *data, t_table *env_table);

/**
 * @brief executes the echo command. Prints all commands with a space inbetween.
 * Ends with a newline unless commands[1] is -n 
 * 
 * @param data struct with cmd and its arguments (possibility to pass
 * multiple strings to be printed)commands[0] is echo and will not
 * be printed. If flaged, until the flag -n is repeated, it will not be printed 
 * and there won't be a newline in the end.
 * @return int32_t 0 success 1 failure
 */
int32_t		ft_echo(t_input *data);

/**
 * @brief prints the current working directory, if function call to change 
 * directory returns NULL, it wll be printed last recorded working directory 
 * from environment else an error will be printed out
 * 
 * @param data structure where to retrieve 2d array with environment
 * @return int32_t 0 success 1 failure
 */
int32_t		ft_pwd(t_input *data);

/**
 * @brief executes the exit command with possibility of passing the exit value
 * 
 * @param data struct with 2d array where to find cmd and the numeric value
 * @return int32_t 1 if incorrect input is passed as value
 */
int32_t		ft_exit(t_input *data);

void		st_print_array(t_token *lst);

#endif