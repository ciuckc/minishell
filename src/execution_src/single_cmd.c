/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:40:04 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/18 17:05:02 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	init_fd(t_input *data)
{
	data->temp_fd[READ] = dup(STDIN_FILENO);
	data->temp_fd[WRITE] = dup(STDOUT_FILENO);
}

void	reset_fd(t_input *data)
{
	if (dup2(data->temp_fd[READ], STDIN_FILENO) == -1)
		error_exit("Dup infile failed", 1);
	if (dup2(data->temp_fd[WRITE], STDOUT_FILENO) == -1)
		error_exit("Dup outfile failed", 1);
	close(data->temp_fd[READ]);
	close(data->temp_fd[WRITE]);
}

int	single_command(t_token *tok, t_input *data, t_table *env_table)
{
	t_token	*token;
	pid_t	id;

	(void) env_table;
	token = tok;
	get_cmd(token, data);
	token = tok;
	init_fd(data);
	if (is_built_in(data->cmd_args[0]))
	{
		if (open_outfiles(token, data))
			dup_and_close(data->fds[WRITE], STDOUT_FILENO);
		g_exit_code = run_builtin(data);
		reset_fd(data);
		return (g_exit_code);
	}
	id = fork();
	if (id == -1)
		error_exit("Fork failed", 1);
	if (id == 0)
		g_exit_code = exec_single(token, data);
	g_exit_code = waiting(id, 1);
	return (g_exit_code);
}
