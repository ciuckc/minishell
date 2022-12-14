/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 18:30:17 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/15 19:18:40 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"
#include <limits.h>

static void	error_numeric_argument(char *arg, t_input *data)
{
	if (!data->exit_for_pipe)
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit (255);
}

static void	st_check_if_valid(char **arg, t_input *data)
{
	int	i;

	i = 0;
	if (arg[1][0] == '-' || arg[1][0] == '+')
		i++;
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
			error_numeric_argument(arg[1], data);
		i++;
	}
}

static int64_t	ft_atoll(char *str, t_input *data)
{
	int64_t		number;
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
		number += (int64_t)str[i] - '0';
		i++;
	}
	if ((sign == -1) && (number > LONG_MAX))
		error_numeric_argument(str, data);
	return (number * sign);
}

static size_t	ft_double_strlen(char **str)
{
	size_t	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}

int32_t	ft_exit(t_input *data)
{
	if (ft_double_strlen(data->cmd_args) == 1)
	{
		if (!data->exit_for_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
		exit (g_exit_code);
	}
	else if (ft_double_strlen(data->cmd_args) == 2)
	{
		st_check_if_valid(data->cmd_args, data);
		data->value = ft_atoll(data->cmd_args[1], data);
		if ((ft_isdigit(data->cmd_args[1][0]) || \
		data->cmd_args[1][0] == '+') && (data->value < 0))
			error_numeric_argument(data->cmd_args[1], data);
		if (!data->exit_for_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
	}
	else if (ft_double_strlen(data->cmd_args) > 2)
	{
		st_check_if_valid(data->cmd_args, data);
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	}
	exit (data->value % 256);
}
