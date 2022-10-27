/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:48:37 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/26 11:50:25 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

// void	error_msg_exit(char *text, int exit_code)
// {
// 	ft_putstr_fd("myshell: ", STDERR_FILENO);
// 	perror(text);
// 	exit(exit_code);
// }

void	error_exit(char *text, int exit_code)
{
	ft_putstr_fd("myshell: ", STDERR_FILENO);
	perror(text);
	exit(exit_code);
}

	//ft_putstr_fd(strerror(errno), 2);