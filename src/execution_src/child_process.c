/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:05:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 16:12:40 by emlicame         ###   ########.fr       */
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
	dprintf(2, "infile data->fds[READ] %d\n", data->fds[READ]);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		error_exit("Dup failed", 1);
	dprintf(2, "infle data->pipe_fd[1] %d\n", data->pipe_fd[1]);
	close(data->pipe_fd[1]);
}

void	dup_outfile(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]); // if no pipe open in last round, this can go
	dprintf(2, "outfile dadta->pipe_fd[0] %d\n", data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup failed", 1);
	dprintf(2, "out data->readfd %d\n", data->readfd);
	close(data->readfd);
	dprintf(2, "outfile data->pipe_fd[1] %d\n", data->pipe_fd[1]);
	close(data->pipe_fd[1]); // if no last pipe can go
	ret = open_outfiles(tok, data);
	if (ret)
	{
		if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
			error_exit("Dup outfile failed", 1);
		close(data->fds[WRITE]);
	}
	dprintf(2, "outfile data->fds[WRITE] %d\n", data->fds[WRITE]);
}

void	dup_pipes(t_input *data)
{
	close(data->pipe_fd[0]);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup readfd failed", 1);
	close(data->readfd);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		error_exit("Dup readfd failed", 1);
	close(data->pipe_fd[1]);
}

void	child_process(t_token *tok, t_input *data, int max)
{
	if (data->cmd_count == max)
	{
		dup_infile(tok, data);
	}
	else if (data->cmd_count == 1)
		dup_outfile(tok, data);
	else
		dup_pipes(data);
	get_cmd(tok, data);
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
}
