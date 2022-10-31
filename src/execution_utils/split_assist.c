/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_assist.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 16:57:02 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 11:40:12 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			i;

	i = 0;
	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (string1[i] == string2[i] && string1 != (void *)0 && i < n - 1)
		i++;
	return (string1[i] - string2[i]);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	dest = (char *) malloc (sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	tot_size;
	size_t	i;

	i = 0;
	tot_size = size * count;
	dest = malloc (tot_size);
	if (dest == NULL)
		return (NULL);
	while (i < tot_size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

char	*ft_strjoin_withfree(char *s1, char *s2)
{
	size_t	x;
	size_t	total_len;
	size_t	i;
	char	*new_string;

	i = 0;
	x = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (s1);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_string = (char *)malloc(sizeof(char) * total_len);
	if (!new_string)
		return (new_string);
	while (s1[x])
		new_string[i++] = s1[x++];
	while (*s2)
		new_string[i++] = *s2++;
	free(s1);
	s1 = NULL;
	new_string[i] = '\0';
	return (new_string);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
