/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:09:48 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/24 14:48:30 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	end_free(t_envi *env, int exit_code)
{
	if (env)
		list_clear(&env);
	exit (exit_code);
}

t_envi	*ft_lstlast(t_envi *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	list_clear(t_envi **lst)
{
	t_envi	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free (*lst);
		*lst = temp;
	}
}

void	ft_lstadd_back(t_envi **lst, t_envi *new)
{
	t_envi	*addlast;

	addlast = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		addlast = ft_lstlast(*lst);
		addlast->next = new;
	}
}

t_envi	*ft_lstnew(void *content)
{
	t_envi	*new_el;

	new_el = (t_envi *)malloc(sizeof(t_envi));
	if (!new_el)
		return (NULL);
	new_el->envectors = ft_strdup(content);
	new_el->next = NULL;
	return (new_el);
}
