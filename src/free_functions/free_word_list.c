/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_word_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 17:28:39 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 23:44:24 by scristia      ########   odam.nl         */
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
		{
			if (prev->type == DLESS)
				unlink(prev->str);
			free(prev->str);
		}
		free(prev);
		prev = *list;
	}
	*list = NULL;
}
