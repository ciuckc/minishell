/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_append_exit_code.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 23:31:50 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 00:49:58 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	str_append_exit_code(char **dst)
{
	char	*str_exit_code;

	str_exit_code = ft_itoa(g_exit_code);
	if (str_exit_code == NULL)
		return ;
	ft_memcpy((*dst), str_exit_code, ft_strlen(str_exit_code));
	(*dst) += ft_strlen(str_exit_code);
}
