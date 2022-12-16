/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanded_var_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 04:17:43 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 23:52:57 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_count_exp_var(char **str, t_expand_len *len, t_table *table, \
bool d_quoted)
{
	if (ft_isdigit(**str))
		(*str)++;
	else if (**str == '$')
	{
		len->env_var_len += get_pid_len();
		(*str)++;
	}
	else if (((**str == '\'' || **str == '\"') && d_quoted) || **str == '\0')
		len->unexp_len++;
	else if (**str == '?')
	{
		len->env_var_len += ft_digit_len(g_exit_code);
		(*str)++;
	}
	else
		count_data_len(str, len, table, d_quoted);
}

static void	st_count_in_d_quote(char **str, t_expand_len *len, t_table *table, \
bool d_quoted)
{
	(void)d_quoted;
	len->unexp_len++;
	while (**str != '\"' && **str)
	{
		if (**str == '$')
		{
			(*str)++;
			st_count_exp_var(str, len, table, true);
			continue ;
		}
		(*str)++;
		len->unexp_len++;
	}
}

static void	st_count_in_s_quote(char **str, t_expand_len *len, t_table *table, \
bool d_quoted)
{
	(void)d_quoted;
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
	void			(**func_table)(char **, t_expand_len *, t_table *, bool);

	full_len = (t_expand_len){0};
	func_table = (void (*[128])(char **, t_expand_len *, \
	t_table *, bool)){[(int) '\''] = st_count_in_s_quote, [(int) '\"'] = \
	st_count_in_d_quote, [(int) '$'] = st_count_exp_var};
	while (*str)
	{
		if (*str == '\'' || *str == '\"' || *str == '$')
		{
			str++;
			(*func_table[(int) *(str - 1)])(&str, &full_len, table, false);
		}
		else
		{
			str++;
			full_len.unexp_len++;
		}
	}
	return (full_len.env_var_len + full_len.unexp_len);
}
