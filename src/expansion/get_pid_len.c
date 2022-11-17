/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pid_len.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 06:27:40 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/17 06:28:01 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

static void	self_pid(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_exit_code = info->si_pid;
}

u_int32_t	get_pid_len(void)
{
	u_int64_t			exit_temp;
	struct sigaction	sig_act;
	pid_t				my_pid;

	exit_temp = g_exit_code;
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.__sigaction_u.__sa_sigaction = self_pid;
	sigaction(SIGUSR1, &sig_act, NULL);
	kill(0, SIGUSR1);
	my_pid = g_exit_code;
	g_exit_code = exit_temp;
	return (ft_digit_len(my_pid));
}