/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_types.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 05:54:23 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/14 06:59:56 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TYPES_H
# define MSH_TYPES_H

# define TOKENS " &<|>"

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

#endif