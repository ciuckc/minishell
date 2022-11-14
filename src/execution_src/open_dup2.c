/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:11:18 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/14 16:58:10 by emlicame         ###   ########.fr       */
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
