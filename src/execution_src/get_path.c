/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:01:48 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/15 12:58:31 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*seeking_path(t_input *data)
{
	char	*get_path;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	get_path = "PATH=";
	while (data->environ[i])
	{
		if (ft_memcmp(get_path, data->environ[i], 5) == 0)
		{
			path = ft_strdup(data->environ[i] + 5);
			if (!path)
				exit(0);
		}
		i++;
	}
	return (path);
}

void	get_path(t_input *data)
{
	int		i;
	char	*my_path;

	i = -1;
	my_path = NULL;
	data->paths = NULL;
	my_path = seeking_path(data);
	if (!my_path)
	{
		data->paths = ft_split("", ' ');
		if (!data->paths)
			error_exit("Malloc failed", 1);
	}
	else
	{
		data->paths = ft_split(my_path, ':');
		free (my_path);
		if (!data->paths)
			error_exit("Malloc failed", 1);
		while (data->paths[++i])
			data->paths[i] = ft_strjoin(data->paths[i], "/");
	}
}
