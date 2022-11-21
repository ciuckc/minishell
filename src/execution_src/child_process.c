/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:55 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/20 18:23:49 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_infile(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]);
	ret = open_infiles(tok, data);
	if (ret)
		dup_and_close(data->fds[READ], STDIN_FILENO);
	dup_and_close(data->pipe_fd[1], STDOUT_FILENO);
	ret = open_outfiles(tok, data);
	if (ret)
		dup_and_close(data->fds[WRITE], STDOUT_FILENO);
}

void	dup_outfile(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup failed", 1);
	close(data->readfd);
	ret = open_infiles(tok, data);
	if (ret)
		dup_and_close(data->fds[READ], STDIN_FILENO);
	close(data->pipe_fd[1]);
	ret = open_outfiles(tok, data);
	if (ret)
		dup_and_close(data->fds[WRITE], STDOUT_FILENO);
}

void	dup_pipes(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup readfd failed", 1);
	close(data->readfd);
	ret = open_infiles(tok, data);
	if (ret)
		dup_and_close(data->fds[READ], STDIN_FILENO);
	dup_and_close(data->pipe_fd[1], STDOUT_FILENO);
	ret = open_outfiles(tok, data);
	if (ret)
		dup_and_close(data->fds[WRITE], STDOUT_FILENO);
}

void	child_process(t_token *tok, t_input *data, int max, t_table *env_table)
{
	t_token	*token;

	token = tok;
	if (data->cmd_count == max)
	{
		dup_infile(tok, data);
	}
	else if (data->cmd_count == 1)
		dup_outfile(tok, data);
	else
		dup_pipes(tok, data);
	get_cmd(tok, data);
	if (is_built_in(data->cmd_args[0]))
	{
		if (open_outfiles(token, data))
			dup_and_close(data->fds[WRITE], STDOUT_FILENO);
		data->exit_for_pipe = 1;
		exit (run_builtin(data, env_table));
	}
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
}
