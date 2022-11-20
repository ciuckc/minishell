/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 03:58:47 by scristia          #+#    #+#             */
/*   Updated: 2022/11/20 17:34:26 by emlicame         ###   ########.fr       */
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

int32_t	ft_echo(char **arg)
{
	int		i;
	int		is_n;

	i = 1;
	is_n = 0;
	if (!arg[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	while (arg[i] && is_flag_n(arg[i]))
		i++;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (arg[1] && is_flag_n(arg[1]) == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
