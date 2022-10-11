/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_string.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 05:39:31 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/11 09:32:07 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

u_int32_t	hash_string(char *string)
{
	u_int32_t		hash;
	unsigned char	*s;

	hash = FNV_OFFSET;
	s = (unsigned char *)string;
	while (*s)
	{
		hash = hash ^ *s;
		hash = hash * FNV_PRIME;
		s++;
	}
	return (hash);
}
