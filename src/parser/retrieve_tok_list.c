/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   retrieve_tok_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/21 03:50:08 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*retrieve_tok_list(char *full_cmd)
{
	t_scan_tok	*scan_tok;

	scan_tok = tok_len_scan_list(&full_cmd);
	if (scan_tok == NULL)
		return (NULL);
	while (scan_tok != NULL)
	{
		printf("%s\n", ft_substr(scan_tok->orginal_str, scan_tok->boundry.start, \
		scan_tok->boundry.end - scan_tok->boundry.start));
		scan_tok = scan_tok->next;
	}
	return (NULL);
}
