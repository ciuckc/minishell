/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 16:52:44 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/17 03:06:29 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	insert_replace_var(t_input *data, t_table *env_table, int pos)
{
	char		*value;
	u_int32_t	key_len;
	u_int32_t	data_len;

	value = NULL;
	key_len = mini_ft_strchr(data->cmd_args[pos], '=');
	data->expo_var.name = ft_substr(data->cmd_args[pos], 0, key_len);
	if (data->expo_var.name == NULL)
		return (free(data->expo_var.name), 1);
	if (item_search(data->expo_var.name, env_table) != NULL)
	{
		value = remove_item(data->expo_var.name, &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	data_len = ft_strlen(data->cmd_args[pos]) - key_len;
	data->expo_var.value = ft_substr(data->cmd_args[pos], key_len + 1, \
	data_len - 1);
	if (data->expo_var.value == NULL)
		return (free(data->expo_var.value), 1);
	insert_in_table(data->expo_var.name, data->expo_var.value, &env_table);
	return (0);
}

int32_t	ins_replace_var_no_eq(t_input *data, t_table *env_table, int pos)
{
	u_int32_t	key_len;
	t_container	*container;

	key_len = ft_strlen(data->cmd_args[pos]);
	data->expo_var.name = ft_substr(data->cmd_args[pos], 0, key_len);
	if (data->expo_var.name == NULL)
		return (free(data->expo_var.name), 1);
	container = item_search(data->expo_var.name, env_table);
	if (container != NULL)
	{
		free(data->expo_var.name);
		free(container->data);
		container->data = NULL;
	}
	else
		insert_in_table(data->expo_var.name, NULL, &env_table);
	return (0);
}

static void	st_join_str_data(t_table *env, char ***new_t, u_int32_t i, \
u_int32_t *j)
{
	char	*temp;

	temp = ft_strdup(env->table[i]->key_str);
	if (!temp)
	{
		ft_free_mem(new_t);
		return ;
	}
	if (env->table[i]->data == NULL)
		(*new_t)[*j] = ft_strdup(temp);
	else if (env->table[i]->data && ft_strlen(env->table[i]->data))
		(*new_t)[*j] = ft_strjoin_va(3, temp, "=", env->table[i]->data);
	else if (env->table[i]->data && !ft_strlen(env->table[i]->data))
		(*new_t)[*j] = ft_strjoin_va(3, temp, "=", "\"\"");
	free (temp);
	if ((*new_t)[*j] == NULL)
	{
		ft_free_mem(new_t);
		return ;
	}
	(*j)++;
}

char	**get_table(t_table *table, char **new_t, u_int32_t i, u_int32_t j)
{
	t_container	*head;

	head = table->table[i];
	while (i < table->containers)
	{
		head = table->table[i];
		while (table->table[i])
		{
			st_join_str_data(table, &new_t, i, &j);
			if (new_t == NULL)
				return (NULL);
			table->table[i] = table->table[i]->next;
		}
		table->table[i] = head;
		i++;
	}
	return (new_t);
}

char	**sort_table(t_table *table)
{
	u_int32_t	i;
	u_int32_t	j;
	char		**current_table;

	i = 0;
	j = 0;
	current_table = (char **)ft_calloc(sizeof(char *), (table->containers + 1));
	if (!current_table)
		return (error_print("Malloc failed"), NULL);
	current_table = get_table(table, current_table, 0, 0);
	if (!current_table)
		return (ft_free_mem(&current_table), NULL);
	while (i < table->entries - 1)
	{
		j = 0;
		while (j < table->entries - i - 1)
		{
			if (ft_strcmp(current_table[j], current_table[j + 1]) > 0)
				ft_str_swap(&current_table[j], &current_table[j + 1]);
			j++;
		}
		i++;
	}
	return (current_table);
}
