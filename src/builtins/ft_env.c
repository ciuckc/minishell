/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 19:00:11 by emlicame      #+#    #+#                 */
/*   Updated: 2022/11/24 11:50:02 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	ft_env(t_input *data)
{
	int	i;

	i = 0;
	while (data->environ[i])
	{
		if (mini_ft_strchr(data->environ[i], '='))
			ft_putstr_fd(data->environ[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
