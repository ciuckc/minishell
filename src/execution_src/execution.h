/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:00:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/04 19:47:47 by emlicame         ###   ########.fr       */
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
int32_t		access_file(t_input *data);

/**
 * @brief in case of redirection as input, opens the files and assigns the 
 * related file descriptor to the reading end of pipe or as standard input;
 * in case of heredoc, it calls st_redirection_heredoc to create a file where 
 * the text from readline will be written and the file will be read and 
 * redirected to the correct reading end. If not existing or if the permissions
 * don't allow the reading of the file, an error will be printed on std error.
 * @param tok list of tokens from parsing
 * @param data struct where file descriptors are stored before dup2
 * @return int32_t 0 if no redirections, 1 if redirection
 */
int32_t		open_infiles(t_token *tok, t_input *data);

/**
 * @brief in case of redirection as output, opens the files and assigns the 
 * related file descriptor to the writing end of pipe or as standard output;
 * in case of heredoc, it calls st_redirection_dgreat to create a file where 
 * the text received  will be appended and the file will be assigned 
 * to the correct writing end. If not existing the file will be created
 * 
 * @param tok token list
 * @param data struct where file descriptors are stored before dup2
 * @return int32_t 0 if no redirections, 1 if redirection
 */
int32_t		open_outfiles(t_token *tok, t_input *data);

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
 * @brief execution of the multple commands, interruption of signals, check for
 * redirections and assignement of correct fd (pipe ends and redirections )
 * Argumenrs : token list, struct with multiple information, number of commands 
 * (max) and hash table
 */
void		child_process(t_token *tok, t_input *data, int max, \
			t_table *env_table);

/**built-ins **/
bool		is_built_in(char *cmd);
int32_t		run_builtin(t_input *data, t_table *env_table);
int32_t		ft_export(t_input *data, t_table *env_table);
char		*ft_export_expand_var(char *unexp_value, t_table *env);
char		**sort_table(t_table *table);
int32_t		mini_ft_strchr(const char *s, int c);
int32_t		replace_var(t_input *data, t_table *env_table, int pos);
int32_t		replace_var_no_eq(t_input *data, t_table *env_table, int pos);
int32_t		ft_unset(t_input *data, t_table *env_table);
int32_t		ft_cd(t_input *data, t_table *env_table);
int32_t		ft_echo(t_input *data);
int32_t		ft_pwd(t_input *data);
int32_t		ft_exit(t_input *data);

#endif