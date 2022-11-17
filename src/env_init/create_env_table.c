/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env_table.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 05:38:11 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/14 18:27:31 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_free_all(t_env *env_data, u_int32_t len)
{
	u_int32_t	i;

	i = 0;
	while (i < len)
	{
		if (env_data[i].name)
			free(env_data[i].name);
		if (env_data[i].value)
			free(env_data[i].value);
		i++;
	}
}

static void	st_assign_env_vars(char **envp, t_env **env_data, u_int32_t n)
{
	char		**var;
	u_int32_t	i;

	i = 0;
	while (i < n)
	{
		var = ft_split(envp[i], '=');
		if (var == NULL)
		{
			st_free_all(*env_data, i);
			free(*env_data);
			return ;
		}
		(*env_data)[i].name = var[0];
		(*env_data)[i].value = var[1];
		free(var);
		i++;
	}
}

static void	st_add_env_var_to_table(t_table **table, t_env *data, u_int32_t len)
{
	u_int32_t	i;
	t_container	*added_item;

	i = 0;
	while (i < len)
	{
		added_item = insert_in_table(data[i].name, data[i].value, table);
		if (added_item == NULL)
		{
			remove_all(*table);
			*table = NULL;
			st_free_all(data, len);
			free(data);
			return ;
		}
		i++;
	}
}

static void	st_remove_old_pwd(t_table *table, t_env *data, u_int32_t n)
{
	t_container	*item;
	u_int32_t	i;

	i = 0;
	item = item_search("OLDPWD", table);
	if (item == NULL)
		return ;
	while (i < n)
	{
		if (data[i].name == item->key_str)
			return (free(remove_item(data[i].name, &table)), \
			free(data[i].name));
		i++;
	}
}

t_table	*create_env_table(char **envp)
{
	t_env		*env_data;
	t_table		*env_table;
	u_int32_t	n_vars;

	n_vars = 0;
	while (envp[n_vars])
		n_vars++;
	env_data = ft_calloc(n_vars, sizeof(t_env));
	if (env_data == NULL)
		return (NULL);
	st_assign_env_vars(envp, &env_data, n_vars);
	env_table = init_table(HASH_TABLE_512);
	if (env_table == NULL)
	{
		st_free_all(env_data, n_vars);
		free(env_data);
		return (NULL);
	}
	st_add_env_var_to_table(&env_table, env_data, n_vars);
	st_remove_old_pwd(env_table, env_data, n_vars);
	free(env_data);
	return (env_table);
}
