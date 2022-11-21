/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/20 18:45:41 by emlicame         ###   ########.fr       */
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
				error_exit("Malloc failed", 1);
		}
		i++;
	}
	return (path);
}

int32_t	ft_cd(t_input *data, t_table *env_table)
{
	char		*newpath;
	char		*cwd;

	(void)env_table;
	cwd = getcwd(0, 0);
	newpath = seeking_home(data);
	if (!data->cmd_args[1])
		data->cmd_args[1] = newpath;
	if (chdir(data->cmd_args[1]) == -1)
	{
		not_a_directory(data);
		return (1);
	}
	// dprintf (2, "cwd %s\n", cwd);
	// insert_in_table("OLDPWD", cwd, &env_table);
	// dprintf (2, "cwd %s\n", cwd);
	cwd = getcwd(0, 0);
	// remove_item("PWD", &env_table);
	dprintf(2, "cwd %s\n", cwd);
	// insert_in_table("PWD", (char *)cwd, &env_table);
	free (cwd);
	free (newpath);
	return (0);
}

	// if (item_search("OLDPWD", env_table != NULL))
	// 		remove_item("OLDPWD", &env_table);
	// insert_in_table("OLDPWD", cwd, &env_table);