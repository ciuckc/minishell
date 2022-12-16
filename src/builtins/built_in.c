/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:47:09 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 02:13:23 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../execution_src/execution.h"

int	exec_built_in(t_input *data, t_table *env_table)
{
	if (ft_strncmp(data->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(data));
	if (ft_strncmp(data->cmd_args[0], "cd", 3) == 0)
		return (ft_cd(data, env_table));
	if (ft_strncmp(data->cmd_args[0], "pwd", 4) == 0)
		return (ft_pwd(data));
	if (ft_strncmp(data->cmd_args[0], "exit", 5) == 0)
		return (ft_exit(data));
	if (ft_strncmp(data->cmd_args[0], "unset", 6) == 0)
		return (ft_unset(data, env_table));
	if (ft_strncmp(data->cmd_args[0], "export", 7) == 0)
		return (ft_export(data, env_table));
	return (1);
}

bool	is_built_in(char *cmd)
{
	if (!cmd)
		return (false);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else
		return (false);
}

int32_t	run_builtin(t_input *data, t_table *env_table)
{
	if (is_built_in(data->cmd_args[0]))
		g_exit_code = exec_built_in(data, env_table);
	ft_free_mem(&data->cmd_args);
	return (g_exit_code);
}
