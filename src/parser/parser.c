/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/03 02:21:52 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser(char *full_cmd)
{
	t_token_list		*tokens;

	tokens = retrieve_word_list(full_cmd);
	if (tokens == NULL)
		return ;
}
