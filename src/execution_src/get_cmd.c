/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:46 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/28 18:09:29 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	st_lstsize(t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		i++;
		tok = tok->next;
	}
	return (i);
}

void	get_cmd(t_token *tok, t_input *data)
{
	int		len;
	int		i;
	t_token	*token;

	i = 0;
	token = tok;
	len = st_lstsize(tok) + 1;
	data->cmd_args = (char **)ft_calloc(len, sizeof (char *));
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR || \
		token->type == S_QUOTE || token->type == D_QUOTE || \
		token->type == ASSIGNMENT_WORD)
		{
			data->cmd_args[i] = ft_strdup(token->str);
			i++;
		}
		if (token->type == LESS || token->type == GREAT || \
		token->type == DGREAT)
		token = token->next->next;
		else
			token = token->next;
	}
	data->cmd_args[i] = NULL;
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
