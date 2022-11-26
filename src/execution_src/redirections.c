/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:43:31 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/26 15:50:28 by emlicame         ###   ########.fr       */
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

static int32_t	redirection_heredoc(t_token *tok, t_input *data)
{
	int	fd_hd;

	//sigignore?
	fd_hd = open ("file.txt", O_CREAT | O_WRONLY, 0644);
	if (fd_hd < 0)
		return (1);
	write(fd_hd, tok->next->str, ft_strlen(tok->next->str));
	write(fd_hd, "\n", 1);
	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	data->fds[WRITE] = fd_hd;
	//free (tok->next->str);
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
			ret = 2;
			if (redirection_heredoc(tok, data))
				error_exit("heredoc file error", 1);
		}
		tok = tok->next;
	}
	return (ret);
}

static int32_t	redirection_dgreat(t_token *tok, t_input *data)
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
			if (redirection_dgreat(tok, data))
				error_exit(tok->next->str, 1);
		}
		tok = tok->next;
	}
	return (ret);
}
