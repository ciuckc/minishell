/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:02:46 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:32:48 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	get_cmd(t_token **tok, t_input *data)
{
	int		len;
	int		i;
	t_token	*token;

	i = 0;
	token = *tok;
	len = ft_lstsize_t(*tok) + 1;
	data->cmd_args = (char **)ft_calloc(len, sizeof (char *));
	while (token && token->token_type != PIPE)
	{
		if (token->token_type == WORD)
		{
			data->cmd_args[i] = ft_strdup(token->content);
			i++;
		}
		if (token->token_type == LESS || \
			token->token_type == GREAT || \
			token->token_type == DLESS || \
			token->token_type == DGREAT)
		token = token->next->next;
		else
			token = token->next;
	}
	data->cmd_args[i] = NULL;
}

// t_file	*last_filelist(t_file *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// static void	add_file_back(t_file **lst, t_file *new)
// {
// 	t_file	*addlast;

// 	addlast = NULL;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	else
// 	{
// 		addlast = last_filelist(*lst);
// 		addlast->next = new;
// 	}
// }

// t_file	*new_node_file(char *content, t_token_type flag)
// {
// 	t_file	*new;

// 	new = (t_file *)malloc(sizeof(t_file));
// 	if (!new)
// 		return (NULL);
// 	new->name = ft_strdup(content);
// 	new->flag = ft_strdup(flag);
// 	new->next = NULL;
// 	return (new);
// }

// printf ("redir %c", token->token_type);
