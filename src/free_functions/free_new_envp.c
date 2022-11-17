/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_new_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 05:41:54 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 05:46:39 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_new_envp(char ***envp, u_int32_t i)
{
	u_int32_t	pos;

	pos = 0;
	while (pos < i)
	{
		free((*envp)[pos]);
		pos++;
	}
	free(*envp);
	*envp = NULL;
}
