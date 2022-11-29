/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:40:04 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/29 18:14:44 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_single(t_token *tok, t_input *data)
{
	t_token	*token;

	token = tok;
	if (open_infiles(token, data))
	{
		if (dup_and_close(data->fds[READ], STDIN_FILENO))
			return (1);
	}
	token = tok;
	if (open_outfiles(token, data))
	{
		if (dup_and_close(data->fds[WRITE], STDOUT_FILENO))
			return (1);
	}
	if (!data->cmd_args[0])
		exit (0);
	access_file(data);
	if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
		command_not_found(data);
	free (data->cmd_path);
	data->cmd_path = NULL;
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

	token = tok;
	get_cmd(token, data);
	token = tok;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (is_built_in(data->cmd_args[0]))
	{
		init_fd(data);
		if (open_outfiles(token, data))
			dup_and_close(data->fds[WRITE], STDOUT_FILENO);
		g_exit_code = run_builtin(data, env_table);
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
