/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:30:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/13 18:19:59 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static void	check_if_valid(char **arg)
{
	int	i;

	i = 0;
	if (arg[1][0] == '-')
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

int	ft_exit(char **arg)
{
	int	num;

	num = 0;
	if (arg[1])
	{
		check_if_valid(arg);
		num = ft_atoi(arg[1]);
		ft_putendl_fd("exit", STDERR_FILENO);
		if (arg[2])
		{
			error_exit("exit: too many arguments\n", 1);
			return (1);
		}
	}
	else
		ft_putendl_fd("exit", STDERR_FILENO);
	exit (num % 256);
}
