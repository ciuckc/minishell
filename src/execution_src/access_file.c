/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:57:16 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/13 18:46:34 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	access_file(t_input *data)
{
	int		i;

	i = 0;
	if (access(data->cmd_args[0], X_OK) == 0)
	{
		data->cmd_path = ft_strdup(data->cmd_args[0]);
		return (1);
	}
	while (data->paths[i])
	{
		data->cmd_path = ft_strjoin(data->paths[i], \
							data->cmd_args[0]);
		if (!data->cmd_path)
			error_exit("Malloc failed", 1);
		if (access(data->cmd_path, X_OK) >= 0)
			return (1);
		i++;
	}
	if (access(data->cmd_path, X_OK) < 0)
		error_exit(data->cmd_args[0], errno);
	return (0);
}
