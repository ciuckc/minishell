/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_len_scan_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 03:09:34 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 03:53:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_quote_len(char **full_cmd, u_int32_t *pos)
{
	char	*quote;

	quote = "\'";
	if ((*full_cmd)[*pos] == '\"')
		quote = "\"";
	(*pos)++;
	while (!ft_strchr(quote, (*full_cmd)[*pos]) && (*full_cmd)[*pos] != '\0')
		(*pos)++;
	if ((*full_cmd)[*pos] == '\0')
	{
		ft_putstr_fd("minishell: synthax error near unexpected token ", 2);
		ft_putendl_fd(quote, 2);
		*full_cmd = NULL;
	}
	else
		(*pos)++;
}

static void	st_tok_len(char **full_cmd, u_int32_t *pos)
{
	if (ft_strchr(OPERATORS, (*full_cmd)[*pos]))
	{
		(*pos)++;
		if ((*full_cmd)[*pos] == (*full_cmd)[*pos - 1])
			(*pos)++;
	}
	else
	{
		while (!ft_strchr(IFS, (*full_cmd)[*pos]) && \
		!ft_strchr(OPERATORS, (*full_cmd)[*pos]) && (*full_cmd)[*pos])
		{
			if ((*full_cmd)[*pos] == '\"' || (*full_cmd)[*pos] == '\'')
			{
				st_quote_len(full_cmd, pos);
				if (*full_cmd == NULL)
					return ;
			}
			else
				(*pos)++;
		}
	}
}

t_scan_tok	*tok_len_scan_list(char **full_cmd)
{
	u_int32_t	start;
	u_int32_t	end;
	t_scan_tok	*scan_tok;

	start = 0;
	scan_tok = NULL;
	while ((*full_cmd)[start] && ft_isspace((*full_cmd)[start]))
		start++;
	end = start;
	while ((*full_cmd)[end])
	{
		st_tok_len(full_cmd, &end);
		if (*full_cmd == NULL)
			return (free_scan_list(&scan_tok), NULL);
		scan_tok = add_boundry_to_list(&scan_tok, start, end, *full_cmd);
		if (scan_tok == NULL)
			return (free_scan_list(&scan_tok), NULL);
		while (ft_strchr(IFS, (*full_cmd)[end]) && (*full_cmd)[end])
			end++;
		start = end;
	}
	return (scan_tok);
}
