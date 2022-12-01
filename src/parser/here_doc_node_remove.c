/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_node_remove.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 22:14:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 23:41:46 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static u_int32_t	st_here_doc_count(t_token *word)
{
	u_int32_t	count;

	count = 0;
	while (word)
	{
		if (word->type == DLESS)
			count++;
		word = word->next;
	}
	return (count);
}

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

static void	st_remove_extra_nodes(t_token **words, t_token **head, u_int32_t \
len)
{
	if (len <= 1)
		return ;
	while (len > 1)
	{
		if ((*words)->type == DLESS)
		{
			st_remove_node(words, head);
			len--;
			continue ;
		}
		(*words) = (*words)->next;
	}
}

static void	st_check_if_one_here_doc(t_token *word)
{
	if (word->type == DLESS && !word->next && !word->prev)
	{
		free(word->str);
		word->str = NULL;
	}
}

void	here_doc_node_remove(t_cmd_list **cmd)
{
	t_token		*head;
	u_int32_t	i;
	u_int32_t	len;

	i = 0;
	len = 0;
	head = (*cmd)[i].cmd_list;
	while ((*cmd)[i].cmd_list)
	{
		head = (*cmd)[i].cmd_list;
		while ((*cmd)[i].cmd_list)
		{
			len = st_here_doc_count((*cmd)[i].cmd_list);
			st_remove_extra_nodes(&(*cmd)[i].cmd_list, &head, len);
			st_check_if_one_here_doc((*cmd)[i].cmd_list);
			(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		}
		(*cmd)[i].cmd_list = head;
		i++;
	}
}
