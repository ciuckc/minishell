/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/16 20:27:31 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	expand_variables(t_token *words, t_table *table)
{
	u_int32_t	i;
	t_token		*head;

	i = 0;
	(void)table;
	head = words;
	while (words)
	{
		expand_var_in_str(words, table);
		if (words == NULL)
		{
			free_word_list(&head);
			return ;
		}
		words = words->next;
	}
}
