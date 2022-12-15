/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 13:42:44 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 19:01:38 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_print_error(t_token *words, t_token_type cmd_type)
{
	char	**str_token_table;

	str_token_table = (char *[]){[PIPE / 4] = "|", [AMP / 4] = "&", \
	[LESS / 4] = "<", [DLESS / 4] = "<<", [GREAT / 4] = ">", \
	[DGREAT / 4] = ">>"};
	if (words == NULL)
	{
		if (cmd_type == END)
			dprintf(2, "minishell: synthax error near unexpected token \
`%s'\n", "END");
		else if (cmd_type == AND_IF)
			dprintf(2, "minishell: synthax error near unexpected token \
`%s'\n", "&&");
		else if (cmd_type == OR_IF)
			dprintf(2, "minishell: synthax error near unexpected token \
`%s'\n", "||");
	}
	else if (words->type != WORD || words->type == DOLLAR)
	{
		dprintf(2, "minishell: synthax error near unexpected token \
`%s'\n", str_token_table[words->type / 4]);
	}
}

static bool	st_check_single_cmd(t_token *words, t_token_type cmd_type)
{
	while (words)
	{
		while (words)
		{
			if (words->type != DOLLAR && words->type != WORD && words->type \
			!= ASSIGNMENT_WORD)
				break ;
			words = words->next;
		}
		if (words == NULL)
			break ;
		if (words->type == LESS || words->type == DLESS || words->type == \
		GREAT || words->type == DGREAT || words->type == PIPE || words->type \
		== AMP)
			words = words->next;
		if (words == NULL)
			return (st_print_error(words, cmd_type), true);
		else if (words->type != WORD && words->type != DOLLAR && words->type != \
		ASSIGNMENT_WORD)
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
			*cmd = NULL;
			return ;
		}
		i++;
	}
}

t_cmd_list	*parser(char *full_cmd)
{
	t_token		*tokens;
	t_cmd_list	*cmd_list;

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
	add_history(full_cmd);
	return (cmd_list);
}
