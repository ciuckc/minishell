/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:02 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/25 15:13:59 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	exec_cmd(t_envi **envi, t_token **tok, t_input **data)
{
	int		i;
	t_token	*tok_head;
	t_input	*data_head;
	pid_t	id;

	i = 0;
	tok_head = *tok;
	data_head = *data;
	get_path(*envi, *data);
	get_cmd(&tok_head, *data);
	check_builtin(&tok_head, *data);
	id = fork();
	if (id == -1)
		error_exit("Fork failed", 1);
	if (id == 0)
	{
		access_file(&data_head);
		dupfiles(*data);
		execution(*tok, data_head);
	}
	else
		wait(NULL);
	return (0);
}

