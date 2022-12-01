/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 19:02:27 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 19:03:57 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../expansion/var_expansion.h"

void	remove_quotes_list(t_token *word)
{
	while (word)
	{
		if (word->str == NULL)
		{
			word = word->next;
			continue ;
		}
		if ((ft_strchr(word->str, '\'') || ft_strchr(word->str, '\"')) \
		&& word->type != DLESS)
			remove_quotes(word);
		word = word->next;
	}
}
