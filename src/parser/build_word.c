/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 05:06:45 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/08 01:20:40 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_assign_type(t_token *word)
{
	u_int32_t	*types;

	types = (u_int32_t [128]){['|'] = PIPE, ['<'] = LESS, ['>'] = GREAT, ['&'] \
	= AMP, ['\''] = S_QUOTE, ['\"'] = D_QUOTE, ['\0'] = END, ['$'] = DOLLAR};
	word->type = types[(u_int32_t) *(word->str)];
	if ((word->type == PIPE || word->type == LESS || word->type == GREAT || \
	word->type == AMP) && (types[(u_int32_t) *(word->str + 1)] == \
	word->type))
		word->type <<= 1;
	if (word->type == 0)
		word->type = WORD;
	if ((word->type == WORD || word->type == DOLLAR) && *(word->str) != '=' && \
	ft_strchr(word->str, '='))
		word->type = ASSIGNMENT_WORD;
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
	(*word)->str = ft_substr((*scan_tok)->orginal_str, boundry.start, \
	boundry.end - boundry.start);
	if ((*word)->str == NULL)
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
		word->str = ft_substr((*scan_tok)->orginal_str, \
		(*scan_tok)->boundry.start, (*scan_tok)->boundry.end - \
		(*scan_tok)->boundry.start);
		if (word->str == NULL)
			return (free(word), NULL);
		st_assign_type(word);
		(*scan_tok) = (*scan_tok)->next;
		return (word);
	}
	st_get_word(scan_tok, &word);
	return (word);
}
