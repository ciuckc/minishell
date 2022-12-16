/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:19:05 by emlicame      #+#    #+#                 */
/*   Updated: 2022/12/16 01:03:03by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// #include <termios.h>

void	ft_free_mem(char ***str)
{
	int	c;

	c = 0;
	if (!*str)
		return ;
	while ((*str)[c])
	{
		free((*str)[c]);
		(*str)[c] = NULL;
		c++;
	}
	free(*str);
	*str = NULL;
}

t_input	*data_init(char **envp)
{
	t_input	*data_in;

	data_in = malloc(sizeof(t_input));
	if (!data_in)
		error_exit("Malloc failed", 1);
	data_in->paths = NULL;
	data_in->cmd_path = NULL;
	data_in->exit_code = 0;
	data_in->value = 0;
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

void	st_print_array(t_token *lst)
{
	while (lst)
	{
		ft_putendl_fd(lst->str, 2);
		lst = lst->next;
	}
	ft_putendl_fd("ok\n", 2);
}

int32_t	execution(t_token *tok, t_table *env_table, char **envp)
{
	t_input		*data;

	data = data_init(envp);
	get_path(data);
	count_cmds(tok, data);
	init_sig_handle(1);
	if (data->cmd_count == 1)
		g_exit_code = single_command(tok, data, env_table);
	else
		g_exit_code = multiple_commands(tok, data, env_table);
	ft_free_mem(&data->paths);
	free(data);
	init_sig_handle(0);
	return (g_exit_code);
}
