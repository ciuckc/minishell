/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 17:17:08 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 11:39:58 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(void)
{
	int				result;
	char			*first;
	char			*second;
	unsigned int	n;

	n = 4;
	first = "\200";
	second = "HaryKrish";
	result = ft_strncmp(first, second, n);
	printf("%d", result);
	result = strncmp(first, second, n);
    printf("%d", result);
	return (0);
}
*/