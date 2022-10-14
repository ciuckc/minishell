/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/14 17:07:58 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser(char *full_cmd, char **envp)
{
	t_list		*tokens;
	t_table		*env_table;

	env_table = create_env_table(envp);
	if (env_table == NULL)
		return ;
	tokens = create_token_list(full_cmd);
	if (tokens == NULL)
		return ;
}
