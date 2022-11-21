/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:47:09 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/20 18:46:46 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../execution_src/execution.h"

int	exec_built_in(t_input *data, t_table *env_table)
{
	if (ft_strncmp(data->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(data->cmd_args));
	if (ft_strncmp(data->cmd_args[0], "cd", 3) == 0)
		return (ft_cd(data, env_table));
	if (ft_strncmp(data->cmd_args[0], "pwd", 4) == 0)
		return (ft_pwd(data));
	if (ft_strncmp(data->cmd_args[0], "exit", 5) == 0)
		return (ft_exit(data));
	return (-1);
}

bool	is_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

int32_t	run_builtin(t_input *data, t_table *env_table)
{
	if (is_built_in(data->cmd_args[0]))
	{
		g_exit_code = exec_built_in(data, env_table);
	}
	return (g_exit_code);
}
