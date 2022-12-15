/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:18:18 by scristia          #+#    #+#             */
/*   Updated: 2022/12/13 19:32:57 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

# define PROMPT "\001\033[1;32m\002minishell$\001\033[0m\002 "

int32_t		synthax_check(t_token *words);

void		remove_null_str(t_token **words);

void		remove_quotes_list(t_token *word);

void		execute_loop(t_cmd_list **cmd_listm, t_table *env_table, char \
***env);

#endif