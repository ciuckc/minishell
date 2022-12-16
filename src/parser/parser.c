/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 18:17:15 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_print_error(t_token *words, t_token_type cmd_type)
{
	if (words == NULL)
	{
		if (cmd_type == END)
			ft_putendl_fd("minishell: synthax error near unexpected token \
`END'", 2);
		else if (cmd_type == AND_IF)
			ft_putendl_fd("minishell: synthax error near unexpected token \
`AND_IF'", 2);
		else if (cmd_type == OR_IF)
			ft_putendl_fd("minishell: synthax error near unexpected token \
`OR_IF'", 2);
	}
	else if (words->type != WORD && words->type != DOLLAR && words->type != \
	ASSIGNMENT_WORD && words->type != PIPE)
	{
		ft_putstr_fd("minishell: synthax error near unexpected token ", 2);
		ft_putendl_fd(words->str, 2);
	}
	g_exit_code = 258;
}

static bool	st_check_single_cmd(t_token *words, t_token_type cmd_type)
{
	while (words)
	{
		while (words)
		{
			if (words->type != DOLLAR && words->type != WORD && words->type \
			!= ASSIGNMENT_WORD && words->type != PIPE)
				break ;
			words = words->next;
		}
		if (words == NULL)
			break ;
		if (words->type == LESS || words->type == DLESS || words->type == \
		GREAT || words->type == DGREAT)
			words = words->next;
		if (words == NULL)
			return (st_print_error(words, cmd_type), true);
		else if (words->type != WORD && words->type != DOLLAR && words->type != \
		ASSIGNMENT_WORD && words->type != PIPE)
			return (st_print_error(words, cmd_type), true);
	}
	return (false);
}

static void	st_synthax_check(t_cmd_list **cmd)
{
	u_int32_t	i;

	i = 0;
	while ((*cmd)[i].cmd_list)
	{
		if (st_check_single_cmd((*cmd)[i].cmd_list, (*cmd)[i].cmd_list_type))
		{
			free_cmd_list(cmd);
			return ;
		}
		i++;
	}
}

t_cmd_list	*parser(char *full_cmd)
{
	t_token		*tokens;
	t_cmd_list	*cmd_list;

	add_history(full_cmd);
	init_sig_handle(1);
	tokens = retrieve_word_list(full_cmd);
	if (tokens == NULL)
		return (NULL);
	cmd_list = NULL;
	create_cmd_list(&cmd_list, tokens);
	if (cmd_list == NULL)
		return (NULL);
	st_synthax_check(&cmd_list);
	if (cmd_list == NULL)
		return (NULL);
	here_doc_expansion(&cmd_list);
	return (cmd_list);
}
