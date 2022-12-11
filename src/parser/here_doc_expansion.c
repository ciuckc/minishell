/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_expansion.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 19:26:12 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/10 22:26:37 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../expansion/var_expansion.h"
#include "../utils/libft/libft.h"

static void	st_read_concat(char **delim, char **here, char **read)
{
	char	*temp;

	temp = NULL;
	while (ft_strcmp(*delim, *read) || ft_strcmp("^C", *read))
	{
		temp = ft_strjoin_va(3, *here, *read, "\n");
		free(*here);
		free(*read);
		if (temp == NULL)
		{
			free(*delim);
			*delim = NULL;
			return ;
		}
		*here = temp;
		*read = readline("> ");
		if (*read == NULL)
		{
			free(*delim);
			*delim = NULL;
			return (free(*here));
		}
	}
	free(*read);
}

static void	st_uncouple_nodes(t_token **delim, char *here_doc)
{
	t_token	*d_less;

	d_less = (*delim)->prev;
	if ((*delim)->next)
		(*delim)->next->prev = d_less;
	d_less->next = (*delim)->next;
	free((*delim)->str);
	free(*delim);
	free(d_less->str);
	*delim = d_less;
	(*delim)->str = here_doc;
}

static void	st_read_here(t_token **delim)
{
	char		*read_line;
	char		*here_doc;

	init_sig_handle(3);
	here_doc = ft_strdup("");
	if (here_doc == NULL)
		return ;
	read_line = readline("> ");
	if (read_line == NULL)
	{
		g_exit_code = 1;
		free((*delim)->str);
		(*delim)->str = NULL;
		return ;
	}
	st_read_concat(&(*delim)->str, &here_doc, &read_line);
	if ((*delim)->str == NULL)
		return ;
	st_uncouple_nodes(delim, here_doc);
}

static void	st_if_type_is_dless(t_cmd_list **cmd, u_int32_t i)
{
	if ((*cmd)[i].cmd_list->type == DLESS)
	{
		(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		remove_quotes((*cmd)[i].cmd_list);
		st_read_here(&(*cmd)[i].cmd_list);
	}
}

void	here_doc_expansion(t_cmd_list **cmd)
{
	t_token		*head;
	u_int32_t	i;

	i = 0;
	head = NULL;
	while ((*cmd)[i].cmd_list)
	{
		head = (*cmd)[i].cmd_list;
		while ((*cmd)[i].cmd_list)
		{
			st_if_type_is_dless(cmd, i);
			if ((*cmd)[i].cmd_list->str == NULL)
				return (free_cmd_list(cmd));
			(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		}
		(*cmd)[i].cmd_list = head;
		i++;
	}
	here_doc_node_remove(cmd);
	init_sig_handle(1);
}
