/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 14:25:33 by emlicame      #+#    #+#                 */
/*   Updated: 2022/11/24 11:47:53 by emanuela      ########   odam.nl         */
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

static int32_t	st_if_valid(char *var)
{
	int			i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isdigit(var[0])
			|| (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[i] != '_'))
		{
			ft_putstr_fd("minishell: export:`", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	st_print_table(char **new_table)
{
	u_int32_t	i;

	i = 0;
	while (new_table[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(new_table[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int32_t	ft_export(t_input *data, t_table *env_table)
{
	int32_t		i;
	char		**new_var_table;

	i = 1;
	printf ("cmd%s\n", data->cmd_args[1]);
	if (data->cmd_args[1] == NULL)
	{
		new_var_table = make_table(env_table);
		st_print_table(new_var_table);
		ft_free_mem(&new_var_table);
		return (0);
	}
	else
	{
		while (data->cmd_args[i])
		{
			if (st_if_valid(data->cmd_args[i]))
				return (0);
			if (mini_ft_strchr(data->cmd_args[i], '='))
				replace_var(data, env_table, i);
			else
				replace_var_no_eq(data, env_table, i);
			i++;
		}
	}
	return (0);
}
