/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 16:34:34 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 02:03:25 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	waiting(int id, int max)
{
	int	status;
	int	exit_code;

	exit_code = -1;
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	while (max > 0)
	{
		wait(NULL);
		max--;
	}
	return (exit_code);
}

void	parent_process(t_input *data)
{
	if (data->readfd != -1)
		close(data->readfd);
	data->readfd = data->pipe_fd[0];
	close(data->pipe_fd[1]);
	if (data->cmd_count == 1)
		close(data->pipe_fd[0]);
}

int	multiple_commands(t_token *tok, t_input *data, t_table *env_table)
{
	int		max;
	pid_t	id;

	data->readfd = -1;
	max = data->cmd_count;
	while (tok)
	{
		if (pipe(data->pipe_fd) == -1)
			error_exit("Pipe failed", 1);
		id = fork();
		if (id == -1)
			return (error_print("fork"), 1);
		if (id == 0)
			child_process(tok, data, max, env_table);
		parent_process(data);
		data->cmd_count--;
		while (tok->next && tok->type != PIPE)
			tok = tok->next;
		tok = tok->next;
	}
	g_exit_code = waiting(id, max);
	return (g_exit_code);
}

	// system("lsof -c minishell");