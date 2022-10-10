/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:10 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/10 23:27:02 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define TOKENS " &<|>"

t_list	*create_token_list(char *full_cmd);

#endif