/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/02 19:23:45 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static void	st_new_pwd(t_input *data, t_table *env_table, char *new_cwd)
{
	char	*value;

	value = NULL;
	if (!new_cwd)
		return ;
	if (item_search("PWD", env_table) != NULL)
	{
		value = remove_item("PWD", &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	data->new_var.name = ft_strdup("PWD");
	data->new_var.value = malloc (sizeof (char *) * ft_strlen(new_cwd) + 1);
	data->new_var.value = ft_strdup(new_cwd);
	insert_in_table(data->new_var.name, data->new_var.value, &env_table);
	// free (data->new_var.name);
	// data->new_var.name = NULL;
	// free (data->new_var.value);
	// data->new_var.value = NULL;
}

static int32_t	st_old_pwd(t_input *data, t_table *env_table, char *old_cwd)
{
	char	*value;

	value = NULL;
	if (item_search("OLDPWD", env_table) != NULL)
	{
		value = remove_item("OLDPWD", &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	if (!old_cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		return (1) ;
	}
	data->old_var.name = ft_strdup("OLDPWD");
	data->old_var.value = ft_strdup(old_cwd);
	insert_in_table(data->old_var.name, data->old_var.value, &env_table);
	return (0);
}

static int32_t	st_not_a_directory(t_input *data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(data->cmd_args[1], 2);
	perror (" ");
	return (1);
}

static char	*st_seeking_home(t_input *data)
{
	char	*get_path;
	char	*path;
	int32_t	i;

	i = 0;
	path = NULL;
	get_path = "HOME=";
	while (data->environ[i])
	{
		if (ft_memcmp(get_path, data->environ[i], 5) == 0)
		{
			path = ft_strdup(data->environ[i] + 5);
			if (!path)
				error_exit("Malloc failed", EXIT_FAILURE);
		}
		i++;
	}
	return (path);
}

int32_t	ft_cd(t_input *data, t_table *env_table)
{
	char		*dir;
	char		*new_cwd;
	char		*old_cwd;

	new_cwd = NULL;
	old_cwd = getcwd(0, 0);
	dir = st_seeking_home(data);
	if (!data->cmd_args[1])
		data->cmd_args[1] = dir;
	if (chdir(data->cmd_args[1]) == -1)
	{
		free (new_cwd);
		free (old_cwd);
		free (dir);
		dir = NULL;
		return (st_not_a_directory(data));
	}
	free (dir);
	st_old_pwd(data, env_table, old_cwd);
	free (old_cwd);
	new_cwd = getcwd(0, 0);
	if (!new_cwd)
		return (0);
		// ft_putendl_fd("No such file or directory", 2);;
	st_new_pwd(data, env_table, new_cwd);
	free (new_cwd);
	return (0);
}

	