/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:52:44 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/23 18:14:41 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 == *s2) && *s1)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *) s1 - *(unsigned char *) s2);
}

void	replace_var(char *var, t_input *data, t_table *env_table)
{
	char	*value;

	value = NULL;
	printf ("var %s\n", var);
	return ;
	if (item_search("OLDPWD", env_table) != NULL)
	{
		value = remove_item("OLDPWD", &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
	}
	data->old_var.name = malloc(sizeof(char *) * 7);
	data->old_var.name = ft_strdup("OLDPWD");
	data->old_var.value = malloc (sizeof (char *) * ft_strlen(var) + 1);
	data->old_var.value = ft_strdup(var);
	insert_in_table(data->old_var.name, data->old_var.value, &env_table);
}

char	**make_table(t_table *table)
{
	u_int32_t	i;
	u_int32_t	j;
	t_container	*head;
	char		**current_table;
	char		*swap;

	i = 0;
	j = 0;
	current_table = (char **)malloc(sizeof(char *) * (table->containers + 1));
	if (!current_table)
		error_exit("Malloc failed", 1);
	head = table->table[0];
	while (i < table->containers)
	{
		head = table->table[i];
		while (table->table[i])
		{
			current_table[j] = ft_strdup(table->table[i]->key_str);
			current_table[j] = ft_strjoin(current_table[j], "=");
			current_table[j] = ft_strjoin(current_table[j], \
			table->table[i]->data);
			j++;
			table->table[i] = table->table[i]->next;
		}
		table->table[i] = head;
		i++;
	}
	current_table[j] = NULL;
	i = 1;
	j = 0;
	swap = NULL;
	while (i < table->entries - 1)
	{
		j = 0;
		while (j < table->entries - i - 1)
		{
			if (ft_strcmp(current_table[j], current_table[j + 1]) > 0)
			{
				swap = current_table[j];
				current_table[j] = current_table[j + 1];
				current_table[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
	return (current_table);
}
