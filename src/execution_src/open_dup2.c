/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:11:18 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 16:28:07 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_infiles(t_token *tok, t_input *data)
{
	int	ret;

	ret = 0;
	while (tok && tok->token_type != PIPE)
	{
		if (tok->token_type == LESS)
		{
			ret = 1;
			if (data->fds[READ] != STDIN_FILENO)
				close(data->fds[READ]);
			data->fds[READ] = open (tok->next->content, O_RDONLY);
			if (data->fds[READ] < 0)
				error_exit(tok->next->content, 1);
		}
		tok = tok->next;
	}
	return (ret);
}

int	open_outfiles(t_token *tok, t_input *data)
{
	int	ret;

	ret = 0;
	while (tok && tok->token_type != PIPE)
	{
		if (tok->token_type == GREAT)
		{
			ret = 1;
			if (data->fds[WRITE] != STDOUT_FILENO)
				close(data->fds[WRITE]);
			data->fds[WRITE] = open(tok->next->content, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (data->fds[WRITE] < 0)
				error_exit(tok->next->content, 1);
		}
		tok = tok->next;
	}
	return (ret);
}


/*
	void	set_fds(t_input *data)
	{
		if (dup2(data->fds[READ], STDIN_FILENO) == -1)
			error_exit("Dup failed", 1);
		close(data->fds[READ]);
		if (dup2(data->fds[WRITE], STDOUT_FILENO) == -1)
			error_exit("Dup failed", 1);
		close(data->fds[WRITE]);
	}
	Remember!!! man dup2
	 In dup2(), the value of the new descriptor fildes2 is specified.  
	 If fildes and fildes2 are equal, then dup2() just returns fildes2; 
	 no other changes are made to the existing descriptor.  
	 Otherwise, if descriptor fildes2 is already in use, it is first deallocated
	 as if a close(2) call had
     been done first.
*/