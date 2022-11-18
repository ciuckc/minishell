/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/18 19:43:42 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static int	not_a_directory(t_input *data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(data->cmd_args[1], 2);
	perror (" ");
	return (1);
}

char	*seeking_home(t_input *data)
{
	char	*get_path;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	get_path = "HOME=";
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

int	ft_cd(t_input *data)
{
	char	*path;

	path = seeking_home(data);
	if (!data->cmd_args[1])
		data->cmd_args[1] = path;
	if (chdir(data->cmd_args[1]) == -1)
	{
		not_a_directory(data);
		return (1);
	}
	//set environ PWD variable(cwd)
	free (path);
	return (0);
}
