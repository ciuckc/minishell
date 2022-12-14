/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_expand_var.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 19:25:16 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 18:56:30 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../expansion/var_expansion.h"

char	*ft_export_expand_var(char *unexp_value, t_table *env)
{
	t_token	temp;

	temp = (t_token){.str = unexp_value, .type = WORD};
	if (needs_expansion(unexp_value))
		unexp_value = expand_var_in_str(&temp, env);
	if (unexp_value == NULL)
		unexp_value = ft_strdup("");
	return (unexp_value);
}
