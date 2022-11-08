/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   retrieve_word_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 02:28:14 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token_list	*st_create_node_word(t_token *word)
{
	t_token_list	*new;

	new = ft_calloc(1, sizeof(t_token_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->tok = word;
	return (new);
}

static void	st_add_back(t_token_list **list, t_token_list *new)
{
	t_token_list	*head;

	head = *list;
	while ((*list)->next)
		*list = (*list)->next;
	new->prev = *list;
	(*list)->next = new;
	*list = head;
}

static void	st_add_word_to_list(t_token_list **list, t_token *word)
{
	t_token_list	*new;

	new = st_create_node_word(word);
	if (new == NULL)
	{
		free_word_list(list);
		free(word);
		return ;
	}
	if (*list == NULL)
		*list = new;
	else
		st_add_back(list, new);
}

static void	st_make_word_list(t_token_list **word_list, t_scan_tok *scan_tok)
{
	t_token		*word;

	word = NULL;
	while (scan_tok)
	{
		word = build_word(&scan_tok);
		if (word == NULL)
			return (free_scan_list(&scan_tok), free_word_list(word_list));
		st_add_word_to_list(word_list, word);
		if (*word_list == NULL)
			return (free_scan_list(&scan_tok));
	}
	word = ft_calloc(1, sizeof(t_token));
	if (word == NULL)
		return (free_scan_list(&scan_tok), free_word_list(word_list));
	word->type = END;
	st_add_word_to_list(word_list, word);
	if (*word_list == NULL)
		return (free_scan_list(&scan_tok));
}

t_token_list	*retrieve_word_list(char *full_cmd)
{
	t_scan_tok		*scan_tok;
	t_token_list	*word_list;

	scan_tok = tok_len_scan_list(&full_cmd);
	if (scan_tok == NULL)
		return (NULL);
	word_list = NULL;
	st_make_word_list(&word_list, scan_tok);
	free_scan_list(&scan_tok);
	return (word_list);
}
