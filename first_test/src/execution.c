/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:45:47 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/25 11:50:47 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	execution(t_token *tok, t_input *data)
{
	(void)tok;
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
}
