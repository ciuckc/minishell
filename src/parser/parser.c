/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:42:44 by scristia          #+#    #+#             */
/*   Updated: 2022/10/11 15:19:09 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser(char *full_cmd, char **envp)
{
	// t_list	*tokens;

	(void)envp;
	if (*full_cmd == '\0')
		return ;
	// tokens = create_token_list(full_cmd);
}
