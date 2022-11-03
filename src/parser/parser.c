/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/03 05:12:45 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser(char *full_cmd, t_table *table)
{
	t_token_list		*tokens;

	tokens = retrieve_word_list(full_cmd, table);
	if (tokens == NULL)
		return ;
}
