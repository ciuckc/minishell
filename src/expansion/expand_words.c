/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_words.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/14 14:12:24 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	expand_words(t_token *words, t_table *table)
{
	u_int32_t	i;
	t_token		*head;

	i = 0;
	(void)table;
	head = words;
	while (words)
	{
		if (dolar_is_unquoted(words->str))
		{
			printf("WILL BE EXPANDED\n");
			expand_var_in_str(words, table);
		}
		words = words->next;
	}
}
