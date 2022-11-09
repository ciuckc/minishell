/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:48:37 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/09 11:52:09 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	error_exit(char *text, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(text);
	exit(exit_code);
}
