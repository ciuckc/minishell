/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:32:42 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/21 15:51:00 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	ft_unset(t_input *data, t_table *env_table)
{
	int		i;
	char	*temp;

	i = 1;
	temp = NULL;
	if (!data->cmd_args[i])
		return (0);
	dprintf (2, "cmd arg %s\n", data->cmd_args[1]);
	dprintf (2, "cmd arg %s\n", data->cmd_args[2]);
	while (data->cmd_args[i])
	{
		temp = ft_strdup(data->cmd_args[i]);
		if (item_search(temp, env_table) != NULL)
		{
			dprintf (2, "unset %p\n", data->cmd_args[i]);
			dprintf (2, "unset %s\n", data->cmd_args[i]);
			free (remove_item(data->cmd_args[i], &env_table));
		}
		i++;
	}
	return (0);
}
