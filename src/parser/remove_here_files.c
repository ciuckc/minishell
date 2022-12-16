/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_here_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 22:39:33 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 23:44:30 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	remove_here_files(t_token **words)
{
	free((*words)->str);
	(*words)->str = NULL;
}
