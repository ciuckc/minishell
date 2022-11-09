/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 02:34:51 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/09 16:02:15 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H

# include "minishell.h"
# include "msh_types.h"

void	expand_variables(t_token *words, t_table *table);

void	expand_var_in_str(t_token *word, t_table *table);

ssize_t	expanded_var_len(char *str, t_table *table);

#endif