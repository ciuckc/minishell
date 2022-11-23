/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/22 14:30:21 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static void	st_new_pwd(t_input *data, t_table *env_table, char *new_cwd)
{
	char	*value;

	value = NULL;
	if (item_search("PWD", env_table) != NULL)
	{
		value = remove_item("PWD", &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	data->new_var.name = malloc(sizeof(char *) * 4);
	data->new_var.name = ft_strdup("PWD");
	data->new_var.value = malloc (sizeof (char *) * ft_strlen(new_cwd) + 1);
	data->new_var.value = ft_strdup(new_cwd);
	insert_in_table(data->new_var.name, data->new_var.value, &env_table);
	// free (data->new_var.name);
	// data->new_var.name = NULL;
	// free (data->new_var.value);
	// data->new_var.value = NULL;
}

static void	st_old_pwd(t_input *data, t_table *env_table, char *old_cwd)
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
	data->old_var.name = malloc(sizeof(char *) * 7);
	data->old_var.name = ft_strdup("OLDPWD");
	data->old_var.value = malloc (sizeof (char *) * ft_strlen(old_cwd) + 1);
	data->old_var.value = ft_strdup(old_cwd);
	insert_in_table(data->old_var.name, data->old_var.value, &env_table);
	// free (data->old_var.name);
	// data->old_var.name = NULL;
	// free (data->old_var.value);
	// data->old_var.value = NULL;
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
				error_exit("Malloc failed", 1);
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
		st_not_a_directory(data);
		return (1);
	}
	free (dir);
	st_old_pwd(data, env_table, old_cwd);
	free (old_cwd);
	new_cwd = getcwd(0, 0);
	st_new_pwd(data, env_table, new_cwd);
	free (new_cwd);
	return (0);
}

	