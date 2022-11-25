/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   retrieve_word_list.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/25 18:29:09 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_add_word_to_list(t_token **list, t_token *word)
{
	t_token	*last;

	last = NULL;
	if (*list == NULL)
		*list = word;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = word;
		word->prev = last;
	}
}

static void	st_add_end_word(t_token **word_list)
{
	t_token	*word;

	word = ft_calloc(1, sizeof(t_token));
	if (word == NULL)
		return (free_word_list(word_list));
	word->type = END;
	st_add_word_to_list(word_list, word);
}

static void	st_make_word_list(t_token **word_list, t_scan_tok *scan_tok)
{
	t_token		*word;

	word = NULL;
	while (scan_tok)
	{
		word = build_word(&scan_tok);
		if (word == NULL)
			return (free_word_list(word_list));
		st_add_word_to_list(word_list, word);
	}
	st_add_end_word(word_list);
}

t_token	*retrieve_word_list(char *full_cmd)
{
	t_scan_tok		*scan_tok;
	t_token			*word_token_list;

	scan_tok = tok_len_scan_list(&full_cmd);
	if (scan_tok == NULL)
		return (NULL);
	word_token_list = NULL;
	st_make_word_list(&word_token_list, scan_tok);
	free_scan_list(&scan_tok);
	return (word_token_list);
}
