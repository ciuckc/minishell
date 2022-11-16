/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:55 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/16 15:29:18 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_infile(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]);
	ret = open_infiles(tok, data);
	if (ret)
	{
		if (dup2(data->fds[READ], STDIN_FILENO) < 0)
			error_exit("Dup dup_infile failed", 1);
		close(data->fds[READ]);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		error_exit("Dup failed", 1);
	close(data->pipe_fd[1]);
	ret = open_outfiles(tok, data);
	if (ret)
	{
		if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
			error_exit("Dup outfile failed", 1);
		close(data->fds[WRITE]);
	}
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
	{
		if (dup2(data->fds[READ], STDIN_FILENO) < 0)
			error_exit("Dup dup_infile failed", 1);
		close(data->fds[READ]);
	}
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		error_exit("Dup pipe_fd[1]", 1);
	close(data->pipe_fd[1]);
	ret = open_outfiles(tok, data);
	if (ret)
	{
		if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
			error_exit("Dup outfile failed", 1);
		close(data->fds[WRITE]);
	}
}

void	child_process(t_token *tok, t_input *data, int max)
{
	t_token	*token;

	token = tok;
	if (data->cmd_count == max)
		dup_infile(tok, data);
	else
		dup_pipes(tok, data);
	get_cmd(tok, data);
	if (is_built_in(data->cmd_args[0]))
	{
		if (open_outfiles(token, data))
		{
			if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
				error_exit("Dup outfile failed", 1);
			close(data->fds[WRITE]);
		}
		data->exit_code = run_builtin(data);
		exit (data->exit_code);
	}
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
}