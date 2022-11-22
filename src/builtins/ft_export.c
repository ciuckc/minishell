/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:25:33 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/22 17:27:32 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static void	st_print_table(t_table *table)
{
	u_int32_t		i;

	i = 0;
	while (i < table->containers)
	{
		while (table->table[i])
		{
			dprintf (2, "key_str %s ", table->table[i]->key_str);
			dprintf (2, "data %s\n", table->table[i]->data);
			table->table[i] = table->table[i]->next;
		}
		i++;
	}
	dprintf (2, "index %d\n", i);
}

int32_t	ft_export(t_input *data, t_table *env_table)
{
	int32_t		i;

	i = 0;
	(void)env_table;
	if (!data->cmd_args[1])
		st_print_table(env_table);
	return (0);
}

//declare -x Apple_PubSub_Socket...
	// int32_t	i;

	// i = 0;
	// while (data->environ[i])
	// {
	// 	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	// 	ft_putstr_fd(data->environ[i], STDOUT_FILENO);
	// 	ft_putchar_fd('\n', STDOUT_FILENO);
	// 	i++;
	// }