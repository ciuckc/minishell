/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:02:46 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/11 16:47:19 by scristia      ########   odam.nl         */
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
	t_token	*to;

	i = 0;
	to = tok;
	len = st_lstsize(tok) + 1;
	data->cmd_args = (char **)ft_calloc(len, sizeof (char *));
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
