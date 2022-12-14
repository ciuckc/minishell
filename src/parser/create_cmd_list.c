/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 04:44:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 06:15:36 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	st_count_cmds(t_token *words)
{
	size_t	count;

	count = 0;
	while (words)
	{
		if (words->type == AND_IF || words->type == OR_IF || \
		words->type == END)
			count++;
		words = words->next;
	}
	return (count);
}

static void	st_and_or_synthax_check(t_token **words, t_cmd_list **list, \
size_t len)
{
	if ((*words) == (*list)[len].cmd_list)
	{
		if ((*words)->type == OR_IF)
			ft_putendl_fd("minishell: synthax error near `||'", 2);
		else if ((*words)->type == AND_IF)
			ft_putendl_fd("minishell: synthax error near `&&'", 2);
		else if ((*words)->type == END)
			ft_putendl_fd("minishell: synthax error near `END'", 2);
		free_cmd_list(list);
		g_exit_code = 258;
	}
}

static void	st_remove_and_link(t_token **words, t_cmd_list **list, size_t len)
{
	t_token	*temp;

	temp = (*words)->next;
	if ((*words)->prev)
		(*words)->prev->next = NULL;
	if ((*words)->next)
		(*words)->next->prev = NULL;
	free((*words)->str);
	st_and_or_synthax_check(words, list, len);
	if (*list == NULL)
		return ;
	free(*words);
	*words = temp;
}

static void	st_assign_to_list(t_cmd_list **list, t_token *words, \
size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*list)[i].cmd_list = words;
		while (words->type != AND_IF && words->type != OR_IF && \
		words->type != END)
			words = words->next;
		(*list)[i].cmd_list_type = words->type;
		st_remove_and_link(&words, list, i);
		if ((*list) == NULL)
			return ;
		i++;
	}
}

void	create_cmd_list(t_cmd_list **list, t_token *words)
{
	size_t	count;

	count = st_count_cmds(words);
	*list = ft_calloc(count + 1, sizeof(t_cmd_list));
	if (*list == NULL)
		return (free_word_list(&words));
	st_assign_to_list(list, words, count);
}
