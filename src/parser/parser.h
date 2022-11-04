/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/04 09:29:32 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "msh_types.h"

/**
 * @brief get word list
 * @param full_cmd
 * @param table
 */
t_token_list	*retrieve_word_list(char *full_cmd);

/**
 * @brief create a list of individual microtokens splitted on 
 * their type(word, assign_word, quotes)
 * @param full_cmd 
 * @return t_scan_tok* list with null terminated CMD node
 */
t_scan_tok		*tok_len_scan_list(char **full_cmd);

/**
 * @brief add the current micro token recognized and it s boundry to the list
 * 
 */
t_scan_tok		*add_boundry_to_list(t_scan_tok **lst, u_int32_t start, \
u_int32_t end, char *cmd);

/**
 * @brief build a word and assign it s type. This word is delimited by END, IFS
 * or OPERTATORS
 * @param lst the list of micro tokens
 * @return t_token* 
 */
t_token			*build_word(t_scan_tok **lst);

void			create_cmd_list(t_cmd_list **list, t_token_list *words);

#endif