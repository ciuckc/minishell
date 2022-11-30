/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:30:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/30 18:45:58 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"
#include <limits.h>

static void	st_check_if_valid(char **arg)
{
	int	i;

	i = 0;
	if (arg[1][0] == '-' || arg[1][0] == '+')
		i++;
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("minishell: exit ", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (255);
		}
		i++;
	}
}

int	ft_atol(const char *str)
{
	long int	number;
	int			sign;
	int			i;

	number = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += (int)str[i] - '0';
		i++;
	}
	return (number * sign);
}

int32_t	ft_exit(t_input *data)
{
	unsigned long int	value;

	value = 0;
	if (data->cmd_args[1])
	{
		st_check_if_valid(data->cmd_args);
		value = ft_atol(data->cmd_args[1]);
		if ((value > LONG_MAX) || value > ((unsigned long)LONG_MAX + 1))
			printf ("long loong\n");
		ft_putendl_fd("exit", STDERR_FILENO);
		if (data->cmd_args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
	}
	else
	{
		if (!data->exit_for_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
		exit (g_exit_code);
	}
	exit (value % 256);
}
