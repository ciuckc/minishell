/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:02:46 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/25 15:21:56 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	get_cmd(t_token **tok, t_input *data)
{
	int		len;
	int		i;
	t_token	*token;

	i = 0;
	token = *tok;
	len = ft_lstsize(*tok) + 1;
	data->cmd_args = (char **)ft_calloc(len, sizeof (char *));
	if (ft_strncmp(token->content, "./a.out", 7) == 0)
		token = token->next;
	if (ft_strncmp(token->content, "infile", 6) == 0)
		token = token->next;
	while (token)
	{
		if (ft_strncmp(token->content, "outfile", 7) == 0)
			break ;
		data->cmd_args[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
}

	// dprintf (2, "%s\n", data->cmd_args[i]);
	// while (token != NULL)
	// {
	// 	printf("*-*%s*-*\n", token->content);
	// 	token = token->next;
	// }