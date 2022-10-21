/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/21 03:40:56 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "msh_types.h"

t_token			*create_token(char *tok);

/**
 * @brief get token list
 * 
 * @param full_cmd 
 * @return t_token_list* 
 */
t_token_list	*retrieve_tok_list(char *full_cmd);

t_scan_tok		*tok_len_scan_list(char **full_cmd);

t_scan_tok		*add_boundry_to_list(t_scan_tok **lst, u_int32_t start, \
u_int32_t end, char *cmd);

void			free_scan_list(t_scan_tok *list);

#endif