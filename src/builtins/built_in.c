/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:47:09 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:08:53 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "execution.h"

int	exec_built_in(t_input *data)
{
	if (ft_strncmp(data->cmd_args[0], "echo", 5) == 0)
		return (ft_echo(data->cmd_args));
	if (ft_strncmp(data->cmd_args[0], "cd", 3) == 0)
		return (ft_cd(data));
	return (-1);
}

bool	is_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	return (false);
}

int	check_builtin(t_input *data)
{
	int	ret;

	ret = 5;
	if (is_built_in(data->cmd_args[0]))
	{
		ret = exec_built_in(data);
	}
	return (ret);
}
