/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_scan_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 03:42:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/03 01:11:00 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_scan_list(t_scan_tok **lst)
{
	t_scan_tok	*prev;

	prev = *lst;
	while (lst != NULL)
	{
		*lst = (*lst)->next;
		free(prev);
		prev = *lst;
	}
	*lst = NULL;
}
