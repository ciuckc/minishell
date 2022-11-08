/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 04:44:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 02:59:19 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	st_count_cmds(t_token_list *words)
{
	size_t	count;

	count = 0;
	while (words)
	{
		if (words->tok->type == AND_IF || words->tok->type == OR_IF || \
		words->tok->type == END)
			count++;
		words = words->next;
	}
	return (count);
}

static void	st_remove_and_link(t_token_list **words)
{
	t_token_list	*next;
	t_token_list	*prev;

	next = (*words)->next;
	prev = (*words)->prev;
	if (prev != NULL)
		prev->next = NULL;
	if (next != NULL)
		next->prev = NULL;
	free((*words)->tok->str);
	free((*words)->tok);
	(*words)->tok = NULL;
	*words = next;
}

static void	st_and_or_synthax_check(t_cmd_list **list, size_t len)
{
	size_t	i;
	char	**err_code;

	i = 0;
	err_code = (char *[]){[OR_IF] = "||", [AND_IF] = "&&"};
	if ((*list)[len].cmd_list->tok == NULL)
	{
		while (i < len)
		{
			free_word_list(&(*list)[i].cmd_list);
			i++;
		}
		printf("minishell: parse error near `%s'\n", \
		err_code[(*list)->cmd_list_type]);
		free(*list);
		*list = NULL;
	}
}

static void	st_assign_to_list(t_cmd_list **list, t_token_list *words, \
size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*list)[i].cmd_list = words;
		while (words->tok->type != AND_IF && words->tok->type != OR_IF && \
		words->tok->type != END)
			words = words->next;
		(*list)[i].cmd_list_type = words->tok->type;
		st_remove_and_link(&words);
		st_and_or_synthax_check(list, i);
		if (*list == NULL)
			break ;
		i++;
	}
}

void	create_cmd_list(t_cmd_list **list, t_token_list *words)
{
	size_t	count;

	count = st_count_cmds(words);
	*list = ft_calloc(count + 1, sizeof(t_cmd_list));
	if (*list == NULL)
		return (free_word_list(&words));
	st_assign_to_list(list, words, count);
}
