/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var_in_str.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 18:55:29 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/02 01:19:29 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static char	*st_extend_var(char *old_str, char *new_str, t_table *env, t_info \
*info)
{
	info->i++;
	if (old_str[info->i] == '$')
	{
		new_str = str_append_pid(old_str, new_str, info);
		info->i++;
	}
	else if (old_str[info->i] == '?')
	{
		new_str = str_append_exit_code(new_str, old_str, info);
		info->i++;
	}
	else if ((ft_strchr("\'\"", old_str[info->i]) && info->d_quoted) || \
	!old_str[info->i])
	{
		new_str[info->j] = '$';
		info->j++;
	}
	else if (ft_strchr("\'\"", old_str[info->i]) && !info->d_quoted)
		return (new_str);
	else
		new_str = str_append_var_data(old_str, new_str, env, info);
	return (new_str);
}

static char	*st_copy_d_quote(char *old_str, char *new_str, t_table *env, \
t_info *info)
{
	new_str[info->j++] = old_str[info->i++];
	while (old_str[info->i] != '\"')
	{
		if (old_str[info->i] == '$')
		{
			new_str = st_extend_var(old_str, new_str, env, info);
			if (new_str == NULL)
				return (NULL);
		}
		else
			new_str[info->j++] = old_str[info->i++];
	}
	new_str[info->j++] = old_str[info->i++];
	return (new_str);
}

static void	st_copy_s_quote(char *old_str, char *new_str, t_info *info)
{
	new_str[info->j++] = old_str[info->i++];
	while (old_str[info->i] != '\'')
		new_str[info->j++] = old_str[info->i++];
	new_str[info->j++] = old_str[info->i++];
}

static char	*st_append_to_new_str(char *old_str, char *new_str, t_table *env)
{
	t_info	info;

	info = (t_info){0};
	while (old_str[info.i])
	{
		if (old_str[info.i] == '\'')
			st_copy_s_quote(old_str, new_str, &info);
		else if (old_str[info.i] == '\"')
		{
			info.d_quoted = true;
			new_str = st_copy_d_quote(old_str, new_str, env, &info);
			info.d_quoted = false;
		}
		else if (old_str[info.i] == '$')
			new_str = st_extend_var(old_str, new_str, env, &info);
		else
			new_str[info.j++] = old_str[info.i++];
		if (new_str == NULL)
			return (NULL);
	}
	return (new_str);
}

char	*expand_var_in_str(t_token *word, t_table *table)
{
	char	*new_str;
	ssize_t	sum_len;

	sum_len = expanded_var_len(word->str, table);
	if (sum_len == 0)
	{
		free(word->str);
		word->str = NULL;
		return (NULL);
	}
	new_str = ft_calloc(sum_len + 1, sizeof(char));
	if (new_str == NULL)
	{
		free(word->str);
		word->str = NULL;
		return (NULL);
	}
	new_str = st_append_to_new_str(word->str, new_str, table);
	if (new_str == NULL)
		return (NULL);
	free(word->str);
	return (new_str);
}
