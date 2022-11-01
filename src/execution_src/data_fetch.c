/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fetch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:02 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/01 19:16:05 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	data_fetch(t_token **tok, t_input **data)
{
	(*data)->fds[0] = 0;
	(*data)->fds[1] = 1;
	get_path(*data);
	get_cmd(*tok, *data);
	count_cmds(*tok, *data);
	execution_start(*tok, *data);
	return (0);
}
