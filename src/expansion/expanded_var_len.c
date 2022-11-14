/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanded_var_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 04:17:43 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/14 15:55:12 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_count_data_len(char **str, t_expand_len *len, t_table *table)
{
	t_env	param;

	param = (t_env){0};
	param.name = ft_substr(*str, 0, ft_len_to_char_set(*str, "\"\'$"));
	if (param.name == NULL)
		return ;
	param.value = item_search(param.name, table)->data;
	if (param.value == NULL)
		return (free(param.name));
	(*str) += ft_strlen(param.name);
	len->env_var_len += ft_strlen(param.value);
	free(param.name);
}

static void	st_count_exp_var(char **str, t_expand_len *len, t_table *table)
{
	t_env		param;

	param = (t_env){0};
	if (**str == '\0')
		return ;
	else if (**str == '$')
		(*str)++;
	else if (**str == '?')
	{
		len->env_var_len += ft_digit_len(g_exit_code);
		(*str)++;
	}
	else
		st_count_data_len(str, len, table);
}

static void	st_count_in_d_quote(char **str, t_expand_len *len, t_table *table)
{
	len->unexp_len++;
	while (**str != '\"' && **str)
	{
		if (**str == '$')
		{
			(*str)++;
			if (**str == '\'' || **str == '\"' || **str == ' ')
			{
				len->unexp_len++;
				continue ;
			}
			st_count_exp_var(str, len, table);
			continue ;
		}
		(*str)++;
		len->unexp_len++;
	}
}

static void	st_count_in_s_quote(char **str, t_expand_len *len, t_table *table)
{
	(void)table;
	len->unexp_len++;
	while (**str != '\'' && **str)
	{
		len->unexp_len++;
		(*str)++;
	}
	len->unexp_len++;
	(*str)++;
}

ssize_t	expanded_var_len(char *str, t_table *table)
{
	t_expand_len	full_len;
	void			(**func_table)(char **, t_expand_len *, t_table *);

	full_len = (t_expand_len){0};
	func_table = (void (*[128])(char **, t_expand_len *, \
	t_table *)){[(int) '\''] = st_count_in_s_quote, [(int) '\"'] = \
	st_count_in_d_quote, [(int) '$'] = st_count_exp_var};
	while (*str)
	{
		if (*str == '\'' || *str == '\"' || *str == '$')
		{
			str++;
			(*func_table[(int) *(str - 1)])(&str, &full_len, table);
		}
		else
		{
			str++;
			full_len.unexp_len++;
		}
	}
	return (full_len.env_var_len + full_len.unexp_len);
}
