/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 02:51:04 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/07 21:15:06 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	st_dec_quote_len(char *str, ssize_t *len)
{
	char	the_quote;

	the_quote = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			*len -= 2;
			the_quote = *str;
			str++;
			while (*str != the_quote && *str)
				str++;
			str++;
			continue ;
		}
		str++;
	}
}

static void	st_assign_str(char *src, char *dst)
{
	char	the_quote;

	the_quote = '\0';
	while (*src)
	{
		if (*src == '\'' || *src == '\"')
		{
			the_quote = *src;
			src++;
			while (*src != the_quote && *src)
				*dst++ = *src++;
			src++;
		}
		else
			*dst++ = *src++;
	}
}

void	remove_quotes(t_token *word)
{
	ssize_t	len;
	ssize_t	len_after_dec;
	char	*new_str;

	len = ft_strlen(word->str);
	st_dec_quote_len(word->str, &len);
	len_after_dec = ft_strlen(word->str);
	if (len == 0)
	{
		free(word->str);
		word->str = ft_strdup("");
		return ;
	}
	if (len == len_after_dec)
		return ;
	new_str = ft_calloc(len + 1, sizeof(char));
	if (new_str == NULL)
	{
		free(word->str);
		word->str = NULL;
		return ;
	}
	st_assign_str(word->str, new_str);
	free(word->str);
	word->str = new_str;
}
