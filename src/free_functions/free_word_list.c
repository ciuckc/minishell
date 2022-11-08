/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_word_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 17:28:39 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 02:11:49 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "free_functions.h"

void	free_word_list(t_token_list **list)
{
	t_token_list	*prev;

	prev = *list;
	while (*list != NULL)
	{
		*list = (*list)->next;
		free(prev->tok->str);
		free(prev->tok);
		prev = *list;
	}
	*list = NULL;
}
