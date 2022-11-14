/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 02:34:51 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/14 17:36:30 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H

# include "minishell.h"
# include "msh_types.h"

typedef struct s_expanded_str_len
{
	u_int32_t	env_var_len;
	u_int32_t	unexp_len;
}	t_expand_len;

bool		dolar_is_unquoted(char *str);

void		expand_variables(t_token *words, t_table *table);

void		expand_var_in_str(t_token *word, t_table *table);

ssize_t		expanded_var_len(char *str, t_table *table);

u_int32_t	get_pid_len(void);

#endif