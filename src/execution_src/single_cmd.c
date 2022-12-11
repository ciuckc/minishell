/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:40:04 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/11 16:47:53 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int32_t	exec_single(t_token *tok, t_input *data)
{
	t_token	*token;

	init_sig_handle(2);
	token = tok;
	if (open_infiles(token, data))
	{
		if (dup_and_close(data->fds[READ], STDIN_FILENO))
			return (1);
	}
	token = tok;
	if (open_outfiles(token, data))
	{
		if (dup_and_close(data->fds[WRITE], STDOUT_FILENO))
			return (1);
	}
	if (!data->cmd_args[0])
		return (0);
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		command_not_found(data);
	free (data->cmd_path);
	data->cmd_path = NULL;
	return (0);
}

/**
 * @brief save the standard in and output * 
 * @param data 
 */
void	init_fd(t_input *data)
{
	data->temp_fd[READ] = dup(STDIN_FILENO);
	data->temp_fd[WRITE] = dup(STDOUT_FILENO);
}

/**
 * @brief  go to dup2_builtin and reset the stdin and stdout afterwards
 * 
 * @param data 
 */
void	reset_fd(t_input *data)
{
	if (dup2(data->temp_fd[READ], STDIN_FILENO) == -1)
		error_exit("Dup infile failed", 1);
	if (dup2(data->temp_fd[WRITE], STDOUT_FILENO) == -1)
		error_exit("Dup outfile failed", 1);
	close(data->temp_fd[READ]);
	close(data->temp_fd[WRITE]);
}

int32_t	single_command(t_token *tok, t_input *data, t_table *env_table)
{
	t_token	*token;
	pid_t	id;

	token = tok;
	get_cmd(token, data);
	token = tok;
	if (is_built_in(data->cmd_args[0]))
	{
		init_fd(data);
		if (open_outfiles(token, data))
			dup_and_close(data->fds[WRITE], STDOUT_FILENO);
		g_exit_code = run_builtin(data, env_table);
		reset_fd(data);
		return (g_exit_code);
	}
	id = fork();
	if (id == -1)
		error_exit("Fork failed", 1);
	if (id == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		g_exit_code = exec_single(token, data);
	}
	return (waiting(id, 1));
}
