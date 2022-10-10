/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/07 21:15:54 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_skip_spaces(char **cmd)
{
	while (**cmd != '\0' && ft_isspace(**cmd))
		(*cmd)++;
}

t_list	*create_token_list(char *full_cmd)
{
	size_t	len;

	st_skip_spaces(&full_cmd);
	len = 0;
	while (*full_cmd)
	{
		len = ft_len_to_char_set(full_cmd, TOKENS);
		full_cmd++;
	}
	return (NULL);
}
