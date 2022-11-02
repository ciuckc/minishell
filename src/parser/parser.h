/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/02 17:31:55 by scristia      ########   odam.nl         */
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

/**
 * @brief create a list of individual microtokens splitted on 
 * their type(word, assign_word, quotes)
 * @param full_cmd 
 * @return t_scan_tok* list with null terminated CMD node
 */
t_scan_tok		*tok_len_scan_list(char **full_cmd);

/**
 * @brief add the current token micro recognized and it s boundry to the list
 * 
 */
t_scan_tok		*add_boundry_to_list(t_scan_tok **lst, u_int32_t start, \
u_int32_t end, char *cmd);

/**
 * @brief free the list in case of error
 * 
 * @param list 
 */
void			free_scan_list(t_scan_tok *list);

void			free_word_list(t_token_list **list);

t_token			*build_word(t_scan_tok **lst);

#endif