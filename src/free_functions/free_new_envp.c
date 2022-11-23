/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_new_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 05:41:54 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/23 13:36:12 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static u_int32_t	get_len_envp(char **envp)
{
	u_int32_t	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

void	free_new_envp(char ***envp, u_int32_t i)
{
	u_int32_t	pos;

	pos = 0;
	if (i == 0)
		i = get_len_envp(*envp);
	while (pos < i)
	{
		free((*envp)[pos]);
		pos++;
	}
	free(*envp);
	*envp = NULL;
}
