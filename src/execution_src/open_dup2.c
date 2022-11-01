/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dup2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:11:18 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/01 19:18:06 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	openfiles(t_input *data)
{
	while (data->file_lst)
	{
		if (data->file_lst->flag == LESS)
		{
			data->fds[READ] = open (data->file_lst->name, O_RDONLY);
			if (data->fds[READ] < 0)
				error_exit(data->file_lst->name, 1);
			if (dup2(data->fds[READ], STDIN_FILENO) < 0)
				error_exit("Dup failed", 1);
		}
		else if (data->file_lst->flag == GREAT)
		{
			data->fds[WRITE] = open(data->file_lst->name, O_CREAT | \
			O_WRONLY | O_TRUNC, 0644);
			if (data->fds[WRITE] < 0)
				error_exit(data->file_lst->name, 1);
			if (dup2(data->fds[WRITE], STDOUT_FILENO) < 0)
				error_exit("Dup failed", 1);
		}
		data->file_lst = data->file_lst->next;
	}
	close(data->fds[READ]);
	close(data->fds[WRITE]);
}

/*
	Remember!!! man dup2
	 In dup2(), the value of the new descriptor fildes2 is specified.  
	 If fildes and fildes2 are equal, then dup2() just returns fildes2; 
	 no other changes are made to the existing descriptor.  
	 Otherwise, if descriptor fildes2 is already in use, it is first deallocated
	 as if a close(2) call had
     been done first.
	*/