/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_new_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 05:12:52 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/21 18:09:53 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_container	*st_get_container(t_table *env, bool reset_static)
{
	static t_container	*last_cont;
	t_container			*return_cont;
	static u_int32_t	i;

	return_cont = NULL;
	if (reset_static)
	{
		last_cont = NULL;
		i = 0;
		return (NULL);
	}
	while (i < env->containers)
	{
		if (last_cont == NULL)
			last_cont = env->table[i];
		while (last_cont)
		{
			return_cont = last_cont;
			last_cont = last_cont->next;
			if (last_cont == NULL)
				i++;
			return (return_cont);
		}
		i++;
	}
	return (return_cont);
}

static char	*st_build_str(t_table *table)
{
	char		*new_str;
	t_container	*next_container;
	t_env		var;

	next_container = st_get_container(table, false);
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
	while (i < table->entries)
	{
		new[i] = st_build_str(table);
		if (new[i] == NULL)
		{
			free_new_envp(&new, i);
			return ;
		}
		i++;
	}
	st_get_container(NULL, true);
}

void	create_new_envp(t_table *table, char ***envp)
{
	char	**new_envp;

	new_envp = ft_calloc(table->entries + 1, sizeof(char *));
	if (new_envp == NULL)
		return ;
	printf("%u\n", table->entries);
	st_create_strings(new_envp, table);
	*envp = new_envp;
}
