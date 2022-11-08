/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 03:59:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_expand_var_in_str(t_token_list *word, t_table *table)
{
}

void	expand_variables(t_token_list *words, t_table *table)
{
	u_int32_t		i;
	t_token_list	*head;

	i = 0;
	head = words;
	while (words)
	{
		if (ft_strchr(words->tok->str, '$'))
			st_expand_var_in_str(words, table);
		if (words->tok == NULL)
		{
			//free_word_list(&head);
			return ;
		}
		words = words->next;
	}
}
