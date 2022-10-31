/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lists_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:09:48 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:32:18 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void	end_free(t_token *env, int exit_code)
// {
// 	if (env)
// 		list_clear(&env);
// 	exit (exit_code);
// }

t_token	*ft_lstlast_t(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	list_clear_t(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free (*lst);
		*lst = temp;
	}
}

void	ft_lstadd_back_t(t_token **lst, t_token *new)
{
	t_token	*addlast;

	addlast = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		addlast = ft_lstlast_t(*lst);
		addlast->next = new;
	}
}

t_token	*ft_lstnew_t(void *content)
{
	t_token	*new_el;

	new_el = (t_token *)malloc(sizeof(t_token));
	if (!new_el)
		return (NULL);
	new_el->content = ft_strdup(content);
	new_el->next = NULL;
	return (new_el);
}

int	ft_lstsize_t(t_token *lst)
{
	t_token	*current;
	int		elements;

	elements = 0;
	if (lst)
		current = lst;
	else
		return (0);
	while (current != NULL)
	{
		elements++;
		current = current->next;
	}
	return (elements);
}
