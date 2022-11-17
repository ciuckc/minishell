/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_words.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 05:36:37 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_remove_node(t_token **words)
{
	t_token	*prev;

	prev = *words;
	if ((*words)->next != NULL)
		(*words)->next->prev = (*words)->prev;
	if ((*words)->prev != NULL)
		(*words)->prev->next = (*words)->next;
	(*words) = (*words)->next;
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

void	expand_words(t_token *words, t_table *table)
{
	u_int32_t	i;
	t_token		*head;

	i = 0;
	(void)table;
	head = words;
	while (words)
	{
		if (st_needs_expansion(words->str))
			expand_var_in_str(words, table);
		if (words->str == NULL)
		{
			st_remove_node(&words);
			continue ;
		}
		if (ft_strchr(words->str, '\'') || ft_strchr(words->str, '\"'))
			remove_quotes(words);
		words = words->next;
	}
}
