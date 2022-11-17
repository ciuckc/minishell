/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:34:40 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/16 18:20:22 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	ft_pwd(t_input *data)
{
	char	cwd[256];

	(void)data;
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
