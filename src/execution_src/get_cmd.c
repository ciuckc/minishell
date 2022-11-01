/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:46 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/01 19:15:06 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_cmd(t_token *tok, t_input *data)
{
	int		len;
	int		i;
	t_token	*token;

	i = 0;
	token = tok;
	len = ft_lstsize_t(tok) + 1;
	data->cmd_args = (char **)ft_calloc(len, sizeof (char *));
	while (token && token->token_type != PIPE)
	{
		if (token->token_type == WORD)
		{
			data->cmd_args[i] = ft_strdup(token->content);
			i++;
		}
		if (token->token_type == LESS || \
			token->token_type == GREAT || \
			token->token_type == DLESS || \
			token->token_type == DGREAT)
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
		if (tok->token_type == PIPE)
			count++;
		tok = tok->next;
	}
	data->cmd_count = count + 1;
	dprintf (2, "how many cmd? %d\n", data->cmd_count);
}
