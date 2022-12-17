/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:40:04 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/16 23:04:37 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int32_t	exec_single(t_token *tok, t_input *data)
{
	init_sig_handle(2);
	open_in_andoutfiles(tok, data);
	if (!data->cmd_args[0])
		return (0);
	access_file(data);
	if (is_dir(data->cmd_path))
		err_is_directory(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		command_not_found(data);
	free (data->cmd_path);
	data->cmd_path = NULL;
	return (0);
}

static int32_t	dup_if_redirection_built(t_input *data)
{
	if (data->fds[READ] != STDIN_FILENO)
	{
		if (dup_and_close(data->fds[READ], STDIN_FILENO) < 0)
			return (1);
	}
	if (data->fds[WRITE] != STDOUT_FILENO)
	{
		if (dup_and_close(data->fds[WRITE], STDOUT_FILENO) < 0)
			return (1);
	}
	return (0);
}

/**
 * @brief save the standard in and output * 
 * @param data 
 */
static void	st_init_fd(t_input *data)
{
	data->temp_fd[READ] = dup(STDIN_FILENO);
	data->temp_fd[WRITE] = dup(STDOUT_FILENO);
}

/**
 * @brief  go to dup2_builtin and reset the stdin and stdout afterwards
 * 
 * @param data 
 */
static void	st_reset_fd(t_input *data)
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
	pid_t	id;

	get_cmd(tok, data);
	if (is_built_in(data->cmd_args[0]))
	{
		st_init_fd(data);
		if (check_if_redir_built(tok, data))
			return (1);
		if (dup_if_redirection_built(data))
			return (1);
		g_exit_code = run_builtin(data, env_table);
		st_reset_fd(data);
		return (g_exit_code);
	}
	id = fork();
	if (id == -1)
		return (error_print("fork"), 1);
	if (id == 0)
		g_exit_code = exec_single(tok, data);
	return (waiting(id, 1));
}
