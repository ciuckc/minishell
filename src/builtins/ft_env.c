/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:00:11 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/22 16:55:39 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int	ft_env(t_input *data)
{
	int	i;

	i = 0;
	while (data->environ[i])
	{
		ft_putstr_fd(data->environ[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
