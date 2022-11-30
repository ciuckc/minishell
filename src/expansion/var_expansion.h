/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 02:34:51 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/30 18:11:43 by scristia      ########   odam.nl         */
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

typedef struct s_expansion_info
{
	size_t	i;
	size_t	j;
	bool	d_quoted;
}	t_info;

void		expand_variables(t_token *words, t_table *table);

char		*expand_var_in_str(t_token *word, t_table *table);

ssize_t		expanded_var_len(char *str, t_table *table);

u_int32_t	get_pid_len(void);

char		*str_append_pid(char *new_str, char *old_str, t_info *info);

char		*str_append_exit_code(char *new_str, char *old_str, t_info *info);

char		*str_append_var_data(char *old_str, char *new_str, t_table *env, \
t_info *info);

void		count_data_len(char **str, t_expand_len *len, t_table *table, \
bool d_quoted);

void		remove_quotes(t_token *word);

#endif