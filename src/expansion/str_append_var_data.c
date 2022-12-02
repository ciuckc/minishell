/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_append_var_data.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 16:29:26 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/02 01:24:17 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static size_t	st_get_name_len(char *str)
{
	size_t	len;

	len = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (len);
	while ((ft_isalpha(str[len]) || ft_isdigit(str[len]) || str[len] \
	== '_') && str[len])
		len++;
	return (len);
}

char	*str_append_var_data(char *old_str, char *new_str, t_table *env, \
t_info *info)
{
	t_env		var;
	size_t		name_len;
	t_container	*container;

	name_len = st_get_name_len(old_str + info->i);
	var.name = ft_substr(old_str + info->i, 0, name_len);
	if (var.name == NULL)
		return (free(old_str), free(new_str), NULL);
	container = item_search(var.name, env);
	info->i += name_len;
	if (container == NULL)
		return (free(var.name), free(old_str), free(new_str), NULL);
	var.value = container->data;
	ft_memcpy(new_str + info->j, var.value, ft_strlen(var.value));
	info->j += ft_strlen(var.value);
	free(var.name);
	return (new_str);
}
