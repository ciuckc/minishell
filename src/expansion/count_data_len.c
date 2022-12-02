/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_data_len.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 15:43:02 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/02 01:18:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static u_int32_t	st_count_name_len(char *str)
{
	size_t	len;

	len = 0;
	while (*str && (ft_isalpha(*str) || ft_isdigit(*str) || *str == '_'))
	{
		str++;
		len++;
	}
	return (len);
}

void	count_data_len(char **str, t_expand_len *len, t_table *table, \
bool d_quoted)
{
	t_env		param;
	u_int32_t	name_len;
	t_container	*var;

	param = (t_env){0};
	name_len = st_count_name_len(*str);
	if (name_len == 0 && d_quoted == false)
		return ;
	else if (name_len == 0 && d_quoted == true)
	{
		len->unexp_len++;
		return ;
	}
	param.name = ft_substr(*str, 0, name_len);
	if (param.name == NULL)
		return ;
	var = item_search(param.name, table);
	(*str) += name_len;
	if (var == NULL)
		return (free(param.name));
	param.value = var->data;
	len->env_var_len += ft_strlen(param.value);
	free(param.name);
}
