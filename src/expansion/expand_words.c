/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_words.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/18 18:07:39 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_remove_node(t_token **words)
{
	t_token	*prev;
	t_token	*next;

	prev = *words;
	next = (*words)->next;
	if (next != NULL)
		next->prev = prev;
	if (prev != NULL)
		prev->next = next;
	(*words) = next;
	free(prev);
}

static void	st_skip_s_quote(char **str)
{
	(*str)++;
	while (**str != '\'' && **str)
		(*str)++;
}

static void	st_skip_d_quote_if_no_dol(char **str)
{
	(*str)++;
	while (**str != '\"' && **str != '$' && **str)
		(*str)++;
}

bool	st_needs_expansion(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			st_skip_s_quote(&str);
		else if (*str == '\"')
			st_skip_d_quote_if_no_dol(&str);
		if (*str == '\0')
			return (false);
		else if (*str == '$')
			return (true);
		else
			str++;
	}
	return (false);
}

void	expand_words(t_token **words, t_table *table)
{
	t_token	*head;

	head = *words;
	while (*words)
	{
		if (st_needs_expansion((*words)->str))
			expand_var_in_str(*words, table);
		if ((*words)->str == NULL)
		{
			st_remove_node(words);
			if (*words == NULL)
				return ;
			continue ;
		}
		if (ft_strchr((*words)->str, '\'') || ft_strchr((*words)->str, '\"'))
			remove_quotes(*words);
		(*words) = (*words)->next;
	}
	*words = head;
}
