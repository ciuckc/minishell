/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:14:41 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/24 14:48:16 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
int	main(void)
{
	ft_putstr_fd("Don't panic", 2);
	return (0);
}
*/
