/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_builtins.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/11 17:39:53 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/17 17:19:27 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int32_t	built_redir_less(t_token *tok, t_input *data)
{
	if (data->fds[READ] != STDIN_FILENO)
		close(data->fds[READ]);
	data->fds[READ] = open (tok->next->str, O_RDONLY);
	if (data->fds[READ] < 0)
		return (error_print(tok->next->str), 1);
	return (0);
}

static int32_t	built_redir_great(t_token *tok, t_input *data)
{
	if (data->fds[WRITE] != STDOUT_FILENO)
		close(data->fds[WRITE]);
	data->fds[WRITE] = open(tok->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fds[WRITE] < 0)
		return (error_print(tok->next->str), 1);
	return (0);
}

static int32_t	built_redir_dgreat(t_token *tok, t_input *data)
{
	if (data->fds[WRITE] != STDOUT_FILENO)
		close(data->fds[WRITE]);
	data->fds[WRITE] = open(tok->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->fds[WRITE] < 0)
		return (error_print(tok->next->str), 1);
	return (0);
}

int32_t	check_if_redir_built(t_token *tok, t_input *data)
{
	int		ret;

	ret = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == LESS)
		{
			if (built_redir_less(tok, data))
				return (1);
		}
		else if (tok->type == GREAT)
		{
			if (built_redir_great(tok, data))
				return (1);
		}
		else if (tok->type == DGREAT)
		{
			if (built_redir_dgreat(tok, data))
				return (1);
		}
		tok = tok->next;
	}
	return (ret);
}
