/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:19:05 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/09 16:52:51 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/// @brief 
/// @param envi 
/// @param data 
void	get_env_array(char **envi, t_input *data)
{
	int		i;
	char	**en;

	i = 0;
	while (envi[i])
		i++;
	en = (char **)malloc(sizeof(char *) * (i + 1));
	if (!en)
		error_exit("Malloc failed", 1);
	i = 0;
	while (envi[i])
	{
		en[i] = ft_strdup(envi[i]);
		i++;
	}
	en[i] = NULL;
	data->environ = en;
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
	data_in->fds[READ] = STDIN_FILENO;
	data_in->fds[WRITE] = STDOUT_FILENO;
	data_in->exit_code = 0;
	get_env_array(envp, data_in);
	return (data_in);
}

/**
 * @brief this is test
 * @param argv from main
 * @param envp from main
 * @return some int value
*/
int	execution(char **argv, char **envp)
{
	t_input		*data;
	t_token		*tok;

	(void)argv;
	data = NULL;
	tok = get_test_input();
	data = data_init(envp);
	get_path(data);
	count_cmds(tok, data);
	if (data->cmd_count == 1)
		data->exit_code = single_command(tok, data);
	else
		data->exit_code = multiple_commands(tok, data);
	return (data->exit_code);
}
