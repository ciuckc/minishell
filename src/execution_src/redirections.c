/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:43:31 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/15 19:14:22 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redir_less(t_token *tok, t_input *data)
{
	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	data->fds[READ] = open (tok->next->str, O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit(tok->next->str, 1);
	if (dup_and_close(data->fds[READ], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
}

void	redir_dless(t_token *tok, t_input *data)
{
	int	bites;
	int	fd_hd;

	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	fd_hd = open ("/tmp/hdoc_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_hd < 0)
		error_exit("heredoc_file", 1);
	bites = write(fd_hd, tok->str, ft_strlen(tok->str));
	if (bites < 0)
		error_exit("heredoc_file", 1);
	close (fd_hd);
	data->fds[READ] = open ("/tmp/hdoc_file.txt", O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit("heredoc_file", 1);
	if (dup_and_close(data->fds[READ], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	unlink("/tmp/hdoc_file.txt");
}

void	redir_great(t_token *tok, t_input *data)
{
	if (data->fds[WRITE] != STDOUT_FILENO)
		close(data->fds[WRITE]);
	data->fds[WRITE] = open(tok->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fds[WRITE] < 0)
		error_exit(tok->next->str, 1);
	if (dup_and_close(data->fds[WRITE], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
}

void	redir_dgreat(t_token *tok, t_input *data)
{
	if (data->fds[WRITE] != STDOUT_FILENO)
		close(data->fds[WRITE]);
	data->fds[WRITE] = open(tok->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->fds[WRITE] < 0)
		error_exit(tok->next->str, 1);
	if (dup_and_close(data->fds[WRITE], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
}
