/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_word_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 17:28:39 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 06:33:31 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "free_functions.h"

void	free_word_list(t_token **list)
{
	t_token	*prev;

	prev = *list;
	while (*list != NULL)
	{
		*list = (*list)->next;
		if (prev->str)
			free(prev->str);
		free(prev);
		prev = *list;
	}
	*list = NULL;
}
