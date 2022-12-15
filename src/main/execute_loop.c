/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_loop.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 23:47:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 19:22:33 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	st_expand_cmd_and_env(t_cmd_list **cmd_list, t_table *env_table, \
char ***envp, u_int32_t i)
{
	create_new_envp(env_table, envp);
	expand_words(&(*cmd_list)[i].cmd_list, env_table);
	remove_quotes_list((*cmd_list)[i].cmd_list);
}

void	execute_loop(t_cmd_list **cmd_list, t_table *env_table, \
char ***envp)
{
	u_int32_t	i;

	i = 0;
	while ((*cmd_list)[i].cmd_list)
	{
		st_expand_cmd_and_env(cmd_list, env_table, envp, i);
		if (synthax_check((*cmd_list)[i].cmd_list))
			return (free_new_envp(envp, 0), free_cmd_list(cmd_list));
		remove_null_str(&(*cmd_list)[i].cmd_list);
		if ((*cmd_list)[i].cmd_list == NULL)
		{
			free_new_envp(envp, 0);
			i++;
			continue ;
		}
		g_exit_code = execution((*cmd_list)[i].cmd_list, env_table, *envp);
		if (g_exit_code != 0 && (*cmd_list)[i].cmd_list_type == AND_IF)
			break ;
		free_new_envp(envp, 0);
		i++;
	}
	if (*envp)
		free_new_envp(envp, 0);
	free_cmd_list(cmd_list);
}
