/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:34:40 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/17 00:52:04 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static int	st_seeking_pwd(t_input *data)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (data->environ[i])
	{
		if (ft_memcmp("PWD", data->environ[i], 3) == 0)
		{
			pwd = ft_strdup(data->environ[i] + 4);
			if (!pwd)
				error_exit("Malloc failed", 1);
		}
		i++;
	}
	if (!pwd)
		return (ft_putendl_fd("minishell: pwd not found", 2), 1);
	else
		ft_putendl_fd(pwd, 2);
	free (pwd);
	return (0);
}

int32_t	ft_pwd(t_input *data)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free (cwd);
	}
	else
	{
		if (st_seeking_pwd(data))
			ft_putendl_fd("minishell: pwd not found", 2);
		return (1);
	}
	return (0);
}
