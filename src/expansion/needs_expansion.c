/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   needs_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 20:12:15 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/30 21:03:27 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

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

bool	needs_expansion(char *str)
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
