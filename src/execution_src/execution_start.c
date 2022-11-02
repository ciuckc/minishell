/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:32:34 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/02 19:49:10 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//function that counts cmds;
//cmd_count = ft_lstsize(commands);
void	execution_start(t_token *tok, t_input *data)
{
	int		exit_code;

	exit_code = 0;
	if (data->cmd_count == 1)
		exit_code = single_command(tok, data);//change get_files!
	else
		exit_code = multiple_commands(tok, data);
	(void)exit_code;
}
