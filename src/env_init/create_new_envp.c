/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_new_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 05:12:52 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 05:30:45 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_create_strings(char **new, t_table *table)
{
	u_int32_t	i;

	while (i < table->entries)
	{
		new[i] = st_build_str(table);
		if (new[i] == NULL)
			free_new_envp()
	}
}

void	create_new_envp(t_table *table, char ***envp)
{
	char	**new_envp;

	new_envp = ft_calloc(table->entries + 1, sizeof(char *));
	if (new_envp == NULL)
		return ;
	st_create_strings(new_envp, table);
}