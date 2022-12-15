/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_here.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 19:59:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 21:55:19 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int32_t	wait_here(pid_t child_pid)
{
	int	status;
	int	exit_code;

	exit_code = -1;
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) - 1;
	return (exit_code);
}
