/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_all.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 03:56:36 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/07 21:41:33 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

void	remove_all(t_table *map)
{
	u_int32_t	i;
	t_container	*prev;

	i = 0;
	prev = NULL;
	while (i < map->containers)
	{
		while (map->table[i] != NULL)
		{
			prev = map->table[i];
			map->table[i] = map->table[i]->next;
			free(prev->data);
			free(prev->key_str);
			free(prev);
		}
		i++;
	}
	free(map->table);
	free(map);
}
