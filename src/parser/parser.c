/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/04 10:16:27 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_list	*parser(char *full_cmd)
{
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;

	tokens = retrieve_word_list(full_cmd);
	if (tokens == NULL)
		return (NULL);
	create_cmd_list(&cmd_list, tokens);
	if (cmd_list == NULL)
		return (free_word_list(&tokens), NULL);
	return (cmd_list);
}
