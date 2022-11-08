/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:05:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 18:15:11 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "execution.h"

// void	dup_pipes(t_token *tok, t_input *data)
// {
// 	int	ret;

// 	if (data->readfd > 0)
// 	{
// 		if (dup2(data->readfd, 0) < 0)
// 			error_exit("Dup readfd failed", 1);
// 		close(data->readfd);
// 	}
// 	ret = open_infiles(tok, data);
// 	if (ret)
// 	{
// 		if (dup2(data->fds[READ], STDIN_FILENO) < 0)
// 			error_exit("Dup dup_infile failed", 1);
// 		close(data->fds[READ]);
// 	}
// 	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
// 		error_exit("Dup pipe 1 failed", 1);
// 	close(data->pipe_fd[1]);
// 	ret = open_outfiles(tok, data);
// 	if (ret)
// 	{
// 		if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
// 			error_exit("Dup outfile failed", 1);
// 		close(data->fds[WRITE]);
// 	}
// }

// void	child_process(t_token *tok, t_input *data)
// {
// 	close(data->pipe_fd[0]);
// 	dup_pipes(tok, data);
// 	get_cmd(tok, data);
// 	access_file(data);
// 	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
// 		error_exit("command not found", 127);
// }
