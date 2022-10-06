/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token_list.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:19 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/06 18:49:35 by scristia      ########   odam.nl         */
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
	st_skip_spaces(&full_cmd);
	while (*full_cmd)
	{
		full_cmd++;
	}
	return (NULL);
}
