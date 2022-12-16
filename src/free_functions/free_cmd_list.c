/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 00:32:36 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 06:32:27 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "free_functions.h"

void	free_cmd_list(t_cmd_list **lst)
{
	u_int32_t	i;

	i = 0;
	while ((*lst)[i].cmd_list)
	{
		free_word_list(&(*lst)[i].cmd_list);
		i++;
	}
	free(((*lst)[i].cmd_list));
	free(*lst);
	*lst = NULL;
}
