/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:19:05 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/30 13:11:49 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int32_t	ft_free_mem(char ***str)
{
	int	c;

	c = 0;
	if (!*str)
		return (0);
	while ((*str)[c])
	{
		free((*str)[c]);
		(*str)[c] = NULL;
		c++;
	}
	free(*str);
	*str = NULL;
	return (1);
}

t_input	*data_init(char **envp)
{
	t_input	*data_in;

	data_in = malloc(sizeof(t_input));
	if (!data_in)
		error_exit("Malloc failed", 1);
	data_in->paths = (char **)malloc(sizeof (char *) * 1);
	if (!data_in->paths)
		error_exit("Malloc failed", 1);
	data_in->exit_code = 0;
	data_in->fds[READ] = STDIN_FILENO;
	data_in->fds[WRITE] = STDOUT_FILENO;
	data_in->exit_for_pipe = 0;
	data_in->environ = envp;
	data_in->new_var.name = NULL;
	data_in->new_var.value = NULL;
	data_in->old_var.name = NULL;
	data_in->old_var.value = NULL;
	return (data_in);
}

int32_t	execution(t_token *tok, t_table *env_table, char **envp)
{
	t_input		*data;

	data = NULL;
	data = data_init(envp);
	get_path(data);
	count_cmds(tok, data);
	if (data->cmd_count == 1)
		g_exit_code = single_command(tok, data, env_table);
	else
		g_exit_code = multiple_commands(tok, data, env_table);
	ft_free_mem(&data->paths);
	free (data);
	data = NULL;
	return (g_exit_code);
}
