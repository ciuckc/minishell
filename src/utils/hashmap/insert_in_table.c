/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insert_in_table.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 04:21:27 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/11 10:42:21 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "stdio.h"

static void	st_add_front(t_table \
**hash_table, u_int32_t hash_idx, t_container *item)
{
	(*hash_table)->table[hash_idx]->prev = item;
	item->next = (*hash_table)->table[hash_idx];
	(*hash_table)->table[hash_idx] = item;
}

static t_container	*st_create_item(char *key, \
void *data, t_table **hash_table, u_int32_t hash_idx)
{
	t_container	*item;

	item = malloc(sizeof(t_container));
	if (item == NULL)
	{
		printf("HERE");
		return (NULL);
	}
	item->prev = NULL;
	item->next = NULL;
	item->data = data;
	item->key_str = key;
	item->hash = hash_idx;
	if ((*hash_table)->table[hash_idx] == NULL)
		(*hash_table)->table[hash_idx] = item;
	else
		st_add_front(hash_table, hash_idx, item);
	item->items++;
	return (item);
}

t_container	*insert_in_table(char *key, void *data, t_table **hash_table)
{
	u_int32_t	hash_key;
	u_int32_t	hash_index;
	t_container	*item;

	if (key == NULL || data == NULL)
		return (NULL);
	if (*hash_table == NULL)
	{
		printf("HERE!");
		*hash_table = init_table(DEFAULT_HASH_TABLE_SIZE);
	}
	hash_key = hash_string(key);
	hash_index = hash_key % (*hash_table)->containers;
	item = st_create_item(key, data, hash_table, hash_index);
	(*hash_table)->entries++;
	printf("%s=%s\n", key, data);
	return (item);
}
