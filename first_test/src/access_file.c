/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:57:16 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/25 11:51:51 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	access_file(t_input **data)
{
	int		i;
	t_input	*data_cmd;

	i = 0;
	data_cmd = *data;
	if (access(data_cmd->cmd_args[0], X_OK) == 0)
	{
		data_cmd->cmd_path = ft_strdup(data_cmd->cmd_args[0]);
		return (1);
	}
	while (data_cmd->paths[i])
	{
		data_cmd->cmd_path = ft_strjoin_withfree(data_cmd->paths[i], \
							data_cmd->cmd_args[0]);
		if (!data_cmd->cmd_path)
			error_exit("Malloc failed", 1);
		if (access(data_cmd->cmd_path, X_OK) >= 0)
			return (1);
		i++;
	}
	if (access(data_cmd->cmd_path, X_OK) < 0)
		error_exit(data_cmd->cmd_args[0], errno);
	return (0);
}
