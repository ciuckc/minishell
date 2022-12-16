/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/26 15:43:31 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 05:23:59 by scristia      ########   odam.nl         */
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
	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	data->fds[READ] = open (tok->str, O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit("heredoc_file", 1);
	unlink(tok->str);
	if (dup_and_close(data->fds[READ], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
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
