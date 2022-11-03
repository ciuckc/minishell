/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/03 23:20:00 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_expand_var_in_str(t_token_list *word, t_table *table)
{
	size_t	len;

	(void)table;
	len = st_get_len_of_expanded_str(word->tok->tok, table);
}

void	expand_variables(t_token_list *words, t_table *table)
{
	u_int32_t		i;
	t_token_list	*head;

	i = 0;
	head = words;
	while (words)
	{
		if (ft_strchr(words->tok->tok, '$') && words->tok->type != S_QUOTE)
			st_expand_var_in_str(words, table);
		if (words->tok == NULL)
			free_word_list(&head);
		words = words->next;
	}
}
