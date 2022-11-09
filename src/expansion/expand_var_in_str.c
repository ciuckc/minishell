/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var_in_str.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 04:02:53 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/09 16:04:55 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	expand_var_in_str(t_token *word, t_table *table)
{
	ssize_t	sum_expanded_vars;

	(void)table;
	sum_expanded_vars = expanded_var_len(word->str, table);
}
