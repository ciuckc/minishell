/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/20 17:32:42 by emlicame      #+#    #+#                 */
/*   Updated: 2022/11/25 17:40:02 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	ft_unset(t_input *data, t_table *env_table)
{
	int		i;

	i = 1;
	if (!data->cmd_args[i])
		return (0);
	while (data->cmd_args[i])
	{
		remove_item(data->cmd_args[i], &env_table);
		i++;
	}
	return (0);
}
