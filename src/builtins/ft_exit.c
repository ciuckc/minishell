/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:30:17 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/11 19:21:02 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	ft_exit(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit (0);
	}
	if (i > 2)
		error_exit("exit: too many arguments\n", 1);
	return (0);
}
