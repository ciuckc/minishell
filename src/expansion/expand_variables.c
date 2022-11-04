/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 02:23:42 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/04 03:13:10 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static ssize_t	st_var_len(char **str, t_table *table)
{
	ssize_t	name_len;
	t_env	vars;

	name_len = 0;
	(*str)++;
	if (**str == '\'' || **str == '\"' || **str == '$')
		return (0);
	name_len += ft_len_to_char_set(*str, "$\'\"");
	vars.name = ft_substr(*str, 0, name_len);
	if (vars.name == NULL)
		return (-1);
	*str += name_len;
	vars.value = item_search(vars.name, table)->data;
	if (vars.value == NULL)
		return (0);
	return (free(vars.name), ft_strlen(vars.value));
}

static ssize_t	st_get_len_of_expanded_var(char *str, t_table *table)
{
	ssize_t	len;

	len = 0;
	while (*str)
	{
		while (*str && ft_strchr("$\"\'", *str))
			str++;
		if (*str == '\'')
		{
			str++;
			str += ft_len_to_char_set(str, "\'") + 1;
		}
		else if (*str == '\"')
		{
			str++;
			str += ft_len_to_char_set(str, "$\"");
			if (*str == '\"')
				str++;
			else if (*str == '$')
				len += st_var_len(&str, table);
		}
		else if (*str == '$')
			len += st_var_len(&str, table);
	}
	return (len);
}

static ssize_t	st_get_len_unexpanded(char *str)
{
	(void)str;
	return (0);
}

static void	st_expand_var_in_str(t_token_list *word, t_table *table)
{
	ssize_t	var_len_sum;
	ssize_t	unexpanded_len;

	var_len_sum = st_get_len_of_expanded_var(word->tok->tok, table);
	unexpanded_len = st_get_len_unexpanded(word->tok->tok);
}

void	expand_variables(t_token_list *words, t_table *table)
{
	u_int32_t		i;
	t_token_list	*head;

	i = 0;
	head = words;
	while (words)
	{
		if (ft_strchr(words->tok->tok, '$'))
			st_expand_var_in_str(words, table);
		if (words->tok == NULL)
		{
			//free_word_list(&head);
			return ;
		}
		words = words->next;
	}
}
