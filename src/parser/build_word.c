/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 05:06:45 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/26 18:29:47 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_assign_type(t_token *word)
{
	u_int32_t	*types;

	types = (u_int32_t [128]){['|'] = PIPE, ['<'] = LESS, ['>'] = GREAT, ['&'] \
	= AND_IF, ['\''] = S_QUOTE, ['\"'] = D_QUOTE, ['\0'] = END};
	word->type = types[(u_int32_t) *(word->tok)];
	if (word->type == 0)
		word->type = WORD;
}

static void	st_get_word(t_scan_tok **scan_tok, t_token **word)
{
	t_tok_len	boundry;

	boundry = (t_tok_len){(*scan_tok)->boundry.start, (*scan_tok)->boundry.end};
	while ((*scan_tok)->orginal_str[boundry.end] && !ft_strchr(OPERATORS, \
	(*scan_tok)->orginal_str[boundry.end]) && !ft_strchr(IFS, \
	(*scan_tok)->orginal_str[boundry.end]))
	{
		(*scan_tok) = (*scan_tok)->next;
		boundry.end = (*scan_tok)->boundry.end;
	}
	(*word)->tok = ft_substr((*scan_tok)->orginal_str, boundry.start, \
	boundry.end - boundry.start);
	if ((*word)->tok == NULL)
		return ;
	st_assign_type(*word);
	(*scan_tok) = (*scan_tok)->next;
}

t_token	*build_word(t_scan_tok **scan_tok)
{
	t_token		*word;

	word = ft_calloc(1, sizeof(t_token));
	if (word == NULL)
		return (NULL);
	if (ft_strchr(OPERATORS, \
	(*scan_tok)->orginal_str[(*scan_tok)->boundry.start]))
	{
		word->tok = ft_substr((*scan_tok)->orginal_str, \
		(*scan_tok)->boundry.start, (*scan_tok)->boundry.end - \
		(*scan_tok)->boundry.start);
		if (word->tok == NULL)
			return (free(word), NULL);
		st_assign_type(word);
		(*scan_tok) = (*scan_tok)->next;
		return (word);
	}
	st_get_word(scan_tok, &word);
	return (word);
}
