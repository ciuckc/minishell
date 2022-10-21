/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_boundry_to_list.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 03:22:23 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/21 03:46:59 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_scan_tok	*st_create_scan_tok(char *cmd, u_int32_t start, \
u_int32_t end)
{
	t_scan_tok	*new;

	new = malloc(sizeof(t_scan_tok));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->orginal_str = cmd;
	new->boundry.start = start;
	new->boundry.end = end;
	return (new);
}

static void	st_add_tok_back(t_scan_tok *lst, t_scan_tok *new)
{
	while (lst->next != NULL)
		lst = lst->next;
	new->prev = lst;
	lst->next = new;
}

t_scan_tok	*add_boundry_to_list(t_scan_tok **lst, u_int32_t start, \
u_int32_t end, char *cmd)
{
	t_scan_tok	*scan_tok;

	scan_tok = NULL;
	if (*lst == NULL)
	{
		scan_tok = st_create_scan_tok(cmd, start, end);
		if (scan_tok == NULL)
			return (NULL);
		*lst = scan_tok;
	}
	else
	{
		scan_tok = st_create_scan_tok(cmd, start, end);
		if (scan_tok == NULL)
			return (NULL);
		st_add_tok_back(*lst, scan_tok);
	}
	return (*lst);
}
