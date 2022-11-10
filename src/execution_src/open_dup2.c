/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:11:18 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/10 15:18:56 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_infiles(t_token *tok, t_input *data)
{
	int	ret;

	ret = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == LESS)
		{
			ret = 1;
			if (data->fds[READ] != STDIN_FILENO)
				close(data->fds[READ]);
			data->fds[READ] = open (tok->next->str, O_RDONLY);
			if (data->fds[READ] < 0)
				error_exit(tok->next->str, 1);
		}
		tok = tok->next;
	}
	return (ret);
}

int	open_outfiles(t_token *tok, t_input *data)
{
	int	ret;

	ret = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == GREAT)
		{
			ret = 1;
			if (data->fds[WRITE] != STDOUT_FILENO)
				close(data->fds[WRITE]);
			data->fds[WRITE] = open(tok->next->str, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (data->fds[WRITE] < 0)
				error_exit(tok->next->str, 1);
		}
		tok = tok->next;
	}
	return (ret);
}

int	dup_and_close(int fd, int in_out)
{
	if (dup2(fd, in_out) < 0)
	{
		error_print("Dup dup_and_close failed");
		return (1);
	}
	close(fd);
	return (0);
}
		// error_exit("Dup dup_and_close failed", 1);

void	dup_pipes(t_token *tok, t_input *data)
{
	int	ret;

	close(data->pipe_fd[0]);
	if (data->readfd > 0)
	{
		if (dup2(data->readfd, 0) < 0)
			error_exit("Dup readfd failed", 1);
		close(data->readfd);
	}
	ret = open_infiles(tok, data);
	if (ret)
		dup_and_close(data->fds[READ], STDIN_FILENO);
	if (data->pipe_fd[1] > 1)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			error_exit("Dup pipe 1 failed", 1);
		close(data->pipe_fd[1]);
	}
	ret = open_outfiles(tok, data);
	if (ret)
		dup_and_close(data->fds[WRITE], STDOUT_FILENO);
}

/*
	Remember!!! man dup2
	 In dup2(), the value of the new descriptor fildes2 is specified.  
	 If fildes and fildes2 are equal, then dup2() just returns fildes2; 
	 no other changes are made to the existing descriptor.  
	 Otherwise, if descriptor fildes2 is already in use, it is first deallocated
	 as if a close(2) call had
     been done first.
*/
/*
	if (data->pipe_fd[1] > 1)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			error_exit("Dup pipe 1 failed", 1);
		close(data->pipe_fd[1]);
	}
*/