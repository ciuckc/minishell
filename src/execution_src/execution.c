/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:45:47 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 11:39:20 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution(t_input *data)
{
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
}
