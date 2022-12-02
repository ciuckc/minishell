/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 03:49:13 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/02 00:54:09 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_FUNCTIONS_H
# define FREE_FUNCTIONS_H

# include "minishell.h"

/**
 * @brief free the built word list with it s assigned types and content
 * 
 * @param list 
 */
void			free_word_list(t_token **list);

/**
 * @brief free the list in case of error
 * 
 * @param list 
 */
void			free_scan_list(t_scan_tok **list);

/**
 * @brief free the envp in case of an error. It will set the whole list to NULL
 * 
 * @param envp 
 * @param i 
 */
void			free_new_envp(char ***envp, u_int32_t i);

/**
 * @brief 
 * 
 * @param str 
 * @return int32_t 
 */
int32_t			ft_free_mem(char ***str);

void			free_cmd_list(t_cmd_list **lst);

#endif