/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 09:34:28 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/03 23:21:59 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

static void	*st_calloc(size_t count, size_t size)
{
	u_int8_t	*ptr;
	size_t		len;
	size_t		i;

	len = count * size;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

t_table	*init_table(u_int32_t containers)
{
	t_table	*new;

	if (!containers)
		containers = DEFAULT_HASH_TABLE_SIZE;
	new = st_calloc(1, sizeof(t_table));
	if (new == NULL)
		return (NULL);
	new->table = st_calloc(containers, sizeof(t_container *));
	if (new->table == NULL)
		return (free(new), NULL);
	new->containers = containers;
	new->entries = 0;
	return (new);
}
