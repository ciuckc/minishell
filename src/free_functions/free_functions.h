/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 03:49:13 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/04 03:54:39 by scristia      ########   odam.nl         */
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
void			free_word_list(t_token_list **list);

/**
 * @brief free the list in case of error
 * 
 * @param list 
 */
void			free_scan_list(t_scan_tok **list);

#endif