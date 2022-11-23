/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 05:12:52 by scristia          #+#    #+#             */
/*   Updated: 2022/11/23 18:06:19 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_container	*st_get_container(t_table *env, u_int32_t *i, t_container \
**save)
{
	t_container			*return_cont;

	return_cont = NULL;
	while (*i < env->containers)
	{
		if (*save == NULL)
			*save = env->table[*i];
		while (*save)
		{
			while ((*save)->data == NULL && (*save)->next != NULL)
				*save = (*save)->next;
			if (!(*save)->data)
			{
				(*save) = NULL;
				break ;
			}
			return_cont = *save;
			*save = (*save)->next;
			if (*save == NULL)
				(*i)++;
			return (return_cont);
		}
		(*i)++;
	}
	return (return_cont);
}

static char	*st_build_str(t_table *table, u_int32_t *table_index, \
t_container **save)
{
	char		*new_str;
	t_container	*next_container;
	t_env		var;

	next_container = st_get_container(table, table_index, save);
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

static void	st_create_strings(char **new, t_table *table, u_int32_t len)
{
	u_int32_t	i;
	u_int32_t	table_index;
	t_container	*saved_container;

	i = 0;
	table_index = 0;
	saved_container = NULL;
	while (i < len)
	{
		new[i] = st_build_str(table, &table_index, &saved_container);
		if (new[i] == NULL)
		{
			free_new_envp(&new, i);
			return ;
		}
		i++;
	}
}

static u_int32_t	st_get_envp_len(t_table *table)
{
	u_int32_t	i;
	u_int32_t	len;
	t_container	*head;

	len = 0;
	i = 0;
	while (i < table->containers)
	{
		head = table->table[i];
		while (table->table[i])
		{
			if (table->table[i]->data)
				len++;
			table->table[i] = table->table[i]->next;
		}
		table->table[i] = head;
		i++;
	}
	return (len);
}

void	create_new_envp(t_table *table, char ***envp)
{
	char		**new_envp;
	u_int32_t	envp_len;

	envp_len = st_get_envp_len(table);
	new_envp = ft_calloc(envp_len + 1, sizeof(char *));
	if (new_envp == NULL)
		return ;
	st_create_strings(new_envp, table, envp_len);
	*envp = new_envp;
}
