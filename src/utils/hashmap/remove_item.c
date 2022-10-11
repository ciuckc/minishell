/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_item.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 07:48:25 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/11 09:32:06 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

bool	remove_item(char *key, t_table **map)
{
	u_int32_t	hash_index;

	hash_index = hash_string(key) % (*map)->containers;
	if ((*map)->table[hash_index] == NULL)
		return (false);
	return (true);
}
