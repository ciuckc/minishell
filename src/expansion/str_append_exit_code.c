/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_append_exit_code.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 23:31:50 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/30 18:20:53 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

char	*str_append_exit_code(char *new_str, char *old_str, t_info *info)
{
	char	*str_exit_code;

	str_exit_code = ft_itoa(g_exit_code);
	if (str_exit_code == NULL)
		return (free(new_str), free(old_str), NULL);
	ft_memcpy(new_str + info->j, str_exit_code, ft_strlen(str_exit_code));
	info->j += ft_strlen(str_exit_code);
	return (new_str);
}
