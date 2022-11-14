/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:40:04 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/14 16:16:45 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	dup_and_close(int fd, int in_out)
{
	if (dup2(fd, in_out) < 0)
	{
		error_print("Dup dup_and_close failed");
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief 
 * 
 * @param tok 
 * @param data 
 * @return int 
 */
int	exec_single(t_token *tok, t_input *data)
{
	t_token	*token;
	int		ret;

	ret = 0;
	token = tok;
		//disable sig
	ret = open_infiles(token, data);
	if (ret)
		if (dup_and_close(data->fds[READ], STDIN_FILENO))
			return (1);
	token = tok;
	ret = open_outfiles(token, data);
	if (ret)
		if (dup_and_close(data->fds[WRITE], STDOUT_FILENO))
			return (1);
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		error_exit("command not found", 127);
	return (0);
}

int	single_command(t_token *tok, t_input *data)
{
	t_token	*token;
	pid_t	id;

	token = tok;
	get_cmd(token, data);
	token = tok;
	if (is_built_in(data->cmd_args[0]))
	{
		open_outfiles(token, data);
		data->exit_code = check_builtin(data);
		return (data->exit_code);
	}
	id = fork();
	if (id == -1)
		error_exit("Fork failed", 1);
	if (id == 0)
		data->exit_code = exec_single(token, data);
	data->exit_code = waiting(id, 1);
	return (data->exit_code);
}

	//return exitcode from waitpid of last child