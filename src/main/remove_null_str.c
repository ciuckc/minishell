/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_null_str.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 18:41:21 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 20:24:37 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_remove_node(t_token **word, t_token **head)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	prev = (*word)->prev;
	curr = *word;
	next = (*word)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (*head == *word)
		*head = next;
	*word = next;
	free(curr);
}

void	remove_null_str(t_token **words)
{
	t_token	*head;

	head = *words;
	while (*words)
	{
		if ((*words)->str == NULL)
		{
			st_remove_node(words, &head);
			continue ;
		}
		*words = (*words)->next;
	}
	*words = head;
}
