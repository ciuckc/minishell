/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   item_search.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 01:21:01 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/23 18:28:51 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stdio.h>

static int32_t	st_strcmp(char *str1, char *str2)
{
	int32_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	return (str1[i] - str2[i]);
}

t_container	*item_search(char *key, t_table *map)
{
	u_int32_t	key_idx;
	t_container	*container;

	if (!key)
		return (NULL);
	key_idx = hash_string(key) % map->containers;
	container = map->table[key_idx];
	if (container == NULL)
	{
		return (NULL);
	}
	while (container != NULL)
	{
		if (st_strcmp(key, container->key_str) == 0)
			break ;
		container = container->next;
	}
	return (container);
}
