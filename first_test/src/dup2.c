/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:11:18 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/24 14:47:41 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	dupfiles(t_input *data)
{
	data->fds[READ] = open("infile", O_RDONLY);
	if (data->fds[READ] < 0)
		error_exit("infile open failed", 1);
	if (dup2(data->fds[READ], 0) < 0)
		error_exit("Dup failed", 1);
	data->fds[WRITE] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds[WRITE] < 0)
		error_exit("outfile open failed", 1);
	if (dup2(data->fds[WRITE], 1) < 0)
		error_exit("Dup failed", 1);
	close (data->fds[READ]);
	close (data->fds[WRITE]);
}

	// dprintf (2, "data->fds[WRITE] %d\n", data->fds[WRITE]);
	// dprintf (2, "STDIN_FILENO %d\n", STDIN_FILENO);
	// dprintf (2, "STDOUT_FILENO %d\n", STDOUT_FILENO);
	// dprintf (2, "data->fds[READ] %d\n", data->fds[READ]);
	// dprintf (2, "STDIN_FILENO %d\n", STDIN_FILENO);
	// dprintf (2, "STDOUT_FILENO %d\n", STDOUT_FILENO);

/*
	Remember!!! man dup2
	 In dup2(), the value of the new descriptor fildes2 is specified.  
	 If fildes and fildes2 are equal, then dup2() just returns fildes2; 
	 no other changes are made to the existing descriptor.  
	 Otherwise, if descriptor fildes2 is already in use, it is first deallocated
	 as if a close(2) call had
     been done first.
	*/