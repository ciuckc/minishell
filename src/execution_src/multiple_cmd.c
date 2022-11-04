/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:34:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/04 18:17:39 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	parent_process(t_input *data)
{
	close(data->readfd);
	data->readfd = data->pipe_fd[0];
	close(data->pipe_fd[1]);
	if (data->cmd_count == 1)
		close(data->pipe_fd[0]);
}

int	multiple_commands(t_token *tok, t_input *data)
{
	int		exit_code;
	int		max;
	pid_t	id;

	data->readfd = -2;
	exit_code = 0;
	max = data->cmd_count;
	set_fds(data);
	while (tok)
	{
		if (pipe(data->pipe_fd) == -1)
			error_exit("Pipe failed", 1);
		id = fork();
		if (id == -1)
			error_exit("Fork failed", 1);
		if (id == 0)
			child_process(tok, data, max);
		parent_process(data);
		data->cmd_count--;
		while (tok->next && tok->token_type != PIPE)
			tok = tok->next;
		tok = tok->next;
	}
	// exit_code = waiting(id);
	return (exit_code);
}
