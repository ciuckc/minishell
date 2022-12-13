/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:52:43 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/12 18:52:15 by emlicame         ###   ########.fr       */
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

void	open_in_andoutfiles(t_token *tok, t_input *data)
{
	while (tok && tok->type != PIPE)
	{
		if (tok->type == LESS)
			redir_less(tok, data);
		else if (tok->type == DLESS)
			redir_dless(tok, data);
		else if (tok->type == GREAT)
			redir_great(tok, data);
		else if (tok->type == DGREAT)
			redir_dgreat(tok, data);
		tok = tok->next;
	}
}
