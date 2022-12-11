/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:25:33 by emlicame          #+#    #+#             */
/*   Updated: 2022/12/10 16:39:19 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

int32_t	mini_ft_strchr(const char *s, int c)
{
	char	*string;
	int		len;

	len = 0;
	string = (char *)s;
	while (*string != c)
	{
		if (*string == '\0')
			return (0);
		string++;
		len++;
	}
	return (len);
}

static int32_t	error_not_valid(char *var)
{
	ft_putstr_fd("minishell: export:`", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
	return (1);
}

static int32_t	st_if_valid(char *var)
{
	int	i;

	i = 0;
	if (var[0] == '=')
		return (error_not_valid(var));
	while (var[i] && var[i] != '=')
	{
		if (ft_isdigit(var[0]) || (var[0] == '=') \
			|| (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_'))
			return (error_not_valid(var));
		i++;
	}
	return (0);
}

static int32_t	st_sort_print(t_table *env_table)
{
	u_int32_t	i;
	char		**new_var_table;

	new_var_table = sort_table(env_table);
	if (!new_var_table)
		return (error_print("Malloc failed"), 1);
	i = 0;
	while (new_var_table[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(new_var_table[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	ft_free_mem(&new_var_table);
	return (0);
}

int32_t	ft_export(t_input *data, t_table *env_table)
{
	int32_t		i;
	int32_t		ret;

	ret = 0;
	i = 1;
	if (data->cmd_args[1] == NULL)
		st_sort_print(env_table);
	while (data->cmd_args[i])
	{
		if (st_if_valid(data->cmd_args[i]))
			return (1);
		if (mini_ft_strchr(data->cmd_args[i], '='))
			ret = insert_replace_var(data, env_table, i);
		else
			ret = ins_replace_var_no_eq(data, env_table, i);
		if (ret == 1)
			return (1);
		i++;
	}
	return (0);
}
