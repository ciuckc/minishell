/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:46 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/17 01:21:09 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_cmd(t_token *tok, t_input *data)
{
	int		i;
	t_token	*to;

	i = 0;
	to = tok;
	while (to && to->type != PIPE)
	{
		if (to->type == WORD || to->type == DOLLAR || to->type == S_QUOTE || \
		to->type == D_QUOTE || to->type == ASSIGNMENT_WORD)
		{
			data->cmd_args[i] = ft_strdup(to->str);
			if (!data->cmd_args)
				error_exit("Malloc failed", 1);
			i++;
		}
		if (to->type == LESS || to->type == GREAT || to->type == DGREAT)
			to = to->next->next;
		else
			to = to->next;
	}
}

void	count_cmds(t_token *tok, t_input *data)
{
	int		count;

	count = 0;
	while (tok)
	{
		if (tok->type == PIPE)
			count++;
		tok = tok->next;
	}
	data->cmd_count = count + 1;
}
