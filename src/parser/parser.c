/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 02:57:45 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_list	*parser(char *full_cmd)
{
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	size_t			i;

	i = 0;
	tokens = retrieve_word_list(full_cmd);
	if (tokens == NULL)
		return (NULL);
	create_cmd_list(&cmd_list, tokens);
	if (cmd_list == NULL)
		return (NULL);
	while (cmd_list[i].cmd_list_type)
	{
		while (cmd_list[i].cmd_list)
		{
			printf("%s\n", cmd_list[i].cmd_list->tok->str);
			cmd_list[i].cmd_list = cmd_list[i].cmd_list->next;
		}
		i++;
	}
	return (cmd_list);
}
