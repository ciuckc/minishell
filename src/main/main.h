/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 19:18:18 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/01 19:19:21 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

int32_t		synthax_check(t_token *words);

void		remove_null_str(t_token **words);

void		remove_quotes_list(t_token *word);

#endif