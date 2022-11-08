/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:34:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 16:24:24 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	waiting(int id, int max)
{
	int	status;
	int	exit_code;

	exit_code = -1;
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	while (max > 1)
	{
		wait(NULL);
		max--;
	}
	return (exit_code);
}

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
	while (tok)
	{
		if (pipe(data->pipe_fd) == -1) // if cmds > 1
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
	exit_code = waiting(id, max);
	system("lsof -c minishell");
	return (exit_code);
}
