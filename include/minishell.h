/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 20:52:52 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 18:41:55 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/utils/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include "../src/utils/hashmap/hashmap.h"
# include "msh_types.h"
# include "../src/free_functions/free_functions.h"
# include "signal.h"

extern volatile u_int64_t	g_exit_code;

void		init_sig_handle(int mode);

int			execution(t_token *tok, t_table *table, char **envp);

void		expand_words(t_token **words, t_table *table);

t_cmd_list	*parser(char *full_cmd, t_table *env);

/**
 * @brief Create a env table object. When initialised, we remove the $OLDPWD 
 * env variable. !!! When done remember to free every piece of data and key_str
 * from each container allocated, before flush the actual table and 
 * containers.
 * @param envp Environment variables.
 * @return t_table* 
 */
t_table		*create_env_table(char **env);

/**
 * @brief Create a new envp array of arrays
 * 
 * @param env_table refference hash table to update to latest changes
 * @param table converted from export and unset
 */
void		create_new_envp(t_table *env_table, char ***table);

#endif
