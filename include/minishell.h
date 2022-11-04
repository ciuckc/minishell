/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 20:52:52 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/04 08:29:34 by scristia      ########   odam.nl         */
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
# include "hashmap.h"
# include "msh_types.h"
# include "../src/free_functions/free_functions.h"

void		expand_variables(t_token_list *words, t_table *table);

t_cmd_list	*parser(char *full_cmd);

/**
 * @brief Create a env table object. When initialised, we remove the $OLDPWD 
 * env variable. !!! When done remember to free every piece of data and key_str
 * from each container allocated, before flush the actual table and 
 * containers.
 * @param envp Environment variables.
 * @return t_table* 
 */
t_table		*create_env_table(char **env);

#endif