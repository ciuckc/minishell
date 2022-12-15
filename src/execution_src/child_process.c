/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:55 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/15 13:59:15 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_infile(t_token *tok, t_input *data)
{
	close(data->pipe_fd[0]);
	dup_and_close(data->pipe_fd[1], STDOUT_FILENO);
	open_in_andoutfiles(tok, data);
}

void	dup_outfile(t_token *tok, t_input *data)
{
	close(data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup failed", 1);
	close(data->readfd);
	close(data->pipe_fd[1]);
	open_in_andoutfiles(tok, data);
}

void	dup_pipes(t_token *tok, t_input *data)
{
	close(data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		exit(EXIT_FAILURE);
	close(data->readfd);
	if (dup_and_close(data->pipe_fd[1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	open_in_andoutfiles(tok, data);
}

void	child_process(t_token *tok, t_input *data, int max, t_table *env_table)
{
	t_token	*token;

	token = tok;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (data->cmd_count == max)
		dup_infile(tok, data);
	else if (data->cmd_count == 1)
		dup_outfile(tok, data);
	else
		dup_pipes(tok, data);
	get_cmd(tok, data);
	if (is_built_in(data->cmd_args[0]))
	{
		open_in_andoutfiles(tok, data);
		data->exit_for_pipe = 1;
		exit (run_builtin(data, env_table));
	}
	if (!data->cmd_args[0])
		exit (0);
	access_file(data);
	if (is_dir(data->cmd_path))
		err_is_directory(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		command_not_found(data);
}
