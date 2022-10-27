/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:01:48 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/24 14:48:27 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*seeking_path(t_envi *envi)
{
	char	*get_path;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	get_path = "PATH=";
	while (envi != NULL)
	{
		if (ft_memcmp(get_path, envi->envectors, 5) == 0)
		{
			path = ft_strdup(envi->envectors + 5);
			if (!path)
				exit(0);
		}
		envi = envi->next;
	}
	return (path);
}

void	get_path(t_envi *envi, t_input *data)
{
	int		i;
	char	**split_path;
	char	*my_path;

	i = -1;
	my_path = NULL;
	split_path = NULL;
	my_path = seeking_path(envi);
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
			data->paths[i] = ft_strjoin_withfree(data->paths[i], "/");
	}
}
