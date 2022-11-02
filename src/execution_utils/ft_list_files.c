/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:13:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/02 19:23:59 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_lstadd_back_file(t_file **lst, t_file *new)
{
	t_file	*addlast;

	addlast = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		addlast = ft_lstlast_file(*lst);
		addlast->next = new;
	}
}

t_file	*ft_lstlast_file(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_file	*ft_lstnew_file(void *content, t_token_type flag)
{
	t_file	*new_el;

	new_el = (t_file *)malloc(sizeof(t_file));
	if (!new_el)
		return (NULL);
	new_el->name = ft_strdup(content);
	new_el->flag = flag;
	new_el->next = NULL;
	return (new_el);
}
