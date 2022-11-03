/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:34:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/03 19:28:24 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	dup_pipes(t_input *data)
{
	close(data->pipe_fd[0]);
	if (dup2(data->pipe_fd[1], 1) < 0)
		error_exit("Dup readfd failed", 1);;
	close(data->pipe_fd[1]);
}

void	child_process(t_token *tok, t_input *data)
{
	dprintf (2, "close data->pipe_fd[0] %d\n", data->pipe_fd[0]);
	close(data->pipe_fd[0]);
	dprintf (2, " data->pipe_fd[1] %d\n", data->pipe_fd[1]);
	if (dup2(data->pipe_fd[1], 1) < 0)
		error_exit("Dup failed", STDOUT_FILENO);
	close(data->pipe_fd[1]);
	dprintf (2, " data->readfd %d\n", data->readfd);
	if (dup2(data->readfd, 0) < 0)
		error_exit("Dup readfd failed", 1);
	close(data->readfd);
	dup_pipes(data);
	get_cmd(tok, data);
	access_file(data);
	openfiles(tok, data);
	execution(data);
}

void	parent_process(t_input *data)
{
	close(data->readfd);
	data->readfd = data->pipe_fd[0];
	close(data->pipe_fd[1]);
	if (data->cmd_count == 1) //aka last command
		close(data->pipe_fd[0]);
}

int	multiple_commands(t_token *tok, t_input *data)
{
	int		exit_code;
	pid_t	id;

	data->readfd = -2;
	exit_code = 0;
	while (tok)
	{
		if (pipe(data->pipe_fd) == -1)
			error_exit("Pipe failed", 1);
		id = fork();
		if (id == -1)
			error_exit("Fork failed", 1);
		if (id == 0)
			child_process(tok, data);
		parent_process(data);
		data->cmd_count--;
		while (tok->next && tok->token_type != PIPE)
			tok = tok->next;
		tok = tok->next;
		data->cmd_count--;
	}
	// exit_code = waiting(id);
	return (exit_code);
}
