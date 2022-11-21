/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/21 18:11:06 by emlicame         ###   ########.fr       */
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
	char		*new_cwd;
	char		*old_cwd;
	t_env		old_var;
	t_env		new_var;

	new_cwd = NULL;
	old_cwd = getcwd(0, 0);
	dir = seeking_home(data);
	if (!data->cmd_args[1])
		data->cmd_args[1] = dir;
	if (chdir(data->cmd_args[1]) == -1)
	{
		free (new_cwd);
		free (old_cwd);
		free (dir);
		not_a_directory(data);
		return (1);
	}
	old_var.name = malloc(sizeof(char *) * 7);
	old_var.name = ft_strdup("OLDPWD");
	old_var.value = malloc (sizeof (char *) * ft_strlen(old_cwd) + 1);
	old_var.value = ft_strdup(old_cwd);
	insert_in_table(old_var.name, old_var.value, &env_table);
	free (old_cwd);
	new_cwd = getcwd(0, 0);
	new_var.name = malloc(sizeof(char *) * 4);
	new_var.name = ft_strdup("PWD");
	new_var.value = malloc (sizeof (char *) * ft_strlen(new_cwd) + 1);
	new_var.value = ft_strdup(new_cwd);
	insert_in_table(new_var.name, new_var.value, &env_table);
	free (new_cwd);
	free (dir);
	return (0);
}
