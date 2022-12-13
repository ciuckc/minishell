/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:32:42 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/13 18:35:08 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

static int32_t	error_not_valid(char *var)
{
	ft_putstr_fd("minishell: unset:`", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
	return (1);
}

static int32_t	st_if_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (ft_isdigit(var[0]) || (var[i] == '=') \
			|| (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_'))
			return (error_not_valid(var));
		i++;
	}
	return (0);
}

int32_t	ft_unset(t_input *data, t_table *env_table)
{
	int		i;

	i = 1;
	if (!data->cmd_args[i])
		return (0);
	while (data->cmd_args[i])
	{
		if (!st_if_valid(data->cmd_args[i]))
			remove_item(data->cmd_args[i], &env_table);
		i++;
	}
	return (g_exit_code);
}
