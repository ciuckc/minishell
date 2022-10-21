/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 08:27:05 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/21 03:20:02 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_token	*create_token(char *tok)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->tok = tok;
	new->type = 0;
	return (NULL);
}
