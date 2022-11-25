/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var_in_str.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 04:02:53 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/25 19:59:15 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_append_var_data(char **src, char **dst, t_table *env)
{
	t_env		var;
	size_t		name_len;
	t_container	*container;

	name_len = 0;
	while (ft_isalpha((*src)[name_len]) || ft_isdigit((*src)[name_len]) || \
	(*src)[name_len] == '_')
		name_len++;
	var.name = ft_substr(*src, 0, name_len);
	if (var.name == NULL)
		return ;
	container = item_search(var.name, env);
	(*src) += name_len;
	if (container == NULL)
		return ;
	var.value = container->data;
	ft_memcpy(*dst, var.value, ft_strlen(var.value));
	(*dst) += ft_strlen(var.value);
	free(var.name);
}

static void	st_extend_var(char **src, char **dst, t_table *env, bool d_quoted)
{
	(*src)++;
	if (**src == '$')
	{
		str_append_pid(dst);
		(*src)++;
	}
	else if (**src == '?')
	{
		str_append_exit_code(dst);
		(*src)++;
	}
	else if (((**src == '\'' || **src == '\"') && d_quoted) || **src == '\0')
	{
		**dst = '$';
		(*dst)++;
	}
	else
		st_append_var_data(src, dst, env);
}

static void	st_copy_d_quote(char **src, char **dst, t_table *env)
{
	**dst = **src;
	(*dst)++;
	(*src)++;
	while (**src != '\"')
	{
		if (**src == '$')
			st_extend_var(src, dst, env, true);
		else
		{
			**dst = **src;
			(*dst)++;
			(*src)++;
		}
	}
	**dst = **src;
	(*dst)++;
	(*src)++;
}

static void	st_append_to_new_str(char *src, char *dst, t_table *env)
{
	char	*dst_head;

	dst_head = dst;
	while (*src)
	{
		if (*src == '\'')
		{
			*dst++ = *src++;
			while (*src != '\'')
				*dst++ = *src++;
			*dst++ = *src++;
		}
		else if (*src == '\"')
			st_copy_d_quote(&src, &dst, env);
		else if (*src == '$')
			st_extend_var(&src, &dst, env, false);
		else
			*dst++ = *src++;
	}
	dst = dst_head;
}

void	expand_var_in_str(t_token *word, t_table *table)
{
	ssize_t	sum_len;
	char	*new_str;

	sum_len = expanded_var_len(word->str, table);
	if (sum_len == 0)
	{
		free(word->str);
		word->str = NULL;
		return ;
	}
	new_str = ft_calloc(sum_len + 1, sizeof(char));
	if (new_str == NULL)
		return ;
	st_append_to_new_str(word->str, new_str, table);
	free(word->str);
	word->str = new_str;
}
