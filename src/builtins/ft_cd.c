/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/17 01:12:46 by emlicame         ###   ########.fr       */
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
	if (data->new_var.name == NULL)
		return ;
	data->new_var.value = ft_strdup(new_cwd);
	if (data->new_var.value == NULL)
		return (free(data->new_var.value));
	insert_in_table(data->new_var.name, data->new_var.value, &env_table);
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
		return (1);
	}
	data->old_var.name = ft_strdup("OLDPWD");
	if (!data->old_var.name)
		return (1);
	data->old_var.value = ft_strdup(old_cwd);
	if (!data->old_var.value)
		return (free(data->old_var.name), 1);
	insert_in_table(data->old_var.name, data->old_var.value, &env_table);
	return (0);
}

static int32_t	st_not_a_directory(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
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
			if (data->environ[i][5] == '\0')
				path = ft_strdup(data->environ[i]);
			else
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
	char		*new_cwd;
	char		*old_cwd;

	new_cwd = NULL;
	old_cwd = getcwd(0, 0);
	if (!data->cmd_args[1])
	{
		data->d = st_seeking_home(data);
		if (!data->d)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
		else if (data->d == NULL && ft_strcmp (data->d, "HOME=") == 0)
			return (0);
		if (chdir(data->d) == -1)
			return (st_not_a_directory(data->d), free(old_cwd), \
			free(data->d), 1);
		return (0);
	}
	if (chdir(data->cmd_args[1]) == -1)
		return (st_not_a_directory(data->d), free (old_cwd), free(data->d), 1);
	st_old_pwd(data, env_table, old_cwd);
	new_cwd = getcwd(0, 0);
	if (!new_cwd)
		return (0);
	st_new_pwd(data, env_table, new_cwd);
	return (free(data->d), free(new_cwd), free(old_cwd), 0);
}
