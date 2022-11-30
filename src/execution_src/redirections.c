/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:43:31 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/29 14:09:02 by emlicame         ###   ########.fr       */
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
	int	bites;
	int	fd_hd;

	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	fd_hd = open ("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
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
	data->fds[READ] = open ("file.txt", O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit("file.txt", 1);
	unlink("file.txt");
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

/*
static int32_t	redirection_heredoc(t_token *tok, t_input *data)
{
	int	fd_hd;
	int	bites;
	char *read_buff;
	char *ret_line;
	
	ret_line = (char *)malloc(1 * sizeof(char));
	ret_line[0] = '\0';
	read_buff = malloc (sizeof(char ) * 1);
	read_buff[0] = '\0';
	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	fd_hd = open ("file.txt", O_RDWR | O_CREAT, 0777);
	if (fd_hd < 0)
		return (1);
	bites = write(fd_hd, tok->str, ft_strlen(tok->str));
	if (bites < 0)
		return (1);
	dprintf (2, "bites prima %d\n", bites);
	bites = 1;
	while (bites)
	{
		bites = read(fd_hd, read_buff, 10);
		dprintf (2, "arriva qui\n");
		dprintf (2, "bites dopo %d\n", bites);
		read_buff[bites] = '\0';
		ret_line = ft_strjoin(ret_line, read_buff);
	}
	ft_putstr_fd(ret_line, 2);
	data->fds[READ] = fd_hd;
	bites = dup_and_close(data->fds[READ], STDIN_FILENO);
	unlink("file.txt");
	if (bites < 0)
		return (1);
	return (0);
}
*/