/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_item.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:25 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/25 17:30:05 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "stdio.h"

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

static void	st_couple_node(t_container *key_item)
{
	if (key_item->prev != NULL)
		key_item->prev->next = key_item->next;
	if (key_item->next != NULL)
		key_item->next->prev = key_item->prev;
}

static void	st_free_container(t_container *key_item)
{
	free(key_item->data);
	free(key_item->key_str);
	free(key_item);
}

void	*remove_item(char *key, t_table **map)
{
	t_container	*key_item;
	u_int32_t	idx;

	key_item = item_search(key, *map);
	if (key_item == NULL)
		return (NULL);
	idx = key_item->hash % (*map)->containers;
	(*map)->entries = (*map)->entries - 1;
	if (key_item->next == NULL && key_item->prev == NULL)
	{
		(*map)->table[idx] = NULL;
		return (st_free_container(key_item), NULL);
	}
	if (key_item == (*map)->table[idx])
	{
		(*map)->table[idx] = key_item->next;
		key_item->next->prev = NULL;
		return (decrease_num_items(key, *map), st_free_container(key_item), \
		NULL);
	}
	st_couple_node(key_item);
	return (decrease_num_items(key, *map), st_free_container(key_item), NULL);
}
