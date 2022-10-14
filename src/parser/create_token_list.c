/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/14 12:08:54 by scristia      ########   odam.nl         */
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
	if (*full_cmd == '\0')
		return (NULL);
	len = 0;
	ft_putendl_fd(full_cmd, 1);
	while (*full_cmd)
	{
		if (*full_cmd == '\'')
			ft_len_to_char_set(full_cmd, "'");
		else if (*full_cmd == '"')
			ft_len_to_char_set(full_cmd, "\"");
		else
			ft_len_to_char_set(full_cmd, TOKENS);
		full_cmd += len;
		st_skip_spaces(&full_cmd);
		ft_putendl_fd(full_cmd, 1);
	}
	return (NULL);
}
