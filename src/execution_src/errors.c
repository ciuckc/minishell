/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:48:37 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/17 19:48:32 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_exit(char *text, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(text);
	exit(exit_code);
}

void	error_print(char *text)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(text);
}

void	command_not_found(t_input *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit (127);
}

void	permission_denied(t_input *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd_args[0], 2);
	ft_putendl_fd(": Permission denied", 2);
	exit (126);
}

void	no_such_file(t_input *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd_args[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	exit (127);
}
