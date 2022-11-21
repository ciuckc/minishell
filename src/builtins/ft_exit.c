/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:30:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/20 17:35:27 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

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
			ft_putstr_fd("minishell: line 0: exit ", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (255);
		}
		i++;
	}
}

int32_t	ft_exit(t_input *data)
{
	int	value;

	value = 0;
	if (data->cmd_args[1])
	{
		st_check_if_valid(data->cmd_args);
		value = ft_atoi(data->cmd_args[1]);
		ft_putendl_fd("exit", STDERR_FILENO);
		if (data->cmd_args[2])
		{
			ft_putendl_fd("minishell: line 0: exit: too many arguments", 2);
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
