/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 00:32:36 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/02 00:51:09 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "free_functions.h"

static u_int32_t	st_get_len(t_cmd_list *lst)
{
	u_int32_t	i;

	i = 0;
	while (lst[i].cmd_list_type != END)
		i++;
	return (i + 1);
}

void	free_cmd_list(t_cmd_list **lst)
{
	u_int32_t	len;
	u_int32_t	i;

	i = 0;
	len = st_get_len(*lst);
	while (i <= len)
	{
		free_word_list(&(*lst)[i].cmd_list);
		i++;
	}
	free(*lst);
	*lst = NULL;
}
