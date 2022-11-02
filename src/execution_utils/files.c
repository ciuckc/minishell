/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:18:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/02 19:39:12 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
t_file	*get_files_input(t_token *tok)
{
	t_file	*top;

	top = NULL;
	while (tok && tok->token_type != PIPE)
	{
		if (tok->token_type == LESS)
		{
			tok = tok->next;
			ft_lstadd_back_file(&top, ft_lstnew_file(tok->content, \
			tok->token_type));
		}
		tok = tok->next;
	}
	return (top);
}
*/

//ft_lstadd_back_t(&argv_l, ft_lstnew_t(args[i++]));

t_file	*get_files_input(void)
{
	t_file	*top;
	t_file	*node1;
	t_file	*node2;

	top = NULL;
	node1 = malloc(sizeof(t_file));
	node1->name = ft_strdup("infile");
	node1->flag = LESS;
	node2 = malloc(sizeof(t_file));
	node2->name = ft_strdup("outfile");
	node2->flag = GREAT;
	top = node1;
	node1->next = node2;
	node2->next = NULL;
	return (top);
}
