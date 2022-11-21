/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 03:58:47 by scristia          #+#    #+#             */
/*   Updated: 2022/11/21 15:18:31 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	is_flag_n(char *str)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] == 'n')
				nl = 1;
			else
				nl = 0;
			i++;
		}
	}
	return (nl);
}

int32_t	ft_echo(t_input *data)
{
	int		i;

	i = 1;
	if (!data->cmd_args[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	while (data->cmd_args[i] && is_flag_n(data->cmd_args[i]))
		i++;
	while (data->cmd_args[i])
	{
		ft_putstr_fd(data->cmd_args[i], STDOUT_FILENO);
		if (data->cmd_args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (data->cmd_args[1] && is_flag_n(data->cmd_args[1]) == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
