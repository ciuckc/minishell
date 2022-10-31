/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:40:04 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:07:03 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	set_fds(t_input *data)
{
	data->temp_fd[0] = dup(STDIN_FILENO);
	data->temp_fd[1] = dup(STDOUT_FILENO);
}

void	reset_fds(t_input *data)
{
	if (dup2(data->temp_fd[0], STDIN_FILENO) < 0)
		error_exit("Dup 0 failed", 1);
	close (data->temp_fd[0]);
	if (dup2(data->temp_fd[1], STDOUT_FILENO) < 0)
		error_exit("Dup 1 failed", 1);
	close (data->temp_fd[1]);
}

int	single_command(t_input *data)
{
	int		exit_code;
	pid_t	child_pid;

	exit_code = 0;
	child_pid = -2;
	set_fds(data);
	if (is_built_in(data->cmd_args[0]))
	{
		openfiles(data);
		exit_code = check_builtin(data);
		// reset_fds(data);
	}
	else
		child_pid = exec_single(data);
	printf ("child_pid  %d\n", child_pid);
	return (exit_code);
}

	//return exitcode from waitpid of last child