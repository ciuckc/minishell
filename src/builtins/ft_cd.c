/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/21 13:40:58 by emlicame         ###   ########.fr       */
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
	char		*dir;
	char		*oldcwd;
	char		*newcwd;
	t_env		variable;

	oldcwd = getcwd(0, 0);
	variable.name = malloc (sizeof (char *) * 7);
	variable.name = ft_strdup("OLDPWD");
	variable.value = malloc (sizeof (char *) * ft_strlen(oldcwd) + 1);
	variable.value = ft_strdup(oldcwd);
	dir = seeking_home(data);
	if (!data->cmd_args[1])
		data->cmd_args[1] = dir;
	if (chdir(data->cmd_args[1]) == -1)
	{
		not_a_directory(data);
		return (1);
	}
	// dprintf (2, "cwd %s\n", cwd);
	// insert_in_table("OLDPWD", cwd, &env_table);
	// dprintf (2, "cwd %s\n", cwd);
	newcwd = getcwd(0, 0);
	// if (item_search("PWD", env_table) != NULL)
	// remove_item("PWD", &env_table);
	insert_in_table("PWD", (char *)newcwd, &env_table);
	free (oldcwd);
	free (newcwd);
	free (dir);
	return (0);
}

	// if (item_search("OLDPWD", env_table != NULL))
	// 		remove_item("OLDPWD", &env_table);
	// insert_in_table("OLDPWD", cwd, &env_table);