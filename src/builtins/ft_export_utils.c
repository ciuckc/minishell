/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:52:44 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/23 21:17:27 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	st_ft_strchr(const char *s, int c)
{
	char	*string;
	int		len;

	len = 0;
	string = (char *)s;
	while (*string != c)
	{
		if (*string == '\0')
			return (0);
		string++;
		len++;
	}
	return (len);
}

void	replace_var(t_input *data, t_table *env_table, int pos)
{
	char		*value;
	u_int32_t	key_len;
	u_int32_t	data_len;

	(void)env_table;
	value = NULL;
	key_len = st_ft_strchr(data->cmd_args[pos], '=');
	data->expo_var.name = malloc(sizeof(char *) * key_len + 1);
	data->expo_var.name = ft_substr(data->cmd_args[pos], 0, key_len);
	printf ("key %s\n", data->expo_var.name);
	if (item_search(data->expo_var.name, env_table) != NULL)
	{
		value = remove_item(data->expo_var.name, &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	data_len = ft_strlen(data->cmd_args[pos]) - key_len;
	data->expo_var.value = malloc(sizeof(char *) * data_len);
	data->expo_var.value = ft_substr(data->cmd_args[pos], key_len + 1, \
	data_len - 1);
	printf ("data->expo_var.value %s\n", data->expo_var.value);
	insert_in_table(data->expo_var.name, data->expo_var.value, &env_table);
}

char	**get_table(t_table *table, char **new_table)
{
	u_int32_t	i;
	u_int32_t	j;
	t_container	*head;

	i = 0;
	j = 0;
	head = table->table[0];
	while (i < table->containers)
	{
		head = table->table[i];
		while (table->table[i])
		{
			new_table[j] = ft_strdup(table->table[i]->key_str);
			new_table[j] = ft_strjoin(new_table[j], "=");
			new_table[j] = ft_strjoin(new_table[j], \
			table->table[i]->data);
			j++;
			table->table[i] = table->table[i]->next;
		}
		table->table[i] = head;
		i++;
	}
	new_table[j] = NULL;
	return (new_table);
}

static void	st_swap(char **str_j, char **str_j1)
{
	char		*swap;

	swap = NULL;
	swap = *str_j;
	*str_j = *str_j1;
	*str_j1 = swap;
}

char	**make_table(t_table *table)
{
	u_int32_t	i;
	u_int32_t	j;
	char		*swap;
	char		**current_table;

	i = 0;
	j = 0;
	current_table = (char **)malloc(sizeof(char *) * (table->containers + 1));
	if (!current_table)
		error_exit("Malloc failed", 1);
	current_table = get_table(table, current_table);
	swap = NULL;
	while (i < table->entries - 1)
	{
		j = 0;
		while (j < table->entries - i - 1)
		{
			if (ft_strcmp(current_table[j], current_table[j + 1]) > 0)
				st_swap(&current_table[j], &current_table[j + 1]);
			j++;
		}
		i++;
	}
	return (current_table);
}
