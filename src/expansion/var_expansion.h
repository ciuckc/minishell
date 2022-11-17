/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 02:34:51 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 02:54:39 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_EXPANSION_H
# define VAR_EXPANSION_H

# include "minishell.h"

typedef struct s_expanded_str_len
{
	u_int32_t	env_var_len;
	u_int32_t	unexp_len;
}	t_expand_len;

bool		needs_expansion(char *str);

void		expand_variables(t_token *words, t_table *table);

void		expand_var_in_str(t_token *word, t_table *table);

ssize_t		expanded_var_len(char *str, t_table *table);

u_int32_t	get_pid_len(void);

void		str_append_pid(char **dst);

void		str_append_exit_code(char **dst);

void		count_data_len(char **str, t_expand_len *len, t_table *table, \
bool d_quoted);

void		remove_quotes(t_token *word);

#endif