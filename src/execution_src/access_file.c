/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access_file.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:57:16 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 05:23:47 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void	err_is_directory(t_input *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(data->cmd_path, STDERR_FILENO);
	ft_putendl_fd(": is a directory", STDERR_FILENO);
	exit (126);
}

static int32_t	if_path(t_input *data)
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

static int32_t	no_path(t_input *data)
{
	if (access(data->cmd_args[0], X_OK) == 0)
	{
		if (if_path(data))
		{
			data->cmd_path = ft_strdup(data->cmd_args[0]);
			if (!data->cmd_path)
				error_exit("Malloc failed", 1);
		}
		else
			command_not_found(data);
		return (1);
	}
	return (0);
}

static void	error_if_no_access(t_input *data)
{
	if (access(data->cmd_args[0], F_OK) < 0)
		no_such_file(data);
	else
		permission_denied(data);
}

void	access_file(t_input *data)
{
	int		i;

	i = 0;
	if (no_path(data))
		return ;
	while (data->paths[i])
	{
		if (if_path(data))
			error_if_no_access(data);
		if (data->cmd_path)
		{
			free(data->cmd_path);
			data->cmd_path = NULL;
		}
		data->cmd_path = ft_strjoin(data->paths[i], data->cmd_args[0]);
		if (!data->cmd_path)
			error_exit("Malloc failed", 1);
		if (access(data->cmd_path, X_OK) >= 0)
			return ;
		i++;
	}
}
