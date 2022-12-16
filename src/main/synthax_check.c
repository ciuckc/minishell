/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   synthax_check.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 16:54:08 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 06:19:57 by scristia      ########   odam.nl         */
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
				return (ft_putendl_fd("minishell: sythax error near unexpected \
token `newline\'", 2), 258);
			if (words->str == NULL)
				return (ft_putendl_fd("minishell: ambiguos redirect", 2), 1);
			if (words->type != WORD && words->type != DOLLAR && words->type != \
			ASSIGNMENT_WORD)
				return (ft_putstr_fd("minishell: synthax error near unexpected \
token `", 2), ft_putstr_fd(words->str, 2), ft_putendl_fd("'", 2), 258);
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
			return (ft_putendl_fd("minishell: synthax error near unexpected \
token \"|\"", 2), 258);
		had_words = false;
		words = words->next;
		if (words == NULL)
			return (ft_putendl_fd("minishell: synthax error near unexpected \
token `|\'", 2), 258);
	}
	return (0);
}

int32_t	synthax_check(t_token *words)
{
	int32_t	check;

	check = st_check_redirections(words);
	if (check)
	{
		g_exit_code = check;
		return (check);
	}
	check = st_check_pipe(words);
	g_exit_code = check;
	return (check);
}
