/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:57:16 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/17 13:39:10 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	void	command_not_found(t_input *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit (127);
}

static int	if_path(t_input *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[0][i])
	{
		if (data->cmd_args[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	access_file(t_input *data)
{
	int		i;

	i = 0;
	if (access(data->cmd_args[0], X_OK) == 0)
	{
		if (if_path(data))
			data->cmd_path = ft_strdup(data->cmd_args[0]);
		else
			command_not_found(data);
		return (1);
	}
	while (data->paths[i])
	{
		if (if_path(data))
			command_not_found(data);
		data->cmd_path = ft_strjoin(data->paths[i], data->cmd_args[0]);
		if (!data->cmd_path)
			error_exit("Malloc failed", 1);
		if (access(data->cmd_path, X_OK) >= 0)
			return (1);
		i++;
	}
	if (access(data->cmd_path, X_OK) < 0)
		command_not_found(data);
	return (0);
}
