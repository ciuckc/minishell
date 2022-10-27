/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fetch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:02 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/27 19:45:52 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	data_fetch(t_envi **envi, t_token **tok, t_input **data)
{
	int		i;
	pid_t	id;
	t_token	*tok_head;
	t_input	*data_head;

	i = 0;
	tok_head = *tok;
	data_head = *data;
	data_head->fds[0] = 0;
	data_head->fds[1] = 1;
	get_path(*envi, *data);
	get_cmd(&tok_head, *data);
	execution_start(*data);
	return (0);
}
