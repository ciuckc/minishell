/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:43:31 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/11 17:40:30 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int32_t	dup_and_close(int fd, int in_out)
{
	if (dup2(fd, in_out) < 0)
	{
		error_print("Dup dup_and_close failed");
		return (1);
	}
	close(fd);
	return (0);
}

static int32_t	st_redirection_heredoc(t_token *tok, t_input *data)
{
	int	bites;
	int	fd_hd;

	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	fd_hd = open ("/tmp/hdoc_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_hd < 0)
	{
		dprintf (2, "errno %d\n", errno);
		strerror(errno);
		return (1);
	}
	bites = write(fd_hd, tok->str, ft_strlen(tok->str));
	if (bites < 0)
		return (1);
	close (fd_hd);
	data->fds[READ] = open ("/tmp/hdoc_file.txt", O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit("heredoc_file", 1);
	unlink("/tmp/hdoc_file.txt");
	return (0);
}

int32_t	open_infiles(t_token *tok, t_input *data)
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
		else if (tok->type == DLESS)
		{
			ret = 1;
			if (st_redirection_heredoc(tok, data))
				error_exit("heredoc file error", 1);
		}
		tok = tok->next;
	}
	return (ret);
}

static int32_t	st_redirection_dgreat(t_token *tok, t_input *data)
{
	if (data->fds[WRITE] != STDOUT_FILENO)
		close(data->fds[WRITE]);
	data->fds[WRITE] = open(tok->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->fds[WRITE] < 0)
		return (1);
	return (0);
}

int32_t	open_outfiles(t_token *tok, t_input *data)
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
		else if (tok->type == DGREAT)
		{
			ret = 1;
			if (st_redirection_dgreat(tok, data))
				error_exit(tok->next->str, 1);
		}
		tok = tok->next;
	}
	return (ret);
}
