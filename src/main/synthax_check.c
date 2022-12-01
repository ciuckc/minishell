/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   synthax_check.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 16:54:08 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 21:10:48 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	st_check_redirections(t_token *words)
{
	while (words)
	{
		if (words->type == LESS || words->type == GREAT \
		|| words->type == DGREAT)
		{
			words = words->next;
			if (words == NULL)
				return (dprintf(2, "minishell: sythax error near unexpected \
token `newline\'\n"));
			if (words->str == NULL)
				return (dprintf(2, "minishell: ambiguos redirect\n"));
			if (words->type != WORD && words->type != DOLLAR && words->type != \
			ASSIGNMENT_WORD)
				return (dprintf(2, "minishell: synthax error near unexpected \
token `%s\'\n", words->str));
		}
		words = words->next;
	}
	return (0);
}

static int32_t	st_check_pipe(t_token *words)
{
	bool	had_words;

	had_words = false;
	while (1)
	{
		while (words != NULL)
		{
			if (words->type == PIPE)
				break ;
			had_words = true;
			words = words->next;
		}
		if (words == NULL && had_words == true)
			return (0);
		if (words->type == PIPE && had_words == false)
			return (dprintf(2, "minishell: synthax error near unexpected \
token \"|\"\n"));
		had_words = false;
		words = words->next;
		if (words == NULL && had_words == false)
			return (dprintf(2, "minishell: synthax error near unexpected \
token `|\'\n"));
	}
	return (1);
}

int32_t	synthax_check(t_token *words)
{
	int32_t	check;

	check = st_check_redirections(words);
	if (check)
		return (1);
	check = st_check_pipe(words);
	return (check);
}
