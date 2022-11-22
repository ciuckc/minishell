/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/20 17:32:42 by emlicame      #+#    #+#                 */
/*   Updated: 2022/11/21 19:39:51 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	ft_unset(t_input *data, t_table *env_table)
{
	int		i;
	char	*temp;
	void	*value;

	i = 1;
	temp = NULL;
	value = NULL;
	if (!data->cmd_args[i])
		return (0);
	dprintf (2, "cmd arg %s\n", data->cmd_args[1]);
	while (data->cmd_args[i])
	{
		value = remove_item(data->cmd_args[i], &env_table);
		if (value != NULL)
			free(value);
		value = NULL;
		i++;
	}
	return (0);
}
