/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_words.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 23:36:01 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	expand_words(t_token **words, t_table *table)
{
	t_token	*head;

	if ((*words))
		if ((*words)->str == NULL)
			return ;
	head = *words;
	while (*words)
	{
		if (needs_expansion((*words)->str))
			(*words)->str = expand_var_in_str(*words, table);
		(*words) = (*words)->next;
	}
	*words = head;
}
