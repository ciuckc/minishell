/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_item.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:25 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/14 02:14:39 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

static void	decrease_num_items(char *key, t_table *map)
{
	u_int32_t	key_idx;
	t_container	*cont;

	key_idx = hash_string(key) % map->containers;
	cont = map->table[key_idx];
	while (cont)
	{
		cont->items--;
		cont = cont->next;
	}
}

void	*remove_item(char *key, t_table **map)
{
	t_container	*key_item;
	void		*data_cpy;

	key_item = item_search(key, *map);
	if (key_item == NULL)
		return (NULL);
	if (key_item->prev != NULL)
		key_item->prev->next = key_item->next;
	if (key_item->next != NULL)
		key_item->next->prev = key_item->prev;
	data_cpy = key_item->data;
	decrease_num_items(key, *map);
	free(key_item);
	return (data_cpy);
}
