/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 05:12:52 by scristia          #+#    #+#             */
/*   Updated: 2022/11/17 17:32:25 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_container	*st_get_container(t_table *table)
{
	static t_container	*saved_container;
	static u_int32_t	index;

	while (index < table->containers)
	{
		while (table->table[index])
		{
			saved_container = table->table[index];
			table->table[index] = table->table[index]->next;
			return (saved_container);
		}
		index++;
	}
	return (saved_container);
}

static char	*st_build_str(t_table *table)
{
	char		*new_str;
	t_container	*next_container;
	t_env		var;

	next_container = st_get_container(table);
	if (next_container == NULL)
		return (NULL);
	var.name = next_container->key_str;
	var.value = next_container->data;
	new_str = ft_calloc(ft_strlen(var.name) + sizeof('=') + \
	ft_strlen(var.value) + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, var.name, ft_strlen(var.name));
	ft_memmove(new_str + ft_strlen(var.name), "=", 1);
	ft_memmove(new_str + ft_strlen(var.name) + 1, var.value, \
	ft_strlen(var.value));
	return (new_str);
}

static void	st_create_strings(char **new, t_table *table)
{
	u_int32_t	i;

	i = 0;
	while (i < table->entries - 1)
	{
		new[i] = st_build_str(table);
		if (new[i] == NULL)
			free_new_envp(&new, i);
		i++;
	}
}

void	create_new_envp(t_table *table, char ***envp)
{
	char	**new_envp;

	new_envp = ft_calloc(table->entries + 1, sizeof(char *));
	if (new_envp == NULL)
		return ;
	st_create_strings(new_envp, table);
	*envp = new_envp;
}
