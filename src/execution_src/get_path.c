/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:01:48 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/15 22:17:11 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*st_seeking_path(t_input *data)
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
				error_exit("Malloc failed", 1);
		}
		i++;
	}
	return (path);
}

static void	st_complete_path(t_input *data)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (data->paths[++i])
	{
		temp = data->paths[i];
		data->paths[i] = ft_strjoin(data->paths[i], "/");
		if (!data->paths[i])
			error_exit("Malloc failed", 1);
		free (temp);
	}		
}

void	get_path(t_input *data)
{
	char	*my_path;

	my_path = NULL;
	data->paths = NULL;
	my_path = st_seeking_path(data);
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
		st_complete_path(data);
	}
}
