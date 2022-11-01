/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:45:08 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/01 17:56:33 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	waiting(int id)
{
	int	status;
	int	exit_code;

	exit_code = -1;
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}
/*
wait for all children
while (data->cmd_count > 1)
{
	wait(&wait_status);
	data->cmd_count--;
}
*/

int	exec_single(t_input *data)
{
	pid_t	id;
	int		exit_code;

	exit_code = -1;
	id = fork();
	if (id == -1)
		error_exit("Fork failed", 1);
	if (id == 0)
	{
		access_file(data);
		openfiles(data);
		execution(data);
	}
	else
		exit_code = waiting(id);
	return (exit_code);
}
