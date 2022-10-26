/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   retrieve_tok_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/25 23:12:16 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*retrieve_tok_list(char *full_cmd)
{
	t_scan_tok	*scan_tok;
	t_token		*word;

	scan_tok = tok_len_scan_list(&full_cmd);
	if (scan_tok == NULL)
		return (NULL);
	while (scan_tok)
	{
		word = build_word(&scan_tok);
		printf("%s\n", word->tok);
	}
	return (NULL);
}
