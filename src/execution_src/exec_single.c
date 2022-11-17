/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:45:08 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/08 16:27:20 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// int	exec_single(t_token *tok, t_input *data)
// {
// 	pid_t	id;
// 	int		exit_code;

// 	exit_code = -1;
// 	id = fork();
// 	if (id == -1)
// 		error_exit("Fork failed", 1);
// 	if (id == 0)
// 	{
// 		access_file(data);
// 		open_infiles(tok, data);
// 		open_outfiles(tok, data);
// 		if (execve(data->cmd_path, data->cmd_args, data->environ) < 0)
// 			error_exit("command not found", 127);
// 	}
// 	else
// 		exit_code = waiting(id, 1);
// 	return (exit_code);
// }