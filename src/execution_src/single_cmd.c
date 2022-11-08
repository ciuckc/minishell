/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:40:04 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 16:26:53 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_single(t_token *tok, t_input *data)
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
		open_infiles(tok, data);
		open_outfiles(tok, data);
		if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
			error_exit("command not found", 127);
	}
	else
		exit_code = waiting(id, 1);
	return (exit_code);
}

int	single_command(t_token *tok, t_input *data)
{
	int		exit_code;
	pid_t	child_pid;

	exit_code = 0;
	child_pid = -2;
	(void)tok;
	if (is_built_in(data->cmd_args[0]))
	{
		open_outfiles(tok, data);
		exit_code = check_builtin(data);
	}
	else
		child_pid = exec_single(tok, data);
	printf ("child_pid  %d\n", child_pid);
	return (exit_code);
}

	//return exitcode from waitpid of last child