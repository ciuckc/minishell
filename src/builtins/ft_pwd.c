/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:34:40 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/18 17:52:38 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	ft_pwd(t_input *data)
{
	char	*cwd;

	(void)data;
	cwd = getcwd(0, 0);
	if (!cwd)
	{
		ft_putendl_fd("minishell: pwd", 2);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free (cwd);
	return (0);
}
