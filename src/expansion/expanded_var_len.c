/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanded_var_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 04:17:43 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/09 16:07:54 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

ssize_t	expanded_var_len(char *str, t_table *table)
{
	bool	is_s_quote;
	bool	is_d_quote;
	ssize_t	len;

	(void)table;
	len = 0;
	is_d_quote = false;
	is_s_quote = false;
	while (*str)
	{
		if (*str == '\'')
			is_s_quote = true;
		else if (*str == '\"')
			is_d_quote = true;
		else if (*str == '$')
			printf("SSS");
		str++;
	}
	return (0);
}
