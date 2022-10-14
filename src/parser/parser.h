/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/14 09:29:10 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "../utils/hashmap/hashmap.h"
# include "msh_types.h"

/**
 * @brief Create a token list
 * @param full_cmd Input command.
 * @return t_list* 
 */
t_list	*create_token_list(char *full_cmd);

/**
 * @brief Create a env table object. When initialised, we remove the $OLDPWD 
 * env variable. !!! When done remember to free every piece of data and key_str
 * from each container allocated, before flush the actual table and containers.
 * @param envp Environment variables.
 * @return t_table* 
 */
t_table	*create_env_table(char **envp);

#endif