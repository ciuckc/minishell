/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:34:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/01 19:26:08 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void	child_process(t_token *tok, t_input *data)
// {
// 	//dupinfile? dup oufile? get pipex
// 	if (dup2(data->readfd, 0) < 0)
// 		error_exit("Dup failed", 1);
// 	close(data->readfd);
// 	dup_pipes(data);
// 	access_file(data);
// 	openfiles(data);
// 	execution(data);
// }

// void	parent_process(t_input *data)
// {
// 	close(data->readfd);
// 	data->readfd = data->pipe_fd[0];
// 	close(data->pipe_fd[1]);
// 	if (data->cmd_count == 1) //aka last command
// 		close(data->pipe_fd[0]);
// }

int	multiple_commands(t_token *tok, t_input *data)
{
	int		exit_code;
	pid_t	id;

	exit_code = 0;
	(void)tok;
	(void)data;
	id = 25487568;
	// while (tok && tok->token_type != PIPE)
	// {
	// 	if (pipe(data->pipe_fd) == -1)
	// 		error_exit("Pipe failed", 1);
	// 	id = fork();
	// 	if (id == -1)
	// 		error_exit("Fork failed", 1);
	// 	if (id == 0)
	// 		child_process(tok, data);
	// 	parent_process(data);
	// 	data->cmd_count--;
	// 	tok = tok->next;
	// }
	// exit_code = waiting(id);
	return (exit_code);
}
